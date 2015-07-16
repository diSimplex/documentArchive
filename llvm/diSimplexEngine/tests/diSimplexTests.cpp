#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

describe(DiSimplex) {

  specSize(DiSimplex);

  it("There should be final simplicies of each dimension") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiSimplex lowerFinalSimplex = universe.getFinalSimplexDim(0);
    shouldBeTrue(lowerFinalSimplex.isFinal());
    shouldBeZero(lowerFinalSimplex.dimension);
    shouldBeZero(lowerFinalSimplex.id);
    shouldBeTrue(lowerFinalSimplex.getLabel().isEmpty());
    for (size_t i = 0; i < 100; i++) {
      DiSimplex simplex = universe.getFinalSimplexDim(i);
      shouldBeTrue(simplex.isFinal());
      shouldBeEqual(simplex.dimension, i);
      shouldBeTrue(simplex.getLabel().isEmpty());
      DiSimplex prevSide = simplex.getSide(0);
      shouldBeEqual(prevSide.dimension, lowerFinalSimplex.dimension);
      shouldBeEqual(prevSide.id,        lowerFinalSimplex.id);
      size_t subDimension = 0;
      if (0 < simplex.dimension) subDimension = simplex.dimension - 1;
      for (size_t j = 1; j <= i; j++) {
        DiSimplex side = simplex.getSide(j);
        shouldBeEqual(subDimension, prevSide.dimension);
        shouldBeEqual(simplex.id,   prevSide.id);
        prevSide = side;
      }
      lowerFinalSimplex = simplex;
    }
  } endIt();

} endDescribe(DiSimplex);
