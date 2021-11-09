What is libembroidery ?
-----------------------

libembroidery is the underlying library that is used by [Embroidermodder 2](http://embroidermodder.github.io)
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

Documentation
-------------

For basic use, we recommend you build as above then run:

```
./embroider
```

which will print out advice on how to use these tools without digging
straight into the full manual. Beyond this the full documentation is in
[embroidermodder_v1.90.0_manual.pdf](https://github.com/Embroidermodder/embroidermodder-manual/blob/master/embroidermodder_v1.90.0_manual.pdf).

Development
-----------

All the documentation for the development of the library and CLI is also
in [the manual](https://github.com/Embroidermodder/libembroidery/blob/master/doc/libembroidery_v0.1_manual.pdf).
If you want to find a simple fix to contribute see the *To Do* section. 

We currently need help with:

  1. Thorough descriptions of each embroidery format.
  2. Finding resources for each of the branded thread libraries (along with a full citation for documentation).
  3. Finding resources for each geometric algorithm used (along with a full citation for documentation).
  4. Completing the full `--full-test-suite`  with no segfaults and at least a clear error message (for example "not implimented yet").
  5. Identifying "best guesses" for filling in missing information when going from, say `.csv` to a late `.pes` version. What should the default be when the data doesn't clarify?
  6. Improving the written documentation.
  7. Funding, see the Sponsor button above. We can treat this as "work" and put far more hours in with broad support in small donations from people who want specific features.
