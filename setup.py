#!/usr/bin/env python3

import setuptools
from distutils.core import Extension

setuptools.setup(
    name="libembroidery",
    version="1.0-alpha-2",
    license="ZLib",
    description="Official Python binding to the libembroidery library.",
    author="The Embroidermodder Team",
    author_email="embroidermodder@gmail.com",
    py_modules=["libembroidery"],
    python_requires=">=3.6"
)

