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
  dse_init_disitt(disitt0);
  disitt1 = &disittObj1;
  dse_init_disitt(disitt1);

  fprintf(stdout, "\n>>>diSiTTCSpec\n\n");
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

    it("should have empty DynArray structures (after diSiTT_ensure_dimension)", ^{
      expect_equal(DynArray_len(disitt0->emptySimplicies), 0);
      expect_equal(DynArray_len(disitt0->instances), 0);
      diSiTT_ensure_dimension(disitt0, 60);
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

  fprintf(stdout, "\n");

  return 0;
}

