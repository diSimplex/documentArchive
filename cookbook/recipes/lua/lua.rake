
require 'rake/clean'

namespace :lua do

  task :cookPreConfig do
    Conf.lua.rock.cModules.each_pair do | moduleName, moduleDetails |
      dllName = 'lua/csrc/'+moduleName.to_s+'.so'
      CLEAN.include(dllName)
      task :buildLuaRock => dllName

      objects = Array.new
      moduleDetails.each_pair do | unitName, unitDetails |

        dependencies = Array.new
        dependencies.push('lua/'+unitName.to_s)
        unitDetails.each do | aFile |
          dependencies.push('lua/'+aFile)
        end
        unitObj = 'lua/'+unitName.to_s.sub(/\.c/, '.o')
        CLEAN.include(unitObj)
        objects.push(unitObj)

        file unitObj => dependencies do
          sh("gcc #{Conf.lua.rock.cflags} -Ilua/csrc -c #{'lua/'+unitName.to_s} -o #{unitObj}")
        end
      end

      file dllName => objects do
        sh("gcc #{Conf.lua.rock.ldflags} -o #{dllName} #{objects.join(' ')}")
      end
    end
  end

  # Helper tasks for CBDD/RSpec testing
  #
  # ALL CBDD tests are UNIT tests (lua does the integration).
  # We use: https://github.com/nassersala/cbdd
  #
  cSpecs = FileList.new('design/**/*CSpec.c');
  task :cspecs do
    cSpecs.each do | aCSpec |
      aCSpecRunner = aCSpec.sub(/\.c$/, '.out')
      sh "clang #{Conf.lua.cbdd.clangFlags} -Ilua/csrc #{aCSpec} #{Conf.lua.cbdd.libFlags} -o #{aCSpecRunner}"
      sh "./#{aCSpecRunner}" if $?
    end
  end

  #
  task 'lsCSpecs' do
    puts cSpecs
  end

  # Helper tasks for Busted/RSpec testing
  #
  # Integration tests against a stable running application instance
  #
  iSpecs = FileList.new('design/**/*ISpec.lua');
  task :ispecs => :buildLuaRock do
    # TODO: startup application
    sh("busted #{iSpecs}") unless iSpecs.empty?
    # TODO: tear down application
  end
  #
  task 'lsISpecs' do
    puts iSpecs
  end
  #
  # Integration tests against possible unstable running application 
  # instances.  Each RSpec specification (file) is responsible for 
  # starting their copy of the application using Aruba.
  #
  aSpecs = FileList.new('design/**/*ASpec.lua');
  task :aspecs => :buildLuaRock do
    sh("busted #{aSpecs}") unless aSpecs.empty?
  end
  #
  task 'lsASpecs' do
    puts aSpecs
  end
  #
  # Unit tests against the application's implementational use of the Rack 
  # stack
  # 
  rSpecs = FileList.new('design/**/*RSpec.lua');
  task :rspecs => :buildLuaRock do
    sh("busted #{rSpecs}") unless rSpecs.empty?
  end
  #
  task 'lsRSpecs' do
    puts rSpecs
  end
  #
  # Unit tests against individual parts of the application implementation
  # 
  uSpecs = FileList.new('design/**/*USpec.lua');
  task :uspecs => :buildLuaRock do
    begin
      sh("busted #{uSpecs}") unless uSpecs.empty?
    rescue RuntimeError => e
      puts e.message
    end
  end
  #
  task 'lsUSpecs' do
    puts uSpecs
  end

end # namespace :lua

task :cookPreConfig => 'lua:cookPreConfig'

#
# All RSpec specification tests
#
desc 'Run all specifications'
task :specs => [ 
  'lua:cspecs',
  'lua:uspecs', 
  'lua:rspecs', 
  'lua:aspecs', 
  'lua:ispecs'
]
#
desc 'List all specifications'
task 'ls:specs' => [ 
  'lua:lsCSpecs',
  'lua:lsUSpecs',
  'lua:lsRSpecs',
  'lua:lsASpecs',
  'lua:lsISpecs'
]

