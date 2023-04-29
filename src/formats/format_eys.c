/*
 * EXP FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 *
\subsection sierra-eys-format Sierra Expanded Embroidery Format (.eys)
\addindex eys
\addindex Sierra Expanded

Stitch Only Format.

Smoothie G-Code Embroidery Format (.fxy)?
 */

char
readEys(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readEys */
}

char
writeEys(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeEys */
}
