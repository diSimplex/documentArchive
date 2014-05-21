package org.disimplextheory;

import org.scalatest.WordSpec

class OrdinalSpec extends DiSiTTSpec {

  val zero   = Ordinal.zero
  val one    = Ordinal.one
  val two    = Ordinal.two
  val omega1 = Ordinal.omega1
  val omega2 = Ordinal.omega2
  val omegaPlusOne = LargeOrdinal(1, one)
  
  "An Ordinal" when {
    
    "Zero" should {
      "correctly suc" in {
        assert(zero.suc.isInstanceOf[Natural])
      }
      
      "correctly omega" in {
        assert(zero.omega.isInstanceOf[Zero])
      }
      
      "correctly ==" in {
        assert(zero == zero)
        assert(zero == Natural(0))
        assert(zero == LargeOrdinal(0, zero))
        assert(zero != one)
        assert(zero != omega1)
        assert(zero != zero.suc)
        assert(zero == zero.omega)
      }
      
      "correctly <" in {
        assert(zero < one)
        assert(zero < omega1)
        assert(zero < zero.suc)
      }
      
      "correctly +" in {
        assert(zero == (zero + zero))
        assert(one  == (zero + one))
        assert(omega1 == (zero + omega1))
      }
      
      "correctly *" in {
        assert(zero == (zero * zero))
        assert(zero == (zero * one))
        assert(zero == (zero * omega1))
      }
    }
    
    "Natural" should {
      "correctly apply" in {
        assert(Natural(0).isInstanceOf[Zero])
        assert(Natural(1).isInstanceOf[Natural])
      }
      
      "correctly suc" in {
        assert(one.suc.isInstanceOf[Natural])
      }
      
      "correctly omega" in {
        assert(one.omega.isInstanceOf[LargeOrdinal])
      }
      
      "correctly ==" in {
        assert(one == one)
        assert(one == Natural(1))
        assert(one == zero.suc)
        assert(one == LargeOrdinal(1, zero))
        assert(one == zero.suc)
        assert(one != zero)
        assert(one != omega1)
      }

      "correctly +" in {
        assert(one == (one + zero))
        assert(two == (one + one))
        assert(omega1 == (one + omega1))
      }
      
      "correctly *" in {
        assert(zero == (one * zero))
        assert(one  == (one * one))
        assert(two  == (one * two))
        assert(Natural(4) == (two * two))
        assert(omega1 == (one * omega1))
        assert(omega2 == (one * omega2))
        assert(omega1 == (two * omega1)) // CHECK
      }
    }
    
    "LargeOrdinal" should {
      "correctly apply" in {
        assert(LargeOrdinal(0,zero).isInstanceOf[Zero])
        assert(LargeOrdinal(1,zero).isInstanceOf[Natural])
        assert(LargeOrdinal(0,one).isInstanceOf[LargeOrdinal])
      }
      
      "correctly ==" in {
        assert(omega1 == LargeOrdinal(0, one))
        assert(omegaPlusOne == LargeOrdinal(1, one))
        assert(omega1 == one.omega)
        assert(omegaPlusOne == omega1.suc)
        assert(omega1 != zero)
        assert(omega1 != one)
        assert(omega1 == omega1)
        assert(omega1 != omega1.suc)
      }
      
      "correctly +" in {
        assert(omega1 == (omega1 + zero))
        assert(omegaPlusOne == (omega1 + one))
        assert(omega1 == (one + omega1))
        assert(omega2 == (omega1 + omega1))
      }
      
      "correctly *" in {
        assert(zero == (omega1 * zero))
        assert(omega1 == (omega1 * one))
        // TODO expand!
      }
    }
  }
    
}
