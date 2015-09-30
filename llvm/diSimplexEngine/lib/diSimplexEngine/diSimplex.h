#ifndef DISIMPLEX_H
#define DISIMPLEX_H

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiSimplex {

public:

typedef VarArray<DiSimplex*> List;

protected: // methods

  DiStructure *getLabel(void);

  DiSimplex *getSide(side_t sideNum);

//  bool initializeFinalSimplexDim(dim_t dimension);

  DiSimplex(DiStructure *aLabel, List &someSimplicies);

  ~DiSimplex(void);

  bool initializeSimplex(DiStructure *aLabel, List &someSimplicies);

protected: // objects

  DiStructure *label;

  DiSimplex *sides[0];

  friend class DiSimplexAllocator;
  friend class DiSimplex;
  friend class DiSITTimpl;

};

#endif
