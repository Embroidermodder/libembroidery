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
    headers=["src/embroidery.h"],
    ext_modules=[Extension("libembroidery", [
        "python/extension.c",
        "src/main.c",
        "src/array.c",
        "src/testing.c",
        "src/formats.c",
        "src/format-data.c",
        "src/pattern.c",
        "src/image.c",
        "src/fill.c",
        "src/geometry.c",
        "src/compress.c",
        "src/encoding.c",
        "src/thread-color.c"
    ])],
    python_requires=">=3.6"
)

