#ifndef DISIMPLEX_ALLOCATOR_H
#define DISIMPLEX_ALLOCATOR_H

#include <cUtils/indexedBlockAllocator.h>

class DiSimplexAllocator : public IndexedBlockAllocator {
public:

  DiSimplexAllocator(dim_t aDimension);

  ~DiSimplexAllocator(void);

protected:

  size_t static dimension2size(dim_t aDimension);

  dim_t dimension;

};


#endif
