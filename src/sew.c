/*
 * Frontend for the command line tool "sew".
 *
 * Features that were in "embroider" that now are going to use some scripting.
 *
 * 1. Hilbert curve generation
 * 2. Sierpinski triangle generation
 * 3. Dragon curve generation
 * 4. Adding geometric primatives to a pattern (which could be convert to
 *    SVG, add primative using text manipulation, convert to original format
 *    or requested format)
 *
 * All features withing emb_convert need a copy here.
 *
 * Check necessary dependencies are installed when they are called against.
 *
 * Check the following flags are covered:
 * --circle, -c
 * --ellipse, -e
 * --line, -l
 * --polygon, -P
 * --polyline, -p
 * --render
 * --satin, -s
 * --stitch, -S
 * --generate hilbert
 * --generate sierpinski
 * --fill, -f
 * --cross-stitch
 * --simulate
 * --combine
 * --ps
 * --report, -R
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "embroidery.h"

/* same order as flag_list, to use in jump table */
#define FLAG_TO                        0
#define FLAG_TO_SHORT                  1
#define FLAG_HELP                      2
#define FLAG_HELP_SHORT                3
#define FLAG_FORMATS                   4
#define FLAG_FORMATS_SHORT             5
#define FLAG_QUIET                     6
#define FLAG_QUIET_SHORT               7
#define FLAG_VERBOSE                   8
#define FLAG_VERBOSE_SHORT             9
#define FLAG_VERSION                  10
#define FLAG_VERSION_SHORT            11
#define FLAG_RENDER                   12
#define FLAG_RENDER_SHORT             13
#define FLAG_SIMULATE                 14
#define FLAG_COMBINE                  15
#define FLAG_REPORT                   16
#define FLAG_REPORT_SHORT             17
#define NUM_FLAGS                     18

const char *help_msg[] = {
        "Usage: sew [OPTIONS] fileToRead... ",
        "",
        "Conversion:",
        "    -t, --to        Convert all files given to the format specified by the arguments to",
        "                    the flag, for example:",
        "                        $ embroider -t dst input.pes",
        "                    would convert \"input.pes\" to \"input.dst\" in the same directory",
        "                    the program runs in.",
        "",
        "                    The accepted input formats are (TO BE DETERMINED).",
        "                    The accepted output formats are (TO BE DETERMINED).",
        "",
        "Analysis:",
        "    -R, --report    Report various statistics on the loaded pattern.",
        "",
        "Output:",
        "    -h, --help       Print this message.",
        "    -F, --formats    Print help on the formats that embroider can deal with.",
        "    -q, --quiet      Only print fatal errors.",
        "    -V, --verbose    Print everything that has reporting.",
        "    -v, --version    Print the version.",
        "",
        "Modify patterns:",
        "    --combine        takes 3 arguments and combines the first",
        "                     two by placing them atop each other and",
        "                     outputs to the third",
        "                        $ embroider --combine a.dst b.dst output.dst",
        "EOF"
};

const char *welcome_message = "sew\n"
    "1.0.0-alpha\n"
    "\n"
    "    A command line program for converting between machine embroidery file formats.\n"
    "    Copyright 2018-2026 The Embroidermodder Team\n"
    "    Licensed under the terms of the zlib license.\n"
    "\n"
    "    https://github.com/Embroidermodder/libembroidery\n"
    "    https://www.libembroidery.org\n"
    "\n"
    "    For a full list of commands available, use the --list-commands argument.\n";

/* EmbString table of flags. */
const EmbString flag_list[] = {
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
        "--render",
        "-r",
        "--simulate",
        "--combine",
        "--report",
        "-R"
};

void usage(void);

/*! TODO: Add capability for converting multiple files of various types to a
 * single format.
 * Currently, we only convert a single file to multiple formats.
 */

/*! TODO: Add capability for converting multiple files of various types to a
 * single format. Currently, we only convert a single file to multiple formats.
 */
int main(int argc, char *argv[])
{
        EmbPattern *current_pattern = embp_create();
        int i, j, result;
        /* If no argument is given, drop into the postscript interpreter. */
        if (argc == 1) {
                usage();
                return 0;
        }

        char *script = (char *)malloc(argc * 100);
        int flags = argc - 1;
        for (i = 1; i < argc; i++) {
                result = -1;
                /* identify what flag index the user may have entered */
                for (j = 0; j < NUM_FLAGS; j++) {
                        if (!strcmp(flag_list[j], argv[i])) {
                                result = j;
                                break;
                        }
                }
                /* apply the flag */
                switch (result) {
                case FLAG_TO:
                case FLAG_TO_SHORT:{
                                to_flag(argv, argc, i);
                                break;
                        }
                case FLAG_HELP:
                case FLAG_HELP_SHORT:{
                                usage();
                                break;
                        }
                case FLAG_FORMATS:
                case FLAG_FORMATS_SHORT:{
                                formats();
                                break;
                        }
                case FLAG_QUIET:
                case FLAG_QUIET_SHORT:{
                                emb_verbose = -1;
                                break;
                        }
                case FLAG_VERBOSE:
                case FLAG_VERBOSE_SHORT:{
                                emb_verbose = 1;
                                break;
                        }
                case FLAG_RENDER:
                case FLAG_RENDER_SHORT:{
                                if (i + 2 < argc) {
                                        /* the user appears to have entered filenames after render */
                                        embp_read_auto(current_pattern,
                                                       argv[i + 1]);
                                        printf("%d\n",
                                               current_pattern->
                                               stitch_list->count);
                                        embp_render(current_pattern,
                                                    argv[i + 2]);
                                        i += 2;
                                        break;
                                        i++;
                                        if (argv[i][0] == '-') {
                                                /* they haven't, use the default name */
                                                puts("Defaulting to the output name 'output.png'.");
                                                embp_render(current_pattern,
                                                            "output.png");
                                                i--;
                                        } else {
                                                /* they have, use the user-supplied name */
                                                embp_render(current_pattern,
                                                            argv[i]);
                                        }
                                } else {
                                        puts("Defaulting to the output name 'output.png'.");
                                        embp_render(current_pattern,
                                                    "output.png");
                                }
                                break;
                        }
                case FLAG_SIMULATE:{
                                if (i + 1 < argc) {
                                        /* the user appears to have entered a filename after render */
                                        i++;
                                        if (argv[i][0] == '-') {
                                                /* they haven't, use the default name */
                                                puts("Defaulting to the output name 'output.avi'.");
                                                embp_simulate(current_pattern,
                                                              "output.avi");
                                                i--;
                                        } else {
                                                /* they have, use the user-supplied name */
                                                embp_simulate(current_pattern,
                                                              argv[i]);
                                        }
                                } else {
                                        puts("Defaulting to the output name 'output.avi'.");
                                        embp_simulate(current_pattern,
                                                      "output.avi");
                                }
                                break;
                        }
                case FLAG_COMBINE:{
                                if (i + 3 < argc) {
                                        EmbPattern *out;
                                        EmbPattern *p1 = embp_create();
                                        EmbPattern *p2 = embp_create();
                                        embp_read_auto(p1, argv[i + 1]);
                                        embp_read_auto(p2, argv[i + 2]);
                                        out = embp_combine(p1, p2);
                                        embp_write_auto(out, argv[i + 3]);
                                        embp_free(p1);
                                        embp_free(p2);
                                        embp_free(out);
                                } else {
                                        puts("--combine takes 3 arguments and you have supplied <3.");
                                }
                                break;
                        }
                case FLAG_VERSION:
                case FLAG_VERSION_SHORT:{
                                puts(version_string);
                                break;
                        }
                case FLAG_REPORT:
                case FLAG_REPORT_SHORT:{
                                embp_read_auto(current_pattern, argv[i + 1]);
                                embp_details(current_pattern);
                                i++;
                                break;
                        }
                default:
                        flags--;
                        break;
                }
        }

        /* No flags set: default to simple from-to conversion. */
        if (!flags && argc == 3) {
                convert(argv[1], argv[2]);
        } else {
                if (!flags) {
                        puts("Please enter an output format for your file, see --help.");
                }
        }
        embp_free(current_pattern);
        safe_free(script);
        return 0;
}

/*! Construct from tables above somehow, like how getopt_long works,
 * but we're avoiding that for compatibility
 * (C90, standard libraries only).
 */
void usage(void)
{
        int i;
        puts(welcome_message);
        for (i = 0; strcmp(help_msg[i], "EOF"); i++) {
                puts(help_msg[i]);
        }
}

/* . */
void formats(void)
{
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
        printf
            ("|________|_______|_______|____________________________________________________|\n");
        printf
            ("|        |       |       |                                                    |\n");

        for (i = 0; i < numberOfFormats; i++) {
                if (formatTable[i].reader_state != ' ') {
                        numReaders++;
                }
                if (formatTable[i].writer_state != ' ') {
                        numWriters++;
                }
                printf("|  %-4s  |   %c   |   %c   |  %-49s |\n",
                       formatTable[i].extension,
                       formatTable[i].reader_state,
                       formatTable[i].writer_state, formatTable[i].description);
        }

        printf
            ("|________|_______|_______|____________________________________________________|\n");
        printf
            ("|        |       |       |                                                    |\n");
        printf
            ("| Total: |  %3d  |  %3d  |                                                    |\n",
             numReaders, numWriters);
        printf
            ("|________|_______|_______|____________________________________________________|\n");
        puts("");
}

/* . */
void to_flag(char **argv, int argc, int i)
{
        if (i + 2 < argc) {
                int j;
                EmbString output_fname;
                int format;
                sprintf(output_fname, "example.%s", argv[i + 1]);
                format = emb_identify_format(output_fname);
                if (format < 0) {
                        puts("Error: format unrecognised.");
                }
                for (j = i + 2; j < argc; j++) {
                        int length = embstr_len(argv[j]);
                        output_fname[0] = 0;
                        strcpy(output_fname, argv[j]);
                        output_fname[length - 4] = 0;
                        strcat(output_fname, formatTable[format].extension);
                        printf("Converting %s to %s.\n", argv[j], output_fname);
                        convert(argv[j], output_fname);
                }
        } else {
                puts("Usage of the to flag is:");
                puts("    sew -t FORMAT FILE(S)");
                puts("but it appears you entered less than 3 arguments to embroider.");
        }
}
