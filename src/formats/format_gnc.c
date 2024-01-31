/*
 * 100 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.

\subsection great-gnc-format Great Notions Embroidery Format (.gnc)
\addindex gnc
\addindex Great Notions

Stitch Only Format.
 *
 */

char
readGnc(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readGnc */
}

char
writeGnc(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGnc */
}
