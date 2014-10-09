#ifndef DISTRUCTURELUA_H
#define DISTRUCTURELUA_H

#include "diSiTTLua.h"
#include "diSimplexLua.h"

// Setup the Lua resources required for the DiStructure classes
//
extern void diStructureLua_init(lua_State *L);

// Pesudo-functions to check for and return a diStructure object
//
#define DISTRUCTURE_TABLE_NAME    "diSimplexEngine.diStructure"
#define checkForDiStructure(L, index) (void*)luaL_checkudata((L), (index), DISTRUCTURE_TABLE_NAME)
#define checkDiStructure(L) checkForDiStructure(L, 1)

#endif
