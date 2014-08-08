#ifndef DISIMPLEXENGINE_H
#define DISIMPLEXENGINE_H

#include "dynArray.h"

#ifndef bool
#define bool	int
#define true	1
#define false	0
#endif

/*

The main diSiTT object, which contains a pair of UT_array of pointers
to UT_arrays. Each sub-UT_array in the "instance" UT_array, contains
the collection of simplex instances for a specific dimension. Each
sub-UT_array in the "simplex_icd" UT_array, contains the simplex_icd
required by the UT_array code for each corresponding dimension of
simplex cotained in the "instance" UT_array.

The simplex at the zero-th index of the "instance" sub-UT_array, is the
Universe simplex of that dimension.

*/
typedef struct DiSiTTStruct {
  DynArray *instances;
  DynArray *emptySimplicies;
} DiSiTT;

// Initialize a DiSiTT instance
extern void dse_init_disitt(DiSiTT *disitt);

typedef int dimension_t;
typedef unsigned int simplex_id;

typedef struct DiSimplexObjStruct {
  unsigned int flags;
  simplex_id side[1];
} DiSimplexObj;

#define DSE_SIMPLEX_INUSE	1

// Compute the size in bytes required to store an actual simplex structure
// of a given dimension.
//
#define  DiSimplexObjSize(dimension) \
  (size_t)(sizeof(DiSimplexObj) + ((dimension)+1)*sizeof(simplex_id))

typedef struct DiSimplexRefStruct {
  DiSiTT      *disitt;
  dimension_t  dimension;
  simplex_id   simplex;
} DiSimplexRef;

#define instances_dimension_exists(disitt, dimension) \
  ( dimension < (DynArray_len(disitt->instances)))

// Ensure that a given dimensionn (and all smaller dimensions)
// have been added to this DiSiTT's collection of instances
//
extern void instances_ensure_dimension(DiSiTT *disitt,
                                       dimension_t newDimension);

// Check that a give simplex exists
extern bool instances_simplex_exists(DiSiTT *disitt,
                                     dimension_t dimension,
                                     simplex_id  simplex);

// Get the next available empty simplex for a given dimension
extern simplex_id instances_get_empty_simplex(DiSiTT     *disitt,
                                              dimension_t dimension);

// Return the given simplex to the pool of avaialble empty simpleices
// for a given dimension
extern void instances_return_simplex(DiSiTT     *disitt,
                                     dimension_t dimension,
                                     simplex_id  simplex);

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
