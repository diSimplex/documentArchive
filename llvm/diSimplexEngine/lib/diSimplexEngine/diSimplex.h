#ifndef DISIMPLEX_H
#define DISIMPLEX_H

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiSimplex {

public:

  typedef VarArray<DiSimplex*> List;

  dim_t dimension(void);

  DiStructure *getLabel(void);

  DiSimplex *getSide(side_t sideNum);

  bool shallowEquals(DiSimplex *other);

//  bool deepEquals(DiSimplex *other);

protected: // methods

//  bool initializeFinalSimplexDim(dim_t dimension);

  DiSimplex(DiStructure *aLabel, List &someSimplicies);

  ~DiSimplex(void);

  bool initializeSimplex(DiStructure *aLabel, List &someSimplicies);

protected: // objects

  size_t numSides;

  DiStructure *label;

  DiSimplex *sides[0];

  friend class DiSimplexAllocator;
  friend class DiStructure;

};

#endif
