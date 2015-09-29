#ifndef DISITT_INLINES_H
#define DISITT_INLINES_H

#include <cUtils/varArray.h>
#include "diSimplexEngine/diSitt.h"

inline DiSITT DiSITT::getUniverse(void) {
  return DiSITT(DiSITTimpl::getUniverse());
}

inline void DiSITT::cleanUpUniverse(void) {
  DiSITTimpl::cleanUpUniverse();
}

inline DiStructure DiSITT::getInitialStructure(void) {
  return DiStructure(ref->getInitialStructure());
}

inline DiStructure DiSITT::getFinalStructure(void) {
  return DiStructure(ref->getFinalStructure());
}

inline DiSimplex DiSITT::getFinalSimplexDim(dim_t aDimension) {
  if (!ref->ensureFinalSimplexOfDimExists(aDimension)) {
    ASSERT_MESSAGE(false,
      "Could not allocate simplicies of correct dimension");
  }
  return DiSimplex(aDimension, 0);
}

//inline DiSimplex DiSITT::getSimplex(DiStructure label,
//                                    DiSimplexList &someSimplicies) {
//  return theUniverse->getSimplex(label, someSimplicies);
//}

inline DiSITT::DiSITT(DiSITTimpl *aUniverse) {
  ref = aUniverse;
}

inline DiSITT::~DiSITT(void) {
  ref = NULL;
}

inline DiSITTimpl *DiSITTimpl::getUniverse(void) {
  if (!theUniverse) theUniverse = new DiSITTimpl();
  return theUniverse;
}

inline void DiSITTimpl::cleanUpUniverse(void) {
  if (theUniverse) delete theUniverse;
  theUniverse = new DiSITTimpl();
}

inline DiStructureImpl *DiSITTimpl::getInitialStructure(void) {
  ASSERT(theUniverse);
  return theUniverse->diStructures->getStructurePtr(0);
}

inline DiStructureImpl *DiSITTimpl::getFinalStructure(void) {
  ASSERT(theUniverse);
  return theUniverse->diStructures->getStructurePtr(1);
}

inline DiSITTimpl::DiSITTimpl(void) {
  diStructures = new DiStructureAllocator();

  // create the initial and final structures as 0 and 1
  strucId_t initialStruct = diStructures->allocateNewStructure();
  ASSERT(initialStruct == 0);
  diStructures->getStructurePtr(0)->initializeStructure(false);

  strucId_t finalStruct = diStructures->allocateNewStructure();
  ASSERT(finalStruct == 1);
  diStructures->getStructurePtr(1)->initializeStructure(true);
}

inline DiSITTimpl::~DiSITTimpl(void) {
  while(diSimplicies.getNumItems()) {
    DiSimplexAllocator *allocator = diSimplicies.popItem();
    if (allocator) delete allocator;
  }
  if (diStructures) delete diStructures;
}

inline DiStructureImpl *DiSITTimpl::getNewStructure(void) {
  strucId_t newStructureId = diStructures->allocateNewStructure();
  ASSERT(newStructureId != 0);
  ASSERT(newStructureId != 1);
  return diStructures->getStructurePtr(newStructureId);
}

#endif
