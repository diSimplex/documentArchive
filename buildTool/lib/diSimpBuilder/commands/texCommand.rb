
module DiSimpBuilder

  class BuildTexCommand < Command
    class << self

      def getCitation(biblatexID, bibFile)
        #
        # normalize the biblatexID and compute the uri path to the citation
        #
        biblatexID[0] = biblatexID[0].downcase
        biblatexUri = biblatexID[0..1]+'/'+biblatexID+'.bib'
        uriPath = Conf.biblatex.uriRoot + biblatexUri
        #
        # get the citation
        #
        wgetCMD = "wget -q -O- #{uriPath}";
        wgetResult = IO.popen(wgetCMD, "r").read
        #
        # check the result
        #
        if wgetResult.empty? then
          #
          # if the result is empty then our reference system does not have 
          # this reference yet... so fake a citation.
          #
          puts "\t\tcould NOT find [#{biblatexID}]"
          bibFile.puts
          bibFile.puts "@article{#{biblatexID},"
          bibFile.puts "  title = {Unknown-#{biblatexID}},"
          bibFile.puts "  author = {Unknown-#{biblatexID}},"
          bibFile.puts "}"
        else
          #
          # A biblatex structure has been found so append it to the *.bib 
          # file
          #
          bibFile.puts

# The following WAS an attempt to ignore unused biblatex fields.
#
# ALAS we are following a LINE oriented approach which is NOT 
# sufficient to reject fields (such as abstracts) which span multiple 
# lines.
#
# To do this properly we probably have to use a BibLatex parser.
#
#          ignoreRegExp = '^\s*$'
#          ignoreRegExp = Conf.biblatex.ignoreFields.join('\s*=|')+'\s*=' if
#            Conf.biblatex.has_key?(:ignoreFields)
#          ignoreRegExp = Regexp.new(ignoreRegExp)

          wgetResult.each_line() do | line |
            next if line =~ /^\s*$/
            next if line =~ /=\s*\{\s*\}/ # ignore empty fields
#            next if line =~ ignoreRegExp
            bibFile.puts line;
          end
        end
      end

      def extractCitations(auxFilePattern, biblatexFileName)
        puts "\n\n\n---------------------------------------------------------"
        puts "Extracting citations"
        #
        # start a hash of all of the biblatexIDs that we HAVE found
        #
        extractedCitations = Hash.new();
        #
        # If the biblateFile already exists...
        # ... then process it to find all of the biblatexIDs we know about
        # (and so do not need to lookup)
        #
        if (File.exists?(biblatexFileName)) then
          if (!File.writable?(biblatexFileName)) then
            #
            # If we can not write to the biblatexFile then there is nothing 
            # we can do!
            #
            puts "Can not write to biblatex file: [#{biblatexFileName}]";
            exit(-2);
          else
            #
            # The biblatexFile exists and we can write to it so... ... 
            # extract all of the entries we know about and place them in the 
            # hash.
            #
            biblatexFile = File.open(biblatexFileName, "r")
            biblatexFile.each_line() do | aLine |
              if aLine =~ /^@/ then
                aLine.chomp!();
                biblatexID = aLine.gsub(/^@[^\{]*\{/,'');
                biblatexID = biblatexID.gsub(/,$/,'');
                extractedCitations[biblatexID] = true;
                puts "\tfound existing biblatex ID: [#{biblatexID}]";
              end
            end
            biblatexFile.close();
          end
        else
          #
          # The biblatexFile does not yet exist...
          # ... so create one with our standard copyright header.
          #
          biblatexFile = File.open(biblatexFileName, "w")
          if Conf.has_key?(:copyrightLicenseHeader) then
            header = IO.read(Conf.copyrightLicenseHeader);
            biblatexFile.puts(header);
          end
          biblatexFile.puts('');
          biblatexFile.close();
        end  
        #
        # now reopen the biblatexFile for appending new citation entries
        #
        biblatexFile = File.open(biblatexFileName, "a");
        #
        # step through the *.aux file looking for \citation entries
        #
        Dir.glob(auxFilePattern) do | auxFileName |  
          File.open(auxFileName, "r").each_line() do | auxLine |
#            if (auxLine =~ /citation\{(.*)\}/) then
            if (auxLine =~ /\@aux\@cite\{(.*)\}/) then
              biblatexID = $1;
              #
              # normalize the biblatexID (first letter MUST be lowercase)
              #
              biblatexID[0] = biblatexID[0].downcase
              #
              if (!extractedCitations.has_key?(biblatexID)) then
                puts "\textracting citation [#{biblatexID}]";
                getCitation(biblatexID, biblatexFile);
                extractedCitations[biblatexID] = true;
              end
            end
          end
        end
        biblatexFile.close()
        puts "Finished extracting citations"
        puts "---------------------------------------------------------\n\n\n"
      end

      def buildBiblatexDB
        bibDependencies = [ Conf.paperName+'.aux' ];
        bibDependencies.concat(Conf.texFiles);

        doIfNeeded(Conf.paperName+'.bib', bibDependencies) do
          system "pdflatex -synctex=1 -halt-on-error #{Conf.paperName}.tex"
          extractCitations(Conf.paperName+'.aux', Conf.paperName+'.bib')
          File.unlink(Conf.paperName+'.pdf')
          system "biber #{Conf.paperName}"
        end
      end

      def buildLaTeXDocument
        pdfDependencies = [ Conf.paperName+'.bib' ]
        pdfDependencies.concat(Conf.texFiles)

        doIfNeeded(Conf.paperName+'.pdf', pdfDependencies) do
          system "pdflatex -synctex=1 -halt-on-error #{Conf.paperName}.tex"
          extractCitations(Conf.paperName+'.aux', Conf.paperName+'.bib')
          system "pdflatex -synctex=1 #{Conf.paperName}.tex"
          system "makeindex -s gind.ist #{Conf.paperName}" if
            File.exists?(Conf.paperName+'.idx')
          system "makeindex -s gglo.ist -o #{Conf.paperName}.gls #{Conf.paperName}.glo" if
            File.exists?(Conf.paperName+'.glo')
          system "pdflatex -synctex=1 #{Conf.paperName}.tex"
          system "pdflatex -synctex=1 #{Conf.paperName}.tex"
        end
      end

      def loadConfiguration(options)
        Conf.addDefaults do
          Conf.paperName = Dir.pwd.sub(/\/+$/,'').split(/\//).last
        end
        Conf.addNormalizations do 
          Conf.biblatex.uriRoot += '/' unless
            Conf.biblatex.uriRoot =~ /\/$/
        end
        Conf.loadConfiguration(options)
      end

      def init_with_program(p)
        p.command(:latex) do |c|
          c.alias(:tex)
          c.syntax 'latex'
          c.description 'Build a LaTeX document.'
          c.option 'force', '-f', '--force', 'Force creation even if path already exists.'
          c.option 'blank', '-b', '--blank', 'Creates scaffolding but with empty files.'

          c.action do |args, options|
            loadConfiguration(options)
            doIn('tex') do
              Conf.texFiles = Dir.glob('**/*.tex')
              buildBiblatexDB
              buildLaTeXDocument
            end
          end
        end # :tex command

        p.command(:bib) do |c|
          c.syntax 'bib'
          c.description 'Collect the citations for a LaTeX document from our reference database.'
          c.option 'force', '-f', '--force', 'Force creation even if path already exists.'
          c.option 'blank', '-b', '--blank', 'Creates scaffolding but with empty files.'

          c.action do |args, options|
            loadConfiguration(options)
            doIn('tex') do
              Conf.texFiles = Dir.glob('**/*.tex')
              buildBiblatexDB
              buildLaTeXDocument
            end
          end
        end # :bib command

        p.command(:wc) do |c|
          c.syntax 'wc'
          c.description 'Store the current version in the working copy repository'
          
          c.action do |args, options|
            loadConfiguration(options)
            doIn('tex') do
              if Conf.tex.has_key?(:workingCopyDir) then
                system "echo cp #{Conf.paperName}.pdf #{Conf.tex.workingCopyDir}"
                system "cp #{Conf.paperName}.pdf #{Conf.tex.workingCopyDir}"
              else
                puts "No local working copy directory specified"
              end
            end
          end
        end

      end # init_with_program

    end
  end
end
