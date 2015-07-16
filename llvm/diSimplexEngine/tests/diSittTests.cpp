#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

describe(DiSITT) {

  specSize(DiSITT);

  it("There should only be ONE DiSITT universe") {
    DiSITT universe0 = DiSITT::getUniverse();
    shouldNotBeNULL(universe0.ref);
    DiSITT universe1 = DiSITT::getUniverse();
    shouldNotBeNULL(universe1.ref);
    shouldBeEqual(universe0.ref, universe1.ref);
  } endIt();

  it("There should be an initial structure") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    shouldBeTrue(initial.isEmpty());
    for (size_t i = 0 ; i < 100 ; i++ ) shouldBeZero(initial.sizeDim(i));
  } endIt();

  it("There should be a terminal structure") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure final = universe.getFinalStructure();
    shouldNotBeNULL(final.ref);
    for (size_t i = 0; i < 100; i++) {
      shouldBeEqual(final.sizeDim(i), 1);
      DiSimplex simplex = universe.getFinalSimplexDim(i);
      shouldBeTrue(simplex.isFinal());
      shouldBeTrue(final.contains(simplex));
    }
  } endIt();

} endDescribe(DiSITT);
