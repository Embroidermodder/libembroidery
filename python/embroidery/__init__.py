#!/usr/bin/env python3

r"""
Libembroidery
1.0.0-alpha
https://www.libembroidery.org

---------------------------------------------

Copyright 2018-2024 The Embroidermodder Team
Libembroidery is Open Source Software.
See LICENSE for licensing terms.

---------------------------------------------

Hand-written bindings to the C library for Python. This is manually updated.

Documentation on the ctypes interface here:
    https://docs.python.org/3.8/library/ctypes.html
"""

import ctypes
import pathlib

def load_library():
    library_dir = pathlib.Path().absolute()
    libembroidery_library = library_dir / "libembroidery.so"
    libembroidery = ctypes.CDLL(libembroidery_library)

    libembroidery.emb_vector_add.argtypes = (vector, vector)
    libembroidery.emb_vector_add.restype = vector
    return libembroidery

class vector(ctypes.Structure):
    """ Wrapper for the EmbVector structure. """
    _fields_ = [
        ('x', ctypes.c_float),
        ('y', ctypes.c_float)
    ]

    def __str__(self,) -> str:
        return f"({self.x}, {self.y})"

libembroidery = load_library()

if __name__ == "__main__":
    print(libembroidery.emb_vector_add(vector(1.0, 1.0), vector(1.0, 6.0)))
