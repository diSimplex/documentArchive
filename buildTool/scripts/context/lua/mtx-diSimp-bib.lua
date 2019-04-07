if not modules then modules = { } end modules ['diSimp-bib'] = {
    version   = 1.001,
    comment   = "companion to mtxrun.lua",
    author    = "Stephen Gaito, PerceptiSys Ltd",
    copyright = "Stephen Gaito, PerceptiSys Ltd",
    license   = "MIT License"
}

local helpinfo = [[
<?xml version="1.0"?>
<application>
 <metadata>
  <entry name="name">diSimp-bib</entry>
  <entry name="detail">update bibTeX databases</entry>
  <entry name="version">0.10</entry>
 </metadata>
 <examples>
  <category>
   <title>Top level commands</title>
   <subcategory>
    <example><command>help     provides this help</command></example>
    <example><command>bib      extracts bibTeX database for the current paper</command></example>
   </subcategory>
  </category>
  <category>
    <title>diSimplex info</title>
    <subcategory>
      <example><command>More information about the diSimplex project</command></example>
      <example><command>can be found at:</command></example>
      <example><command></command></example>
      <example><command>webpage: http://diSimplex.org</command></example>
    </subcategory>
  </category>
  <category>
  <title>ConTeXt info</title>
  </category>
 </examples>
</application>
]]

local application = logs.application {
  name     = "diSimp-bib",
  banner   = "update BibTeX databases for diSimp papers",
  helpinfo = helpinfo,
}

local report = application.report
local lfs    = require('lfs')
local http   = require('socket.http')
local pp     = require('pl.pretty') -- for use while debugging

scripts               = scripts or { }
scripts.xrefs         = scripts.xrefs or { }
scripts.xrefs.verbose = false

local function saveObj(anObj, aFile, indent)
  if type(anObj) == 'boolean' then
    if anObj then
      aFile:write('true')
    else
      aFile:write('false')
    end
  elseif type(anObj) == 'number' then
    aFile:write(anObj)
  elseif type(anObj) == 'string' then
    aFile:write(string.format('%q',anObj))
  elseif type(anObj) == 'table' then
    aFile:write('{\n')
    for aKey, aValue in pairs(anObj) do
      if type(aKey) == 'string' or type(aKey) == 'number' then
        aFile:write(indent)
        aFile:write(aKey)
        aFile:write(' = ')
        saveObj(aValue, aFile, indent..'  ')
        aFile:write(',\n')
      end
    end
    aFile:write(indent)
    aFile:write('}')
  else
    -- can't do anything with this... so ignore
  end
end

local function extractReferencesFrom(aFile)
  report('loading information from ['..aFile..']')
  local bibFileName = aFile:gsub('%.tuc$', 'Bib.lua')
  local ok = false
  local bibRefs = { }
  if lfs.isfile(bibFileName) then
    report('  trying to load ['..bibFileName..']')
    ok, bibRefs = pcall(dofile, bibFileName)
    if not ok then
      report('    ERROR: ['..bibRefs..']')
      bibRefs = { }
    end
  end
  if not ok then report('  rebuilding ['..bibFileName..']') end
  local tucData = dofile(aFile)
  local collected = tucData.structures.lists.collected
  for i, obj in ipairs(collected) do 
    if obj.userdata then
      if obj.userdata.btxref then
        local citeId = obj.userdata.btxref
        if citeId:match('%?+') then
          report('  ignoring ['..citeId..']')
        else
          if bibRefs[citeId] == nil or bibRefs[citeId]['notFound'] then
            report('  getting ['..citeId..']')
            local prefix = citeId:sub(1,2)
            local url = 'http://noteserver/refs/cite/'..prefix..'/'..citeId..'.lua'
            local body, code = http.request(url)
            if code ~= 200 then
              body = [=[
  return {
    title    = "Unknown-]=]..citeId..[=[",
    author   = "Unknown-]=]..citeId..[=[",
    tag      = "]=]..citeId..[=[",
    notFound = true
  }
]=]
            end
            local ok, refLua = pcall(load, body)
            if ok then refLua = refLua() else refLua = nil end
            if refLua and refLua.tag then
              bibRefs[refLua.tag] = refLua
            end
          end
        end
      end
    end
  end
  report('  creating ['..bibFileName..']')
  local bibFile = io.open(bibFileName, 'w')
  bibFile:write('return ')
  saveObj(bibRefs, bibFile, '  ')
  bibFile:close()
end

local function lookForTUCFiles(aDir)
  local oldDir = lfs.currentdir()
  lfs.chdir(aDir)
  for aFile in lfs.dir('.') do
    if aFile:match('^%.+$') or aFile:match('%.git') then
      -- ignore
    elseif aFile:match('%.tuc$') then 
      extractReferencesFrom(aFile)
    elseif lfs.isdir(aFile) then
      lookForTUCFiles(aFile)
    end
  end
  lfs.chdir(oldDir)
end

report('')

if environment.argument('help') then
  application.help()
elseif 0 < #environment.files then
  for i, aFile in ipairs(environment.files) do
    if aFile:match('%.tuc$') then
      extractReferencesFrom(aFile)
    else
      lookForTUCFiles(aFile)
    end
  end
else
  lookForTUCFiles('.')
end
