#include "diSimplexEngine/diSitt.h"

DiSITTimpl *DiSITTimpl::theUniverse = new DiSITTimpl();

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

DiSimplexImpl *DiSITTimpl::getSimplex(DiSimplex aSimplex) {

  DiSimplexAllocator *allocator =
    diSimplicies.getItem(aSimplex.dimension + 1, NULL);
  if (!allocator) return NULL;

  DiSimplexImpl *aSimplexImpl =
    (DiSimplexImpl*)allocator->getItemPtr(aSimplex.id);
  if (!aSimplexImpl) return NULL;

  return aSimplexImpl;
}

DiSimplexImplTuple DiSITTimpl::getNewSimplex(dim_t dimension) {
  if (dimension < -1) dimension = -1;

  if (!ensureFinalSimplexOfDimExists(dimension)) {
    ASSERT_MESSAGE(false,
      "Could not allocate simplicies of correct dimension");
  }

  DiSimplexAllocator *allocator =
    diSimplicies.getItem(dimension + 1, NULL);
  if (!allocator) return DiSimplexImplTuple(-1, 0, NULL);

  simpId_t newSimplexId = allocator->allocateNewStructure();
  if (newSimplexId == 0) return DiSimplexImplTuple(-1, 0, NULL);

  DiSimplexImpl *newSimplex =
    (DiSimplexImpl*) allocator->getItemPtr(newSimplexId);

  return DiSimplexImplTuple(dimension, newSimplexId, newSimplex);
}

//DiSimplexImpl *DiSITTimpl::getSimplex(DiStructure label,
//                                    DiSimplexList &someSimplicies) {
//  dim_t dimension = someSimplicies.getNumItems() - 1;
//  if (!ensureFinalSimplexOfDimExists(dimension)) {
//    ASSERT_MESSAGE(false,
//      "Could not allocate simplicies of correct dimension");
//  }
//
//  DiSimplexAllocator *allocator =
//    diSimplicies.getItem(dimension + 1, NULL);
//  if (!allocator) return DiSimplex(dimension, 0);
//
//  simpId_t newSimplexId = allocator->allocateNewStructure();
//  if (newSimplexId == 0) return DiSimplex(dimension, 0);
//
//  DiSimplexImpl *newSimplex =
//    (DiSimplexImpl*) allocator->getItemPtr(newSimplexId);
//  if (!newSimplex) return DiSimplex(dimension, 0);
//
//  newSimplex->initializeSimplex(label, someSimplicies);
//
//  return DiSimplex(dimension, newSimplexId);
//}

