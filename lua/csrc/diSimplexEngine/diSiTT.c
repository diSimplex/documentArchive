#include <stdio.h>
#include "diSiTT.h"

/***

The diSimplexEngine's DiSiTT component.

All of the code in this component is pure C helper code.

A DiSiTT structure provides an encapsulated environment in which
directed simplicial structures can exist. Note that a given Lua script
can interact with multiple DiSiTT structures, each of which will be
totally separate from each other.

@module diSimplexEngine.diSiTT
*/

///
// Initialize a DiSiTT instance.
// @function diSiTT_init
// @param disitt :: DiSiTT*; the diSiTT structure to be initialized.
void diSiTT_init(DiSiTT *disitt) {
  disitt->emptySimplicies = DynArray_new(sizeof(simplex_id), 0);
  disitt->simplicies      = DynArray_new(sizeof(DynArray*),  0);
  disitt->emptyStructures = DynArray_new(sizeof(structure_id), 0);
  disitt->structures      = DynArray_new(sizeof(DynArray*), 0);
}


///
// Ensure that a given dimensionn (and all smaller dimensions)
// have been added to this DiSiTT's collection of simplicies.
// @function diSiTT_ensure_dimension
// @param disitt :: DiSiTT*; the diSiTT.
// @param newDimension :: dimension_t; the dimension which must exists or be added.
//
void diSiTT_ensure_dimension(DiSiTT *disitt,
                                dimension_t newDimension) {
  if (newDimension < 0) newDimension = 0;

  dimension_t numDimensions = DynArray_len(disitt->simplicies);

  // check to see if we already have added this dimension
  if ( newDimension < numDimensions ) {
    return;  // nothing to do...
  }

  // check to see if we need to add lower dimensions
  if ( numDimensions < newDimension ) {
    diSiTT_ensure_dimension(disitt, newDimension - 1);
  }

  // now add this dimension
  //
  // now provision the dynArray for the new dimension
  //
  DynArray *newDimensionArray = DynArray_new(DiSimplexObjSize(newDimension), 0);
  //
  // a universe simplex for a given dimension has all sides zero which hence
  // points to the universe simplex for the next lower dimension.
  // So adding a zero element (and doing nothing else) ensures that
  // the element is a universe simplex. BUT we must assert that the universe
  // simplex is DISITT_DISIMPLEX_INUSE.
  //
  DynArray_addZeroedElement(newDimensionArray);
  DiSimplexObj *universeSimplex =
    DynArray_getElementPtr(newDimensionArray, 0, DiSimplexObj);
  universeSimplex->flags |= DISITT_DISIMPLEX_INUSE;
  //
  // now place this new DynArray onto the end of the simplicies array
  //
  DynArray_addElement(disitt->simplicies, DynArray*, newDimensionArray);
  //
  // now initalize the empty simplex linked list to the null simplex
  //
  DynArray_addZeroedElement(disitt->emptySimplicies);
}

// Check that a give simplex exists
bool diSiTT_simplex_exists(DiSiTT     *disitt,
                              dimension_t dimension,
                              simplex_id  simplexId) {

  if (!diSiTT_dimension_exists(disitt, dimension)) {
    return 0;
  }

  DynArray *simplicies =
    *DynArray_getElementPtr(disitt->simplicies, dimension, DynArray*);
  if (simplexId < DynArray_len(simplicies)) {
    DiSimplexObj *simplexObj =
      DynArray_getElementPtr(simplicies, simplexId, DiSimplexObj);
    if (simplexObj->flags && DISITT_DISIMPLEX_INUSE) {
      return 1;
    }
  }

  return 0;
}

///
// Get the next available empty diSimplex for a given dimension.
// @function diSiTT_get_empty_simplex
// @param disitt :: DiSiTT*; the diSiTT.
// @param dimension :; dimension_t; the dimension of the new diSimplex.
simplex_id diSiTT_get_empty_simplex(DiSiTT     *disitt,
                                       dimension_t dimension){
  // normalize the dimension
  if (dimension < 0) dimension = 0;

  diSiTT_ensure_dimension(disitt, dimension);

  // get the simplex simplicies for this dimension
  DynArray *simplicies =
    *DynArray_getElementPtr(disitt->simplicies, dimension, DynArray*);

  // allocate a variable for the new simplex id
  simplex_id newSimplexId = 0;

  // get the head of the linked list
  simplex_id *linkedListHead =
    DynArray_getElementPtr(disitt->emptySimplicies, dimension, simplex_id);

  if (*linkedListHead) {
    // if the linked list of empty simplicies is not itself empty
    // use the first simplex on the linked list
    // and re-point the list of empties to the next empty simplex
    newSimplexId   = *linkedListHead;
    DiSimplexObj *newSimplexObj =
      DynArray_getElementPtr(simplicies, newSimplexId, DiSimplexObj);
    *linkedListHead = newSimplexObj->side[0];
  } else {
    // if the linked list of empty simplicies is itself empty
    // use DynArray_addZeroedElement to add a new (zeroed) simplex
    DynArray_addZeroedElement(simplicies);
    newSimplexId = DynArray_len(simplicies)-1;  // adjust to zero relative index
  }

  // zero the empty simplex before returning it
  DiSimplexObj *newSimplexObj =
    DynArray_getElementPtr(simplicies, newSimplexId, DiSimplexObj);
  memset(newSimplexObj, 0, DynArray_elementSize(simplicies));
  newSimplexObj->flags |= DISITT_DISIMPLEX_INUSE;
  return newSimplexId;
}

/// 
// Release the given diSimplex to the pool of avaialble empty diSimpleices
// for a given dimension
// @function diSiTT_release_simplex
// @param disitt :: DiSiTT*; the diSiTT.
// @param dimension :: dimension_t; the dimension of the diSimplex being released.
// @param oldSimplexId :: simplex_id; the ID of the diSimplex being released.
void diSiTT_return_simplex(DiSiTT     *disitt,
                              dimension_t dimension,
                              simplex_id  oldSimplexId){

  // make sure this simplex actually exists
  if (!diSiTT_simplex_exists(disitt, dimension, oldSimplexId)) {
    return;
  }

  // normalize the dimension
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
    DynArray_getElementPtr(simplicies, oldSimplexId, DiSimplexObj);
  // ensure the old simplex is zeroed
  memset(oldSimplexObj, 0, DynArray_elementSize(simplicies));
  // place the linkedListHead into the old simplex
  oldSimplexObj->side[0] = *linkedListHead;
  // place the oldSimplexId in the linkedListHead
  *linkedListHead = oldSimplexId;
}

