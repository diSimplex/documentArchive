#include <stdio.h>
#include "diStructure.h"

/***

The diSimplexEngine's DiStructure component.

All of the code in this component is pure C helper code.

A DiStructure encapsulates a directed simplex structure in the diSimplexEngine.

@module diSimplexEngine.diStructure
*/

///
// Determine if myStructure is contained in otherStructure.
// @function diStructure_contained_in
// @param myStructure :: DiStructureRef*;
// @param otherStructure :: DiStructureRef *;
// @return bool; true if myStructure is contained in otherStructure; false otherwise.
bool diStructure_contained_in(DiStructureRef *myStructure,
                              DiStructureRef *otherStructure) {

  return true;
}

///
// Return true if this diStructure still exists
// @function diStructure_exists
// @param diStructure :: DiStructureRef*; this diStructure.
// @return boolean; true if this diStructure exists; false otherwise
bool diStructure_exists(DiStructureRef *structure) {

  diStructureRef_get_structureObj_or_return_false(structure, structureObj);
  if (structureObj->flags && DISITT_DISTRUCTURE_INUSE) {
      return true;
  }

  return false;
}

///
// Get the next available initial (empty) diStructure. A partial reference
// to the new diStructure is passed in (with a valid diSiTT field), and
// the required structure field is assigned on sucessful return.
// @function diStructure_get_initial
// @param structure :: DiStructureRef*; an partial initial (empty) diStructure.
// @return bool; true if initial (empty) structure assigned; false otherwise.
bool diStructure_get_initial(DiStructureRef *initialStructure) {

  DiSiTT *diSiTT = initialStructure->diSiTT;
  initialStructure->structure = 0;

  // the disitt->emptyStructures DynArray is used as a push down queue
  // of empty diStructures. If it is not empty, then we simply reuse
  // the most recently releasted diStructure.

  if ( 0 < DynArray_len(diSiTT->emptyStructures) ) {
    // there is at least one already existing empty diStructure....
    // so pop it off the end of the emptyStructures dynArray and use it.
    initialStructure->structure =
      *DynArray_popLastElementPtr(diSiTT->emptyStructures, structure_id);
  } else {
    // there are no emptyStructures which we can reuse... so create a new one.
    DynArray_addZeroedElement(diSiTT->structures);
    initialStructure->structure = DynArray_len(diSiTT->structures)-1; // adjust to zero realitive index
  }

  // (re)initialize this empty diStructure before returning it
  DiStructureObj *initialStructureObj =
    DynArray_getElementPtr(diSiTT->structures,
                           initialStructure->structure, DiStructureObj);
  if ( initialStructureObj->dimensions ) {
    // this newStructureObj already has a dynArray assigned to it
    // so walk through each existing dimension
    // and clear its list of simplicies (clear its DynArray)
    size_t numDimensions = DynArray_len(initialStructureObj->dimensions);
    int i = 0;
    for (i = 0; i < numDimensions; i++) {
      DynArray *simplicies =
        *DynArray_getElementPtr(initialStructureObj->dimensions, i, DynArray*);
      DynArray_clear(simplicies);
    }
  } else {
    // this is a completely new diStructure
    // so we need to assign it a new DynArray
    initialStructureObj->dimensions = DynArray_new(sizeof(DynArray*), 0);
  }
  // mark this diStructure as "INUSE"
  initialStructureObj->flags |= DISITT_DISTRUCTURE_INUSE;
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

  // we can NOT release the zero structure.
  if (oldStructure->structure == 0) return false;

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

  diStructureRef_get_structureObj_or_return_false(diStructure, diStructureObj);

  diStructureRef_get_simplicies_or_return_false(diStructureObj,
                                                dimension, simplicies);

  return DynArray_len( simplicies );
}


///
// Add an additional diSimplex to this structure
// @function diStructure_add
// @param diStructure :: DiStructureRef*; this structure.
// @param diSimplex :: DiSimplexRef*; the diSimplex to add.
// @return boolean; true if diSimplex was added; false otherwise
bool diStructure_add(DiStructureRef *diStructure, DiSimplexRef *diSimplex) {

  // We can NOT add anything to the zero structure.
  if (diStructure->structure == 0) return false;

  if (diStructure->diSiTT != diSimplex->diSiTT) return false;

  diStructureRef_get_structureObj_or_return_false(diStructure, diStructureObj);

  dimension_t dimension = diSimplex->dimension;
  if (dimension < 0) dimension = 0;
  diStructure_ensure_dimension_exists(diStructureObj, dimension);

  diStructureRef_get_simplicies_or_return_false(diStructureObj,
                                                dimension, simplicies);

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

  diStructureRef_get_structureObj_or_return_false(diStructure, diStructureObj);

  diStructureRef_get_simplicies_or_return_false(diStructureObj,
                                                dimension, simplicies);

  //if ( itemNumber < 0 ) return false;
  if ( DynArray_len(simplicies) <= itemNumber ) return false;

  simplex->diSiTT    = diStructure->diSiTT;
  simplex->dimension = dimension;
  simplex->simplex   =
    *DynArray_getElementPtr(simplicies, itemNumber, simplex_id);

  return true;
}

///
// Compute the union of two existing diStructures
// @function diStructure_union
// @param structureA :: DiStructureRef*; structure A.
// @param structureB :: DiStructureRef*; structure B.
// @param result :: DiStructureRef*; the resulting union diStructure.
// @return bool; true if union could be computed; false otherwise.
bool diStructure_union(DiStructureRef *structureA,
                       DiStructureRef *structureB,
                       DiStructureRef *result) {

  // do nothing at the moment
  return true;
}

///
// Compute the merge of two existing diStructures
// @function diStructure_merge_into
// @param structureA :: DiStructureRef*; merged structure.
// @param structureB :: DiStructureRef*; other structure.
// @return bool; true if merge could be computed; false otherwise.
bool diStructure_merge_into(DiStructureRef *mergedStructure,
                       DiStructureRef *otherStructure) {

  // do nothing at the moment
  return true;
}
