require 'erb'

module DiSimpBuilder

  module TexUtils

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

    def writeFile(outFilePath, contents, mode = 0644)
      File.chmod(mode, outFilePath) if File.exists?(outFilePath)
      File.write(outFilePath, contents)
      File.chmod(mode, outFilePath)
    end
  end

  class CreateCommand < Command
    extend TexUtils

    def self.init_with_program(p)
      documentTypes = { 'article' => 'art', 'book' => 'book' }
      p.command(:create) do |c|
        c.syntax "create { #{documentTypes.keys.sort.join(' | ')} }"
        c.description 'Creates an initial LaTeX document of the requested type'
        c.action do |args, options|
          if args.empty? then
            c.logger.error "Please choose a LaTeX document type"
            puts c
            exit(-1)
          end
          computeTexConfiguration(options)
          requestedDocumentType = args[0].strip
          if documentTypes.has_key?(requestedDocumentType) then
            Conf.documentType = documentTypes[requestedDocumentType]
            Conf.isBook = false;
            Conf.isBook = true if Conf.documentType == 'book'
          else
            c.logger.error "You can only choose one of the following document types #{documentTypes.keys.sort.join(', ')}"
            puts c
            exit(-1)
          end
          Conf.texDirectories.each do | aDir |
            template = File.read(File.join($globalLib, 'diSimpBuilder', 'templates', 'paperName.tex.erb'))
            contents = ERB.new(template).result(binding())
            writeFile(File.join(aDir, "#{Conf.paper.name}.tex"), contents)

            template = File.read(File.join($globalLib, 'diSimpBuilder', 'templates', 'frontMatter.tex.erb'))
            contents = ERB.new(template).result(binding())
            writeFile(File.join(aDir, "frontMatter.tex"), contents)

            writeFile(File.join(aDir, "#{Conf.paper.name}.bib"), "")

#            writeFile(File.join(aDir, "includeAll.tex"), "")

#            writeFile(File.join(aDir, "tikzAll.tex"), "")
          end
        end
      end
    end
  end

  class InitCommand < Command
    extend TexUtils

    def self.init_with_program(p)
      p.command(:init) do |c|
        c.syntax 'init'
        c.description 'Initialize the git repository hooks'
        c.action do |args, options|
          computeTexConfiguration(options)
          template = File.read(File.join($globalLib, 'diSimpBuilder', 'templates', 'post-xxx-sample.erb'))
          hook     = ERB.new(template).result(binding())
          [ 'post-checkout', 'post-commit', 'post-merge'].each do |aFileName|
            outFilePath = File.join('.git', 'hooks', aFileName)
            writeFile(outFilePath, hook, 0755)
          end
          template = File.read(File.join($globalLib, 'diSimpBuilder', 'templates', 'latexGitIgnore.erb'))
          gitIgnore = ERB.new(template).result(binding())
          Conf.texDirectories.each do | aDir |
            writeFile(File.join(aDir, '.gitignore'), gitIgnore)
          end
        end
      end
    end
  end

end
