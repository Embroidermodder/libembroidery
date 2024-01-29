.. meta::
   :description: The Embroidermodder Project
   :keywords: machine embroidery, embroidery, dst, pes, jef

The Embroidermodder Project
===========================

.. toctree::
   :maxdepth: 2
   :caption: Contents
   :name: maintoc

.. warning::

   IN ALPHA DEVELOPMENT: NOT READY FOR SERIOUS USE.

Embroidermodder is a free and open source machine embroidery application.
If our project is successful, it will:

  * edit and create embroidery designs
  * estimate the amount of thread and machine time needed to stitch a design
  * convert embroidery files to a variety of formats
  * upscale or downscale designs
  * run on Windows, Mac and Linux

To try out the software in alpha see our `downloads page <https://libembroidery.org/downloads>`_.

Various sample embroidery design files can be found in
the github samples folder.

Screenshots
-----------

If you use multiple operating systems, it's important to choose
software that works on all of them. Embroidermodder 2 runs on Windows,
Linux and Mac OS X. Let's not forget the `Raspberry Pi <https://www.raspberrypi.org>`_.

History
-------

Embroidermodder 1 was started by Mark Pontius in 2004 while staying up all night
with his son in his first couple months. When Mark returned to his day job, he
lacked the time to continue the project. Mark made the decision to focus on his
family and work, and in 2005, Mark gave full control of the project to Josh Varga
so that Embroidermodder could continue its growth.

Embroidermodder 2 was conceived in mid 2011 when Jonathan Greig and Josh Varga
discussed the possibility of making a cross-platform version. It is currently in
active development and will run on GNU/Linux, Mac OS X, Microsoft Windows and
Raspberry Pi.

The source code and binaries for Embroidermodder 1 were hosted on Sourceforge, but
due to link rot we've lost them.

.. warning::

   TODO: upload a backup here.

The `source code for Embroidermodder 2 <https://github.com/Embroidermodder/Embroidermodder>`_
was moved to GitHub on July 18, 2013.

`This website <https://github.com/Embroidermodder/docs>`_ was moved
to GitHub on September 9, 2013. Due to us losing the domain name it was renamed
to ``www.libembroidery.org`` from ``www.embroidermodder.org``.

The `libembroidery library <https://github.com/Embroidermodder/libembroidery>`_
became a seperate project in 2018 as a way of supporting other frontends with
the same file parsing and geometry routines.

The Embroidermodder Project and Team
------------------------------------

The *Embroidermodder 2* project is a collection of small software utilities for
manipulating, converting and creating embroidery files in all major embroidery
machine formats. The program *Embroidermodder 2* itself is a larger graphical
user interface (GUI) which is at the heart of the project.

The tools and associated documents are:

* This website (www.libembroidery.org), which is maintained [docs-repo]_.
* The manual [manual-link]_ covering all these projects which is maintained seperately as LaTeX [manual-src]_.
* The GUI (embroidermodder), maintained [gui]_.
* The core library of low-level functions: [libembroidery-src]_.
* The CLI `embroider` which is part of [libembroidery-src]_.
* Mobile embroidery format viewers and tools [EmbroideryMobile-src]_.
* Specs for an open hardware embroidery machine called Embroiderbot (not started yet) which is also part of [libembroidery-src]_.

.. [docs-repo] https://github.com/Embroidermodder/docs
.. [manual-link] https://www.libembroidery.org/embroidermodder_2.0_manual.pdf
.. [manual-src] https://github.com/Embroidermodder/emrm
.. [gui] https://github.com/Embroidermodder/embroidermodder
.. [libembroidery-src] https://github.com/Embroidermodder/libembroidery
.. [EmbroideryMobile-src] https://github.com/Embroidermodder/embroiderymobile

They are all tools to make the standard user experience of working with an
embroidery machine better without expensive software which is locked to specific
manufacturers and formats. But ultimately we hope that the core *Embroidermodder 2*
is a practical, ever-present tool in larger workshops, small cottage industry workshops
and personal hobbyist's bedrooms.

Embroidermodder 2 is licensed under the zlib license and we aim to keep all of
our tools open source and free of charge. If you would like to support the
project check out our `Open Collective <https://opencollective.com/embroidermodder>`_
group. If you would like to help, please
join us on GitHub. This document is written as developer training as well
helping new users (see the last sections) so this is the place to learn how
to start changing the code.

The Embroidermodder Team is the collection of people who've submitted
patches, artwork and documentation to our three projects.
The team was established by Jonathan Greig and Josh Varga.
The full list of contributors who wish to be credited is
`here <https://www.libembroidery.org/docs/credits/>`_

Core Development Team
---------------------

Embroidermodder 2:

  * `Jonathan Greig <https://github.com/redteam316>`_
  * `Josh Varga <https://github.com/JoshVarga>`_
  * `Robin Swift <https://github.com/robin-swift>`_

Embroidermodder 1:

  * `Josh Varga <https://github.com/JoshVarga>`_
  * `Mark Pontius <http://sourceforge.net/u/mpontius/profile>`_

History
-------

Embroidermodder 1 was started by Mark Pontius in 2004 while staying up all night
with his son in his first couple months. When Mark returned to his day job,
he lacked the time to continue the project. Mark made the decision to focus on his
family and work, and in 2005, Mark gave full control of the project to Josh Varga
so that Embroidermodder could continue its growth.

Embroidermodder 2 was conceived in mid 2011 when Jonathan Greig and Josh Varga
discussed the possibility of making a cross-platform version. It is currently in
active development and will run on GNU/Linux, Mac OS X, Microsoft Windows and Raspberry Pi.

The source code and binaries for Embroidermodder 1 were hosted on Sourceforge, but
due to link rot we've lost them.

.. todo: upload a backup here.

The `source code <https://github.com/Embroidermodder/Embroidermodder>`_ for Embroidermodder
2 was moved to GitHub on July 18, 2013.

`This website <https://github.com/Embroidermodder/www.libembroidery.org>`_ was moved to
GitHub on September 9, 2013. Due to us losing the domain name it was renamed to
``www.libembroidery.org`` from ``www.embroidermodder.org``.

The `libembroidery library <https://github.com/Embroidermodder/libembroidery>`_
became a seperate project in 2018 as a way of supporting other frontends with the
same file parsing and geometry routines.

Downloads
=========

Build Packages
--------------

These are a highly experimental build: we recommend users wait for the beta releases
when the basic features are functional.

Embroidermodder (Alpha Build)
-----------------------------

This is a highly experimental build: we recommend users wait for the beta release when the basic features
are functional.

* Embroidermodder 2.0.0-alpha3
   - Windows (https://www.libembroidery.org/builds/embroidermodder_2.0.0-alpha3_windows.zip)
   - GNU/Linux (https://www.libembroidery.org/builds/embroidermodder_2.0.0-alpha3_linux.tar.gz)
   - Mac OS (https://www.libembroidery.org/builds/embroidermodder_2.0.0-alpha3_macos.tar.gz)
* Embroidermodder 2.0.0-alpha2
   - Windows (https://www.libembroidery.org/builds/Windows_Archive.zip)
   - GNU/Linux (https://www.libembroidery.org/builds/GNU_Linux_Archive.tar.gz)
   - Mac OS (https://www.libembroidery.org/builds/MacOS_Archive.tar.gz)

For the most up-to date builds visit our [GitHub Releases page](https://github.com/Embroidermodder/Embroidermodder/releases/tag/alpha).

libembroidery
-------------

* Windows (https://www.libembroidery.org/builds/Windows_Archive.zip)
* GNU/Linux (https://www.libembroidery.org/builds/GNU_Linux_Archive.tar.gz)
* Mac OS (https://www.libembroidery.org/builds/MacOS_Archive.tar.gz)

embroider
---------

For systems which will only use `embroider` in scripts, these static URLs will always
be available for `CURL` or `wget` for the current version.
However, if you need to be sure that it works the
same in less-often updated machines, you will need specific versions which will be maintained below.

.. warning:: These links need fixing.

* https://www.libembroidery.org/downloads/windows/embroider
* https://www.libembroidery.org/downloads/gnulinux/embroider
* https://www.libembroidery.org/downloads/macos/embroider

For example:

    wget https://www.libembroidery.org/builds/windows/embroider

gets the executable directly.

EmbroideryMobile
----------------

* Windows (https://www.libembroidery.org/builds/Windows_Archive.zip)
* GNU/Linux (https://www.libembroidery.org/builds/GNU_Linux_Archive.tar.gz)
* Mac OS (https://www.libembroidery.org/builds/MacOS_Archive.tar.gz)

Old Versions
------------

These will be maintained from the beta onwards for both the
documentation, source code and builds.

Version 1.70
------------

During this alpha development you may prefer to use the original
Embroidermodder 1.70 (Windows Only):
https://www.libembroidery.org/builds/embroidermodder170_exe.zip

Documentation
=============

For all of these manuals (except the `embroider` manpage),
the source code is maintained as part
of the website `here <https://github.com/Embroidermodder/libembroidery>`_.

User Manuals
------------

Note that these URLs are maintained as the permalinks.

For all of these user manuals (except the ``embroider`` manpage),
the source code is maintained as part
of the website `here <https://github.com/Embroidermodder/docs>`_.

* Embroidermodder: https://www.libembroidery.org/em_user
* embroider: https://www.libembroidery.org/docs/embroider.txt
* EmbroideryMobile: https://www.libembroidery.org/mobile_user
* PET: https://www.libembroidery.org/pet_user

The Developer Manual
--------------------

The Embroidermodder Reference Manual (EMRM) is the main developer 
resource found here: https://www.libembroidery.org/emrm

For developers working on other project that use libembroidery,
the API is documented here: https://www.libembroidery.org/api/html

Changelog (From early alpha to beta)
====================================

* Up and Down keys cycle thru commands in the command prompt.

Current Work
============

* `EmbPattern *pattern` as a variable in the `View` class.
* Removing the now unnecessary `SaveObject` class.
* Converting all comments to C style.
  * Switching away from Doxygen-style in favour of direct commentary and a custom written reference manual.

Documentation
-------------

* Document all tests.
  * Automation of tests.
  * Ensure that the stitch count matches what we know the file has.
  * 
* 

Embroidermodder
---------------

2.0 alpha1
~~~~~~~~~~

* WIP - Statistics from 1.0, needs histogram
* WIP - Saving DST/PES/JEF (varga)
* WIP - Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug

2.0 alpha2
~~~~~~~~~~

* Notify user of data loss if not saving to an object format.
* Import Raster Image
* SNAP/ORTHO/POLAR
* Layer Manager + LayerSwitcher DockWidget
* Reading DXF

2.0 alpha3
~~~~~~~~~~

* Writing DXF
* Amount of Thread & Machine Time Estimation (also allow customizable times for setup, color changes, manually trimming jump threads, etc...that way a realistic total time can be estimated)
* Otto Theme Icons - whatsthis icon doesn't scale well, needs redone
* embroidermodder2.ico 16 x 16 looks horrible

2.0 alpha4
~~~~~~~~~~

* WIP - CAD Command: Arc (rt)
* Load/Save Menu/Toolbars configurations into settings.ini

2.0 beta1
~~~~~~~~~

* Custom Filter Bug - doesn't save changes in some cases
* Cannot open file with # in name when opening multiple files (works fine when opening the single file)
* Closing Settings Dialog with the X in the window saves settings rather than discards them
* WIP - Advanced Printing
* Filling Algorithms (varga)
* Otto Theme Icons - beta (rt) - Units, Render, Selectors

2.0 rc1
~~~~~~~

* Review KDE4 Thumbnailer
* Documentation for libembroidery & formats
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

2.0 release
~~~~~~~~~~~

* tar.gz archive
* zip archive
* Debian Package (rt)
* NSIS Installer (rt)
* Mac Bundle?
* press release

2.x/Ideas
~~~~~~~~~

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
* CAD Command: GripColor & GripCool
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
* Hilburt Curve Fill
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
* emscripten/javascript port of libembroidery

Embedded
--------

Arduino
~~~~~~~

* Fix emb-outline files
* Fix thread-color files
* Logging of Last Stitch Location to External USB Storage(commonly available and easily replaced) ...wait until TRE is available to avoid rework
* inotool.org - seems like the logical solution for Nightly/CI builds
* Smoothieboard experiments

libembroidery-tests
-------------------

* looping test that reads 10 times while running valgrind. See embPattern_loadExternalColorFile() Arduino leak note for more info.

Contact us
==========

For general questions email: `embroidermodder at gmail.com <mailto:embroidermodder@gmail.com>`_.

To request a new feature `open an issue on the main Embroidermodder GitHub repository <https://github.com/Embroidermodder/Embroidermodder/issues>`_.
We'll move it to the correct repository.
