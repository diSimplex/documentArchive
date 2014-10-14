/***
A structure of directed simplicies.
@module diStructure
*/

#include "diStructureLua.h"

///
// Add an existing diSimplex of a given dimension to this diStructure.
// @function add
// @param diStructure the diStructure to which this diSimplex is to be added.
// @param diSimplex the diSimplex to be added to this diStructure.
// @return true if simplex added; false otherwise
static int diStructureLua_add(lua_State *L){
  DiStructureObj *diStructure = checkDiStructure(L);
  DiSimplexRef   *diSimplex   = checkForDiSimplex(L, 2);
  // ensure the diStructure exists
  if (!diStructure_exists(diStructure)) {
    luaL_argerror(L, 1, "the specified diStructure does not exist");
  }
  // ensure the diSimplex exists
  if (!diSimplex_exists(diSimplex)) {
    luaL_argerror(L, 2, "the specified diSimplex does not exist");
  }
  // ensure diStructure and diSimplex are in the same diSiTT
  if (diStructure->diSiTT != diSimplex->diSiTT) {
    luaL_argerror(L, 2, "the specified diSimplex must be in the same DiSiTT as the diStructure");
  }
  // add the diSimplex to the diStructure
  lua_pushboolean(L, diStructure_add(diStructure, diSimplex));

  return 1;
}

///
// Return the number of diSimplicies in a given dimension.
// @function size
// @param diStructure the diStructure whose size is requested.
// @param dimension the dimension whose size is requested.
// @return the number of diSimplicies in the dimension.
static int diStructureLua_size(lua_State *L){
  DiStructureObj *diStructure = checkDiStructure(L);
  int unCheckedDimension = luaL_checkint(L, 2);
  luaL_argcheck(L, -1 <= unCheckedDimension, 2, "dimensions must be greater than or equal to -1");
  dimension_t dimension = (dimension_t)unCheckedDimension;

  lua_pushnumber(L, diStructure_size(diStructure, dimension));
  return 1;
}

///
// Return the requested diSimplex in the ordered set of simplicies
// of a given dimension.
// @function simplex
// @param diStructure the diStructure from which to obtain the diSimplex.
// @param dimension the dimension of the required simplex.
// @param itemNumber the index (zero relative) of the requested simplex.
// @return a lua reference to a diSimplex.
static int diStructureLua_simplex(lua_State *L){
  DiStructureObj *diStructure = checkDiStructure(L);
  int unCheckedDimension = luaL_checkint(L, 2);
  luaL_argcheck(L, -1 <= unCheckedDimension, 2, "dimensions must be greater than or equal to -1");
  dimension_t dimension = (dimension_t)unCheckedDimension;

  int unCheckedItemNumber = luaL_checkint(L, 3);
  luaL_argcheck(L, -1 < unCheckedItemNumber, 3, "simplex number must be greater than or equal to 0");
  size_t itemNumber = (size_t)unCheckedItemNumber;

  return diSimplexLua_return_simplex(L,
                                     diStructure->diSiTT,
                                     dimension,
                                     diStructure_get_simplex_number(diStructure,
                                                                    dimension,
                                                                    itemNumber));
}

///
// Provide a string representation of the diStructure object.
// @function __tosting
// @param diStructure the diStructure to be printed.
// @return A string representation of the diStructure object.
//
static int diStructureLua_toString(lua_State *L) {
  DiStructureObj *diStructure = checkDiStructure(L);

  lua_pushfstring(L, "%s", "diSimplexStructure");
  return 1;
}

static struct luaL_Reg diStructureLua_meta_functions[] = {
  {"add", diStructureLua_add},
  {"size", diStructureLua_size},
  {"simplex", diStructureLua_simplex},
  {"__tostring", diStructureLua_toString},
  {NULL, NULL}
};

// Setup the Lua resources required for the DiStructure classes
//
void diStructureLua_init(lua_State *L) {
  // create and setup a new metatable for the DiSiTT system
  luaL_newmetatable(L, DISTRUCTURE_TABLE_NAME);
  lua_pushvalue(L, -1);            // duplicates the metatable
  lua_setfield(L, -2, "__index");  // set metatable.__index = metatable

  luaL_setfuncs(L, diStructureLua_meta_functions, 0);
}

