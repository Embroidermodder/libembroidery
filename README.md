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

1. Combine stitch and thread memory management tools into the EmbArray functions. Remove linked list code.
1. Translate emb-outline to C90 (started).
1. Document all structs, macros and functions (will contribute directly on the web version).
1. Add more command line flags to embroider to control the specific algorithms used in coversion
   and creation of patterns.
   1. Incorporate convert tests into -test flag so we don't need emb-test.sh any more.
   2. Add building patterns using Imagemagick style filters and modifiers like -circle to add
      a circle to the current pattern.
1. Make a texinfo/PDF user manual for embroider.
1. Incorporate experimental code, improve support for language bindings.
1. Better integrate the EmbVector, EmbCircle etc. structs into functions that work with them throughout.

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
