**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Sprint 003 Engine Semantics (Denotational, operational and axiomatic)](#sprint-003-engine-semantics-denotational-operational-and-axiomatic)
	- [Objectives](#objectives)
	- [Tasks](#tasks)
	- [Stories/Features](#storiesfeatures)
	- [Busted/RSpec specifications](#bustedrspec-specifications)
	- [Questions and Risks](#questions-and-risks)
		- [What does "fully abstract" mean for the DiSiTT engine?](#what-does-fully-abstract-mean-for-the-disitt-engine)
			- [Why are we *not* interested in using "game semantics"?](#why-are-we-not-interested-in-using-game-semantics)
			- [Researchers in computational semantics](#researchers-in-computational-semantics)
			- [Resources for computational semantics](#resources-for-computational-semantics)
			- [Resources for simplicial sturctures](#resources-for-simplicial-sturctures)
		- [What is the "size" of a constructive mathematics which allows for coalgebraicly defined (imprecise) reals?](#what-is-the-size-of-a-constructive-mathematics-which-allows-for-coalgebraicly-defined-imprecise-reals)
		- [Type theory](#type-theory)
	- [Wrap-up](#wrap-up)

# Sprint 003 Engine Semantics (Denotational, operational and axiomatic)

* overlaps with all 003 sprints
* Started: 2014/09/19

## Objectives

Our primary objective is to understand the semantic 
[*meaning*](http://en.wikipedia.org/wiki/Semantics_(computer_science)#Approaches) 
of the DiSiTT engine.

Our intent is to ensure that the 
[denotational](http://en.wikipedia.org/wiki/Denotational_semantics) 
semantics *is* the 
[operational](http://en.wikipedia.org/wiki/Operational_semantics) (and 
[axiomtic](http://en.wikipedia.org/wiki/Axiomatic_semantics)) 
semantics.  In computational semantics terms we want to ensure the 
engine's external syntax/operations are fully abstract.

It is critical to realize that the engine manipulates its own 
denotational meaning.  This makes it very important to carefully 
distinguish between the mathematical and meta-mathematical levels.

Another objective is to provide a deep understanding of the foundations 
of mathematics through the construction of causal structures.  This 
provides a very different understanding of what mathematics is "all 
about".  It should begin to answer the question of what time and space 
are.  In particular, it is important to question the deeply held bias 
of time/function in the roots of mathematics.

One aspect of this is that *construction* of causal structures is 
basic, while "classical" first order logic is actually an emergent 
"structure".

## Tasks

1. research semantics

## Stories/Features

## Busted/RSpec specifications

## Questions and Risks

### What does "fully abstract" mean for the DiSiTT engine?

What is the relationship between the denotational, operational and 
axiomatic semantics for the DiSiTT engine?

> In general one says that a denotational semantics is fully abstract 
> if contextual (operational) equivalence coincides with equality of 
> denotation. ( [Denotational 
> Semantics](http://www.cl.cam.ac.uk/%7Egw104/dens.pdf) page 71)

[Plotkin's LCF 
paper](http://homepages.inf.ed.ac.uk/gdp/publications/LCF.pdf) proved 
that, without parallel-or, PCF had "contextually equivalent terms with 
unequal denotations".

#### Why are we *not* interested in using "game semantics"?

Game semantics (see works by Hyland and Abramsky below), has been used 
to provide the full abstraction for the *sequential* component of 
Scott's LCF or Plotkin's PCF (PCF is the logical extension of LCF). 
Plotkin, in his, original analysis of the full abstraction for LCF, 
found that the denotational semantics forced non-sequentiality on the 
operational semantics. At the time LCF only had sequentical constructs.

Our **primary** interest in DiSiTT is to provide a new understanding of 
space-time. By forcing sequentiality through the use of game semantics, we 
are essentially continuing the deep mathematical bias towards time 
rather than space.

Similarly our primary goal, is to have the constructive component of 
DiSiTT *be* the denotational and operational semantics of the engine. 
A game semantics overlay on DiSiTT is *not* the theory we are looking 
for.

#### Researchers in computational semantics

* [Samson Abramsky](http://www.cs.ox.ac.uk/people/samson.abramsky/pubs.html)

* [J. Martin E. Hyland](https://www.dpmms.cam.ac.uk/~martin/) 
([publications](https://www.dpmms.cam.ac.uk/~martin/Research/research.html))

* [Gordon Plotkin](http://homepages.inf.ed.ac.uk/gdp/publications/)

 * [LCF Considered as a Programming 
Language](http://homepages.inf.ed.ac.uk/gdp/publications/LCF.pdf)

 * [A Structural Approach to Operational 
Semantics](http://homepages.inf.ed.ac.uk/gdp/publications/SOS.ps)

 * [Logical Full Abstraction and PCF 
](http://homepages.inf.ed.ac.uk/gdp/publications/Log_Full_Abs.pdf)

* [Glynn Winskel](http://www.cl.cam.ac.uk/~gw104/)

 * [The Formal Semantics of Programming Languages: An 
Introduction](http://mitpress.mit.edu/books/formal-semantics-programming-languages)

 * [Denotational Semantics](http://www.cl.cam.ac.uk/%7Egw104/dens.pdf)

* [David Schmidt](http://people.cis.ksu.edu/~schmidt/)

 * [Denotational Semantics: A Methodology for Language 
Development](http://people.cis.ksu.edu/~schmidt/text/densem.html)

* [Prakash Panangaden](http://www.cs.mcgill.ca/~prakash/)

 * [Bisimulation for Labelled Markov 
Processes](http://www.cs.mcgill.ca/~prakash/Pubs/j-markov.ps)

#### Resources for computational semantics

* [Denotational Semantics - Cambridge part II 
course](http://www.cl.cam.ac.uk/teaching/1314/DenotSem/materials.html)

* [Specification and Verification I - Cambridge part II 
course](http://www.cl.cam.ac.uk/~mjcg/Lectures/SpecVer1/SpecVer1.html)

* [Haskell/Denotational 
semantics](http://en.wikibooks.org/wiki/Haskell/Denotational_semantics) 
in particular [Strict and Non-Strict Semantics == lazy 
evaluation](http://en.wikibooks.org/wiki/Haskell/Denotational_semantics#Strict_and_Non-Strict_Semantics)

* [Function-level 
programming](http://en.wikipedia.org/wiki/Function-level_programming) 
is an example of a non-Lisp, non-ML, non-Haskell functional type of 
language. See John Backus' 1977 Turing award lecture [Can Programming 
Be Liberated from the von Neumann Style? A Functional Style and Its 
Algebra of 
Programs](http://web.stanford.edu/class/cs242/readings/backus.pdf) (and 
[Dijkstra's 
review](https://www.cs.utexas.edu/users/EWD/transcriptions/EWD06xx/EWD692.html)). 
See also [The FL Project: The Design of a Functional 
Language](http://theory.stanford.edu/~aiken/publications/trs/FLProject.pdf). 
The *most* ***important*** point is that FP/FL tries to build a *simple* 
functional language which has a specific Denotational model. 
Unfortunately it is a strcit rather than a lazy language, but many of 
the ideas are helpful in understanding the overall problem.

#### Resources for simplicial sturctures

* [An elementary illustrated introduction to simplicial sets](http://arxiv.org/abs/0809.4221).


### What is the "size" of a constructive mathematics which allows for coalgebraicly defined (imprecise) reals?

* [locally presentable 
category](http://ncatlab.org/nlab/show/locally+presentable+category)

* [accessible category 
](http://ncatlab.org/nlab/show/accessible+category)

* [ind-object](http://ncatlab.org/nlab/show/ind-object)

### Type theory

The DiSiTT engine was originally inspired by both Martin-Löf's 
Dependent Type theory and the more recent work on HoTT.

Good exposition of the original Dependent Type Theory can be found in 
either:

* [Type Theory and Functional Programming 
](https://www.cs.kent.ac.uk/people/staff/sjt/TTFP/)

* [Programming in Martin-Löf's Type 
Theory](http://www.cse.chalmers.se/research/group/logic/book/)

For the more recent [Homotopy Type Theory](http://homotopytypetheory.org/) see:

* [Homotopy Type Theory: Univalent Foundations of 
Mathematics](http://homotopytypetheory.org/book/)

## Wrap-up

None at the moment.
