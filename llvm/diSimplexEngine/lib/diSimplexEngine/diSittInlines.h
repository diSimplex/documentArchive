#ifndef DISITT_INLINES_H
#define DISITT_INLINES_H

#include <cUtils/varArray.h>
#include "diSimplexEngine/diSitt.h"

inline DiSITT DiSITT::getUniverse(void) {
  if (!theUniverse) theUniverse = new DiSITTimpl();
  return DiSITT(theUniverse);
}

inline void DiSITT::cleanUpUniverse(void) {
  if (theUniverse) delete theUniverse;
  theUniverse = NULL;
}

inline DiStructure DiSITT::getInitialStructure(void) {
  return DiStructure(NULL);
}

inline DiStructure DiSITT::getFinalStructure(void) {
  return DiStructure(NULL);
}

inline DiSimplex DiSITT::getFinalSimplexDim(size_t aDimension) {
  if (!ref->ensureFinalSimplexOfDimExists(aDimension)) {
    ASSERT_MESSAGE(false,
      "Could not allocate simplicies of correct dimension");
  }
  return DiSimplex(aDimension, 0);
}

inline DiStructure DiSITT::getLabel(DiSimplex aSimplex) {
  return theUniverse->getLabel(aSimplex);
}

inline DiSimplex DiSITT::getSide(DiSimplex aSimplex, size_t sideNum) {
  return theUniverse->getSide(aSimplex, sideNum);
}


inline DiSITT::DiSITT(DiSITTimpl *aUniverse) {
  ref = aUniverse;
}

inline DiSITT::~DiSITT(void) {
  ref = NULL;
}

inline DiSITTimpl::DiSITTimpl(void) {

}

inline DiSITTimpl::~DiSITTimpl(void) {
  while(diSimplicies.getNumItems()) {
    DiSimplexAllocator *allocator = diSimplicies.popItem();
    if (allocator) delete allocator;
  }
}

inline DiStructure DiSITTimpl::getLabel(DiSimplex aSimplex) {
  return DiStructure(NULL);
}

#endif
