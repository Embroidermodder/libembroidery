<h1 align="center">
Libembroidery
</h1>

<h4 align="center">
A library for working with machine embroidery files.
</h4>

<p align="center">
<code>v1.0-alpha</code>
<br>
(Under construction, please wait for v1.0 release.)
<br>
<a href="https://github.com/Embroidermodder/libembroidery/actions/workflows/build.yml">
  <img src="https://github.com/Embroidermodder/libembroidery/actions/workflows/build.yml/badge.svg">
    Build status
  </img>
</a>
<br>
Copyright (c) 2018-2025 The Embroidermodder Team and Josh Varga
<br>
https://www.libembroidery.org
</p>

Libembroidery is a low-level library for reading, writing, 
and altering digital embroidery files in C. It is implemented in a single-file
so you can add it to your project by dropping `embroidery.h` in your source code.
It is part of the Embroidermodder Project
for open source machine embroidery.

Libembroidery is the underlying library that is used by
[Embroidermodder 2](http://embroidermodder.org) and is developed by
[The Embroidermodder Team](#the-embroidermodder-team).
A full list of contributors to the project is maintained in
[the Embroidermodder 2 github](https://github.com/Embroidermodder/embroidermodder)
in the file `CREDITS.md`.
It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

It also includes a CLI called `sew` that allows for better automation of
changes to embroidery files and will be more up-to date than
the Embroidermodder 2 GUI.

## Documentation

For basic usage, the `sew` command line program should have some in-built
help starting with:

```sh
    $ sew --help
```

If you need libembroidery for any non-trivial usage the source code is ordered
in literate program style

### License

Libembroidery is distributed under the permissive zlib licence, see the
[LICENCE](./LICENCE.md) file. You are not required to supply this file in your
source code when adding the library but you are required to keep the license message
in the comment within `embroidery.h` in place as it clarifies the same rights.

### Build

libembroidery and EmbroiderModder 2 use CMake builds
so if you are building the project to use as a library we recommend
you run:

```sh
git clone https://github.com/Embroidermodder/libembroidery
cd libembroidery
cmake .
cmake --build .
cmake --install .
```

This builds both the static and shared versions of the library as well
as the command line program `embroider`.

### Testing

On building the software, enter your build directory and type:

```sh
$ sew --test
```

for a suite basic diagnostics on your system.

The full suite requires that you have imagemagick installed to fully test
the more image-processing based tasks, as does `sew` generally.
