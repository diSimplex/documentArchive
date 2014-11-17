**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Sprint 003 Engine syntax](#sprint-003-engine-syntax)
	- [Objectives](#objectives)
	- [Tasks](#tasks)
	- [Stories/Features](#storiesfeatures)
	- [Busted/RSpec specifications](#bustedrspec-specifications)
	- [Questions and Risks](#questions-and-risks)
		- [Researchers](#researchers)
			- [Reflections](#reflections)
		- [Other resources](#other-resources)
	- [Wrap-up](#wrap-up)

# Sprint 003 Engine syntax

* overlaps with all 003 sprints
* Started: 2014/09/26 

## Objectives

Our primary objective is to provide DiSiTT engine (Lua) resources with 
which to write DiSiTT programs.

A secondary objective (related to the LaTeX syntax) is to understand 
the modular structure of the DiSiTT language. In particular how will 
users extend the DiSiTT language.

Through the previous work (in this sprint), I have come to realize that 
the diSimplexEngine is essentially a project in showing that 
Mathematics ***is*** all about ***computation***.

The semantics of the diSimplexEngine is provided by the collection of 
diSimplicial structures (diStructures), that is by the functor 
category: [ \Delta, \Universe ], the functors from \Delta to the 
\Universe.  It is critical here that $\Universe \isomorphic_to [ 
\Delta, \Universe ]$, that is, that \Universe is the largest fixed 
point by the co-algebraic operator [ \Delta, \Universe ], and that 
identity is defined by the largest (identity) bisimularity associated 
with this co-algebraic operator.

These diSimplicial structures simultaneously represent data and 
process. Data and computation. The fundamental theory of diSimplicial 
computation is provided by diStructure transform (the diStructure 
extension of graph transforms).

"Constructive" mathematics ***is*** the closure of the finitely 
computable component of \Universe. (The rest of) "Mathematics" is the 
potentially non-finite computable (similar to Turing-oracles) "rest" of 
the \Universe. Part of this project is to show that, using (classically 
non-well-founded) co-algebraic reasoning, Mathematical Physics/Science 
is contained in the "Constructive" components of mathematics.

In fact the "Rest of (Classical) Mathematics" is almost certainly 
meta-computable. That is, classical mathematics has finitely 
specifiable (co-algebraic) definitions, which can be computed with at a 
meta-mathematical or meta-meta-....-mathematical level (though almost 
certainly not at the "mathematical level").

To implement this vision, we need to define an ***extensible*** 
diStructure computational langauge. This will take a number of forms. 
It is critical that a diStructure ***can*** be ***interpreted*** as a 
computational algorithm in its own-right. However we will also need a 
textural language with which to construct diStructures and their 
algorithms. The "base" textural language will most appropriately be 
written in Lua or a language defined by a Lua based parser (since we 
have nominally decided that Lua will be the base computational 
environment). However an alternate textural language ***must*** be 
provided in LaTeX to enable its use in general mathematical writting.

## Tasks

## Stories/Features

## Busted/RSpec specifications

## Questions and Risks

### Researchers

* [Detlef Plump](http://www-users.cs.york.ac.uk/~det/papers.html)

 * [The York Abstract Machine 
(YAM)](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.06.p
df)

 * [The GP Programming 
System](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.08.
pdf)

 * [The Graph Programming Language 
GP](http://www.cs.york.ac.uk/plasma/publications/pdf/Plump.CAI.09.pdf)

 * [The Semantics of Graph 
Programs](http://www.cs.york.ac.uk/plasma/publications/pdf/PlumpSteinert.RULE.0
9.pdf).

 * [The Design of GP 
2](http://www.cs.york.ac.uk/plasma/publications/pdf/Plump.WRS.11.pdf)

 * [Double pushout graph transformation 
revisited](http://www-users.cs.york.ac.uk/%7Edet/Papers/mscs.01.pdf)

 * [Verifying Monadic Second-Order Properties of Graph 
Programs](http://www.cs.york.ac.uk/plasma/publications/pdf/PoskittPlump.ICGT.14
.pdf)

 * [Relabelling in Graph 
Transformation](http://www-users.cs.york.ac.uk/%7Edet/Papers/icgt.02.pdf).

 * [M,N-Adhesive Transformation 
Systems](http://www.cs.york.ac.uk/plasma/publications/pdf/HabelPlump.12a.pdf) 
covers graph transformations with relabelling (which will be important 
for our work).

* [Medha Shukla Sarkar](http://www.mtsu.edu/~msarkar/)

 * Ph.D. thesis [GXL - A Graph Transformation Language with Scoping and 
Graph 
Parameters](http://research.cs.queensu.ca/~cordy/Papers/TAGT98_GXL.pdf) 
(co-supervised between [Dorothea 
Blostein](http://research.cs.queensu.ca/~blostein/) and Jim Cordy) 
importantly this is based upon a mixture of (double push-out) graph 
transforms, Haskell, and the syntax of the [TXL programming 
language](http://www.txl.ca/)

* [Jim Cordy](http://research.cs.queensu.ca/home/cordy/papers.html)

 * [TXL programming language](http://www.txl.ca/) (see also wikipedia's 
entry [TXL (programming 
language)](http://en.wikipedia.org/wiki/TXL_%28programming_language%29)).

 * [TXL Documents](http://www.txl.ca/ndocs.html).

 * [The TXL Programming Language, Version 
10.6](http://www.txl.ca/docs/TXL106ProgLang.pdf)

* [D Wagellar](http://www.micallefwagelaar.be/dennis/doku.php/start)

 * [Towards a General Composition Semantics for Rule-Based Model 
Transformation](http://soft.vub.ac.be/Publications/2011/vub-soft-tr-11-07.pdf). 
Defines 
[simpleGT](https://code.google.com/a/eclipselabs.org/p/simplegt/) which 
is an interesting syntax for a Graph transform language with rule and 
module inheritance.

#### Reflections 

* The GP programming system has a *very* clean syntax which would map 
nicely to a diStructure.

* The GXL has an interesting overview of how TXL, Haskell and DPO graph 
transforms can be used together.

* The TXL has a very nice syntax which has similarities to Haskell but 
might be easier to use/parse (though is slightly wordier than Haskell). 
In particular it has explicit (algebraic) constructors and 
(co-algebraic) deconstructors. It also has explicit "failure" 
conditions based solely on graph matching. These failure conditions can 
be used as explicit NAC conditions.

* The simpleGT syntax has interesting rule and module inheritance.

### Other resources

* [Available transformation 
languages](http://en.wikipedia.org/wiki/Model_transformation_language#Available_transformation_languages).

## Wrap-up

None at the moment.
