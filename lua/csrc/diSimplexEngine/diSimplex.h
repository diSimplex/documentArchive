#ifndef DISIMPLEX_H
#define DISIMPLEX_H

#include "dynArray.h"
#include "diSiTT.h"

// Store the side into the simplex provided
extern void simplex_store_side(DiSiTT *disitt,
                               dimension_t dimensionOfSimplex,
                               simplex_id  parentSimplex,
                               int         sideNumber,
                               simplex_id  sideSimplex);

// Return the requested side
extern simplex_id simplex_get_side(DiSiTT *disitt,
                                   dimension_t dimensionOfSimplex,
                                   simplex_id  parentSimplex,
                                   int         sideNumber);

// provide a human readable output of the given simplex
extern void simplex_toString(DiSiTT *disitt,
                             dimension_t dimension,
                             simplex_id simplex_id,
                             char *buffer,
                             size_t bufferSize);

#endif
