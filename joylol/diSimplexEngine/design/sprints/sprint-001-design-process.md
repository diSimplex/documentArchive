**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Sprint 001 starting up the design process](#sprint-001-starting-up-the-design-process)
	- [Tasks](#tasks)
	- [Stories/Features](#storiesfeatures)
	- [Busted/RSpec specifications](#bustedrspec-specifications)
	- [Questions and Risks](#questions-and-risks)
		- [What does "proof" mean in diSimplex Type Theory?](#what-does-proof-mean-in-disimplex-type-theory)
		- [Building the MetaTheory](#building-the-metatheory)
	- [Wrap-up](#wrap-up)

# Sprint 001 starting up the design process

* Started: 2014/07/11
* Completed: 2014/07/18

## Tasks

1. build GripPlus tool to help drive design process using simple 
markdown, Busted, Lua, RSpec, and Ruby files.

1. understand what it means to "prove" mathematics without classical 
logic.

1. develop design of [Cunnian](https://github.com/fandianpf/cunnian) 
([development version](https://github.com/stephengaito/cunnian)) as the 
bridge between [FandianPF](https://github.com/fandianpf/fandianpf) 
([development version](https://github.com/stephengaito/fandianpf)) and 
diSimplex projects.  (The design of Cunnian will place requirements on 
both FandianPF and diSimplex which each project might not require 
individually).

1. develop design of diSimplexEngine enough to be able to construct a 
single examplar.

## Stories/Features

A mathematician (who understands Lua scripting) wants to construct an 
1-simplicial examplar.

## Busted/RSpec specifications

* simplicialStructures/oneSimplicialStructuresUSpec.lua

## Questions and Risks

### What does "proof" mean in diSimplex Type Theory?

**Problem**: (taken from design/goals)

To show that Mathematical Sciences are constructive, we need to rethink 
a number of fundamental assumptions of the mathematical "world" over 
the past 150 years. Firstly, we need to rethink the received assumption 
that the foundations of mathematics rely on "logic" and "set theory". 
More importantly, we also need to rethink the "fact" that mathematical 
foundations must be not be "non-well-founded" and conversely must rely 
on the unrestricted use of the Axiom of Choice.

If we give up logic what does it mean to "prove" mathematical theory?

What is "Truth"?

If we allow non-well-founded structures, aren't we forced to "prove" 
the various "liar" type paradoxes?

If we are not allowed to make use of the unrestricted Axiom of Choice, 
how can we prove anything remotely similar to Mathematical Analysis 
(which provides the foundations for all of Mathematical Physics)?

For a classically trained mathematician over the past 100 years, these 
very concepts are un-nerving and disorienting.

To (re)define "proof" in a mathematical world in which we only have 
"constructions", we start with five concepts:

1. **examplar**: a "thing" or "object" which provides an example of an 
instance of some other "thing" or "object" or "concept".

1. **definitional objects**: an "object" which "defines" all examplars 
for a given mathematical concept. It is itself an examplar of some 
other definitional object (possibly itself).

1. **construction**: a definitional object whose examplars define how 
to construct one examplar from a collection of other examplars.

1. **complexity**: all examplars have an (ordinal) measure of their 
complexity.

1. **directed limit**: a collection of examplars is directed if there 
is a partial ordering of the collection in which "previous" examplars 
(with respect to the ordering) are embedded in "later" examplars.

We accept as mathematically (kappa) valid any examplar, definitional 
object, or construction which has an ordinal complexity, or bound of 
less than kappa or is the directed limit of examplars, definitional 
objects, or constructions which have complexity or bounds less than 
kappa.

### Building the MetaTheory

The metaTheory of 1-simplicial structures is much simpler than that of 
kappa-simplicial structures (for 1 < kappa).  In fact the 
kappa-metaTheory requires that of the 1-metaTheory, so we should start 
by developing the Lua/C interface using 1-simplicial structures, and 
then redevelop the Lua/C library for the more general kappa-simplicial 
structures.

## Wrap-up

* Built GripPlus to make it easier to do Readme Driven Development ;-)

* Sketched out design, in both diSimplexEngine as well as Cunnian.

* Integrated and started using Lua/Busted as the Lua version of RSpec

* fleshed out simplicialStructures/oneSimplicialStructuresUSpec.lua

* Begun thinking about what computation looks like in DiSitt.

* Begun thinking about what "computational lanugage" should look like.

* Begun thinking about how DiSitt is probably best fibred a.la. Jacobs

A very disjointed sprint, but a good start.

