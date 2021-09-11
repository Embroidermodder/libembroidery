What is libembroidery ?
-----------------------

libembroidery is the underlying library that is used and
developed by [Embroidermodder 2](http://embroidermodder.github.io).
It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

Build
-----

You can use either use a CMake (for the library itself) or qmake build
(as part of `Embroidermodder2`).

So if you are building the project to use as a library we recommend:
 
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

Developer Documentation can be generated using [Doxygen](http://www.doxygen.org)

```
doxygen libembroidery.doxyfile
```

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
   1. Incorporate convert tests into -test flag so we don't need emb-test.sh any more.
   2. Add building patterns using Imagemagick style filters and modifiers like -circle to add
      a circle to the current pattern.
   3. Make a list of flags that would be useful and describe their operation.
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

