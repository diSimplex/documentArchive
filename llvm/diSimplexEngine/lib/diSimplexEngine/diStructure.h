#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

#include <cUtils/bitSet.h>

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiStructureImpl;

class DiStructure {
public:

  bool isEmpty(void);

  bool isFinal(void);

  bool contains(DiSimplex aSimplex);

  size_t sizeDim(dim_t aDimension);

  DiStructure clone(void);

protected:

  DiStructure(DiStructureImpl *aDiStructure);

  DiStructureImpl *ref;

  friend class DiSITT;
  friend class DiSITTimpl;
  friend class DiSimplex;
  friend class DiSimplexImpl;
};

class DiStructureImpl {

protected: // methods

  bool initializeStructure(bool final = false);

  DiStructureImpl *clone(void);

//  ToDO();

protected: // objects

  bool isFinalStructure;

  VarArray<BitSet> diSimplicies;

  friend class DiStructure;
  friend class DiSITTimpl;
};

#endif
