/* Frontend for compiling as the command line tool embroider.
 *
 * Copyright 2018-2024 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */
#include "embroidery.c"

int
main(int argc, char *argv[])
{
    return command_line_interface(argc, argv);
}
