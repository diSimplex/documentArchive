#ifndef DISIMPLEX_INLINES_H
#define DISIMPLEX_INLINES_H

#include <stdint.h>
#include <diSimplexEngine/diSimplex.h>

inline DiSimplex::~DiSimplex(void) {
}

inline dim_t DiSimplex::dimension(void) {
  return numSides - 1;
}

inline DiStructure *DiSimplex::getLabel(void) {
  return label;
}

inline DiSimplex *DiSimplex::getSide(side_t sideNum) {
//  size_t subDimension = -1;
//  if (-1 < dimension) subDimension = dimension - 1;
//
//  DiSimplexImpl *simplexImpl = DiSITTimpl::getUniverse()->getSimplex(*this);
//  if (!simplexImpl) return DiSimplex(subDimension, 0);

  return sides[sideNum];
}

inline bool DiSimplex::shallowEquals(DiStructure *aLabel,
                                     DiSimplex::List &someSimplicies) {
  if (numSides != someSimplicies.getNumItems()) return false;

  if (label != aLabel) return false;

  VarArrayIterator<DiSimplex*> iter = someSimplicies.getIterator();
  for ( size_t i = 0 ; iter.hasMoreItems() ; i++ ) {
    if (sides[i] != iter.nextItem()) return false;
  }

  return true;
}

inline bool DiSimplex::shallowEquals(DiSimplex *other) {
  if (this == other) return true;

  if (numSides != other->numSides) return false;

  if (label != other->label) return false;

  for ( size_t i = 0 ; i < numSides ; i++ ) {
    if (sides[i] != other->sides[i]) return false;
  }

  return true;
}

//inline bool DiSimplexImpl::initializeFinalSimplexDim(dim_t aDimension) {
//  // create the *final* diSimplex of dimension aDimension
//  label = DiSITT::getUniverse().getFinalStructure().ref;
//  for (dim_t i = 0 ; i <= aDimension ; i++) {
//    simplicies[i] = 0;
//  }
//  return true;
//}

inline DiSimplex::DiSimplex(DiStructure *aLabel,
                            DiSimplex::List &someSimplicies) {
  initializeSimplex(aLabel, someSimplicies);
}

inline bool DiSimplex::initializeSimplex(DiStructure *aLabel,
                                         DiSimplex::List &someSimplicies) {
  numSides = someSimplicies.getNumItems();
  dim_t dimension = numSides - 1;
  label = aLabel;
  dim_t subDimension = -1;
  if (-1 < dimension) subDimension = dimension - 1;
  size_t i = 0;
  for ( VarArrayIterator<DiSimplex*> iter = someSimplicies.getIterator() ;
        iter.hasMoreItems() ; i++ ) {
    DiSimplex *sideSimplex = iter.nextItem();
//    ASSERT_MESSAGE((sideSimplex.dimension == subDimension),
//      "Incorrect dimension of side");
    sides[i] = sideSimplex;
  }
  return true;
}

#endif
