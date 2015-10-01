#ifndef DISIMPLEX_ALLOCATOR_H
#define DISIMPLEX_ALLOCATOR_H

#include <cUtils/indexedBlockAllocator.h>

class DiSimplexAllocatorIterator;

class DiSimplexAllocator : public BlockAllocator {
public:

  DiSimplexAllocator(size_t aNumSides, size_t aBitShift = 5);

  ~DiSimplexAllocator(void);

  /// \brief Allocate an indexed new (sub)structure.
  ///
  /// The indexes returns are contiquous.
  DiSimplex *allocateNewSimplex(void);

  DiSimplexAllocatorIterator getIterator(void);

protected:

  /// \brief Override the BlockAllocator::allocateNewStructure to
  /// prevent its use.
  char *allocateNewStructure(size_t structureSize);

  size_t static numSides2size(size_t numSides);

  size_t numSides;

  size_t itemSize;

  friend class DiSimplexAllocatorIterator;

};

class DiSimplexAllocatorIterator {
public:

  bool hasMoreItems(void);

  DiSimplex *nextItem(void);

  ~DiSimplexAllocatorIterator(void);

protected:

  DiSimplexAllocatorIterator(DiSimplexAllocator *allocator);

protected:

  DiSimplexAllocator *baseAllocator;

  char* curAllocationByte;

  char* endAllocationByte;

  size_t curBlock;

  friend class DiSimplexAllocator;
};

#endif
