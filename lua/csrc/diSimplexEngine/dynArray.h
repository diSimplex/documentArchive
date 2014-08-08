#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t len;
  size_t capacity;
  size_t elementSize;
  char* data;
} DynArray;

#define DYNARRAY_CAPACITY_INCREMENT	10L

#define DYNARRAY_CALLOC	calloc
#define DYNARRAY_FREE	free

///
// create a new DynArray
extern DynArray *DynArray_new(size_t elementSize, size_t initialCapacity);

///
// destroy the DynArray
#define DynArray_free(dynArray)						\
  if (dynArray) {							\
    if (dynArray->data) { 						\
      DYNARRAY_FREE(dynArray->data);					\
      dynArray->data = NULL;						\
     }									\
    DYNARRAY_FREE(dynArray);						\
    dynArray = NULL;							\
  }

///
// return the current number of elements in the array
#define DynArray_len(dynArray)	((dynArray)->len)

///
// return the current number of elements in the array
#define DynArray_size(dynArray)	((dynArray)->len)

///
// return the current potential number of elements in the array
#define DynArray_capacity(dynArray)	((dynArray)->capacity)

///
// return the size of the dynArray elements
#define	DynArray_elementSize(dynArray)	((dynArray)->elementSize)

///
// ensure that the dynArray has a capcity of at least the requested capacity
#define DynArray_ensureCapacity(dynArray, requestedCapacity) 		\
  if ((dynArray)->capacity < (requestedCapacity)) {			\
    DynArray_increaseCapacity(dynArray, requestedCapacity);		\
  }

///
// ensure that the dynArray has the capacity to add numElementsToAdd
#define DynArray_ensureCanAddElements(dynArray, numElementsToAdd)	\
  DynArray_ensureCapacity(dynArray, 					\
                           (DynArray_len(dynArray) + numElementsToAdd))

extern void DynArray_increaseCapacity(DynArray *dynArray,
                                      size_t requesedCapacity);
///
// Add an new element which is zeroed
#define DynArray_addZeroedElement(dynArray)				\
  do {									\
    DynArray_ensureCanAddElements(dynArray, 1);				\
    (dynArray)->len++;							\
  } while(0)

///
// returns a pointer of the type elementType
// to the elementIndex-th element in the dynArray.
#define DynArray_getElementPtr(dynArray, elementIndex, elementType)	\
  ((elementType*)(((dynArray)->data)+(elementIndex*((dynArray)->elementSize))))

///
// Add a new element of type
#define DynArray_addElement(dynArray, elementType, elementValue)	\
  DynArray_addZeroedElement(dynArray);					\
  (*(DynArray_getElementPtr(dynArray, (((dynArray)->len)-1), elementType))) = elementValue

#endif
