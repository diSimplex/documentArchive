# Tex tasks:

require 'rake/clean'

namespace :tex do

  def getCitation(biblatexID, bibFile)
    #
    # normalize the biblatexID and compute the uri path to the citation
    #
    biblatexID[0] = biblatexID[0].downcase
    biblatexUri = biblatexID[0..1]+'/'+biblatexID+'.bib'
    uriPath = Conf.global.tex.biblatexUriRoot+biblatexUri
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
      wgetResult.each_line() do | line |
        next if line =~ /^\s*$/
        bibFile.puts line;
      end
    end
  end

  def extractCitations(auxFilePattern, biblatexFileName)
    puts "\n\n\n--------------------------------------------------------------"
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
      header = IO.read("/home/stg/ExpositionGit/tools/texmf/copyrightLicenseHeader.tex");
      biblatexFile = File.open(biblatexFileName, "w")
      biblatexFile.puts(header);
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
        if (auxLine =~ /citation\{(.*)\}/) then
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
    puts "--------------------------------------------------------------\n\n\n"
  end

  def appendExtension(nameArray, fileExtension)
    results = [];
    nameArray.each do | aName |
      results.push(aName+fileExtension);
    end
    results
  end

  Conf.paper.files = [] unless Conf.paper.has_key?('files');
  Conf.paper.files.unshift(Conf.paper.name);
  texPaperNames = [];
  Conf.paper.files.each do | aName |
    texPaperNames.push("tex/#{aName}");
  end
  texPaperName      = texPaperNames[0];
  texPaperNameArray = [ texPaperName ]

  bibDependencies = [ texPaperName+'.aux' ];
  bibDependencies.concat(appendExtension(texPaperNames, '.tex'));

  file texPaperName+'.bib' => bibDependencies do
    Dir.chdir('tex') do
      if system "pdflatex -synctex=1 -halt-on-error #{Conf.paper.name}.tex" then
        extractCitations(Conf.paper.name+'.aux', Conf.paper.name+'.bib')
      else
        fail "pdflatex(bib) for [#{Conf.paper.name}] failed"
      end
    end
    system "rm -rf #{texPaperName}.pdf"
  end

  pdfDependencies = [ ];
  pdfDependencies.concat(appendExtension(texPaperNameArray, '.bib'));
  pdfDependencies.concat(appendExtension(texPaperNames,     '.tex'));

  file texPaperName+'.pdf' => pdfDependencies do
    Dir.chdir('tex') do
      if system "pdflatex -synctex=1 -halt-on-error #{Conf.paper.name}.tex" then
        extractCitations(Conf.paper.name+'.aux', Conf.paper.name+'.bib')
        system "pdflatex -synctex=1 #{Conf.paper.name}.tex"
        system "makeindex -s gind.ist #{Conf.paper.name}"
        system "makeindex -s gglo.ist -o #{Conf.paper.name}.gls #{Conf.paper.name}.glo"
        system "pdflatex -synctex=1 #{Conf.paper.name}.tex"
        system "pdflatex -synctex=1 #{Conf.paper.name}.tex"
      else
        fail "pdflatex for [#{Conf.paper.name}] failed"
      end
    end
  end

  task :initialClean => texPaperName+'.pdf' do
#    system "cd tex; rm -rf *.aux *.dvi *.idx *.log *.out *.toc *.glo *.gls *.ilg *.ind"
  end

  task :localRelease => :initialClean do
#   do nothing
  end

  task :finalClean => :localRelease do
#    system "cd tex; rm -rf *.sty *.cwl *.tex"
  end

  CLEAN.include(
    '**/*.aux',
    '**/*.glo',
    '**/*.gls',
    '**/*.idx',
    '**/*.ilg',
    '**/*.ind',
    '**/*.lgout',
    '**/*.log',
    '**/*.pdf',
    '**/*.glo',
    '**/*.toc',
    '**/*synctex.gz',
  )

  task :default => :finalClean
end

task :tex => 'tex:default';
