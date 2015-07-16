#ifndef DISIMPLEX_H
#define DISIMPLEX_H

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiSimplex {

public:

protected: // methods

  DiSimplex(size_t aDimension, size_t anId);

  ~DiSimplex(void);

  bool isFinal(void);

  DiStructure getLabel(void);

  DiSimplex getSide(size_t sideNum);

protected: // objects

  size_t dimension;

  size_t id;

  friend class DiSITT;
  friend class DiSITTimpl;
  friend class DiSimplexImpl;
};

typedef VarArray<DiSimplex> DiSimplexList;

class DiSimplexImpl {
public:

protected: // methods

  bool initializeFinalSimplexDim(size_t dimension);

  bool initializeSimplex(size_t aLabel, DiSimplexList &someSimplicies);

  size_t getSide(size_t dimension, size_t sideNum);

protected: // objects

  size_t label;

  size_t simplicies[0];

  friend class DiSimplexAllocator;
  friend class DiSITTimpl;

};


#endif
