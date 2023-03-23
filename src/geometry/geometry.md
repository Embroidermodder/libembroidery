# Geometry and Algorithms

## To Do

\todo (Arduino) Fix emb-outline files

\todo (Arduino)Fix thread-color files

\todo (Arduino) Logging of Last Stitch Location to External USB Storage(commonly available and easily replaced) ...wait until TRE is available to avoid rework

\todo (Arduino) inotool.org - seems like the logical solution for Nightly/CI builds

\todo (Arduino) Smoothieboard experiments

\todo (testing) looping test that reads 10 times while running valgrind. See \texttt{embPattern\_loadExternalColorFile()} Arduino leak note for more info.

## Development

If you wish to develop with us you can chat via the contact email
on the [website]\url{https://libembroidery.org} or in the issues tab on the
[github page]\url{https://github.com/Embroidermodder/Embroidermodder/issues}.
People have been polite and friendly in these conversations and I (Robin)
have really enjoyed them.
If we do have any arguments please note we have a
[Code of Conduct] CODE\_OF\_CONDUCT.md so there is a consistent policy to
enforce when dealing with these arguments.

The first thing you should try is building from source using the [build advice](build)
above. Then read some of the [manual] \url{https://libembroidery.org/embroidermodder_2.0_manual.pdf} to get the general
layout of the source code and what we are currently planning.

## Testing

To find unfixed errors run the tests by launching from the command line with:

    $ embroidermodder --test

then dig through the output. It's currently not worth reporting the errors, since
there are so many but if you can fix anything reported here you can submit a PR.

## Contributing

### Funding

The easiest way to help is to fund development (see the Donate button above),
since we can't afford to spend a lot of time developing and only have limited
kit to test out libembroidery on.

### Programming and Engineering

Should you want to get into the code itself:

*  Low level C developers are be needed for the base library `libembroidery`.
*  Low level assembly programmers are needed for translating some of `libembroidery` to `EmbroiderBot`.
*  Hardware Engineers to help design our own kitbashed embroidery machine `EmbroiderBot`, one of the original project aims in 2013.
*  Scheme developers and C/SDL developers to help build the GUI.
*  Scheme developers to help add designs for generating of custom stitch-filled emblems like the heart or dolphi. Note that this happens in Embroidermodder not libembroidery (which assumes that you already have a function available).

### Writing

We also need people familiar with the software and the general
machine embroidery ecosystem to contribute to the
[documentation](https://github.com/Embroidermodder/docs).

We need researchers to find references for the documentation: colour tables,
machine specifications etc. The history is murky and often very poorly maintained
so if you know anything from working in the industry that you can share: it'd be
appreciated!

## Embroidermodder Project Coding Standards

A basic set of guidelines to use when submitting code.

Code structure is mre important than style, so first we advise you read ``Design'' and experimenting before getting into the specifics of code style.

### Where Code Goes

Anything that deals with the specifics of embroidery file formats, threads, rendering to images, embroidery machinery or command line interfaces should go in `libembroidery` not here.

Should your idea pass this test:

*  A new kind of GUI structure it goes in `src/ui.c`.
*  If it's something the user can do, make a section of the `actuator` function (which lives in `src/actuator.c`) using the guide "The Actuator's Behaviour".
*  Potentially variable data that is global goes in `src/data.c`.
*  If the data will not vary declare it as a compiler definition using the "Compiler definitions" section and put it in `src/em2.h`.
*  All other C code goes in `src/em2.c`.

### Where Non-compiled Files Go

\todo Like most user interfaces Embroidermodder is mostly data, so here we will have a list describing where each CSV goes.

### Ways in which we break style on purpose

Most style guides advise you to keep functions short. We make a few pointed exceptions to this where the overall health and functionality of the source code should benefit.

The `actuator` function will always be a mess and it should be: we're keeping the total source lines of code down by encoding all user action into a descrete sequence of strings that are all below \texttt{\_STRING\_LENGTH} in length. See the section on the actuator (TODO) describing why any other solution we could think  here would mean more more code without a payoff in speed of execution or clarity.

### Naming Conventions

Name variables and functions intelligently to minimize the need for comments. It should be immediately obvious what information it represents. Short names such as \texttt{x} and \texttt{y} are fine when referring to coordinates. Short names such as \texttt{i} and \texttt{j} are fine when doing loops.

Variable names should be `camelCase`, starting with a lowercase word followed by uppercase word(s). C Functions that attempt to simulate namespacing, should be \texttt{nameSpace\_camelCase}.

All files and directories shall be lowercase and contain no spaces.

## Code Style

Tabs should not be used when indenting. Setup your IDE or text editor to use 4 spaces.

### Braces

For functions: please put each brace on a new line.

    void function_definition(int argument)
    {
        /* code block */
    }

For control statements: please put the first brace on the same line.

    if (condition) {
        /* code block */    
    }

Use exceptions sparingly.

Do not use ternary operator `(?:)` in place of if/else.

Do not repeat a variable name that already occurs in an outer scope.

## Version Control

Being an open source project, developers can grab the latest code at any time and attempt to build it themselves. We try our best to ensure that it will build smoothly at any time, although occasionally we do break the build. In these instances, please provide a patch, pull request which fixes the issue or open an issue and notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

## Donations

Creating software that interfaces with hardware is costly. A summary of some of the costs involved:

*  Developer time for 2 core developers
*  Computer equipment and parts
*  Embroidery machinery
*  Various electronics for kitbashing Embroiderbot
*  Consumable materials (thread, fabric, stabilizer, etc...)

If you have found our software useful, please consider funding further development by donating to the project on Open Collective (\url{https://opencollective.com/embroidermodder}).

### Format Support

Support for Singer FHE, CHE (Compucon) formats?

## Embroidermodder Project Coding Standards

A basic set of guidelines to use when submitting code.

### Naming Conventions

Name variables and functions intelligently to minimize the need for
comments. It should be immediately obvious what information it
represents. Short names such as x and y are fine when referring to
coordinates. Short names such as i and j are fine when doing loops.

Variable names should be "camelCase", starting with a lowercase word
followed by uppercase word(s). C++ Class Names should be "CamelCase",
using all uppercase word(s). C Functions that attempt to simulate namespacing, should be "nameSpace\_camelCase".

All files and directories shall be lowercase and contain no spaces.

## Code Style

Tabs should not be used when indenting. Setup your IDE or text editor to
use 4 spaces.

### Braces

For functions: please put each brace on a new line.

    void function_definition(int argument)
    {

    }

For control statements: please put the first brace on the same line.

    if (condition) {

    }

Use exceptions sparingly.

Do not use ternary operator (?:) in place of if/else.

Do not repeat a variable name that already occurs in an outer scope.

### Version Control

Being an open source project, developers can grab the latest code at any
time and attempt to build it themselves. We try our best to ensure that
it will build smoothly at any time, although occasionally we do break
the build. In these instances, please provide a patch, pull request
which fixes the issue or open an issue and notify us of the problem, as
we may not be aware of it and we can build fine.

Try to group commits based on what they are related to:
features/bugs/comments/graphics/commands/etc...

### Comments

When writing code, sometimes there are items that we know can be
improved, incomplete or need special clarification. In these cases, use
the types of comments shown below. They are pretty standard and are
highlighted by many editors to make reviewing code easier. We also use
shell scripts to parse the code to find all of these occurrences so
someone wanting to go on a bug hunt will be able to easily see which
areas of the code need more love.

libembroidery and Embroidermodder are written in C and adheres to C89 standards. This means
that any C99 or C++ comments will show up as errors when compiling with
gcc. In any C code, you must use:

    /* Use C Style Comments within code blocks. */

    /**
     * Use Doxygen style code blocks to place todo items like this:
     * \todo EXAMPLE: This code clearly needs more work or further review.
     */

    /**
     * BUG: This code is definitely wrong. It needs fixed.
     */

    /**
     * HACK: This code shouldn't be written this way or I don't feel right about it. There may a better solution
     */

    /**
     * WARNING: Think twice (or more times) before changing this code. I put this here for a good reason.
     */

    /**
     * NOTE: This comment is much more important than lesser comments.
     */

## Ideas

### Why this document

I've been trying to make this document indirectly through the Github
issues page and the website we're building but I think a
straightforward, plain-text file needs to be the ultimate backup for
this. Then I can have a printout while I'm working on the project.

### googletests

gtests are non-essential, testing is for developers not users so we can
choose our own framework. I think the in-built testing for libembroidery
was good and I want to re-instate it.

### Qt and dependencies

I'm switching to SDL2 (which is a whole other conversation) which means
we can ship it with the source code package meaning only a basic build
environment is necessary to build it.

### Documentation

Can we treat the website being a duplicate of the docs a non-starter?
I'd be happier with tex/pdf only and (I know this is counter-intuitive)
one per project.

### Social Platform

So... all the issues and project boards etc. being on Github is all
well and good assuming that we have our own copies. But we don't if
Github goes down or some other major player takes over the space and we
have to move (again, since this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between
them.

### Identify the meaning of these TODO items

* Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug `#179`
* Lego Mindstorms NXT/EV3 ports and/or commands

### Progress Chart

The chart of successful from-to conversions (previously a separate issue)
is something that should appear in the README.

### Style

Rather than maintain our own standard for style, please defer to
the Python's PEP 7 \cite pep7 for C style.
If it passes the linters for that we consider it well styled
for a pull request.

As for other languages we have no house style other than whatever
"major" styles exist, for example Java in
Google style \cite google_java
would be acceptable. We'll elect specific standards if it becomes
an issue.

### Standard

The criteria for a good Pull Request from an outside developer has these properties, from most to least important:

*  No regressions on testing.
*  Add a feature, bug fix or documentation that is already agreed on through GitHub issues or some other way with a core developer.
*  No GUI specific code should be in libembroidery, that's for Embroidermodder.
*  Pedantic/ansi C unless there's a good reason to use another language.
*  Meet the style above (i.e. [PEP 7, Code Lay-out](\url{https://peps.python.org/pep-0007/#code-lay-out})). We'll just fix the style if the code's good and it's not a lot of work.
*  `embroider` should be in POSIX style as a command line program.
*  No dependancies that aren't "standard", i.e. use only the C Standard Library.

### Image Fitting

A currently unsolved problem in development that warrants further research is
the scenario where a user wants to feed embroider an image that can then be .

### To Place

A _right-handed coordinate system_ is one where up is positive and right is
positive. Left-handed is up is positive, left is positive. Screens often use
down is positive, right is positive, including the OpenGL standard so when
switching between graphics formats and stitch formats we need to use a vertical
flip (`embPattern\_flip`).

`0x20` is the space symbol, so when padding either 0 or space is preferred and in the case of space use the literal ' '.

### To Do

We currently need help with:

*  Thorough descriptions of each embroidery format.
*  Finding resources for each of the branded thread libraries (along with a full citation for documentation).
*  Finding resources for each geometric algorithm used (along with a full citation for documentation).
*  Completing the full `--full-test-suite`  with no segfaults and at least a clear error message (for example ``not implemented yet``).
*  Identifying ``best guesses`` for filling in missing information when going from, say `.csv` to a late `.pes` version. What should the default be when the data doesn't clarify?
*  Improving the written documentation.
*  Funding, see the Sponsor button above. We can treat this as ``work`` and put far more hours in with broad support in small donations from people who want specific features.

Beyond this the development targets are categories sorted into:

*  Basic Features
*  Code quality and user friendliness
*  embroider CLI
*  Documentation
*  GUI
*  electronics development

### Basic features

*  Incorporate `#if 0`ed parts of `libembroidery.c`.
*  Interpret how to write formats that have a read mode from the source code and vice versa.
*  Document the specifics of the file formats here for embroidery machine specific formats. Find websites and other sources that break down the binary formats we currently don't understand.
*  Find more and better documentation of the structure of the headers for the formats we do understand.

### Code quality and user friendliness

*  Document all structs, macros and functions (will contribute directly
   on the web version).
*  Incorporate experimental code, improve support for language bindings.
*  Make stitch x, y into an EmbVector.

### Documentation

*  Create csv data files for thread tables.
*  Convert tex to markdown, make tex an output of `build.bash`.
*  Run `sloccount` on `extern/` and `.` (and ) so we know the current scale of the project, aim to get this number low. Report the total as part of the documentation.
*  Try to get as much of the source code that we maintain into C as possible so new developers don't need to learn multiple languages to have an effect. This bars the embedded parts of the code. 

### GUI

*  Make EmbroideryMobile (Android) also backend to `libembroidery` with a Java wrapper.
*  Make EmbroideryMobile (iOS) also backend to `libembroidery` with a Swift wrapper.
*  Share some of the MobileViewer and iMobileViewer layout with the main EM2. Perhaps combine those 3 into the Embroidermodder repository so there are 4 repositories total.
*  Convert layout data to JSON format and use cJSON for parsing.

## Electronics development

*  Currently experimenting with Fritzing[8](8), upload netlists to embroiderbot when they can run simulations using the asm in `libembroidery`.
*  Create a common assembly for data that is the same across chipsets `libembrodiery\_data\_internal.s`.
*  Make the defines part of `embroidery.h` all systems and the function list `c code only`. That way we can share some development between assembly and C versions.

## Development

### Contributing

If you're interested in getting involved, here's some guidance
for new developers. Currently The Embroidermodder Team is all
hobbyists with an interest in making embroidery machines more
open and user friendly. If you'd like to support us in some other way
you can donate to our Open Collective page (click the Donate button) so
we can spend more time working on the project.

All code written for libembroidery should be ANSI C89 compliant
if it is C. Using other languages should only be used where
necessary to support bindings.

### Debug

If you wish to help with development, run this debug script and send us the error log.

    #!/bin/bash

    rm -fr libembroidery-debug

    git clone http://github.com/embroidermodder/libembroidery libembroidery-debug
    cd libembroidery-debug

    cmake -DCMAKE_BUILD_TYPE=DEBUG .
    cmake --build . --config=DEBUG

    valgrind ./embroider --full-test-suite

While we will attempt to maintain good results from this script as part of normal development it should be the first point of failure on any system we haven't tested or format we understand less.

### Binary download

We need a current `embroider` command line program download, so people can update
without building.
