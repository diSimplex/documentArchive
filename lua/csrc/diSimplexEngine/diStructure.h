#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

#include "dynArray.h"
#include "diSiTT.h"


#define diStructureRef_get_structureObj_or_return_false(structureRef, structureObj) \
  DiStructureObj *(structureObj);					\
  if (true) {								\
    if (DynArray_len((structureRef)->diSiTT->structures) <= 		\
          (structureRef)->structure) return false;			\
    (structureObj) =							\
        DynArray_getElementPtr((structureRef)->diSiTT->structures,	\
                               (structureRef)->structure,		\
                                DiStructureObj);			\
  }

#define diStructureRef_get_simplicies_or_return_false(structureObj, dimension, simpliciesArray) \
  DynArray *(simpliciesArray);						\
  if (true) {								\
    if ( (dimension) < -1 ) return false;				\
    if ( (dimension) == -1 ) (dimension) = 0;				\
    if ( DynArray_len((structureObj)->dimensions) <=			\
         (dimension) ) return false;					\
  (simpliciesArray) =							\
    *DynArray_getElementPtr((structureObj)->dimensions,			\
                            (dimension), DynArray*);			\
  }

#define diStructureRef_init(structureRef, diSiTTPtr, structureId)	\
  if (structureRef) {							\
    (structureRef)->diSiTT = (diSiTTPtr);				\
    (structureRef)->structure = (structureId);				\
  }

//
// Determine if myStructure is contained in otherStructure.
// @function diStructure_contained_in
// @param myStructure :: DiStructureRef*;
// @param otherStructure :: DiStructureRef *;
// @return bool; true if myStructure is contained in otherStructure; false oth$
bool diStructure_contained_in(DiStructureRef *myStructure,
                              DiStructureRef *otherStructure);

//
// Return true if this diStructure still exists
// @param diStructure :: DiStructureRef*; a reference to a possible diStructure.
// @return bool; true if this diStructure exists; false otherwise
extern bool diStructure_exists(DiStructureRef *structure);

//
// Get the next available initial (empty) diStructure. A partial reference
// to the new diStructure is passed in (diSiTT), and
// the required structure field is assigned on sucessful return.
// @function diStructure_get_initial
// @param structure :: DiStructureRef*; an partial initial (empty) diStructure.
// @return bool; true if initial (empty) structure assigned; false otherwise.
extern bool diStructure_get_initial(DiStructureRef *initialStructure);

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

//
// Compute the union of two existing diStructures
// @function diStructure_union
// @param structureA :: DiStructureRef*; structure A.
// @param structureB :: DiStructureRef*; structure B.
// @param result :: DiStructureRef*; the resulting union diStructure.
// @return bool; true if union could be computed; false otherwise.
extern bool diStructure_union(DiStructureRef *structureA,
                              DiStructureRef *structureB,
                              DiStructureRef *result);

//
// Compute the merge of two existing diStructures
// @function diStructure_merge_into
// @param structureA :: DiStructureRef*; merged structure.
// @param structureB :: DiStructureRef*; other structure.
// @return bool; true if merge could be computed; false otherwise.
extern bool diStructure_merge_into(DiStructureRef *mergedStructure,
                                   DiStructureRef *otherStructure);

#endif
