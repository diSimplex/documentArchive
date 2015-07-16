#ifndef DISITT_H
#define DISITT_H

// start by including any required cUtils
#include <cUtils/varArray.h>

// Now forward declare the engine's implementation class
// so it can be used as a pointer
class DiSimplex;
class DiStructure;

// Now include all of the engine sub-components
#include "diSimplexEngine/diSimplex.h"
#include "diSimplexEngine/diStructure.h"
#include "diSimplexEngine/diSimplexAllocator.h"

class DiSITTimpl;

/// \brief The DiSITT represents a *reference* to the whole
/// Mathematical universe. All mathematical structures exist in the
/// same universe.
///
class DiSITT {
public:

  /// \brief Get the unique mathematical universe.
  static DiSITT getUniverse(void);

  /// \brief Clean up the unique mathematical universe.
  ///
  /// This can only be called once, and should only be called at the
  /// end of a given invocation of a diSimplexEngine.
  static void cleanUpUniverse(void);

  /// \brief Create a new mathematical universe.
  DiSITT(DiSITTimpl *aUniverse);

  /// \brief Destroy a mathematical universe.
  ~DiSITT(void);

  DiStructure getInitialStructure(void);

  DiStructure getFinalStructure(void);

  DiSimplex getFinalSimplexDim(size_t aDimension);

  DiStructure getLabel(DiSimplex aSimplex);

  DiSimplex   getSide(DiSimplex aSimplex, size_t sideNum);

protected: // methods

protected: // objects

  /// \brief *The* unique mathematical universe.
  static DiSITTimpl *theUniverse;

  DiSITTimpl *ref;

};

class DiSITTimpl {
protected: // methods

  DiSITTimpl(void);

  ~DiSITTimpl(void);

  bool ensureFinalSimplexOfDimExists(size_t aDimension);

  DiStructure getLabel(DiSimplex aSimplex);

  DiSimplex   getSide(DiSimplex aSimplex, size_t sideNum);

protected: // objects

  /// \brief The collection of non-empty simplicies of each dimension.
  VarArray<DiSimplexAllocator*> diSimplicies;

  DiStructure *diStructures;

  friend class DiSITT;
};

// Now include the inlines
#include <diSimplexEngine/diSittInlines.h>
#include <diSimplexEngine/diSimplexInlines.h>
#include <diSimplexEngine/diStructureInlines.h>
#include <diSimplexEngine/diSimplexAllocatorInlines.h>

#endif
