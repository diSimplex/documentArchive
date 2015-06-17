# This is the cmake description of how to build the diSimplexEngine
# sources as a subproject.

project(diSimplexEngine)

defineLibrary(diSimplexEngine "lib" "" "lib")
add_dependencies(lib diSimplexEngine)
