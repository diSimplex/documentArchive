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

local relativePaths = {}
local pathSeparator = package.config:sub(1, 1)

local function pushRelativePath(aRelativePath)
  local pp = require 'pl.pretty'
  local aRelativePathDir =
    aRelativePath:gsub('[^'..pathSeparator..']+$', '')
  tInsert(relativePaths, aRelativePathDir)
end

-- repeat after me... this WILL break!!!
--
-- the use of environments.arguments.fulljobname
-- was infered from grep'ing the experimental distribution
-- for fulljobname and finding it defined in the
-- the environment table.
-- (defined in core-sys.lua)
--
pushRelativePath(environment.arguments.fulljobname)

local function popRelativePath()
  pp = require 'pl.pretty'
  texio.write_nl('     relativePaths: ['..pp.write(relativePaths)..']')
  tRemove(relativePaths)
  texio.write_nl('     relativePaths: ['..pp.write(relativePaths)..']')
end

diSimp.popRelativePath = popRelativePath

local function relativeComponent(componentType, componentPath)
  local thisComponentPath = tConcat(relativePaths)..componentPath
  thisComponentPath = file.collapsepath(thisComponentPath, true)
  texio.write_nl('relativeComponent: ['..componentType..']')
  texio.write_nl('relativeComponent: ['..componentPath..']')
  texio.write_nl('relativeComponent: ['..thisComponentPath..']')
  pushRelativePath(componentPath)
  pp = require 'pl.pretty'
  texio.write_nl('     relativePaths: ['..pp.write(relativePaths)..']')
  tex.print({
    '\\'..componentType..' '..thisComponentPath,
    '\\popRelativePath'
  })
end

diSimp.relativeComponent = relativeComponent

-- from file: documentSetup.tex after line: 450

-- repeat after me... this WILL break!!!
--
local function startAppendices(sectionDepth)
  local numbers = structures.documents.data.numbers
  for i=sectionDepth,#numbers,1 do
    numbers[i] = 0
  end
end

diSimp.startAppendices = startAppendices