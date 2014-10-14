#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stdlib.h>
#include <string.h>

/***
The diSimplexEngine's dynamic array component (c-macros).
All of the macros in this component are pure C helper macros.

A DynArray is a dynamical array which has both allocated elements and
additional capacity for new elements. Once new elements have been added
which exhaust the current capacity, new capacity will be allocated.

@module diSimplexEngine.dynArray.macros
*/

typedef struct {
  size_t len;
  size_t capacity;
  size_t elementSize;
  char* data;
} DynArray;

#define DYNARRAY_CAPACITY_INCREMENT	10L

#define DYNARRAY_CALLOC	calloc
#define DYNARRAY_FREE	free

extern DynArray *DynArray_new(size_t elementSize, size_t initialCapacity);

///
// Macro to destroy a DynArray.
// @function DynArray_free
// @param dynArray :: DynArray*; the dynArray to be freed.
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
// Return the current number of elements in the array.
// @function DynArray_len
// @param dynArray :: DynArray*; the dynArray.
// @return size_t; the number of elements in the dynArray.
#define DynArray_len(dynArray)	((dynArray)->len)

///
// Return the current number of elements in the array.
// @function DynArray_size
// @param dynArray :: DynArray*; the dynArray.
// @return size_t; the number of elements in the dynArray.
#define DynArray_size(dynArray)	((dynArray)->len)

///
// Return the current potential number of elements in the array.
// @function DynArray_capacity
// @param dynArray :: DynArray*; the dynArray.
// @return size_t; the number of possible elements in the dynArray if full.
#define DynArray_capacity(dynArray)	((dynArray)->capacity)

///
// Return the size of an indivicual dynArray element.
// @function DynArray_elementSize
// @param dynArray :: DynArray*; the dynArray.
// @return size_t; the size of an individual elements in the dynArray.
#define	DynArray_elementSize(dynArray)	((dynArray)->elementSize)

///
// Ensure that the dynArray has a capcity of at least the requested capacity.
// @function DynArray_ensureCapacity
// @param dynArray :: DynArray*; the dynArray.
// @param requestedCapacity :: size_t; the total capacity required.
#define DynArray_ensureCapacity(dynArray, requestedCapacity) 		\
  if ((dynArray)->capacity < (requestedCapacity)) {			\
    DynArray_increaseCapacity(dynArray, requestedCapacity);		\
  }

///
// Ensure that the dynArray has the capacity to add numElementsToAdd.
// @function DynArray_ensureCanAddElements
// @param dynArray :: DynArray*; the dynArray.
// @param numElementsToAdd :: size_t; the number of ***additional*** elements to be added.
#define DynArray_ensureCanAddElements(dynArray, numElementsToAdd)	\
  DynArray_ensureCapacity(dynArray, 					\
                           (DynArray_len(dynArray) + numElementsToAdd))

extern void DynArray_increaseCapacity(DynArray *dynArray,
                                      size_t requesedCapacity);
///
// Add an new element which is zeroed.
// @function DynArray_addZeroedElement
// @param dynArray :: DynArray*; the dynArray.
#define DynArray_addZeroedElement(dynArray)				\
  do {									\
    DynArray_ensureCanAddElements(dynArray, 1);				\
    (dynArray)->len++;							\
  } while(0)

///
// Returns a pointer of the type elementType
// to the elementIndex-th element in the dynArray.
// @function DynArray_getElementPtr
// @param dynArray :: DynArray*; the dynArray.
// @param elementIndex :: size_t; the requested element (zero relative).
// @param elementType :: macro-text; the C type of the element to which to cast.
// @return a type cast pointer to the requested element.
#define DynArray_getElementPtr(dynArray, elementIndex, elementType)	\
  ((elementType*)(((dynArray)->data)+(elementIndex*((dynArray)->elementSize))))

///
// Add a new element of type
// @function DynArray_addElement
// @param dynArray :: DynArray*; the dynArray.
// @param elementType :: macro-text; the C type of the element to be added.
// @param elementValue :: macro-text; the C value of the element.
#define DynArray_addElement(dynArray, elementType, elementValue)	\
  DynArray_addZeroedElement(dynArray);					\
  (*(DynArray_getElementPtr(dynArray, (((dynArray)->len)-1), elementType))) = elementValue

#endif
