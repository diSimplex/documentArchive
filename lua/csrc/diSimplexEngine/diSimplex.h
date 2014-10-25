#ifndef DISIMPLEX_H
#define DISIMPLEX_H

#include "dynArray.h"
#include "diSiTT.h"
#include "diStructure.h"

#define diSimplexRef_get_simplicies_or_return_false(simplexRef, simpliciesDynArray) \
  DynArray *(simplicies);						\
  if (true) {								\
    DiSiTT *diSiTT = (simplexRef)->diSiTT;				\
    dimension_t dimension = (simplexRef)->dimension;			\
    if (dimension < 0) dimension = 0;					\
    if ( DynArray_len(diSiTT->simplicies) <= dimension ) return false;	\
    (simpliciesDynArray) =						\
      *DynArray_getElementPtr(diSiTT->simplicies, dimension, DynArray*);\
  }

#define diSimplexRef_get_simplexObj_or_return_false(simplexRef, simplexObj) \
  DiSimplexObj *(simplexObj);						    \
  if (true) {								    \
    diSimplexRef_get_simplicies_or_return_false(simplexRef, simplicies);    \
    if (DynArray_len(simplicies) <= (simplexRef)->simplex) return false;    \
    (simplexObj) =							    \
        DynArray_getElementPtr(simplicies, (simplexRef)->simplex, DiSimplexObj); \
  }

#define diSimplexRef_init(diSimplexRef, diSiTTPtr, dimensionId,		\
                          simplexId, structureId) 			\
  if (diSimplexRef) {							\
    (diSimplexRef)->diSiTT    = (diSiTTPtr);				\
    (diSimplexRef)->dimension = (dimensionId);				\
    (diSimplexRef)->simplex   = (simplexId);				\
    (diSimplexRef)->structure = (structureId);				\
  }

//
// Determine if two diSimplicies are equal by ensuring that one of the two
// simplicies underlying structures is contained in the other, and that both
// simplicies have the same ordered collection of sides.
// @function diSimplex_equal
// @param mySimplex :: DiSimplexRef*;
// @param otherSimplex :: DiSimplexRef*;
// @return bool; true if both simplicies are equal; false otherwise.
extern bool diSimplex_equals(DiSimplexRef *mySimplex,
                             DiSimplexRef *otherSimplex);

// Check that a give diSimplex exists
extern bool diSimplex_exists(DiSimplexRef *simplex);

// Get the next available empty diSimplex for a given dimension
extern bool diSimplex_get_empty(DiSimplexRef *emptySimplex);

// Release the given diSimplex back to the pool of available empty
// diSimpleices for a given dimension.
extern bool diSimplex_release(DiSimplexRef *simplex);

// Store the side into the simplex provided
extern bool diSimplex_store_side(DiSimplexRef *parentSimplex,
                                 size_t        sideNumber,
                                 DiSimplexRef *sideSimplex);

// Return the requested side
extern bool diSimplex_get_side(DiSimplexRef *parentSimplex,
                               size_t       sideNumber,
                               DiSimplexRef *sideSimplex);

// provide a human readable output of the given simplex
extern void diSimplex_toString(DiSimplexRef *simplex,
                               char *buffer,
                               size_t bufferSize);

#endif
