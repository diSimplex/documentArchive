#ifndef DISIMPLEX_INLINES_H
#define DISIMPLEX_INLINES_H

#include <stdint.h>
#include <diSimplexEngine/diSimplex.h>

inline DiSimplex::DiSimplex(size_t aDimension, size_t anId) {
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

inline DiSimplex DiSimplex::getSide(size_t sideNum) {
  return DiSITT::getUniverse().getSide(*this, sideNum);
}

inline bool DiSimplexImpl::initializeFinalSimplexDim(size_t aDimension) {
  // create the *final* diSimplex of dimension aDimension
  label = 0;
  for (size_t i = 0 ; i <= aDimension ; i++) {
    simplicies[i] = 0;
  }
  return true;
}

inline bool DiSimplexImpl::initializeSimplex(size_t aLabel,
                                             DiSimplexList &someSimplicies) {
  size_t dimension = someSimplicies.getNumItems();
  label = aLabel;
  size_t subDimension = 0;
  if (0 < dimension) subDimension = dimension - 1;
  DiSimplex nullSimplex(subDimension, 0);
  for (size_t i = 0; i < someSimplicies.getNumItems() ; i++ ) {
    simplicies[i] = someSimplicies.getItem(i, nullSimplex).id;
  }
  return true;
}

inline size_t DiSimplexImpl::getSide(size_t dimension, size_t sideNum) {
  if (dimension < sideNum) return 0;

  return simplicies[sideNum];
}

#endif
