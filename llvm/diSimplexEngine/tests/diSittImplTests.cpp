#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

describe(DiSITTimpl) {

  specSize(DiSITTimpl);

  it("should create initial empty object") {
    DiSITTimpl *diSitt = new DiSITTimpl();
    shouldNotBeNULL(diSitt);
    shouldBeZero(diSitt->diSimplicies.getNumItems());
    // check diStructures
    delete diSitt;
  } endIt();

  it("should ensure final simplicies of various dimensions exist") {
    DiSITTimpl *diSitt = new DiSITTimpl();
    shouldNotBeNULL(diSitt);
    shouldBeZero(diSitt->diSimplicies.getNumItems());
    //
    shouldBeTrue(diSitt->ensureFinalSimplexOfDimExists(0));
    shouldBeEqual(diSitt->diSimplicies.getNumItems(), 2);
    DiSimplexAllocator *allocator = diSitt->diSimplicies.getTop();
    shouldNotBeNULL(allocator);
    shouldBeTrue(allocator->invariant());
    shouldBeEqual(allocator->nextIndex(), 1);
    //
    shouldBeTrue(diSitt->ensureFinalSimplexOfDimExists(10));
    shouldBeEqual(diSitt->diSimplicies.getNumItems(), 12);
    for (size_t i = 0; i < diSitt->diSimplicies.getNumItems(); i++) {
      DiSimplexAllocator *allocator = diSitt->diSimplicies.getItem(i, NULL);
      shouldNotBeNULL(allocator);
      shouldBeTrue(allocator->invariant());
      shouldBeEqual(allocator->nextIndex(), 1);
    }
    //
    shouldBeTrue(diSitt->ensureFinalSimplexOfDimExists(100));
    shouldBeEqual(diSitt->diSimplicies.getNumItems(), 102);
    for (size_t i = 0; i < diSitt->diSimplicies.getNumItems(); i++) {
      DiSimplexAllocator *allocator = diSitt->diSimplicies.getItem(i, NULL);
      shouldNotBeNULL(allocator);
      shouldBeTrue(allocator->invariant());
      shouldBeEqual(allocator->nextIndex(), 1);
    }
    delete diSitt;
  } endIt();

} endDescribe(DiSITTimpl);
