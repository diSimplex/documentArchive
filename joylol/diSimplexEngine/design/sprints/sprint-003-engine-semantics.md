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
		- [Computation via Graph Transforms](#computation-via-graph-transforms)
			- [Researchers](#researchers)
			- [Approach](#approach)
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

### Computation via Graph Transforms

We use computation via a diStructure generalization of Graph 
Transforms.  We use the diStructure generalization of the double 
pushout setup, see: [Algebraic Approaches to Graph Transformation, Part 
I: Basic Concepts and Double Pushout 
Approach](http://compass2.di.unipi.it/TR/files/TR-96-17.ps.gz)

(See also the second chapter: [Algebraic approaches to graph 
transformation. Part II: single pushout approach and comparison with 
double pushout approach](http://dl.acm.org/citation.cfm?id=278930). In 
particular both chapters read together, in their analysis of causal 
orders and parallelism theories, suggest reasons for the space-time we 
experience being 3+1 dimensions.)

We model our work closely on that of the work done by the Programming 
Languages and Systems (sub)group run by [Detlef 
Plump](http://www-users.cs.york.ac.uk/~det/) at the University of York 
in the UK ([PLASMA's GP 
subgroup](http://www.cs.york.ac.uk/plasma/wiki/index.php?title=GP_%28Graph_Programs%29)).  
The [York Abstract Machine 
(YAM)](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.06.pdf) 
and its associated [The GP Programming 
System](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.08.pdf) 
are particularly important to our work.

One particularly important facet of this work are the various different 
approaches to the subgraph isomorphism problem:

* [An Optimization Technique for Subgraph Matching 
Strategies](http://www.info.uni-karlsruhe.de/papers/TR_2006_7.pdf) 
provides a very good overview of the work of Dörr extended by Batz to 
include graphical query cost heuristics.

* section 4.1 of [The GP Programming 
System](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.08.pdf) 
provides a useful simplification of Batz's work which might be useful 
to keep in mind.

* [Messmer and Bunke's paper "Efficient subgraph isomorphism detection: 
A decomposition 
approach"](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.318.8651) 
This is a RETE like approach to the Subgraph Isomorphism problem.

#### Researchers

* [Detlef Plump](http://www-users.cs.york.ac.uk/~det/papers.html)

 * [The York Abstract Machine 
(YAM)](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.06.pdf)

 * [The GP Programming 
System](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.08.pdf)

 * [The Graph Programming Language 
GP](http://www.cs.york.ac.uk/plasma/publications/pdf/Plump.CAI.09.pdf)

 * [The Semantics of Graph 
Programs](http://www.cs.york.ac.uk/plasma/publications/pdf/PlumpSteinert.RULE.09.pdf).

 * [The Design of GP 
2](http://www.cs.york.ac.uk/plasma/publications/pdf/Plump.WRS.11.pdf)

 * [Double pushout graph transformation 
revisited](http://www-users.cs.york.ac.uk/%7Edet/Papers/mscs.01.pdf)

 * [Verifying Monadic Second-Order Properties of Graph 
Programs](http://www.cs.york.ac.uk/plasma/publications/pdf/PoskittPlump.ICGT.14.pdf)

 * [Relabelling in Graph 
Transformation](http://www-users.cs.york.ac.uk/%7Edet/Papers/icgt.02.pdf).

 * [M,N-Adhesive Transformation 
Systems](http://www.cs.york.ac.uk/plasma/publications/pdf/HabelPlump.12a.pdf) 
covers graph transformations with relabelling (which will be important 
for our work).

* [Annegret Habel 
](http://formale-sprachen.informatik.uni-oldenburg.de/persons/annegret.habel/eindex.html#publications)

* [Pawel Sobocinski](http://users.ecs.soton.ac.uk/ps/) (see his work on 
Adhesive categories as well as Van Kempen theories).

* [Steve Lack](http://maths.mq.edu.au/~slack/papers.html) (again see 
his work on Adhesive categories).


#### Approach

We use a structure inspired by that of the YAM (figure 2 section 2 page 
234(4) of [The York Abstract Machine 
(YAM)](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.06.pdf)):

* the **diStructure** which is **being transformed/constructed**.

* a **choice stack** which is used both to hold the 
macro-choices as to which diStructure transform to appy, *as well as*, 
to hold the micro-choices associated with the substructure isomorphism 
identification (tranformation match) problem.

* a corresponding **diStructure change stack**.

* a **(local) "data" stack**.  In our case all labels are themselves 
diStructures, so the contents of the data stack are a collection of 
currently partially built diStructures.

The base commands of our diStructure machine come from roughly the same 
categories of commands as those used by the YAM:

* **Data stack commands**

* **Control instructions**, which delimit rules, explicitly represent 
choices or mark deterministic sections of code.  Note that [The Design 
of GP 
2](http://www.cs.york.ac.uk/plasma/publications/pdf/Plump.WRS.11.pdf) 
changed the commands which control the choice stack to allow for a more 
nuanced collection of backtracking behaviours.


* **diStructure query instructions** Our collection of diStructure 
queries will be our generalization of Batz's lookup and extension 
commands.  Node lookup will be the same, but we need a vastly increased 
collection of "extension" commands which will come from the maps which 
underly the diStructure's functorial structure maps.

* **diStructure modification instructions** Our collection of 
diStructure modification instructions will, again, come from the maps 
which underly the diStructure's functorial structure maps. GP/GP2 has 
an associated graph editing graphical user interface. Higher-order 
diStructures can by definition (of our human limitations) not have any 
such graphical user interface. This means that modifications must take 
place using a textual interface, essentially providing ordered lists of 
diSimplicies which are interpreted as higher order simplicies. In our 
context, any concept of "order" will require 1-diSimplicial structures.

Our ultimate goal to be able to interpret diStructures as either a 
"data" structure, **or** as "program" description depending upon the 
context. This is important for, for example, infinite diStructures 
which represent process traces which are lazily unfolded as and when 
needed.  For this we need to consider the GP/GP2 programming constructs:

* non-deterministic **collections** of transforms to be applied 
(non-deterministically) once.

* deterministic **sequences** of transforms applied one at a time in sequence.

* **repetitive application** of a (set of) transform(s)

* if/then (GP) or try (GP/GP2) **choice** of one of two transforms 
depending on whether or not a conditional transform applies.

A. Habel and D. Plump in [Computational Completeness of Programming 
Languages Based on Graph 
Transformation](http://www-users.cs.york.ac.uk/%7Edet/Papers/fossacs.01.pdf) 
show that the above programming constructs are [Turing 
complete](http://en.wikipedia.org/wiki/Turing_completeness). However *do 
we really need the choice constructs, or can we get Turing completeness 
using failure backtracking alone?*

The GP/GP2 "complier" translates a collection of graph transforms into 
(more) optimal sequences of graph query commands using heuristics set 
out in section 4.1 of [The GP Programming 
System](http://www.cs.york.ac.uk/plasma/publications/pdf/ManningPlumpGT-VMT.08.pdf). 
Alternatively Batz finds minimal spanning arborescences of the Plan 
graph, see sections 7.1 and 7.2 of [An Optimization Technique for 
Subgraph Matching 
Strategies](http://www.info.uni-karlsruhe.de/papers/TR_2006_7.pdf).

Quite often we will be "applying" specific transforms by providing 
initial partial matches. This suggests that instead of solving the full 
substructure isomorphims problem we really need to solve a substructure 
isomorphism extension problem. To do this we probably need to solve the 
minimal spanning tree *extension* problem. In addition, whenever we 
need to do an unrestricted node search, we should proceed by 
potentially matching nodes closest to the existing substructure first.  
As well, to accommodate possible infinite limit structures, we might 
consider matching higher-order diSimplicies rather than just 
0-diSimplicies (of which there might be inifinite numbers).

## Wrap-up

None at the moment.
