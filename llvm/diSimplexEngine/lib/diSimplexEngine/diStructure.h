#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

#include <stdint.h>
#include <cUtils/bitSet.h>

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiStructureImpl;

class DiStructure {
public:

  bool isEmpty();

  bool contains(DiSimplex aSimplex);

  size_t sizeDim(size_t aDimension);

protected:

  DiStructure(DiStructureImpl *aDiStructure);

  DiStructureImpl *ref;

  friend class DiSITT;
  friend class DiSITTimpl;

};

class DiStructureImpl {

protected: // methods

  bool initializeStructure(bool final = false);

protected: // objects

  bool extendByFinalSimplicies;

  VarArray<BitSet> diSimplicies;

  friend class DiStructure;
  friend class DiSITTimpl;

};

#endif
