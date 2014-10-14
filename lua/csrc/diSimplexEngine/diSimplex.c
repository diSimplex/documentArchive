#include <stdio.h>
#include "diSimplex.h"

/***

The diSimplexEngine's DiSimplex component.

All of the code in this component is pure C helper code.

A DiSimplex structure encapsulates a directed simplex in the diSimplexEngine.

@module diSimplexEngine.diSimplex
*/

///
// Return true if this diSimplex still exists
// @function diSimplex_exists
// @param diSimplex :: DiSimplexRef*; this diSimplex.
// @return true if this diSimplex exists; false otherwise
int diSimplex_exists(DiSimplexRef *diSimplex) {
  return diSiTT_simplex_exists(diSimplex->diSiTT,
                               diSimplex->dimension,
                               diSimplex->simplex);
}

///
// Store the diSimplex for this side into the (parent) diSimplex provided.
// Sides are zero relative index as in traditional simplicial practice,
// BUT the zeroth side represents the "definitional" simplex.
// @function diSimplex_store_side
// @param disitt :: DiSiTT*; the diSiTT which contains this diSimplex
// @param parentSimplexId :: simplex_id; the ID of the parent diSimplex.
// @param sideNumber :: (signed) int; the side to be added to the parent.
// @param sideSimplexId :: simplex_id; the ID of the diSimplex to be added.
void diSimplex_store_side(DiSiTT *disitt,
                          dimension_t dimension,
                          simplex_id  parentSimplexId,
                          int         sideNumber,
                          simplex_id  sideSimplexId){
  // make sure this simplicies actually exist
  if (!diSiTT_simplex_exists(disitt, dimension, parentSimplexId)) return;
  if (!diSiTT_simplex_exists(disitt, dimension-1, sideSimplexId)) return;

  // make sure that the requested side exists
  if (dimension < sideNumber) return;
  if (sideNumber < 0) return;

  // normalize the dimension
  if (dimension < 0) dimension = 0;

  // get the simplex instances for this dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(disitt->simplicies, dimension, DynArray*);

  // get the parent diSimplex object
  DiSimplexObj *parentSimplexObj =
    DynArray_getElementPtr(simplicies, parentSimplexId, DiSimplexObj);

  // store the side (note we add one to allow for the definitional simplex)
  parentSimplexObj->side[sideNumber+1] = sideSimplexId;
}

///
// Get the requested side.
// Sides are zero relative index as in traditional simplicial practice,
// BUT the zeroth side represents the "definitional" simplex.
// @function diSimplex_get_side
// @param disitt :: DiSiTT*; the diSiTT which contains this diSimplex.
// @param dimension :: dimension_t; the dimension of this diSimplex.
// @param parentSimplexId :: simplex_id; the ID of the parent diSimplex.
// @param sideNumber :: (signed) int; the side number to be returned.
simplex_id simplex_get_side(DiSiTT *disitt,
                            dimension_t dimension,
                            simplex_id parentSimplexId,
                            int sideNumber) {

  // make sure this simplex actually exists
  if (!diSiTT_simplex_exists(disitt, dimension, parentSimplexId)) return 0;

  // make sure that the requested side exists
  if (dimension < sideNumber) return 0;
  if (sideNumber < 0) return 0;

  // normalize the dimension
  if (dimension < 0) dimension = 0;

  // get the simplex instances for this dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(disitt->simplicies, dimension, DynArray*);

  // get the parent diSimplex object
  DiSimplexObj *parentSimplexObj =
    DynArray_getElementPtr(simplicies, parentSimplexId, DiSimplexObj);

  // store the side (note we add one to allow for the definitional simplex)
  return parentSimplexObj->side[sideNumber+1];
//  return 0;
}

///
// Return a string which represents/decodes this diSimplex instance.
// @function diSimplex_toString
// @param disitt :: DiSiTT*; the diSiTT which contains this diSimplex.
// @param dimension :: dimension_t; the dimension of this diSimplex.
// @param simplex_id :: simplex_id; the ID of this diSimplex.
// @param buffer :: char*; the buffer which will contain the string.
// @param bufferSize :: size_t; the total size of the buffer.
void diSimplex_toString(DiSiTT *disitt,
                        dimension_t dimension,
                        simplex_id simplex_id,
                        char *buffer,
                        size_t bufferSize) {

  if (bufferSize < 1) return;

  buffer[0] = 0;

  char listBuf[250];
  listBuf[0] = 0;

  if (diSiTT_simplex_exists(disitt, dimension, simplex_id)) {
    char numberBuf[20];
    int numSides = dimension + 1;
    if (10 < numSides) numSides = 10;
    int i = 0;
    for( ; i < numSides; i++) {
      numberBuf[0] = 0;
      sprintf(numberBuf, "%u ", simplex_get_side(disitt,
                                                 dimension,
                                                 simplex_id,
                                                 i));
      strncat(listBuf, numberBuf, 20);
    }
  }

  snprintf(buffer, bufferSize,
           "diSimplex(%p, %d, %d, [ 0 ][ %s])",
           disitt,
           dimension,
           simplex_id,
           listBuf);
}
