package org.disimplextheory.mutable

class DiSimplex ( facesC: DiSimplex* ) {

  val n : Int = facesC.length - 1
  val faces : Seq[DiSimplex] = facesC
  
}