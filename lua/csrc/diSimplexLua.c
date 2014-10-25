/***
A single directed simplex.
@module diSimplex
*/

#include "diSimplexLua.h"

///
// A C helper function which provides a lua reference to a diSimplex.
// Constructs and returns a Lua user data object which contains
// ***references*** to a specific simplex of a given dimension
// in a given DiSiTT.
// @function diSimplexLua_return_simplex_ref
// @param L ::lua_State; the lua state.
// @param diSiTT :: DiSiTT; the diSiTT environment which contains the simplex.
// @param dimension :: dimension_t; the dimension of the simplex.
// @param simplex :: simplex_id; the simplex reference.
int diSimplexLua_return_simplex_ref(lua_State *L,
                                    DiSimplexRef *localSimplex) {

  DiSimplexRef *diSimplex =
    (DiSimplexRef *)lua_newuserdata(L, sizeof(DiSimplexRef));

  diSimplex->diSiTT    = localSimplex->diSiTT;
  diSimplex->dimension = localSimplex->dimension;
  diSimplex->simplex   = localSimplex->simplex;
  diSimplex->structure = localSimplex->structure;

  luaL_getmetatable(L, DISIMPLEXLUA_TABLE_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

///
// Determine if two diSimplicies are equal.
// @function __eq
// @param diSimplex the diSimplex object.
// @param otherDiSimplex the other diSimplex reference object.
// @return true if the two objects refer to the same diSimplex
static int diSimplexLua_equal(lua_State *L) {
  DiSimplexRef *mySimplex    = checkDiSimplex(L);
  DiSimplexRef *otherSimplex = checkForDiSimplex(L, 2);
  lua_pushboolean(L, diSimplex_equals(mySimplex, otherSimplex));
  return 1;
}

///
// Provide a string representation of the diSimplex object.
// @function __tosting
// @param diSimplex the diSimplex object to be printed.
// @return A string representation of the diSimplex object.
//
static int diSimplexLua_toString(lua_State *L) {
  DiSimplexRef *diSimplex = checkDiSimplex(L);

  char strBuf[500];
  strBuf[0] = 0;

  diSimplex_toString(diSimplex, strBuf, 500);

  lua_pushfstring(L, "%s", strBuf);
  return 1;
}

///
// Returns the dimension of this simplex.
// @function dimension
// @param diSimplex the diSimplex object whose dimension is being requested.
// @return the dimension of this simplex
static int diSimplexLua_dimension(lua_State *L) {
  DiSimplexRef *diSimplex = checkDiSimplex(L);

  lua_pushnumber(L, diSimplex->dimension);
  return 1;
}

///
// Get the requested side of this simplex.
// @function side
// @param diSimplex the diSimplex whose side is being requested.
// @param index the (zero releative) side.
// @return the requested side of this simplex.
static int diSimplexLua_side(lua_State *L) {
  DiSimplexRef *diSimplex = checkDiSimplex(L);

  DiSiTT     *disitt    = diSimplex->diSiTT;
  dimension_t dimension = diSimplex->dimension;
  simplex_id  simplex   = diSimplex->simplex;

  if (!diSimplex_exists(diSimplex)) {
    luaL_argerror(L, 1, "the specified diSimplex does not exist");
  }
  // check for the side argument
  int side = luaL_checkinteger(L, 2);
  DiSimplexRef sideSimplex;
  sideSimplex.diSiTT    = diSimplex->diSiTT;
  sideSimplex.dimension = diSimplex->dimension - 1;
  diSimplex_get_side(diSimplex, side, &sideSimplex);

  return diSimplexLua_return_simplex_ref(L, &sideSimplex);
}

static struct luaL_Reg diSimplexLua_meta_functions[] = {
  {"__eq",       diSimplexLua_equal},
  {"__tostring", diSimplexLua_toString},
  {"dimension",  diSimplexLua_dimension},
  {"side",       diSimplexLua_side},
  {NULL, NULL}
};

/*** A C helper function which initializes the DiSimplex lua module.
Setup the Lua resources required for the DiSimplex module.

@function diSimplexLua_init
@param L ::lua_State; the lua state.
*/
void diSimplexLua_init(lua_State *L) {
  // create and setup a new metatable for the DiSiTT system
  luaL_newmetatable(L, DISIMPLEXLUA_TABLE_NAME);
  lua_pushvalue(L, -1);            // duplicates the metatable
  lua_setfield(L, -2, "__index");  // set metatable.__index = metatable

  luaL_setfuncs(L, diSimplexLua_meta_functions, 0);
}

