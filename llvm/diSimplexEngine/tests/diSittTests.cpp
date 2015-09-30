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

//  it("should be able to create a simplex from an empty collection of simplicies") {
//    DiSITT *universe = DiSITT::getUniverse();
//    shouldNotBeNULL(universe);
//    DiStructure initial(universe->getInitialStructure());
//    shouldNotBeNULL(initial.ref);
//    DiSimplexList emptyList;
//    shouldBeZero(emptyList.getNumItems());
//    DiSimplex simplex0 = universe->createSimplex(initial, emptyList);
//    shouldBeEqual(simplex0.dimension, -1);
//    shouldNotBeZero(simplex0.id);
//    shouldBeEqual(simplex0.getLabel().ref, initial.ref);
//  } endIt();

//  it("should be able to create a simplex from a collection of one simplex") {
//    DiSITTimpl *universe = DiSITTimpl::getUniverse();
//    shouldNotBeNULL(universe);
//    DiStructure initial(universe->getInitialStructure());
//    shouldNotBeNULL(initial.ref);
//    DiSimplexList listOfOne;
//    DiSimplex simplex0 = DiSITT(universe).getFinalSimplexDim(-1);
//    listOfOne.pushItem(simplex0);
//    shouldBeEqual(listOfOne.getNumItems(), 1);
//    DiSimplex simplex1 = universe->createSimplex(initial, listOfOne);
//    shouldBeEqual(simplex1.dimension, 0);
//    shouldNotBeZero(simplex1.id);
//    shouldBeEqual(simplex1.getLabel().ref, initial.ref);
//    DiSimplex simplex0a = simplex1.getSide(0);
//    shouldBeEqual(simplex0a.dimension, simplex0.dimension);
//    shouldBeEqual(simplex0a.id, simplex0.id);
//  } endIt();

//  it("should be able to create a simplex from a collection of two simplicies") {
//    DiSITTimpl *universe = DiSITTimpl::getUniverse();
//    shouldNotBeNULL(universe);
//    DiStructure initial(universe->getInitialStructure());
//    shouldNotBeNULL(initial.ref);
//    DiSimplexList listOfTwo;
//    DiSimplex simplex0 = DiSITT(universe).getFinalSimplexDim(0);
//    DiSimplex simplex1 = DiSITT(universe).getFinalSimplexDim(0);
//    listOfTwo.pushItem(simplex0);
//    listOfTwo.pushItem(simplex1);
//    shouldBeEqual(listOfTwo.getNumItems(), 2);
//    DiSimplex simplex2 = universe->createSimplex(initial, listOfTwo);
//    shouldBeEqual(simplex2.dimension, 1);
//    shouldNotBeZero(simplex2.id);
//    shouldBeEqual(simplex2.getLabel().ref, initial.ref);
//    DiSimplex simplex0a = simplex2.getSide(0);
//    shouldBeEqual(simplex0a.dimension, simplex0.dimension);
//    shouldBeEqual(simplex0a.id, simplex0.id);
//    DiSimplex simplex1a = simplex2.getSide(1);
//    shouldBeEqual(simplex1a.dimension, simplex1.dimension);
//    shouldBeEqual(simplex1a.id, simplex1.id);
//  } endIt();

} endDescribe(DiSITT);

