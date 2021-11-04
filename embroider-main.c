#include "embroidery.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static const char *version_string = "embroider v0.1";
static const char *welcome_message = "EMBROIDER\n"
    "    A command line program for machine embroidery.\n"
    "    Copyright 2013-2021 The Embroidermodder Team\n"
    "    Licensed under the terms of the zlib license.\n"
    "\n"
    "    https://github.com/Embroidermodder/libembroidery\n"
    "    https://embroidermodder.org\n";

static void usage(void)
{
    puts(welcome_message);
    puts("Usage: embroider [OPTIONS] fileToRead... \n");
    puts("");
    puts("Conversion:");
    puts("    -t, -to         Convert all files given to the format specified");
    puts("                    by the arguments to the flag, for example:");
    puts("                        $ embroider -t dst input.pes");
    puts("                    would convert \"input.pes\" to \"input.dst\"");
    puts("                    in the same directory the program runs in.");
    puts("");
    puts("                    The accepted input formats are (TO BE DETERMINED).");
    puts("                    The accepted output formats are (TO BE DETERMINED).");
    puts("");
    puts("Output:");
    puts("    -h, --help       Print this message.");
    puts("    -f, --formats     Print help on the formats that embroider can deal with.");
    puts("    -q, --quiet      Only print fatal errors.");
    puts("    -V, --verbose    Print everything that has reporting.");
    puts("    -v, --version    Print the version.");
    puts("");
    puts("Graphics:");
    puts("    -c, --circle     Add a circle defined by the arguments given to the current pattern.");
    puts("    -e, --ellipse    Add a circle defined by the arguments given to the current pattern.");
    puts("    -l, --line       Add a line defined by the arguments given to the current pattern.");
    puts("    -P, --polyline   Add a polyline.");
    puts("    -p, --polygon    Add a polygon.");
    puts("    -r, --render     Create an image in PPM format of what the embroidery should look like.");
    puts("    -s, --satin      Fill the current geometry with satin stitches according");
    puts("                     to the defined algorithm.");
    puts("    -S, --stitch     Add a stitch defined by the arguments given to the current pattern.");
    puts("");
    puts("Quality Assurance:");
    puts("        --test       Run the basic test suite.");
    puts("        --full-test-suite  Run all tests, even those we expect to fail.");
}

static void formats(void)
{
    const char* extension = 0;
    const char* description = 0;
    char readerState;
    char writerState;
    int numReaders = 0;
    int numWriters = 0;
    int i;
    puts("List of Formats");
    puts("---------------");
    puts("");
    puts("    KEY");
    puts("    'S' = Yes, and is considered stable.");
    puts("    'U' = Yes, but may be unstable.");
    puts("    ' ' = No.");
    puts("");
    printf("  Format   Read    Write   Description\n");
    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");

    for (i=0; i<numberOfFormats; i++) {
        extension = formatTable[i].extension;
        description = formatTable[i].description;
        readerState = formatTable[i].reader_state;
        writerState = formatTable[i].writer_state;

        numReaders += readerState != ' '? 1 : 0;
        numWriters += writerState != ' '? 1 : 0;
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n", extension, readerState, writerState, description);
    }

    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");
    printf("| Total: |  %3d  |  %3d  |                                                    |\n", numReaders, numWriters);
    printf("|________|_______|_______|____________________________________________________|\n");
    puts("");
}

/* TODO: Add capability for converting multiple files of various types to a single format. Currently, we only convert a single file to multiple formats. */

int main(int argc, const char* argv[])
{
    int i, flags;
    if (argc == 1) {
        usage();
        return 0;
    }

    flags = argc-1;
    for (i=1; i<argc; i++) {
        /* Output */
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            usage();
            continue;
        }
        if (!strcmp(argv[i], "--formats") || !strcmp(argv[i], "-f")) {
            formats();
            continue;
        }
        if (!strcmp(argv[i], "--quiet") || !strcmp(argv[i], "-q")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--verbose") || !strcmp(argv[i], "-V")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-v")) {
            puts(version_string);
            continue;
        }
        /* Graphics */
        if (!strcmp(argv[i], "--circle") || !strcmp(argv[i], "-c")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--ellipse") || !strcmp(argv[i], "-e")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--line") || !strcmp(argv[i], "-l")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--hilbert-curve")) {
            hilbert_curve(4);
            continue;
        }
        if (!strcmp(argv[i], "--polygon") || !strcmp(argv[i], "-P")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--polyline") || !strcmp(argv[i], "-p")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--render") || !strcmp(argv[i], "-r")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--satin") || !strcmp(argv[i], "-s")) {
            puts("This flag is not implimented.");
            continue;
        }
        if (!strcmp(argv[i], "--stitch") || !strcmp(argv[i], "-S")) {
            puts("This flag is not implimented.");
            continue;
        }
        /* Quality Assurance */
        if (!strcmp(argv[i], "--test")) {
            testMain(0);
            continue;
        }
        if (!strcmp(argv[i], "--full-test-suite")) {
            testMain(1);
            continue;
        }
        flags--;
    }

    /* simple from-to conversion */
    if (!flags) {
        convert(argv[1], argv[2]);
    }

    return 0;

}
