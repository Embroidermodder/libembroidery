#!/usr/bin/env python3
# GENERATE LIBEMBROIDERY HEADER
# This file is part of libembroidery.
#
# Copyright 2018-2023 The Embroidermodder Team
# Licensed under the terms of the zlib license.

import json

def make_constant(f, a, lang="c"):
    key, value = a[0], a[1]
    if lang == "py":
        if len(a) == 3:
            f.write("# " + a[2] + "\n")
        a = max(35 - len(key + "= " + value), 1)
        f.write(key + " " * a + "= " + value + "\n")

    elif lang == "java":
        if len(a) == 3:
            f.write("# " + a[2] + "\n")
        a = max(35 - len(key + "= " + value), 1)
        f.write(key + " " * a + "= " + value + "\n")

    elif lang == "swift":
        if len(a) == 3:
            f.write("# " + a[2] + "\n")
        a = max(35 - len(key + "= " + value), 1)
        f.write(key + " " * a + "= " + value + "\n")

    else:
        if len(a) == 3:
            f.write("/* " + a[2] + " */\n")
        a = max(35 - len("#define " + key + value), 1)
        f.write("#define " + key + " " * a + value + "\n")

def make_file(out_fname, lang):
    f = open("data/defines.json", "r")
    s = f.read()
    f.close()

    d = json.loads(s)

    f = open(out_fname, "w")
    if lang == "c":
        f.write("/*\n")
        for a in d["copyright_notice"]:
            f.write(" * " + a + "\n")
        f.write(" */\n\n")
    elif lang == "py":
        f.write("#\n")
        for a in d["copyright_notice"]:
            f.write("# " + a + "\n")
        f.write("#\n\n")

    for block in d["blocks"]:
        for k in d[block]:
            make_constant(f, k, lang)
        f.write("\n\n")
    f.close()

make_file("constants.h", "c")
make_file("constants.py", "py")
make_file("constants.java", "java")
make_file("constants.swift", "swift")
