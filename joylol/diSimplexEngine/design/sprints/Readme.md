**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Overview of sprint planning process.](#overview-of-sprint-planning-process)
- [Relationship with FandianPF and Cunnian projects](#relationship-with-fandianpf-and-cunnian-projects)

# Overview of sprint planning process.

We work in 
[sprints](http://en.wikipedia.org/wiki/Scrum_(development)#Sprint) of 
multiples of single weeks (depending upon how difficult the next most 
important story turns out to be).

We use one or more files in the backlog directory to collect our 
current collection of potential Cucumber features.

For each sprint we move one or more story/feature from our backlog 
to an appropriate subdirectory of the features directory.

For each sprint we have one file (in Markdown format) which records the 
feature titles to be tackled in that sprint, together with some 
overview of the difficulty or risks anticipated or observed.

Since we are using Behaviour Driven Development using Busted/RSpec, 
each story is developed into one or more Busted/RSpec specifications of 
the "features" (located in the design/features directory) representing 
the external model's behaviour . Each sprint file records the features 
worked on during that sprint.

While working on a given feature we will need to write a number of 
Busted/RSpec specifications for the behaviour of various parts of the 
implementation. These implementation level Busted/RSpec specifications 
will be located in an appropriate subdirectory of the design directory.
Each sprint file will also record the implementation level Busted/RSpec 
specifications worked on during that sprint.

# Relationship with FandianPF and Cunnian projects

The [Cunnian project](https://github.com/fandianpf/cunnian) 
([development version](https://github.com/stephengaito/cunnian)) 
provides a bridge between the 
[FandianPF](https://github.com/fandianpf/fandianpf) ([development 
version](https://github.com/stephengaito/fandianpf)) and the diSimplex 
projects.

