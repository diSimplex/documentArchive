#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

pending_describe(DiStructure) {

  specSize(DiStructure);

  it("should get the initial diStructure object") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    shouldBeTrue(initial.isEmpty());
    for (size_t i = 0 ; i < 100 ; i++ ) shouldBeZero(initial.sizeDim(i));
  } endIt();

  it("should get the final diStructure object") {
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

  it("initial and final diStructure objects should be different") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    DiStructure final = universe.getFinalStructure();
    shouldNotBeNULL(final.ref);
    shouldNotBeEqual(initial.ref, final.ref);
  } endIt();

  it("should be able to clone a diStructure object") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    DiStructure clone = initial.clone();
    shouldNotBeNULL(clone.ref);
    shouldNotBeEqual(initial.ref, clone.ref);
  } endIt();

} endDescribe(DiStructure);
