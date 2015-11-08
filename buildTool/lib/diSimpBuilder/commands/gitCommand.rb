require 'readline'

module DiSimpBuilder

    class GitCommand < Command
    def self.init_with_program(p)
      p.command(:git) do |c|
        c.syntax 'git'
        c.description 'Uses Git to add, commit and then push all recent changes'

        c.action do |args, options|
          begin
            puts ""
            system('git status')
            commitMessage = Readline.readline( "\n^C to abort\ncommit message: ", true)
            system('git add -A')
            system("git commit -m \"#{commitMessage}\"")
            system('git push')
          rescue Exception
            puts ""
          end
        end
      end
    end
  end


  class CleanCommand < Command
    def self.init_with_program(p)
      p.command(:clean) do |c|
        c.syntax 'clean'
        c.description 'Removes the transient TeX files'

        c.action do |args, options|
          begin
            puts ""
            system('rm -rf *.aux *.bbl *.bib *.blg *.log *.out *.synctex.gz *.toc')
          rescue Exception
            puts ""
          end
        end
      end
    end
  end

end

