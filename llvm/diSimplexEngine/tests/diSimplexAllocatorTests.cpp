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
    shouldBeEqual(DiSimplexAllocator::dimension2size(0),
      sizeof(DiSimplexImpl) + sizeof(simpId_t));
    shouldBeEqual(DiSimplexAllocator::dimension2size(1265),
      sizeof(DiSimplexImpl) + 1266*sizeof(simpId_t));
  } endIt();

} endDescribe(DiSimplexAllocator);
