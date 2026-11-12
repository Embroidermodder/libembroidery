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
Copyright (c) 2018-2026 The Embroidermodder Team and Josh Varga
<br>
https://www.libembroidery.org
</p>

Libembroidery is a low-level library for reading, writing, 
and altering machine embroidery files in C. It is the underlying
library that is used by Embroidermodder 2 and is developed by
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

Both a UNIX style Makefile and CMake build are available. Internally,
we use `cmake` for Embroidermodder and `make` for CI in this repository
so they should be equally reliable.

### Testing

To run a suite basic diagnostics on your system run:

```sh
$ make check
```

The last line of output reports the proportion of tests that have
passed which, at the time of writing is:

```
61 / 138 tests 44.202899%
```

### Coverage

To make sure that testing covers all code in the main library we use
a set of `lcov` calls that can be called with the `coverage` recipe:

```sh
$ make coverage
```

At the time of writing opening the generated webpage shows: 25.4% line and 39.0% function coverage for the library itself.

## Development

We defer to the linux style guide
[here](https://www.kernel.org/doc/html/v4.10/process/coding-style.html).
If you find it too difficult to both contribute your patch and keep within the guide,
we can adjust it to comply in the PR.

Where our files do not match this style, it is the core developers'
responsibility to repair this.

