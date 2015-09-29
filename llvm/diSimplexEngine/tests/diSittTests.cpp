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

  it("There should only be ONE DiSITT universe") {
    DiSITT universe0 = DiSITT::getUniverse();
    shouldNotBeNULL(universe0.ref);
    DiSITT universe1 = DiSITT::getUniverse();
    shouldNotBeNULL(universe1.ref);
    shouldBeEqual(universe0.ref, universe1.ref);
  } endIt();

  it("There should be exactly ONE initial structure") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial0 = universe.getInitialStructure();
    shouldNotBeNULL(initial0.ref);
    DiStructure initial1 = universe.getInitialStructure();
    shouldNotBeNULL(initial1.ref);
    shouldBeEqual(initial0.ref, initial1.ref);
  } endIt();

  it("There should be exactly ONE terminal structure") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure final0 = universe.getFinalStructure();
    shouldNotBeNULL(final0.ref);
    DiStructure final1 = universe.getFinalStructure();
    shouldNotBeNULL(final1.ref);
    shouldBeEqual(final0.ref, final1.ref);
  } endIt();

  it("initial and final diStructure objects should be different") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    DiStructure final = universe.getFinalStructure();
    shouldNotBeNULL(final.ref);
    shouldNotBeEqual(initial.ref, final.ref);
  } endIt();

  it("should be able to create a simplex from an empty collection of simplicies") {
    DiSITTimpl *universe = DiSITTimpl::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure initial(universe->getInitialStructure());
    shouldNotBeNULL(initial.ref);
    DiSimplexList emptyList;
    shouldBeZero(emptyList.getNumItems());
    DiSimplex simplex0 = universe->createSimplex(initial, emptyList);
    shouldBeEqual(simplex0.dimension, -1);
    shouldNotBeZero(simplex0.id);
    shouldBeEqual(simplex0.getLabel().ref, initial.ref);
  } endIt();

  it("should be able to create a simplex from a collection of one simplex") {
    DiSITTimpl *universe = DiSITTimpl::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure initial(universe->getInitialStructure());
    shouldNotBeNULL(initial.ref);
    DiSimplexList listOfOne;
    DiSimplex simplex0 = DiSITT(universe).getFinalSimplexDim(-1);
    listOfOne.pushItem(simplex0);
    shouldBeEqual(listOfOne.getNumItems(), 1);
    DiSimplex simplex1 = universe->createSimplex(initial, listOfOne);
    shouldBeEqual(simplex1.dimension, 0);
    shouldNotBeZero(simplex1.id);
    shouldBeEqual(simplex1.getLabel().ref, initial.ref);
    DiSimplex simplex0a = simplex1.getSide(0);
    shouldBeEqual(simplex0a.dimension, simplex0.dimension);
    shouldBeEqual(simplex0a.id, simplex0.id);
  } endIt();

  it("should be able to create a simplex from a collection of two simplicies") {
    DiSITTimpl *universe = DiSITTimpl::getUniverse();
    shouldNotBeNULL(universe);
    DiStructure initial(universe->getInitialStructure());
    shouldNotBeNULL(initial.ref);
    DiSimplexList listOfTwo;
    DiSimplex simplex0 = DiSITT(universe).getFinalSimplexDim(0);
    DiSimplex simplex1 = DiSITT(universe).getFinalSimplexDim(0);
    listOfTwo.pushItem(simplex0);
    listOfTwo.pushItem(simplex1);
    shouldBeEqual(listOfTwo.getNumItems(), 2);
    DiSimplex simplex2 = universe->createSimplex(initial, listOfTwo);
    shouldBeEqual(simplex2.dimension, 1);
    shouldNotBeZero(simplex2.id);
    shouldBeEqual(simplex2.getLabel().ref, initial.ref);
    DiSimplex simplex0a = simplex2.getSide(0);
    shouldBeEqual(simplex0a.dimension, simplex0.dimension);
    shouldBeEqual(simplex0a.id, simplex0.id);
    DiSimplex simplex1a = simplex2.getSide(1);
    shouldBeEqual(simplex1a.dimension, simplex1.dimension);
    shouldBeEqual(simplex1a.id, simplex1.id);
  } endIt();

} endDescribe(DiSITT);

