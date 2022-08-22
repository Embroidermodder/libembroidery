# EmbroiderBot: The Open Source Embroidery Machine

We're in the process of developing an embroidery machine that is completely
free of patents and runs on software that is also free.

The full cutting list and pricing of the design will come out as we ammend it
so hopefully various shops can build the experimental alpha design alongside
our own. Perhaps, in the long run this could be sold as a complete kit similar
to recent open source hardware 3D printer designs, but as with
our other projects we prefer donations to keep the Embroidermodder Team going.

## License

Unlike Embroidermodder and libembroidery, Embroiderbot is closer to a physical
product and we want the licensing to reflect that.

All software parts (that is assembly code, files with the suffixes `.S` and `.ino`)
are under the permissive zlib license as with our other projects.

All hardware designs, images, circuit board designs, desciptions like this document
and physical implimentations thereof are under Creative Commons Attributation
Share-Alike 3.0 (CC BY-SA 3.0).

The upshot of this is you may take the assembly out of this project to build an
entirely new closed source machine, but derivative machines need to remain
open because of the share alike clause.

## Software

The software component of EmbroiderBot is a hand translated collection
of assembly macros, functions and data from our sister project
[`libembroidery`](https://github.com/Embroidermodder/libembroidery).
No verbatim code is copied over because, in practice, sharing code between
the desktop, mobile and embedded versions was impractical. However, the
documentation and C functions serve as a good template for the development
of our own user interface.

This means that to create your own forked hardware we don't supply a library of
assembly routines as would be the case for creating GUIs that backend to `libembroidery`.
Instead, derivative works should 

## Hardware

We intend for this to be buildable from standard parts with a minimum of
waste. For example:

1. The housing will be laser cut plywood, reducing unnecessary plastic waste.
2. The drive will use no more than the required 3 stepper motors and hopefully less.
3. Wooden rack and pinion rather than worm gears to reduce the cost of the build.
4. There will be no locking to a specific thread brand or material: hopefully standard sewing machine cottons should run just as well in it.
5. The sewing head will use repurposed existing parts, so standard bobbins, needles, bobbin cases, free presser foot etc.
