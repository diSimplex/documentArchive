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

  it("should create an empty DiSITT universe") {
    DiSITT *diSitt = new DiSITT();
    shouldNotBeNULL(diSitt);
    shouldNotBeNULL(diSitt->diStructures);
    shouldNotBeNULL(diSitt->initialStruct);
    shouldNotBeNULL(diSitt->finalStruct);
    delete diSitt;
  } endIt();

  it("There should only be ONE DiSITT universe") {
    DiSITT *universe0 = DiSITT::getUniverse();
    shouldNotBeNULL(universe0);
    DiSITT *universe1 = DiSITT::getUniverse();
    shouldNotBeNULL(universe1);
    shouldBeEqual(universe0, universe1);
  } endIt();

  it("should ensure the initial structure is empty") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    shouldBeTrue(initial->isEmpty());
  } endIt();

  it("There should be exactly ONE initial structure") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial0 = universe->getInitialStructure();
    shouldNotBeNULL(initial0);
    DiStructure *initial1 = universe->getInitialStructure();
    shouldNotBeNULL(initial1);
    shouldBeEqual(initial0, initial1);
  } endIt();

//  it("should ensure final simplicies of various dimensions exist") {
//    DiSITT *diSitt = new DiSITT();
//    shouldNotBeNULL(diSitt);
//    shouldBeZero(diSitt->diSimplicies.getNumItems());
//    //
//    shouldBeTrue(diSitt->ensureFinalSimplexOfDimExists(0));
//    shouldBeEqual(diSitt->diSimplicies.getNumItems(), 2);
//    DiSimplexAllocator *allocator = diSitt->diSimplicies.getTop();
//    shouldNotBeNULL(allocator);
//    shouldBeTrue(allocator->invariant());
//    shouldBeEqual(allocator->nextIndex(), 1);
//    //
//    shouldBeTrue(diSitt->ensureFinalSimplexOfDimExists(10));
//    shouldBeEqual(diSitt->diSimplicies.getNumItems(), 12);
//    for (size_t i = 0; i < diSitt->diSimplicies.getNumItems(); i++) {
//      DiSimplexAllocator *allocator = diSitt->diSimplicies.getItem(i, NULL);
//      shouldNotBeNULL(allocator);
//      shouldBeTrue(allocator->invariant());
//      shouldBeEqual(allocator->nextIndex(), 1);
//    }
//    //
//    shouldBeTrue(diSitt->ensureFinalSimplexOfDimExists(100));
//    shouldBeEqual(diSitt->diSimplicies.getNumItems(), 102);
//    for (size_t i = 0; i < diSitt->diSimplicies.getNumItems(); i++) {
//      DiSimplexAllocator *allocator = diSitt->diSimplicies.getItem(i, NULL);
//      shouldNotBeNULL(allocator);
//      shouldBeTrue(allocator->invariant());
//      shouldBeEqual(allocator->nextIndex(), 1);
//    }
//    delete diSitt;
//  } endIt();

  it("There should be exactly ONE terminal structure") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *final0 = universe->getFinalStructure();
    shouldNotBeNULL(final0);
    DiStructure *final1 = universe->getFinalStructure();
    shouldNotBeNULL(final1);
    shouldBeEqual(final0, final1);
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

} endDescribe(DiSITT);

