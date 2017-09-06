-- A Lua template file

-- from file: preamble.tex after line: 50

if not modules then modules = { } end modules ['t-diSimp-templates'] = {
    version   = 1.000,
    comment   = "ConTeXt macros for diSimplex papers - templates",
    author    = "PerceptiSys Ltd (Stephen Gaito)",
    copyright = "PerceptiSys Ltd (Stephen Gaito)",
    license   = "MIT License"
}

thirddata              = thirddata        or {}
thirddata.diSimpCoAlgs = thirddata.diSimp or {}

local diSimp     = thirddata.diSimp

local templates  = { }

diSimp.templates = templates

interfaces.writestatus('diSimp', 'loaded diSimp templates')