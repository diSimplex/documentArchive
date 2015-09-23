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
  size_t subDimension = -1;
  if (-1 < aSimplex.dimension) subDimension = aSimplex.dimension - 1;

  DiSimplexAllocator *allocator =
    diSimplicies.getItem(aSimplex.dimension + 1, NULL);
  if (!allocator) return DiSimplex(subDimension, 0);

  DiSimplexImpl *aSimplexImpl =
    (DiSimplexImpl*)allocator->getItemPtr(aSimplex.id);
  if (!aSimplexImpl) return DiSimplex(subDimension, 0);

  return DiSimplex(subDimension,
    aSimplexImpl->getSide(aSimplex.dimension, sideNum));
}

DiStructure DiSITTimpl::getLabel(DiSimplex aSimplex) {

  DiSimplexAllocator *allocator =
    diSimplicies.getItem(aSimplex.dimension + 1, NULL);
  if (!allocator) return DiSITT::getUniverse().getInitialStructure();

  DiSimplexImpl *aSimplexImpl =
    (DiSimplexImpl*)allocator->getItemPtr(aSimplex.id);
  if (!aSimplexImpl) return DiSITT::getUniverse().getInitialStructure();

  return DiStructure(aSimplexImpl->getLabel());
}


DiSimplex DiSITTimpl::getSimplex(DiStructure label,
                                    DiSimplexList &someSimplicies) {
  dim_t dimension = someSimplicies.getNumItems() - 1;
  if (!ensureFinalSimplexOfDimExists(dimension)) {
    ASSERT_MESSAGE(false,
      "Could not allocate simplicies of correct dimension");
  }

  DiSimplexAllocator *allocator =
    diSimplicies.getItem(dimension + 1, NULL);
  if (!allocator) return DiSimplex(dimension, 0);

  simpId_t newSimplexId = allocator->allocateNewStructure();
  if (newSimplexId == 0) return DiSimplex(dimension, 0);

  DiSimplexImpl *newSimplex =
    (DiSimplexImpl*) allocator->getItemPtr(newSimplexId);
  if (!newSimplex) return DiSimplex(dimension, 0);

  newSimplex->initializeSimplex(label, someSimplicies);

  return DiSimplex(dimension, newSimplexId);

}

