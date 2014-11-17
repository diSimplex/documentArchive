**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Sprint 003 Engine syntax -- first attempt (retired)](#sprint-003-engine-syntax----first-attempt-retired)
	- [Objectives](#objectives)
	- [Tasks](#tasks)
	- [Stories/Features](#storiesfeatures)
	- [Busted/RSpec specifications](#bustedrspec-specifications)
	- [Questions and Risks](#questions-and-risks)
		- [What syntax will be used for the DiSiTT engine?](#what-syntax-will-be-used-for-the-disitt-engine)
		- [What is the mapping between the natural deduction and haskell syntax?](#what-is-the-mapping-between-the-natural-deduction-and-haskell-syntax)
		- [Why does Haskell not have a begin/end like block to contain local variables?](#why-does-haskell-not-have-a-beginend-like-block-to-contain-local-variables)
		- [What is the meaning of an individual rule?](#what-is-the-meaning-of-an-individual-rule)
		- [How are groups of rules related versus haskell's pattern matching?](#how-are-groups-of-rules-related-versus-haskell's-pattern-matching)
		- [What are "definitional" "objects"?](#what-are-definitional-objects)
	- [Wrap-up](#wrap-up)

# Sprint 003 Engine syntax -- first attempt (retired)

* overlaps with all 003 sprints
* Started: 2014/09/26 

## Objectives

Our primary objective is to provide DiSiTT engine (Lua) resources with 
which to write DiSiTT programs.

A secondary objective (related to the LaTeX syntax) is to understand 
the modular structure of the DiSiTT language. In particular how will 
users extend the DiSiTT language.

## Tasks

## Stories/Features

## Busted/RSpec specifications

## Questions and Risks

### What syntax will be used for the DiSiTT engine?

We will primarily base the *syntax* of the DiSiTT engine on the similar 
syntax of [HoTT](http://homotopytypetheory.org/book/), in particular 
the "second" (more formal) presentation of the [natural 
deduction](http://en.wikipedia.org/wiki/Natural_deduction) based syntax 
found in the appendix A.2.

We will also base the *syntax* of the DiSiTT engine on the 
"classical" development of the internal langauge of a Topos (this is 
essentially a proof of the "full abstractness" of the *internal* 
*language* of Toposes). A good exposition of this can be found in 
chapter 3 of J. L. Bell's book [Toposes and Local Set 
Theories](http://store.doverpublications.com/0486462862.html). (See 
also [J Lambek's 
review](http://projecteuclid.org/euclid.bams/1183555325)).

Note that in both cases we do *not* make use of, or define, any 
*infinite* first order logic.

The syntax of the DiSiTT language is also inspired by that of 
[Haskell](http://www.haskell.org) and 
[Agda](http://wiki.portal.chalmers.se/agda/pmwiki.php).

### What is the mapping between the natural deduction and haskell syntax?

The haskell syntax depends heavily on pattern matching.  For the 
natural deduction style, pattern matching is "*essentially*" the 
judgement context.

Alternatively the contexts (across all judegements) provides what is 
essentially the collection of local variables used in a given 
judegment, while the premises of a rule provide the pattern matching.

### Why does Haskell not have a begin/end like block to contain local variables?

Haskell certainly has "where" and "let" "blocks" which introduce local 
"variables". Note that Haskell values are immutable, Haskell variables 
can change reference but the values they contain can not be "changed".

### What is the meaning of an individual rule?

A given rule corresponds to a *directed* simplex between 
*configurations* as objects.  

How does this correspond to (or get "mapped down to") the structure of 
the simplicies in the configurations?

What are the "*sides*" of a given rule's *directed* simplex?

In Jacobs' analysis of [Categorical Logic and Type 
Theory](http://www.cs.ru.nl/B.Jacobs/CLT/bookinfo.html) for many 
"logics" the premises are assumed to be replaceable by the product 
("and-ing") of the individual premises. However since the product is 
(usually) symmetric, this leads to an undirected (or symmetric) 
simplex. Note that the underlying logic for dependent types *is* 
directed. How does [linear 
logic](http://en.wikipedia.org/wiki/Linear_logic) fit into this scheme?

### How are groups of rules related versus haskell's pattern matching?

### What are "definitional" "objects"?

I strongly suspect that what I want to mean by "definitional" "object" 
are essentially Ehresmann's 
[*sketches*](http://ncatlab.org/nlab/show/sketch). We will base our use 
of sketches on the books [Locally Presentable and Accessible 
Categories](http://ebooks.cambridge.org/ebook.jsf?bid=CBO9780511600579) 
or [Accessible categories: The foundations of categorical model 
theory](http://www.ams.org/books/conm/104/)

However, how do we "construct" a sketch?

## Wrap-up

None at the moment.
