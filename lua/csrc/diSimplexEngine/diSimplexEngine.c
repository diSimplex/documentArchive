#include <stdio.h>
#include "diSimplexEngine.h"

// Initialize a DiSiTT instance
void dse_init_disitt(DiSiTT *disitt) {
  disitt->emptySimplicies = DynArray_new(sizeof(simplex_id), 0);
  disitt->instances       = DynArray_new(sizeof(DynArray*),  0);
}

// Ensure that a given dimensionn (and all smaller dimensions)
// have been added to this DiSiTT's collection of instances
//
void instances_ensure_dimension(DiSiTT *disitt,
                                dimension_t newDimension) {
  if (newDimension < 0) newDimension = 0;

  dimension_t numDimensions = DynArray_len(disitt->instances);

  // check to see if we already have added this dimension
  if ( newDimension < numDimensions ) {
    return;  // nothing to do...
  }

  // check to see if we need to add lower dimensions
  if ( numDimensions < newDimension ) {
    instances_ensure_dimension(disitt, newDimension - 1);
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
  // simplex is DSE_SIMPLEX_INUSE.
  //
  DynArray_addZeroedElement(newDimensionArray);
  DiSimplexObj *universeSimplex =
    DynArray_getElementPtr(newDimensionArray, 0, DiSimplexObj);
  universeSimplex->flags |= DSE_SIMPLEX_INUSE;
  //
  // now place this new DynArray onto the end of the instances array
  //
  DynArray_addElement(disitt->instances, DynArray*, newDimensionArray);
  //
  // now initalize the empty simplex linked list to the null simplex
  //
  DynArray_addZeroedElement(disitt->emptySimplicies);
}

// Check that a give simplex exists
bool instances_simplex_exists(DiSiTT     *disitt,
                              dimension_t dimension,
                              simplex_id  simplexId) {

  if (!instances_dimension_exists(disitt, dimension)) {
    return 0;
  }

  DynArray *simplicies =
    *DynArray_getElementPtr(disitt->instances, dimension, DynArray*);
  if (simplexId < DynArray_len(simplicies)) {
    DiSimplexObj *simplexObj =
      DynArray_getElementPtr(simplicies, simplexId, DiSimplexObj);
    if (simplexObj->flags && DSE_SIMPLEX_INUSE) {
      return 1;
    }
  }

  return 0;
}

// Get the next available empty simplex for a given dimension
simplex_id instances_get_empty_simplex(DiSiTT     *disitt,
                                       dimension_t dimension){
  // normalize the dimension
  if (dimension < 0) dimension = 0;

  instances_ensure_dimension(disitt, dimension);

  // get the simplex instances for this dimension
  DynArray *instances =
    *DynArray_getElementPtr(disitt->instances, dimension, DynArray*);

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
      DynArray_getElementPtr(instances, newSimplexId, DiSimplexObj);
    *linkedListHead = newSimplexObj->side[0];
  } else {
    // if the linked list of empty simplicies is itself empty
    // use DynArray_addZeroedElement to add a new (zeroed) simplex
    DynArray_addZeroedElement(instances);
    newSimplexId = DynArray_len(instances)-1;  // adjust to zero relative index
  }

  // zero the empty simplex before returning it
  DiSimplexObj *newSimplexObj =
    DynArray_getElementPtr(instances, newSimplexId, DiSimplexObj);
  memset(newSimplexObj, 0, DynArray_elementSize(instances));
  newSimplexObj->flags |= DSE_SIMPLEX_INUSE;
  return newSimplexId;
}

// Return the given simplex to the pool of avaialble empty simpleices
// for a given dimension
void instances_return_simplex(DiSiTT     *disitt,
                              dimension_t dimension,
                              simplex_id  oldSimplexId){

  // make sure this simplex actually exists
  if (!instances_simplex_exists(disitt, dimension, oldSimplexId)) {
    return;
  }

  // normalize the dimension
  if (dimension < 0) dimension = 0;

  // get the simplex instances for this dimension
  DynArray *instances =
    *DynArray_getElementPtr(disitt->instances, dimension, DynArray*);

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
    DynArray_getElementPtr(instances, oldSimplexId, DiSimplexObj);
  // ensure the old simplex is zeroed
  memset(oldSimplexObj, 0, DynArray_elementSize(instances));
  // place the linkedListHead into the old simplex
  oldSimplexObj->side[0] = *linkedListHead;
  // place the oldSimplexId in the linkedListHead
  *linkedListHead = oldSimplexId;
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
  if (!instances_simplex_exists(disitt, dimension, parentSimplexId)) return;
  if (!instances_simplex_exists(disitt, dimension-1, sideSimplexId)) return;

  // make sure that the requested side exists
  if (dimension < sideNumber) return;
  if (sideNumber < 0) return;

  // normalize the dimension
  if (dimension < 0) dimension = 0;

  // get the simplex instances for this dimension
  DynArray *instances =
    *DynArray_getElementPtr(disitt->instances, dimension, DynArray*);

  // get the parent diSimplex object
  DiSimplexObj *parentSimplexObj =
    DynArray_getElementPtr(instances, parentSimplexId, DiSimplexObj);

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
  if (!instances_simplex_exists(disitt, dimension, parentSimplexId)) return 0;

  // make sure that the requested side exists
  if (dimension < sideNumber) return 0;
  if (sideNumber < 0) return 0;

  // normalize the dimension
  if (dimension < 0) dimension = 0;

  // get the simplex instances for this dimension
  DynArray *instances =
    *DynArray_getElementPtr(disitt->instances, dimension, DynArray*);

  // get the parent diSimplex object
  DiSimplexObj *parentSimplexObj =
    DynArray_getElementPtr(instances, parentSimplexId, DiSimplexObj);

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

  if (instances_simplex_exists(disitt, dimension, simplex_id)) {
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
