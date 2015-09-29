#ifndef DISTRUCTURE_INLINES_H
#define DISTRUCTURE_INLINES_H

inline DiStructure::DiStructure(DiStructureImpl *aDiStructure) {
  ref = aDiStructure;
}

inline bool DiStructure::isEmpty(void) {
  ASSERT(ref);
//  ASSERT_MESSAGE(false, "FIX DiStructure::isEmpty");
  for (size_t i = 0; i < ref->diSimplicies.getNumItems(); i++) {
    BitSet bitSet = ref->diSimplicies.getItem(i, BitSet());
    if (!bitSet.isEmpty()) return false;
  }
  return true;
}

inline bool DiStructure::isFinal(void) {
  ASSERT(ref)
  return ref->isFinalStructure;
}

inline bool DiStructure::contains(DiSimplex aSimplex) {
  ASSERT(ref);

  if (ref->isFinalStructure) {
    if (aSimplex.id == 0) return true;
    return false;
  }

  if (ref->diSimplicies.getNumItems() <= aSimplex.dimension) {
    return false;
  }

  BitSet bitSet = ref->diSimplicies.getItem(aSimplex.dimension, BitSet());

  return bitSet.getBit(aSimplex.id) ? true : false;
}

inline size_t DiStructure::sizeDim(dim_t aDimension) {
  ASSERT(ref);

  if (ref->isFinalStructure) return 1;

  if (ref->diSimplicies.getNumItems() <= aDimension) return 0;

  BitSet bitSet = ref->diSimplicies.getItem(aDimension, BitSet());

  return bitSet.numNonZero();
}


inline DiStructure DiStructure::clone(void) {
  return DiStructure(ref->clone());
}

inline DiStructureImpl *DiStructureImpl::clone(void) {
  DiStructureImpl *newStructure = DiSITTimpl::getUniverse()->getNewStructure();
  for ( VarArrayIterator<BitSet> iter = diSimplicies.getIterator() ;
        iter.hasMoreItems() ; ) {
    newStructure->diSimplicies.pushItem(iter.nextItem().clone());
  }
  return newStructure;
}

inline bool DiStructureImpl::initializeStructure(bool final) {
  isFinalStructure = final;
  return true;
}

#endif
