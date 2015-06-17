# Lexer and Symbol table design

## Lexer

For the lexer we should consider [re2c](http://www.re2c.org/) for a 
statically produced lexer. See [The Gritty Details Of A Lexical 
analyzer In C Using 
re2c](http://support.triumph4php.com/2011/11/the-gritty-details-of-a-lexical-analyzer-in-c-using-re2c/) 
for a good tutorial/example.

Alternatively we should consider Russ Cox's [Implementing Regular 
Expressions](https://swtch.com/~rsc/regexp/) for MIT based code to 
simulate NFA/DFAs together with a simple (reduced) Regular Expression 
interpreter.

## Symbol table

If we want a symbol table to freeze each non-character token, we should 
consider either a [Trie](http://en.wikipedia.org/wiki/Trie) or 
(minimal)[DAFSA](http://en.wikipedia.org/wiki/Deterministic_acyclic_finite_state_automaton).

Some resources for DAFSAs:

* [Incremental Construction of Minimal Acyclic Finite-State 
Automata](http://www.mitpressjournals.org/doi/abs/10.1162/089120100561601)

* [Applications of Finite Automata Representing Large 
Vocabularies](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.56.5272) 
(see figure 7 page 12 and section 5.2).

Consider using ideas from 
[HAT-Tries](http://crpit.com/abstracts/CRPITV62Askitis.html) and see 
[dcjones/hat-trie](https://github.com/dcjones/hat-trie) for a BSD-like 
example implementation.

## Questions:

1. Do we need to allow user extension of the lexer? NO (so use re2c)

1. Do we need to freeze (symbolize) tokens?  YES (so use mDAFSA as 
described in section 5.2 of "Applications of Finite Automata 
Representing Large Vocabularies" together with an unsorted array of 
pointers to the symbolized strings.

## Implementation

We integrate symbolization, using the mDAFSA, into the actual lexer 
recognition process since they are both character by character 
analysis.
