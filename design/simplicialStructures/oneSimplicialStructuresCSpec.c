#include <stdio.h>

#include <cbdd.h>

#include <diSimplexEngine/dynArray.c>
#include <diSimplexEngine/diSimplexEngine.c>

DiSiTT  disittObj0, disittObj1;
DiSiTT *disitt0, *disitt1;


int main() {

  // setup our DiSiTT engine(s)
  disitt0 = &disittObj0;
  dse_init_disitt(disitt0);
  disitt1 = &disittObj1;
  dse_init_disitt(disitt1);

  fprintf(stdout, "\n>>>oneSimplicialStructuresCSpec\n\n");
  fprintf(stdout, "size of             int = %lu\n", sizeof(int));
  fprintf(stdout, "size of     dimension_t = %lu\n", sizeof(dimension_t));
  fprintf(stdout, "size of      simplex_id = %lu\n", sizeof(simplex_id));
  fprintf(stdout, "size of           void* = %lu\n", sizeof(void*));
  fprintf(stdout, "size of          DiSiTT = %lu\n", sizeof(DiSiTT));
  fprintf(stdout, "size of    DiSimplexObj = %lu",   sizeof(DiSimplexObj));
  fprintf(stdout, "   + (dimension + 1)*sizeof(int)\n");
  fprintf(stdout, "size of DiSimplexObj(1) = %lu\n",  DiSimplexObjSize(1));
  fprintf(stdout, "size of    DiSimplexRef = %lu\n", sizeof(DiSimplexRef));
  fprintf(stdout, "\n");

  describe("DiSiTT engine", ^{

    it("should have empty DynArray structures (before use)", ^{
      expect_equal(DynArray_len(disitt0->emptySimplicies), 0);
      expect_equal(DynArray_len(disitt0->instances), 0);
    });

    it("should have empty DynArray structures (after instances_ensure_dimension)", ^{
      expect_equal(DynArray_len(disitt0->emptySimplicies), 0);
      expect_equal(DynArray_len(disitt0->instances), 0);
      instances_ensure_dimension(disitt0, 60);
      expect_equal(DynArray_len(disitt0->emptySimplicies), 61);
      expect_equal(DynArray_len(disitt0->instances), 61);

      // walk through each dimension and check the icd...
      int i = 52;
      for(; i < 61; i++) {
        DynArray *dimInstances =
          *DynArray_getElementPtr(disitt0->instances, i, DynArray*);
        expect_equal(DynArray_len(dimInstances), 1);
        refute_equal(DynArray_capacity(dimInstances), 0);
        expect_equal(DynArray_elementSize(dimInstances), DiSimplexObjSize(i));
      }
    });

  });

  describe("Simplex constructor/descructors using empty disitt", ^{

    it("should get and return one empty simplex", ^{
      // get a simplex
      simplex_id newSimplex = instances_get_empty_simplex(disitt1, 3);
      expect_equal(newSimplex, 1);
      expect_equal(DynArray_len(disitt1->instances), 4);
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex));
      DynArray *dim3Instances =
        *DynArray_getElementPtr(disitt1->instances, 3, DynArray*);
      expect_equal(DynArray_len(dim3Instances), 2);
      expect_equal(DynArray_elementSize(dim3Instances), DiSimplexObjSize(3));
      DiSimplexObj *newSimplexObj =
        DynArray_getElementPtr(dim3Instances, 1, DiSimplexObj);
      expect_equal(newSimplexObj->side[0], 0);
      //
      // return the simplex
      //
      instances_return_simplex(disitt1, 3, newSimplex);
      expect_false(instances_simplex_exists(disitt1, 3, newSimplex));
      dim3Instances =
        *DynArray_getElementPtr(disitt1->instances, 3, DynArray*);
      expect_equal(DynArray_len(dim3Instances), 2);
    });

    it("should get and return a number of  empty simplicies", ^{
      simplex_id newSimplex0 = instances_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex1 = instances_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex2 = instances_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex3 = instances_get_empty_simplex(disitt1, 3);
      simplex_id newSimplex4 = instances_get_empty_simplex(disitt1, 3);
      expect_equal(newSimplex0, 1);
      expect_equal(newSimplex1, 2);
      expect_equal(newSimplex2, 3);
      expect_equal(newSimplex3, 4);
      expect_equal(newSimplex4, 5);
      expect_equal(DynArray_len(disitt1->instances), 4);
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex0));
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex1));
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex2));
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex3));
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex4));
      DynArray *dim3Instances =
        *DynArray_getElementPtr(disitt1->instances, 3, DynArray*);
      expect_equal(DynArray_len(dim3Instances), 6);
      expect_equal(DynArray_elementSize(dim3Instances), DiSimplexObjSize(3));
      DiSimplexObj *newSimplex0Obj =
        DynArray_getElementPtr(dim3Instances, newSimplex0, DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 0);
      newSimplex0Obj->side[0] = 10;
      DiSimplexObj *newSimplex1Obj =
        DynArray_getElementPtr(dim3Instances, newSimplex1, DiSimplexObj);
      expect_equal(newSimplex1Obj->side[0], 0);
      newSimplex1Obj->side[0] = 10;
      //
      // return some simplicies
      //
      instances_return_simplex(disitt1, 3, newSimplex1);
      instances_return_simplex(disitt1, 3, newSimplex3);
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex0));
      expect_false(instances_simplex_exists(disitt1, 3, newSimplex1));
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex2));
      expect_false(instances_simplex_exists(disitt1, 3, newSimplex3));
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex4));
      dim3Instances =
        *DynArray_getElementPtr(disitt1->instances, 3, DynArray*);
      expect_equal(DynArray_len(dim3Instances), 6);
      newSimplex0Obj =
        DynArray_getElementPtr(dim3Instances, newSimplex0, DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 10);
      //
      // get some more simplicies (should reuse newSimplex1 and newSimplex3
      //
      newSimplex1 = instances_get_empty_simplex(disitt1, 3);
      newSimplex3 = instances_get_empty_simplex(disitt1, 3);
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex1));
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex3));
      dim3Instances =
        *DynArray_getElementPtr(disitt1->instances, 3, DynArray*);
      expect_equal(DynArray_len(dim3Instances), 6);
      newSimplex0Obj =
        DynArray_getElementPtr(dim3Instances, newSimplex0, DiSimplexObj);
      expect_equal(newSimplex0Obj->side[0], 10);
      newSimplex1Obj =
        DynArray_getElementPtr(dim3Instances, newSimplex1, DiSimplexObj);
      expect_equal(newSimplex1Obj->side[0], 0);
      //
      // get a new simplex (should be completely new)
      //
      expect_false(instances_simplex_exists(disitt1, 3, 6));
      simplex_id newSimplex5 = instances_get_empty_simplex(disitt1, 3);
      expect_equal(newSimplex5, 6);
      expect_true(instances_simplex_exists(disitt1, 3, newSimplex5));
      dim3Instances =
        *DynArray_getElementPtr(disitt1->instances, 3, DynArray*);
      expect_equal(DynArray_len(dim3Instances), 7);
    });

  });

  describe("storing/getting sides", ^{

    it("should be able to store and get sides", ^{
      simplex_id parentSimplexId = instances_get_empty_simplex(disitt1, 3);
      simplex_id childSimplexId  = instances_get_empty_simplex(disitt1, 2);
      simplex_store_side(disitt1, 3, parentSimplexId, 0, childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, 0), childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, 1), 0);
    });

    it("should do nothing if side is not part of simplex", ^{
      simplex_id parentSimplexId = instances_get_empty_simplex(disitt1, 3);
      simplex_id childSimplexId  = instances_get_empty_simplex(disitt1, 2);
      simplex_store_side(disitt1, 3, parentSimplexId, 10, childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, 10), 0);
      simplex_store_side(disitt1, 3, parentSimplexId, -1, childSimplexId);
      expect_equal(simplex_get_side(disitt1, 3, parentSimplexId, -1), 0);
    });

  });

  describe("universe simplicies", ^{

    it("should exist", ^{
      instances_ensure_dimension(disitt1, 5);
      expect_true(instances_simplex_exists(disitt1, 0, 0));
      expect_true(instances_simplex_exists(disitt1, 1, 0));
      expect_true(instances_simplex_exists(disitt1, 2, 0));
      expect_true(instances_simplex_exists(disitt1, 3, 0));
      expect_true(instances_simplex_exists(disitt1, 4, 0));
      expect_true(instances_simplex_exists(disitt1, 5, 0));
      expect_false(instances_simplex_exists(disitt1, 6, 0));
      expect_false(instances_simplex_exists(disitt1, 7, 0));
    });
  });

  fprintf(stdout, "\n");

  return 0;
}

