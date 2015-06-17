#include <stdio.h>
#include "diSiTT.h"
#include "diStructure.h"
#include "diSimplex.h"

/***

The diSimplexEngine's DiSiTT component.

All of the code in this component is pure C helper code.

A DiSiTT structure provides an encapsulated environment in which
directed simplicial structures can exist. Note that a given Lua script
can interact with multiple DiSiTT structures, each of which will be
totally separate from each other.

@module diSimplexEngine.diSiTT
*/

///
// Initialize a DiSiTT instance.
// @function diSiTT_init
// @param disitt :: DiSiTT*; the diSiTT structure to be initialized.
void diSiTT_init(DiSiTT *disitt) {
  disitt->emptySimplicies = DynArray_new(sizeof(simplex_id), 0);
  disitt->simplicies      = DynArray_new(sizeof(DynArray*),  0);
  disitt->emptyStructures = DynArray_new(sizeof(structure_id), 0);
  disitt->structures      = DynArray_new(sizeof(DiStructureObj), 0);
  //
  // create the empty structure at structure_id 0...
  // this will be used/assumed to exist almost everywhere...
  //
  DiStructureRef initialStructure;
  diStructureRef_init(&initialStructure, disitt, 0);
  diStructure_get_initial(&initialStructure);
}

///
// Ensure that a given dimension (and all smaller dimensions)
// have been added to this DiSiTT's collection of simplicies.
// @function diSiTT_ensure_dimension
// @param disitt :: DiSiTT*; the diSiTT.
// @param newDimension :: dimension_t; the dimension which must exists or be added.
void diSiTT_ensure_dimension(DiSiTT *disitt,
                                dimension_t newDimension) {
  if (newDimension < 0) newDimension = 0;

  dimension_t numDimensions = DynArray_len(disitt->simplicies);

  // check to see if we already have added this dimension
  if ( newDimension < numDimensions ) {
    return;  // nothing to do...
  }

  // check to see if we need to add lower dimensions
  if ( numDimensions < newDimension ) {
    diSiTT_ensure_dimension(disitt, newDimension - 1);
  }

  // now add this dimension
  //
  // now provision the dynArray for the new dimension
  //
  DynArray *newDimensionArray = DynArray_new(DiSimplexObjSize(newDimension), 0);
  //
  // a terminal simplex for a given dimension has all sides zero which hence
  // points to the terminal simplex for the next lower dimension.
  // So adding a zero element (and doing nothing else) ensures that
  // the element is a terminal simplex. BUT we must assert that the terminal
  // simplex is DISITT_DISIMPLEX_INUSE.
  //
  DynArray_addZeroedElement(newDimensionArray);
  DiSimplexObj *terminalSimplex =
    DynArray_getElementPtr(newDimensionArray, 0, DiSimplexObj);
  terminalSimplex->flags |= DISITT_DISIMPLEX_INUSE;
  //
  // now place this new DynArray onto the end of the simplicies array
  //
  DynArray_addElement(disitt->simplicies, DynArray*, newDimensionArray);
  //
  // now initalize the empty simplex linked list to the null simplex
  //
  DynArray_addZeroedElement(disitt->emptySimplicies);
}

///
// Collect all unused diSimplicies and diStructures.
// @function diSiTT_collect_garbage
// @param disitt :: DiSiTT*; the diSiTT.
void diSiTT_collect_garbage(DiSiTT *disitt) {
  // do nothing at the moment.... however eventually....

  // clear all diSimplex and diStructure GC_MARKS

  // walk all diStructures which are "INUSE" marking all unmarked diSimplicies

  // walk all diSimplicies and release any which are "INUSE" but not GC_MARKed

  // walk all diStructures and release any which are "INUSE" but not GC_MARKed

  // clear all diSimplex and diStructure GC_MARKS
}

