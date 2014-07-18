**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [diSimplexEngine high-level goals](#disimplexengine-high-level-goals)
	- [Problem](#problem)
		- [diSimplex "Proof"](#disimplex-proof)
	- [Goals](#goals)
	- [Requirements](#requirements)

# diSimplexEngine high-level goals

## Problem

The diSimplexEngine was originally started to solve two distinctly 
different problems:

1. Provide objective tools to check mathematical proofs including all 
of Mathematical Physics.

1. Explore the concept of mathematical validity of any mathematical 
theory of reality which finite entities can experience.

That these two problems require the same solution, is, at first, 
surprising. If you had told me two years ago that this was even 
remotely possible, I would have told you it was misguided if not 
impossible.  In fact one of the results of the diSimplex project is to 
show that *all* of Mathematical Physics, and hence any Mathematical 
Science, is *constructively* mathematically valid.

However to show that Mathematical Sciences are *constructive*, we need 
to rethink a number of fundamental assumptions of the mathematical 
"world" over the past 150 years.  Firstly, we need to rethink the 
received assumption that the foundations of mathematics *rely* on 
"logic" and "set theory".  More importantly, we also need to rethink 
the "fact" that mathematical foundations must be not be 
"non-well-founded" and conversely must rely on the unrestricted use of 
the Axiom of Choice.

If we give up logic what does it *mean* to "prove" mathematical theory? 

What is "Truth"?

If we allow non-well-founded structures, aren't we forced to "prove" the 
various "liar" type paradoxes?

If we are not allowed to make use of the unrestricted Axiom of Choice, 
how can we prove anything remotely similar to Mathematical Analysis 
(which provides the foundations for all of Mathematical Physics)?

For a classically trained mathematician over the past 100 years, these 
very concepts are un-nerving and disorienting.  

### diSimplex "Proof"

To (re)define "proof" in a mathematical world in which we only have 
"constructions", we start with five concepts:

1. **examplar**: a "thing" or "object" which provides an *example* of 
an instance of some other "thing" or "object" or "concept".

1. **definitional objects**: an "object" which "defines" all examplars 
for a given mathematical concept. It is itself an examplar of some 
other definitional object (possibly itself).

1. **construction**: a definitional object whose examplars define how 
to construct one examplar from a collection of other examplars.

1. **complexity**: all examplars have an (ordinal) measure of their 
complexity.

1. **directed limit**: a collection of examplars is directed if there 
is a partial ordering of the collection in which "previous" examplars (with 
respect to the ordering) are embedded in "later" examplars.

We accept as mathematically (kappa) valid any examplar, definitional 
object, or construction which has an ordinal complexity, or bound of 
less than kappa or is the directed limit of examplars, definitional 
objects, or constructions which have complexity or bounds less than 
kappa.

## Goals

Our primary goal for the diSimplexEngine is to provide implementations 
of the above 5 concepts using directed simplicial structures.

## Requirements

> Define/implement directed simplicial structures.

> Define/implement an examplar object.

> Define/implement a definitional object.

> Define/implement a construction object (both examplars and 
> definitional versions).

> Define/implement a measure of complexity.

> Define/implement the concept of embedding one directed simplicial 
> structure "inside" another directed simplicial structure.

> Define/implement the concept of partial order.

> Define/implment directed limits of directed simplicial structures.
