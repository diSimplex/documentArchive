## Building

The diSimplexEngine can make use of LLVM's link time optimiztion. To do 
this we use the CMake build system.

To build the DiSimplexEngine, git clone a copy of the project into 
a directory, for example "diSimplexEngine"

    git clone https://github.com/stephengaito/diSimplexEngine

then cd into the "llvm" subdirectory and a directory (*beside* the 
diSimplexEngine sources) for the build, for example 
"build"

    mkdir build

then in the build directory use CMake to configure and make to build 
the project

    cd build
    cmake ../diSimplexEngine

Once you have run the cmake command, on Linux, you have the following 
make targets:

* **make help** provides a list of the available make targets

* **make doc** builds the Doxygen based documentation for the 
  diSimplexEngine

* **make lib** builds the diSimplexEngine library (only)

* **make bin** builds the diSimplexEngine library and engine

* **make tests** build both libraries as well as all of the tests and 
  runs the diSimplexEngineTests binary (i.e. *just* the diSimplexEngine
  tests).

* **make release** builds all of the above and then installs into the 
  CMAKE_INSTALL_PREFIX directories.

Typically I build using LLVM's clang. I have also occasionaly built 
using gcc/g++.

