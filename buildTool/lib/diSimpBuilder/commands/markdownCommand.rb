
require 'fileutils'

module DiSimpBuilder

  class MarkdownCommand < Command
    class << self

      TOC_TIME_STAMP_PATH = ".tocTimeStamp"

      DEPTH_PREFIX = [ 
        '',         # 0 
        ' - ',      # 1
        '  - ',     # 2
        '   - ',    # 3
        '    - ',   # 4
        '     - ',  # 5
      ]

      def createTag(origHeader)
        aHeader = origHeader.clone
        depth = aHeader.gsub(/[^\#]+/,'').length
        depth = 5 unless depth < 5
        depth = DEPTH_PREFIX[depth]
        aHeader.gsub!(/^[ \t]*#+[ \t]*/,'')
        aTag = aHeader.clone
        aTag.downcase!
        aTag.gsub!(/[^a-z0-9]+/,'-')
        "#{depth}[#{aHeader}](##{aTag})"
      end

      # NOTE we ONLY deal with ATX-style headers (those that use '#'s)
      # AND we only deal with a depth of 5
      #
      def updateTOC(markdownFilePath)
        #
        # Check to see if any changes need updating
        #
        return if FileUtils.uptodate?(TOC_TIME_STAMP_PATH, [markdownFilePath])
        puts "Regenerating TOC for [#{markdownFilePath}]"
        #
        # Read in the Markdown file as individual lines
        #
        mdLines = Array.new
        File.open(markdownFilePath, 'r') do | md |
          mdLines = md.readlines
        end
        #
        # Remove line endings
        #
        mdLines.collect! { | aLine | aLine.chomp! }
        #
        # Remove any existing TOC
        #
        foundEndTOC = false
        trialMDLines = mdLines.select do | aLine |
          oldFoundEndTOC = foundEndTOC
          foundEndTOC = foundEndTOC || aLine =~ /\<\!\-\-\- END TOC/ 
          oldFoundEndTOC
        end
        mdLines = trialMDLines unless trialMDLines.empty?
        while (mdLines[0] =~ /^[ \t]*$/) do mdLines.shift end
        #
        # collect the new TOC
        #
        mdHeaders = mdLines.select { | aLine | aLine =~ /^[ \t]*\#/ }
        mdHeaders.collect! { | aLine | createTag(aLine) }
        #
        # Merge the new TOC into the existing Markdown lines
        #
        mdLines.unshift("\n<!--- END TOC -->\n")
        mdHeaders.reverse.each { | aLine | mdLines.unshift(aLine) }
        mdLines.unshift("**Table of Contents**\n")
        #
        # Write out the Markdown file with TOC
        #
        File.write(markdownFilePath, mdLines.join("\n"))
      end

      def findMarkdownFiles(curDir)
#        puts "Looking in [#{curDir}]"
        Dir.foreach(curDir) do | aFile |
          next if aFile =~ /^\.+/
          next if aFile =~ /^tmp$/
          aPath = curDir +'/' + aFile
          if aFile =~ /\.md$/ then
            updateTOC(aPath) 
          elsif File.directory?(aPath) then
            findMarkdownFiles(aPath)
          end            
        end
      end

      def init_with_program(p)
        p.command(:tableOfContents) do |c|
          c.alias(:toc)
          c.syntax 'tableOfContents'
          c.description 'Update the tables of contents for all Markdown files.'

          c.action do |args, options|
            Conf.loadConfiguration(options)
            findMarkdownFiles(".")
            sleep(1)
            FileUtils.touch(TOC_TIME_STAMP_PATH)
          end
        end # :toc command

      end # init_with_program

    end
  end
end
