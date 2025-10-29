/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 *
 * -----------------------------------------------------------------------------
 *
 * The Testing System
 */

#include <stdio.h>
#include <string.h>

#include "embroidery.h"

int verbosity = 0;

int all_tests(void);
int arc_tests(void);
int vector_tests(void);

int
main(int argc, char *argv[])
{
    if (argc == 0) {
        return all_tests();
    }
    for (int i=0; i<argc; i++) {
        
    }
    return 0;
}

int
all_tests(void)
{
    return 0;
}

int
arc_tests(void)
{
    return 0;
}

