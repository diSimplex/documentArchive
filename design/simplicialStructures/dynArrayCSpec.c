#include <stdio.h>

#include <cbdd.h>

#include <diSimplexEngine/dynArray.c>

/* TODO: should actually test DynArray_addZeroedElement actually
returns a zero element after pops.  However, at the moment this is not
strictly needed. (DynArray_addZeroedElement is used and so tested in
DynArray_addElement. */

int main() {
  fprintf(stdout, "\n>>>dynArrayCSpec\n\n");
  fprintf(stdout, "size of        void* = %u\n", sizeof(void*));
  fprintf(stdout, "size of     DynArray = %u",   sizeof(DynArray));
  fprintf(stdout, "   + DynArray_capacity()*DynArray_elementSize()\n");
  fprintf(stdout, "\n");

  describe("DynArray", ^{

    it("new dynArrays have zero size/len and capacity", ^{
      DynArray *dynArray = DynArray_new(10, 0);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_size(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), 10);
      DynArray_free(dynArray);
    });

    it("ensure capacity will increase the capacity of the dynArray", ^{
      DynArray *dynArray = DynArray_new(10, 0);
      void* oldData = dynArray->data;
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), 10);
      DynArray_ensureCapacity(dynArray, 30);
      expect_false(dynArray->data == oldData);
      expect_equal(DynArray_len(dynArray), 0);
      expect_true(30 < DynArray_capacity(dynArray));
      expect_equal(DynArray_elementSize(dynArray), 10);
      DynArray_free(dynArray);
    });

    it("ensure capacity with elements will be copied properly", ^{
      DynArray *dynArray = DynArray_new(sizeof(long), 0);
      void* oldData = dynArray->data;
      DynArray_addElement(dynArray, long, 10L);
      DynArray_addElement(dynArray, long, 11L);
      DynArray_addElement(dynArray, long, 12L);
      DynArray_addElement(dynArray, long, 13L);
      DynArray_addElement(dynArray, long, 14L);
      expect_equal(DynArray_len(dynArray), 5);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      DynArray_ensureCapacity(dynArray, 30);
      expect_false(dynArray->data == oldData);
      expect_equal(DynArray_len(dynArray), 5);
      expect_true(30 < DynArray_capacity(dynArray));
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      expect_equal(*DynArray_getElementPtr(dynArray,  0, long), 10L);
      expect_equal(*DynArray_getElementPtr(dynArray,  1, long), 11L);
      expect_equal(*DynArray_getElementPtr(dynArray,  2, long), 12L);
      expect_equal(*DynArray_getElementPtr(dynArray,  3, long), 13L);
      expect_equal(*DynArray_getElementPtr(dynArray,  4, long), 14L);
      DynArray_free(dynArray);
    });

    it("can add an new zeroed element on the end", ^{
      DynArray *dynArray = DynArray_new(sizeof(long), 0);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      DynArray_addZeroedElement(dynArray);
      expect_equal(DynArray_len(dynArray), 1);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      expect_equal(*DynArray_getElementPtr(dynArray, 0, long), 0L);
      DynArray_free(dynArray);
    });

    it("can add a new non-zero element on the end", ^{
      DynArray *dynArray = DynArray_new(sizeof(long), 0);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      DynArray_addElement(dynArray, long, 10L);
      DynArray_addElement(dynArray, long, 11L);
      DynArray_addElement(dynArray, long, 12L);
      DynArray_addElement(dynArray, long, 13L);
      DynArray_addElement(dynArray, long, 14L);
      DynArray_addElement(dynArray, long, 15L);
      DynArray_addElement(dynArray, long, 16L);
      DynArray_addElement(dynArray, long, 17L);
      DynArray_addElement(dynArray, long, 18L);
      DynArray_addElement(dynArray, long, 19L);
      DynArray_addElement(dynArray, long, 20L);
      DynArray_addElement(dynArray, long, 21L);
      DynArray_addElement(dynArray, long, 22L);
      DynArray_addElement(dynArray, long, 23L);
      DynArray_addElement(dynArray, long, 24L);
      expect_equal(DynArray_len(dynArray), 15);
      expect_equal(DynArray_capacity(dynArray), 2*DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      expect_equal(*DynArray_getElementPtr(dynArray,  0, long), 10L);
      expect_equal(*DynArray_getElementPtr(dynArray,  1, long), 11L);
      expect_equal(*DynArray_getElementPtr(dynArray,  2, long), 12L);
      expect_equal(*DynArray_getElementPtr(dynArray,  3, long), 13L);
      expect_equal(*DynArray_getElementPtr(dynArray,  4, long), 14L);
      expect_equal(*DynArray_getElementPtr(dynArray,  5, long), 15L);
      expect_equal(*DynArray_getElementPtr(dynArray,  6, long), 16L);
      expect_equal(*DynArray_getElementPtr(dynArray,  7, long), 17L);
      expect_equal(*DynArray_getElementPtr(dynArray,  8, long), 18L);
      expect_equal(*DynArray_getElementPtr(dynArray,  9, long), 19L);
      expect_equal(*DynArray_getElementPtr(dynArray, 10, long), 20L);
      expect_equal(*DynArray_getElementPtr(dynArray, 11, long), 21L);
      expect_equal(*DynArray_getElementPtr(dynArray, 12, long), 22L);
      expect_equal(*DynArray_getElementPtr(dynArray, 13, long), 23L);
      expect_equal(*DynArray_getElementPtr(dynArray, 14, long), 24L);
      DynArray_free(dynArray);
    });

    it("can clear a dynArray after adding lots of new non-zero elements on the end", ^{
      DynArray *dynArray = DynArray_new(sizeof(long), 0);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      DynArray_addElement(dynArray, long, 10L);
      DynArray_addElement(dynArray, long, 11L);
      DynArray_addElement(dynArray, long, 12L);
      DynArray_addElement(dynArray, long, 13L);
      DynArray_addElement(dynArray, long, 14L);
      DynArray_addElement(dynArray, long, 15L);
      DynArray_addElement(dynArray, long, 16L);
      DynArray_addElement(dynArray, long, 17L);
      DynArray_addElement(dynArray, long, 18L);
      DynArray_addElement(dynArray, long, 19L);
      DynArray_addElement(dynArray, long, 20L);
      DynArray_addElement(dynArray, long, 21L);
      DynArray_addElement(dynArray, long, 22L);
      DynArray_addElement(dynArray, long, 23L);
      DynArray_addElement(dynArray, long, 24L);
      expect_equal(DynArray_len(dynArray), 15);
      expect_equal(DynArray_capacity(dynArray), 2*DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      expect_equal(*DynArray_getElementPtr(dynArray,  0, long), 10L);
      expect_equal(*DynArray_getElementPtr(dynArray,  1, long), 11L);
      expect_equal(*DynArray_getElementPtr(dynArray,  2, long), 12L);
      expect_equal(*DynArray_getElementPtr(dynArray,  3, long), 13L);
      expect_equal(*DynArray_getElementPtr(dynArray,  4, long), 14L);
      expect_equal(*DynArray_getElementPtr(dynArray,  5, long), 15L);
      expect_equal(*DynArray_getElementPtr(dynArray,  6, long), 16L);
      expect_equal(*DynArray_getElementPtr(dynArray,  7, long), 17L);
      expect_equal(*DynArray_getElementPtr(dynArray,  8, long), 18L);
      expect_equal(*DynArray_getElementPtr(dynArray,  9, long), 19L);
      expect_equal(*DynArray_getElementPtr(dynArray, 10, long), 20L);
      expect_equal(*DynArray_getElementPtr(dynArray, 11, long), 21L);
      expect_equal(*DynArray_getElementPtr(dynArray, 12, long), 22L);
      expect_equal(*DynArray_getElementPtr(dynArray, 13, long), 23L);
      expect_equal(*DynArray_getElementPtr(dynArray, 14, long), 24L);
      DynArray_clear(dynArray);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), 2*DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      expect_equal(*DynArray_getElementPtr(dynArray,  0, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  1, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  2, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  3, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  4, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  5, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  6, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  7, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  8, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray,  9, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray, 10, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray, 11, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray, 12, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray, 13, long), 0L);
      expect_equal(*DynArray_getElementPtr(dynArray, 14, long), 0L);
      DynArray_free(dynArray);
    });

    it("can pop elements off the end after adding lots of new non-zero elements on the end", ^{
      DynArray *dynArray = DynArray_new(sizeof(long), 0);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      DynArray_addElement(dynArray, long, 10L);
      DynArray_addElement(dynArray, long, 11L);
      DynArray_addElement(dynArray, long, 12L);
      DynArray_addElement(dynArray, long, 13L);
      DynArray_addElement(dynArray, long, 14L);
      DynArray_addElement(dynArray, long, 15L);
      DynArray_addElement(dynArray, long, 16L);
      DynArray_addElement(dynArray, long, 17L);
      DynArray_addElement(dynArray, long, 18L);
      DynArray_addElement(dynArray, long, 19L);
      DynArray_addElement(dynArray, long, 20L);
      DynArray_addElement(dynArray, long, 21L);
      DynArray_addElement(dynArray, long, 22L);
      DynArray_addElement(dynArray, long, 23L);
      DynArray_addElement(dynArray, long, 24L);
      expect_equal(DynArray_len(dynArray), 15);
      expect_equal(DynArray_capacity(dynArray), 2*DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      expect_equal(*DynArray_getElementPtr(dynArray,  0, long), 10L);
      expect_equal(*DynArray_getElementPtr(dynArray,  1, long), 11L);
      expect_equal(*DynArray_getElementPtr(dynArray,  2, long), 12L);
      expect_equal(*DynArray_getElementPtr(dynArray,  3, long), 13L);
      expect_equal(*DynArray_getElementPtr(dynArray,  4, long), 14L);
      expect_equal(*DynArray_getElementPtr(dynArray,  5, long), 15L);
      expect_equal(*DynArray_getElementPtr(dynArray,  6, long), 16L);
      expect_equal(*DynArray_getElementPtr(dynArray,  7, long), 17L);
      expect_equal(*DynArray_getElementPtr(dynArray,  8, long), 18L);
      expect_equal(*DynArray_getElementPtr(dynArray,  9, long), 19L);
      expect_equal(*DynArray_getElementPtr(dynArray, 10, long), 20L);
      expect_equal(*DynArray_getElementPtr(dynArray, 11, long), 21L);
      expect_equal(*DynArray_getElementPtr(dynArray, 12, long), 22L);
      expect_equal(*DynArray_getElementPtr(dynArray, 13, long), 23L);
      expect_equal(*DynArray_getElementPtr(dynArray, 14, long), 24L);
      expect_equal(DynArray_len(dynArray), 15);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 24L);
      expect_equal(DynArray_len(dynArray), 14);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 23L);
      expect_equal(DynArray_len(dynArray), 13);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 22L);
      expect_equal(DynArray_len(dynArray), 12);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 21L);
      expect_equal(DynArray_len(dynArray), 11);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 20L);
      expect_equal(DynArray_len(dynArray), 10);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 19L);
      expect_equal(DynArray_len(dynArray), 9);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 18L);
      expect_equal(DynArray_len(dynArray), 8);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 17L);
      expect_equal(DynArray_len(dynArray), 7);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 16L);
      expect_equal(DynArray_len(dynArray), 6);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 15L);
      expect_equal(DynArray_len(dynArray), 5);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 14L);
      expect_equal(DynArray_len(dynArray), 4);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 13L);
      expect_equal(DynArray_len(dynArray), 3);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 12L);
      expect_equal(DynArray_len(dynArray), 2);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 11L);
      expect_equal(DynArray_len(dynArray), 1);
      expect_equal(*DynArray_popLastElementPtr(dynArray, long), 10L);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), 2*DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long));
      DynArray_free(dynArray);
    });

    it("can add a new pointer element on the end", ^{
      long aLong00 = 10L;
      long aLong01 = 11L;
      long aLong02 = 12L;
      long aLong03 = 13L;
      long aLong04 = 14L;
      long aLong05 = 15L;
      long aLong06 = 16L;
      long aLong07 = 17L;
      long aLong08 = 18L;
      long aLong09 = 19L;
      long aLong10 = 20L;
      long aLong11 = 21L;
      long aLong12 = 22L;
      long aLong13 = 23L;
      long aLong14 = 24L;
      DynArray *dynArray = DynArray_new(sizeof(long*), 0);
      expect_equal(DynArray_len(dynArray), 0);
      expect_equal(DynArray_capacity(dynArray), DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long*));
      DynArray_addElement(dynArray, long*, &aLong00);
      DynArray_addElement(dynArray, long*, &aLong01);
      DynArray_addElement(dynArray, long*, &aLong02);
      DynArray_addElement(dynArray, long*, &aLong03);
      DynArray_addElement(dynArray, long*, &aLong04);
      DynArray_addElement(dynArray, long*, &aLong05);
      DynArray_addElement(dynArray, long*, &aLong06);
      DynArray_addElement(dynArray, long*, &aLong07);
      DynArray_addElement(dynArray, long*, &aLong08);
      DynArray_addElement(dynArray, long*, &aLong09);
      DynArray_addElement(dynArray, long*, &aLong10);
      DynArray_addElement(dynArray, long*, &aLong11);
      DynArray_addElement(dynArray, long*, &aLong12);
      DynArray_addElement(dynArray, long*, &aLong13);
      DynArray_addElement(dynArray, long*, &aLong14);
      expect_equal(DynArray_len(dynArray), 15);
      expect_equal(DynArray_capacity(dynArray), 2*DYNARRAY_CAPACITY_INCREMENT);
      expect_equal(DynArray_elementSize(dynArray), sizeof(long*));
      expect_true(*DynArray_getElementPtr(dynArray,  0, long*) == &aLong00);
      expect_equal(**DynArray_getElementPtr(dynArray,  0, long*), aLong00);
      expect_true(*DynArray_getElementPtr(dynArray,  1, long*) == &aLong01);
      expect_equal(**DynArray_getElementPtr(dynArray,  1, long*), aLong01);
      expect_true(*DynArray_getElementPtr(dynArray,  2, long*) == &aLong02);
      expect_equal(**DynArray_getElementPtr(dynArray,  2, long*), aLong02);
      expect_true(*DynArray_getElementPtr(dynArray,  3, long*) == &aLong03);
      expect_equal(**DynArray_getElementPtr(dynArray,  3, long*), aLong03);
      expect_true(*DynArray_getElementPtr(dynArray,  4, long*) == &aLong04);
      expect_equal(**DynArray_getElementPtr(dynArray,  4, long*), aLong04);
      expect_true(*DynArray_getElementPtr(dynArray,  5, long*) == &aLong05);
      expect_equal(**DynArray_getElementPtr(dynArray,  5, long*), aLong05);
      expect_true(*DynArray_getElementPtr(dynArray,  6, long*) == &aLong06);
      expect_equal(**DynArray_getElementPtr(dynArray,  6, long*), aLong06);
      expect_true(*DynArray_getElementPtr(dynArray,  7, long*) == &aLong07);
      expect_equal(**DynArray_getElementPtr(dynArray,  7, long*), aLong07);
      expect_true(*DynArray_getElementPtr(dynArray,  8, long*) == &aLong08);
      expect_equal(**DynArray_getElementPtr(dynArray,  8, long*), aLong08);
      expect_true(*DynArray_getElementPtr(dynArray,  9, long*) == &aLong09);
      expect_equal(**DynArray_getElementPtr(dynArray,  9, long*), aLong09);
      expect_true(*DynArray_getElementPtr(dynArray, 10, long*) == &aLong10);
      expect_equal(**DynArray_getElementPtr(dynArray, 10, long*), aLong10);
      expect_true(*DynArray_getElementPtr(dynArray, 11, long*) == &aLong11);
      expect_equal(**DynArray_getElementPtr(dynArray, 11, long*), aLong11);
      expect_true(*DynArray_getElementPtr(dynArray, 12, long*) == &aLong12);
      expect_equal(**DynArray_getElementPtr(dynArray, 12, long*), aLong12);
      expect_true(*DynArray_getElementPtr(dynArray, 13, long*) == &aLong13);
      expect_equal(**DynArray_getElementPtr(dynArray, 13, long*), aLong13);
      expect_true(*DynArray_getElementPtr(dynArray, 14, long*) == &aLong14);
      expect_equal(**DynArray_getElementPtr(dynArray, 14, long*), aLong14);
      DynArray_free(dynArray);
    });

  });

  fprintf(stdout, "\n");

  return 0;
}

