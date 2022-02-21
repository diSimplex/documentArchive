# This ruby library provides a collection of functions for use in the 
# diSimplex cookbook recipes.

def doReleases(releaseName, releaseArea, releaseVersion, &block)
  doARelease(releaseName, releaseArea, releaseVersion, 'full', &block)
  doARelease(releaseName, releaseArea, releaseVersion, 'draft', &block)
end

def doARelease(releaseName, releaseArea, releaseVersion, releaseType, &block)
  releaseTypeEnvKey  = releaseType.upcase
  releaseTypeConfKey = releaseType.to_sym
  if ENV[releaseTypeEnvKey] then 
    if releaseVersion == ENV[releaseTypeEnvKey] then
      if Conf.global.has_key?(:diSimplex) &&    
         Conf.global.diSimplex.has_key?(:release) &&
         Conf.global.diSimplex.release.has_key?(releaseTypeConfKey) &&
         Conf.global.diSimplex.release[releaseTypeConfKey].has_key?(:gitHubPages)  then
        projectRepo = "#{Conf.global.diSimplex.release[releaseTypeConfKey].gitHubPages}/#{Conf.project.name}/#{releaseArea}"
        releaseRepo = "#{Conf.texStyle.name}-#{Conf.texStyle.version}"
        releaseRepo << "-draft" if releaseType =~ /draft/
        releaseDir  = "#{projectRepo}/#{releaseRepo}"
        ensureDirExists(releaseDir);
        puts "\nReleasing to [#{releaseDir}]"
        block.call(projectRepo, releaseRepo, releaseDir)
      else
        puts <<EOT

==============================================================================
To do a #{releaseType} release you must specify the local location of 
your #{releaseType} release GitHubPages repository in:
  Conf.global.diSimplex.release.#{releaseTypeConfKey}.gitHubPages
==============================================================================

EOT
      end
    else
      puts <<EOT

==============================================================================
#{releaseName} #{releaseType} version (#{releaseVersion}) 
and requested #{releaseType} release version (#{ENV[releaseTypeEnvKey]})
do NOT agree. NOT releasing globally
==============================================================================

EOT
    end
  else 
    puts <<EOT

==============================================================================
No #{releaseTypeEnvKey}=x.y.z supplied... only releasing locally 
==============================================================================

EOT
  end
end
