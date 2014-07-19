**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Sprint 002 first computations](#sprint-002-first-computations)
	- [Tasks](#tasks)
	- [Stories/Features](#storiesfeatures)
	- [Busted/RSpec specifications](#bustedrspec-specifications)
	- [Questions and Risks](#questions-and-risks)
	- [Wrap-up](#wrap-up)

# Sprint 002 first computations

* Started: 2014/07/18
* Ends: 2014/07/25

## Tasks

1. Start exploring syntax and semantics of computation in DiSiTT

## Stories/Features

## Busted/RSpec specifications

## Questions and Risks

### Are simplicies "numbered" globally or locally?

Plato's playground version of the "universe" requires an "axiom of 
plentatude" (see \cite{barwiseMoss1996viciousCircles}). A potential 
version *we* could use is to assume there is a 0-simplex for each 
ordinal.  If we use this version of the axiom of plentatude, then we 
must build both the ordinals *and* the universe simultaneously.

BUT if we use this version of the axiom of plentatude, we effectively 
have globally numbered all 0-simplicies and by extension (since there 
is a unique "unnamed" simplex for each ordered collection of 0-simplex) 
all simplicies.

However this is not quite correct, since we can have more than one 
simplex associated with any ordered collection of 0-simplicies.  This 
means that higher dimensional simplicies have externally chosen 
identities (names, numbers). Should these names be globally or only 
locally unique?

Can we have more than one 0-simplex with the same ordinal?  What does 
this mean?

How do we "locate" a simplex in the simplicial structure?

Simplicial structures should have a "now" point.  That is they should 
be pointed. This forms the equivilant of the root of a tree in 
classical functional languages.

All simplicies are additionally named by their "type" which functions 
like a class in a typcial OO language.  This "type" points to a simplex 
of the same dimension, in the examplar's definitional object.

## Wrap-up

None at the moment.
