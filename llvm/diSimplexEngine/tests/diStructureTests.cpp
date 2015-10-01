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

  it("should get the initial diStructure object") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    shouldBeTrue(initial->isEmpty());
    shouldBeFalse(initial->isFinal());
    shouldBeTrue(initial->isFrozen());
  } endIt();

  it("should get the final diStructure object") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *final = universe->getFinalStructure();
    shouldNotBeNULL(final);
    shouldBeTrue(final->isFinal());
    shouldBeFalse(final->isEmpty());
    shouldBeTrue(final->isFrozen());
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

  it("should be able to clone a diStructure") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiStructure *clone   = initial->clone();
    shouldNotBeNULL(clone);
    shouldBeFalse(clone->isFinal());
    shouldBeFalse(clone->isFrozen());
  } endIt();

  it("should ensure simplex allocators of various dimensions exist") {
    DiStructure *structure = new DiStructure();
    shouldNotBeNULL(structure);
    shouldBeZero(structure->diSimplicies.getNumItems());
    //
    shouldBeTrue(structure->ensureSimpliciesOfNumSidesExist(0));
    shouldBeEqual(structure->diSimplicies.getNumItems(), 1);
    DiSimplexAllocator *allocator = structure->diSimplicies.getTop();
    shouldNotBeNULL(allocator);
    shouldBeTrue(allocator->invariant());
    //
    shouldBeTrue(structure->ensureSimpliciesOfNumSidesExist(10));
    shouldBeEqual(structure->diSimplicies.getNumItems(), 11);
    for (size_t i = 0; i < structure->diSimplicies.getNumItems(); i++) {
      DiSimplexAllocator *allocator = structure->diSimplicies.getItem(i, NULL);
      shouldNotBeNULL(allocator);
      shouldBeTrue(allocator->invariant());
    }
    //
    shouldBeTrue(structure->ensureSimpliciesOfNumSidesExist(100));
    shouldBeEqual(structure->diSimplicies.getNumItems(), 101);
    for (size_t i = 0; i < structure->diSimplicies.getNumItems(); i++) {
      DiSimplexAllocator *allocator = structure->diSimplicies.getItem(i, NULL);
      shouldNotBeNULL(allocator);
      shouldBeTrue(allocator->invariant());
    }
    delete structure;
  } endIt();

  it("should be able to create a simplex from an empty collection of simplicies") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial   = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiStructure *structure = universe->getNewStructure();
    shouldNotBeNULL(structure);
    DiSimplex::List emptyList;
    shouldBeZero(emptyList.getNumItems());
    DiSimplex *simplex = structure->addSimplex(initial, emptyList);
    shouldNotBeNULL(simplex);
    shouldBeEqual(simplex->dimension(), -1);
    shouldBeEqual(simplex->getLabel(), initial);
  } endIt();

  it("should be able to create a simplex from a collection of a one simplex") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiStructure *structure = universe->getNewStructure();
    shouldNotBeNULL(structure);
    DiSimplex::List emptyList;
    shouldBeZero(emptyList.getNumItems());
    DiSimplex *simplex0 = structure->addSimplex(initial, emptyList);
    shouldNotBeNULL(simplex0);
    DiSimplex::List listOfOne;
    listOfOne.pushItem(simplex0);
    shouldBeEqual(listOfOne.getNumItems(), 1);
    DiSimplex *simplex1 = structure->addSimplex(initial, listOfOne);
    shouldNotBeNULL(simplex1);
    shouldBeEqual(simplex1->dimension(), 0);
    shouldBeEqual(simplex1->getLabel(), initial);
    DiSimplex *simplex0a = simplex1->getSide(0);
    shouldNotBeNULL(simplex0a);
    shouldBeEqual(simplex0a, simplex0);
    shouldBeEqual(simplex0a->dimension(), simplex0->dimension());
  } endIt();

  it("should be able to create a simplex from a collection of two simplicies") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiStructure *structure = universe->getNewStructure();
    shouldNotBeNULL(structure);
    DiSimplex::List emptyList;
    DiSimplex *simplex0 = structure->addSimplex(initial, emptyList);
    shouldNotBeNULL(simplex0);
    DiSimplex::List listOfOne;
    listOfOne.pushItem(simplex0);
    DiSimplex *simplex1a = structure->addSimplex(initial, listOfOne);
    shouldNotBeNULL(simplex1a);
    DiSimplex *simplex1b = structure->addSimplex(structure, listOfOne);
    shouldNotBeNULL(simplex1b);
    DiSimplex::List listOfTwo;
    listOfTwo.pushItem(simplex1a);
    listOfTwo.pushItem(simplex1b);
    shouldBeEqual(listOfTwo.getNumItems(), 2);
    DiSimplex *simplex2 = structure->addSimplex(initial, listOfTwo);
    shouldBeEqual(simplex2->dimension(), 1);
    shouldBeEqual(simplex2->getLabel(), initial);
    DiSimplex *simplex1Aa = simplex2->getSide(0);
    shouldBeEqual(simplex1Aa->dimension(), simplex1a->dimension());
    shouldBeEqual(simplex1Aa, simplex1a);
    DiSimplex *simplex1Ab = simplex2->getSide(1);
    shouldBeEqual(simplex1Ab->dimension(), simplex1b->dimension());
    shouldBeEqual(simplex1Ab, simplex1b);
  } endIt();

} endDescribe(DiStructure);
