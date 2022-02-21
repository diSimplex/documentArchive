What am I doing?

??

Mathematics is all about computation.... the "classical" "logic" 
"proof" is the Axiomatic semantical "proof" of the correctness of a 
given computation.

The denotation of mathematics is the co-algebraic universe of 
disimplicial structures (Plato's universe).

The goal of our tool is to verify the axiomatic semanitcal correctness 
of a given computation.

The axiomatic logical language is the co-algebraic substructure 
language (see Jacob's book ..)

I need an **extensible** language. Which means that I need to design an 
**extensible** lexer/parser. Do I need to extend the lexer? Yes as a 
"simple" (ordered?) collection of regular expressions.

How do we extend the parser rules?

Given that mathematical notation is highly (geometrically?) structured, 
how do we provide extensibility? Base the parser on LaTeX? Do we need 
pluggable layout engines to be able to "display" the diSimplicial 
strctures (well the low "dimensional" ones).

TeX as a macro processor is essentially the extensible language I 
should "use".

However, the use of exclusively TeX makes the "programming" tedious (as 
raw TeX can be rather verbose). So we want a hybrid approach, some 
hard-wired(?) "programming" language for "most" of the work, with the 
ability to escape into an extension language. Possibly this might be by 
recompiling the compiler?
