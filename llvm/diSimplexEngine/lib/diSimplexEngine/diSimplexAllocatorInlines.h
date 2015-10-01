#ifndef DISIMPLEX_ALLOCATOR_INLINES_H
#define DISIMPLEX_ALLOCATOR_INLINES_H

inline DiSimplexAllocator::DiSimplexAllocator(size_t aNumSides,
                                              size_t aBitShift ) :
  BlockAllocator((1<<aBitShift)*numSides2size(aNumSides)) {
  numSides = aNumSides;
  itemSize = numSides2size(aNumSides);
}

inline DiSimplexAllocator::~DiSimplexAllocator(void) {
}

inline DiSimplex *DiSimplexAllocator::allocateNewStructure(void) {
  ASSERT(invariant());

  DiSimplex *newSimplex =
    (DiSimplex*)BlockAllocator::allocateNewStructure(itemSize);
  ASSERT(newSimplex);

  newSimplex->numSides = numSides;

  return newSimplex;
}

inline size_t DiSimplexAllocator::numSides2size(size_t numSides) {
 return sizeof(DiSimplex) + (numSides)*sizeof(DiSimplex*);
}

inline char *DiSimplexAllocator::allocateNewStructure(size_t structureSize) {
  ASSERT(invariant());
  return NULL;
}

#endif
