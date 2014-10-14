#include <stdio.h>
#include "diStructure.h"

/***

The diSimplexEngine's DiStructure component.

All of the code in this component is pure C helper code.

A DiStructure encapsulates a directed simplex structure in the diSimplexEngine.

@module diSimplexEngine.diStructure
*/

///
// Initialize a new diStructure object
// @function diStructure_init
// @param diStructure :: DiStructure*; the uninitialized diStructure.
// @param diSiTT :: DiSiTT*; the diSiTT environment in which this diStructure should exist
void diStructure_init(DiStructureObj *diStructure, DiSiTT *diSiTT) {
  diStructure->diSiTT               = diSiTT;
  diStructure->dimensions           = DynArray_new(sizeof(DynArray*), 0);
  diStructure->curSimplex.diSiTT    = diSiTT;
  diStructure->curSimplex.dimension = 0;
  diStructure->curSimplex.simplex   = 0; // the universal zero-simplex
}


///
// Return true if this diStructure still exists
// @function diStructure_exists
// @param diStructure :: DiStructureObj*; this diStructure.
// @return boolean; true if this diStructure exists; false otherwise
int diStructure_exists(DiStructureObj *diStructure) {

  return true;
}

///
// Ensure that a given dimension (and all smaller dimensions) exists
// in the diStruture.
// @function diStructure_ensure_dimension_exists
// @param diStructure :: DiStructureObj*; this diStructure.
// @param dimension :: dimension_t; the dimension to ensure exists.
// return boolean; true if dimension now exists; false otherwise
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
// @function diStructure_size
// @param diStructure :: DiStructureObj*; this structure.
// @param dimension :: dimension_t; the dimension to check.
// @return int; number of simplicies
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
// @function diStructure_add
// @param diStructure :: DiStructureObj*; this structure.
// @param diSimplex :: DiSimplexRef*; the diSimplex to add.
// @return boolean; true if diSimplex was added; false otherwise
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
// @function diStructure_get_simplex_number
// @param diStructure :: DiStructureObj*; this structure.
// @param dimension :: dimension_t; the required diSimplex dimension.
// @param itemNumber :: size_t; the required diSimplex in the diStructure's ordered set of diSimplicies of this dimension.
// @return simplex_id; the requested diSimplex.
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
