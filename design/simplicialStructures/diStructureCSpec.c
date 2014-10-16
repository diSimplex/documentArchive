#include <stdio.h>

#include <cbdd.h>

#include <diSimplexEngine/dynArray.c>
#include <diSimplexEngine/diSiTT.c>
#include <diSimplexEngine/diSimplex.c>
#include <diSimplexEngine/diStructure.c>

DiSiTT  disittObj0, disittObj1;
DiSiTT *disitt0,   *disitt1;

int main() {

  // setup our DiSiTT engine(s)
  disitt0 = &disittObj0;
  diSiTT_init(disitt0);
  disitt1 = &disittObj1;
  diSiTT_init(disitt1);

  fprintf(stdout, "\n>>>diStructureCSpec\n\n");

  describe("diStructures", ^{

    it("should get and return some empty structures", ^{
      DiStructureRef newStructure0;
      diStructureRef_init(&newStructure0, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure0));
      expect_true(newStructure0.diSiTT == disitt0);
      expect_equal(newStructure0.structure, 0);
      expect_true(diStructure_exists(&newStructure0));
      DiStructureRef newStructure1;
      diStructureRef_init(&newStructure1, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure1));
      expect_true(newStructure1.diSiTT == disitt0);
      expect_equal(newStructure1.structure, 1);
      expect_true(diStructure_exists(&newStructure1));
    });

    it("diStructures should be properly formed (before use)", ^{
      DiStructureRef newStructure0;
      diStructureRef_init(&newStructure0, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure0));
      expect_true(newStructure0.diSiTT == disitt0);
      expect_equal(newStructure0.structure, 2);
      expect_true(diStructure_exists(&newStructure0));
      DiStructureObj *structureObj =
        DynArray_getElementPtr(disitt0->structures,
                               newStructure0.structure,
                               DiStructureObj);
      expect_true(structureObj->dimensions != 0);
      expect_equal(DynArray_len(structureObj->dimensions), 0);
      expect_true(structureObj->curSimplex.diSiTT == disitt0);
      expect_equal(structureObj->curSimplex.dimension, 0);
      expect_equal(structureObj->curSimplex.simplex, 0);
      expect_true(structureObj->flags && DISITT_DISTRUCTURE_INUSE);
    });

    it("should have empty DynArray structures (after diStructure_ensure_dimension_exists)", ^{
      DiStructureRef newStructure0;
      diStructureRef_init(&newStructure0, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure0));
      expect_true(newStructure0.diSiTT == disitt0);
      expect_equal(newStructure0.structure, 3);
      expect_true(diStructure_exists(&newStructure0));
      DiStructureObj *structureObj =
        DynArray_getElementPtr(disitt0->structures,
                               newStructure0.structure,
                               DiStructureObj);
      expect_true(structureObj->dimensions != 0);
      expect_equal(DynArray_len(structureObj->dimensions), 0);
      diStructure_ensure_dimension_exists(structureObj, 10);
      expect_equal(DynArray_len(structureObj->dimensions), 11);

      for(int i = 0; i < 11; i++) {
        DynArray *simplicies =
          *DynArray_getElementPtr(structureObj->dimensions, i, DynArray*);
        expect_equal(DynArray_len(simplicies), 0);
      }
    });

    it("should have non-empty DynArray structures (after adding a simplex)", ^{
      DiStructureRef newStructure0;
      diStructureRef_init(&newStructure0, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure0));
      expect_true(newStructure0.diSiTT == disitt0);
      expect_equal(newStructure0.structure, 4);
      expect_true(diStructure_exists(&newStructure0));
      DiStructureObj *structureObj =
        DynArray_getElementPtr(disitt0->structures,
                               newStructure0.structure,
                               DiStructureObj);
      expect_true(structureObj->dimensions != 0);
      expect_equal(DynArray_len(structureObj->dimensions), 0);
      DiSimplexRef newSimplex;
      diSimplexRef_init(&newSimplex, disitt0, 0, 0);
      diSimplex_get_empty(&newSimplex);
      expect_equal(newSimplex.simplex, 1);
      diStructure_add(&newStructure0, &newSimplex);
      expect_equal(DynArray_len(structureObj->dimensions), 1);
      DynArray *simplicies =
        *DynArray_getElementPtr(structureObj->dimensions, 0, DynArray*);
      expect_equal(DynArray_len(simplicies), 1);
      expect_equal(diStructure_size(&newStructure0, 0), 1);
      fprintf(stdout, "  TODO: test with higher dimensional simplicies\n");
      fprintf(stdout, "  TODO: to ensure all lower dimensional simplicies are added as well\n");
    });

    it("should be able to release and reobtain diStructures", ^{
      DiStructureRef structure0;
      diStructureRef_init(&structure0, disitt0, 0);
      expect_true(diStructure_exists(&structure0));
      DiStructureRef structure1;
      diStructureRef_init(&structure1, disitt0, 1);
      expect_true(diStructure_exists(&structure1));
      DiStructureRef structure2;
      diStructureRef_init(&structure2, disitt0, 2);
      expect_true(diStructure_exists(&structure2));
      DiStructureRef structure3;
      diStructureRef_init(&structure3, disitt0, 3);
      expect_true(diStructure_exists(&structure3));
      DiStructureRef structure4;
      diStructureRef_init(&structure4, disitt0, 4);
      expect_true(diStructure_exists(&structure4));
      DiStructureRef structure5;
      diStructureRef_init(&structure5, disitt0, 5);
      expect_false(diStructure_exists(&structure5));
      expect_true(diStructure_release(&structure3));
      expect_false(diStructure_exists(&structure3));
      expect_true(diStructure_release(&structure2));
      expect_false(diStructure_exists(&structure2));
      DiStructureRef newStructure2;
      diStructureRef_init(&newStructure2, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure2));
      expect_equal(newStructure2.structure, 2);
      DiStructureRef newStructure3;
      diStructureRef_init(&newStructure3, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure3));
      expect_equal(newStructure3.structure, 3);
      DiStructureRef newStructure5;
      diStructureRef_init(&newStructure5, disitt0, 0);
      expect_true(diStructure_get_empty(&newStructure5));
      expect_equal(newStructure5.structure, 5);
    });


  });

  fprintf(stdout, "\n");

  return 0;
}

