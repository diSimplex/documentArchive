# This texFont recipe contains the tasks required to build and install 
# TeX/LaTeX fonts.

# This cookbook recipe collects and renames the required font 
# description files from the FontForge directory to the working 
# directory. It then proceeds to build the information which is 
# required to install these fonts into the appropraite places in the 
# (TDS/TeXLive) Tex/LaTeX system.
#
# The renaming (roughly) follows the TeX Font Naming scheme (Karl 
# Berry) see: http://www.tug.org/fontname/fontname.pdf
#
# The full process is discussed in Philipp Lehman's "The Font 
# Installation Guide" (Revision 2.14 Dec 2004) which can be found at: 
# http://mirrors.ctan.org/info/Type1fonts/fontinstallationguide/fontinstallationguide.pdf

# NOTE there is a bug in the FontForge's creation of the *.afm files 
# (see 
# http://old.nabble.com/Incorrect-Descender-value-in-generated-afm-for-fonts-lacking-glyphs-with-descenders-td32145012.html 
# ) IF there are only a few glyphs then the Descender value may be 
# wildly incorrect. At the moment the easiest solution is to correct 
# this value by hand in the *.afm files in the fontForgeDir (in the 
# future this ruby script might be extended to automate this 
# correction). The value to use should be the least value listed in the 
# second position of the FontBBox (which should be the least value 
# listed in the second position of the B for each character in the 
# CharMetrics list.

# This cookbook recipe installs the required font files for a 
# TDS/TeXLive TeX/LaTeX system

# The following steps have been taken from Tutorial 2 of Philipp 
# Lehman's "The Font Installation Guide" (Revision 2.14 Dec 2004) which 
# can be found at: 
# http://mirrors.ctan.org/info/Type1fonts/fontinstallationguide/fontinstallationguide.pdf
#
# NOTE that the installation guide's placement of the *.map files 
# conflicts with the more recent TDS ( TeX Directory Structure: 
# http://www.tug.org/tds/ ). Using the TDS ensures that the updmap-sys 
# script finds the *.map files. See: 
# http://www.tug.org/fonts/fontinstall.html

# The following copies any (new/changed) font files to the correct 
# location in the TDS
#

# Once the new TeX fonts have been installed (see below) ...
#
# TO TEST the new TeX/LaTeX fonts type (in the texFontsDir):
#   $ tex testfont # or pdftex testfont ... Name of the font to test = 
#   tfm-8t-or-8r-name-without-.tfm ... *\table *\bye
#
# (we need to use the font name associated to the TeX standard encoding 
# (8r) or the T1-Cork encoding (8t) )

# This cookbook recipe removes a TeXFontFamily from the local font directories

# The following steps have been taken from Tutorial 2 of Philipp Lehman's
# "The Font Installation Guide" (Revision 2.14 Dec 2004)
# which can be found at:
# http://mirrors.ctan.org/info/Type1fonts/fontinstallationguide/fontinstallationguide.pdf
#
# NOTE that the installation guide's placement of the *.map files conflicts
# with the more recent TDS ( TeX Directory Structure: http://www.tug.org/tds/ ).
# Using the TDS ensures that the updmap-sys script finds the *.map files. See:
# http://www.tug.org/fonts/fontinstall.html

namespace :texFonts do

  task :cleanFonts do
    system "rm -rf #{Conf.texFont.texFonts.dir}"
    ensureDirExists Conf.texFont.texFonts.dir
  end

  task :buildFonts => :cleanFonts do
    texFontsName = Conf.texFont.texFonts.fontName;
    texFontsDir = Conf.texFont.texFonts.dir;
    fontForgeName = Conf.texFont.fontForge.fontName;
    fontForgeDir = Conf.texFont.fontForge.dir;

    puts "building TeX font family [#{texFontsName}]";
    puts "\tusing [#{fontForgeName}]";

    system("cp #{fontForgeDir}/#{fontForgeName}.afm #{texFontsDir}/#{texFontsName}r8a.afm");
    system("cp #{fontForgeDir}/#{fontForgeName}.pfb #{texFontsDir}/#{texFontsName}r8a.pfb");
  
    File.open("#{texFontsDir}/#{texFontsName}-fontinst.tex", "w") do | finst |
      finst.puts "\\input fontinst.sty";
      finst.puts "\\needsfontinstversion{1.926}";
      finst.puts "\\recordtransforms{#{texFontsName}-rec.tex}";
      finst.puts "\\transformfont{#{texFontsName}r8r}{\\reencodefont{8r}{\\fromafm{#{texFontsName}r8a}}}";
      finst.puts "\\installfonts";
      finst.puts "\\installfamily{T1}{#{texFontsName}}{}";
      finst.puts "\\installfont{#{texFontsName}r8t}{#{texFontsName}r8r,newlatin}{t1}{T1}{#{texFontsName}}{m}{n}{}";
      finst.puts "\\endinstallfonts";
      finst.puts "\\endrecordtransforms";
      finst.puts "\\bye";
    end

    File.open("#{texFontsDir}/#{texFontsName}-map.tex", "w") do | fmap |
      fmap.puts "\\input finstmsc.sty";
      fmap.puts "\\resetstr{PSfontsuffix}{.pfb}";
      fmap.puts "\\adddriver{dvips}{#{texFontsName}.map}";
      fmap.puts "\\input #{texFontsName}-rec.tex";
      fmap.puts "\\donedrivers";
      fmap.puts "\\bye";
    end

    # The following steps to build this family of fonts is taken from 
    # Tutorial 2 of Philipp Lehman's guild (see above).
    Dir.chdir(texFontsDir) do
      system("tex #{texFontsName}-fontinst.tex");
      system("for file in *.pl; do pltotf $file; done");
      system("for file in *.vpl; do vptovf $file; done");
      system("tex #{texFontsName}-map.tex");
    end
  end

  task :packageFiles => :buildFonts do
    templatePath = Conf.find_resource("texFonts/templates/");
    applyTemplate(templatePath+'readme.md.erb',
                  "texFont/package/#{Conf.texFont.name}-readme.md");
    applyTemplate(templatePath+'uninstall.sh.erb',
                  "texFont/package/#{Conf.texFont.name}-uninstall.sh");
    system "chmod a+x texFont/package/*.sh";
  end

  task :packageFonts => :packageFiles do
    abort "NEED TO UPDATE GLOBAL RELEASE TASK"

    localFontDir = "ctanRepo/#{Conf.texFont.name}"
    ensureDirExists(localFontDir);

    texFontsDir  = Conf.texFont.texFonts.dir;

    Conf.texFont.fontPaths.each do | aPathArray |
      ensureDirExists "#{localFontDir}/#{aPathArray[0]}"
      system "cp #{texFontsDir}/*.#{aPathArray[1]} #{localFontDir}/#{aPathArray[0]}"
    end

    system "cp texFont/package/* #{localFontDir}"

    system "cd ctanRepo; zip -r #{Conf.texFont.name}.zip #{Conf.texFont.name}";
  end

end


task :cleanFonts   => 'texFonts:cleanFonts';
task :buildFonts   => 'texFonts:buildFonts';
task :packageFonts => 'texFonts:packageFonts';
