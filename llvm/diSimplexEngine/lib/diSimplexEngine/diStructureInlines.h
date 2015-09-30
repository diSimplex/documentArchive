#ifndef DISTRUCTURE_INLINES_H
#define DISTRUCTURE_INLINES_H

inline bool DiStructure::isEmpty(void) {
  for ( VarArrayIterator<BlockAllocator*> iter = diSimplicies.getIterator() ;
        iter.hasMoreItems() ; ) {
    if (!iter.nextItem()->isEmpty()) return false;
  }
  return true;
}

inline bool DiStructure::isFinal(void) {
  return isFinalStructure;
}

inline bool DiStructure::initializeStructure(bool final) {
  isFinalStructure = final;
  return true;
}

#endif
