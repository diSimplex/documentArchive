package org.disimplextheory;

import org.scalatest.WordSpec

class DiSimplexSpec extends DiSiTTSpec {

  "A DiSimplex" when {
    "empty" should {
      "have size -1" in {
        var disis = new DiSimplex()
        disis.n shouldBe -1
      }
    }

    "it contains only one face" should {
      "be a Seq and have size 0" in {
        var disis0 = new DiSimplex()
        var disis1 = new DiSimplex(disis0)
        disis1.n shouldBe 0
        disis1.faces shouldBe a [Seq[_]]
        disis1.faces should contain (disis0)
      }
    }
    
    "it contains two faces" should {
      "be a Seq and have size 1" in {
        var disis0 = new DiSimplex()
        var disis1 = new DiSimplex()
        var disis2 = new DiSimplex(disis0, disis1)
        disis2.n shouldBe 1
        disis2.faces shouldBe a [Seq[_]]
        disis2.faces should contain (disis0)
        disis2.faces should contain (disis1)
      }
    }
  }
}