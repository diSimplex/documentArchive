#ifndef DISIMPLEX_ALLOCATOR_INLINES_H
#define DISIMPLEX_ALLOCATOR_INLINES_H

inline DiSimplexAllocator::DiSimplexAllocator(size_t aDimension) :
  IndexedBlockAllocator(dimension2size(aDimension)) {
  dimension = aDimension;
}

inline DiSimplexAllocator::~DiSimplexAllocator(void) {
}

inline size_t DiSimplexAllocator::dimension2size(size_t aDimension) {
 return sizeof(DiSimplexImpl) + (aDimension+1)*sizeof(size_t);
}


#endif
