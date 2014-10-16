#include <stdio.h>
#include "diStructure.h"

/***

The diSimplexEngine's DiStructure component.

All of the code in this component is pure C helper code.

A DiStructure encapsulates a directed simplex structure in the diSimplexEngine.

@module diSimplexEngine.diStructure
*/

///
// Return true if this diStructure still exists
// @function diStructure_exists
// @param diStructure :: DiStructureRef*; this diStructure.
// @return boolean; true if this diStructure exists; false otherwise
bool diStructure_exists(DiStructureRef *structure) {
  DiSiTT *diSiTT = structure->diSiTT;

  if (DynArray_len(diSiTT->structures) <= structure->structure) return false;

  DiStructureObj *structureObj =
    DynArray_getElementPtr(structure->diSiTT->structures,
                            structure->structure, DiStructureObj);
  if (structureObj->flags && DISITT_DISTRUCTURE_INUSE) {
      return true;
  }

  return false;
}

///
// Get the next available empty diStructure. A partial reference
// to the new diStructure is passed in (with a valid diSiTT field), and
// the required structure field is assigned on sucessful return.
// @function diStructure_get_empty
// @param structure :: DiStructureRef*; an partial empty diStructure.
// @return bool; true if empty structure assigned; false otherwise.
bool diStructure_get_empty(DiStructureRef *newStructure) {

  DiSiTT *diSiTT = newStructure->diSiTT;
  newStructure->structure = 0;

  // the disitt->emptyStructures DynArray is used as a push down queue
  // of empty diStructures. If it is not empty, then we simply reuse
  // the most recently releasted diStructure.

  if ( 0 < DynArray_len(diSiTT->emptyStructures) ) {
    // there is at least one already existing empty diStructure....
    // so pop it off the end of the emptyStructures dynArray and use it.
    newStructure->structure =
      *DynArray_popLastElementPtr(diSiTT->emptyStructures, structure_id);
  } else {
    // there are no emptyStructures which we can reuse... so create a new one.
    DynArray_addZeroedElement(diSiTT->structures);
    newStructure->structure = DynArray_len(diSiTT->structures)-1; // adjust to zero realitive index
  }

  // (re)initialize this empty diStructure before returning it
  DiStructureObj *newStructureObj =
    DynArray_getElementPtr(diSiTT->structures,
                           newStructure->structure, DiStructureObj);
  if ( newStructureObj->dimensions ) {
    // this newStructureObj already has a dynArray assigned to it
    // so walk through each existing dimension
    // and clear its list of simplicies (clear its DynArray)
    size_t numDimensions = DynArray_len(newStructureObj->dimensions);
    int i = 0;
    for (i = 0; i < numDimensions; i++) {
      DynArray *simplicies =
        *DynArray_getElementPtr(newStructureObj->dimensions, i, DynArray*);
      DynArray_clear(simplicies);
    }
  } else {
    // this is a completely new diStructure
    // so we need to assign it a new DynArray
    newStructureObj->dimensions = DynArray_new(sizeof(DynArray*), 0);
  }
  // mark this diStructure as "INUSE"
  newStructureObj->flags |= DISITT_DISTRUCTURE_INUSE;
  // (re)initialize all fields
  newStructureObj->curSimplex.diSiTT    = diSiTT;
  newStructureObj->curSimplex.dimension = 0;
  newStructureObj->curSimplex.simplex   = 0; // the universal zero-simplex
  return true;
}

///
// Release the given diStructure back to the pool of available empty
// diStructures.
// @function diStructure_release
// @param structure :: DiStructureRef*; the diStructure to be released.
// @return bool; true if the diStructure has been sucessfully released; false otherwise.
bool diStructure_release(DiStructureRef *oldStructure) {

  // if the old structure does not exist... then it has already been released.
  if (!diStructure_exists(oldStructure)) return true;

  DiSiTT *disitt = oldStructure->diSiTT;

  DynArray_addElement(disitt->emptyStructures,
                      structure_id,
                      oldStructure->structure);

  // zero the flags (DISITT_DISTRUCTURE_INUSE)
  DiStructureObj *emptyStructureObj =
    DynArray_getElementPtr(disitt->structures,
                           oldStructure->structure,
                           DiStructureObj);
  emptyStructureObj->flags = 0;

  // otherwise, old diStructures are emptied on re-assignment.

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
// @param diStructure :: DiStructureRef*; this structure.
// @param dimension :: dimension_t; the dimension to check.
// @return int; number of simplicies
size_t diStructure_size(DiStructureRef *diStructure, dimension_t dimension) {

  if ( dimension < -1 ) return 0;
  if ( dimension == -1 ) dimension = 0;

  DiStructureObj *diStructureObj =
    DynArray_getElementPtr(diStructure->diSiTT->structures,
                           diStructure->structure,
                           DiStructureObj);

  if ( DynArray_len(diStructureObj->dimensions) <= dimension ) return 0;

  DynArray *simplicies =
    *DynArray_getElementPtr(diStructureObj->dimensions, dimension, DynArray*);
  return DynArray_len( simplicies );
}


///
// Add an additional diSimplex to this structure
// @function diStructure_add
// @param diStructure :: DiStructureRef*; this structure.
// @param diSimplex :: DiSimplexRef*; the diSimplex to add.
// @return boolean; true if diSimplex was added; false otherwise
bool diStructure_add(DiStructureRef *diStructure, DiSimplexRef *diSimplex) {

  if (diStructure->diSiTT != diSimplex->diSiTT) return false;

  DiSiTT *disitt = diStructure->diSiTT;
  DiStructureObj *diStructureObj =
    DynArray_getElementPtr(disitt->structures,
                           diStructure->structure,
                           DiStructureObj);

  dimension_t dimension = diSimplex->dimension;
  if (dimension < 0) dimension = 0;
  diStructure_ensure_dimension_exists(diStructureObj, dimension);

  // get the dynArray for this diStructure's dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(diStructureObj->dimensions, dimension, DynArray*);

  DynArray_addElement(simplicies, simplex_id, diSimplex->simplex);

  return true;
}

///
// Return the requested diSimplex
// @function diStructure_get_simplex_number
// @param diStructure :: DiStructureRef*; this structure.
// @param dimension :: dimension_t; the required diSimplex dimension.
// @param itemNumber :: size_t; the required diSimplex in the diStructure's ordered set of diSimplicies of this dimension.
// @param simplex :: DiSimplexRef*; an empty diSimplexRef which will be filled in with a valid diSimplex which is the requested simplex.
// @return bool; true if the requested diSimplex has been found; false otherwise.
bool diStructure_get_simplex_number(DiStructureRef *diStructure,
                                    dimension_t dimension,
                                    size_t itemNumber,
                                    DiSimplexRef *simplex ) {
  if ( dimension < -1 ) return false;
  if ( dimension == -1 ) dimension = 0;

  DiSiTT *disitt = diStructure->diSiTT;
  DiStructureObj *diStructureObj =
    DynArray_getElementPtr(disitt->structures,
                           diStructure->structure,
                           DiStructureObj);

  if ( DynArray_len(diStructureObj->dimensions) <= dimension ) return false;

  DynArray *simplicies =
    *DynArray_getElementPtr(diStructureObj->dimensions, dimension, DynArray*);

  //if ( itemNumber < 0 ) return false;
  if ( DynArray_len(simplicies) <= itemNumber ) return false;

  simplex->diSiTT    = disitt;
  simplex->dimension = dimension;
  simplex->simplex   =
    *DynArray_getElementPtr(simplicies, itemNumber, simplex_id);

  return true;
}
