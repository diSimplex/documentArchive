<!-- leave blank -->
# ConTeXt maintenance scripts for Unix

This directory contains a collection of simple scripts which help install, 
update, and use the various ConTeXt standalone installations. Since I only 
have access to XUbuntu based machines, all these scripts will only work on a 
Unix derivative. Windows users will need to modify these scripts for their 
own use. 

These scripts are known to work on XUbuntu machines which have [TeXLive 
(2016)](https://www.tug.org/texlive/) [installed over the 
internet](https://www.tug.org/texlive/acquire-netinstall.html). Installing 
[ConTeXt standalone](http://wiki.contextgarden.net/ConTeXt_Standalone) as 
well, provides a wide range of ConTeXt/LuaTeX versions with which to test 
your modules. **Note** that [ConTeXt on MiKTeX is not currently working 
(2017/March/07)](http://wiki.contextgarden.net/MikTeX), TeXLive works but is 
about a year out of date. In either case, the most up to date and well tested 
ConTeXt installations *will* be the [ConTeXt 
standalone](http://wiki.contextgarden.net/ConTeXt_Standalone) installations 
taken directly from the ConTeXT developers. 

These scripts fall into four broad use-cases:

1. Installation and update of one of the [ConTeXt 
standalone](http://wiki.contextgarden.net/ConTeXt_Standalone) installations. 

2. Starting [Textadept](https://foicica.com/textadept/) using a given 
installation. 

3. Ensuring the current shell terminal uses a given installation.

4. Starting ConTeXt webservers for browsing commands and code.

# Installing and using these scripts

## Installation and Update scripts

The installation and update scripts should be installed in the root directory 
of your ConTeXt installations. In my case I have installed all of my ConTeXt 
standalone installations into: 

> /use/local/context

To install the installation and update scripts, while in the bin directory, 
type: 

> ./setupContext <full Path to root of the ConTeXt standalone installation>

To use these scripts cd into the root of your ConTeXt installation and type: 

> ./downLoad-beta

or

> ./downLoad-current

or

> ./downLoad-experiemental

These scripts will install the appropriate version into 'beta', 'current' or 
'experimental' directories respectively. 

The corresponding 'update-xxx' scripts can be used in the same way to ensure 
that your installations are up todate. 

**Note** if your user does not own your chosen ConTeXt installation root 
directory they you *will* need to preface each of the above commands with 
'sudo' inorder to run these commands as root. 

## Installation of personal commands

The installation of the [Textadept](https://foicica.com/textadept/), shell 
terminal and webserver scripts assume that you have a 'bin' directory in your 
$HOME directory which is also included in your $PATH variable. If you place 
your personal scripts in some other directory you will need to modify the 
'setupBin' script accordingly. 

To install the [Textadept](https://foicica.com/textadept/) and webserver 
scripts type: 

> ./setupBin

To install the shell terminal functions ('uc-xx') you need to append the 
*contents* of the 'context.all.sh' file to your '.bashrc' script near the 
beginning. *Make sure you use a programmer's editor such as nano*. 

## Using Textadept commands 

There are three 'ta-x' commands: 'ta-b', 'ta-c' and 'ta-e', each of which 
starts textadept after sourcing the setuptex script in the beta, current or 
experimental installation respectively. Note that these scripts assume that 
your root ConTeXt installation is located in the '/usr/local/context' 
directory. If this is not the case then you will need to alter these scripts 
accordingly. 

## Using the shell terminal functions 

There are three shell functions: 'uc-b', 'uc-c', and 'uc-e' to source the 
setuptex script from the beta, current or experimental ConTeXt installations 
respectively.

To use these shell functions you *must* put the *contents* of the 
'context.all.sh' script near the top of your '.bashrc' script. These 
functions then source the appropriate setuptex script into your *current* 
shell. 

## Using the webserver commands

There are two webserver commands: 'webXrefs' and 'webContext'.

### webXrefs

The 'webXrefs' command uses the light weight 'webfsd' webserver to serve the 
previously created ConTeXt cross referenced code. To create this cross 
referenced code type: 

> mtxrun --script xrefs --build

This xrefs mtxrun script is part of the "A ConTeXt Module Writer's Progress". 
It is located in the 't-helloworld/scripts/context/lua' directory. You are 
welcome to alter your own local copy to provide any cross references you 
might find useful. GitHub pull requests will be happily considered. 

**Note** both the 'webXrefs' and 'mtxrun --scripts xrefs --build' commands 
can only be run in shells in which you have chosen a ConTeXt installation 
using one of the 'uc-x' functions.

To use the 'webXrefs' command you must also have installed the 'webfsd' 
package. On a debian derived system, you can do this by typing: 

> sudo apt-get install webfs

The standard Debian/Ubuntu installation of webfs is setup to automatically 
run webfsd on port 8000. The whole point of using webfsd is to be able to 
run a controlled webserver in the foreground and only on the local 
loop-back for security reasons. To stop the automatic running of webfsd, 
type: 

> sudo /etc/init.d/webfs stop
> sudo chmod a-x /etc/init.d/webfs

### webContext

The 'webContext' command automates the standard ConTeXt mtxrun server script. 
To use this command you must have previously chosen a ConTeXt installation 
using one of the 'uc-x' functions. 

# License 

All of the scripts *in this 'bin' directory* are placed in the public domain and 
may be used and altered as you wish. There is NO WARRANTY FOR ANY USE. Use 
these scripts at your own risk. 
