#ifndef DISIMPLEX_ALLOCATOR_H
#define DISIMPLEX_ALLOCATOR_H

#include <cUtils/indexedBlockAllocator.h>

class DiSimplexAllocator : public BlockAllocator {
public:

  DiSimplexAllocator(size_t aNumSides, size_t aBitShift = 5);

  ~DiSimplexAllocator(void);

  /// \brief Allocate an indexed new (sub)structure.
  ///
  /// The indexes returns are contiquous.
  DiSimplex *allocateNewStructure(void);

protected:

  /// \brief Override the BlockAllocator::allocateNewStructure to
  /// prevent its use.
  char *allocateNewStructure(size_t structureSize);

  size_t static numSides2size(size_t numSides);

  size_t numSides;

  size_t itemSize;

};


#endif
