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

which will print out advice on how to use these tools without digging
straight into the source code.

In the future there will be deeper documentation read the contents
of doc/ (currently not written).

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
   1. Make -circle flag to add a circle to the current pattern.
   2. Make -rect flag to add a rectangle to the current pattern.
   3. Make -fill flag to set the current satin fill algorithm for the current geometry. (for example "-fill crosses -circle 11,13,10" fills a circle with center 11mm, 13mm with radius 10mm with crosses).
   4. Make -ellipse flag to add to ellipse to the current pattern.
   5. Make -bezier flag to add a bezier curve to the current pattern.
4. Improve embedded compatibility.
   1. Remove reliance on slower, memory expensive parts of the C Standard Library that are in the main library, for example, not using printf, sprintf, fprintf etc. (Use embFile_puts.)
   2. Share heavy memory usage between functions, for example use embBuffer for buffering headers rather than having a seperate `char header[]` variables.
   3. Reduce calls to malloc when we know the total usage as dynamic memory may not be present and we may need to get rid of malloc entirely.
   4. Consider using an alternative C standard library for the remaining functions like uclibc.

### Finding fixes

To find jobs marked within the source code rather than the list above, use:

```
grep "TODO" *.c *.h
```

### Testing

Build `embroider` then run:

```
./embroider -test &> report.txt
```

If any of the tests return a fail in the summary (see `tail report.txt`)
then it would help the project to send us an issue attatching the file to
your message along with a description of the system you ran the program on.
