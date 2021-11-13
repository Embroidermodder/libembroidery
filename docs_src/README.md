# **libembroidery** <!-- CI badge -->

<!-- nav -->

## What is libembroidery?

libembroidery aims to be a low-level library for reading, writing, 
and programmatically manipulating digital embroidery files, 
available to in many different programming languages.

Currently, libembroidery is the underlying library that is used 
by [Embroidermodder 2](http://embroidermodder.github.io)
and is developed by the Embroidermodder team.
It handles over 45 different embroidery specific formats as well 
as several non-embroidery specific vector formats.

It also includes a CLI called `embroider` that allows for better automation of
changes to embroidery files and will be more up-to date than
the Embroidermodder 2 GUI.

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