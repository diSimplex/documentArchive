require 'readline'

module DiSimpBuilder

  class InstallCommand < Command
    def self.init_with_program(p)
      p.command(:install) do |c|
        c.syntax 'install'
        c.description 'Installs any local diSimp commands'

        c.action do |args, options|
          begin
            if File.exist?("buildTool/diSimp-install") then
              Dir.chdir("buildTool") do
                system("diSimp-install")
              end
            else
              puts ""
              puts "No local diSimp commands to install"
            end
          rescue Exception
            puts ""
          end
        end
      end
    end
  end

end

