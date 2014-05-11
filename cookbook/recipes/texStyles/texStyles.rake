# TexStyle tasks:
namespace :texStyles do

  Conf.texStyle.install = false unless Conf.texStyle.has_key?(:install);

  def extractTXScwlFile(inputFilePath, outputFilePath)
    inputFile  = File.open(inputFilePath, "r");
    outputFile = File.open(outputFilePath, "w");
    #TODO we need to switch from %TXS to %txsBeginComment/%txsEndComment
    inTxsComment = false;
    inputFile.each_line do | aLine |
      if inTxsComment then
        if aLine =~ /^%txsEndComment/ then
          inTxsComment = false;
          next;
        end
        outputFile.puts("# "+aLine);
        next;
      end

      if aLine =~ /^%txsBeginComment/ then
        inTxsComment = true;
        next;
      end

      next unless aLine =~ /^\%txs/;

      outputFile.puts(aLine.sub(/^\%txs/,''));
    end
    outputFile.close;
    inputFile.close;
  end

  def appendExtension(nameArray, fileExtension)
    results = [];
    nameArray.each do | aName |
      results.push(aName+fileExtension);
    end
    results
  end

  Conf.texStyle.files = [] unless Conf.texStyle.has_key?(:files);
  Conf.texStyle.files.unshift(Conf.texStyle.name);
  texStyleNames = [];
  Conf.texStyle.files.each do | aName |
    texStyleNames.push("texStyle/#{aName}");
  end
  texStyleName = texStyleNames[0];

  pdfDependencies = [ ];
  pdfDependencies.concat(appendExtension(texStyleNames, '.dtx'));
  pdfDependencies.concat(appendExtension(texStyleNames, '.sty'));

  texStyleNames.each do | aName |
    subName = aName.sub(/^texStyle\//,'');

    # create the TeXStudio CWL file
    file aName+'.cwl' => aName+'.dtx' do
      extractTXScwlFile(aName+'.dtx', aName+'.cwl');
    end

    # create the style files
    file aName+'.sty' => [ aName+'.dtx', texStyleName+'.ins' ] do
      Dir.chdir('texStyle') do
        system "pdflatex #{Conf.texStyle.name}.ins"
      end
    end

    # create any test files
    file aName+'-test.tex' => [ aName+'.dtx', texStyleName+'.ins' ] do
      Dir.chdir('texStyle') do
        system "pdflatex #{Conf.texStyle.name}.ins"
      end
    end

    file aName+'.pdf' => pdfDependencies do
      Dir.chdir('texStyle') do
        if system "pdflatex -synctex=1 -halt-on-error #{subName}.dtx" then
          system "makeindex -s gind.ist #{subName}"
          system "makeindex -s gglo.ist -o #{subName}.gls #{subName}.glo"
          system "pdflatex -synctex=1 #{subName}.dtx"
          system "pdflatex -synctex=1 #{subName}.dtx"
        else
          fail "pdflatex failed"
        end
      end
    end

    testResult = aName+'-test.lgout';
    testFile   = aName+'-test.tex';
    file testResult => testFile do
      Dir.chdir("texStyle") do 
        system "pdflatex -halt-on-error #{testFile.sub(/^texStyle\//,'')}"
      end
    end
    task :tstest => testResult;
  end

  task :tsdoc => appendExtension(texStyleNames,'.pdf');

  defaultDependencies = [];
  defaultDependencies.concat(appendExtension(texStyleNames, '.pdf'));
  defaultDependencies.concat(appendExtension(texStyleNames, '.sty'));
  defaultDependencies.concat(appendExtension(texStyleNames, '.cwl'));
  defaultDependencies.concat(appendExtension(texStyleNames, '-test.lgout'));
   
  task :initialClean => defaultDependencies do
    system "cd texStyle; rm -rf *.aux *.dvi *.idx *.log *.out *.toc *.glo *.gls *.ilg *.ind"
  end

  task :globalReleases => :initialClean do
    require 'diSimplexRake'
    doReleases('TeXStyle', 'ctanRepo', Conf.texStyle.version) do | projectRepo, releaseRepo, releaseDir |
      system "cd texStyle; cp *.dtx *.ins *.pdf *.sty *.cwl *.tex #{releaseDir}"
      system "cp Readme.md #{releaseDir}/README"
      system "cd #{projectRepo}; zip -r #{releaseRepo}.zip #{releaseRepo}"
    end
  end

  task :localRelease => :globalReleases do
    if Conf.global.has_key?(:texStudio) && 
       Conf.global.texStudio.has_key?(:localConfDir) &&
       Dir.exists?(Conf.global.texStudio.localConfDir) then
      system "cp texStyle/*.cwl #{Conf.global.texStudio.localConfDir}";
    end
    if Conf.global.has_key?(:texStyle) &&
       Conf.global.texStyle.has_key?(:localConfDir) && 
       Dir.exists?(Conf.global.texStyle.localConfDir) then
      system "mkdir -p #{Conf.global.texStyle.localConfDir}/#{Conf.texStyle.name}";
      system "cd texStyle; cp *.dtx *.ins *.pdf *.sty *.cwl #{Conf.global.texStyle.localConfDir}/#{Conf.texStyle.name}"
    end
  end

  task :finalClean => :localRelease do
    system "cd texStyle; rm -rf *.sty *.cwl *.tex"
  end

  task :default => :finalClean
end

task :texStyleTest => 'texStyles:tstest';
task :tst => :texStyleTest;

task :texStyleDoc => 'texStyles:tsdoc';
task :tsd => :texStyleDoc;

task :texStyle => 'texStyles:default';
task :ts => :texStyle;
