#ifndef DISIMPLEX_ALLOCATOR_H
#define DISIMPLEX_ALLOCATOR_H

#include <cUtils/indexedBlockAllocator.h>

class DiSimplexAllocator : public IndexedBlockAllocator {
public:

  DiSimplexAllocator(size_t aDimension);

  ~DiSimplexAllocator(void);

protected:

  size_t static dimension2size(size_t aDimension);

  size_t dimension;

};


#endif
