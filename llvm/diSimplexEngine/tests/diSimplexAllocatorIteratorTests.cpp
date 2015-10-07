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
    DiSimplexAllocatorIterator iter = allocator->getIterator();
    // test iterator on empty allocator
    shouldBeFalse(iter.hasMoreItems());

    DiSimplex::List emptyList;
    // fill multiple blocks but leave the last block part full
    size_t i = 0;
    for ( i = 0 ; i < 10 ; i++ ) {
      DiSimplex *simplex = allocator->allocateNewSimplex();
      shouldNotBeNULL(simplex);
      simplex->initializeSimplex((DiStructure*)i, emptyList);
    }
    // test iterator with a last unfully filled block
    iter = allocator->getIterator();
    for ( i = 0 ; iter.hasMoreItems() ; i++ ) {
      DiSimplex *simplex = iter.nextItem();
      shouldNotBeNULL(simplex);
      shouldBeEqual(simplex->getLabel(), (DiSimplex*)i);
    }
    shouldBeEqual(i, 10);

    // now fully fill the last block
    DiSimplex *simplex = allocator->allocateNewSimplex();
    shouldNotBeNULL(simplex);
    simplex->initializeSimplex((DiStructure*)10, emptyList);
    simplex = allocator->allocateNewSimplex();
    shouldNotBeNULL(simplex);
    simplex->initializeSimplex((DiStructure*)11, emptyList);
    // test iterator with a last fully filled block
    iter = allocator->getIterator();
    for ( i = 0 ; iter.hasMoreItems() ; i++ ) {
      DiSimplex *simplex = iter.nextItem();
      shouldNotBeNULL(simplex);
      shouldBeEqual(simplex->getLabel(), (DiSimplex*)i);
    }
    shouldBeEqual(i, 12);

    delete allocator;
  } endIt();

} endDescribe(DiSimplexAllocatorIterator);

