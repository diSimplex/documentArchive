/***
A structure of directed simplicies.
@module diStructure
*/

#include "diStructureLua.h"


///
// Construct and return a new diStructure in the disitt DiSiTT.
// @param disitt the DiSiTT universe in which this structure exists
// @return[1] a new diStructure
int diStructureLua_new(lua_State *L,
                       DiSiTT *disitt) {

  DiStructureObj *diStructure =
    (DiStructureObj *)lua_newuserdata(L, sizeof(DiStructureObj));

  luaL_getmetatable(L, DISTRUCTURE_TABLE_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

///
// Add an existing simplex of a given dimension to this structure
// @param simplex
// @return[1] true if simplex added
static int diStructureLua_add(lua_State *L){

}

///
// Return the number of simplicies in a given dimension
// @param dimension
// @return[1] the number of simplicies in the dimension
static int diStructureLua_size(lua_State *L){
  DiStructureObj *diStructure = checkDiStructure(L);
  int unCheckedDimension = luaL_checkint(L, 2);
  luaL_argcheck(L, -1 <= unCheckedDimension, 2, "dimensions must be greater than or equal to -1");
  dimension_t dimension = (dimension_t)unCheckedDimension;

  lua_pushnumber(L, diStructure_size(diStructure, dimension));
  return 1;
}

///
// Provide a string representation of the diStructure object.
// @function __tosting
// @return[1] A string representation of the diStructure object.
//
static int diStructureLua_toString(lua_State *L) {
  DiStructureObj *diStructure = checkDiStructure(L);

  lua_pushfstring(L, "%s", "diSimplexStructure");
  return 1;
}

static struct luaL_Reg diStructureLua_meta_functions[] = {
  {"add", diStructureLua_add},
  {"size", diStructureLua_size},
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

