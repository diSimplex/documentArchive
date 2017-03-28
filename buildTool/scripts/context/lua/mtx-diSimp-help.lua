if not modules then modules = { } end modules ['diSimp-help'] = {
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
  <entry name="name">diSimp-help</entry>
  <entry name="detail">ConTeXt cross reference builder</entry>
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
  name     = "diSimp-help",
  banner   = "diSimplex command help",
  helpinfo = helpinfo,
}

local report = application.report
local lfs    = require('lfs')
local pp     = require('pl.pretty') -- for use while debugging

scripts               = scripts or { }
scripts.xrefs         = scripts.xrefs or { }
scripts.xrefs.verbose = false

application.help()
