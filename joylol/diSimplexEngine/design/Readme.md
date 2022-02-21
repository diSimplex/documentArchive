**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Overview of design process](#overview-of-design-process)
- [RSpec specification testing](#rspec-specification-testing)
- [Organisation of the design artefacts](#organisation-of-the-design-artefacts)
- [Thanks](#thanks)
- [ToDo](#todo)

# Overview of design process

We use our slightly modified version of Behavioural Driven Development 
([BDD](http://en.wikipedia.org/wiki/Behavior-driven_development)) 
paradigm. A good introduction to BDD can be found in the "[The RSpec 
Book](http://pragprog.com/book/achbd/the-rspec-book)".

The RSpec book champions the use of a two cycle development process. 
The outer (external behaviour) and inner (implementation behaviour) 
developmental cycles.

This process starts by specifying the external behaviour of the 
application by writing (testable) RSpec specifications for this 
behaviour. Once these external specifications fail due to an 
"implementation level" problem we drop down to the inner or 
implementation level cycle and write some RSpec specifications as we 
develop our understanding of the implementation level details.

I am an ardent believer in the usefulness of RSpec.  RSpec is all about 
writing *testable* (behavioural) **specifications**.  The most 
important word here is (behavioural) "specification" (which happen to 
also be testable).  The RSpec specifications should not be tests which 
happen to provide a cobbled together "specification" (after the fact). 
The *behavioural* specification comes first and foremost.

I am also an ardent believer in the use of Yardoc to expose a 
consistent documentation of the code.  We use yard-rspec to ensure the 
RSpec specifications are an integral part of the code documentation.

While the RSpec book champions the use of Cucumber, for various reasons 
we do not use Cucumber.  Instead we use RSpec together with the 
non-Cucumber parts of Aruba and Capybara to test the external behaviour 
of our application. 

One of the short comings, in my use of Cucumber, was that I was seeing 
the features as a bag of things, and not as a coherent model of the 
external behaviour of the application. To deal with this I believe, 
there is a need for an model of the overall system in which the 
application is used as a part.  This external model should have objects 
corresponding to the primary users, deployment platforms, and "things" 
the primary users see as important.  This external model will have many 
of the aspects of a proper domain model.  However the external model's 
domain objects (which will be repeated in the internal/implementation 
model) will effectively capture the end user's expectations of these 
notional object's external behaviour (and not the internal behaviour 
required to **implement** the application).

To be as Agile as possible we use (roughly) [weekly sprint 
cycles](sprints/Readme.md).

# RSpec specification testing

> "Happy families are all alike; every unhappy family is unhappy in its 
> own way." (Leo Tolstoy -- Anna Karenina )

While the primary aim of an RSpec specification is to provide a 
coherent *specification* of the behaviour of the application, the 
inherent run-ability of the RSpec specifications *as* *tests* is *very* 
*useful* to help keep the application and its code base stable.

There are three primary types of tests which are important.

1. Integration tests against a stable application instance. (Happy 
application startup path integration tests).

1. Integration tests against a potentially unstable application 
scenario. (Unhappy application startup path integration tests).

1. Unit tests against distinct parts of the application. (No 
application needs to be running).

As with Anna Karenina, while the integration tests against a stable 
application instance should all be able to use the same instance, the 
integration tests against the potentially unstable application 
scenarios, will each need a different instance to test against.

Using a combination of Rake (to orchestrate the startup of the 
application) and RSpec (to provide the specification tests), we can 
provide (semi-)automatic testing of all aspects of the application.

We use a fixed file naming convention to distinguish these three 
different types of RSpec specifications:

1. All stable application (integration) test specifications end in 
*ISpec.rb

1. All (potentially) unstable application (integration) test 
specifications end in *ASpec.rb

1. All unit test specifications end in *USpec.rb.

Any given RSpec specification may or may not have [ordered example 
groups or 
examples](http://mettadore.com/analysis/using-rspec-with-mixed-random-and-ordered-tests/). 
The (potentially) unstable application (integration) tests are almost 
certainly going to have ordered example groups as well as ordered 
examples.

# Organisation of the design artefacts

All RSpec specifications are contained in files whose name ends in 
"xSpec.rb" (where "x" is one of "I", "A", and "U").

The RSpec specifications which specify the features of the external 
behaviour are located in the design/features directory.

Discussion of the problems, goals, requirements and (high-level) 
solutions to the design of the external behaviour of the application 
will be found in appropriate Markdown files (*.md) located in 
(sub)directories of the design/goals directory.

Discussion of the (implementational) architecture will be found in 
appropriate Markdown files (*.md) located in (sub)directories of the 
design/architecture directory.

The RSpec specifications which specify the internal or implementation 
behaviour are located in an appropriate (sub)directories of the 
design/implemenation directory.

The goals capture the external behaviour which is critical to an end 
user's *use* of the application. The architecture captures the external 
behaviour which is critical to day to day operational *deployment* of 
the application. The implementation captures the internal behaviour 
which allows the application to "work".

The details of each sprint plan will be found in the "sprints" 
directory.

Finally, arbitrary Ruby files found under the design directory are 
either implementations of the external behavioural model, or support 
for the actual RSpec testing infrastructure.  Ruby files which provide 
general support code will be found in the design/support directory.

# Thanks

While I have been for a while dissatisfied by my use of Cucumber's 
feature specifications, and felt a need for what I am now calling an 
"external behavioural model", it was 
[nu7hatch](https://github.com/nu7hatch)'s [Nothing really 
matters](http://areyoufuckingcoding.me/2012/03/25/nothing-really-matters/) 
post that "kicked" me into changing things.  While this post is 
provocative, nu7hatch has good things to say.

[Steve Klabnik](http://steveklabnik.com/)'s post [BDD with Rspec and 
Steak](http://timelessrepo.com/bdd-with-rspec-and-steak) provides a 
good example of the use of RSpec specifications for external behaviour.

We will try to use the [Better Specs](http://betterspecs.org/) examples 
to improve our RSpec specifications.

# ToDo

Consider using SimpleCov to look at "test"/"specification" coverage.

Use Dependency Injection to allow mocking of Ruby Classes and/or Ruby 
scripts.
