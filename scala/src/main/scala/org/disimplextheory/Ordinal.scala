package org.disimplextheory;

import org.disimplextheory.Ordinal._

/* 
 * We use a factory pattern to ensure that there is NO overlap between 
 * Ordinal case types. To do this we make the Natural and LargeOrdinal
 * case class primary constructors private. This means that the Natural
 * and LargeOrdinal companion classes need a factory (via the "apply" 
 * method) to create the correct case class.
 */
 
// We use this PrivateOrdinal trait to dis-ambiguate overloaded apply
// methods so that we can have private case constructors.
// see: http://stackoverflow.com/questions/20030826/scala-case-class-private-constructor-but-public-apply-method/20031500#20031500
trait PrivateOrdinal

abstract class Ordinal {
  def suc() : Ordinal
  def omega() : Ordinal
  def ==(that: Ordinal) : Boolean
  def !=(that: Ordinal) : Boolean = !(this == that)
  def <(that: Ordinal) : Boolean
  def >(that: Ordinal) : Boolean = !(this < that) && !(this == that)
  def +(that: Ordinal) : Ordinal
  def *(that: Ordinal) : Ordinal
}

case class Zero() extends Ordinal {
  def suc() = Natural(1)
  def omega() = zero
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => true
    case Natural(_) => false
    case LargeOrdinal(_, _) => false
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => true
    case LargeOrdinal(thatNat, thatLimitOrd) => true 
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => zero
    case Natural(_) => that
    case LargeOrdinal(_, _) => that
  }
  def *(that: Ordinal) : Ordinal = zero
}

case class Natural private(nat: Int with PrivateOrdinal) extends Ordinal {
  def suc() = Natural(this.nat+1)
  def omega() = LargeOrdinal(0, this)
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (this.nat == thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) => false
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (this.nat < thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) => true 
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => this
    case Natural(thatNat) => Natural(this.nat + thatNat)
    case LargeOrdinal(_, _) => that
  }
  def *(that: Ordinal) : Ordinal = that match {
    case Zero() => zero
    case Natural(thatNat) => Natural(this.nat * thatNat)
    case LargeOrdinal(_, _) => that
  }
}

case class LargeOrdinal protected(nat: Int with PrivateOrdinal,
                                  limitOrd: Ordinal) extends Ordinal {
  def suc() = LargeOrdinal(this.nat+1, this.limitOrd)
  def omega() = LargeOrdinal(0, this)
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => false
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      (this.limitOrd == thatLimitOrd) && (this.nat == thatNat)
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => false
    case LargeOrdinal(thatNat, thatLimitOrd) => 
      if (this.limitOrd < thatLimitOrd) true
      else if (thatLimitOrd < this.limitOrd) false
      else (this.nat < thatNat)
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => this
    case Natural(thatNat) => LargeOrdinal(this.nat+thatNat, this.limitOrd)
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      if (this.limitOrd < thatLimitOrd) that
      else if (thatLimitOrd < this.limitOrd) this
      else LargeOrdinal(this.nat + thatNat, 
                        this.limitOrd + thatLimitOrd)
  }
  def *(that: Ordinal) : Ordinal = that match {
    case Zero() => zero
    case Natural(thatNat) => LargeOrdinal(this.nat * thatNat, 
                                          this.limitOrd * that)
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      LargeOrdinal(0,zero) // TODO this is wrong!
  }
}

object Ordinal {
  val zero   = new Zero()
  val one    = Natural(1)
  val two    = Natural(2)
  val omega1 = LargeOrdinal(0, one)
  val omega2 = LargeOrdinal(0, two) 
}

object Natural {
  def apply(aNat: Int) : Ordinal = 
    if (aNat == 0) zero
    else new Natural(aNat.asInstanceOf[Int with PrivateOrdinal])
}

object LargeOrdinal {
  def apply(aNat: Int, anOrdinal: Ordinal) : Ordinal = 
    if (anOrdinal == zero) Natural(aNat)
    else new LargeOrdinal(aNat.asInstanceOf[Int with PrivateOrdinal], 
                          anOrdinal)
}

