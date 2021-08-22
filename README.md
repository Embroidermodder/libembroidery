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
as the command line program `embroider` and the testing program
`libembroidery_test`.

License
-------

Libembroidery is distributed under the permissive zlib licence, see the LICENSE
file.

Documentation
-------------

Developer Documentation can be generated using [Doxygen](http://www.doxygen.org)

```
doxygen libembroidery.doxyfile
```

Development
-----------

## To Do

1. Combine stitch and thread memory management tools into the EmbArray functions. Remove linked list code.
1. Translate emb-outline to C90.
1. Document all struts, macros and functions.
1. Add more command line flags to embroider to control the specific algorithms used in coversion
   and creation of patterns.
1. Make a texinfo/PDF user manual for embroider.
1. Incorporate experimental code, improve support for language bindings.
1. Better integrate the EmbVector, EmbCircle etc. structs into functions that work with them throughout.

## Finding fixes

Use:

```
grep "TODO" *.c *.h */*.c */*.h
```

to find jobs marked within the source code rather than the list above.

