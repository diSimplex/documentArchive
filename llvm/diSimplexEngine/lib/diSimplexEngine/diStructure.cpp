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

