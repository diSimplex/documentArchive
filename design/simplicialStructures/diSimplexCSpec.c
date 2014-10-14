#include <stdio.h>

#include <cbdd.h>

#include <diSimplexEngine/dynArray.c>
#include <diSimplexEngine/diSiTT.c>
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
      simplex_id newSimplex = diSiTT_get_empty_simplex(disitt1, 3);
      expect_equal(newSimplex, 1);
      expect_equal(DynArray_len(disitt1->simplicies), 4);
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex));
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
      diSiTT_release_simplex(disitt1, 3, newSimplex);
      expect_false(diSiTT_simplex_exists(disitt1, 3, newSimplex));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 2);
    });

    it("should get and return a number of  empty simplicies", ^{
      simplex_id newSimplex0 = diSiTT_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex1 = diSiTT_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex2 = diSiTT_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex3 = diSiTT_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex4 = diSiTT_get_empty_simplex(disitt1, 3);
      expect_equal(newSimplex0, 1);
      expect_equal(newSimplex1, 2);
      expect_equal(newSimplex2, 3);
      expect_equal(newSimplex3, 4);
      expect_equal(newSimplex4, 5);
      expect_equal(DynArray_len(disitt1->simplicies), 4);
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex0));
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex1));
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex2));
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex3));
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex4));
      DynArray *dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 6);
      expect_equal(DynArray_elementSize(dim3Simplicies), DiSimplexObjSize(3));
      DiSimplexObj *newSimplex0Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex0, DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 0);
      newSimplex0Obj->side[0] = 10;
      DiSimplexObj *newSimplex1Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex1, DiSimplexObj);
      expect_equal(newSimplex1Obj->side[0], 0);
      newSimplex1Obj->side[0] = 10;
      //
      // return some simplicies
      //
      diSiTT_release_simplex(disitt1, 3, newSimplex1);
      diSiTT_release_simplex(disitt1, 3, newSimplex3);
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex0));
      expect_false(diSiTT_simplex_exists(disitt1, 3, newSimplex1));
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex2));
      expect_false(diSiTT_simplex_exists(disitt1, 3, newSimplex3));
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex4));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 6);
      newSimplex0Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex0, DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 10);
      //
      // get some more simplicies (should reuse newSimplex1 and newSimplex3
      //
      newSimplex1 = diSiTT_get_empty_simplex(disitt1, 3);
      newSimplex3 = diSiTT_get_empty_simplex(disitt1, 3);
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex1));
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex3));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 6);
      newSimplex0Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex0, DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 10);
      newSimplex1Obj =
        DynArray_getElementPtr(dim3Simplicies, newSimplex1, DiSimplexObj);
      expect_equal(newSimplex1Obj->side[0], 0);
      //
      // get a new simplex (should be completely new)
      //
      expect_false(diSiTT_simplex_exists(disitt1, 3, 6));
      simplex_id newSimplex5 = diSiTT_get_empty_simplex(disitt1, 3);
      expect_equal(newSimplex5, 6);
      expect_true(diSiTT_simplex_exists(disitt1, 3, newSimplex5));
      dim3Simplicies =
        *DynArray_getElementPtr(disitt1->simplicies, 3, DynArray*);
      expect_equal(DynArray_len(dim3Simplicies), 7);
    });

  });

  describe("storing/getting sides", ^{

    it("should be able to store and get sides", ^{
      simplex_id parentSimplexId = diSiTT_get_empty_simplex(disitt1, 3);
      simplex_id childSimplexId  = diSiTT_get_empty_simplex(disitt1, 2);
      diSimplex_store_side(disitt1, 3, parentSimplexId, 0, childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, 0), childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, 1), 0);
    });

    it("should do nothing if side is not part of simplex", ^{
      simplex_id parentSimplexId = diSiTT_get_empty_simplex(disitt1, 3);
      simplex_id childSimplexId  = diSiTT_get_empty_simplex(disitt1, 2);
      diSimplex_store_side(disitt1, 3, parentSimplexId, 10, childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, 10), 0);
      diSimplex_store_side(disitt1, 3, parentSimplexId, -1, childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, -1), 0);
    });

  });

  describe("universe simplicies", ^{

    it("should exist", ^{
      diSiTT_ensure_dimension(disitt1, 5);
      expect_true(diSiTT_simplex_exists(disitt1, 0, 0));
      expect_true(diSiTT_simplex_exists(disitt1, 1, 0));
      expect_true(diSiTT_simplex_exists(disitt1, 2, 0));
      expect_true(diSiTT_simplex_exists(disitt1, 3, 0));
      expect_true(diSiTT_simplex_exists(disitt1, 4, 0));
      expect_true(diSiTT_simplex_exists(disitt1, 5, 0));
      expect_false(diSiTT_simplex_exists(disitt1, 6, 0));
      expect_false(diSiTT_simplex_exists(disitt1, 7, 0));
    });
  });

  fprintf(stdout, "\n");

  return 0;
}

