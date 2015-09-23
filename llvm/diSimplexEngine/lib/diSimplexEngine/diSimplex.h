#ifndef DISIMPLEX_H
#define DISIMPLEX_H

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiSimplex {

public:

protected: // methods

  DiSimplex(dim_t aDimension, simpId_t anId);

  ~DiSimplex(void);

  bool isFinal(void);

  DiStructure getLabel(void);

  DiSimplex getSide(side_t sideNum);

protected: // objects

  dim_t dimension;

  simpId_t id;

  friend class DiSITT;
  friend class DiSITTimpl;
  friend class DiSimplexImpl;
  friend class DiStructure;
};

typedef VarArray<DiSimplex> DiSimplexList;

class DiSimplexImpl {
public:

protected: // methods

  bool initializeFinalSimplexDim(dim_t dimension);

  bool initializeSimplex(DiStructure aLabel, DiSimplexList &someSimplicies);

  simpId_t getSide(dim_t dimension, side_t sideNum);

  DiStructureImpl *getLabel(void);

protected: // objects

  DiStructureImpl *label;

  simpId_t simplicies[0];

  friend class DiSimplexAllocator;
  friend class DiSITTimpl;

};


#endif
