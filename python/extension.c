/* Python Extension for libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include "../src/embroidery.h"
#include <Python.h>

EmbPattern **patterns;

static PyObject *
method_command(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

PyDoc_STRVAR(
    command_doc,
    "command(cmd)\n"
    "--\n"
    "\n"
    "The main starting point for interfacing Python and C.\n"
    "\n"
    "Rather than write a seperate binding for each individual function,\n"
    "pass a command similar to a command line argument list to the function\n"
    "as a string.\n"
    "\n"
    "The python object returned doesn't have a set type as it is emulating\n"
    "all the possible returns.\n"
    "\n"
    "For example:\n"
    "    pattern_index = command(\"pattern create\")\n"
    "    command(\"convert infile.svg outfile.pes\")\n"
    "    command(\"add line 0 0 100 100\")\n"
);

static PyMethodDef LibembcoreMethods[] = {
    {"command", (PyCFunction) method_command, METH_VARARGS, command_doc},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef libembcoremodule = {
    PyModuleDef_HEAD_INIT,
    "libembcore",
    "The core of the official Python interface to the libembroidery C library.",
    -1,
    LibembcoreMethods
};

PyMODINIT_FUNC
PyInit_libembcore(void)
{
    return PyModule_Create(&libembcoremodule);
}
