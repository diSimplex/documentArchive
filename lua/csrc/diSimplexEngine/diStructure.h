#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

#include "dynArray.h"
#include "diSiTT.h"
#include "diSimplex.h"

#define diStructureRef_init(structureRef, diSiTTPtr, structureId)	\
  if (structureRef) {							\
    (structureRef)->diSiTT = (diSiTTPtr);				\
    (structureRef)->structure = (structureId);				\
  }

//
// Return true if this diStructure still exists
// @param diStructure :: DiStructureRef*; a reference to a possible diStructure.
// @return bool; true if this diStructure exists; false otherwise
extern bool diStructure_exists(DiStructureRef *structure);

//
// Get the next available empty diStructure. A partial reference
// to the new diStructure is passed in (diSiTT), and
// the required structure field is assigned on sucessful return.
// @function diStructure_get_empty
// @param structure :: DiStructureRef*; an partial empty diStructure.
// @return bool; true if empty structure assigned; false otherwise.
extern bool diStructure_get_empty(DiStructureRef *newStructure);

//
// Release the given diStructure back to the pool of available empty
// diStructures.
// @function diStructure_release
// @param structure :: DiStructureRef*; the diStructure to be released.
// @return bool; true if the diStructure has been sucessfully released; false otherwise.
extern bool diStructure_release(DiStructureRef *structure);

//
// Return the number of simplicies of a given dimension in this structure
// @param diStructure this structure
// @param dimension the dimension to check
// @return[1] number of simplicies
extern size_t diStructure_size(DiStructureRef *diStructure, dimension_t dimension);

//
// Add an additional diSimplex to this structure
// @param diStructure this structure
// @param diSimplex the diSimplex to add
// @return[1] true if diSimplex was added; false otherwise
extern bool diStructure_add(DiStructureRef *diStructure, DiSimplexRef *diSimplex);

//
// Return the requested diSimplex
// @function diStructure_get_simplex_number
// @param diStructure :: DiStructureRef*; this structure.
// @param dimension :: dimension_t; the required diSimplex dimension.
// @param itemNumber :: size_t; the required diSimplex in the diStructure's or$
// @param simplex :: DiSimplexRef*; an empty diSimplexRef which will be filled in with a valid diSimplex which is the requested simplex.
// @return bool; true if the requested diSimplex has been found; false otherwise.
extern bool diStructure_get_simplex_number(DiStructureRef *diStructure,
                                           dimension_t dimension,
                                           size_t itemNumber,
                                           DiSimplexRef *simplex );

#endif
