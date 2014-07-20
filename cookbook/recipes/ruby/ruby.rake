

# Helper tasks for RSpec testing
#
# Integration tests against a stable running application instance
#
iSpecs = FileList.new('design/**/*ISpec.rb');
task :ispecs do
  # TODO: startup application
  sh("rspec -fs #{iSpecs}") unless iSpecs.empty?
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
aSpecs = FileList.new('design/**/*ASpec.rb');
task :aspecs do
  sh("rspec -fs #{aSpecs}") unless aSpecs.empty?
end
#
task 'ls:aspecs' do
  puts aSpecs
end
#
# Unit tests against the application's implementational use of the Rack 
# stack
# 
rSpecs = FileList.new('design/**/*RSpec.rb');
task :rspecs do
  sh("rspec -fs #{rSpecs}") unless rSpecs.empty?
end
#
task 'ls:rspecs' do
  puts rSpecs
end
#
# Unit tests against individual parts of the application implementation
# 
uSpecs = FileList.new('design/**/*USpec.rb');
task :uspecs do
  sh("rspec -fs #{uSpecs}") unless uSpecs.empty?
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

