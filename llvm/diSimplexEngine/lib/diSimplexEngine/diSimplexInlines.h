#ifndef DISIMPLEX_INLINES_H
#define DISIMPLEX_INLINES_H

#include <stdint.h>
#include <diSimplexEngine/diSimplex.h>

inline DiSimplex::~DiSimplex(void) {
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
  dim_t dimension = someSimplicies.getNumItems() - 1;
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
