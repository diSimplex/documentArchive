/***
The diSimplexEngine's DiSiTT component.
The DiSiTT module provides the core of the diSimplexEngine.
@module disitt
*/

#include "diSimplex.h"
#include "lua.h"
#include "lauxlib.h"

#define DISITT_TABLE_NAME	"diSimplexEngine.DiSiTT"
#define checkDiSiTT(L)	(void*)luaL_checkudata(L, 1, DISITT_TABLE_NAME)

/*

The main diSiTT object, which contains a pair of UT_array of pointers 
to UT_arrays. Each sub-UT_array in the "instance" UT_array, contains 
the collection of simplex instances for a specific dimension. Each 
sub-UT_array in the "simplex_icd" UT_array, contains the simplex_icd 
required by the UT_array code for each corresponding dimension of 
simplex cotained in the "instance" UT_array.

The simplex at the zero-th index of the "instance" sub-UT_array, is the 
Universe simplex of that dimension.

*/
typedef struct DiSiTTStruct {
  UT_array *instance;
  UT_array *simplex_icd;
} DiSiTT;

UT_icd instance_icd = {sizeof(UT_array*), NULL, NULL, NULL};

UT_icd simplex_icd_icd = {sizeof(UT_icd*), NULL, NULL, NULL};

/***
Create a new instance of a diSiTT object.
@function new
@return A new instance of a diSiTT object.
*/
static int disitt_new(lua_State *L) {
  DiSiTT *disitt = (DiSiTT *)lua_newuserdata(L, sizeof(DiSiTT));
  luaL_getmetatable(L, DISITT_TABLE_NAME);
  lua_setmetatable(L, -2);
  return 1;
}

/***
Provide a string representation of the disitt object.
@function__tosting
@return[1] A string representation of the diSiTT object.
*/

static int disitt_toString(lua_State *L) {
  void *disitt = checkDiSiTT(L);
  lua_pushfstring(L, "DiSiTT(%p)", &disitt);
  return 1;
}

static struct luaL_Reg disitt_functions[] = {
  {"new", disitt_new},
  {NULL, NULL}
};

static struct luaL_Reg disitt_meta_functions[] = {
  {"__tostring", disitt_toString},
  {NULL, NULL}
};

int luaopen_diSimplexLuaC (lua_State *L) {

  // create and setup a new metatable for the DiSiTT system
  luaL_newmetatable(L, DISITT_TABLE_NAME);
  lua_pushvalue(L, -1);            // duplicates the metatable
  lua_setfield(L, -2, "__index");  // set metatable.__index = metatable

  luaL_setfuncs(L, disitt_meta_functions, 0);

  luaL_newlib(L, disitt_functions);
  return 1;
}

