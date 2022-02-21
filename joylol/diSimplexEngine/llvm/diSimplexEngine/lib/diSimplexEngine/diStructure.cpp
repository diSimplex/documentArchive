#include "diSimplexEngine/diSitt.h"

bool DiStructure::ensureSimpliciesOfNumSidesExist(size_t numSides) {
  if (numSides < diSimplicies.getNumItems()) return true;

  if (diSimplicies.getNumItems() < numSides) {
    if (!ensureSimpliciesOfNumSidesExist(numSides - 1)) return false;
  }

  DiSimplexAllocator *allocator = new DiSimplexAllocator(numSides);

  diSimplicies.pushItem(allocator);

  return true;
}

DiSimplex *DiStructure::addSimplex(DiStructure *aLabel,
                                   DiSimplex::List &someSimplicies) {
  size_t numSides = someSimplicies.getNumItems();
  ensureSimpliciesOfNumSidesExist(numSides);

  DiSimplexAllocator *allocator = diSimplicies.getItem(numSides, NULL);
  ASSERT(allocator);

  DiSimplexAllocatorIterator allocatorIter = allocator->getIterator();
  while (allocatorIter.hasMoreItems()) {
    DiSimplex* curSimplex = allocatorIter.nextItem();
    if (curSimplex->shallowEquals(aLabel, someSimplicies)) {
      return curSimplex;
    }
  }

  DiSimplex *simplex = allocator->allocateNewSimplex();
  ASSERT(simplex);

  simplex->initializeSimplex(aLabel, someSimplicies);

  return simplex;
}

