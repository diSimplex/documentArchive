package org.disimplextheory;

import org.disimplextheory.Ordinal._

abstract class Ordinal {
  def suc() : Ordinal
  def omega() : Ordinal
  def ==(that: Ordinal) : Boolean
  def !=(that: Ordinal) : Boolean = !(this == that)
  def <(that: Ordinal) : Boolean
  def >(that: Ordinal) : Boolean = !(this < that) && !(this == that)
  def +(that: Ordinal) : Ordinal
}

case class Zero() extends Ordinal {
  def suc() = new Natural(1)
  def omega() = zero
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => true
    case Natural(thatNat) => (0 == thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      (zero == thatLimitOrd) && (0 == thatNat)
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (0 < thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) => 
      if (zero < thatLimitOrd) true
      else (0 < thatNat)
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => zero
    case Natural(_) => that
    case LargeOrdinal(_, _) => that
  }
}

case class Natural protected(nat: Int) extends Ordinal {
  def suc() = new Natural(this.nat+1)
  def omega() = new LargeOrdinal(0, this)
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => (this.nat == 0)
    case Natural(thatNat) => (this.nat == thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      (zero == thatLimitOrd) && (this.nat == thatNat)
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (this.nat < thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) => 
      if (zero < thatLimitOrd) true
      else if (thatLimitOrd < zero) false
      else (this.nat < thatNat)
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => this
    case Natural(thatNat) => new Natural(this.nat + thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      if (zero < thatLimitOrd) that
      else new Natural(this.nat + thatNat)
  }
}

case class LargeOrdinal protected(nat: Int, limitOrd: Ordinal) extends Ordinal {
  def suc() = new LargeOrdinal(this.nat+1, this.limitOrd)
  def omega() = new LargeOrdinal(0, this)
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => (this.limitOrd == zero) && (this.nat == 0)
    case Natural(thatNat) => (this.limitOrd == zero) && (this.nat == thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      (this.limitOrd == thatLimitOrd) && (this.nat == thatNat)
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (this.nat < thatNat)
    case LargeOrdinal(thatNat, thatLimitOrd) => 
      if (this.limitOrd < thatLimitOrd) true
      else if (thatLimitOrd < this.limitOrd) false
      else (this.nat < thatNat)
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => this
    case Natural(thatNat) => new LargeOrdinal(this.nat+thatNat, this.limitOrd)
    case LargeOrdinal(thatNat, thatLimitOrd) =>
      if (this.limitOrd < thatLimitOrd) that
      else if (thatLimitOrd < this.limitOrd) this
      else new LargeOrdinal(this.nat + thatNat, this.limitOrd)
  }
}

object Ordinal {
  def Ordinal(aNat: Int, anOrdinal: Ordinal) = 
    if (anOrdinal == zero) {
      if (aNat == 0) zero
      else new Natural(aNat)
    } else new LargeOrdinal(aNat, anOrdinal)

  val zero = new Zero()
  val one  = new Natural(1)
  val two  = new Natural(2)
}

