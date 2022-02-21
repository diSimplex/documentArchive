
require 'yaml';

class ConfStack

  def initialize(object, method, *args)
    @confStack = Array.new;
    calling(object, method, args);
  end

  def calling(object, method, where, *args)
#    puts "Calling"
#    pp object
#    pp method
#    pp where
#    pp *args
#    puts "END calling"
    @confStack.push([object, method, where, args]) unless
      !@confStack.empty? && 
      @confStack.last[0] == object && 
      @confStack.last[1] == method;
  end

  def reportNoMethodError(errorObject)
#    puts "reportNoMethodError"
#    pp errorObject
#    pp @confStack
#    puts "END reportNoMethodError"

    # Take off the base object (Conf) so that we can use it later to 
    # get the missingKey messages
    #
    confObj = @confStack.shift()[0];

    # Take of the top of the configure stack so we can treat it as the 
    # message which was not found.
    #
    top     = @confStack.pop();

    # Compute the full configuration path to report to the user
    #
    confPath = "Conf";
    @confStack.each do | aStackLevel |
      confPath << '.' + aStackLevel[1].to_s;
    end
    
    # Start by dumping the problem together with the FULL backtrace for 
    # any experienced user.
    #
    puts ""
    puts "Could not find the key [#{top[1].to_s}]";
    puts "in the configuration path [#{confPath}]\n\n";

    puts errorObject.backtrace.join("\n") unless errorObject.backtrace.nil?;

    # Now construct a more user friendly discussion of the problem for 
    # novice users.
    #
    # Start with the problem...
    #
    puts ""
    puts "=================================================================";
    puts ""
    puts "Could not find the key [#{top[1].to_s}]";
    puts "in the configuration path [#{confPath}]\n\n";

    # Now collect the parameter lines they will need to specify 
    # together with any missingKey messages (in reverse order) that the 
    # configuration might have specified.
    #
    missingKey = confObj.missingKey;
    messages = Array.new;
    parameterLines = Array.new;
    indent = "";
    @confStack.each do | aStackLevel |
      parameterLines.push(indent + aStackLevel[1].to_s + ':');
      indent += "  ";
      missingKey = missingKey[aStackLevel[1]] if missingKey.has_key?(aStackLevel[1]);
      messages.unshift(missingKey.delete(:message)) if missingKey.has_key?(:message);
    end

    # Start by printing out any missingKey messages for the missing key 
    # itself.
    #
    missingKey = missingKey[top[1]] if missingKey.has_key?(top[1]);
    puts missingKey[:message] if missingKey.has_key?(:message);

    # Now provide a template of the configuration path that seems to be 
    # missing together with any specific valueMessage associated with 
    # the missing key.
    #
    puts ""
    puts "Please ensure your configuration contains the following lines"
    parameterLines.push(indent + top[1].to_s + ': <<value>>');
    puts "-----------------------------------------------------------------";
    puts parameterLines.join("\n");
    puts "-----------------------------------------------------------------";
    puts missingKey[:valueMessage] if missingKey.has_key?(:valueMessage);

    # Now provide any additional configuration messages found most 
    # specific first.
    #
    puts ""
    puts messages.join("\n\n");
    puts ""

    # Now exit since there is nothing else we can usefully do to 
    # recover
    #
    exit(-1);
  end

end

# The following Construct class was inspired by the Ruby Construct gem.
# Originally written by: 'Kyle Kingsbury'.
# With contributions by: 'Kyle Kingsbury', 'Spencer Miles', 'John MacKenzie'.
# URL = 'http://github.com/aphyr/construct'
#
class Construct

  def initialize(data = {})
    @data = Hash.new
    data.each do |key, value|
      self[key] = value
    end
  end

  def cloneData()
    @data = @data.clone;
  end

  def data
    @data
  end

  def empty?()
    @data.empty?();
  end

  def has_key?(key)
    @data.has_key?(key);
  end

  def each_pair(*args, &block)
    @data.each_pair(*args, &block)
  end

  def each_key(*args, &block)
    @data.each_key(*args, &block)
  end

  def include?(*args)
    @data.include?(*args)
  end

  def unWrappedMethodMissing(meth, *args)
    meth_s = meth.to_s
    if meth_s[-1..-1] == '='
      # Assignment
      if args.size != 1
        raise ArgumentError.new("#{meth} takes exactly one argument")
      end
      self[meth_s[0..-2]] = args[0]
    elsif include? meth
      self[meth]
    else
      raise NoMethodError.new("no such key #{meth} in construct")
    end
  end

  def method_missing(meth, *args)
    Thread.current[:confStack].calling(self, meth, :method_missing, args);
    begin
      resultObject = unWrappedMethodMissing(meth, *args);
    rescue NoMethodError => errorObject
      Thread.current[:confStack].reportNoMethodError(errorObject);
    end
    resultObject
  end

  def [](key)
    Thread.current[:confStack].calling(self, key, :key_lookup);

    key = key.to_sym if String === key

    return @data[key] if @data.include? key

    nil
  end

  def []=(key, value)
    key = key.to_sym if String === key
    raise ArgumentError.new('Construct only accepts symbols (and strings) as keys.') unless key.is_a? Symbol

    value = Hash.new() if value.nil?;

    if @data.include?(key) &&
       @data[key].is_a?(Construct) &&
       (value.is_a?(Hash) || value.is_a?(Construct)) then
      value = @data[key].merge(value);
    end

    # Convert suitable hashes into Constructs
    if value.is_a? Hash
      if value.keys.all? { |k|
            k.is_a? String or k.is_a? Symbol
          }
        value = Construct.new(value)
      end
    end

    @data[key] = value
  end

  def merge(valueToMerge)
    if valueToMerge.is_a?(Hash) || valueToMerge.is_a?(Construct) then
      valueToMerge.each do | key, value |
        key = key.to_sym;
        if value.is_a?(Hash) || value.is_a?(Construct) then
          self[key] = Construct.new() unless self.has_key?(key);
          if !self[key].is_a?(Construct) then
            raise ArgumentError, "attempting to merge a Hash/Construct into an existing non Hash/Construct key [#{key}]";
          end
          self[key].merge(value);
        elsif value.is_a?(Array) then
          self[key] = Array.new() unless self.has_key?(key);
          if !self[key].is_a?(Array) then
            raise ArgumentError, "attempting to merge an Array into an existing non Array key [#{key}]";
          end
          value.each do | item |
            self[key].push(item);
          end
        else
          self[key] = value;
        end
      end
    end
    return self;
  end

  def to_stringHash() 
    result = Hash.new();
    data.each_pair do | aKey, aValue |
      if aValue.is_a?(Construct) then
        aValue = aValue.to_stringHash();
      end
      result[aKey.to_s] = aValue;
    end
    return result;
  end

  def prettyPrint(result, prefix)
    if empty? then
      result.puts(prefix+'=emptyConstruct');
    else
      data.keys.sort{ |x,y| x.to_s <=> y.to_s }.each do | aKey |
        aValue = data[aKey];
        if aValue.respond_to?(:prettyPrint) then
          aValue.prettyPrint(result, prefix+'.'+aKey.to_s);
        else
          result.puts(prefix+'.'+aKey.to_s+"="+aValue.to_s);
        end
      end
    end
  end
  
end

class ConfigurationError < StandardError
end

class ResourceNotFoundError < StandardError
end

class Conf

  @@data = Construct.new();
  @@computedDefaults = []
  @@normalizations   = []

  DEFAULTS = {
    global: {
      configFile: $globalConfig
    },

    configFile: 'config.yaml',

    # Ensure we have the basic missingKey error messages
    missingKey: {
      global: {
        message: "" +
"Global parameters are usually set in the cookbook.conf YAML file\n" +
"contained in the .cookbook directory in your home directory.",
        cookbook: {
          message: "" +
"The cookbook configuration parameter needs to be set to the location of\n" +
"the appropriate cookbook.", 

          valueMessage: "" +
"where <<value>> is the full path to the approprate cookbook directory."
        },
      },
    },

    # Ensure the gpg hash exists (but may be empty)
    gpg: Hash.new
  }

  class << self

    def data
      Thread.current[:confStack] = ConfStack.new(self, :Conf);
      Thread.current[:confStack].calling(@@data, :data, :data);
      return @@data;
    end

    def has_key?(aKey)
      return @@data.has_key?(aKey);
    end

#    def load(yaml)
#      loadedHash = YAML::load(yaml);
#      if loadedHash then
#        @@data.merge(loadedHash);
#      end
#    end

    def load_file(yamlFileName)
      puts "loading configuration file [#{yamlFileName}]\n  in #{Dir.getwd}"
      loadedHash = YAML::load_file(yamlFileName);
      if loadedHash then
        @@data.merge(loadedHash);
      end
    end

    def loadConfiguration(options = {})
      Thread.current[:confStack] = ConfStack.new(self, :Conf);
      Thread.current[:confStack].calling(self, :loadConfiguration, options);
      #
      # start by merging in DEFAULTS
      #
      @@data.merge(DEFAULTS)
      #
      # merge computed defaults from each command
      #
      @@computedDefaults.each do | aBlock |
        aBlock.call()
      end
      #
      # now merge in the global configuration YAML file
      #
      Conf.global.configFile = options['globalConfigFile'] if
        options.has_key?('globalConfigFile')
      load_file(Conf.global.configFile) if 
        File.exists?(Conf.global.configFile)
      #
      # now merge in the local configuration YAML file
      #
      Conf.configFile = options['configFile'] if
        options.has_key?('configFile')
      load_file(Conf.configFile) if File.exists?(Conf.configFile)
      #
      # finally merge in the command line options
      #
      @@data.merge(options)
      #
      # do any normalization
      #
      @@normalizations.each do | aBlock |
        aBlock.call()
      end
      #
      # explicitly list the configuration
      #
      puts "\n------------------------------------------------------------"
      puts "Configuration:"
      puts "------------------------------------------------------------"
      puts Conf.prettyPrint
      puts "------------------------------------------------------------\n\n"
    end

    def method_missing(meth, *args)
      Thread.current[:confStack] = ConfStack.new(self, :Conf, args);
      Thread.current[:confStack].calling(self, meth, :method_missing, args);
      meth_s = meth.to_s
      if @@data.respond_to?(meth) ||
        @@data.data.has_key?(meth) ||
        meth_s[-1..-1] == '='then
        @@data.method_missing(meth, *args);
      else 
        Thread.current[:confStack].reportNoMethodError(
           NoMethodError.new("no such key #{meth} in construct"))
      end
    end

    def addDefaults(&block)
      @@computedDefaults << block
    end

    def addNormalizations(&block)
      @@normalizations << block
    end

    def prettyPrint
      result = StringIO.new;
      @@data.prettyPrint(result, "Conf");
      result.string;
    end

  end
end
