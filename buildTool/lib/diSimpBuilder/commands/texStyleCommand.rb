
module DiSimpBuilder
  class BuildTexStyleCommand < Command
    class << self

      def computeDependencies
        Conf.texStyle.files = [] unless Conf.texStyle.has_key?(:files);
        Conf.texStyle.files.unshift(Conf.texStyle.name);

        Conf.depend = {}
        Conf.depend.pdf = [ ];
        Conf.texStyle.files.each do | aName |
          Conf.depend.pdf.push(aName+'.dtx')
          Conf.depend.pdf.push(aName+'.sty')
        end
      end

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

      def extractTeXStudioCWLfiles
        Conf.texStyle.files.each do | aName |
          doIfNeeded(aName+'.cwl', aName+'.dtx') do
            extractTXScwlFile(aName+'.dtx', aName+'.cwl');
          end
        end
      end

      def buildTexStyles
        Conf.texStyle.files.each do | aName |
          #
          # extract the style files
          #
          doIfNeeded(aName+'.sty', [ aName+'.dtx', Conf.texStyle.name+'.ins' ] ) do 
            system "pdflatex #{Conf.texStyle.name}.ins"
          end
          #
          # build the style files documentation
          #
          doIfNeeded(aName+'.pdf', Conf.depend.pdf) do
            system "pdflatex -synctex=1 -halt-on-error #{aName}.dtx"
            system "makeindex -s gind.ist #{aName}"
            system "makeindex -s gglo.ist -o #{aName}.gls #{aName}.glo"
            system "pdflatex -synctex=1 #{aName}.dtx"
            system "pdflatex -synctex=1 #{aName}.dtx"
          end
        end
      end

      def runTexStyleTests
        Conf.texStyle.files.each do | aName |
          #
          # extract the test scripts
          #
          doIfNeeded(aName+'-test.tex', [ aName+'.dtx', Conf.texStyle.name+'.ins' ]) do
            system "pdflatex #{Conf.texStyle.name}.ins"
          end
          #
          # run the tests
          #
          doIfNeeded(aName+'-test.lgout', aName+'-test.tex') do
            system "pdflatex -halt-on-error #{aName+'-test.tex'}"
          end
        end
      end

      def initialClean
        system "rm -rf *.aux *.dvi *.idx *.log *.out *.toc *.glo *.gls *.ilg *.ind"
      end

      def globalRelease
        doReleases('TeXStyle', 'ctanRepo', Conf.texStyle.version) do | projectRepo, releaseRepo, releaseDir |
          system "cp *.dtx *.ins *.pdf *.sty *.cwl *.tex #{releaseDir}"
          system "cp Readme.md #{releaseDir}/README"
          system "cd #{projectRepo}; zip -r #{releaseRepo}.zip #{releaseRepo}"
        end
      end

      def localRelease
        if Conf.has_key?(:texStudio) && 
           Conf.texStudio.has_key?(:localConfDir) &&
           Dir.exists?(Conf.texStudio.localConfDir) then
          system "cp *.cwl #{Conf.texStudio.localConfDir}";
        end
        if Conf.texStyle.has_key?(:localConfDir) && 
           Dir.exists?(Conf.texStyle.localConfDir) then
           FileUtils.mkdir_p Conf.texStyle.localConfDir  + 
             '/' + Conf.texStyle.name
          system "cp *.dtx *.ins *.pdf *.sty *.cwl #{Conf.texStyle.localConfDir}/#{Conf.texStyle.name}"
        end
      end

      def finalClean
        system "rm -rf *.sty *.cwl *.tex"
      end

      def init_with_program(p)
        p.command(:texStyle) do |c|
          c.alias :ts
          c.syntax 'texStyle'
          c.description 'Build a LaTeX Style.'
          c.option 'force', '-f', '--force', 'Force creation even if path already exists.'
          c.option 'blank', '-b', '--blank', 'Creates scaffolding but with empty files.'
        
          c.action do |args, options|
            Conf.loadConfiguration(options)
            doIn('texStyle') do
              computeDependencies
              buildTexStyles
              runTexStyleTests
              extractTeXStudioCWLfiles
              initialClean
              globalRelease
              localRelease
              finalClean
            end
          end
        end # :texStyle command

      end # init_with_program

    end
  end
end
