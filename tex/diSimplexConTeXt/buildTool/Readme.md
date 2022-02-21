# diSimp build tool

The diSimp build tool is a ConTeXt mtxrun based collection of scripts 
which implement various build actions which you might want to apply to 
a diSimplex paper.

Currently the 'diSimp' tool implements:

1. **bib** a tool to update the paper's bibTeX database

# Requirements

An installation of ConTeXt

# Installation

## Linux (and Mac-OS?)

On a Unix based OS, assuming you have your personal scripts in your 
'~/bin' directory, you can install the diSimp build tool by typing: 

> cp diSimp ~/bin

then type:

> diSimp install

## Windows (or Mac-OS?)

Type:

> mtxrun --script diSimp-install

**NOTE** I do not use Windows or Mac-OS so I can not provide and test 
commands for theses OSs. However skilled users should be able to create a 
batch script (based upon the Linux 'diSimp' script) which works on their 
own platform. In all cases, the 'mtxrun --script diSimp-<subCommand>' 
should work on all platforms. Note that for the 'install' command, 
<subCommand> should be 'install'. 

# Use

Again, on a Linux based OS, you can obtain basic usage information by 
typing:

> diSimp

in any directory containing a diSimplex based ConTeXt paper.

# License

The MIT License (MIT)

Copyright (c) 2017 Stephen Gaito, PerceptiSys Ltd.

Permission is hereby granted, free of charge, to any person obtaining a 
copy of this software and associated documentation files (the 
"Software"), to deal in the Software without restriction, including 
without limitation the rights to use, copy, modify, merge, publish, 
distribute, sublicense, and/or sell copies of the Software, and to 
permit persons to whom the Software is furnished to do so, subject to 
the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
