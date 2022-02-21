require 'erb'

module DiSimpBuilder

  module JoyLoLUtils

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

    def extractJoyLoLCodeFrom(texFileName)
      texFile   = File.open(texFileName, "r")
      if (texFile.nil?) then
        puts "Could not open (la)tex file: [#{texFileName}]"
        return
      end
      joyLoLFileName = 'generatedJoyLoLCode/'+texFileName.sub(/\.tex$/,'.joy')
      joyLoLFile = File.open(joyLoLFileName, "w")
      if (joyLoLFile.nil?) then
        puts "Could not open joyLoL file: [#{joyLoLFileName}]"
        return
      end
      joyLoLFile.puts ";; joyLoL code extracted"
      joyLoLFile.puts ";;   from '#{texFileName}'"
      joyLoLFile.puts ";;   on #{DateTime.now}"
      joyLoLFile.puts ";;   by the 'diSimp joy' command"
      joyLoLFile.puts

      puts "Processing [#{texFileName}]"
  
      outsideJoyLoL = true
      lineNumber = 0
 
      texFile.each_line do | aLine |
        lineNumber+=1
        aLine.chomp!
        if (outsideJoyLoL) then
          next if (aLine =~ /^[ \t]*$/)
          if (aLine =~ /^[ \t]*\\joyLoLRequirePkg\{([^\}]+)\}/) then
            requiredPackage = $1
            joyLoLFile.puts "\n;; require joyLoL package from #{texFileName}(#{lineNumber})"
            joyLoLFile.puts "(require #{requiredPackage})"
          end
          if (aLine =~ /^[ \t]*\\joyLoLRequireFile\{([^\}]+)\}/) then
            requiredFileName = $1
            joyLoLFile.puts "\n;; require joyLoL local file from #{texFileName}(#{lineNumber})"
            joyLoLFile.puts "(require \"#{requiredFileName}\")"
          end
          if (aLine =~ /^[ \t]*\\begin\{joyLoL/) then
#            puts ""
            joyLoLFile.puts "\n;; begin joyLoL code from #{texFileName}(#{lineNumber})\n\n"
            outsideJoyLoL = false
          end
        else
          if (aLine =~ /^[ \t]*\\end\{joyLoL/) then
#            puts ""
            joyLoLFile.puts "\n;; end joyLoL code from #{texFileName}(#{lineNumber})\n\n"
            outsideJoyLoL = true
          else
            aLine.gsub!(/\t/, '  ')
#            aLine.gsub!(/^%pragma /,'')
#            aLine.gsub!(/\\mapsTo/, '->')
#            aLine.gsub!(/\\/,'')
#            puts "#{joyLoLFileName}[#{lineNumber}]:#{aLine}"
            joyLoLFile.puts aLine
          end
        end
      end
      joyLoLFile.chmod(0755)
      joyLoLFile.close
    end

    def writeFile(outFilePath, contents, mode = 0644)
      File.chmod(mode, outFilePath) if File.exists?(outFilePath)
      File.write(outFilePath, contents)
      File.chmod(mode, outFilePath)
    end
  end

  class JoyLoLCommand < Command
    extend JoyLoLUtils

    def self.init_with_program(p)
      p.command(:joyLoL) do |c|
        c.alias :joy
        c.syntax "joyLoL"
        c.description 'extract and compile JoyLoL code'
        c.action do |args, options|
          computeTexConfiguration(options)
          Conf.texDirectories.each do | aDir |
            Dir.chdir(aDir) do
              puts "Compiled JoyLoL"
              puts "PWD: #{Dir.getwd}"
              if (File.directory?("generatedJoyLoLCode")) then
                system("rm -rf generatedJoyLoLCode/*");
              else
                system("rm -rf generatedJoyLoLCode");
                system("mkdir generatedJoyLoLCode");
              end
              Dir.glob("*.tex").each do | aTexFile |
                extractJoyLoLCodeFrom(aTexFile)
              end
              system "joyLoL -v generatedJoyLoLCode/#{Conf.paper.name}.joy"
            end
          end
        end
      end
    end
  end

end
