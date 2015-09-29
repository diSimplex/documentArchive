#ifndef DISITT_H
#define DISITT_H

#include <stdint.h>

// start by including any required cUtils
#include <cUtils/varArray.h>

#ifdef __x86_64__
// size_t is 8 bytes
typedef int64_t dim_t;
#else
// size_t is 4 bytes
typedef int32_t dim_t;
#endif
typedef size_t side_t;
typedef size_t simpId_t;
typedef size_t strucId_t;

// Now forward declare the engine's implementation class
// so it can be used as a pointer
class DiSimplex;
class DiStructure;
class DiStructureImpl;

// Now include all of the engine sub-components
#include "diSimplexEngine/diSimplex.h"
#include "diSimplexEngine/diStructure.h"
#include "diSimplexEngine/diSimplexAllocator.h"
#include "diSimplexEngine/diStructureAllocator.h"

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

//  DiSimplex   getSimplex(DiStructure label, DiSimplexList &someSimplicies);

protected: // methods

  DiSimplex getFinalSimplexDim(dim_t aDimension);

protected: // objects

  DiSITTimpl *ref;

};

class DiSITTimpl {

public: // methods

  /// \brief Get the unique mathematical universe.
  static DiSITTimpl *getUniverse(void);

protected: // methods

  /// \brief Clean up the unique mathematical universe.
  ///
  /// This can only be called once, and should only be called at the
  /// end of a given invocation of a diSimplexEngine.
  static void cleanUpUniverse(void);

  DiSITTimpl(void);

  ~DiSITTimpl(void);

  bool ensureFinalSimplexOfDimExists(dim_t aDimension);

  DiStructureImpl *getInitialStructure(void);

  DiStructureImpl *getFinalStructure(void);

  DiSimplexImpl *getSimplex(DiSimplex aSimplex);

  DiSimplexImpl *createSimplex(DiStructure label,
                               DiSimplexList &someSimplicies);

  DiSimplexImplTuple getNewSimplex(dim_t dimension);

  DiStructureImpl *getNewStructure(void);

protected: // objects

  /// \brief The collection of non-empty simplicies of each dimension.
  VarArray<DiSimplexAllocator*> diSimplicies;

  DiStructureAllocator *diStructures;

  /// \brief *The* unique mathematical universe.
  static DiSITTimpl *theUniverse;

  friend class DiSITT;
  friend class DiSimplex;
  friend class DiStructure;
  friend class DiStructureImpl;
};

// Now include the inlines
#include <diSimplexEngine/diSittInlines.h>
#include <diSimplexEngine/diSimplexInlines.h>
#include <diSimplexEngine/diStructureInlines.h>
#include <diSimplexEngine/diSimplexAllocatorInlines.h>
#include <diSimplexEngine/diStructureAllocatorInlines.h>

#endif
