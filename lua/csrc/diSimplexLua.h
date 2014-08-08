#ifndef DISIMPLEX_H
#define DISIMPLEX_H

#include "diSiTTLua.h"

// Construct and return a Lua user data object which contains
// **references** to a specific simplex of a given dimension in a given
// DiSiTT
//
extern int diSimplex_return_simplex(lua_State *L,
                                    DiSiTT *disitt,
                                    dimension_t dimension,
                                    simplex_id simplex);

// Setup the Lua resources required for the DiSimplex classes
//
extern void diSimplex_init(lua_State *L);

// Pesudo-functions to check for and return a diSimplex object
//
#define DISIMPLEX_TABLE_NAME    "diSimplexEngine.diSimplex"
#define checkForDiSimplex(L, index) (void*)luaL_checkudata((L), (index), DISIMPLEX_TABLE_NAME)
#define checkDiSimplex(L) checkForDiSimplex(L, 1)

#endif
