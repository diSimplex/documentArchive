#include <string.h>

#include "dynArray.h"

//#pragma GCC diagnostic ignored "-Wtautological-compare"

/***
The diSimplexEngine's dynamic array component (c-code).
All of the code in this component is pure C helper code.

A DynArray is a dynamical array which has both allocated elements and
additional capacity for new elements. Once new elements have been added
which exhaust the current capacity, new capacity will be allocated.

@module diSimplexEngine.dynArray
*/

///
// Create a new DynArray
// @function DynArray_new
// @param elementSize ::size_t; the size of an individual element in this dynamic array.
// @param initialCapacity ::size_t; the initial capacity of this dynamic array.
// @return DynArray*; a pointer to the newly created dynamic array.
DynArray *DynArray_new(size_t elementSize, size_t initialCapacity) {
  DynArray *newArray = (DynArray*)DYNARRAY_CALLOC(1, sizeof(DynArray));
  newArray->elementSize = elementSize;
  //if (initialCapacity < 0) initialCapacity = 0;
  initialCapacity = ((initialCapacity % DYNARRAY_CAPACITY_INCREMENT) + 1)*DYNARRAY_CAPACITY_INCREMENT;
  newArray->capacity = initialCapacity;
  newArray->data = calloc(newArray->capacity, newArray->elementSize);
  return newArray;
}

///
// Ensure that the dynArray has a capcity of at least the requested capacity.
// @function DynArray_increaseCapacity
// @param dynArray :: DynArray*
// @param requestedCapacity :: size_t; the total capacity required.
void DynArray_increaseCapacity(DynArray *dynArray, size_t requestedCapacity) {
  size_t newCapacity = dynArray->capacity;
  while(newCapacity <= requestedCapacity) {
    newCapacity += DYNARRAY_CAPACITY_INCREMENT;
  }
  if (dynArray->capacity < newCapacity) {
    char *newData = DYNARRAY_CALLOC(newCapacity, dynArray->elementSize);
    memmove(newData, dynArray->data, (dynArray->len)*(dynArray->elementSize));
    DYNARRAY_FREE(dynArray->data);
    dynArray->data = newData;
    dynArray->capacity = newCapacity;
  }
}
