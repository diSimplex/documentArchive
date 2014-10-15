#ifndef DISTRUCTURELUA_H
#define DISTRUCTURELUA_H

#include "diSiTTLua.h"
#include "diSimplexLua.h"

//
// A C helper function which provides a lua reference to a diStructure.
// Constructs and returns a Lua user data object which contains
// ***references*** to a specific structure in a given DiSiTT.
// @function diSimplexLua_return_structure_ref
// @param L ::lua_State; the lua state.
// @param localStructure :: DiStructureRef*; a local structure reference.
extern int diStructureLua_return_structure_ref(lua_State *L,
                                               DiStructureRef *localStructure);


// Setup the Lua resources required for the DiStructure classes
//
extern void diStructureLua_init(lua_State *L);

// Pesudo-functions to check for and return a diStructure object
//
#define DISTRUCTURELUA_TABLE_NAME    "diSimplexEngine.diStructure"
#define checkForDiStructure(L, index) (void*)luaL_checkudata((L), (index), DISTRUCTURELUA_TABLE_NAME)
#define checkDiStructure(L) checkForDiStructure(L, 1)

#endif
