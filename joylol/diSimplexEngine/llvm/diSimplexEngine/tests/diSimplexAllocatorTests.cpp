#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

describe(DiSimplexAllocator) {

  specSize(DiSimplexAllocator);

  it("should compute the correct itemSize") {
    shouldBeEqual(DiSimplexAllocator::numSides2size(0),
      sizeof(DiSimplex));
    shouldBeEqual(DiSimplexAllocator::numSides2size(1),
      sizeof(DiSimplex) + sizeof(DiSimplex*));
    shouldBeEqual(DiSimplexAllocator::numSides2size(1266),
      sizeof(DiSimplex) + 1266*sizeof(DiSimplex*));
  } endIt();

} endDescribe(DiSimplexAllocator);
