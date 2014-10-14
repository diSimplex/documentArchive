#include <stdio.h>
#include "diSimplex.h"

///
// Return true if this diSimplex still exists
// @param diSimplex this diSimplex
// @return[1] true if this diSimplex exists; false otherwise
int diSimplex_exists(DiSimplexRef *diSimplex) {
  return diSiTT_simplex_exists(diSimplex->diSiTT,
                               diSimplex->dimension,
                               diSimplex->simplex);
}

// Store the side into the simplex provided
// sides are zero relative index as in traditional simplicial practice
// BUT the zeroth side represents the "definitional" simplex
void simplex_store_side(DiSiTT *disitt,
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

// Get the requested side
// sides are zero relative index as in traditional simplicial practice
// BUT the zeroth side represents the "definitional" simplex
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

void simplex_toString(DiSiTT *disitt,
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
