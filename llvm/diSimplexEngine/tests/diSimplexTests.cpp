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

//  it("There should be final simplicies of each dimension") {
//    DiSITT *universe = DiSITT::getUniverse();
//    shouldNotBeNULL(universe);
//    for (dim_t i = -1; i < 100; i++) {
//      DiSimplex simplex = universe->getFinalSimplexDim(i);
//      shouldBeTrue(simplex.isFinal());
//      shouldBeEqual(simplex.dimension, i);
//      shouldBeZero(simplex.id);
//      shouldBeTrue(simplex.getLabel().isEmpty());
//      dim_t subDimension = -1;
//      if (-1 < simplex.dimension) subDimension = simplex.dimension - 1;
//      DiSimplex lowerFinalSimplex = universe.getFinalSimplexDim(subDimension);
//      for (dim_t j = 0; j <= i; j++) {
//        DiSimplex side = simplex.getSide(j);
//        shouldBeEqual(subDimension, lowerFinalSimplex.dimension);
//        shouldBeEqual(simplex.id,   lowerFinalSimplex.id);
//      }
//    }
//  } endIt();

} endDescribe(DiSimplex);
