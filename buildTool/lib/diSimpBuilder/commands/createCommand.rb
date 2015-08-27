require 'erb'

module DiSimpBuilder

  class CreateCommand < Command
    def self.init_with_program(p)
      p.command(:create) do |c|
        c.syntax 'create'
        c.description 'Creates an initial LaTeX document'
        c.action do |args, options|
        end
      end
    end
  end

  class InitCommand < Command
    def self.init_with_program(p)
      p.command(:init) do |c|
        c.syntax 'init'
        c.description 'Initialize the git repository hooks'
        c.action do |args, options|
          Conf.addDefaults do
            Conf.paper = Hash.new
            Conf.paper.name = Dir.pwd.sub(/\/+$/,'').split(/\//).last
          end
          Conf.loadConfiguration(options)
          Conf.texDirectories = Array.new
          Dir.glob(File.join('**', Conf.paper.name+'.tex')) do |aFilePath|
            if aFilePath =~ /^tex/ then
              Conf.texDirectories.push('tex') 
            else
              Conf.texDirectories.push('.') 
            end
          end
          template = File.read(File.join($globalLib, 'diSimpBuilder', 'templates', 'post-xxx-sample.erb'))
          hook     = ERB.new(template).result(binding())
          [ 'post-checkout', 'post-commit', 'post-merge'].each do |aFileName|
            outFilePath = File.join('.git', 'hooks', aFileName)
            File.chmod(0755, outFilePath)
            File.write(outFilePath, hook)
            File.chmod(0755, outFilePath)
          end
          template = File.read(File.join($globalLib, 'diSimpBuilder', 'templates', 'latexGitIgnore.erb'))
          gitIgnore = ERB.new(template).result(binding())
          Conf.texDirectories.each do | aDir |
            File.write(File.join(aDir, '.gitignore'), gitIgnore)
          end
        end
      end
    end
  end

end
