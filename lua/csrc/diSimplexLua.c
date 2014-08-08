/***
A single directed simplex.
@module diSimplex
*/

#include "diSimplexLua.h"

// Construct and return a Lua user data object which contains
// **references** to a specific simplex of a given dimension in a given
// DiSiTT
//
int diSimplex_return_simplex(lua_State *L,
                             DiSiTT *disitt,
                             dimension_t dimension,
                             simplex_id simplex) {

  DiSimplexRef *diSimplex =
    (DiSimplexRef *)lua_newuserdata(L, sizeof(DiSimplexRef));

  diSimplex->disitt    = disitt;
  diSimplex->dimension = dimension;
  diSimplex->simplex   = simplex;

  luaL_getmetatable(L, DISIMPLEX_TABLE_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

///
// Determine if two diSimplex reference objects are equal
// @param other the other diSimplex reference object
// @return[1] true if the two objects refer to the same diSimplex
static int diSimplex_equal(lua_State *L) {
  DiSimplexRef *myDiSimplex    = checkDiSimplex(L);
  DiSimplexRef *otherDiSimplex = checkForDiSimplex(L, 2);
  bool isEqual = true;
  if (myDiSimplex->disitt    != otherDiSimplex->disitt)    isEqual = false;
  if (myDiSimplex->dimension != otherDiSimplex->dimension) isEqual = false;
  if (myDiSimplex->simplex   != otherDiSimplex->simplex)   isEqual = false;
  lua_pushboolean(L, isEqual);
  return 1;
}

///
// Provide a string representation of the diSimplex object.
// @function __tosting
// @return[1] A string representation of the diSimplex object.
//
static int diSimplex_toString(lua_State *L) {
  DiSimplexRef *diSimplex = checkDiSimplex(L);

  char strBuf[500];
  strBuf[0] = 0;

  simplex_toString(diSimplex->disitt,
                   diSimplex->dimension,
                   diSimplex->simplex,
                   strBuf, 500);

  lua_pushfstring(L, "%s", strBuf);
  return 1;
}

///
// Returns the dimension of this simplex
// @return[1] the dimension of this simplex
static int diSimplex_dimension(lua_State *L) {
  DiSimplexRef *diSimplex = checkDiSimplex(L);

  lua_pushnumber(L, diSimplex->dimension);
  return 1;
}

///
// Get the requested side of this simplex.
// @function side
// @param index the (zero releative) side.
// @return[1] the requested side of this simplex.
static int diSimplex_side(lua_State *L) {
  DiSimplexRef *diSimplex = checkDiSimplex(L);

  DiSiTT     *disitt    = diSimplex->disitt;
  dimension_t dimension = diSimplex->dimension;
  simplex_id  simplex   = diSimplex->simplex;

  if (!instances_simplex_exists(disitt, dimension, simplex)) {
    luaL_argerror(L, 1, "the specified diSimplex does not exist");
  }
  // check for the side argument
  int side = luaL_checkinteger(L, 2);
  simplex_id sideSimplexId = simplex_get_side(disitt,
                                              dimension,
                                              simplex,
                                              side);

  return diSimplex_return_simplex(L, disitt,
                                  dimension - 1,
                                  sideSimplexId);
}

static struct luaL_Reg disimplex_meta_functions[] = {
  {"__eq",       diSimplex_equal},
  {"__tostring", diSimplex_toString},
  {"dimension",  diSimplex_dimension},
  {"side",       diSimplex_side},
  {NULL, NULL}
};

// Setup the Lua resources required for the DiSimplex classes
//
void diSimplex_init(lua_State *L) {
  // create and setup a new metatable for the DiSiTT system
  luaL_newmetatable(L, DISIMPLEX_TABLE_NAME);
  lua_pushvalue(L, -1);            // duplicates the metatable
  lua_setfield(L, -2, "__index");  // set metatable.__index = metatable

  luaL_setfuncs(L, disimplex_meta_functions, 0);
}

