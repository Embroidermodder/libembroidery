What is libembroidery ?
-----------------------

libembroidery is the underlying library that is used and
developed by [Embroidermodder 2](http://embroidermodder.github.io).
It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

Build
-----

libembroidery and EmbroiderModder 2 use CMake builds
so if you are building the project to use as a library we recommend:
 
```
git clone https://github.com/Embroidermodder/libembroidery
cd libembroidery
mkdir build
cd build
cmake ..
cmake --build .
```

This builds both the static and shared versions of the library as well
as the command line program `embroider`.

License
-------

Libembroidery is distributed under the permissive zlib licence, see the LICENSE
file.

Documentation
-------------

For users, we recommend you build as above then run:

```
./embroider
```

which will print out advice on how to use these tools without digging straight into the source
code.

Development
-----------

### To Do

1. Basic features.
   1. Incorporate `#if 0`ed parts of `emb-stitch-fill.c`.
   2. Interpret how to write formats that have a read mode from the source code and vice versa.
   3. Identify sources that break down the binary formats we currently don't understand.
   4. Better documentation of the structure of the headers for the formats we do understand.
2. Code quality and user friendliness.
   1. Document all structs, macros and functions (will contribute directly on the web version).
   2. Make a texinfo/PDF user manual for embroider.
   3. Incorporate experimental code, improve support for language bindings.
   4. Make stitch x, y into an EmbVector.
3. embroider CLI
   1. Add building patterns using Imagemagick style filters and modifiers like -circle to add
      a circle to the current pattern. (see embroider-main.c, needs a new file)
   2. Make a list of flags that would be useful and describe their operation.
      * -circle
      * -rect
      * -satin
4. Improve embedded compatibility.
   1. Remove reliance on slower, memory expensive parts of the C Standard Library that are in the main library,
      for example, not using printf, sprintf, fprintf etc. (Use embFile_puts.)
   2. Make a list of all functions used by the source that aren't implimented here.
   3. Share heavy memory usage between functions, for example use embBuffer for buffering headers rather
      than having a seperate `char header[]` variables.
   4. Reduce calls to malloc when we know the total usage as dynamic memory may not be present and we may
      need to get rid of malloc entirely.
   5. Consider using an alternative C standard library for the remaining functions like uclibc.
   6. Testing framework for the total size of the library under different versions of the code to
      run AB tests on variants.

### Finding fixes

To find jobs marked within the source code rather than the list above, use:

```
grep "TODO" *.c *.h
```

### Testing

To get an idea of what does and does not work we plan to expand the testing
suite to cover uses of the library we wish to support, to see this in action
try:

```
./emb-test.sh
```

Long term everything this script does would be covered by:

```
./embroider -test

libembroidery on Arduino
------------------------

This folder contains Arduino specific files for libembroidery.

Compatible Boards
-----------------

We recommend using an Arduino Mega 2560 or another board
with equal or greater specs. That being said, we have had success
using an Arduino Uno R3 but this will likely require further
optimization and other improvements to ensure continued compatibility
with the Uno. See below for more information.

Arduino Considerations
----------------------
There are two main concerns here: Flash Storage & SRAM.

libembroidery continually outgrows the 32KB of Flash storage
on the Arduino Uno and every time this occurs, a decision has to
be made as to what capabilities should be included or omitted. While
reading files is the main focus on arduino, writing files may
also play a bigger role in the future. Long term, it would be most
practical to handle the inclusion or omission of any feature
via a single configuration header file that the user can modify
to suit their needs.

SRAM is in extremely limited supply and it will deplete quickly so
any dynamic allocation should occur early during the setup phase 
of the sketch and sparingly or not at all later in the sketch.
To help minimize SRAM consumption on Arduino and ensure libembroidery
can be used in any way the sketch creator desires, it is required that
any sketch using libembroidery must implement event handlers. See
the ino-event source and header files for more information.

There is also an excellent article by Bill Earl on the
Adafruit Learning System which covers these topics in more depth:
http://learn.adafruit.com/memories-of-an-arduino?view=all

Special Notes
-------------

Due to historical reasons and to remain compatible with the
Arduino 1.0 IDE, this folder must be called "utility".
Refer to the arduino build process for more info:
https://code.google.com/p/arduino/wiki/BuildProcess

libembroidery relies on the Arduino SD library for reading files.
See the ino-file source and header files for more information.
