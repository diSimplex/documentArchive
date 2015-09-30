#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

#include <cUtils/bitSet.h>

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiStructure {
public:

  bool isEmpty(void);

  bool isFinal(void);

protected: // methods

  bool initializeStructure(bool final = false);

protected: // objects

  bool isFinalStructure;

  VarArray<BlockAllocator*> diSimplicies;

  friend class DiSITT;
};

#endif
