#include "diSimplexEngine/diSitt.h"

DiSITTimpl *DiSITT::theUniverse = NULL;

bool DiSITTimpl::ensureFinalSimplexOfDimExists(dim_t aDimension) {
  if (aDimension + 1 < diSimplicies.getNumItems()) return true;

  if (diSimplicies.getNumItems() < aDimension + 1) {
    if (!ensureFinalSimplexOfDimExists(aDimension - 1)) return false;
  }

  DiSimplexAllocator *allocator = new DiSimplexAllocator(aDimension);

  diSimplicies.pushItem(allocator);

  if (allocator->allocateNewStructure() != 0) {
    diSimplicies.popItem();
    return false;
  }

  DiSimplexImpl *aSimplexImpl = (DiSimplexImpl*)allocator->getItemPtr(0);
  if (!aSimplexImpl) {
    diSimplicies.popItem();
    return false;
  }

  aSimplexImpl->initializeFinalSimplexDim(aDimension);

  return true;
}

DiSimplex DiSITTimpl::getSide(DiSimplex aSimplex, side_t sideNum) {
  size_t subDimension = 0;
  if (0 < aSimplex.dimension) subDimension = aSimplex.dimension - 1;

  DiSimplexAllocator *allocator =
    diSimplicies.getItem(aSimplex.dimension, NULL);
  if (!allocator) DiSimplex(subDimension, 0);

  DiSimplexImpl *aSimplexImpl =
    (DiSimplexImpl*)allocator->getItemPtr(aSimplex.id);
  if (!aSimplexImpl) DiSimplex(subDimension, 0);

  return DiSimplex(subDimension,
    aSimplexImpl->getSide(aSimplex.dimension, sideNum));
}

