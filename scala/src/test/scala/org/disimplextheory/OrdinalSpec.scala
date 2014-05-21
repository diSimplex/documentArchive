package org.disimplextheory;

import org.scalatest.WordSpec

class OrdinalSpec extends DiSiTTSpec {

  val zero = Ordinal.zero
  val one  = Ordinal.one
  
  "An Ordinal" when {
    
    "zero" should {
      "be equal to Natural(0) or LargeOrdinal(0, zero)" in {
        assert(zero == Natural(0))
        assert(zero == LargeOrdinal(0, zero))
      }
    }
    
    "one" should {
      "be equal to Natural(1) or LargeOrdinal(1, zero)" in {
        assert(one == Natural(1))
        assert(one == zero.suc)
        assert(one == LargeOrdinal(1, zero))
        assert(one == (zero + one))
        assert(one != zero)
      }
    }
  }
    
}
