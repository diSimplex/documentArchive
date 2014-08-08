#include <string.h>

#include "dynArray.h"

//#pragma GCC diagnostic ignored "-Wtautological-compare"

///
// create a new DynArray
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
// ensure that the dynArray has a capcity of at least the requested capacity
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
