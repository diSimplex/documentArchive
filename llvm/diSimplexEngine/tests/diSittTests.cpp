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

  it("There should be an initial structure") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    shouldBeTrue(initial.isEmpty());
    for (size_t i = 0 ; i < 100 ; i++ ) shouldBeZero(initial.sizeDim(i));
  } endIt();

  it("There should be a terminal structure") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure final = universe.getFinalStructure();
    shouldNotBeNULL(final.ref);
    for (size_t i = 0; i < 100; i++) {
      shouldBeEqual(final.sizeDim(i), 1);
      DiSimplex simplex = universe.getFinalSimplexDim(i);
      shouldBeTrue(simplex.isFinal());
      shouldBeTrue(final.contains(simplex));
    }
  } endIt();

  it("should be able to create a simplex from an empty collection of simplicies") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    DiSimplexList emptyList;
    shouldBeZero(emptyList.getNumItems());
    DiSimplex simplex0 = universe.getSimplex(initial, emptyList);
    shouldBeEqual(simplex0.dimension, -1);
    shouldNotBeZero(simplex0.id);
    shouldBeEqual(simplex0.getLabel().ref, initial.ref);
  } endIt();

  it("should be able to create a simplex from a collection of one simplex") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    DiSimplexList listOfOne;
    DiSimplex simplex0 = universe.getFinalSimplexDim(-1);
    listOfOne.pushItem(simplex0);
    shouldBeEqual(listOfOne.getNumItems(), 1);
    DiSimplex simplex1 = universe.getSimplex(initial, listOfOne);
    shouldBeEqual(simplex1.dimension, 0);
    shouldNotBeZero(simplex1.id);
    shouldBeEqual(simplex1.getLabel().ref, initial.ref);
    DiSimplex simplex0a = simplex1.getSide(0);
    shouldBeEqual(simplex0a.dimension, simplex0.dimension);
    shouldBeEqual(simplex0a.id, simplex0.id);
  } endIt();

  it("should be able to create a simplex from a collection of two simplicies") {
    DiSITT universe = DiSITT::getUniverse();
    shouldNotBeNULL(universe.ref);
    DiStructure initial = universe.getInitialStructure();
    shouldNotBeNULL(initial.ref);
    DiSimplexList listOfTwo;
    DiSimplex simplex0 = universe.getFinalSimplexDim(0);
    DiSimplex simplex1 = universe.getFinalSimplexDim(0);
    listOfTwo.pushItem(simplex0);
    listOfTwo.pushItem(simplex1);
    shouldBeEqual(listOfTwo.getNumItems(), 2);
    DiSimplex simplex2 = universe.getSimplex(initial, listOfTwo);
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
