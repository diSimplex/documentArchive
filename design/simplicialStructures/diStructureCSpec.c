#include <stdio.h>

#include <cbdd.h>

#include <diSimplexEngine/dynArray.c>
#include <diSimplexEngine/diSiTT.c>
#include <diSimplexEngine/diSimplex.c>
#include <diSimplexEngine/diStructure.c>

DiSiTT  disittObj0, disittObj1;
DiSiTT *disitt0,   *disitt1;
DiSimplexRef  diSimplexObj0, diSimplexObj1;
DiSimplexRef *diSimplex0,   *diSimplex1;
DiStructureObj  diStructureObj0, diStructureObj1;
DiStructureObj *diStructure0,   *diStructure1;

int main() {

  // setup our DiSiTT engine(s)
  disitt0 = &disittObj0;
  dse_init_disitt(disitt0);
  disitt1 = &disittObj1;
  dse_init_disitt(disitt1);
  diSimplex0 = &diSimplexObj0;
  diSimplex0->diSiTT = disitt0;
  diSimplex0->dimension = 0;
  diSimplex0->simplex   = 0;
  diSimplex1 = &diSimplexObj1;
  diSimplex1->diSiTT = disitt1;
  diSimplex1->dimension = 0;
  diSimplex1->simplex   = 0;
  diStructure0 = &diStructureObj0;
  diStructure_init(diStructure0, disitt0);
  diStructure1 = &diStructureObj1;
  diStructure_init(diStructure1, disitt1);

  fprintf(stdout, "\n>>>diStructureCSpec\n\n");

  describe("diStructures", ^{

    it("should have empty DynArray structures (before use)", ^{
      expect_true(diStructure0->diSiTT == disitt0);
      expect_equal(DynArray_len(diStructure0->dimensions), 0);
      expect_true(diStructure0->curSimplex.diSiTT == disitt0);
      expect_equal(diStructure0->curSimplex.dimension, 0);
      expect_equal(diStructure0->curSimplex.simplex, 0);
    });

    it("should have empty DynArray structures (after diStructure_ensure_dimension_exists)", ^{
      expect_equal(DynArray_len(diStructure0->dimensions), 0);
      diStructure_ensure_dimension_exists(diStructure0, 10);
      expect_equal(DynArray_len(diStructure0->dimensions), 11);

      for(int i = 0; i < 11; i++) {
        DynArray *simplicies =
          *DynArray_getElementPtr(diStructure0->dimensions, i, DynArray*);
        expect_equal(DynArray_len(simplicies), 0);
      }
    });

    it("should have non-empty DynArray structures (after adding a simplex)", ^{
      expect_equal(DynArray_len(diStructure1->dimensions), 0);
      diStructure_add(diStructure1, diSimplex1);
      expect_equal(DynArray_len(diStructure1->dimensions), 1);
      DynArray *simplicies =
        *DynArray_getElementPtr(diStructure1->dimensions, 0, DynArray*);
      expect_equal(DynArray_len(simplicies), 1);
    });

  });

  fprintf(stdout, "\n");

  return 0;
}

