#ifndef DISIMPLEX_INLINES_H
#define DISIMPLEX_INLINES_H

#include <stdint.h>
#include <diSimplexEngine/diSimplex.h>

inline DiSimplex::DiSimplex(dim_t aDimension, simpId_t anId) {
  dimension = aDimension;
  id        = anId;
}

inline DiSimplex::~DiSimplex(void) {
  dimension = 0;
  id        = 0;
}

inline bool DiSimplex::isFinal(void) {
  return id == 0 ? true : false;
}

inline DiStructure DiSimplex::getLabel(void) {
  return DiSITT::getUniverse().getLabel(*this);
}

inline DiSimplex DiSimplex::getSide(side_t sideNum) {
  return DiSITT::getUniverse().getSide(*this, sideNum);
}

inline bool DiSimplexImpl::initializeFinalSimplexDim(dim_t aDimension) {
  // create the *final* diSimplex of dimension aDimension
  label = 0;
  for (dim_t i = 0 ; i <= aDimension ; i++) {
    simplicies[i] = 0;
  }
  return true;
}

inline bool DiSimplexImpl::initializeSimplex(DiStructure aLabel,
                                             DiSimplexList &someSimplicies) {
  dim_t dimension = someSimplicies.getNumItems() - 1;
  label = aLabel.ref;
  dim_t subDimension = -1;
  if (-1 < dimension) subDimension = dimension - 1;
  DiSimplex nullSimplex(subDimension, 0);
  for (size_t i = 0; i < someSimplicies.getNumItems() ; i++ ) {
    DiSimplex sideSimplex = someSimplicies.getItem(i, nullSimplex);
    ASSERT_MESSAGE((sideSimplex.dimension == subDimension),
      "Incorrect dimension of side");
    simplicies[i] = sideSimplex.id;
  }
  return true;
}

inline simpId_t DiSimplexImpl::getSide(dim_t dimension, side_t sideNum) {
  if (dimension < sideNum) return 0;

  return simplicies[sideNum];
}

inline DiStructureImpl *DiSimplexImpl::getLabel(void) {

  return label;
}

#endif
