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

  it("should create a simplex") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiSimplex::List emptyList;
    DiSimplex *simplex = new DiSimplex(initial, emptyList);
    shouldNotBeNULL(simplex);
    delete simplex;
  } endIt();

  it("shallowEquals other should fail except when pointers equal") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiStructure *clone = initial->clone();
    shouldNotBeNULL(clone);
    DiSimplex::List emptyList;
    DiSimplex *simplex0 = clone->addSimplex(initial, emptyList);
    shouldNotBeNULL(simplex0);
    DiSimplex::List listOfOne;
    listOfOne.pushItem(simplex0);
    DiSimplex *simplex1 = clone->addSimplex(initial, listOfOne);
    shouldNotBeNULL(simplex1);
    shouldNotBeEqual(simplex0, simplex1);
    // unequal dimensions
    shouldBeFalse(simplex0->shallowEquals(simplex1));
    shouldBeFalse(simplex1->shallowEquals(simplex0));
    // unequal labels
    DiStructure *final = universe->getFinalStructure();
    shouldNotBeNULL(final);
    shouldNotBeEqual(initial, final);
    DiSimplex *simplex0a = clone->addSimplex(final, emptyList);
    shouldNotBeNULL(simplex0a);
    shouldNotBeEqual(simplex0, simplex0a);
    shouldBeFalse(simplex0->shallowEquals(simplex0a));
    shouldBeFalse(simplex0a->shallowEquals(simplex0));
    // unequal sides
    DiSimplex::List listOfOneA;
    listOfOneA.pushItem(simplex0a);
    DiSimplex *simplex1a = clone->addSimplex(initial, listOfOneA);
    shouldNotBeNULL(simplex1a);
    shouldNotBeEqual(simplex1, simplex1a);
    shouldBeFalse(simplex1->shallowEquals(simplex1a));
    shouldBeFalse(simplex1a->shallowEquals(simplex1));
    // identical equals
    shouldBeTrue(simplex0->shallowEquals(simplex0));
  } endIt();

  it("shallowEquals parts specifications") {
    DiSITT *universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure *initial = universe->getInitialStructure();
    shouldNotBeNULL(initial);
    DiStructure *clone = initial->clone();
    shouldNotBeNULL(clone);
    DiSimplex::List emptyList;
    DiSimplex *simplex0 = clone->addSimplex(initial, emptyList);
    shouldNotBeNULL(simplex0);
    DiSimplex::List listOfOne;
    listOfOne.pushItem(simplex0);
    DiSimplex *simplex1 = clone->addSimplex(initial, listOfOne);
    shouldNotBeNULL(simplex1);
    shouldNotBeEqual(simplex0, simplex1);
    // equal parts
    shouldBeTrue(simplex0->shallowEquals(initial, emptyList));
    shouldBeTrue(simplex1->shallowEquals(initial, listOfOne));
    // unequal dimensions
    shouldBeFalse(simplex0->shallowEquals(initial, listOfOne));
    shouldBeFalse(simplex1->shallowEquals(initial, emptyList));
    // unequal labels
    shouldBeFalse(simplex0->shallowEquals(clone, emptyList));
    shouldBeFalse(simplex1->shallowEquals(clone, listOfOne));
    // unequal lists (of correct dimension)
    DiSimplex::List listOfOneA;
    listOfOneA.pushItem(simplex1);
    shouldBeFalse(simplex1->shallowEquals(initial, listOfOneA));
  } endIt();

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
