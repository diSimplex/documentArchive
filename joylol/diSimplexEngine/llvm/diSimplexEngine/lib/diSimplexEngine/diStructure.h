#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

#include <cUtils/bitSet.h>

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiStructure {
public:

  static const size_t FINAL  = 1<<0;
  static const size_t FROZEN = 1<<1;

//  bool shallowEquals(DiStructure *other);

//  bool deepEquals(DiStructure *other);

  bool isEmpty(void);

  bool isFinal(void);

  void freeze(void);

  bool isFrozen(void);

  DiStructure *clone(void);

  DiSimplex *addSimplex(DiStructure *aLabel, DiSimplex::List &someSimplicies);

protected: // methods

  DiStructure(void);

  ~DiStructure(void);

  bool initializeStructure(size_t flags = 0);

  bool ensureSimpliciesOfNumSidesExist(size_t numSides);

protected: // objects

  size_t flags;

  VarArray<DiSimplexAllocator*> diSimplicies;

  friend class DiSITT;
};

#endif
