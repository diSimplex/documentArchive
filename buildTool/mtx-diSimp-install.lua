if not modules then modules = { } end modules ['diSimp-install'] = {
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
  <entry name="name">diSimp-install</entry>
  <entry name="detail">diSimp installation tool</entry>
  <entry name="version">0.10</entry>
 </metadata>
 <examples>
  <category>
   <title>Top level commands</title>
   <subcategory>
    <example><command>help     provides this help</command></example>
    <example><command>install  installs the diSimp command</command></example>
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
  name     = "diSimp-install",
  banner   = "diSimplex installation tool",
  helpinfo = helpinfo,
}

local report = application.report
local lfs    = require('lfs')
local pp     = require('pl.pretty') -- for use while debugging

scripts               = scripts or { }
scripts.xrefs         = scripts.xrefs or { }
scripts.xrefs.verbose = false

if environment.argument("help") then
  application.help()
else
  --
  -- do the installation
  --
  local oldDir = lfs.currentdir()
  --
  -- create texmf directories
  --
  report('')
  local texmfDir = resolvers.resolve('home:texmf')
  report('creating directories in ['..texmfDir..']')
  lfs.chdir(texmfDir)
  lfs.mkdir('scripts')
  lfs.mkdir('scripts/context')
  lfs.mkdir('scripts/context/lua')
  lfs.chdir(oldDir)
  --
  -- copy mtx-diSimp-* files
  --
  report('')
  local installDir = texmfDir..'/scripts/context/lua'
  report('copying scripts to ['..installDir..']')
  lfs.chdir('scripts/context/lua')
  for aFileName in lfs.dir('.') do
    if lfs.attributes(aFileName).mode == "file" then
      local targetFile = installDir..'/'..aFileName
      report('')
      report(' copying ['..aFileName..']')
      report('  to ['..targetFile..']')
      
      aFile    = io.open(aFileName, 'r')
      aFileStr = aFile:read("*a")
      aFile:close()

      outFile = io.open(targetFile, 'w')
      outFile:write(aFileStr)
      outFile:close()
    end
  end
  --
  -- run generate command (taken from mtxrun)
  --
  report('')
  report('re-indexing TeX files')
  report('')
  report('----------------------------------------------------------------------')
  resolvers.renewcache()
  trackers.enable("resolvers.locating")
  resolvers.load()
  report('----------------------------------------------------------------------')
  report('')
  report('done')
  --
  -- clean up
  --
  lfs.chdir(oldDir)
  
  
end
