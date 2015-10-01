#include <string.h>
#include <stdio.h>
#include <exception>

#include <cUtils/specs/specs.h>

#ifndef protected
#define protected public
#endif

#include <diSimplexEngine/diSitt.h>

describe(DiSimplexAllocatorIterator) {

  specSize(DiSimplexAllocatorIterator);

  it("should be able to iterate over lots of simplicies") {
    DiSimplexAllocator *allocator = new DiSimplexAllocator(0,2);
    shouldNotBeNULL(allocator);
    DiSimplex::List emptyList;
    size_t i = 0;
    for ( i = 0 ; i < 10 ; i++ ) {
      DiSimplex *simplex = allocator->allocateNewSimplex();
      shouldNotBeNULL(simplex);
      simplex->initializeSimplex((DiStructure*)i, emptyList);
    }
    DiSimplexAllocatorIterator iter = allocator->getIterator();
    for ( i = 0 ; iter.hasMoreItems() ; i++ ) {
      DiSimplex *simplex = iter.nextItem();
      shouldNotBeNULL(simplex);
      shouldBeEqual(simplex->getLabel(), (DiSimplex*)i);
    }
    shouldBeEqual(i, 10);

    DiSimplex *simplex = allocator->allocateNewSimplex();
    shouldNotBeNULL(simplex);
    simplex->initializeSimplex((DiStructure*)10, emptyList);
    iter = allocator->getIterator();
    for ( i = 0 ; iter.hasMoreItems() ; i++ ) {
      DiSimplex *simplex = iter.nextItem();
      shouldNotBeNULL(simplex);
      shouldBeEqual(simplex->getLabel(), (DiSimplex*)i);
    }
    shouldBeEqual(i, 11);

    delete allocator;
  } endIt();

} endDescribe(DiSimplexAllocatorIterator);

