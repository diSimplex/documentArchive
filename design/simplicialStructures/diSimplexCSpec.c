#include <stdio.h>

#include <cbdd.h>

#include <diSimplexEngine/dynArray.c>
#include <diSimplexEngine/diSiTT.c>
#include <diSimplexEngine/diStructure.c>
#include <diSimplexEngine/diSimplex.c>

DiSiTT  disittObj0, disittObj1;
DiSiTT *disitt0, *disitt1;


int main() {

  // setup our DiSiTT engine(s)
  disitt0 = &disittObj0;
  diSiTT_init(disitt0);
  disitt1 = &disittObj1;
  diSiTT_init(disitt1);

  fprintf(stdout, "\n>>>diSimplexCSpec\n\n");

  describe("Simplex constructor/descructors using empty disitt", ^{

    it("should get and return one empty simplex", ^{
      // get a simplex
      DiSimplexRef newSimplex;
      diSimplexRef_init(&newSimplex, disitt1, 3, 0, 0);
      expect_true(diSimplex_get_empty(&newSimplex));
      expect_equal(newSimplex.simplex, 1);
      expect_equal(DynArray_len(disitt1->simplicies), 4);
      expect_true(diSimplex_exists(&newSimplex));
      DynArray *dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 2);
      expect_equal(DynArray_elementSize(dim3Simplicies), DiSimplexObjSize(3));
      DiSimplexObj *newSimplexObj =
        DynArray_getElementPtr(dim3Simplicies, 1, DiSimplexObj);
      expect_equal(newSimplexObj->side[0], 0);
      //
      // return the simplex
      //
      diSimplex_release(&newSimplex);
      expect_false(diSimplex_exists(&newSimplex));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 2);
    });

    it("should get and return a number of  empty simplicies", ^{
      DiSimplexRef newSimplex0;
      diSimplexRef_init(&newSimplex0, disitt1, 3, 0, 0);
      expect_true(diSimplex_get_empty(&newSimplex0));
      DiSimplexRef newSimplex1;
      diSimplexRef_init(&newSimplex1, disitt1, 3, 0, 0);
      expect_true(diSimplex_get_empty(&newSimplex1));
      DiSimplexRef newSimplex2;
      diSimplexRef_init(&newSimplex2, disitt1, 3, 0, 0);
      expect_true(diSimplex_get_empty(&newSimplex2));
      DiSimplexRef newSimplex3;
      diSimplexRef_init(&newSimplex3, disitt1, 3, 0, 0);
      expect_true(diSimplex_get_empty(&newSimplex3));
      DiSimplexRef newSimplex4;
      diSimplexRef_init(&newSimplex4, disitt1, 3, 0, 0);
      expect_true(diSimplex_get_empty(&newSimplex4));
      expect_equal(newSimplex0.simplex, 1);
      expect_equal(newSimplex1.simplex, 2);
      expect_equal(newSimplex2.simplex, 3);
      expect_equal(newSimplex3.simplex, 4);
      expect_equal(newSimplex4.simplex, 5);
      expect_equal(DynArray_len(disitt1->simplicies), 4);
      expect_true(diSimplex_exists(&newSimplex0));
      expect_true(diSimplex_exists(&newSimplex1));
      expect_true(diSimplex_exists(&newSimplex2));
      expect_true(diSimplex_exists(&newSimplex3));
      expect_true(diSimplex_exists(&newSimplex4));
      DynArray *dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 6);
      expect_equal(DynArray_elementSize(dim3Simplicies), DiSimplexObjSize(3));
      DiSimplexObj *newSimplex0Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex0.simplex,
                               DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 0);
      newSimplex0Obj->side[0] = 10;
      DiSimplexObj *newSimplex1Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex1.simplex,
                               DiSimplexObj);
      expect_equal(newSimplex1Obj->side[0], 0);
      newSimplex1Obj->side[0] = 10;
      //
      // return some simplicies
      //
      diSimplex_release(&newSimplex1);
      diSimplex_release(&newSimplex3);
      expect_true(diSimplex_exists(&newSimplex0));
      expect_false(diSimplex_exists(&newSimplex1));
      expect_true(diSimplex_exists(&newSimplex2));
      expect_false(diSimplex_exists(&newSimplex3));
      expect_true(diSimplex_exists(&newSimplex4));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 6);
      newSimplex0Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex0.simplex,
                               DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 10);
      //
      // get some more simplicies (should reuse newSimplex1 and newSimplex3
      //
      expect_true(diSimplex_get_empty(&newSimplex1));
      expect_true(diSimplex_get_empty(&newSimplex3));
      expect_true(diSimplex_exists(&newSimplex1));
      expect_true(diSimplex_exists(&newSimplex3));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 6);
      newSimplex0Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex0.simplex,
                               DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 10);
      newSimplex1Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex1.simplex,
                               DiSimplexObj);
      expect_equal(newSimplex1Obj->side[0], 0);
      //
      // get a new simplex (should be completely new)
      //
      DiSimplexRef newSimplex5;
      diSimplexRef_init(&newSimplex5, disitt1, 3, 6, 0);
      expect_false(diSimplex_exists(&newSimplex5));
      expect_true(diSimplex_get_empty(&newSimplex5));
      expect_equal(newSimplex5.simplex, 6);
      expect_true(diSimplex_exists(&newSimplex5));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 7);
    });

  });

  describe("storing/getting sides", ^{

    it("should be able to store and get sides", ^{
      DiSimplexRef parentSimplex;
      parentSimplex.diSiTT    = disitt1;
      parentSimplex.dimension = 3;
      expect_true(diSimplex_get_empty(&parentSimplex));
      DiSimplexRef childSimplex;
      childSimplex.diSiTT    = disitt1;
      childSimplex.dimension = 2;
      expect_true(diSimplex_get_empty(&childSimplex));
      diSimplex_store_side(&parentSimplex, 0, &childSimplex);
      DiSimplexRef sideSimplex0;
      expect_true(diSimplex_get_side(&parentSimplex, 0, &sideSimplex0));
      expect_true(childSimplex.diSiTT == sideSimplex0.diSiTT);
      expect_equal(childSimplex.dimension, sideSimplex0.dimension);
      expect_equal(childSimplex.simplex,   sideSimplex0.simplex);
      DiSimplexRef sideSimplex1;
      expect_true(diSimplex_get_side(&parentSimplex, 1, &sideSimplex1));
      expect_true(sideSimplex1.diSiTT == disitt1);
      expect_equal(sideSimplex1.dimension, 2);
      expect_equal(sideSimplex1.simplex, 0);
    });

    it("should do nothing if side is not part of simplex", ^{
      DiSimplexRef parentSimplex;
      parentSimplex.diSiTT    = disitt1;
      parentSimplex.dimension = 3;
      expect_true(diSimplex_get_empty(&parentSimplex));
      DiSimplexRef childSimplex;
      childSimplex.diSiTT    = disitt1;
      childSimplex.dimension = 2;
      childSimplex.simplex   = 0;
      expect_true(diSimplex_get_empty(&childSimplex));
      expect_true(childSimplex.diSiTT == disitt1);
      expect_equal(childSimplex.dimension, 2);
      expect_equal(childSimplex.simplex, 2);
      childSimplex.simplex = 0;
      diSimplex_store_side(&parentSimplex, 10, &childSimplex);
      expect_false(diSimplex_get_side(&parentSimplex, 10, &childSimplex));
      expect_true(childSimplex.diSiTT == disitt1);
      expect_equal(childSimplex.dimension, 2);
      expect_equal(childSimplex.simplex, 0);
      diSimplex_store_side(&parentSimplex, -1, &childSimplex);
      expect_false(diSimplex_get_side(&parentSimplex, -1, &childSimplex));
      expect_true(childSimplex.diSiTT == disitt1);
      expect_equal(childSimplex.dimension, 2);
      expect_equal(childSimplex.simplex, 0);
    });

  });

  describe("terminal simplicies", ^{

    it("should exist", ^{
      diSiTT_ensure_dimension(disitt1, 5);
      DiSimplexRef terminalSimplex;
      terminalSimplex.diSiTT    = disitt1;
      terminalSimplex.simplex   = 0;
      terminalSimplex.structure = 0;

      terminalSimplex.dimension = 0;
      expect_true(diSimplex_exists(&terminalSimplex));

      terminalSimplex.dimension = 1;
      expect_true(diSimplex_exists(&terminalSimplex));

      terminalSimplex.dimension = 2;
      expect_true(diSimplex_exists(&terminalSimplex));

      terminalSimplex.dimension = 3;
      expect_true(diSimplex_exists(&terminalSimplex));

      terminalSimplex.dimension = 4;
      expect_true(diSimplex_exists(&terminalSimplex));

      terminalSimplex.dimension = 5;
      expect_true(diSimplex_exists(&terminalSimplex));

      terminalSimplex.dimension = 6;
      expect_false(diSimplex_exists(&terminalSimplex));

      terminalSimplex.dimension = 7;
      expect_false(diSimplex_exists(&terminalSimplex));
    });
  });

  fprintf(stdout, "\n");

  return 0;
}

