#ifndef DISIMPLEXLUA_H
#define DISIMPLEXLUA_H

#include "diSiTTLua.h"

// Construct and return a Lua user data object which contains
// **references** to a specific simplex of a given dimension in a given
// DiSiTT
//
extern int diSimplexLua_return_simplex_ref(lua_State *L,
                                           DiSimplexRef *simplex);

// Setup the Lua resources required for the DiSimplex classes
//
extern void diSimplexLua_init(lua_State *L);

// Pesudo-functions to check for and return a diSimplex object
//
#define DISIMPLEXLUA_TABLE_NAME    "diSimplexEngine.diSimplex"
#define checkForDiSimplex(L, index) (void*)luaL_checkudata((L), (index), DISIMPLEXLUA_TABLE_NAME)
#define checkDiSimplex(L) checkForDiSimplex(L, 1)

#endif
