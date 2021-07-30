What is libembroidery ?
-----------------------

libembroidery is the underlying library that is used by [Embroidermodder 2](http://embroidermodder.github.io)
and is developed by the Embroidermodder team.
It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

It also includes a CLI called `embroider` that allows for better automation of
changes to embroidery files and will be more up-to date than
the Embroidermodder 2 GUI.

Finally there are some shell tools in `embtools.sh/embtools.bat`
to help with calls to ImageMagick and other programs that can
help produce new embroidery machine files.

## Build

libembroidery and EmbroiderModder 2 use CMake builds
so if you are building the project to use as a library we recommend
you run:

#### Linux or MacOS
 
```
git clone https://github.com/Embroidermodder/libembroidery
cd libembroidery
./embtools.sh build
```

#### Windows (or any system without Bash)

(IN DEVELOPMENT)
 
```
git clone https://github.com/Embroidermodder/libembroidery
cd libembroidery
embtools.bat build
```

These builds both the static and shared versions of the library as well
as the command line program `embroider`.

### License

Libembroidery is distributed under the permissive zlib licence, see the LICENSE file.

## Documentation

For basic use, we recommend you build as above then run:

```
./embroider
```

which will print out advice on how to use these tools without digging
straight into the [full manual](manual.md).

## Contributing

If you want to find a simple fix to contribute see the *To Do* section
of the manual. 

