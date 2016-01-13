require 'erb'

module DiSimpBuilder

  module RacketUtils

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

    def extractRacketCodeFrom(texFileName)
      texFile   = File.open(texFileName, "r")
      if (texFile.nil?) then
        puts "Could not open (la)tex file: [#{texFileName}]"
        return
      end
      racketFileName = 'generatedRacketCode/'+texFileName.sub(/\.tex$/,'.rkt')
      racketFile = File.open(racketFileName, "w")
      if (racketFile.nil?) then
        puts "Could not open racket file: [#{racketFileName}]"
        return
      end
      racketFile.puts "#! /usr/bin/env racket"
      racketFile.puts "#lang racket"

      puts "Processing [#{texFileName}]"
  
      outsideRacket = true
      lineNumber = 0
 
      texFile.each_line do | aLine |
        lineNumber+=1
        aLine.chomp!
        if (outsideRacket) then
          next if (aLine =~ /^[ \t]*$/)
          if (aLine =~ /^[ \t]*\\racketRequire\{([^\}]+)\}/) then
            requiredFileName = $1
            racketFile.puts "\n;; require racket module from #{texFileName}(#{lineNumber})"
            racketFile.puts "(require \"#{requiredFileName}\")"
          end
          if (aLine =~ /^[ \t]*\\begin\{racket/) then
#            puts ""
            racketFile.puts "\n;; begin racket code from #{texFileName}(#{lineNumber})\n\n"
            outsideRacket = false
          end
        else
          if (aLine =~ /^[ \t]*\\end\{racket/) then
#            puts ""
            racketFile.puts "\n;; end racket code from #{texFileName}(#{lineNumber})\n\n"
            outsideRacket = true
          else
            aLine.gsub!(/\t/, '  ')
#            aLine.gsub!(/^%pragma /,'')
#            aLine.gsub!(/\\mapsTo/, '->')
#            aLine.gsub!(/\\/,'')
#            puts "#{racketFileName}[#{lineNumber}]:#{aLine}"
            racketFile.puts aLine
          end
        end
      end
      racketFile.chmod(0755)
      racketFile.close
    end

    def writeFile(outFilePath, contents, mode = 0644)
      File.chmod(mode, outFilePath) if File.exists?(outFilePath)
      File.write(outFilePath, contents)
      File.chmod(mode, outFilePath)
    end
  end

  class RacketCommand < Command
    extend RacketUtils

    def self.init_with_program(p)
      p.command(:racket) do |c|
        c.alias :rkt
        c.syntax "racket"
        c.description 'extract and compile Racket code'
        c.action do |args, options|
          computeTexConfiguration(options)
          Conf.texDirectories.each do | aDir |
            Dir.chdir(aDir) do
              puts "Compiled Racket"
              puts "PWD: #{Dir.getwd}"
              if (File.directory?("generatedRacketCode")) then
                system("rm -rf generatedRacketCode/*");
              else
                system("rm -rf generatedRacketCode");
                system("mkdir generatedRacketCode");
              end
              Dir.glob("*.tex").each do | aTexFile |
                extractRacketCodeFrom(aTexFile)
              end
              system "generatedRacketCode/#{Conf.paper.name}.rkt"
            end
          end
        end
      end
    end
  end

end
