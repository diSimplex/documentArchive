require 'readline'

module DiSimpBuilder

  class CheckCommand < Command
    def self.init_with_program(p)
      p.command(:check) do |c|
        c.syntax 'check'
        c.description 'Checks all proofs in the TeX files'

        c.action do |args, options|
          begin
            puts ""
            puts "Please install the Racket diSimp package"
          rescue Exception
            puts ""
          end
        end
      end
    end
  end

end

