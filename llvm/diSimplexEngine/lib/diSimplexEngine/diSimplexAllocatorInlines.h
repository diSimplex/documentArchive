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

inline DiSimplex *DiSimplexAllocator::allocateNewSimplex(void) {
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

inline DiSimplexAllocatorIterator DiSimplexAllocator::getIterator(void) {
  DiSimplexAllocatorIterator iter(this);
  return iter;
}

inline DiSimplexAllocatorIterator::DiSimplexAllocatorIterator(DiSimplexAllocator *anAllocator) {
  ASSERT(anAllocator);

  baseAllocator = anAllocator;
  curBlock = 0;
  curAllocationByte = baseAllocator->blocks.getItem(curBlock, NULL);
  ASSERT(curAllocationByte);

  endAllocationByte = curAllocationByte + baseAllocator->blockSize;
}

inline DiSimplexAllocatorIterator::~DiSimplexAllocatorIterator(void) {
  baseAllocator = NULL;
  curBlock = 0;
  curAllocationByte = NULL;
  endAllocationByte = NULL;
}

inline bool DiSimplexAllocatorIterator::hasMoreItems(void) {
  ASSERT(baseAllocator);

  // we are not in the last block...
  if (curBlock + 1 < baseAllocator->blocks.getNumItems()) return true;

  // we are in the last block but we are not at the last allocation
  if (curAllocationByte < baseAllocator->curAllocationByte) return true;

  return false;
}

inline DiSimplex *DiSimplexAllocatorIterator::nextItem(void) {
  ASSERT(baseAllocator);
  ASSERT(curBlock < baseAllocator->blocks.getNumItems());

  DiSimplex *simplex = (DiSimplex*)curAllocationByte;

  curAllocationByte += baseAllocator->itemSize;
  if (endAllocationByte <= curAllocationByte) {
    curBlock++;
    curAllocationByte = baseAllocator->blocks.getItem(curBlock, NULL);
    ASSERT(curAllocationByte);
    endAllocationByte = curAllocationByte + baseAllocator->blockSize;
  }

  return simplex;
}

#endif
