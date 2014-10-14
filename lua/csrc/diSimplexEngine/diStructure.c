#include <stdio.h>
#include "diStructure.h"

///
// Initialize a new diStructure object
// @param diStructure the uninitialized diStructure
// @param diSiTT the diSiTT environment in which this diStructure should exist
// return[0] void
void diStructure_init(DiStructureObj *diStructure, DiSiTT *diSiTT) {
  diStructure->diSiTT               = diSiTT;
  diStructure->dimensions           = DynArray_new(sizeof(DynArray*), 0);
  diStructure->curSimplex.diSiTT    = diSiTT;
  diStructure->curSimplex.dimension = 0;
  diStructure->curSimplex.simplex   = 0; // the universal zero-simplex
}


///
// Return true if this diStructure still exists
// @param diStructure this structure
// @return[1] true if this diStructure exists; false otherwise
int diStructure_exists(DiStructureObj *diStructure) {

  return true;
}

///
// Ensure that a given dimension (and all smaller dimensions) exists
// int the diStruture.
// @param diStructure this diStructure
// @param dimension the dimension to ensure exists
// return[1] true if dimension now exists; false otherwise
int diStructure_ensure_dimension_exists(DiStructureObj *diStructure,
                                        dimension_t newDimension) {
  if (newDimension < 0) newDimension = 0;

  dimension_t numDimensions = DynArray_len(diStructure->dimensions);

  if (newDimension < numDimensions) return true;

  if (numDimensions < newDimension) {
    diStructure_ensure_dimension_exists(diStructure, newDimension - 1);
  }

  DynArray *newDimensionArray = DynArray_new(sizeof(simplex_id), 0);

  DynArray_addElement(diStructure->dimensions, DynArray*, newDimensionArray);

  return true;
}

///
// Return the number of simplicies of a given dimension in this structure
// @param diStructure this structure
// @param dimension the dimension to check
// @return[1] number of simplicies
int diStructure_size(DiStructureObj *diStructure, dimension_t dimension) {

  if ( dimension < -1 ) return 0;
  if ( DynArray_len(diStructure->dimensions) <= dimension ) return 0;

  if ( dimension == -1 ) dimension = 0;

  DynArray *simplicies =
    *DynArray_getElementPtr(diStructure->dimensions, dimension, DynArray*);
  return DynArray_len( simplicies );
}


///
// Add an additional diSimplex to this structure
// @param diStructure this structure
// @param diSimplex the diSimplex to add
// @return[1] true if diSimplex was added; false otherwise
int diStructure_add(DiStructureObj *diStructure, DiSimplexRef *diSimplex) {
  dimension_t dimension = diSimplex->dimension;
  if (dimension < 0) dimension = 0;
  diStructure_ensure_dimension_exists(diStructure, dimension);

  // get the dynArray for this diStructure's dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(diStructure->dimensions, dimension, DynArray*);

  DynArray_addElement(simplicies, simplex_id, diSimplex->simplex);

  return true;
}

///
// Return the requested diSimplex
// @param diStructure this structure
// @param dimension the required diSimplex dimension
// @param itemNumber the required diSimplex in the diStructure's ordered set of diSimplicies of this dimension
// @return[1] diSimplex
simplex_id diStructure_get_simplex_number(DiStructureObj *diStructure,
                                          dimension_t dimension,
                                          size_t itemNumber) {
  if ( dimension < -1 ) return 0;
  if ( DynArray_len(diStructure->dimensions) <= dimension ) return 0;
  if ( dimension == -1 ) dimension = 0;

  DynArray *simplicies =
    *DynArray_getElementPtr(diStructure->dimensions, dimension, DynArray*);

  //if ( itemNumber < 0 ) return 0;
  if ( DynArray_len(simplicies) <= itemNumber ) return 0;

  return *DynArray_getElementPtr(simplicies, itemNumber, simplex_id);
}
