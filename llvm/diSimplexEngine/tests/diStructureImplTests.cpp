#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

pending_describe(DiStructureImpl) {

  specSize(DiStructureImpl);

  it("should be able to clone the initial diStructure object") {
    DiSITTimpl *universe = DiSITTimpl::getUniverse();
    shouldNotBeNULL(universe);
    DiStructureImpl *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    shouldBeZero(initial->diSimplicies.getNumItems());
    DiStructureImpl *clone = initial->clone();
    shouldNotBeNULL(clone);
    shouldBeZero(clone->diSimplicies.getNumItems());
  } endIt();

} endDescribe(DiStructureImpl);
