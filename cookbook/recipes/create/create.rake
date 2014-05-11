# The rake task definitions for the create tasks

# We ensure gitinfo and latex-git-log are both integrated into our 
# paper's git repository
#
# see: http://www.ctan.org/tex-archive/macros/latex/contrib/gitinfo
# see: http://www.ctan.org/tex-archive/support/latex-git-log
#

namespace :create do
  Conf.paper.fileName = 'tex/' + Conf.paper.name + '.tex';
  templateFiles = [
    '.git/hooks/post-commit',
    '.git/hooks/post-checkout',
    '.git/hooks/post-merge',
    '.git/hooks/latex-git-log',
    '.gitignore.d/git-gitignore',
    '.gitignore.d/java-gitignore',
    '.gitignore.d/latex-gitignore',
    '.gitignore.d/scala-gitignore',
    '.gitignore.d/font-gitignore',

    'tex/frontMatter.tex',
    'tex/options.tex'
  ];

  task :config do
    Conf.cookbook.create = Hash.new unless Conf.cookbook.has_key?(:create)
    Conf.cookbook.create.templatePath = Conf.find_resource('create/templates/');
  end

  templateFiles.each do | aTemplateFile |
    templateFileName = aTemplateFile.sub(/^\./,'');
    file aTemplateFile do
      applyTemplate(Conf.cookbook.create.templatePath+templateFileName+'.erb',
                    aTemplateFile);
      next unless (aTemplateFile =~ /post-/) or (aTemplateFile =~ /-git-/);
      File.chmod(0755, aTemplateFile);
    end
  end

  file Conf.paper.fileName do
    applyTemplate(Conf.cookbook.create.templatePath+'tex/document.tex.erb',
                  Conf.paper.fileName);
  end

  task :cleanHooks do
    templateFiles.each do | aTemplateFile |
      next unless (aTemplateFile =~ /post-/) or (aTemplateFile =~ /-git-/);
      File.unlink(aTemplateFile);
    end
  end

  # Ensure we have an up to date .gitignore
  #
  gitIgnoreParts = FileList.new( '.gitignore.d/*-gitignore')
  file '.gitignore' => gitIgnoreParts do
    puts "cat `ls .gitignore.d/*-gitignore'` > .gitignore"
    system "cat `ls .gitignore.d/*-gitignore` > .gitignore"
  end

  task :default => '.gitignore';
  task :default => templateFiles;
  task :default => Conf.paper.fileName;

end

task :cookConfig => 'create:config';

task :create => 'create:default';

task :cleanHooks => 'create:cleanHooks';
