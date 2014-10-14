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
extern int diStructure_exists(DiStructureObj *diStructure);

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
