#ifndef DISTRUCTURE_ALLOCATOR_H
#define DISTRUCTURE_ALLOCATOR_H

#include <cUtils/indexedBlockAllocator.h>

class DiStructureAllocator : public IndexedBlockAllocator {
public:

  DiStructureAllocator(void);

  ~DiStructureAllocator(void);

  DiStructureImpl *getItemPtr(size_t itemNum);

protected:

};


#endif
