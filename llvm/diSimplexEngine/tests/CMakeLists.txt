# This is the cmake description of how to build the diSimplexEngine
# tests as a subproject.

project(diSimplexEngineTests)

defineTestsFor( diSimplexEngine "lib" "dynUtf8Parser;hattrie" )
add_dependencies(tests diSimpexEngineTests)

