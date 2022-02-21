**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Problem bin.. things for potential possible use](#problem-bin-things-for-potential-possible-use)
	- [Immutable structure sharing](#immutable-structure-sharing)
	- [Garbage collection](#garbage-collection)

# Problem bin.. things for potential possible use

## Immutable structure sharing

Most functional languages have immutable structures, some implement 
techniques to be able to share structures so that computational 
space/time can be saved instead of copying the complete (large) 
structure.

At some point we will need to implement structure sharing.

However all (current) functional languages are essentiall 1-dimensional 
and work on lists or trees. In this case structure sharing can be 
fairly easily implemented using path copying.

See:

* http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey 
Rich is the authour of Clojure which implements both immutable 
structures (with structure sharing) as well as strict 
identity/reference-value concurrency control

* http://en.wikipedia.org/wiki/Persistent_data_structure

* http://en.wikipedia.org/wiki/Multiversion_concurrency_control

Our (potential) problem is our structures are NOT tree like. Though we 
might have semi-cannonical access via "tree-like-sub-structures".

Wikipedia's article suggests there are two general approaches, 
"fat/version-nodes" and "path copying". 

WE could mandate one consistent tree structure through our directed 
simplicial structures, and then use fat nodes for any cyclical paths.  
Alternatively, maybe, we could have multiple overlapping tree 
structures which together uniquely "cover" a simplicial structure to 
which we could path copy inside each tree to obtain our "new simplicial 
structure".

Note that Rich Hickey implies that *shallow* trees are important to the 
efficiency of the path-copying approach.

Another approach might be to look at: [Functional Programming with 
Structured 
Graphs](https://www.cs.utexas.edu/~wcook/Drafts/2012/graphs.pdf)

Yet another approach is suggested by http://stackoverflow.com/a/1659082 
or the thesis: http://www.cs.cmu.edu/~rwh/theses/okasaki.pdf

This is the result of a google search for "functional programming 
structure sharing"


## Garbage collection

If I do implement parts of any directed simplicial structure in C code, 
then I will need to program both memory management and garbage 
collection. Since this C code might become a library which might be 
wrapped for both Ruby and PHP, I need to ensure the memory management 
and garbage collection are fairly simple and light weight.
