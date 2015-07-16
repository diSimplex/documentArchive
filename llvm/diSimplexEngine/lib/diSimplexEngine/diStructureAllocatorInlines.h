#ifndef DISTRUCTURE_ALLOCATOR_INLINES_H
#define DISTRUCTURE_ALLOCATOR_INLINES_H

inline DiStructureAllocator::DiStructureAllocator(void) :
  IndexedBlockAllocator(sizeof(DiStructureImpl)) {
}

inline DiStructureAllocator::~DiStructureAllocator(void) {
}

inline DiStructureImpl *DiStructureAllocator::getItemPtr(size_t itemNum) {
  return (DiStructureImpl*)IndexedBlockAllocator::getItemPtr(itemNum);
}

#endif
