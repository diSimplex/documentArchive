-- A Lua file

-- from file: preamble.tex after line: 50

-- This is the lua code associated with t-diSimp.mkiv

if not modules then modules = { } end modules ['t-diSimp'] = {
    version   = 1.000,
    comment   = "ConTeXt macros for diSimplex papers -- lua",
    author    = "PerceptiSys Ltd (Stephen Gaito)",
    copyright = "PerceptiSys Ltd (Stephen Gaito)",
    license   = "MIT License"
}

thirddata        = thirddata        or {}
thirddata.diSimp = thirddata.diSimp or {}

local diSimp   = thirddata.diSimp

local tInsert = table.insert
local tConcat = table.concat
local tRemove = table.remove
local tSort   = table.sort
local sFmt    = string.format
local sMatch  = string.match
local toStr   = tostring

interfaces.writestatus('diSimp', "loaded diSimp macros")

-- from file: documentSetup.tex after line: 300

local fullComponentPaths = {}
local pathSeparator      = package.config:sub(1, 1)

local function lastRelativePath()
  return fullComponentPaths[#fullComponentPaths] or ""
end

local function pushRelativePath(aFullPath)
  texio.write_nl('pushRelativePath('..aFullPath..')')
  local pp = require 'pl.pretty'
  local aFullPathDir =
    aFullPath:gsub('[^'..pathSeparator..']+$', '')
  texio.write_nl('  aFullPathDir: ['..pp.write(aFullPathDir)..']')
  if aFullPathDir:sub(-1) ~= '/' then
    aFullPathDir = aFullPathDir..pathSeparator
  end
  tInsert(fullComponentPaths, aFullPathDir)
  texio.write_nl('fullComponentPaths: ['..pp.write(fullComponentPaths)..']')
end

-- repeat after me... this WILL break!!!
--
-- the use of environments.arguments.fulljobname
-- was infered from grep'ing the experimental distribution
-- for fulljobname and finding it defined in the
-- the environment table.
-- (defined in core-sys.lua)
--
pushRelativePath(file.collapsepath(environment.arguments.fulljobname,true))

local function popRelativePath()
  texio.write_nl('popRelativePath()')
  pp = require 'pl.pretty'
  texio.write_nl('fullComponentPaths: ['..pp.write(fullComponentPaths)..']')
  tRemove(fullComponentPaths)
  texio.write_nl('fullComponentPaths: ['..pp.write(fullComponentPaths)..']')
  texio.write_nl('<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<')
end

diSimp.popRelativePath = popRelativePath

local function findDiSimpPath(curBasePath, componentPath, origBasePath)
  texio.write_nl('findDiSimpPath(['..curBasePath..'],['..componentPath..'],['..origBasePath..'])')
  local potentialPath =
    file.collapsepath(curBasePath..componentPath, true)
  if lfs.attributes(potentialPath..'.tex', 'mode') == 'file' then
    texio.write_nl('found: ['..potentialPath..']')
    return potentialPath
  end
  potentialPath =
    file.collapsepath(curBasePath..'doc/'..componentPath, true)
  if lfs.attributes(potentialPath..'.tex', 'mode') == 'file' then
    texio.write_nl('found: ['..potentialPath..']')
    return potentialPath
  end
  if curBasePath == '' or curBasePath == pathSeparator then
    texio.write_nl('no path found using: ['..origBasePath..componentPath..']')
    return file.collapsepath(origBasePath..componentPath, true)
  end
  local newCurBasePath =
    curBasePath:gsub('[^'..pathSeparator..']+'..pathSeparator..'$','')
  return findDiSimpPath(newCurBasePath, componentPath, origBasePath)
end

local function relativeComponent(componentType, componentPath)
  texio.write_nl('>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>')
  texio.write_nl('relativeComponent(['..componentType..'],['..componentPath..'])')
  local basePath = lastRelativePath()
  local thisComponentPath = findDiSimpPath(basePath, componentPath, basePath)
  texio.write_nl(' thisComponentPath: ['..thisComponentPath..']')
  pushRelativePath(thisComponentPath)
  tex.print({
    '\\'..componentType..' '..thisComponentPath,
    '\\popRelativePath'
  })
end

diSimp.relativeComponent = relativeComponent

-- from file: documentSetup.tex after line: 500

-- repeat after me... this WILL break!!!
--
local function startAppendices(sectionDepth)
  local numbers = structures.documents.data.numbers
  for i=sectionDepth,#numbers,1 do
    numbers[i] = 0
  end
end

diSimp.startAppendices = startAppendices