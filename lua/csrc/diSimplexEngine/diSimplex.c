#include <stdio.h>
#include "diSimplex.h"

/***

The diSimplexEngine's DiSimplex component.

All of the code in this component is pure C helper code.

A DiSimplex structure encapsulates a directed simplex in the diSimplexEngine.

@module diSimplexEngine.diSimplex
*/

///
// Check that a given diSimplex exists in this diSiTT environment.
// @function diSiTT_simplex_exists
// @param simplex :: DiSimplexRef*; a reference to a possible diSimplex.
// @return boolean; true if this diSimplex exists in this diSiTT environment.
bool diSimplex_exists(DiSimplexRef *simplex) {

  DiSiTT      *diSiTT    = simplex->diSiTT;
  dimension_t  dimension = simplex->dimension;

  if ( dimension < 0 ) dimension = 0;

  if ( DynArray_len(diSiTT->simplicies) <= dimension ) {
    return 0;
  }

  DynArray *simplicies =
    *DynArray_getElementPtr(diSiTT->simplicies, dimension, DynArray*);
  if (simplex->simplex < DynArray_len(simplicies)) {
    DiSimplexObj *simplexObj =
      DynArray_getElementPtr(simplicies, simplex->simplex, DiSimplexObj);
    if (simplexObj->flags && DISITT_DISIMPLEX_INUSE) {
      return 1;
    }
  }

  return 0;
}

///
// Get the next available empty diSimplex for a given dimension. A partial
// reference to the new diSimplex is passed in (diSiTT and dimension), and
// the required simplex field is assigned on sucessful return.
// @function diSiTT_get_empty
// @param newSimplex :: DiSimplexRef*; a partial reference to the new diSimplex.
// @return bool; true if a new diSimplex has been allocated; false otherwise
bool diSimplex_get_empty(DiSimplexRef *newSimplex) {

  DiSiTT *diSiTT = newSimplex->diSiTT;

  // normalize the dimension
  if (newSimplex->dimension < 0) newSimplex->dimension = 0;

  diSiTT_ensure_dimension(diSiTT, newSimplex->dimension);

  // get the simplex simplicies for this dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(diSiTT->simplicies,
                            newSimplex->dimension, DynArray*);

  newSimplex->simplex = 0;

  // get the head of the linked list
  simplex_id *linkedListHead =
    DynArray_getElementPtr(diSiTT->emptySimplicies,
                           newSimplex->dimension, simplex_id);

  if (*linkedListHead) {
    // if the linked list of empty simplicies is not itself empty
    // use the first simplex on the linked list
    // and re-point the list of empties to the next empty simplex
    newSimplex->simplex = *linkedListHead;
    DiSimplexObj *newSimplexObj =
      DynArray_getElementPtr(simplicies, newSimplex->simplex, DiSimplexObj);
    *linkedListHead = newSimplexObj->side[0];
  } else {
    // if the linked list of empty simplicies is itself empty
    // use DynArray_addZeroedElement to add a new (zeroed) simplex
    DynArray_addZeroedElement(simplicies);
    newSimplex->simplex = DynArray_len(simplicies)-1;  // adjust to zero relative index
  }

  // zero the empty simplex before returning it
  DiSimplexObj *newSimplexObj =
    DynArray_getElementPtr(simplicies, newSimplex->simplex, DiSimplexObj);
  memset(newSimplexObj, 0, DynArray_elementSize(simplicies));
  newSimplexObj->flags |= DISITT_DISIMPLEX_INUSE;
  return true;
}

/// 
// Release the given diSimplex to the pool of avaialble empty diSimpleices
// for a given dimension
// @function diSimplex_release
// @param oldSimplex :: DiSimplexRef*; a reference to the diSimplex being released.
void diSimplex_release(DiSimplexRef *oldSimplex){
  DiSiTT *disitt = oldSimplex->diSiTT;

  // make sure this simplex actually exists
  if (!diSimplex_exists(oldSimplex)) return;

  // normalize the dimension
  dimension_t dimension = oldSimplex->dimension;
  if (dimension < 0) dimension = 0;

  // get the simplex simplicies for this dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(disitt->simplicies, dimension, DynArray*);

  // get the head of the linked list
  simplex_id *linkedListHead =
    DynArray_getElementPtr(disitt->emptySimplicies, dimension, simplex_id);

  // add this simplex to the begining of the linked list of empty simplicies
  //
  // take the current start of the list and store it in the first element
  // of the newly empty simplex and place the index of this newly empty
  // simplex in the disitt->emptySimplicies pointer.
  //
  // get the old simplex object itself
  DiSimplexObj *oldSimplexObj =
    DynArray_getElementPtr(simplicies, oldSimplex->simplex, DiSimplexObj);
  // ensure the old simplex is zeroed
  memset(oldSimplexObj, 0, DynArray_elementSize(simplicies));
  // place the linkedListHead into the old simplex
  oldSimplexObj->side[0] = *linkedListHead;
  // place the oldSimplexId in the linkedListHead
  *linkedListHead = oldSimplex->simplex;
}

///
// Store the diSimplex for this side into the (parent) diSimplex provided.
// Sides are zero relative index as in traditional simplicial practice,
// BUT the zeroth side represents the "definitional" simplex.
// @function diSimplex_store_side
// @param parentSimplex :: DiSimplexRef*; the parent diSimplex.
// @param sideNumber :: size_t; the side to be added to the parent.
// @param sideSimplex :: DiSimplexRef*; the diSimplex to be added.
void diSimplex_store_side(DiSimplexRef *parentSimplex,
                          size_t sideNumber,
                          DiSimplexRef *sideSimplex) {
  // make sure these simplicies are in the same diSiTT environment
  if (parentSimplex->diSiTT != sideSimplex->diSiTT) return;

  DiSiTT *disitt = parentSimplex->diSiTT;

  // make sure that the side diSimplex id one dimension less than the
  // parent diSimplex.
  if (parentSimplex->dimension != sideSimplex->dimension + 1) return;

  dimension_t dimension = parentSimplex->dimension;

  // make sure that the requested side exists
  if (dimension < sideNumber) return;
  //if (sideNumber < 0) return;

  // normalize the dimension
  if (dimension < 0) dimension = 0;

  // make sure this simplicies actually exist
  if (!diSimplex_exists(parentSimplex)) return;
  if (!diSimplex_exists(sideSimplex)) return;

  // get the simplex instances for this dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(disitt->simplicies, dimension, DynArray*);

  // get the parent diSimplex object
  DiSimplexObj *parentSimplexObj =
    DynArray_getElementPtr(simplicies, parentSimplex->simplex, DiSimplexObj);

  // store the side (note we add one to allow for the definitional simplex)
  parentSimplexObj->side[sideNumber+1] = sideSimplex->simplex;
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
bool diSimplex_get_side(DiSimplexRef *parentSimplex,
                      size_t        sideNumber,
                      DiSimplexRef *sideSimplex) {

  // make sure this simplex actually exists
  if (!diSimplex_exists(parentSimplex)) return 0;

  dimension_t dimension = parentSimplex->dimension;

  // make sure that the requested side exists
  if (dimension < sideNumber) return 0;
  //if (sideNumber < 0) return 0;

  // normalize the dimension
  if (dimension < 0) dimension = 0;

  // get the simplex instances for this dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(parentSimplex->diSiTT->simplicies,
                            dimension, DynArray*);

  // get the parent diSimplex object
  DiSimplexObj *parentSimplexObj =
    DynArray_getElementPtr(simplicies, parentSimplex->simplex, DiSimplexObj);

  // store the side (note we add one to allow for the definitional simplex)
  sideSimplex->diSiTT    = parentSimplex->diSiTT;
  sideSimplex->dimension = parentSimplex->dimension - 1;
  sideSimplex->simplex   = parentSimplexObj->side[sideNumber+1];

  return true;
}

///
// Return a string which represents/decodes this diSimplex instance.
// @function diSimplex_toString
// @param disitt :: DiSiTT*; the diSiTT which contains this diSimplex.
// @param dimension :: dimension_t; the dimension of this diSimplex.
// @param simplex_id :: simplex_id; the ID of this diSimplex.
// @param buffer :: char*; the buffer which will contain the string.
// @param bufferSize :: size_t; the total size of the buffer.
void diSimplex_toString(DiSimplexRef *simplex,
                        char *buffer,
                        size_t bufferSize) {

  if (bufferSize < 1) return;

  buffer[0] = 0;

  char listBuf[250];
  listBuf[0] = 0;

  if (diSimplex_exists(simplex)) {
    char numberBuf[20];
    DiSimplexRef sideSimplex;
    int numSides = simplex->dimension + 1;
    if (10 < numSides) numSides = 10;
    int i = 0;
    for( ; i < numSides; i++) {
      numberBuf[0] = 0;
      diSimplex_get_side(simplex, i, &sideSimplex);
      sprintf(numberBuf, "%u ", sideSimplex.simplex);
      strncat(listBuf, numberBuf, 20);
    }
  }

  snprintf(buffer, bufferSize,
           "diSimplex(%p, %d, %d, [ 0 ][ %s])",
           simplex->diSiTT,
           simplex->dimension,
           simplex->simplex,
           listBuf);
}
