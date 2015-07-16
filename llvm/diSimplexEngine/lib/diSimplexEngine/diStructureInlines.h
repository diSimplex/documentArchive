#ifndef DISTRUCTURE_INLINES_H
#define DISTRUCTURE_INLINES_H

inline DiStructure::DiStructure(DiStructureImpl *aDiStructure) {
  ref = aDiStructure;
}

inline bool DiStructure::isEmpty() {
  return true;
}

inline bool DiStructure::contains(DiSimplex aSimplex) {
  return false;
}

inline size_t DiStructure::sizeDim(size_t aDimension) {
  return 0;
}


#endif
