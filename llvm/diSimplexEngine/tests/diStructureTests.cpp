#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

describe(DiStructure) {

  specSize(DiStructure);

  it("should get the initial diStructure object") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    shouldBeTrue(initial->isEmpty());
  } endIt();

  it("should get the final diStructure object") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *final = universe->getFinalStructure();
    shouldNotBeNULL(final);
  } endIt();

  it("initial and final diStructure objects should be different") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiStructure *final = universe->getFinalStructure();
    shouldNotBeNULL(final);
    shouldNotBeEqual(initial, final);
  } endIt();

} endDescribe(DiStructure);
