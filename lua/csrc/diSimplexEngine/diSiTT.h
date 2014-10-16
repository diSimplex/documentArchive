#ifndef DISITT_H
#define DISITT_H

#include "dynArray.h"

#ifndef bool
#define bool	int
#define true	1
#define false	0
#endif

/***

The diSimplexEngine's DiSiTT component.

All of the macros in this component are pure C helper macros.

A DiSiTT structure provides an encapsulated environment in which
directed simplicial structures can exist. Note that a given Lua script
can interact with multiple DiSiTT structures, each of which will be
totally separate from each other.

@module diSimplexEngine.diSiTT.macros
*/

/*

The main diSiTT object, which contains four DynArrays of pointers to
DynArrays. Each sub-DynArray in the "simplicies" DynArray, contains the
collection of simplex instances for a specific dimension. Each
sub-DynArray in the "simplex_icd" DynArray, contains the simplex_icd
required by the DynArray code for each corresponding dimension of
simplex cotained in the "simplicies" DynArray.

The simplex at the zero-th index of the "simplicies" sub-DynArray, is
the Universe simplex of that dimension.

*/
typedef struct DiSiTTStruct {
  DynArray *simplicies;
  DynArray *emptySimplicies;
  DynArray *structures;
  DynArray *emptyStructures;
} DiSiTT;

// Initialize a DiSiTT instance
extern void diSiTT_init(DiSiTT *disitt);

typedef int dimension_t;
typedef unsigned int simplex_id;
typedef unsigned int structure_id;

// Ensure that a given dimensionn (and all smaller dimensions)
// have been added to this DiSiTT's collection of simplicies
//
extern void diSitt_ensure_dimension(DiSiTT *disitt,
                                    dimension_t newDimension);

// Collect all unused diSimplicies and diStructures.
extern void diSiTT_collect_garbage(DiSiTT *disitt);

// ==========================================================================
// DiSimplex objects

typedef struct DiSimplexObjStruct {
  unsigned int flags;
  structure_id structure;
  simplex_id side[1];
} DiSimplexObj;

// diSimplex flags --- powers of 2 indexing in a bit-array
#define DISITT_DISIMPLEX_INUSE	 1
#define DISITT_DISIMPLEX_GC_MARK 2

///
// Compute the size in bytes required to store an actual simplex structure
// of a given dimension.
// @function DiSimplexObjSize
// @param dimension :: dimension_t; the dimension of the diSimplex.
// @return size_t; the size of the requested diSimplex.
#define  DiSimplexObjSize(dimension) \
  (size_t)(sizeof(DiSimplexObj) + ((dimension)+1)*sizeof(simplex_id))

typedef struct DiSimplexRefStruct {
  DiSiTT      *diSiTT;
  dimension_t  dimension;
  simplex_id   simplex;
} DiSimplexRef;

// ==========================================================================
// DiStructure objects

// Each of the DiStructureObj's dimensions is an ordered array of
// simplexIds.

typedef struct DiStructureObjStruct {
  unsigned int flags;
  DynArray *dimensions;  // a DynArray of DynArrays
  DiSimplexRef curSimplex;
} DiStructureObj;

// diStructure flags --- powers of 2 indexing in a bit-array
#define DISITT_DISTRUCTURE_INUSE   1
#define DISITT_DISTRUCTURE_GC_MARK 2

typedef struct DiStructureRefStruct {
  DiSiTT       *diSiTT;
  structure_id  structure;
} DiStructureRef;

#endif
