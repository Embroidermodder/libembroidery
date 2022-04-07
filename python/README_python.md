# Libembroidery 1.0 On Python (Alpha)

The Official binding for libembroidery on Python.

This is a stub to save the name on the Python Package Index.

Usage would be something like:

    import libembroidery as emb

    p = emb.createPattern()
    p.add_circle([2, 4], 5, color="blue")
    p.save("circle.dst", emb.FORMAT_DST)

For more see our website: https://embroidermodder.org.

To support this and other Embroidermodder projects see
[https://opencollective.com/embroidermodder](our Open Collective page).

## Installation

We recommend you install the working draft using

    python3 setup.py install --user

from the top level.

In the future we'd recommend that you use the current most
up-to-date version on PyPI using:

    python3 -m pip install libembroidery

or

    py -m pip install libembroidery

on Windows.

## A seperate folder for each language

In theory, for every language that people actively write in a 
well-made binding should be supplied for something as low-level 
as libembroidery. Practically, the Embroidermodder Team will
only know so many languages and for those languages won't necessarily
know about writing bindings.

We can have experts on individual languages take more 
control of the support of this work without it affecting the overall 
support and core library and the levels of completion can be different 
for each language.

While this problem could be solved by the generation of bindings
from a specification like SWIG, we feel that this doesn't account
for the object oriented structure that we want to apply to the
bound functions. Also writing good documentation is helped by
that generation step. Calling conventions may be different between
languages and we'd rather have a human make sure that the documentation
is written with an awareness of the language being written for.