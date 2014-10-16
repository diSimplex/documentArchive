#ifndef DISIMPLEX_H
#define DISIMPLEX_H

#include "dynArray.h"
#include "diSiTT.h"

#define diSimplexRef_init(diSimplexRef, diSiTTPtr, dimensionId, simplexId) \
  if (diSimplexRef) {							   \
    (diSimplexRef)->diSiTT    = diSiTTPtr;				   \
    (diSimplexRef)->dimension = dimensionId;				   \
    (diSimplexRef)->simplex   = simplexId;				   \
  }

// Check that a give diSimplex exists
extern bool diSimplex_exists(DiSimplexRef *simplex);

// Get the next available empty diSimplex for a given dimension
extern bool diSimplex_get_empty(DiSimplexRef *emptySimplex);

// Release the given diSimplex back to the pool of available empty
// diSimpleices for a given dimension.
extern void diSimplex_release(DiSimplexRef *simplex);

// Store the side into the simplex provided
extern void diSimplex_store_side(DiSimplexRef *parentSimplex,
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
