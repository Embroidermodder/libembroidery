============================================
Embroidermodder Reference Manual
============================================

-----------
2.0.0-alpha
-----------

Introduction
============

The Embroidermodder Project and Team
------------------------------------

The _Embroidermodder 2_ project is a collection of small software
utilities for manipulating, converting and creating embroidery files in all
major embroidery machine formats. The program _Embroidermodder 2_ itself
is a larger graphical user interface (GUI) which is at the heart of the project.

The tools and associated documents are:

* The website https://www.libembroidery.org
* This reference manual covering the development of all these projects with
the current version available here:
https://www.libembroidery.org/embroidermodder_2.0_manual.pdf}
* The GUI *Embroidermodder 2* covered in Chapter~\ref{GUI}.
* The core library of low-level functions: `libembroidery`, covered in
Chapter~\ref{libembroidery}
* The CLI `embroider`, which is part of libembroidery
* Mobile embroidery format viewers and tools convered in Chapter~\ref{Mobile}.
* Specs for an open source hardware embroidery machine extension called the Portable Embroidery Tool (PET) which is also part of libembroidery. See Chapter~\ref{PET}.

The website, this manual and some scripts to construct the distribution are
maintained in \citep{embroidermodder_website}.

They all tools to make the standard
user experience of working with an embroidery machine better without expensive
software which is locked to specific manufacturers and formats. But ultimately
we hope that the core *Embroidermodder 2* is a practical, ever-present tool in
larger workshops, small cottage industry workshops and personal hobbyist's
bedrooms.

Embroidermodder 2 is licensed under the zlib license and we aim to keep all of our tools open
source and free of charge. If you would like to support the project check out our  Open
Collective (https://opencollective.com/embroidermodder) group.
If you would like to help,
please join us on GitHub. This document is written as developer training as well helping new
users (see the last sections) so this is the place to learn how to start changing the code.

The Embroidermodder Team is the collection of people who've submitted
patches, artwork and documentation to our three projects.
The team was established by Jonathan Greig and Josh Varga.
The full list is actively maintained below.

Core Development Team
~~~~~~~~~~~~~~~~~~~~~

Embroidermodder 2:

* Jonathan Greig (https://github.com/redteam316)
* Josh Varga (https://github.com/JoshVarga)
* Robin Swift (https://github.com/robin-swift)

Embroidermodder 1:

* Josh Varga (https://github.com/JoshVarga)
* Mark Pontius (http://sourceforge.net/u/mpontius/profile)

Credits for Embroidermodder 2, libembroidery and all other related code
-----------------------------------------------------------------------

If you have contributed and wish to be added to this list, alter the  README on Embroidermodder
github page (https://github.com/Embroidermodder/Embroidermodder) and we'll copy it to the
libembroidery source code since that is credited to ``The Embroidermodder Team''.

Embroidermodder 1
~~~~~~~~~~~~~~~~~

The Embroidermodder Team is also inspired by the original Embroidermodder that
was built by Mark Pontius and the same Josh Varga on SourceForge which
unfortunately appears to have died from linkrot. We may create a distribution
on here to be the official ``legacy'' Embroidermodder code but likely in a
seperate repository because it's GNU GPL v3 and this code is written to be
zlib (that is, permissive licensed) all the way down.

One reason why this is useful is that the rewrite by Jonathan Greig, John Varga
and Robin Swift for Embroidermodder 2 should have no regressions: no features
present in v1 should be missing in v2.

Features
~~~~~~~~

Embroidermodder 2 has many advanced features that enable you to create awesome designs quicker, tweak existing designs to perfection, and can be fully customized to fit your workflow.

A summary of these features:

* Cross Platform
* Realistic rendering
* Various grid types and auto-adjusting rulers
* Many measurement tools
* Add text to any design
* Supports many formats
* Batch Conversion
* Scripting API

Cross Platform
~~~~~~~~~~~~~~

If you use multiple operating systems, it's important to choose software that works on all of them.

Embroidermodder 2 runs on Windows, Linux and Mac OS X. Let's not forget the  Raspberry
Pi (https://www.raspberrypi.org).

![Running on different platforms](images/features-platforms-1.png)

### Realistic Rendering

It is important to be able to visualize what a design will look like when stitched and our
pseudo ``3D'' realistic rendering helps achieve this
(see Figure~\ref{real-render}).

// \label{fig-real-render}
.Real render examples.
\includegraphics[width=0.4\textwidth]{images/features-realrender-1.png}
\includegraphics[width=0.4\textwidth]{images/features-realrender-2.png}
\includegraphics[width=0.4\textwidth]{images/features-realrender-3.png}

### Various grid types and auto-adjusting rulers}

Making use of the automatically adjusting ruler in conjunction with the grid will ensure your
design is properly sized and fits within your embroidery hoop area.

Use rectangular, circular or isometric grids to construct your masterpiece!

Multiple grids and rulers in action Figure ref fig grid-ruler.

// \label{fig-grid-ruler}
.Grid and ruler examples.
image{features-grid-ruler-1.png}

### Many measurement tools}

Taking measurements is a critical part of creating great designs. Whether you are designing
mission critical embroidered space suits for NASA or some other far out design for your next
meet-up, you will have precise measurement tools at your command to make it happen. You can
locate individual points or find distances between any 2 points anywhere in the design!

Take quick and accurate measurements:

image{images/features-measure-1.png}

### Add text to any design}

Need to make company apparel for all of your employees with individual names on them? No sweat.
Just simply add text to your existing design or create one from scratch, quickly and easily.
Didn't get it the right size or made a typo? No problem. Just select the text and update it
with the property editor.

Add text and adjust its properties quickly:

image{images/features-text-1.png}

### Supports many formats}

Embroidery machines all accept different formats. There are so many formats
available that it can sometimes be confusing whether a design will work with your machine.

Embroidermodder 2 supports a wide variety of embroidery formats as well as several vector
formats, such as SVG and DXF. This allows you to worry less about which designs you can use.

Batch Conversion
~~~~~~~~~~~~~~~~

Need to send a client several different formats? Just use libembroidery-convert, our command
line utility which supports batch file conversion.

There are a multitude of formats to choose from:

image{images/features-formats-1.png[features formats}

Scripting API
~~~~~~~~~~~~~

If you've got programming skills and there is a feature that isn't currently available that you
absolutely cannot live without, you have the capability to create your own custom commands for
Embroidermodder 2. We provide an QtScript API which exposes various application functionality
so that it is possible to extend the application without requiring a new release. If you have
created a command that you think is worth including in the next release, just  contact
us (contact.html) and we will review it for functionality, bugs, and finally inclusion.

An Embroidermodder 2 command excerpt:

.. image::
   images/features-scripting-1.png

% scripting screenshot

Scraps
------

For
Embroidermodder 2.0.0-alpha4, libembroidery 1.0.0-alpha, PET 1.0.0-alpha
and EmbroideryMobile 1.0.0-alpha.

Since the document is shipped automatically try to update the revnumber each
time you edit using `revision.sh`.

Test these:

    sudo apt install latexml texlive-latex-base imagemagick info2man

    # For our command line tools:
    makeinfo embroider.texi -o embroider.info
    info2man embroider.info > embroider.1
    texi2pdf embroider.texi
    # Or groff macro package for example ms.
    # These may be housed in libembroidery since they're to be shipped as part of
    # the embroider tarball.

    # For online documentation:
    pandoc embroidermodder_refman.tex -f latex -t html -s -o emb_refman.html --bibliography embroidermodder.bib
    # Or latexml/latexmlpost

Command Language
~~~~~~~~~~~~~~~~

Printer Command Language (PCL), see \citet{packard1992pcl}.

HP-GL/2 Vector Graphics \index{HP-GL/2} described in \citet{packard1992pcl}.
Has commands like: \texttt{PU} Pen Up, \texttt{PR} Plot Relative,
\texttt{EP} edge polygon.

So commands read like this:

    PA40,10;

command argument seperator(``,``) argument terminator(``;``)

Constructing new commands from old ones in the command language is less
natural in the HP-GL/2 language, but a similar layer for us is
the tajima DST format \citep{4} for existing printers and CNC commands for
direct control... where'd we'd use G-Code \citep{7} and Linux CNC \citep{6}.

Could we `setpagedevice` to a printer in some cases and a similar CUPS service
for embroidery machines in others?

All systems are supported by ghostscript, when you account for homebrew \citet{9}:

    brew update
    brew upgrade
    brew install ghostscript
    brew cleanup

Vector graphic logos don't require the SVG Qt library.

### Man Pages}

We maintain a traditional manpage for \texttt{embroider} using
the basic macros.

### Arduino}

\begin{verbatim}
apt-get install avr-libc gcc-avr uisp avrdude
\end{verbatim}

## Libembroidery}

(Under construction, please wait for v1.0 release.)

Libembroidery is a low-level library for reading, writing,
and altering digital embroidery files in C. It is part of the Embroidermodder Project
for open source machine embroidery.

Libembroidery is the underlying library that is used by Embroidermodder 2
and is developed by  The Embroidermodder Team \ref{the-embroidermodder-team}.
A full list of contributors to the project is maintained in
https://github.com/Embroidermodder/embroidermodder}
the Embroidermodder 2 github in the file `CREDITS.md`.
It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

It also includes a CLI called `embroider` that allows for better automation of
changes to embroidery files and will be more up-to date than
the Embroidermodder 2 GUI.

### Documentation}

Libembroidery is documented as part of this reference manual. If you need
libembroidery for any non-trivial usage or want to contribute to the library we
advise you read the appropriate design sections of the manual first. Copies of
this manual will be shipped with the packaged version of libembroidery, but to
build it we use the Doxyfile in
https://github.com/Embroidermodder/embroidermodder} the Embroidermodder git
repository.

For more basic usage, `embroider` should have some in-built help
starting with:

\begin{lstlisting}
$ embroider --help
\end{lstlisting}

### License}

Libembroidery is distributed under the permissive zlib licence, see the LICENCE
file.

## Demos}

We're currently trying out some fill techniques which will be demonstrated here
and in the script `qa\_test.sh`.

// center and caption
image{images/examples/logo.png[the logo}

Converts to:

// center and caption
\includegraphics{images/examples/crossstitch_logo.png}
crossstitch logo

### Build}

libembroidery and EmbroiderModder 2 use CMake builds
so if you are building the project to use as a library we recommend
you run:

\begin{verbatim}
git clone https://github.com/Embroidermodder/libembroidery
cd libembroidery
cmake .
cmake --build .
cmake --install .
\end{verbatim}

This builds both the static and shared versions of the library as well
as the command line program `embroider`.

\citep{packard1992pcl}
\citep{linuxcncsrc}
\citep{linuxcnc}
\citep{adobe1990postscript}
\citep{postscript1999postscript}
\citep{eduTechDST}
\citep{cups}
\citep{millOperatorsManual}
\citep{oberg1914machinery}
\citep{dxf_reference}
\citep{embroidermodder_source_code}
\citep{libembroidery_source_code}
\citep{acatina}
\citep{kde_tajima}
\citep{wotsit_archive}
\citep{wotsit_siterip}
\citep{fineemb_dst}
\citep{edutechwiki_dst}

## Graphical User Interface for PC}
\ref{GUI}

### Overview}

\emph{UNDER MAJOR RESTRUCTURING, PLEASE WAIT FOR VERSION 2}

https://www.libembroidery.org}

Embroidermodder is a free machine embroidery application.
The newest version, Embroidermodder 2 can:

\begin{itemize}
* edit and create embroidery designs
* estimate the amount of thread and machine time needed to stitch a design
* convert embroidery files to a variety of formats
* upscale or downscale designs
* run on Windows, Mac and Linux
\end{itemize}

\emph{Embroidermodder 2} is very much a work in progress since we're doing a ground
up rewrite to an interface in C using the GUI toolkit SDL2.
The reasoning for this is detailed in the issues tab.

For a more in-depth look at what we are developing read our
website (https://www.libembroidery.org}) which includes these docs as well
as the up-to date printer-friendly versions. These discuss recent changes,
plans and has user and developer guides for all the Embroidermodder projects.

To see what we're focussing on right now, see the Open Collective
News (https://opencollective.com/embroidermodder}).

// fixme
This current printer-friendly version
is here (https://www.libembroidery.org/EM2.0.0-alpha_refman_a4.pdf}).

### License}

The source code is under the terms of the zlib license: see `LICENSE.md`
in the source code directory.

Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.

A copy of the license is included in Section~\ref{GNU-free-documentation-license}.

### Build and Install}

Assuming you already have the SDL2 libraries you can proceed to using the fast build, which
assumes you want to build and test locally.

The fast build should be:

\begin{verbatim}
bash build.sh
\end{verbatim}

or, on Windows:

\begin{verbatim}
.\build.bat
\end{verbatim}

Then run using the `run.bat` or `run.sh` scripts in the build/ directory.

Otherwise, follow the instructions below.

If you plan to install the dev version to your system (we recommend you wait
for the official installers and beta release first) then use the CMake build
instead.

### Install on Desktop}

We recommend that if you want to install the development version you use the CMake build. Like
this:

\begin{lstlisting}
git submodule --init --update

mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
\end{lstlisting}

These lines are written into the file:

\begin{lstlisting}
./build_install.sh
\end{lstlisting}

On Windows use the next section.

## History}

Embroidermodder 1 was started by Mark Pontius in 2004 while staying up all night
with his son in his first couple months. When Mark returned to his day job, he
lacked the time to continue the project. Mark made the decision to focus on his
family and work, and in 2005, Mark gave full control of the project to Josh
Varga so that Embroidermodder could continue its growth.

Embroidermodder 2 was conceived in mid 2011 when Jonathan Greig and Josh Varga
discussed the possibility of making a cross-platform version. It is currently in
active development and will run on GNU/Linux, Mac OS X, Microsoft Windows and
Raspberry Pi.

All Embroidermodder downloads (downloads.html) are hosted on SourceForge.

The source code for Embroidermodder 1
(http://sourceforge.net/p/embroidermodder/code/HEAD/tree/embroidermodder1})
has always been hosted on Sourceforge.

The source code for Embroidermodder 2
(https://github.com/Embroidermodder/Embroidermodder}) was moved to GitHub
on July 18, 2013.

The website for Embroidermodder
(https://github.com/Embroidermodder/www.libembroidery.org}) was moved to
GitHub on September 9, 2013.

# Contact us}

For general questions email:  embroidermodder at gmail.com (mailto:embroidermodder@gmail.com})

To request a new feature  open an issue on the main Embroidermodder GitHub repository (https://github.com/Embroidermodder/Embroidermodder/issues}). We'll move it to the correct repository.

# Downloads}

## Alpha Build}

This is a highly experimental build: we recommend users wait for the beta release when the basic features
are functional.

Visit our  GitHub Releases page (https://github.com/Embroidermodder/Embroidermodder/releases)
for the current build. Unfortunately, earlier builds went down with the Sourceforge page we hosted them on.

# GUI}

Embroidermodder 2 is very much a work in progress since we're doing a ground up rewrite to an
interface in Python using the GUI toolkit Tk. The reasoning for this is detailed in the issues
tab.

For a more in-depth look at what we are developing read the developer notes (link to dev notes
section). This discusses recent changes in a less formal way than a changelog (since this
software is in development) and covers what we are about to try.

## Documentation}

The documentation is in the form of the website (included in the `docs/` directory) and the
printed docs in this file.

### Development}

If you wish to develop with us you can chat via the contact email on the
website (https://www.libembroidery.org}) or in the issues tab on the
github page (https://github.com/Embroidermodder/Embroidermodder/issues}).
People have been polite and friendly in these conversations and I (Robin) have
really enjoyed them. If we do have any arguments please note we have a Code of
Conduct (`CODE\_OF\_CONDUCT.md`) so there is a consistent policy to enforce when
dealing with these arguments.

The first thing you should try is building from source using the build advice(link to build)
above. Then read some of the development notes (link to dev notes.md) to get the general
layout of the source code and what we are currently planning.

### Testing}

To find unfixed errors run the tests by launching from the command line with:

\begin{lstlisting}
$ embroidermodder --test
\end{lstlisting}

then dig through the output. It's currently not worth reporting the errors, since
there are so many but if you can fix anything reported here you can submit a PR.

## Code Optimisations and Simplifications}

### Geometry}

The geometry is stored, processed and altered via libembroidery. See the Python specific part
of the documentation for libembroidery for this. What the code in Embroidermodder does is make
the GUI widgets to change and view this information graphically.

For example if we create a circle with radius 10mm and center at `(20mm, 30mm)` then fill it
with stitches the commands would be

\begin{lstlisting}
from libembroidery import Pattern, Circle, Vector, satin
circle = Circle(Vector(20, 30), 10)
pattern = Pattern()
pattern.add_circle(circle, fill=satin)
pattern.to_stitches()
\end{lstlisting}

but the user would do this through a series of GUI actions:

\begin{enumerate}
* Create new file
* Click add circle
* Use the Settings dialog to alter the radius and center
* Use the fill tool on circle
* Select satin from the drop down menu
\end{enumerate}

So EM2 does the job of bridging that gap.

### Postscript Support}

In order to safely support user contributed/shared data that can define, for
example, double to double functions we need a consistent processor for these
descriptions.

Embroidermodder backends to the postscript interpreter included in libembroidery
to accomplish this.

For example the string: `5 2 t mul add` is equivalent to
the expression $2*t + 5$.

The benefit of not allowing this to simply be a Python expression is that it is safe against
malicious use, or accidental misuse. The program can identify whether the output is of the
appropriate form and give finitely many calculations before declaring the function to have run
too long (stopping equations that hang).

To see examples of this see the \texttt{assets/shapes/*.ps} files.

### SVG Icons}

To make the images easier to alter and restyle we could switch to svg icons.
There's some code in the git history to help with this.

### The Actions System}

In order to simplify the development of a GUI that is flexible and easy to
understand to new developers we have a custom action system that all user
actions will go via an \texttt{actuator} that takes a string argument. By using a
string argument the undo history is just an array of strings.

The C \texttt{action\_hash\_data} struct will contain: the icon used, the
labels for the menus and tooltips and the function pointer for that action.
There will be an accompanying argument for this function call, currently being
drafted as `action\_call`. So when the user makes a function call it should
contain information like the mouse position, whether special key is pressed etc.

### Accessibility}

Software can be more or less friendly to people with dyslexia, partial
sightedness, reduced mobility and those who don't speak English. Embroidermodder
2 has, in its design, the following features to help:

\begin{itemize}
* icons for everything to reduce the amount of reading required
* the system font is configurable: if you have a dyslexia-friendly font you
can load it
* the interface rescales to help with partial-sightedness
* the system language is configurable, unfortunately the docs will only be
in English but we can try to supply lots of images of the interface to make it
easier to understand as a second language
* buttons are remappable: XBox controllers are known for being good for
people with reduced mobility so remapping the buttons to whatever setup you have
should help
\end{itemize}

Note that most of these features will be released with version 2.1, which is planned for around
early 2023.

### Sample Files}

Various sample embroidery design files can be found in the `embroidermodder2/samples` folder.

### Shortcuts}

A shortcut can be made up of zero or more modifier keys and at least one non-modifier key
pressed at once.

To make this list quickly assessable, we can produce a list of hashes which are simply the
flags ORed together.

The shortcuts are stored in the csv file `shortcuts.csv` as a 5-column table
with the first 4 columns describing the key combination. This is loaded into
the shortcuts `TABLE`. Each tick the program checks the input state for this
combination by first translating the key names into indices for the key state,
then checking for whether all of them are set to true.

### Removed Elements}

So I've had a few pieces of web infrastructure fail me recently and I think
it's worth noting. An issue that affects us is an issue that can effect people
who use our software.

### Qt and dependencies}

Downloading and installing Qt has been a pain for some users (46Gb on possibly
slow connections).

I'm switching to FreeGLUT 3 (which is a whole other conversation) which means
we can ship it with the source code package meaning only a basic build
environment is necessary to build it.

### Social Platform}

Github is giving me a server offline (500) error and is still giving a bad ping.

So... all the issues and project boards etc. being on Github is all well and
good assuming that we have our own copies. But we don't if Github goes down or
some other major player takes over the space and we have to move (again, since
this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between them.

### OpenGL}

OpenGL rendering within the application. This will allow for Realistic Visualization - Bump
Mapping/OpenGL/Gradients?

This should backend to a C renderer or something.

### Configuration Data Ideas}

Embroidermodder should boot from the command line regardless of whether it is or is not
installed (this helps with testing and running on machines without root). Therefore, it can
create an initiation file but it won't rely on its existence to boot:
`~/.embroidermodder/config.json`.

\begin{itemize}
* Switch colors to be stored as 6 digit hexcodes with a `\#`.
* We've got close to a hand implemented ini read/write setup in `settings.py`.
\end{itemize}

### Distribution}
\index{distribution}

When we release the new pip wheel we should also package:

\begin{itemize}
* `.tar.gz` and `.zip` source archive.
* Debian package
* RPM package
\end{itemize}

Only do this once per minor version number.

\begin{itemize}
* todo Screenshot a working draft to demonstrate.
\end{itemize}

### Perennial Jobs}

\begin{itemize}
* Check for memory leaks
* Clear compiler warnings on `-Wall -ansi -pedantic` for C.
* Write new tests for new code.
* Get Embroidermodder onto the current version of libembroidery.
* PEP7 compliance.
* Better documentation with more photos/screencaps.
\end{itemize}

### Full Test Suite}
\index{testing}

(This needs a hook from Embroidermodder to embroider's full test suite.)

The flag `--full-test-suite` runs all the tests that have been written.
Since this results in a lot of output the details are both to stdout
and to a text file called `test\_matrix.txt`.

Patches that strictly improve the results in the `test\_matrix.txt` over
the current version will likely be accepted and it'll be a good place
to go digging for contributions. (Note: strictly improve means that
the testing result for each test is as good a result, if not better.
Sacrificing one critera for another would require some design work
before we would consider it.)

### Symbols}
\index{symbols}

Symbols use the SVG path syntax.

In theory, we could combine the icons and symbols systems, since they could be
rendered once and stored as icons in Qt. (Or as textures in FreeGLUT.)

Also we want to render the patterns themselves using SVG syntax, so it would
save on repeated work overall.

## Features}

### Bindings}
\index{bindings}

Bindings for libembroidery are maintained for the languages we use internally
in the project, for other languages we consider that the responsibility of
other teams using the library.

So libembroidery is going to be supported on:

\begin{itemize}
* `C` (by default)
* `C++` (also by default)
* `Java` (for the Android\index{Android} application MobileViewer)
* `Swift` (for the iOS\index{iOS} application iMobileViewer)
\end{itemize}

For `C\#` \index{C-sharp} we recommend directly calling the function directly
using the DllImport feature:

\begin{lstlisting}
/* Calling readCsv() via C# as a native function. */
[DllImport("libembroidery.so", EntryPoint="readCsv")]
\end{lstlisting}

see this StackOverflow discussion for help:
https://stackoverflow.com/questions/11425202/is-it-possible-to-call-a-c-function-from-c-net}.

For Python you can do the same using ctypes:
https://www.geeksforgeeks.org/how-to-call-a-c-function-in-python/}.

### Other Supported Thread Brands}
\index{supported threads}

The thread lists that aren't preprogrammed into formats but are indexed in
the data file for the purpose of conversion or fitting to images/graphics.

\begin{itemize}
* Arc Polyester
* Arc Rayon
* Coats and Clark Rayon
* Exquisite Polyester
* Fufu Polyester
* Fufu Rayon
* Hemingworth Polyester
* Isacord Polyester
* Isafil Rayon
* Marathon Polyester
* Marathon Rayon
* Madeira Polyester
* Madeira Rayon
* Metro Polyester
* Pantone
* Robison Anton Polyester
* Robison Anton Rayon
* Sigma Polyester
* Sulky Rayon
* ThreadArt Rayon
* ThreadArt Polyester
* ThreaDelight Polyester
* Z102 Isacord Polyester
\end{itemize}

## House Style}

\begin{verbatim}
//=========================================
// Embroidermodder Project Coding Standards
//=========================================
A basic set of guidelines to use when submitting code.

//=====================
// Naming Conventions
//=====================
Name variables and functions intelligently to minimize the need for comments.
It should be immediately obvious what information it represents.
Short names such as x and y are fine when referring to coordinates.
Short names such as i and j are fine when doing loops.

Variable names should be "camelCase", starting with a lowercase word followed by uppercase word(s).
C++ Class Names should be "CamelCase", using all uppercase word(s).
C Functions that attempt to simulate namespacing, should be "nameSpace_camelCase".

All files and directories shall be lowercase and contain no spaces.

//=====================
// Code Style
//=====================
Tabs should not be used when indenting. Setup your IDE or text editor to use 4 spaces.

If you use KATE (KDE Advanced Text Editor), modelines are included in our code to enforce 
some of our coding standards. When creating new C/C++ files, please add
the modeline to the bottom of the file followed by a blank line. Always make sure there
is an extra blank line at the end of a file.

When using braces, please put the brace on a new line, unless the code is specially formatted
for easier reading such as a block of one liner if/else statements.

Use exceptions sparingly.

if/else is preferred over switch/case.

Do not use ternary operator (?:) in place of if/else.

Do not repeat a variable name that already occurs in an outer scope.

//=====================
// Version Control 
//=====================
Being an open source project, developers can grab the latest code at any time
and attempt to build it themselves. We try our best to ensure that it will build smoothly
at any time, although occasionally we do break the build. In these instances,
please provide a patch, pull request which fixes the issue or open an issue and
notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

//=====================
// Comments
//=====================
When writing code, sometimes there are items that we know can be improved,
incomplete or need special clarification. In these cases, use the types of
comments shown below. They are pretty standard and are highlighted by many editors to
make reviewing code easier. We also use shell scripts to parse the code to find
all of these occurances so someone wanting to go on a bug hunt will be able to
easily see which areas of the code need more love.

//C++ Style Comments
//TODO: This code clearly needs more work or further review.
//BUG: This code is definitely wrong. It needs fixed.
//HACK: This code shouldn't be written this way or I don't feel right about it. There may a better solution.
//WARNING: Think twice (or more times) before changing this code. I put this here for a good reason.
//NOTE: This comment is much more important than lesser comments.

libembroidery is written in C and adheres to C89 standards. This means
that any C99 or C++ comments will show up as errors when compiling with
gcc. In any C code, you must use:

/* C Style Comments */
/* TODO: This code clearly needs more work or further review. */
/* BUG: This code is definitely wrong. It needs fixed. */
/* HACK: This code shouldn't be written this way or I don't feel right about it. There may a better solution */
/* WARNING: Think twice (or more times) before changing this code. I put this here for a good reason. */
/* NOTE: This comment is much more important than lesser comments. */

\end{verbatim}

These are rules for the general intended style of Embroidermodder's GUI source
code. Not included are anything that a compiler will warn you about: fixing
compiler warnings is more important than fixing style.

Most of this section is rationale, so skip to the end for the summary.

NEW DEVELOPERS: if your patch to Embroidermodder doesn't follow these rules,
don't worry about it. We only ask that your source code follow the basic rules
in the developer training section. These rules are for sculpting Embroidermodder
into a body of code that is resiliant to future bugs and reliable for users.

### Brevity}

Readable source code is short. Developers have finite time and becoming
acquainted with more than 1000 lines of dense C code is often too high a bar
for a new developer to a project. However, this leads to a bunch of tradeoffs
that have caused issues, so instead we consider the ``minimal library''
rather than ``minimal code'' approach. Not everyone will have used the more
abstract, syntactic features of C++ like templates and operator overloading.
Even if they are capable developers with these features it makes debugging far
harder since the choice of called function is interpreted by the compiler and compiler
errors are hundred line monsters per infraction of ``these are all of the possible
variations of this function that don't match''.

Using C++'s `unordered\_map` can simplify source code in that anything can
map to anything. However, it also means we don't have to associate related structures.
For example the `action\_table` came together replacing a collection of unordered maps
with one, then replaced the mapping with labelled indices. Since the `actuator\_core`
is a giant switch/case statement this cuts the step of identifying the action by its
label `std::string`.
The structure given by this table allowed the code to be much
easier to interpret. So for this reason we don't recommend the use unordered maps or hashes any more.

### Rigidity Vs. Ease of Modification

Difficult to restructure code is good if the structure that's there is good.
It guides new developers into safe practices without having to explain them.
Therefore we want ease of modification that comes from well chosen `structs`
and a carefully curated global header of .

### Developer Prose


### Macro Policy}

Macros are great, you can do all sorts with them. But it's easy to make readable
short code that is really difficult to safely modify.

### Function Style}

\begin{enumerate}
* Don't write a new convenience function unless there are two
existing applications of it in the source code.
* 
\end{enumerate}

### Summary}

\begin{itemize}
* 
\end{itemize}

## GUI Design}
\index{GUI}

Embroidermodder 2 was written in C++/Qt5 and it was far too complex. We had
issues with people not able to build from source because the Qt5 libraries were
so ungainly. So I decided to do a rewrite in C/SDL2 (originally FreeGLUT, but
that was a mistake) with data stored as YAML. This means linking 4-7 libraries
depending on your system which are all well supported and widely available.

This is going well, although it's slow progress as I'm trying to keep track of
the design while also doing a ground up rewrite. I don't want to throw away good
ideas. Since I also write code for libembroidery my time is divided.

Overview of the UI rewrite

(Problems to be solved in brackets.)

It's not much to look at because I'm trying to avoid using an external
widgets system, which in turn means writing things like toolbars and menubars
over. If you want to get the design the actuator is the heart of it.

Without Qt5 we need a way of assigning signals with actions, so this is what
I've got: the user interacts with a UI element, this sends an integer to the
actuator that does the thing using the current state of the mainwindow struct
of which we expect there to be exactly one instance. The action is taken out
by a jump table that calls the right function (most of which are missing in
action and not connected up properly). It also logs the number, along with
key parts of the main struct in the undo history (an unsolved problem because
we need to decide how much data to copy over per action). This means undo,
redo and repeat actions can refer to this data.

## To Do}

These should be sorted into relevant code sections.

\begin{itemize}
* todo sort todo list.
* Alpha: High priority
\begin{itemize}
* Statistics from 1.0, needs histogram
* Saving DST/PES/JEF (varga)
* Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug
\end{itemize}
* Alpha: medium priority
\begin{itemize}
* Notify user of data loss if not saving to an object format.
* Import Raster Image
* SNAP/ORTHO/POLAR
* Layer Manager + LayerSwitcher DockWidget
* Reading DXF
\end{itemize}
* Alpha: low priority
\begin{itemize}
* Writing DXF
* Up and Down keys cycle thru commands in the command prompt
* Amount of Thread, Machine Time Estimation (also allow customizable times
for setup, color changes, manually
trimming jump threads, etc...that way a realistic total time can be estimated)
* Otto Theme Icons - whatsthis icon doesn't scale well, needs redone
* embroidermodder2.ico 16 x 16 looks horrible
\end{itemize}
* Alpha: lower priority
\begin{itemize}
* CAD Command: Arc (rt)
\end{itemize}
* beta
\begin{itemize}
* Custom Filter Bug - doesn't save changes in some cases
* Cannot open file with `\#` in name when opening multiple files (works fine
when opening the single file)
* Closing Settings Dialog with the X in the window saves settings rather than
discards them
* Advanced Printing
* Filling Algorithms (varga)
* Otto Theme Icons - beta (rt) - Units, Render, Selectors
\end{itemize}
* Finish before 2.0 release
\begin{itemize}
* QDoc Comments
* Review KDE4 Thumbnailer
* Documentation for libembroidery and formats
* HTML Help files
* Update language translations
* CAD Command review: line
* CAD Command review: circle
* CAD Command review: rectangle
* CAD Command review: polygon
* CAD Command review: polyline
* CAD Command review: point
* CAD Command review: ellipse
* CAD Command review: arc
* CAD Command review: distance
* CAD Command review: locatepoint
* CAD Command review: move
* CAD Command review: rgb
* CAD Command review: rotate
* CAD Command review: scale
* CAD Command review: singlelinetext
* CAD Command review: star
* Clean up all compiler warning messages, right now theres plenty :P
\end{itemize}
* 2.0
\begin{itemize}
* tar.gz archive
* zip archive
* Debian Package (rt)
* NSIS Installer (rt)
* Mac Bundle?
* press release
\end{itemize}
* 2.x/Ideas
\begin{itemize}
* libembroidery.mk for MXE project (refer to qt submodule packages for qmake based building. Also refer to plibc.mk for example of how write an update macro for github.)
* libembroidery safeguard for all writers - check if the last stitch is an END stitch. If not, add an end stitch in the writer and modify the header data if necessary.
* Cut/Copy - Allow Post-selection
* CAD Command: Array
* CAD Command: Offset
* CAD Command: Extend
* CAD Command: Trim
* CAD Command: BreakAtPoint
* CAD Command: Break2Points
* CAD Command: Fillet
* CAD Command: Chamfer
* CAD Command: Split
* CAD Command: Area
* CAD Command: Time
* CAD Command: PickAdd
* CAD Command: Product
* CAD Command: Program
* CAD Command: ZoomFactor
* CAD Command: GripHot
* CAD Command: GripColor and GripCool
* CAD Command: GripSize
* CAD Command: Highlight
* CAD Command: Units
* CAD Command: Grid
* CAD Command: Find
* CAD Command: Divide
* CAD Command: ZoomWindow (Move out of view.cpp)
* Command: Web (Generates Spiderweb patterns)
* Command: Guilloche (Generates Guilloche patterns)
* Command: Celtic Knots
* Command: Knotted Wreath
* Lego Mindstorms NXT/EV3 ports and/or commands.
* native function that flashes the command prompt to get users attention when using the prompt is required for a command.
* libembroidery-composer like app that combines multiple files into one.
* Settings Dialog, it would be nice to have it notify you when switching tabs that a setting has been changed. Adding an Apply button is what would make sense for this to happen.
* Keyboard Zooming/Panning
* G-Code format?
* 3D Raised Embroidery
* Gradient Filling Algorithms
* Stitching Simulation
* RPM packages?
* Reports?
* Record and Playback Commands
* Settings option for reversing zoom scrolling direction
* Qt GUI for libembroidery-convert
* EPS format? Look at using Ghostscript as an optional add-on to libembroidery...
* optional compile option for including LGPL/GPL libs etc... with warning to user about license requirements.
* Realistic Visualization - Bump Mapping/OpenGL/Gradients?
* Stippling Fill
* User Designed Custom Fill
* Honeycomb Fill
* Hilbert Curve Fill
* Sierpinski Triangle fill
* Circle Grid Fill
* Spiral Fill
* Offset Fill
* Brick Fill
* Trim jumps over a certain length.
* FAQ about setting high number of jumps for more controlled trimming.
* Minimum stitch length option. (Many machines also have this option too)
* Add 'Design Details' functionality to libembroidery-convert
* Add 'Batch convert many to one format' functionality to libembroidery-convert
* EmbroideryFLOSS - Color picker that displays catalog numbers and names.
\end{itemize}
* beta
\begin{itemize}
* Realistic Visualization - Bump Mapping/OpenGL/Gradients?
* Get undo history widget back (BUG).
* Mac Bundle, .tar.gz and .zip source archive.
* NSIS installer for Windows, Debian package, RPM package
* GUI frontend for embroider features that aren't
supported by embroidermodder: flag selector from a table
* Update all formats without color to check for edr or rgb files.
* Setting for reverse scrolling direction (for zoom, vertical pan)
* Keyboard zooming, panning
* New embroidermodder2.ico 16x16 logo that looks good at that scale.
* Saving dst, pes, jef.
* Settings dialog: notify when the user is switching tabs
that the setting has been changed, adding apply button is what would
make sense for this to happen.
* Update language translations.
* Replace KDE4 thumbnailer.
* Import raster image.
* Statistics from 1.0, needs histogram.
* SNAP/ORTHO/POLAR.
* Cut/copy allow post-selection.
* Layout into config.
* Notify user of data loss if not saving to an object format.
* Add which formats to work with to preferences.
* Cannot open file with `\#` in the name when opening multiple
files but works with opening a single file.
* Closing settings dialog with the X in the window saves
settings rather than discarding them.
* Otto theme icons: units, render, selectors, what's
this icon doesn't scale.
* Layer manager and Layer switcher dock widget.
* Test that all formats read data in correct scale
(format details should match other programs).
* Custom filter bug -- doesn't save changes in some cases.
* Tools to find common problems in the source code and suggest fixes
to the developers. For example, a translation miss: that is, for any language
other than English a missing entry in the translation table should supply a
clear warning to developers.
* Converting Qt C++ version to native GUI C throughout.
* OpenGL Rendering: `Real` rendering to see what the embroidery
looks like, Icons and toolbars, Menu bar.
* Libembroidery interfacing: get all classes to use the proper
libembroidery types within them. So `Ellipse` has `EmbEllipse` as public
data within it.
* Move calculations of rotation and scaling into `EmbVector` calls.
* GUI frontend for embroider features that aren't supported by
embroidermodder: flag selector from a table
* Update all formats without color to check for edr or rgb files.
* Setting for reverse scrolling direction (for zoom, vertical pan)
* Keyboard zooming, panning
* Better integrated help: I don't think the help should backend to
a html file somewhere on the user's system. A better system would be a custom
widget within the program that's searchable.
* New embroidermodder2.ico 16x16 logo that looks good at that scale.
* Settings dialog: notify when the user is switching tabs that the
setting has been changed, adding apply button is what would make sense for
this to happen.
\end{itemize}
\end{itemize}

## Contributing}

### Version Control}

Being an open source project, developers can grab the latest code at any time
and attempt to build it themselves. We try our best to ensure that it will build smoothly
at any time, although occasionally we do break the build. In these instances,
please provide a patch, pull request which fixes the issue or open an issue and
notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

See the coding style  here (coding-style).

### Get the Development Build going}

When we switch to releases we recommend using them, unless you're reporting a bug in which case you can check the development build for whether it has been patched. If this applies to you, the current development build is https://github.com/Embroidermodder/Embroidermodder/releases/tag/alpha3[here].

### To Do}

\begin{itemize}
* Beta
\begin{itemize}
* Libembroidery 1.0.
* Better integrated help: I don't think the help should backend to a html file somewhere on the user's system. A better system would be a custom widget within the program that's searchable.
* EmbroideryFLOSS - Color picker that displays catalog numbers and names.
* Custom filter bug -- doesn't save changes in some cases.
* Advanced printing.
* Stitching simulation.
\end{itemize}
* 2.x/ideas
\begin{itemize}
* User designed custom fill.
\end{itemize}
\end{itemize}

These are key bits of reasoning behind why the GUI is built the way it is.

## Translation of the user interface}

In a given table the left column is the default symbol and the right string is the translation.
If the translate function fails to find a translation it returns the default symbol.

So in US English it is an empty table, but in UK English
only the dialectical differences are present.

Ideally, we should support at least the 6 languages spoken at the UN. Quoting https://www.un.org}

\begin{quote}
\emph{There are six official languages of the UN. These are Arabic, Chinese, English, French, Russian and Spanish.}
\end{quote}

We're adding Hindi, on the grounds that it is one of the most commonly spoken languages and at
least one of the Indian languages should be present.

Written Chinese is generally supported as two different symbol sets and we follow that
convension.

English is supported as two dialects to ensure that the development team is aware of what those
differences are. The code base is written by a mixture of US and UK native English speakers
meaning that only the variable names are consistently one dialect: US English. As for
documentation: it is whatever dialect the writer prefers (but they should maintain consistency
within a text block like this one).

Finally, we have ``default'', which is the dominant language
of the internals of the software. Practically, this is
just US English, but in terms of programming history this
is the ``C locale''.

## Old action system notes}

Action: the basic system to encode all user input.

This typedef gives structure to the data associated with each action
which, in the code, is referred to by the action id (an int from
the define table above).

## DESCRIPTION OF STRUCT CONTENTS}

### label}

The action label is always in US English, lowercase,
seperated with hyphens.

For example: \texttt{new-file}.

## Flags}

The bit based flags all collected into a 32-bit integer.

\begin{table}
\begin{tabular}{l l}
bit(s) & description \\
0 & User (0) or system (1) permissions. \\
1-3 & The mode of input. \\
4-8 & The object classes that this action can be applied to. \\
9-10 & What menu (if any) should it be present in. \\ 
11-12 & What
\end{tabular}
\label{tab:flags-for-actions}
\caption{Flags of EM actions}
\end{table}

## Description}

The string placed in the tooltip describing the action.

## Original Prompt System}

NOTE: `main()` is run every time the command is started.
Use it to reset variables so they are ready to go.

NOTE: `click()` is run only for left clicks.
Middle clicks are used for panning.
Right clicks bring up the context menu.

NOTE: `move()` is optional. It is run only after
`enableMoveRapidFire()` is called. It
will be called every time the mouse moves until
`disableMoveRapidFire()` is called.

NOTE: `prompt()` is run when Enter is pressed.
`appendPromptHistory` is automatically called before `prompt()`
is called so calling it is only needed for erroneous input.
Any text in the command prompt is sent as an uppercase string.

\include{actions.tex}

## Changelog}

## Ideas}

Stuff that is now supposed to be generated by Doxygen:

\begin{itemize}
* todo: Bibliography style to plainnat.
* todo: US letter paper version of printed docs.
\end{itemize}

# Formats}

## Overview}

#### Read/Write Support Levels}

The table of read/write format support levels uses the status levels described here:

\begin{longtable}{p{4cm} p{8cm}}
\caption{Read/Write Support Levels.}
\label{tab:read-write-support} \\
\textbf{Status Label} &
\textbf{Description} \\

\texttt{rw-none} &
Either the format produces no output, reporting an error. Or it produces a
Tajima dst file as an alternative. \\

\texttt{rw-poor} &
A file somewhat similar to our examples is produced. We don't know how well
it runs on machines in practice as we don't have any user reports or personal
tests. \\

\texttt{rw-basic} &
Simple files in this format run well on machines that use this format. \\

\texttt{rw-standard} &
Files with non-standard features work on machines and we have good documentation
on the format. \\

\texttt{rw-reliable} &
All known features don't cause crashes. Almost all work as expected. \\

\texttt{rw-complete} &
All known features of the format work on machines that use this format.
Translations from and to this format preserve all features present in both.
\end{longtable}

These can be split into `r-basic w-none`, for example, if they don't match.

So all formats can, in principle, have good read and good write support, because it's defined in relation to files that we have described the formats for.

#### Test Support Levels}

\begin{longtable}{p{4cm} p{8cm}}
\caption{Test Support Levels.}
\label{tab:test-support} \\
\textbf{Status Label} &
\textbf{Description} \\

\texttt{test-none} &
No tests have been written to test the specifics of the format. \\

\texttt{test-basic} &
Stitch Lists and/or colors have read/write tests. \\

\texttt{test-thorough} &
All features of that format has at least one test. \\

\texttt{test-fuzz} &
Can test the format for uses of features that we haven't thought of by feeding
in nonsense that is designed to push possibly dangerous weaknesses to reveal
themselves. \\

\texttt{test-complete} &
Both thorough and fuzz testing is covered.
\end{longtable}

So all formats can, in principle, have complete testing support, because it's
defined in relation to files that we have described the formats for.

#### Documentation Support Levels}

\begin{longtable}{p{4cm} p{8cm}}
\caption{Test Support Levels.}
\label{tab:test-support} \\
\textbf{Status Label} &
\textbf{Description} \\

\texttt{doc-none} &
We haven't researched this beyond finding example files. \\

\texttt{doc-basic} &
We have a rough sketch of the size and contents of the header if there is one.
We know the basic stitch encoding (if there is one), but not necessarily all
stitch features. \\

\texttt{doc-standard} &
We know some good sources and/or have tested all the features that appear to
exist. They mostly work the way we have described. \\

`doc-good` &
All features that were described somewhere have been covered here or we have
thoroughly tested our ideas against other softwares and hardwares and they work
as expected. \\

`doc-complete` &
There is a known official description and our description covers all the same
features.
\end{longtable}

Not all formats can have complete documentation because it's based on what
information is publically available. So the total score is reported in the table
below based on what level we think is available.

#### Overall Support}

Since the overall support level is the combination of these
4 factors, but rather than summing up their values it's an
issue of the minimum support of the 4.

\begin{table}
\begin{tabular}{l l}
\textbf{Status Label} &
\textbf{Description}
\\
`read-only` &
If write support is none and read support is not none.
\\
`write-only` &
If read support is none and write support is not none.
\\
`unstable` &
If both read and write support are not none but testing or documentation is none.
\\
`basic` &
If all ratings are better than none.
\\
`reliable` &
If all ratings are better than basic.
\\
`complete` &
If all ratings could not reasonably be better (for example any improvements
rely on information that we may never have access to). This is the only status
that can be revoked, since if the format changes or new documentation is
released it is no longer complete.
\\
`experimental` &
For all other scenarios.
\end{tabular}
\caption{.}
\end{table}

## Table of Format Support Levels}

Overview of documentation support by format.

\begin{table}
\begin{tabular}{l l l}
*Format* &
*Ratings* &
*Score* \\

\index{Toyota} Embroidery Format (\index{100}.100`) &
rw-basic doc-none test-none &
unstable \\

\index{Toyota} Embroidery Format (\index{10o}.10o`) &
rw-basic doc-none test-none &
unstable \\

\index{Bernina} Embroidery Format (\index{art}`.art`) &
rw-none doc-none test-none &
experimental \\

\index{Bitmap Cache} Embroidery Format (\index{bmc}`.bmc`) &
r-basic w-none doc-none test-none &
unstable \\

\index{Bits and Volts} Embroidery Format (`.bro`) &
rw-none doc-none test-none &
experimental \\

Melco Embroidery Format (`.cnd`) &
rw-none doc-none test-none &
experimental \\

Embroidery Thread Color Format (`.col`) &
rw-basic doc-none test-none &
`experimental` \\

Singer Embroidery Format (`.csd`) &
rw-none doc-none test-none &
experimental \\

Comma Separated Values (`.csv`) &
rw-none doc-none test-none &
experimental \\

| Barudan Embroidery Format (`.dat`)
| rw-none doc-none test-none
| experimental
\\
| Melco Embroidery Format (.dem)
| rw-none doc-none test-none
| experimental

| Barudan Embroidery Format (.dsb)
| rw-none doc-none test-none
| experimental

| Tajima Embroidery Format (.dst)
| rw-none doc-none test-none
| experimental

| ZSK USA Embroidery Format (.dsz)
| rw-none doc-none test-none
| experimental

| Drawing Exchange Format (.dxf)
| rw-none doc-none test-none
| experimental

| Embird Embroidery Format (.edr)
| rw-none doc-none test-none
| experimental

| Elna Embroidery Format (.emd)
| rw-none doc-none test-none
| experimental

| Melco Embroidery Format (.exp)
| rw-none doc-none test-none
| experimental

| Eltac Embroidery Format (.exy)
| rw-none doc-none test-none
| experimental

| Sierra Expanded Embroidery Format (.eys)
| rw-none doc-none test-none
| experimental

| Fortron Embroidery Format (.fxy)
| rw-none doc-none test-none
| experimental

| Smoothie G-Code Embroidery Format (.gc)
| rw-none doc-none test-none
| experimental

| Great Notions Embroidery Format (.gnc)
| rw-none doc-none test-none
| experimental

| Gold Thread Embroidery Format (.gt)
| rw-none doc-none test-none
| experimental

| Husqvarna Viking Embroidery Format (.hus)
| rw-none doc-none test-none
| experimental

| Inbro Embroidery Format (.inb)
| rw-none doc-none test-none
| experimental

| Embroidery Color Format (.inf)
| rw-none doc-none test-none
| experimental

| Janome Embroidery Format (.jef)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (.ksm)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (.max)
| rw-none doc-none test-none
| experimental

| Mitsubishi Embroidery Format (.mit)
| rw-none doc-none test-none
| experimental

| Ameco Embroidery Format (.new)
| rw-none doc-none test-none
| experimental

| Melco Embroidery Format (`.ofm`)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (.pcd)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (`.pcm`)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (`.pcq`)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (`.pcs`)
| rw-none doc-none test-none
| experimental

| Brother Embroidery Format (`.pec`)
| rw-none doc-none test-none
| experimental

| Brother Embroidery Format (.pel)
| rw-none doc-none test-none
| experimental

| Brother Embroidery Format (.pem)
| rw-none doc-none test-none
| experimental

| Brother Embroidery Format (.pes)
| rw-none doc-none test-none
| experimental

| Brother Embroidery Format (.phb)
| rw-none doc-none test-none
| experimental

| Brother Embroidery Format (.phc)
| rw-none doc-none test-none
| experimental

| AutoCAD Embroidery Format (.plt)
| rw-none doc-none test-none
| experimental

| RGB Embroidery Format (.rgb)
| rw-none doc-none test-none
| experimental

| Janome Embroidery Format (.sew)
| rw-none doc-none test-none
| experimental

| Husqvarna Viking Embroidery Format (.shv)
| rw-none doc-none test-none
| experimental

| Sunstar Embroidery Format (.sst)
| rw-none doc-none test-none
| experimental

| Data Stitch Embroidery Format (.stx)
| rw-none doc-none test-none
| experimental

| Scalable Vector Graphics (.svg)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (.t01)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (.t09)
| rw-none doc-none test-none
| experimental

| Happy Embroidery Format (.tap)
| rw-none doc-none test-none
| experimental

| ThredWorks Embroidery Format (`.thr`)
| rw-none doc-none test-none
| experimental

| Text File (`.txt`)
| rw-none doc-none test-none
| experimental

| Barudan Embroidery Format (`.u00`)
| rw-none doc-none test-none
| experimental

| Barudan Embroidery Format (\index{u01}`.u01`)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (`.vip`)
| rw-none doc-none test-none
| experimental

| Pfaff Embroidery Format (`.vp3`)
| rw-none doc-none test-none
| experimental

| Singer Embroidery Format (`.xxx`)
| rw-none doc-none test-none
| experimental

| ZSK USA Embroidery Format (`.zsk`)
| rw-none doc-none test-none
| experimental

| *FORMAT*
| *READ, WRITE*
| *NOTES*

| \index{\texttt{10o}}
| YES, NO
| read (need to fix external color loading) (maybe find out what ctrl and code flags of `0x10`, `0x08`, `0x04`, and `0x02` mean)

| \index{\texttt{100}}
| NO, NO
| none (4 byte codes) `61 00 10 09` (type, type2, x, y ?) x and y (signed char)

| \index{\texttt{art}}
| NO, NO
| none

| \index{\texttt{bro}}
| YES NO
| read (complete)(maybe figure out detail of header)

| \index{\texttt{cnd}}
| NO, NO
| none

| \index{\texttt{col}}
| NO, NO
| (color file no design) read(final) write(final)

| \index{\texttt{csd}}
| YES NO
| read (complete)

| \index{\texttt{dat}}
| NO, NO
| read ()

| \index{\texttt{dem}}
| NO, NO
| none (looks like just encrypted cnd)

| \index{\texttt{dsb}}
| YES NO
| read (unknown how well) (stitch data looks same as 10o)

| \index{\texttt{dst}}
| YES NO
| read (complete) / write(unknown)

| \index{\texttt{dsz}}
| YES NO
| read (unknown)

| \index{\texttt{dxf}}
| NO, NO
| read (Port to C. needs refactored)

| \index{\texttt{edr}}
| NO, NO
| read (C version is broken) / write (complete)

| \index{\texttt{emd}}
| NO, NO
| read (unknown)

| \index{\texttt{exp}}
| YES NO
| read (unknown) / write(unknown)

| \index{\texttt{exy}}
| YES NO
| read (need to fix external color loading)

| \index{\texttt{fxy}}
| YES NO
| read (need to fix external color loading)

| \index{\texttt{gnc}}
| NO, NO
| none

| \index{\texttt{gt}}
| NO, NO
| read (need to fix external color loading)

| \index{\texttt{hus}}
| YES NO
| read (unknown) / write (C version is broken)

| \index{\texttt{inb}}
| YES NO
| read (buggy?)

| \index{\texttt{jef}}
| YES NO
| write (need to fix the offsets when it is moving to another spot)

| \index{\texttt{ksm}}
| YES NO
| read (unknown) / write (unknown)

| \index{\texttt{pcd}}
| NO, NO
|

| \index{\texttt{pcm}}
| NO, NO
|

| \index{\texttt{pcq}}
| NO, NO
| read (Port to C)

| \index{\texttt{pcs}}
| BUGGY, NO
| read (buggy / colors are not correct / after reading, writing any other format is messed up)

| \index{\texttt{pec}}
| NO, NO
| read / write (without embedded images, sometimes overlooks some stitches leaving a gap)

| \index{\texttt{pel}}
| NO, NO
| none

| \index{\texttt{pem}}
| NO, NO
| none

| \index{\texttt{pes}}
| YES, NO
|

| \index{\texttt{phb}}
| NO, NO
|

| \index{\texttt{phc}}
| NO, NO
|

| \index{\texttt{rgb}}
| NO, NO
|

| \index{\texttt{sew}}
| YES, NO
|

| \index{\texttt{shv}}
| NO, NO
| read (C version is broken)

| \index{\texttt{sst}}
| NO, NO
| none

| \index{\texttt{svg}}
| NO, YES
|

| \index{\texttt{tap}}
| YES, NO
| read (unknown)

| \index{\texttt{u01}}
| NO, NO
|

| \index{\texttt{vip}}
| YES, NO
|

| \index{\texttt{vp3}}
| YES, NO
|

| \index{\texttt{xxx}}
| YES, NO
|

| \index{\texttt{zsk}}
| NO, NO
| read (complete)
\end{tabular}
\end{table}

\begin{itemize}
* TODO Josh, Review this section and move any info still valid or
needing work into TODO comments in the actual libembroidery code. Many items in
this list are out of date and do not reflect the current status of
libembroidery. When finished, delete this file.
\begin{itemize}
* Test that all formats read data in correct scale (format details should
match other programs)
* Add which formats to work with to preferences.
* Check for memory leaks
* Update all formats without color to check for edr or rgb files
* Fix issues with DST (VERY important that DST work well)
\end{itemize}
* todo Support for Singer FHE, CHE (Compucon) formats?
\end{itemize}

# Geometry and Algorithms}

## To Do}

#### Arduino}

\begin{itemize}
* Fix emb-outline files
* Fix thread-color files
* Logging of Last Stitch Location to External USB Storage(commonly available and easily replaced) ...wait until TRE is available to avoid rework
* inotool.org - seems like the logical solution for Nightly/CI builds
* Smoothieboard experiments
\end{itemize}

#### Testing}

\begin{itemize}
* looping test that reads 10 times while running valgrind. See `embPattern\_loadExternalColorFile()` Arduino leak note for more info.
\end{itemize}

#### Development}

If you wish to develop with us you can chat via the contact email
on the  website https://libembroidery.org} or in the issues tab on the
 github page https://github.com/Embroidermodder/Embroidermodder/issues}.
People have been polite and friendly in these conversations and I (Robin)
have really enjoyed them.
If we do have any arguments please note we have a
 Code of Conduct  CODE\_OF\_CONDUCT.md so there is a consistent policy to
enforce when dealing with these arguments.

The first thing you should try is building from source using the  build advice (build)
above. Then read some of the  manual
https://libembroidery.org/emrm_alpha_a4.pdf} to get the general
layout of the source code and what we are currently planning.

#### Testing}

To find unfixed errors run the tests by launching from the command line with:

\begin{lstlisting}
$ embroidermodder --test
\end{lstlisting}

then dig through the output. It's currently not worth reporting the errors, since
there are so many but if you can fix anything reported here you can submit a PR.

## Contributing}

#### Funding}

The easiest way to help is to fund development (see the Donate button above),
since we can't afford to spend a lot of time developing and only have limited
kit to test out libembroidery on.

#### Programming and Engineering}

Should you want to get into the code itself:

\begin{itemize}
* Low level C developers are be needed for the base library
\texttt{libembroidery}.
* Low level assembly programmers are needed for translating some of
\texttt{libembroidery} to \texttt{EmbroiderBot}.
* Hardware Engineers to help design our own kitbashed embroidery machine
\texttt{EmbroiderBot}, one of the original project aims in 2013.
* Scheme developers and C/SDL developers to help build the GUI.
* Scheme developers to help add designs for generating of custom
stitch-filled emblems like the heart or dolphi. Note that this happens in
Embroidermodder not libembroidery (which assumes that you already have a
function available).
\end{itemize}

#### Writing}

We also need people familiar with the software and the general
machine embroidery ecosystem to contribute to the
documentation (https://github.com/Embroidermodder/www.libembroidery.org).

We need researchers to find references for the documentation: colour tables,
machine specifications etc. The history is murky and often very poorly maintained
so if you know anything from working in the industry that you can share: it'd be
appreciated!

## Embroidermodder Project Coding Standards}

A basic set of guidelines to use when submitting code.

Code structure is mre important than style, so first we advise you read
``Design'' and experimenting before getting into the specifics of code style.

#### Where Code Goes}

Anything that deals with the specifics of embroidery file formats, threads,
rendering to images, embroidery machinery or command line interfaces should go 
in \texttt{libembroidery} not here.

#### Where Non-compiled Files Go}

TODO: Like most user interfaces Embroidermodder is mostly data, so here we will have a list describing where each CSV goes.

#### Ways in which we break style on purpose}

Most style guides advise you to keep functions short. We make a few pointed
exceptions to this where the overall health and functionality of the source code should benefit.

The `actuator` function will always be a mess and it should be: we're keeping
the total source lines of code down by encoding all user action into a descrete
sequence of strings that are all below \texttt{\_STRING\_LENGTH} in length. See
the section on the actuator (TODO) describing why any other solution we could
think  here would mean more more code without a payoff in speed of execution or
clarity.

## Version Control}

Being an open source project, developers can grab the latest code at any time and attempt to build it themselves. We try our best to ensure that it will build smoothly at any time, although occasionally we do break the build. In these instances, please provide a patch, pull request which fixes the issue or open an issue and notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

## Donations}

Creating software that interfaces with hardware is costly. A summary of some of the costs involved:

\begin{itemize}
* Developer time for 2 core developers
* Computer equipment and parts
* Embroidery machinery
* Various electronics for kitbashing Embroiderbot
* Consumable materials (thread, fabric, stabilizer, etc...)
\end{itemize}

If you have found our software useful, please consider funding further development by donating to the project on Open Collective
(https://opencollective.com/embroidermodder}).

## Embroidermodder Project Coding Standards}

Rather than maintain our own standard for style, please defer to
the Python's PEP 7 \citep{pep7} for C style and emulating that in C++.

A basic set of guidelines to use when submitting code. Defer to the PEP7 standard with the following additions:

\begin{itemize}
* All files and directories shall be lowercase and contain no spaces.
* Structs and class names should use `LeadingCapitals`.
* Enums and constants should be \texttt{BLOCK\_CAPITALS}.
* Class members and functions without a parent class should be \texttt{snake\_case}.
With the exception of when one of the words is a ``class'' name from
libembroidery in which case it has the middle capitals like this:
`embArray\_add`.
* Don't use exceptions.
* Don't use ternary operator (?:) in place of if/else.
* Don't repeat a variable name that already occurs in an outer scope.
\end{itemize}

### Version Control}

Being an open source project, developers can grab the latest code at any
time and attempt to build it themselves. We try our best to ensure that
it will build smoothly at any time, although occasionally we do break
the build. In these instances, please provide a patch, pull request
which fixes the issue or open an issue and notify us of the problem, as
we may not be aware of it and we can build fine.

Try to group commits based on what they are related to:
features/bugs/comments/graphics/commands/etc...

### Comments}

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

\begin{lstlisting}
/* Use C Style Comments within code blocks.
 *
 * Use Doxygen style code blocks to place todo, bug, hack, warning,
 * and note items like this:
 *
 * \todo EXAMPLE: This code clearly needs more work or further review.
 *
 * \bug This code is definitely wrong. It needs fixed.
 *
 * \hack This code shouldn't be written this way or I don't
 * feel right about it. There may a better solution
 *
 * \warning Think twice (or more times) before changing this code.
 * I put this here for a good reason.
 *
 * \note This comment is much more important than lesser comments.
 */
\end{lstlisting}

## Ideas}

### Why this document}

I've been trying to make this document indirectly through the Github
issues page and the website we're building but I think a
straightforward, plain-text file needs to be the ultimate backup for
this. Then I can have a printout while I'm working on the project.

### Qt and dependencies}

I'm switching to SDL2 (which is a whole other conversation) which means
we can ship it with the source code package meaning only a basic build
environment is necessary to build it.

### Documentation}

Can we treat the website being a duplicate of the docs a non-starter?
I'd be happier with tex/pdf only and (I know this is counter-intuitive)
one per project.

### Social Platform}

So... all the issues and project boards etc. being on Github is all
well and good assuming that we have our own copies. But we don't if
Github goes down or some other major player takes over the space and we
have to move (again, since this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between
them.

### Identify the meaning of these TODO items}

\begin{itemize}
* Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug `\#179`
* Lego Mindstorms NXT/EV3 ports and/or commands
\end{itemize}

### Progress Chart}

The chart of successful from-to conversions (previously a separate issue)
is something that should appear in the README.

### Standard}

The criteria for a good Pull Request from an outside developer has these properties, from most to least important:

\begin{itemize}
* No regressions on testing.
* Add a feature, bug fix or documentation that is already agreed on through
  GitHub issues or some other way with a core developer.
* No GUI specific code should be in libembroidery, that's for Embroidermodder.
* Pedantic/ansi C unless there's a good reason to use another language.
* Meet the style above (i.e.  PEP 7, Code Lay-out
  (https://peps.python.org/pep-0007/#code-lay-out}). We'll just fix the style
  if the code's good and it's not a lot of work.
* `embroider` should be in POSIX style as a command line program.
* No dependancies that aren't ``standard'', i.e. use only the C Standard Library.
\end{itemize}

### Image Fitting}

A currently unsolved problem in development that warrants further research is
the scenario where a user wants to feed embroider an image that can then be .

### To Place}

A \emph{right-handed coordinate system} \index{right-handed coordinate system}
is one where up is positive and right is
positive. Left-handed is up is positive, left is positive. Screens often use
down is positive, right is positive, including the OpenGL standard so when
switching between graphics formats and stitch formats we need to use a vertical
flip (`embPattern\_flip`).

`0x20` is the space symbol, so when padding either 0 or space is preferred and
in the case of space use the literal ' '.

### To Do}

We currently need help with:

\begin{itemize}
* Thorough descriptions of each embroidery format.
* Finding resources for each of the branded thread libraries (along with a
full citation for documentation).
* Finding resources for each geometric algorithm used (along with a full
citation for documentation).
* Completing the full `--full-test-suite` with no segfaults and at least a
clear error message (for example ``not implemented yet'').
* Identifying ``best guesses'' for filling in missing information when going
from, say `.csv` to a late `.pes` version. What should the default be when
the data doesn't clarify?
* Improving the written documentation.
* Funding, see the Sponsor button above. We can treat this as ``work'' and
put far more hours in with broad support in small donations from people who want
specific features.
\end{itemize}

Beyond this the development targets are categories sorted into:

\begin{itemize}
* Basic Features
* Code quality and user friendliness
* embroider CLI
* Documentation
* GUI
* electronics development
\end{itemize}

### Basic features}

\begin{itemize}
* Incorporate `\#if 0` ed parts of `libembroidery.c`.
* Interpret how to write formats that have a read mode from the source
code and vice versa.
* Document the specifics of the file formats here for embroidery machine
specific formats. Find websites and other sources that break down the binary
formats we currently don't understand.
* Find more and better documentation of the structure of the headers for the
formats we do understand.

### Code quality and user friendliness}

* Document all structs, macros and functions (will contribute directly
on the web version).
* Incorporate experimental code, improve support for language bindings.
* Make stitch x, y into an EmbVector.

### Documentation

Run `sloccount` on `extern/` and `.` (and ) so we know the
current scale of the project, aim to get this number low. Report the total as
part of the documentation.

Try to get as much of the source code that we maintain into C as possible so
new developers don't need to learn multiple languages to have an effect. This
bars the embedded parts of the code.

### GUI

* Make EmbroideryMobile (Android) also backend to `libembroidery` with a Java wrapper.
* Make EmbroideryMobile (iOS) also backend to `libembroidery` with a Swift wrapper.
* Share some of the MobileViewer and iMobileViewer layout with the main EM2. Perhaps combine those 3 into the Embroidermodder repository so there are 4 repositories total.
* Convert layout data to JSON format and use cJSON for parsing.

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

If you wish to help with development, run this debug script and send us the
error log.

```bash
#!/bin/bash

rm -fr libembroidery-debug

git clone http://github.com/embroidermodder/libembroidery libembroidery-debug
cd libembroidery-debug

cmake -DCMAKE_BUILD_TYPE=DEBUG .
cmake --build . --config=DEBUG

valgrind ./embroider --full-test-suite
```

While we will attempt to maintain good results from this script as part of
normal development it should be the first point of failure on any system we
haven't tested or format we understand less.

### Binary download}

We need a current `embroider` command line program download, so people can update
without building.

# Programming principles for the C core}

End arrays of char arrays with the symbol ``END'', the code will never require
this symbol as an entry.

Define an array as one of 3 kinds: constant, editable or data.

\begin{itemize}
* Constant arrays are defined const and have fixed length matching the data.
* Editable arrays are fixed length, but to a length based on the practical use
  of that array. A dropdown menu can't contain more than 30 items, because we
  don't want to flood the user with options. However it can nest indefinately,
  so it is not restricted to a total number of entries.
* Data arrays is editable and changes total size at runtime to account for user data.
\end{itemize}

## Style rules for arrays}

1.
