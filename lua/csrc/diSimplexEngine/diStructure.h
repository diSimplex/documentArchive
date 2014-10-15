#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

#include "dynArray.h"
#include "diSiTT.h"
#include "diSimplex.h"



//
// Initialize a new diStructure object
// @param diStructure the uninitialized diStructure
// @param diSiTT the diSiTT environment in which this diStructure should exist
// return[0] void
extern void diStructure_init(DiStructureObj *diStructure,
                             DiSiTT         *diSiTT);
//
// Return true if this diStructure still exists
// @param diStructure this structure
// @return[1] true if this diStructure exists; false otherwise
extern bool diStructure_exists(DiStructureRef *structure);

// Get the next available empty diStructure
extern structure_id diStructure_get_empty(DiSiTT *disitt);

// Release the given diStructure back to the pool of available empty
// diStructures.
extern void diStructure_release(DiSiTT *disitt,
                                     structure_id structureId);

//
// Empty an existing diStructure
// @function diStructure_empty
// @param disitt :: DiSiTT*; the diSiTT.
// @param structureId :: structure_id; the ID of the diStructure to empty.
extern void diStructure_empty(DiSiTT *disitt, structure_id structureId);

//
// Return the number of simplicies of a given dimension in this structure
// @param diStructure this structure
// @param dimension the dimension to check
// @return[1] number of simplicies
extern int diStructure_size(DiStructureObj *diStructure, dimension_t dimension);

//
// Add an additional diSimplex to this structure
// @param diStructure this structure
// @param diSimplex the diSimplex to add
// @return[1] true if diSimplex was added; false otherwise
extern int diStructure_add(DiStructureObj *diStructure, DiSimplexRef *diSimplex);

#endif
