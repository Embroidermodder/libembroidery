#include "embroidery.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* same order as flag_list, to use in jump table */
#define FLAG_TO             0
#define FLAG_TO_SHORT       1
#define FLAG_HELP           2
#define FLAG_HELP_SHORT     3
#define FLAG_FORMATS        4
#define FLAG_FORMATS_SHORT  5
#define FLAG_QUIET          6
#define FLAG_QUIET_SHORT    7
#define FLAG_VERBOSE        8
#define FLAG_VERBOSE_SHORT  9
#define FLAG_VERSION        10
#define FLAG_VERSION_SHORT  11
#define FLAG_CIRCLE         12
#define FLAG_CIRCLE_SHORT   13
#define FLAG_ELLIPSE        14
#define FLAG_ELLIPSE_SHORT  15
#define FLAG_LINE           16
#define FLAG_LINE_SHORT     17
#define FLAG_POLYGON        18
#define FLAG_POLYGON_SHORT  19
#define FLAG_POLYLINE       20
#define FLAG_POLYLINE_SHORT 21
#define FLAG_RENDER         22
#define FLAG_RENDER_SHORT   23
#define FLAG_SATIN          24
#define FLAG_SATIN_SHORT    25
#define FLAG_STITCH         26
#define FLAG_STITCH_SHORT   27
#define FLAG_TEST           28
#define FLAG_FULL_TEST_SUITE 29
#define FLAG_HILBERT_CURVE  30
#define FLAG_SIERPINSKI_TRIANGLE 31
#define FLAG_FILL           32
#define FLAG_FILL_SHORT     33
#define NUM_FLAGS           34

static const char *flag_list[] = {
    "--to",
    "-t",
    "--help",
    "-h",
    "--formats",
    "-F",
    "--quiet",
    "-q",
    "--verbose",
    "-V",
    "--version",
    "-v",
    "--circle",
    "-c",
    "--ellipse",
    "-e",
    "--line",
    "-l",
    "--polyline",
    "-P",
    "--polygon",
    "-p",
    "--render",
    "-r",
    "--satin",
    "-s",
    "--stitch",
    "-S",
    "--test",
    "--full-test-suite",
    "--hilbert-curve",
    "--sierpinski-triangle",
    "--fill",
    "-f"
};

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
    /* construct from tables above somehow, like how getopt_long works,
     * but we're avoiding that for compatibility
     * (C90, standard libraries only) */
    puts("Usage: embroider [OPTIONS] fileToRead... \n");
    puts("");
    puts("Conversion:");
    puts("    -t, --to        Convert all files given to the format specified");
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
    puts("    -F, --formats     Print help on the formats that embroider can deal with.");
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
    int i, j, flags, result;
    if (argc == 1) {
        usage();
        return 0;
    }

    flags = argc-1;
    for (i=1; i<argc; i++) {
        result = -1;
        for (j=0; j<NUM_FLAGS; j++) {
            if (!strcmp(flag_list[j], argv[i])) {
                result = j;
                break;
            }
        }
        switch (result) {
        case FLAG_TO:
            break;
        case FLAG_HELP:
        case FLAG_HELP_SHORT:
            usage();
            break;
        case FLAG_FORMATS:
        case FLAG_FORMATS_SHORT:
            formats();
            break;
        case FLAG_QUIET:
        case FLAG_QUIET_SHORT:
        case FLAG_VERBOSE:
        case FLAG_VERBOSE_SHORT:
        case FLAG_CIRCLE:
        case FLAG_CIRCLE_SHORT:
        case FLAG_ELLIPSE:
        case FLAG_ELLIPSE_SHORT:
        case FLAG_LINE:
        case FLAG_LINE_SHORT:
        case FLAG_POLYGON:
        case FLAG_POLYGON_SHORT:
        case FLAG_POLYLINE:
        case FLAG_POLYLINE_SHORT:
        case FLAG_SATIN:
        case FLAG_SATIN_SHORT:
        case FLAG_STITCH:
        case FLAG_STITCH_SHORT:
        case FLAG_SIERPINSKI_TRIANGLE:
        case FLAG_FILL:
            puts("This flag is not implimented.");
            break;
        case FLAG_VERSION:
        case FLAG_VERSION_SHORT:
            puts(version_string);
            break;
        case FLAG_HILBERT_CURVE:
            hilbert_curve(3);
            break;
        default:
            flags--;
            break;
        }
    }

    /* simple from-to conversion */
    if (!flags) {
        convert(argv[1], argv[2]);
    }

    return 0;

}
