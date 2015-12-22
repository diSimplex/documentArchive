require 'erb'

module DiSimpBuilder

  module GuileUtils

    def computeTexConfiguration(options)
      Conf.addDefaults do
        Conf.paper = Hash.new
        Conf.paper.name = Dir.pwd.sub(/\/+$/,'').split(/\//).last
      end
      Conf.loadConfiguration(options)
      Conf.texDirectories = Array.new
      if File.directory?("tex") then
        Conf.texDirectories.push('tex') 
      else
        Conf.texDirectories.push('.') 
      end
    end

    def extractGuileCodeFrom(texFileName)
      texFile   = File.open(texFileName, "r")
      if (texFile.nil?) then
        puts "Could not open (la)tex file: [#{texFileName}]"
        return
      end
      guileFileName = 'generatedGuileCode/'+texFileName.sub(/\.tex$/,'.guile')
      guileFile = File.open(guileFileName, "w")
      if (guileFile.nil?) then
        puts "Could not open guile file: [#{guileFileName}]"
        return
      end
      guileFile.puts "#!/usr/bin/guile -s"
      guileFile.puts "!#"

      puts "Processing [#{texFileName}]"
  
      outsideGuile = true
      lineNumber = 0
 
      texFile.each_line do | aLine |
        lineNumber+=1
        aLine.chomp!
        if (outsideGuile) then
          next if (aLine =~ /^[ \t]*$/)
          if (aLine =~ /^[ \n]*\\begin\{guile\}/) then
            puts ""
            guileFile.puts "\n;; #{texFileName}(#{lineNumber})\n\n"
            outsideGuile = false
          end
        else
          if (aLine =~ /^[ \n]*\\end\{guile\}/) then
            puts ""
            guileFile.puts "\n;; #{texFileName}(#{lineNumber})\n\n"
            outsideGuile = true
          else
            aLine.gsub!(/\t/, '  ')
#            aLine.gsub!(/^%pragma /,'')
#            aLine.gsub!(/\\mapsTo/, '->')
#            aLine.gsub!(/\\/,'')
#            puts "#{guileFileName}[#{lineNumber}]:#{aLine}"
            guileFile.puts aLine
          end
        end
      end
      guileFile.chmod(0755)
      guileFile.close
    end

    def writeFile(outFilePath, contents, mode = 0644)
      File.chmod(mode, outFilePath) if File.exists?(outFilePath)
      File.write(outFilePath, contents)
      File.chmod(mode, outFilePath)
    end
  end

  class GuileCommand < Command
    extend GuileUtils

    def self.init_with_program(p)
      p.command(:guile) do |c|
        c.syntax "guile"
        c.description 'extract and compile Guile code'
        c.action do |args, options|
          computeTexConfiguration(options)
          Conf.texDirectories.each do | aDir |
            Dir.chdir(aDir) do
              puts "Compiled Guile"
              puts "PWD: #{Dir.getwd}"
              if (File.directory?("generatedGuileCode")) then
                system("rm -rf generatedGuileCode/*");
              else
                system("rm -rf generatedGuileCode");
                system("mkdir generatedGuileCode");
              end
              Dir.glob("*.tex").each do | aTexFile |
                extractGuileCodeFrom(aTexFile)
              end
              system "generatedGuileCode/#{Conf.paper.name}.guile"
            end
          end
        end
      end
    end
  end

end
