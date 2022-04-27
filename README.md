# 1. Libembroidery v1.0-alpha Manual

(Under construction, please wait for v1.0 release.)

## 1.1. What is libembroidery?

libembroidery is a low-level library for reading, writing, 
and altering digital embroidery files in C.

libembroidery is the underlying library that is used by [Embroidermodder 2](http://embroidermodder.org)
and is developed by [The Embroidermodder Team](#the-embroidermodder-team).
It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

It also includes a CLI called `embroider` that allows for better automation of
changes to embroidery files and will be more up-to date than
the Embroidermodder 2 GUI.

If you want to find a simple fix to contribute see the *Development* section
of the manual.

https://embroidermodder.org

Copyright (c) 2013-2022 The EmbroiderModder Team

## 1.2. Table of Contents

- [1. Libembroidery v1.0-alpha Manual](#1-libembroidery-v10-alpha-manual)
  - [1.1. What is libembroidery?](#11-what-is-libembroidery)
  - [1.2. Table of Contents](#12-table-of-contents)
    - [1.2.1. License](#121-license)
    - [1.2.2. The Embroidermodder Project](#122-the-embroidermodder-project)
    - [1.2.3. The Embroidermodder Team](#123-the-embroidermodder-team)
  - [1.3. Build](#13-build)
    - [1.3.1. Debug](#131-debug)
  - [1.4. Usage](#14-usage)
    - [1.4.1. To Flag](#141-to-flag)
    - [1.4.2. Circle Flag](#142-circle-flag)
    - [1.4.3. Ellipse Flag](#143-ellipse-flag)
    - [1.4.4. Line Flag](#144-line-flag)
    - [1.4.5. Polyline Flag](#145-polyline-flag)
    - [1.4.6. Polygon Flag](#146-polygon-flag)
    - [1.4.7. Satin Flag](#147-satin-flag)
    - [1.4.8. Stitch Flag](#148-stitch-flag)
    - [1.4.9.](#149)
    - [1.4.10. Basic Test Suite](#1410-basic-test-suite)
    - [1.4.11. Full Test Suite](#1411-full-test-suite)
  - [1.5. Ideas](#15-ideas)
      - [1.5.0.1. Rendering system](#1501-rendering-system)
      - [1.5.0.2. Binary download](#1502-binary-download)
      - [1.5.0.3. Identify the meaning of these TODO items](#1503-identify-the-meaning-of-these-todo-items)
      - [1.5.0.4. Progress Chart](#1504-progress-chart)
      - [1.5.0.5. Tactile art and braille support](#1505-tactile-art-and-braille-support)
  - [1.6. Development](#16-development)
    - [1.6.1. Contributing](#161-contributing)
      - [1.6.1.1. Style](#1611-style)
      - [1.6.1.2. Standard](#1612-standard)
    - [1.6.2. Image Fitting](#162-image-fitting)
    - [1.6.3. To Place](#163-to-place)
    - [1.6.4. To Do](#164-to-do)
      - [1.6.4.1. Basic features.](#1641-basic-features)
      - [1.6.4.2. Code quality and user friendliness](#1642-code-quality-and-user-friendliness)
      - [1.6.4.3. embroider CLI](#1643-embroider-cli)
        - [1.6.4.3.1. Embroider pipeline](#16431-embroider-pipeline)
      - [1.6.4.4. Documentation](#1644-documentation)
      - [1.6.4.5. GUI](#1645-gui)
      - [1.6.4.6. Electronics development](#1646-electronics-development)
  - [1.7. Formats](#17-formats)
    - [1.7.1. Overview](#171-overview)
      - [1.7.1.1. Read/Write Support Levels](#1711-readwrite-support-levels)
      - [1.7.1.2. Test Support Levels](#1712-test-support-levels)
      - [1.7.1.3. Documentation Support Levels](#1713-documentation-support-levels)
      - [1.7.1.4. Table of Format Support Levels](#1714-table-of-format-support-levels)
    - [1.7.2. Toyota Embroidery Format (.100)](#172-toyota-embroidery-format-100)
    - [1.7.3. Toyota Embroidery Format (.10o)](#173-toyota-embroidery-format-10o)
    - [1.7.4. Bernina Embroidery Format (.art)](#174-bernina-embroidery-format-art)
    - [1.7.5. Bitmap Cache Embroidery Format (.bmc)](#175-bitmap-cache-embroidery-format-bmc)
    - [1.7.6. Bits and Volts Embroidery Format (.bro)](#176-bits-and-volts-embroidery-format-bro)
    - [1.7.7. Melco Embroidery Format (.cnd)](#177-melco-embroidery-format-cnd)
    - [1.7.8. Embroidery Thread Color Format (.col)](#178-embroidery-thread-color-format-col)
      - [1.7.8.1. Example](#1781-example)
    - [1.7.9. Singer Embroidery Format (.csd)](#179-singer-embroidery-format-csd)
    - [1.7.10. Comma Separated Values (.csv)](#1710-comma-separated-values-csv)
    - [1.7.11. Barudan Embroidery Format (.dat)](#1711-barudan-embroidery-format-dat)
    - [1.7.12. Melco Embroidery Format (.dem)](#1712-melco-embroidery-format-dem)
    - [1.7.13. Barudan Embroidery Format (.dsb)](#1713-barudan-embroidery-format-dsb)
    - [1.7.14. Tajima Embroidery Format (.dst)](#1714-tajima-embroidery-format-dst)
      - [1.7.14.1. Header](#17141-header)
    - [1.7.15. ZSK USA Embroidery Format (.dsz)](#1715-zsk-usa-embroidery-format-dsz)
    - [1.7.16. Drawing Exchange Format (.dxf)](#1716-drawing-exchange-format-dxf)
    - [1.7.17. Embird Embroidery Format (.edr)](#1717-embird-embroidery-format-edr)
    - [1.7.18. Elna Embroidery Format (.emd)](#1718-elna-embroidery-format-emd)
    - [1.7.19. Melco Embroidery Format (.exp)](#1719-melco-embroidery-format-exp)
    - [1.7.20. Eltac Embroidery Format (.exy)](#1720-eltac-embroidery-format-exy)
    - [1.7.21. Sierra Expanded Embroidery Format (.eys)](#1721-sierra-expanded-embroidery-format-eys)
    - [1.7.22. Fortron Embroidery Format (.fxy)](#1722-fortron-embroidery-format-fxy)
    - [1.7.23. Great Notions Embroidery Format (.gnc)](#1723-great-notions-embroidery-format-gnc)
    - [1.7.24. Gold Thread Embroidery Format (.gt)](#1724-gold-thread-embroidery-format-gt)
    - [1.7.25. Husqvarna Viking Embroidery Format (.hus)](#1725-husqvarna-viking-embroidery-format-hus)
    - [1.7.26. Inbro Embroidery Format (.inb)](#1726-inbro-embroidery-format-inb)
    - [1.7.27. Embroidery Color Format (.inf)](#1727-embroidery-color-format-inf)
    - [1.7.28. Janome Embroidery Format (.jef)](#1728-janome-embroidery-format-jef)
    - [1.7.29. Pfaff professional Design format (.ksm)](#1729-pfaff-professional-design-format-ksm)
    - [1.7.30. Pfaff Embroidery Format (.max)](#1730-pfaff-embroidery-format-max)
    - [1.7.31. Mitsubishi Embroidery Format (.mit)](#1731-mitsubishi-embroidery-format-mit)
    - [1.7.32. Ameco Embroidery Format (.new)](#1732-ameco-embroidery-format-new)
    - [1.7.33. Melco Embroidery Format (.ofm)](#1733-melco-embroidery-format-ofm)
    - [1.7.34. Pfaff PCD File Format](#1734-pfaff-pcd-file-format)
    - [1.7.35. Pfaff Embroidery Format (.pcm)](#1735-pfaff-embroidery-format-pcm)
    - [1.7.36. Pfaff Embroidery Format (.pcq)](#1736-pfaff-embroidery-format-pcq)
    - [1.7.37. Pfaff Embroidery Format (.pcs)](#1737-pfaff-embroidery-format-pcs)
    - [1.7.38. Brother Embroidery Format (.pec)](#1738-brother-embroidery-format-pec)
    - [1.7.39. Brother Embroidery Format (.pel)](#1739-brother-embroidery-format-pel)
    - [1.7.40. Brother Embroidery Format (.pem)](#1740-brother-embroidery-format-pem)
    - [1.7.41. Brother Embroidery Format (.pes)](#1741-brother-embroidery-format-pes)
    - [1.7.42. Brother Embroidery Format (.phb)](#1742-brother-embroidery-format-phb)
    - [1.7.43. Brother Embroidery Format (.phc)](#1743-brother-embroidery-format-phc)
    - [1.7.44. AutoCAD Embroidery Format (.plt)](#1744-autocad-embroidery-format-plt)
    - [1.7.45. RGB Embroidery Format (.rgb)](#1745-rgb-embroidery-format-rgb)
    - [1.7.46. Janome Embroidery Format (.sew)](#1746-janome-embroidery-format-sew)
    - [1.7.47. Husqvarna Viking Embroidery Format (.shv)](#1747-husqvarna-viking-embroidery-format-shv)
    - [1.7.48. Sunstar Embroidery Format (.sst)](#1748-sunstar-embroidery-format-sst)
    - [1.7.49. Data Stitch Embroidery Format (.stx)](#1749-data-stitch-embroidery-format-stx)
    - [1.7.50. Scalable Vector Graphics (.svg)](#1750-scalable-vector-graphics-svg)
    - [1.7.51. Pfaff Embroidery Format (.t01)](#1751-pfaff-embroidery-format-t01)
    - [1.7.52. Pfaff Embroidery Format (.t09)](#1752-pfaff-embroidery-format-t09)
    - [1.7.53. Happy Embroidery Format (.tap)](#1753-happy-embroidery-format-tap)
    - [1.7.54. ThredWorks Embroidery Format (.thr)](#1754-thredworks-embroidery-format-thr)
    - [1.7.55. Text File (.txt)](#1755-text-file-txt)
    - [1.7.56. Barudan Embroidery Format (.u00)](#1756-barudan-embroidery-format-u00)
    - [1.7.57. Barudan Embroidery Format (.u01)](#1757-barudan-embroidery-format-u01)
    - [1.7.58. Pfaff Embroidery Format (.vip)](#1758-pfaff-embroidery-format-vip)
    - [1.7.59. Pfaff Embroidery Format (.vp3)](#1759-pfaff-embroidery-format-vp3)
    - [1.7.60. Singer Embroidery Format (.xxx)](#1760-singer-embroidery-format-xxx)
    - [1.7.61. ZSK USA Embroidery Format (.zsk)](#1761-zsk-usa-embroidery-format-zsk)
  - [1.8. On Embedded Systems](#18-on-embedded-systems)
    - [1.8.1. Compatible Boards](#181-compatible-boards)
    - [1.8.2. Arduino Considerations](#182-arduino-considerations)
    - [1.8.3. Space](#183-space)
    - [1.8.4. Tables](#184-tables)
    - [1.8.5. Current Pattern Memory Management](#185-current-pattern-memory-management)
    - [1.8.6. Special Notes](#186-special-notes)
  - [1.9. The Assembly Split](#19-the-assembly-split)
  - [1.10. Build](#110-build)
  - [1.11. Features](#111-features)
    - [1.11.1. Bindings](#1111-bindings)
  - [1.12. Threads](#112-threads)
    - [1.12.1. DXF color table](#1121-dxf-color-table)
    - [1.12.2. HUS color table](#1122-hus-color-table)
    - [1.12.3. JEF color table](#1123-jef-color-table)
    - [1.12.4. PCM color table](#1124-pcm-color-table)
    - [1.12.5. PEC color table](#1125-pec-color-table)
  - [1.13. Other Supported Thread Brands](#113-other-supported-thread-brands)
  - [1.14. Bibliography](#114-bibliography)

### 1.2.1. License

Libembroidery is distributed under the permissive zlib licence, see the 
LICENCE file. This applies to all the source code in this directory.

### 1.2.2. The Embroidermodder Project

The _Embroidermodder 2_ project is a collection of small software utilities for
manipulating, converting and creating embroidery files in all major embroidery
machine formats. The program _Embroidermodder 2_ itself is a larger graphical
user interface (GUI) which is at the heart of the project.

This manual, the website (`embroidermodder.org`), mobile embroidery format viewers
and tools (`iMobileViewer`, `MobileViewer`), the core library of functions
(`libembroidery`) and CLI (`embroider`) are all tools to make the standard
user experience of working with an embroidery machine better without expensive
software which is locked to specific manufacturers and formats. But ultimately
we hope that the core _Embroidermodder 2_ is a practical, ever-present tool in
larger workshops, small cottage industry workshops and personal hobbyist's
bedrooms.

Embroidermodder 2 is licensed under the zlib license and we aim to keep all of
our tools open source and free of charge. If you would like to support the
project check out our Open Collective group. If you would like to help, please
join us on GitHub. This document is written as developer training as well
helping new users (see the last sections) so this is the place to learn how
to start changing the code.

### 1.2.3. The Embroidermodder Team

The Embroidermodder Team is the collection of people who've submitted
patches, artwork and documentation to our three projects.
The team was established by Jonathan Greig and Josh Varga.
For a full list of members please see the
[Embroidermodder github page](https://github.com/Embroidermodder/Embroidermodder)
where it is actively maintained.

## 1.3. Build

libembroidery and EmbroiderModder 2 use CMake builds
so if you are building the project to use as a library we recommend
you run:
 
```
git clone https://github.com/Embroidermodder/libembroidery
cd libembroidery
cmake .
cmake --build .
cmake --install .
```

This builds both the static and shared versions of the library as well
as the command line program `embroider`.

### 1.3.1. Debug

If you wish to help with development, [run this debug script](https://embroidermodder.org/libembroidery_debugger.sh) and send us the error log.
Note: this is maintained outside of the repository because it gives us a oneliner for new systems with a stable URL:
```
curl https://embroidermodder.org/libembroidery_debugger.sh | sh
```

While we will attempt to maintain good results from this script as part of normal development
it should be the first point of failure on any system we haven't tested or format we understand less.

## 1.4. Usage

For basic use, we recommend you build as above, then run without arguments:

    $ embroider

which will print out this advice on how to use these tools without digging
straight into the rest of this manual.

    EMBROIDER
        A command line program for machine embroidery.
        Copyright 2013-2021 The Embroidermodder Team
        Licensed under the terms of the zlib license.

        https://github.com/Embroidermodder/libembroidery
        https://embroidermodder.org

    Usage: embroider [OPTIONS] fileToRead...

    Conversion:
    -t, -to         Convert all files given to the format specified
                    by the arguments to the flag, for example:
                        $ embroider -t dst input.pes
                    would convert \"input.pes\" to \"input.dst\"
                    in the same directory the program runs in.

                    The accepted input formats are (TO BE DETERMINED).
                    The accepted output formats are (TO BE DETERMINED).

    Output:
    -h, -help       Print this message.
    -f, -format     Print help on the formats that
                    embroider can deal with.
    -q, -quiet      Only print fatal errors.
    -V, -verbose    Print everything that has reporting.
    -v, -version    Print the version.

    Graphics:
    -c, -circle     Add a circle defined by the arguments
                    given to the current pattern.
    -e, -ellipse    Add a circle defined by the arguments
                    given to the current pattern.
    -l, -line       Add a line defined by the arguments
                    given to the current pattern.
    -P, -polyline   Add a polyline.
    -p, -polygon    Add a polygon.
    -s, -satin      Fill the current geometry with satin
                    stitches according
                    to the defined algorithm.
    -S, -stitch     Add a stitch defined by the arguments
                    given to the current pattern.

    Quality Assurance:
        -test       Run the test suite.

For each of the flags described here we will go into greater detail in this manual.

### 1.4.1. To Flag

### 1.4.2. Circle Flag

### 1.4.3. Ellipse Flag

### 1.4.4. Line Flag

### 1.4.5. Polyline Flag

### 1.4.6. Polygon Flag

### 1.4.7. Satin Flag

### 1.4.8. Stitch Flag

### 1.4.9. 

### 1.4.10. Basic Test Suite

The flag `--test` runs the tests that take the least time and have the
most utility. If you're submitting a patch for review, please run:

    $ embroider --test | tail -n 1

You'll be presented with an overall PASS or FAIL for your build,
if your build fails you can try and trace the error with:

    $ valgrind embroider --verbose --test

or

    $ gdb --args embroider --verbose --test

depending on your preferred debugging approach. Passing this test
will be required for us to accept your patch.

### 1.4.11. Full Test Suite

The flag `--full-test-suite` runs all the tests that have been written.
Since this results in a lot of output the details are both to stdout
and to a text file called `test_matrix.txt`.

Patches that strictly improve the results in the `test_matrix.txt` over
the current version will likely be accepted and it'll be a good place
to go digging for contributions. (Note: strictly improve means that
the testing result for each test is as good a result, if not better.
Sacrificing one critera for another would require some design work
before we would consider it.)

## 1.5. Ideas

#### 1.5.0.1. Rendering system

There are two forms of render that will be produced.

1. A raster format as ppm so we can have a pixel for pixel output (for example extracting the embedded images in some formats).
2. The SVG format that will be fairly similar to InkStitch's format.

We have an EmbImage struct to store the raster format.

    $ embroider test01.csv --render

currently creates a blank image. Previously the Hilbert curve test managed to
create a correctly rendered version.

#### 1.5.0.2. Binary download

We need a current `embroider` command line program download, so people can update
without building.

#### 1.5.0.3. Identify the meaning of these TODO items

* Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug #179
* Lego Mindstorms NXT/EV3 ports and/or commands

#### 1.5.0.4. Progress Chart

The chart of successful from-to conversions (previously a separate issue)
is something that should appear in the README.

#### 1.5.0.5. Tactile art and braille support

One application I'd like to leave a reminder here for is automating embroidery
for blind and partially sighted people.

There are many limitations to making braille (cost, poor support, lack of
widespread adoption in the sighted world) and as such there is a strong DIY
culture around it.

There are blind internet users who can also run terminal applications using a
refreshable braille display, so in theory we could support an application like
this for them:

    $ embroider --braille "Hello, world!" hello.dst

which would produce braille that would read "Hello, world!" as an embroidery
design.

Another option is tactile fills that use the same fill algorithms but are
designed better to facilitate tactile art.

I think the way forward on this is to call up the RNIB business advice line and
ask for assistance once we have a working model. That way they can get us in
contact with experts to review how legible the output is and usable the
software is for the intended audience.

This is less important than getting better machine support but given the high
social impact I think it should be a priority.

## 1.6. Development

### 1.6.1. Contributing

If you're interested in getting involved, here's some guidance
for new developers. Currently The Embroidermodder Team is all
hobbyists with an interest in making embroidery machines more
open and user friendly. If you'd like to support us in some other way
you can donate to our Open Collective page (click the Donate button) so
we can spend more time working on the project.

All code written for libembroidery should be ANSI C89 compliant
if it is C. Using other languages should only be used where
necessary to support bindings.

#### 1.6.1.1. Style

Rather than maintain our own standard for style, please defer to
the Python's PEP 7 ([12](#12)) for C style.
If it passes the linters for that we consider it well styled
for a pull request.

As for other languages we have no house style other than whatever
"major" styles exist, for example Java in
Google style ([13](#13))
would be acceptable. We'll elect specific standards if it becomes
an issue.

#### 1.6.1.2. Standard

The criteria for a good Pull Request from an outside developer is,
from most to least important:

1. No regressions on testing.
2. Add a feature, bug fix or documentation that is already agreed on
   through GitHub issues or some other way with a core developer.
3. No GUI specific code should be in libembroidery, that's for Embroidermodder.
4. Pedantic/ansi C unless there's a good reason to use another language.
5. Meet the style above (i.e. [PEP 7, Code Lay-out](https://peps.python.org/pep-0007/#code-lay-out)).
   We'll just fix the style if the code's good and it's not a lot of work.
6. `embroider` should be in POSIX style as a command line program.
7. No dependancies that aren't "standard", i.e. use only the C Standard Library.

### 1.6.2. Image Fitting

A currently unsolved problem in development that warrants further research is
the scenario where a user wants to feed embroider an image that can then be .

### 1.6.3. To Place

A _right-handed coordinate system_ is one where up is positive and right is
positive. Left-handed is up is positive, left is positive. Screens often use
down is positive, right is positive, including the OpenGL standard so when
switching between graphics formats and stitch formats we need to use a vertical
flip (`embPattern_flip`).

`0x20` is the space symbol, so when padding either 0 or space is preferred and
in the case of space use the literal ' '.

### 1.6.4. To Do

We currently need help with:

1. Thorough descriptions of each embroidery format.
2. Finding resources for each of the branded thread libraries
   (along with a full citation for documentation).
3. Finding resources for each geometric algorithm used (along with a
   full citation for documentation).
4. Completing the full `--full-test-suite`  with no segfaults and at least
   a clear error message (for example "not implemented yet").
5. Identifying "best guesses" for filling in missing information when going
   from, say `.csv` to a late `.pes` version. What should the default be when
   the data doesn't clarify?
6. Improving the written documentation.
7. Funding, see the Sponsor button above. We can treat this as "work" and put
   far more hours in with broad support in small donations from people who
   want specific features.

Beyond this the development targets are categories sorted into:

1. [Basic Features](#basic-features)
2. [Code quality and user friendliness](#code-quality-and-user-friendliness)
3. [embroider CLI](#embroider-cli)
4. [Documentation](#documentation)
5. [GUI](#gui)
6. [electronics development](#electronics-development)

#### 1.6.4.1. Basic features.

1. Incorporate \texttt{\#if\ 0}ed parts of \texttt{libembroidery.c}.
2. Interpret how to write formats that have a read mode from the source
   code and vice versa.
3. Document the specifics of the file formats here for embroidery machine
   specific formats. Find websites and other sources that break down the
   binary formats we currently don't understand.
4. Find more and better documentation of the structure of the headers for
   the formats we do understand.

#### 1.6.4.2. Code quality and user friendliness

1. Document all structs, macros and functions (will contribute directly
   on the web version).
2. Incorporate experimental code, improve support for language bindings.
3. Make stitch x, y into an EmbVector.

#### 1.6.4.3. embroider CLI

1. Make -circle flag to add a circle to the current pattern.
2. Make -rect flag to add a rectangle to the current pattern.
3. Make -fill flag to set the current satin fill algorithm for the current
   geometry. (for example ``-fill crosses -circle 11,13,10'' fills a circle
   with center 11mm, 13mm with radius 10mm with crosses).
4. Make -ellipse flag to add to ellipse to the current pattern.
5. Make -bezier flag to add a bezier curve to the current pattern.

##### 1.6.4.3.1. Embroider pipeline

Adjectives apply to every following noun so

```
embroider --satin 0.3,0.6 --thickness 2 --circle 10,20,5 \
    --border 3 --disc 30,40,10 --arc 30,50,10,60 output.pes
```

Creates:

1. a circle with properties: thickness 2, satin 0.3,0.6
2. a disc with properties: 
3. an arc with properties:

in that order then writes them to the output file `output.pes`.

#### 1.6.4.4. Documentation

1. Create csv data files for thread tables.
2. Convert tex to markdown, make tex an output of `build.bash`.
3. Run `sloccount` on `extern/` and `.` (and ) so we know the current scale
   of the project, aim to get this number low. Report the total as part of
   the documentation.
4. Try to get as much of the source code that we maintain into C as possible
   so new developers don't need to learn multiple languages to have an effect.
   This bars the embedded parts of the code. 

#### 1.6.4.5. GUI

1. Make MobileViewer also backend to `libembroidery` with a Java wrapper.
2. Make iMobileViewer also backend to `libembroidery` with a Swift wrapper.
3. Share some of the MobileViewer and iMobileViewer layout with the main
   EM2. Perhaps combine those 3 into the Embroidermodder repository so there
   are 4 repositories total.
4. Convert layout data to JSON format and use cJSON for parsing.

#### 1.6.4.6. Electronics development

1. Currently experimenting with Fritzing^(*8*), upload netlists to embroiderbot
   when they can run simulations using the asm in `libembroidery`.
2. Create a common assembly for data that is the same across chipsets
   `libembrodiery_data_internal.s`.
3. Make the defines part of `embroidery.h` all systems and the function list
   "c code only". That way we can share some development between assembly and C
   versions.

## 1.7. Formats

### 1.7.1. Overview

#### 1.7.1.1. Read/Write Support Levels

The table of read/write format support levels uses the status levels described here:

| Status | Description |
|---|---|
| None (0) | Either the format produces no output, reporting an error. Or it produces a Tajima dst file as an alternative. |
| Poor (1) | A file somewhat similar to our examples is produced. We don't know how well it runs on machines in practice as we don't have any user reports or personal tests. |
| Basic (2) | Simple files in this format run well on machines that use this format. |
| Standard (3) | Files with non-standard features work on machines and we have good documentation on the format. |
| Reliable (4) | All known features don't cause crashes. Almost all work as expected. |
| Good (5) | All known features of the format work on machines that use this format. Translations from and to this format preserve all features present in both. |

So all formats can, in principle, have good read and good write support, because it's defined in relation to files that we have described the formats for.

#### 1.7.1.2. Test Support Levels

| Status | Description |
|---|---|
| None (0) | No tests have been written to test the specifics of the format. |
| Basic (1) | Stitch Lists and/or colors have read/write tests. |
| Thorough (2) | All features of that format has at least one test. |
| Fuzz (2) | Can test the format for uses of features that we haven't thought of by feeding in nonsense that is designed to push possibly dangerous weaknesses to reveal themselves. |
| Complete (3) | Both thorough and fuzz testing is covered. |

So all formats can, in principle, have complete testing support, because it's defined in relation to files that we have described the formats for.

#### 1.7.1.3. Documentation Support Levels

| Status | Description |
|---|---|
| None (0) | We haven't researched this beyond finding example files. |
| Basic (1) | We have a rough sketch of the size and contents of the header if there is one. We know the basic stitch encoding (if there is one), but not necessarily all stitch features. |
| Standard (2) | We know some good sources and/or have tested all the features that appear to exist. They mostly work the way we have described. |
| Good (3) | All features that were described somewhere have been covered here or we have thoroughly tested our ideas against other softwares and hardwares and they work as expected. |
| Complete (4) | There is a known official description and our description covers all the same features. |

Not all formats can have complete documentation because it's based on what 
information is publically available. So the total score is reported in the table
below based on what level we think is available.

#### 1.7.1.4. Table of Format Support Levels

| *Format* | *Read Support* | *Write Support* | *Specialised Tests* | *Documentation* | *Score* |
|---|---|---|---|---|---|
| [Toyota Embroidery Format (.100)](#toyota-embroidery-format-100) | Basic | Basic | None | None | 2/11 |
| [Toyota Embroidery Format (.10o)](#toyota-embroidery-format-10o) | Basic | Basic | None | None | 2/11 |
| [Bernina Embroidery Format (.art)](#bernina-embroidery-format-art) | None | None | None | None | 0/11 |
| [Bitmap Cache Embroidery Format (.bmc)](#bitmap-cache-embroidery-format-bmc) | Basic | None | None | None | 1/11 |
| [Bits and Volts Embroidery Format (.bro)](#bits-and-volts-embroidery-format-bro) | None | None | None | None | 0/11 |
| [Melco Embroidery Format (.cnd)](#melco-embroidery-format-cnd) | None | None | None | None | 0/11 |
| [Embroidery Thread Color Format (.col)](#embroidery-thread-color-format-col) | Basic | Basic | None | Basic | 0/11 |
| [Singer Embroidery Format (.csd)](#singer-embroidery-format-csd) | None | None | None | None | 0/11 |
| [Comma Separated Values (.csv)](#comma-seperated-values-csv) | None | None | None | None | 0/11 |
| [Barudan Embroidery Format (.dat)](#barudan-embroidery-format-dat) | None | None | None | None | 0/11 |
| [Melco Embroidery Format (.dem)](#melco-embroidery-format-dem) | None | None | None | None | 0/11 |
| [Barudan Embroidery Format (.dsb)](#barudan-embroidery-format-dsb) | None | None | None | None | 0/11 |
| [Tajima Embroidery Format (.dst)](#tajima-embroidery-format-dst) | None | None | None | None | 0/11 |
| [ZSK USA Embroidery Format (.dsz)](#zsk-usa-embroidery-format-dsz) | None | None | None | None | 0/11 |
| [Drawing Exchange Format (.dxf)](#drawing-exchange-format-dxf) | None | None | None | None | 0/11 |
| [Embird Embroidery Format (.edr)](#embird-embroidery-format-edr) | None | None | None | None | 0/11 |
| [Elna Embroidery Format (.emd)](#elna-embroidery-format-emd) | None | None | None | None | 0/11 |
| [Melco Embroidery Format (.exp)](#melco-embroidery-format-exp) | None | None | None | None | 0/11 |
| [Eltac Embroidery Format (.exy)](#eltac-embroidery-format-exy) | None | None | None | None | 0/11 |
| [Sierra Expanded Embroidery Format (.eys)](#sierra-expanded-embroidery-format-eys) | None | None | None | None | 0/11 |
| [Fortron Embroidery Format (.fxy)](#fortran-embroidery-format-fxy) | None | None | None | None | 0/11 |
| [Smoothie G-Code Embroidery Format (.gc)](#smoothie-g-code-embroidery-format-gc) | None | None | None | None | 0/11 |
| [Great Notions Embroidery Format (.gnc)](#great-notions-embroidery-format-gnc) | None | None | None | None | 0/11 |
| [Gold Thread Embroidery Format (.gt)](#gold-thread-embroidery-format-gt) | None | None | None | None | 0/11 |
| [Husqvarna Viking Embroidery Format (.hus)](#husqvarna-viking-embroidery-format-hus) | None | None | None | None | 0/11 |
| [Inbro Embroidery Format (.inb)](#inbro-embroidery-format-inb) | None | None | None | None | 0/11 |
| [Embroidery Color Format (.inf)](#embroidery-color-format-inf) | None | None | None | None | 0/11 |
| [Janome Embroidery Format (.jef)](#janome-embroidery-format-jef) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.ksm)](#pfaff-embroidery-format-ksm) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.max)](#pfaff-embroidery-format-max) | None | None | None | None | 0/11 |
| [Mitsubishi Embroidery Format (.mit)](#mitsubishi-embroidery-format-mit) | None | None | None | None | 0/11 |
| [Ameco Embroidery Format (.new)](#ameco-embroidery-format-new) | None | None | None | None | 0/11 |
| [Melco Embroidery Format (.ofm)](#melco-embroidery-format-ofm) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.pcd)](#pfaff-embroidery-format-pcd) |  None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.pcm)](#pfaff-embroidery-format-pcm) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.pcq)](#pfaff-embroidery-format-pcq) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.pcs)](#pfaff-embroidery-format-pcs) | None | None | None | None | 0/11 |
| [Brother Embroidery Format (.pec)](#brother-embroidery-format-pec) | None | None | None | None | 0/11 |
| [Brother Embroidery Format (.pel)](#brother-embroidery-format-pel) | None | None | None | None | 0/11 |
| [Brother Embroidery Format (.pem)](#brother-embroidery-format-pem) | None | None | None | None | 0/11 |
| [Brother Embroidery Format (.pes)](#brother-embroidery-format-pes) | None | None | None | None | 0/11 |
| [Brother Embroidery Format (.phb)](#brother-embroidery-format-phb) | None | None | None | None | 0/11 |
| [Brother Embroidery Format (.phc)](#brother-embroidery-format-phc) | None | None | None | None | 0/11 |
| [AutoCAD Embroidery Format (.plt)](#brother-embroidery-format-plt) | None | None | None | None | 0/11 |
| [RGB Embroidery Format (.rgb)](#rgb-embroidery-format-rgb) | None | None | None | None | 0/11 |
| [Janome Embroidery Format (.sew)](#janome-embroidery-format-sew) | None | None | None | None | 0/11 |
| [Husqvarna Viking Embroidery Format (.shv)](#husqvarna-viking-embroidery-format-shv) | None | None | None | None | 0/11 |
| [Sunstar Embroidery Format (.sst)](#sunstar-embroidery-format-sst) | None | None | None | None | 0/11 |
| [Data Stitch Embroidery Format (.stx)](#data-stitch-embroidery-format-stx) | None | None | None | None | 0/11 |
| [Scalable Vector Graphics (.svg)](#scalable-vector-graphics-svg) | None | None | None | None | 0/12 |
| [Pfaff Embroidery Format (.t01)](#pfaff-embroidery-format-t01) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.t09)](#pfaff-embroidery-format-t09) | None | None | None | None | 0/11 |
| [Happy Embroidery Format (.tap)](#happy-embroidery-format-tap) | None | None | None | None | 0/11 |
| [ThredWorks Embroidery Format (.thr)](#thredworks-embroidery-format-thr) | None | None | None | None | 0/11 |
| [Text File (.txt)](#text_file_txt) | None | None | None | None | 0/11 |
| [Barudan Embroidery Format (.u00)](#barudan-embroidery-format-u00) | None | None | None | None | 0/11 |
| [Barudan Embroidery Format (.u01)](#barudan-embroidery-format-u01) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.vip)](#pfaff-embroidery-format-vip) | None | None | None | None | 0/11 |
| [Pfaff Embroidery Format (.vp3)](#pfaff-embroidery-format-vp3) | None | None | None | None | 0/11 |
| [Singer Embroidery Format (.xxx)](#singer-embroidery-format-xxx) | None | None | None | None | 0/11 |
| [ZSK USA Embroidery Format (.zsk)](#zsk_usa_embroidery_format_zsk) | None | | None | None | None | 0/11 |
| *Total* | - | - | - | - | 0/671 |

For a total of 0% coverage.

### 1.7.2. Toyota Embroidery Format (.100)

The Toyota 100 format is a stitch-only format that uses an external color file.

The stitch encoding is in 4 byte chunks.

### 1.7.3. Toyota Embroidery Format (.10o)

The Toyota 10o format is a stitch-only format that uses an external color file.

The stitch encoding is in 3 byte chunks.

### 1.7.4. Bernina Embroidery Format (.art)

We don't know much about this format. TODO: Find a source.

### 1.7.5. Bitmap Cache Embroidery Format (.bmc)

We don't know much about this format. TODO: Find a source.

### 1.7.6. Bits and Volts Embroidery Format (.bro)

The Bits and Volts bro format is a stitch-only format that uses an external color file.

The header is 256 bytes. There's a series of unknown variables in the
header.

The stitch list uses a variable length encoding which is 2 bytes for any
stitch

### 1.7.7. Melco Embroidery Format (.cnd)

The Melco cnd format is a stitch-only format.

We don't know much about this format. TODO: Find a source.

### 1.7.8. Embroidery Thread Color Format (.col)

An external color file format for formats that do not record their own colors. 

It is a human-readable format that has a header that is a single line containing
only the number of threads in decimal followed by the windows line break '\r\n'.

Then the rest of the file is a comma seperated value list of all threads with
4 values per line: the index of the thread then the red, green and blue channels
of the color in that order.

#### 1.7.8.1. Example

If we had a pattern called "example" with four colors: black, red, magenta and 
cyan in that order then the file is (with the white space written out):

example.col

    4\r\n
    0,0,0,0\r\n
    1,255,0,0\r\n
    2,0,255,0\r\n
    3,0,0,255\r\n

### 1.7.9. Singer Embroidery Format (.csd)

Stitch Only Format

### 1.7.10. Comma Separated Values (.csv)

Comma Seperated Values files aren't a universal system, here we aim to
offer a broad support.

| Control Symbol | Type |  |
|---|---|---|
| `#` | COMMENT | |
| `>` | VARIABLE | To store records of a pattern's width, height etc. This means that data stored in the header of say a `.dst` file is preserved. |
| `$` | THREAD | |
| `*` | STITCH | |
| `*` | JUMP | |
| `*` | COLOR | To change a color: used for trim as well |
| `*` | END | To end a pattern. |
| `*` | UNKNOWN | For any feature that we can't identify. |

### 1.7.11. Barudan Embroidery Format (.dat)

Stitch Only Format

### 1.7.12. Melco Embroidery Format (.dem)

Stitch Only Format

### 1.7.13. Barudan Embroidery Format (.dsb)

  * Stitch Only Format.
  * [X] Basic Read Support
  * [ ] Basic Write Support
  * [ ] Well Tested Read
  * [ ] Well Tested Write

### 1.7.14. Tajima Embroidery Format (.dst)

  * Stitch Only Format.
  * [X] Basic Read Support
  * [X] Basic Write Support
  * [ ] Well Tested Read
  * [ ] Well Tested Write

.DST (Tajima) embroidery file read/write routines
Format comments are thanks to tspilman@dalcoathletic.com who's
notes appeared at \url{http://www.wotsit.org} under Tajima Format.

#### 1.7.14.1. Header

The header seems to contain information about the design.
Seems to be ASCII text delimited by 0x0D (carriage returns).
This must be in the file for most new software or hardware
to consider it a good file! This is much more important
than I originally believed. The header is 125 bytes in
length and padded out by 0x20 to 512 bytes total.
All entries in the header seem to be 2 ASCII characters
followed by a colon, then it's value trailed by a carriage return.

| *C memory* | *Description* |
|------------|-------------|
| `char LA[16+1];` | First is the 'LA' entry, which is the design name with no path or extension information. The blank is 16 characters in total, but the name must not be longer that 8 characters and padded out with spaces (0x20). |
| `char ST[7+1];` | Next is the stitch count ST, this is a 7 digit number padded by leading zeros. This is the total stitch count including color changes, jumps, nups, and special records. |
| `char CO[3+1];` | Next, is CO or colors, a 3 digit number padded by leading zeros. This is the number of color change records in the file. |
| `char POSX[5+1];` | Next is +X or the positive X extent in centimeters, a 5 digit non-decimal number padded by leading zeros. |
| `char NEGX[5+1];` | Following is the -X or the negative X extent in millimeters, a 5 digit non-decimal number padded by leading zeros. |
| `char POSY[5+1];` | Again, the +Y extents. |
| `char NEGY[5+1];` | Again, the -Y extents. |
| `char AX[6+1]; char AY[6+1];` | AX and AY should express the relative coordinates of the last point from the start point in 0.1 mm. If the start and last points are the same, the coordinates are (0,0). |
| `char MX[6+1];` `char MY[6+1];` | MX and MY should express coordinates of the last point of the previous file for a multi-volume design. A multi-volume design means a design consisted of two or more files. This was used for huge designs that can not be stored in a single paper tape roll. It is not used so much (almost never) nowadays. |
| `char PD[9+1];` | PD is also storing some information for multi-volume design. |

Uses 3 byte per stitch encoding with the format as follows:

The 3 byte encoding for the dxf format.

| *Bit* | *7* | *6* | *5* | *4* | *3* | *2* | *1* | *0* |
|----|----|----|----|----|----|----|----|----|
| Byte 0 | y+1 | y-1 | y+9 | y-9 | x-9 | x+9 | x-1 | x+1 |
| Byte 1 | y+3 | y-3 | y+27 | y-27 | x-27 | x+27 | x-3 | x+3 |
| Byte 2 | jump | color change | y+81 | y-81 | x-81 | x+81 | set | set |

T01 and Tap appear to use Tajima Ternary.
 
Where the stitch type is determined as:

  * Normal Stitch `00000011 0x03`
  * Jump Stitch `10000011 0x83`
  * Stop/Change Color `11000011 0xC3`
  * End Design `11110011 0xF3`

Inclusive or'ed with the last byte.

Note that:

  1. The max stitch length is the largest sum of `1+3+9+27+81=121` where the unit length is 0.1mm so 12.1mm.
  2. The coordinate system is right handed.


### 1.7.15. ZSK USA Embroidery Format (.dsz)

The ZSK USA dsz format is stitch-only.

### 1.7.16. Drawing Exchange Format (.dxf)

Graphics format.

### 1.7.17. Embird Embroidery Format (.edr)

Stitch Only Format

### 1.7.18. Elna Embroidery Format (.emd)

Stitch Only Format.

### 1.7.19. Melco Embroidery Format (.exp)

Stitch Only Format.

### 1.7.20. Eltac Embroidery Format (.exy)

Stitch Only Format.

### 1.7.21. Sierra Expanded Embroidery Format (.eys)

Stitch Only Format.

Smoothie G-Code Embroidery Format (.fxy)?

### 1.7.22. Fortron Embroidery Format (.fxy)

Stitch Only Format.

### 1.7.23. Great Notions Embroidery Format (.gnc)

Stitch Only Format.

### 1.7.24. Gold Thread Embroidery Format (.gt)

Stitch Only Format.

### 1.7.25. Husqvarna Viking Embroidery Format (.hus)

Stitch Only Format.

### 1.7.26. Inbro Embroidery Format (.inb)

Stitch Only Format.

### 1.7.27. Embroidery Color Format (.inf)

Stitch Only Format.

### 1.7.28. Janome Embroidery Format (.jef)

Stitch Only Format.

### 1.7.29. Pfaff professional Design format (.ksm)

Stitch Only Format.

### 1.7.30. Pfaff Embroidery Format (.max)

Stitch Only Format.

### 1.7.31. Mitsubishi Embroidery Format (.mit)

Stitch Only Format.

### 1.7.32. Ameco Embroidery Format (.new)

Stitch Only Format.

### 1.7.33. Melco Embroidery Format (.ofm)

Stitch Only Format.

### 1.7.34. Pfaff PCD File Format

Stitch Only Format.

The format uses a signed 3 byte-length number type.

See the description here ([5](#5)) for the overview of the format.

For an example of the format see ([11](#11)).

### 1.7.35. Pfaff Embroidery Format (.pcm)

The Pfaff pcm format is stitch-only.

### 1.7.36. Pfaff Embroidery Format (.pcq)

The Pfaff pcq format is stitch-only.

### 1.7.37. Pfaff Embroidery Format (.pcs)

The Pfaff pcs format is stitch-only.

### 1.7.38. Brother Embroidery Format (.pec)

The Brother pec format is stitch-only.

### 1.7.39. Brother Embroidery Format (.pel)

The Brother pel format is stitch-only.

### 1.7.40. Brother Embroidery Format (.pem)

The Brother pem format is stitch-only.

### 1.7.41. Brother Embroidery Format (.pes)

The Brother pes format is stitch-only.

```
struct PEShdr
{
char PESId[8];
DWORD PECOffset;
};
```

### 1.7.42. Brother Embroidery Format (.phb)

The Brother phb format is stitch-only.

### 1.7.43. Brother Embroidery Format (.phc)

The Brother phc format is stitch-only.

### 1.7.44. AutoCAD Embroidery Format (.plt)

The AutoCAD plt format is stitch-only.

### 1.7.45. RGB Embroidery Format (.rgb)

The RGB format is a color-only format to act as an external color file for other formats.

### 1.7.46. Janome Embroidery Format (.sew)

The Janome sew format is stitch-only.

### 1.7.47. Husqvarna Viking Embroidery Format (.shv)

The Husqvarna Viking shv format is stitch-only.

### 1.7.48. Sunstar Embroidery Format (.sst)

The Sunstar sst format is stitch-only.

### 1.7.49. Data Stitch Embroidery Format (.stx)

The Data Stitch stx format is stitch-only.

### 1.7.50. Scalable Vector Graphics (.svg)

The scalable vector graphics (SVG) format is a graphics format
maintained by ...

### 1.7.51. Pfaff Embroidery Format (.t01)

The Pfaff t01 format is stitch-only.

### 1.7.52. Pfaff Embroidery Format (.t09)

The Pfaff t09 format is stitch-only.

### 1.7.53. Happy Embroidery Format (.tap)

The Happy tap format is stitch-only.

### 1.7.54. ThredWorks Embroidery Format (.thr)

The ThreadWorks thr format is stitch-only.

### 1.7.55. Text File (.txt)

The txt format is stitch-only and isn't associated with a specific company.

### 1.7.56. Barudan Embroidery Format (.u00)

The Barudan u00 format is stitch-only.

### 1.7.57. Barudan Embroidery Format (.u01)

The Barudan u01 format is stitch-only.

### 1.7.58. Pfaff Embroidery Format (.vip)

The Pfaff vip format is stitch-only.

### 1.7.59. Pfaff Embroidery Format (.vp3)

The Pfaff vp3 format is stitch-only.

### 1.7.60. Singer Embroidery Format (.xxx)

The Singer xxx format is stitch-only.

### 1.7.61. ZSK USA Embroidery Format (.zsk)

The ZSK USA zsk format is stitch-only.
  
## 1.8. On Embedded Systems

The library is designed to support embedded environments, so it can
be used in CNC applications.

### 1.8.1. Compatible Boards

We recommend using an Arduino Mega 2560 or another board with equal or
greater specs. That being said, we have had success using an Arduino Uno
R3 but this will likely require further optimization and other
improvements to ensure continued compatibility with the Uno. See below
for more information.

### 1.8.2. Arduino Considerations

There are two main concerns here: Flash Storage \& SRAM.

libembroidery continually outgrows the 32KB of Flash storage on the
Arduino Uno and every time this occurs, a decision has to be made as to
what capabilities should be included or omitted. While reading files is
the main focus on arduino, writing files may also play a bigger role in
the future. Long term, it would be most practical to handle the
inclusion or omission of any feature via a single configuration header
file that the user can modify to suit their needs.

SRAM is in extremely limited supply and it will deplete quickly so any
dynamic allocation should occur early during the setup phase of the
sketch and sparingly or not at all later in the sketch. To help minimize
SRAM consumption on Arduino and ensure libembroidery can be used in any
way the sketch creator desires, it is required that any sketch using
libembroidery must implement event handlers. See the ino-event source
and header files for more information.

There is also an excellent article by Bill Earl on the Adafruit Learning
System which covers these topics in more depth:
\url{http://learn.adafruit.com/memories-of-an-arduino?view=all}.

### 1.8.3. Space

Since a stitch takes 3 bytes of storage and many patterns use more than
10k stitches, we can't assume that the pattern will fit in memory. Therefore
we will need to buffer the current pattern on and off storage in small
chunks. By the same reasoning, we can't load all of one struct beore
looping so we will need functions similar to binaryReadInt16 for each
struct.

This means the EmbArray approach won't work since we need to load
each element and dynamic memory management is unnecessary because
the arrays lie in storage.

TODO: Replace EmbArray functions with embPattern load functions.

### 1.8.4. Tables

All thread tables and large text blocks are too big to compile directly
into the source code. Instead we can package the library with a data packet
that is compiled from an assembly program in raw format so the specific
padding can be controlled.

In the user section above we will make it clear that this file
needs to be loaded on the pattern USB/SD card or the program won't function.

TODO: Start file with a list of offsets to data with a corresponding table
to load into with macro constants for each label needed.

### 1.8.5. Current Pattern Memory Management

It will be simpler to make one file per EmbArray so we keep an EmbFile*
and a length, so no malloc call is necessary. So there needs to be a consistent
tmpfile naming scheme.

TODO: For each pattern generate a random string of hexadecimal and append it
to the filenames like \texttt{stitchList$\_$A16F.dat}. Need to check for a file
which indicates that this string has been used already.

### 1.8.6. Special Notes

Due to historical reasons and to remain compatible with the Arduino 1.0
IDE, this folder must be called ``utility''. Refer to the arduino build
process for more info:
https://arduino.github.io/arduino-cli/0.19/sketch-build-process/

libembroidery relies on the Arduino SD library for reading files. See
the ino-file source and header files for more information.

## 1.9. The Assembly Split

One problem to the problem of supporting both systems with abundant memory
(such as a 2010s or later desktop) and with scarce memory (such as embedded
systems) is that they don't share the same assembly language. To deal with
this: there will be two equivalent software which are hand engineered to be
similar but one will be in C and the other in the assembly dialects we support.

All assembly will be intended for embedded systems only, since a slightly
smaller set of features will be supported. However, we will write a
`x86` version since that can be tested.

That way the work that has been done to simplify the C code can be applied to
the assembly versions.

## 1.10. Build

To build the documentation run `make`. This should run no problem on a normal Unix-like environment
assuming pandoc is available.

  * Pandoc creates the content of the page by converting the markdown to html.
  * Pandoc also creates the printer-friendly documentation from the same markdown.
  * Markdown acts as a go-between because it is easy to alter directly in the GH editor.

This way:
  1. We write one set of documents for all projects.
  2. The website can be simple and static, supporting machines that don't run javascript.
  3. We control the styling of each version independently of our editing (Markdown) version
  4. The printer-friendly documentation can have nicely rendered fonts and well placed figures.

## 1.11. Features

### 1.11.1. Bindings

Bindings for libembroidery are maintained for the languages we use
internally in the project, for other languages we consider that the
responsibility of other teams using the library.

So libembroidery is going to be supported on:

    * C (by default)
    * C++ (also by default)
    * Java (for the Android application MobileViewer)
    * Swift (for the iOS application iMobileViewer)

For C# we recommend directly calling the function directly
using the DllImport feature:

        [DllImport("libembroidery.so", EntryPoint="readCsv")]

see this StackOverflow discussion [for help](https://stackoverflow.com/questions/11425202/is-it-possible-to-call-a-c-function-from-c-net).

For Python you can do the same using [ctypes](https://www.geeksforgeeks.org/how-to-call-a-c-function-in-python/).

## 1.12. Threads

* [DXF Color Table](#dxf_color_table)
* [HUS Color Table](#hus_color_table)
* [JEF Color Table](#jef_color_table)
* [PCM Color Table](#pcm_color_table)
* [PEC Color Table](#pec_color_table)

### 1.12.1. DXF color table

### 1.12.2. HUS color table

### 1.12.3. JEF color table

### 1.12.4. PCM color table

### 1.12.5. PEC color table

## 1.13. Other Supported Thread Brands

The thread lists that aren't preprogrammed into formats but
are indexed in the data file for the purpose of conversion
or fitting to images/graphics.

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

## 1.14. Bibliography

1. <a name="1"></a> Rudolf _Technical Info_ [http://www.achatina.de/sewing/main/TECHNICL.HTM](http://www.achatina.de/sewing/main/TECHNICL.HTM)
(Accessed 25 November 2021)
2. <a name="2"></a> fineEmbStudio2021
3. <a name="3"></a> Edutech format description (eduTechWikiDST)
4. <a name="4"></a> KDE Liberty Description (libertyTajima)
5. <a name="5"></a> The Sewing Witch _PCD2FMT_ [http://www.sewingwitch.com/sewing/bin/pcd2fmt.html](http://www.sewingwitch.com/sewing/bin/pcd2fmt.html) (Accessed November 2021)
6. <a name="6"></a> [http://steve-jansen.github.io/guides/windows-batch-scripting/part-7-functions.html](http://steve-jansen.github.io/guides/windows-batch-scripting/part-7-functions.html)
7. <a name="7"></a> [https://stackoverflow.com/questions/16286134/imagemagick-how-can-i-work-with-histogram-result](https://stackoverflow.com/questions/16286134/imagemagick-how-can-i-work-with-histogram-result)
8. <a name="8"></a> Fritzing [https://github.com/fritzing/fritzing-app](https://github.com/fritzing/fritzing-app)
9. <a name="9"></a> Sahoo, P., Wilkins, C., and Yeager, J., “Threshold selection using Renyi's entropy”, _Pattern Recognition_, vol. 30, no. 1, pp. 71–84, 1997. doi:10.1016/S0031-3203(96)00065-9.
10. <a name="10"></a> [http://www.fmwconcepts.com/imagemagick/sahoothresh/index.php](http://www.fmwconcepts.com/imagemagick/sahoothresh/index.php) (Accessed 12 Dec 2021)
11. <a name="11"></a> FINDME
12. <a name="12"></a> G. van Rossum and B. Warsaw "Python PEP 7" [https://peps.python.org/pep-0007/](https://peps.python.org/pep-0007/) (Accessed April 2020)
13. <a name="13"></a> Google et al. "Google Java Style Guide" [https://google.github.io/styleguide/javaguide.html](https://google.github.io/styleguide/javaguide.html) (Accessed April 2022)
