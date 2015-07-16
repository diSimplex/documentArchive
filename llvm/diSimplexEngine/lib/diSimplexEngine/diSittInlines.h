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
  return DiStructure(theUniverse->diStructures->getItemPtr(0));
}

inline DiStructure DiSITT::getFinalStructure(void) {
  return DiStructure(theUniverse->diStructures->getItemPtr(1));
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
  diStructures = new DiStructureAllocator();

  // create the initial and final structures as 0 and 1
  size_t initialStruct = diStructures->allocateNewStructure();
  ASSERT(initialStruct == 0);
  diStructures->getItemPtr(0)->initializeStructure();
  size_t finalStruct = diStructures->allocateNewStructure();
  ASSERT(finalStruct == 1);
  diStructures->getItemPtr(1)->initializeStructure(true);
}

inline DiSITTimpl::~DiSITTimpl(void) {
  while(diSimplicies.getNumItems()) {
    DiSimplexAllocator *allocator = diSimplicies.popItem();
    if (allocator) delete allocator;
  }
  if (diStructures) delete diStructures;
}

inline DiStructure DiSITTimpl::getLabel(DiSimplex aSimplex) {
  return DiStructure(NULL);
}

#endif
