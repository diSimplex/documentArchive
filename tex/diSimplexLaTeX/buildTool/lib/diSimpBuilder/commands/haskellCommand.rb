require 'erb'

module DiSimpBuilder

  module HaskellUtils

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

    def extractHaskellCodeFrom(texFileName)
      texFile   = File.open(texFileName, "r")
      if (texFile.nil?) then
        puts "Could not open (la)tex file: [#{texFileName}]"
        return
      end
      haskellFileName = 'generatedHaskellCode/'+texFileName.sub(/\.tex$/,'.hs')
      haskellFile = File.open(haskellFileName, "w")
      if (haskellFile.nil?) then
        puts "Could not open haskell file: [#{haskellFileName}]"
        return
      end
      haskellFile.puts "-- Haskell code extracted from #{texFileName}"

      puts "Processing [#{texFileName}]"
  
      outsideHaskell = true
      lineNumber = 0
 
      texFile.each_line do | aLine |
        lineNumber+=1
        aLine.chomp!
        if (outsideHaskell) then
          next if (aLine =~ /^[ \t]*$/)
          if (aLine =~ /^[ \n]*\\begin\{haskell/) then
            puts ""
            haskellFile.puts "\n-- #{texFileName}(#{lineNumber})\n\n"
            outsideHaskell = false
          end
        else
          if (aLine =~ /^[ \n]*\\end\{haskell/) then
            puts ""
            haskellFile.puts "\n-- #{texFileName}(#{lineNumber})\n\n"
            outsideHaskell = true
          else
            aLine.gsub!(/\t/, '  ')
#            aLine.gsub!(/^%pragma /,'')
#            aLine.gsub!(/\\mapsTo/, '->')
#            aLine.gsub!(/\\/,'')
#            puts "#{haskellFileName}[#{lineNumber}]:#{aLine}"
            haskellFile.puts aLine
          end
        end
      end
      haskellFile.chmod(0755)
      haskellFile.close
    end

    def writeFile(outFilePath, contents, mode = 0644)
      File.chmod(mode, outFilePath) if File.exists?(outFilePath)
      File.write(outFilePath, contents)
      File.chmod(mode, outFilePath)
    end
  end

  class HaskellCommand < Command
    extend HaskellUtils

    def self.init_with_program(p)
      p.command(:haskell) do |c|
        c.syntax "haskell"
        c.description 'extract and compile Haskell code'
        c.action do |args, options|
          computeTexConfiguration(options)
          Conf.texDirectories.each do | aDir |
            Dir.chdir(aDir) do
              puts "Compiled Haskell"
              puts "PWD: #{Dir.getwd}"
              if (File.directory?("generatedHaskellCode")) then
                system("rm -rf generatedHaskellCode/*");
              else
                system("rm -rf generatedHaskellCode");
                system("mkdir generatedHaskellCode");
              end
              Dir.glob("*.tex").each do | aTexFile |
                extractHaskellCodeFrom(aTexFile)
              end
              system "runhaskell generatedHaskellCode/#{Conf.paper.name}.hs"
            end
          end
        end
      end
    end
  end

end
