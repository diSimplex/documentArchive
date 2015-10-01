#ifndef DISTRUCTURE_INLINES_H
#define DISTRUCTURE_INLINES_H

inline bool DiStructure::isEmpty(void) {
  if (flags & FINAL) return false;

  for ( VarArrayIterator<DiSimplexAllocator*> iter =
          diSimplicies.getIterator() ;
        iter.hasMoreItems() ; ) {
    if (!iter.nextItem()->isEmpty()) return false;
  }
  return true;
}

inline bool DiStructure::isFinal(void) {
  return (flags & FINAL) ? true : false;
}

inline void DiStructure::freeze(void) {
  flags |= FROZEN;
}

inline bool DiStructure::isFrozen(void) {
  return (flags & FROZEN) ? true : false;
}

inline DiStructure *DiStructure::clone(void) {
  DiStructure *newStruct =
    DiSITT::getUniverse()->getNewStructure(flags & (~FROZEN) & (~FINAL));
  return newStruct;
}

inline DiSimplex *DiStructure::addSimplex(DiStructure *aLabel,
                                          DiSimplex::List &someSimplicies) {
  size_t numSides = someSimplicies.getNumItems();
  ensureSimpliciesOfNumSidesExist(numSides);

  DiSimplexAllocator *allocator = diSimplicies.getItem(numSides, NULL);
  ASSERT(allocator);

  DiSimplex *simplex = allocator->allocateNewStructure();
  ASSERT(simplex);

  simplex->initializeSimplex(aLabel, someSimplicies);

  return simplex;
}

inline DiStructure::DiStructure(void) { }

inline DiStructure::~DiStructure(void) {
  for ( VarArrayIterator<DiSimplexAllocator*> iter =
          diSimplicies.getIterator() ; iter.hasMoreItems(); ) {
    DiSimplexAllocator *allocator = iter.nextItem();
    if (allocator) delete allocator;
  }
  diSimplicies.~VarArray();
  flags = 0;
}

inline bool DiStructure::initializeStructure(size_t someFlags) {
  flags = someFlags;
  return true;
}

#endif
