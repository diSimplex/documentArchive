/***
The diSimplexEngine's DiSiTT component.
The DiSiTT module provides the core of the diSimplexEngine.
@module diSiTT
*/

#include "diSiTTLua.h"
#include "diSimplexLua.h"
#include "diStructureLua.h"

#define DISITTLUA_TABLE_NAME	"diSimplexEngine.DiSiTT"
#define checkForDiSiTT(L, index) (void*)luaL_checkudata((L), (index), DISITTLUA_TABLE_NAME)
#define checkDiSiTT(L)	checkForDiSiTT(L, 1)

///
// Create a new instance of a diSiTT object.
// @function new
// @return A new instance of a diSiTT object.
//
static int diSiTTLua_new(lua_State *L) {
  DiSiTT *disitt = (DiSiTT *)lua_newuserdata(L, sizeof(DiSiTT));
  diSiTT_init(disitt);

  luaL_getmetatable(L, DISITTLUA_TABLE_NAME);
  lua_setmetatable(L, -2);
  return 1;
}

///
// Provide a string representation of the disitt object.
// @function __tosting
// @param diSiTT the diSiTT object to print.
// @return A string representation of the diSiTT object.
//
static int diSiTTLua_toString(lua_State *L) {
  void *disitt = checkDiSiTT(L);
  lua_pushfstring(L, "DiSiTT(%p)", disitt);
  return 1;
}

///
// Return the universe simplex of a given dimension.
// @function universe
// @param diSiTT the diSiTT object which contains this universe.
// @param dimension The dimension of the requested universe simplex.
// @return The requested universe simplex
//
static int diSiTTLua_universe(lua_State *L) {
  DiSimplexRef universeSimplex;
  universeSimplex.diSiTT = checkDiSiTT(L);
  int unCheckedDimension = luaL_checkint(L, 2);
  luaL_argcheck(L, -1 <= unCheckedDimension, 2, "dimensions must be greater than or equal to -1");
  universeSimplex.dimension = (dimension_t)unCheckedDimension;
  diSiTT_ensure_dimension(universeSimplex.diSiTT, universeSimplex.dimension);
  universeSimplex.simplex = 0;
  return diSimplexLua_return_simplex_ref(L, &universeSimplex);
}

///
// Create a new diSimplex containing the given sides.
// @function simplex
// @param diSiTT the diSiTT object which will contain this simplex.
// @param sides an array of diSimplex references of the correct dimension and number.
// @return a diSimplex reference to the new diSimplex.
static int diSiTTLua_simplex(lua_State *L) {
  DiSimplexRef newSimplex;
  newSimplex.diSiTT = checkDiSiTT(L);
  // the second argument is a array(table) of diSimplicies
  luaL_checktype(L, 2, LUA_TTABLE);

  // the dimension of all of the sides MUST be equal to
  // two less than the number of sides being added to this diSimplex
  int numberOfSides              = luaL_len(L, 2);
  newSimplex.dimension = numberOfSides - 1;
  if (newSimplex.dimension < 0) newSimplex.dimension = 0;
  dimension_t dimensionOfSides   = newSimplex.dimension - 1;
  if ( dimensionOfSides < 0 ) dimensionOfSides = 0;

  diSiTT_ensure_dimension(newSimplex.diSiTT, newSimplex.dimension);
  diSimplex_get_empty(&newSimplex);

  // inspect each side
  int i = 1;
  for(; i <= numberOfSides; i++) {
    // push the ith value of the array onto the stack
    lua_rawgeti(L, 2, i);
    // check that this value is a diSimplex and get its reference
    DiSimplexRef *aSide = checkForDiSimplex(L, 3);
    // remove the reference from the top of the stack
    lua_pop(L, 1);
    // check the validity of the side
    if (aSide->diSiTT != newSimplex.diSiTT) {
      // return the un-used simplex
      diSimplex_release(&newSimplex);
      // raise an error!
      luaL_argerror(L, 2, "all sides MUST be from the same underlying DiSiTT structure");
    }
    // check the dimension
    if (aSide->dimension != dimensionOfSides) {
      // return the un-used simplex
      diSimplex_release(&newSimplex);
      // raise an error!
      luaL_argerror(L, 2, "dimension of all sides must be two less than the number of sides in the simplex");
    }
    // check that the side simplex exists
    if (!diSimplex_exists(aSide)) {
      // return the un-used simplex
      diSimplex_release(&newSimplex);
      // raise an error!
      luaL_argerror(L, 2, "the simplex of all sides must already exist");
    }
    char strBuf[500];
    strBuf[0] = 0;
    diSimplex_toString(aSide, strBuf, 500);
    diSimplex_store_side(&newSimplex, i-1, aSide);
  }
  return diSimplexLua_return_simplex_ref(L, &newSimplex);
}

///
// Create a new diSimplexStructure containing the given sides.
// @function structure
// @param diSiTT the diSiTT which will contain this structure.
// @return a new diSimplexStructure.
static int diSiTTLua_structure(lua_State *L) {
  DiStructureRef newStructure;
  newStructure.diSiTT = checkDiSiTT(L);

  diStructure_get_empty(&newStructure);
  return diStructureLua_return_structure_ref(L, &newStructure);
}

static struct luaL_Reg diSiTTLua_functions[] = {
  {"new", diSiTTLua_new},
  {NULL, NULL}
};

static struct luaL_Reg diSiTTLua_meta_functions[] = {
  {"__tostring", diSiTTLua_toString},
  {"universe",   diSiTTLua_universe},
  {"simplex",    diSiTTLua_simplex},
  {"structure",  diSiTTLua_structure},
  {NULL, NULL}
};

// Initialize the DiSiTT and DiSimplex Lua resources
//
int luaopen_diSimplexLuaC (lua_State *L) {

  diSimplexLua_init(L);
  diStructureLua_init(L);

  // create and setup a new metatable for the DiSiTT system
  luaL_newmetatable(L, DISITTLUA_TABLE_NAME);
  lua_pushvalue(L, -1);            // duplicates the metatable
  lua_setfield(L, -2, "__index");  // set metatable.__index = metatable

  luaL_setfuncs(L, diSiTTLua_meta_functions, 0);

  luaL_newlib(L, diSiTTLua_functions);
  return 1;
}

