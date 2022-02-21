**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Sprint 002 first computations](#sprint-002-first-computations)
	- [Tasks](#tasks)
	- [Stories/Features](#storiesfeatures)
	- [Busted/RSpec specifications](#bustedrspec-specifications)
	- [Questions and Risks](#questions-and-risks)
		- [Simplicial identity](#simplicial-identity)
			- [Are these names globally or only locally unique?](#are-these-names-globally-or-only-locally-unique)
		- [Simplicial structures](#simplicial-structures)
			- [How do we "locate" a simplex in the simplicial structure?](#how-do-we-locate-a-simplex-in-the-simplicial-structure)
			- [How do we "locate" the simplicial structures which "use" a given simplex?](#how-do-we-locate-the-simplicial-structures-which-use-a-given-simplex)
		- [What is a "variable"?](#what-is-a-variable)
	- [Wrap-up](#wrap-up)

# Sprint 002 first computations

* Started: 2014/07/18
* Paused: 2014/08/08  
* Restarted: 2014/09/01
* Ended: 2014/09/19

## Tasks

1. Start building simple simplicial structures complete with the 
universe.

1. Explore the theory of definitional objects defined by (open?) 
covers. Focus on the simplicial structure of an (open?) cover.

1. Understand the simplicial structure of a (bi)similarity.

1. Explore patterns build out of definitional objects as the base of 
Jacob's (logical) fibrations.

1. Start exploring syntax and semantics of computation in DiSiTT 
(delayed).

## Stories/Features

## Busted/RSpec specifications

## Questions and Risks

### Simplicial identity

The "identity" of an individual simplex is "globally" unique within a 
specific computational infrastructure, but has no meaning outside of a 
given computational infrastructure. That is, a simplex is only 
identifiable inside a specific calculation.

Plato's playground version of the "universe" requires an "axiom of 
plentatude" (see \cite{barwiseMoss1996viciousCircles}). A potential 
version *we* could use is to assume there is a 0-simplex for each 
ordinal.  If we use this version of the axiom of plentatude, then we 
must build both the ordinals *and* the universe simultaneously.

The ordinal used to "name" a 0-simplex in the axiom of plentatude is 
merely accidental. However since it is unique within a specific 
calculation, it does provide a (part of) a unique "name" or idendity 
for a 0-simplex in a give computational infrastructure.

If we assume there is a 0-simplex for each ordinal as our axiom of 
plentatude, we effectively have globally numbered all 0-simplicies and 
by extension (since there is a unique "unnamed" simplex for each 
ordered collection of 0-simplex) all simplicies *inside a given 
computational infrastructure*.

However this is not quite correct, since we can have more than one 
simplex associated with any ordered collection of 0-simplicies.  This 
means that higher dimensional simplicies may have externally chosen 
identities (names, numbers). 

#### Are these names globally or only locally unique?

All simplicies are additionally named by their "type" which functions 
like a class in a typcial OO language.  This "type" points to a simplex 
of the same dimension, in the examplar's definitional object.

### Simplicial structures

In a given computational infrastructure, a given simplex may 
participate in many simplicial structures.

#### How do we "locate" a simplex in the simplicial structure?

#### How do we "locate" the simplicial structures which "use" a given simplex?

Simplicial structures should have a "now" point.  That is they should 
be pointed. This forms the equivilant of the root of a tree in 
classical functional languages.

### What is a "variable"?

See: http://en.wikipedia.org/wiki/Variable_%28mathematics%29

In our use, variables are merely parameters of a particular part of the 
computation. See the discussion just after Lemma 1.6.6 on page 69 of 
\cite{jacobs1999catLogic}. 

As such they are used to structure the fibration of the "logic" over 
the base category.

## Wrap-up

Essentially sketched basic structure of engine.

Worked on a number of distinctly unrelated projects, which required 
repeated restarts, which provided distinct distractions.

The current work has transitioned to a study of the underlying 
mathematical *meaning* of what is being constructed.

**So** this work is transitioning to sprint-003.

