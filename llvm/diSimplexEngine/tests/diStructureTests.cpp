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

  it("should create a diStructure object") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
  } endIt();

} endDescribe(DiStructure);
