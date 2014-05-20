package org.disimplextheory;

import org.disimplextheory.Ordinal._

abstract class Ordinal {
  def ==(that: Ordinal) : Boolean
  def <(that: Ordinal) : Boolean
  def >(that: Ordinal) : Boolean = !(this < that)
  def +(that: Ordinal) : Ordinal
}

case class Zero() extends Ordinal {
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => true
    case Natural(thatNat) => (0 == thatNat)
    case LargeOrdinal(thatNat, thatOmega) =>
      (zero == thatOmega) && (0 == thatNat)
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (0 < thatNat)
    case LargeOrdinal(thatNat, thatOmega) => 
      if (zero < thatOmega) true
      else (0 < thatNat)
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => zero
    case Natural(_) => that
    case LargeOrdinal(_, _) => that
  }
}

case class Natural(nat: Int) extends Ordinal {
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => (this.nat == 0)
    case Natural(thatNat) => (this.nat == thatNat)
    case LargeOrdinal(thatNat, thatOmega) =>
      (zero == thatOmega) && (this.nat == thatNat)
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (this.nat < thatNat)
    case LargeOrdinal(thatNat, thatOmega) => 
      if (zero < thatOmega) true
      else if (thatOmega < zero) false
      else (this.nat < thatNat)
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => this
    case Natural(thatNat) => new Natural(this.nat + thatNat)
    case LargeOrdinal(thatNat, thatOmega) =>
      if (zero < thatOmega) that
      else new Natural(this.nat + thatNat)
  }
}

case class LargeOrdinal(nat: Int, omega: Ordinal) extends Ordinal {
  def ==(that: Ordinal) : Boolean = that match {
    case Zero() => (this.omega == zero) && (this.nat == 0)
    case Natural(thatNat) => (this.omega == zero) && (this.nat == thatNat)
    case LargeOrdinal(thatNat, thatOmega) =>
      (this.omega == thatOmega) && (this.nat == thatNat)
  }
  def <(that: Ordinal) : Boolean = that match {
    case Zero() => false
    case Natural(thatNat) => (this.nat < thatNat)
    case LargeOrdinal(thatNat, thatOmega) => 
      if (this.omega < thatOmega) true
      else if (thatOmega < this.omega) false
      else (this.nat < thatNat)
  }
  def +(that: Ordinal) : Ordinal = that match {
    case Zero() => this
    case Natural(thatNat) => new LargeOrdinal(this.nat+thatNat, this.omega)
    case LargeOrdinal(thatNat, thatOmega) =>
      if (this.omega < thatOmega) that
      else if (thatOmega < this.omega) this
      else new LargeOrdinal(this.nat + thatNat, this.omega)
  }
}

object Ordinal {
  val zero = new Zero()
  val one  = new Natural(1)
  val two  = new Natural(2)
}

