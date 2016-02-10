# This is a Mercenary based build tool for the diSimplex based papers
Dir.chdir(ARGV.shift)

STDOUT.sync = true
$globalConfig = File.join(ENV['HOME'], '.diSimp', 'config.yaml')
$globalLib = File.join(ENV['HOME'], '.diSimp', 'lib')
$LOAD_PATH.unshift($globalLib)

require 'mercenary'
require 'diSimpBuilder'

# Pre-load diSimpBuilder commands
#
libs = Array.new
libs.push($globalLib)
libs.push(Dir.pwd+'/diSimpLib')
libs.each do |aLib|
  Dir.chdir(aLib) do 
    $LOAD_PATH.unshift Dir.pwd
    Dir[File.join("**", "*.rb")].sort.each do |f|
      next if f =~ /^main.rb$/
      require f
    end
  end if Dir.exists?(aLib)
end

Mercenary.program(:diSimp) do |p|
  p.version DiSimpBuilder::VERSION
  p.description 'diSimp is a build tool for diSimplex based papers'
  p.syntax 'diSimp <subcommand> [options]'

  DiSimpBuilder::Command.subclasses.each { |c| c.init_with_program(p) }

  p.action do |args, options|
    if args.empty?
      puts p
    else
      unless p.has_command?(args.first)
        puts "Invalid command. Use --help for more information"
      end
    end
  end
end

