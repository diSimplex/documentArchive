

# Helper tasks for Busted/RSpec testing
#
# Integration tests against a stable running application instance
#
iSpecs = FileList.new('design/**/*ISpec.lua');
task :ispecs do
  # TODO: startup application
  sh("busted #{iSpecs}") unless iSpecs.empty?
  # TODO: tear down application
end
#
task 'ls:ispecs' do
  puts iSpecs
end
#
# Integration tests against possible unstable running application 
# instances.  Each RSpec specification (file) is responsible for 
# starting their copy of the application using Aruba.
#
aSpecs = FileList.new('design/**/*ASpec.lua');
task :aspecs do
  sh("busted #{aSpecs}") unless aSpecs.empty?
end
#
task 'ls:aspecs' do
  puts aSpecs
end
#
# Unit tests against the application's implementational use of the Rack 
# stack
# 
rSpecs = FileList.new('design/**/*RSpec.lua');
task :rspecs do
  sh("busted #{rSpecs}") unless rSpecs.empty?
end
#
task 'ls:rspecs' do
  puts rSpecs
end
#
# Unit tests against individual parts of the application implementation
# 
uSpecs = FileList.new('design/**/*USpec.lua');
task :uspecs do
  begin
    sh("busted #{uSpecs}") unless uSpecs.empty?
  rescue RuntimeError => e
    puts e.message
  end
end
#
task 'ls:uspecs' do
  puts uSpecs
end
#
# All RSpec specification tests
#
task :specs => [ :uspecs, :rspecs, :aspecs, :ispecs ]
#
task 'ls:specs' => [ 'ls:uspecs', 'ls:rspecs', 'ls:aspecs', 'ls:ispecs' ]

