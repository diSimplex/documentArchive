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

  fprintf(stdout, "\n>>>diSiTTCSpec\n\n");
  fprintf(stdout, "size of             int = %lu\n", (unsigned long)sizeof(int));
  fprintf(stdout, "size of     dimension_t = %lu\n", (unsigned long)sizeof(dimension_t));
  fprintf(stdout, "size of      simplex_id = %lu\n", (unsigned long)sizeof(simplex_id));
  fprintf(stdout, "size of           void* = %lu\n", (unsigned long)sizeof(void*));
  fprintf(stdout, "size of          DiSiTT = %lu\n", (unsigned long)sizeof(DiSiTT));
  fprintf(stdout, "size of    DiSimplexObj = %lu",   (unsigned long)sizeof(DiSimplexObj));
  fprintf(stdout, "   + (dimension + 1)*sizeof(int)\n");
  fprintf(stdout, "size of DiSimplexObj(1) = %lu\n",  (unsigned long)DiSimplexObjSize(1));
  fprintf(stdout, "size of    DiSimplexRef = %lu\n", (unsigned long)sizeof(DiSimplexRef));
  fprintf(stdout, "\n");

  describe("DiSiTT engine", ^{

    it("should have empty DynArray structures (before use)", ^{
      expect_equal(DynArray_len(disitt0->emptySimplicies), 0);
      expect_equal(DynArray_len(disitt0->simplicies), 0);
      expect_equal(DynArray_len(disitt0->emptyStructures), 0);
      expect_equal(DynArray_len(disitt0->structures), 1);
      DiStructureRef initialStructure;
      diStructureRef_init(&initialStructure, disitt0, 0);
      expect_true(diStructure_exists(&initialStructure));
    });

    it("should have empty DynArray structures (after diSiTT_ensure_dimension)", ^{
      expect_equal(DynArray_len(disitt0->emptySimplicies), 0);
      expect_equal(DynArray_len(disitt0->simplicies), 0);
      expect_equal(DynArray_len(disitt0->emptyStructures), 0);
      expect_equal(DynArray_len(disitt0->structures), 1);
      DiStructureRef initialStructure;
      diStructureRef_init(&initialStructure, disitt0, 0);
      expect_true(diStructure_exists(&initialStructure));
      diSiTT_ensure_dimension(disitt0, 60);
      expect_equal(DynArray_len(disitt0->emptySimplicies), 61);
      expect_equal(DynArray_len(disitt0->simplicies), 61);

      // walk through each dimension and check the icd...
      int i = 52;
      for(; i < 61; i++) {
        DynArray *dimSimplicies =
          *DynArray_getElementPtr(disitt0->simplicies, i, DynArray*);
        expect_equal(DynArray_len(dimSimplicies), 1);
        refute_equal(DynArray_capacity(dimSimplicies), 0);
        expect_equal(DynArray_elementSize(dimSimplicies), DiSimplexObjSize(i));
      }
    });

  });

  fprintf(stdout, "\n");

  return 0;
}

