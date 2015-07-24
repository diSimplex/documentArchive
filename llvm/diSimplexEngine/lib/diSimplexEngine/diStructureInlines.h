#ifndef DISTRUCTURE_INLINES_H
#define DISTRUCTURE_INLINES_H

inline DiStructure::DiStructure(DiStructureImpl *aDiStructure) {
  ref = aDiStructure;
}

inline bool DiStructure::isEmpty() {
  return true;
}

inline bool DiStructure::contains(DiSimplex aSimplex) {
  ASSERT(ref);

  if (ref->diSimplicies.getNumItems() <= aSimplex.dimension) {
    if ((ref->extendByFinalSimplicies) && (aSimplex.id == 0)) return true;
    else return false;
  }

  BitSet bitSet = ref->diSimplicies.getItem(aSimplex.dimension, BitSet());

  return bitSet.getBit(aSimplex.id) ? true : false;
}

inline size_t DiStructure::sizeDim(dim_t aDimension) {
  ASSERT(ref);

  if (ref->diSimplicies.getNumItems() <= aDimension) {
    if (ref->extendByFinalSimplicies) return 1;
    else                              return 0;
  }

  BitSet bitSet = ref->diSimplicies.getItem(aDimension, BitSet());

  return bitSet.numNonZero();
}


inline bool DiStructureImpl::initializeStructure(bool final) {
  extendByFinalSimplicies = final;
  return true;
}

#endif
