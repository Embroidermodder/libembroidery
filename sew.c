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
 * Frontend for compiling as the command line tool sew.
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
    "    A command line program for converting between machine embroidery file formats.\n"
    "    Copyright 2018-2024 The Embroidermodder Team\n"
    "    Licensed under the terms of the zlib license.\n"
    "\n"
    "    https://github.com/Embroidermodder/libembroidery\n"
    "    https://www.libembroidery.org\n";

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
int
main(int argc, char *argv[])
{
    EmbPattern *current_pattern = emb_pattern_create();
    int i, j, result;
    /* If no argument is given, drop into the postscript interpreter. */
    if (argc == 1) {
        usage();
        return 0;
    }

    char *script = (char *)malloc(argc*100);
    int flags = argc - 1;
    for (i=1; i < argc; i++) {
        result = -1;
        /* identify what flag index the user may have entered */
        for (j=0; j < NUM_FLAGS; j++) {
            if (!strcmp(flag_list[j], argv[i])) {
                result = j;
                break;
            }
        }
        /* apply the flag */
        switch (result) {
        case FLAG_TO:
        case FLAG_TO_SHORT: {
            to_flag(argv, argc, i);
            break;
        }
        case FLAG_HELP:
        case FLAG_HELP_SHORT: {
            usage();
            break;
        }
        case FLAG_FORMATS:
        case FLAG_FORMATS_SHORT: {
            formats();
            break;
        }
        case FLAG_QUIET:
        case FLAG_QUIET_SHORT: {
            emb_verbose = -1;
            break;
        }
        case FLAG_VERBOSE:
        case FLAG_VERBOSE_SHORT: {
            emb_verbose = 1;
            break;
        }
        case FLAG_RENDER:
        case FLAG_RENDER_SHORT: {
            if (i + 2 < argc) {
                /* the user appears to have entered filenames after render */
                emb_pattern_readAuto(current_pattern, argv[i+1]);
                printf("%d\n", current_pattern->stitch_list->count);
                emb_pattern_render(current_pattern, argv[i+2]);
                i += 2;
                break;
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.png'.");
                    emb_pattern_render(current_pattern, "output.png");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    emb_pattern_render(current_pattern, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.png'.");
                emb_pattern_render(current_pattern, "output.png");
            }
            break;
        }
        case FLAG_SIMULATE: {
            if (i + 1 < argc) {
                /* the user appears to have entered a filename after render */
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.avi'.");
                    emb_pattern_simulate(current_pattern, "output.avi");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    emb_pattern_simulate(current_pattern, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.avi'.");
                emb_pattern_simulate(current_pattern, "output.avi");
            }
            break;
        }
        case FLAG_COMBINE: {
            if (i + 3 < argc) {
                EmbPattern *out;
                EmbPattern *p1 = emb_pattern_create();
                EmbPattern *p2 = emb_pattern_create();
                emb_pattern_readAuto(p1, argv[i+1]);
                emb_pattern_readAuto(p2, argv[i+2]);
                out = emb_pattern_combine(p1, p2);
                emb_pattern_writeAuto(out, argv[i+3]);
                emb_pattern_free(p1);
                emb_pattern_free(p2);
                emb_pattern_free(out);
            }
            else {
                puts("--combine takes 3 arguments and you have supplied <3.");
            }
            break;
        }
        case FLAG_VERSION:
        case FLAG_VERSION_SHORT: {
            puts(version_string);
            break;
        }
        case FLAG_REPORT:
        case FLAG_REPORT_SHORT: {
            emb_pattern_readAuto(current_pattern, argv[i+1]);
            emb_pattern_details(current_pattern);
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
    }
    else {
        if (!flags) {
            puts("Please enter an output format for your file, see --help.");
        }
    }
    emb_pattern_free(current_pattern);
    safe_free(script);
    return 0;
}

/*! Construct from tables above somehow, like how getopt_long works,
 * but we're avoiding that for compatibility
 * (C90, standard libraries only).
 */
void
usage(void)
{
    int i;
    puts(welcome_message);
    for (i=0; strcmp(help_msg[i], "EOF"); i++) {
        puts(help_msg[i]);
    }
}

/*
 * The Testing System
 */

/* Caller wrapper for testing: note that this assumes that the error variable
 * is called "error".
 */
#define TEST(LINE) \
    LINE; \
    if (error) { \
        return error; \
    }

int verbosity = 0;

/* Debugging output */
void emb_vector_print(EmbVector v, char *label);
void emb_arc_print(EmbArc a);

/* Test groups */
EmbError all_tests(void);
EmbError arc_tests(void);
EmbError circle_tests(void);
EmbError ellipse_tests(void);
EmbError vector_tests(void);

/* Individual tests. */
EmbError test_arc_attributes(EmbGeometry arc);
EmbError test_cross(void);
EmbError test_fill(void);
EmbError test_vadd(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence);
EmbError test_vsubtract(EmbVector v1, EmbVector v2, EmbVector result,
    EmbReal tolerence);
EmbError test_convert(int test_case, int from, int to);

int
test_main(int argc, char *argv[])
{
    if (argc == 0) {
        return all_tests();
    }
    for (int i=0; i<argc; i++) {
        EmbError error = EMB_NO_ERR;
        /* Isolating test types: each uses a fail fast approach. */
        if (strncmp(argv[i], "--arc", 20)) {
            error = arc_tests();
        }
        if (strncmp(argv[i], "--vector", 20)) {
            error = vector_tests();
        }
        if (error) {
            return error;
        }
    }
    return 0;
}

EmbError
all_tests(void)
{
    EmbError error = EMB_NO_ERR;
    TEST(error = arc_tests())
    TEST(error = circle_tests())
    TEST(error = ellipse_tests())
    TEST(error = vector_tests())
    return error;
}

/* TODO: a clockwise and a anti-clockwise test. */
EmbError
arc_tests(void)
{
    EmbError error;
    EmbGeometry g = emb_arc(1.0, 0.0, 0.0, 0.0, 2.0, 1.0);
    TEST(error = test_arc_attributes(g))

    g = emb_arc(4.0, 0.0, 0.0, 0.0, 5.0, 1.0);
    TEST(error = test_arc_attributes(g))

    return EMB_NO_ERR;
}

/*
 * Testing if all arc attributes can be created without error.
 */
EmbError
test_arc_attributes(EmbGeometry g)
{
    EmbVector center, chordMid;
    EmbReal bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    unsigned char clockwise;
    EmbError error = EMB_NO_ERR;
    bulge = -0.414213562373095f;
    /* bulge = emb_arc_bulge(g); */
    TEST(center = emb_center(&g, &error))
    TEST(chord = emb_vector_length(emb_chord(&g, &error)))
    TEST(radius = emb_radius(&g, &error))
    TEST(diameter = emb_diameter(&g, &error))
/* FIXME:
    TEST(chordMid = emb_chord_mid(&g, &error))
*/
    TEST(sagitta = emb_sagitta(&g, &error))
/* FIXME:
    TEST(apothem = emb_apothem(&g, &error))
    TEST(incAngle = emb_inc_angle(&g, &error))
*/
    TEST(clockwise = emb_clockwise(&g, &error))

    printf("test_arc:");
// FIXME:    emb_arc_print(g);
    emb_vector_print(center, "center");
    emb_vector_print(chordMid, "chordMid");
    printf(
        "bulge     = %f\n"
        "radius    = %f\n"
        "diameter  = %f\n"
        "chord     = %f\n"
        "sagitta   = %f\n"
        "apothem   = %f\n"
        "incAngle  = %f\n"
        "clockwise = %d\n"
        "\n",
        bulge,
        radius,
        diameter,
        chord,
        sagitta,
        apothem,
        incAngle,
        clockwise);
}

/* Circle Tangent Test */
int
test_ctangents(EmbGeometry c, EmbVector p, EmbVector s0, EmbVector s1,
    EmbReal tolerence)
{
    EmbVector p0, p1;
    if (!getCircleTangentPoints(c.object.circle, p, &p0, &p1)) {
        printf("Error calculating tangent points.\n");
        return 1;
    }

    printf("Circle : cr=%f, cx=%f, cy=%f\n"
       "Point  : px=%f, py=%f\n"
       "Tangent: tx0=%f, ty0=%f\n"
       "Tangent: tx1=%f, ty1=%f\n\n",
       c.object.circle.radius, c.object.circle.center.x, c.object.circle.center.y,
       p.x, p.y,
       p0.x, p0.y,
       p1.x, p1.y);

    double error = emb_vector_distance(p0, s0) + emb_vector_distance(p1, s1);
    if (error > tolerence) {
        printf("Error larger than tolerance, circle test 2: %f.\n\n", error);
        return 1;
    }
    return 0;
}

EmbError
circle_tests(void)
{
    EmbReal epsilon = 0.001f;
    EmbGeometry c1 = emb_circle(0.0f, 0.0f, 3.0f);
    EmbVector p = emb_vector(4.0f, 0.0f);
    /* Solution */
    EmbVector s0 = emb_vector(2.2500f, 1.9843f);
    EmbVector s1 = emb_vector(2.2500f, -1.9843f);
    int result = test_ctangents(c1, p, s0, s1, epsilon);
    if (result) {
        return result;
    }
    
    c1 = emb_circle(20.1762f, 10.7170f, 6.8221f);
    p = emb_vector(24.3411f, 18.2980f);
    /* Solution */
    s0 = emb_vector(19.0911f, 17.4522f);
    s1 = emb_vector(26.4428f, 13.4133f);
    result = test_ctangents(c1, p, s0, s1, epsilon);
    if (result) {
        return result;
    }
    return EMB_NO_ERR;
}

EmbError
ellipse_tests(void)
{
    return EMB_NO_ERR;
}

/* Conversion Testing */
EmbError
convert_tests(void)
{
    int i;
    for (i=0; i<3; i++) {
        int result = test_convert(i, EMB_FORMAT_CSV, EMB_FORMAT_DST);
        if (result) {
            return result;
        }
        result = test_convert(i, EMB_FORMAT_CSV, EMB_FORMAT_SVG);
        if (result) {
            return result;
        }
    }
    return 0;
}

/* Currently just crash testing. */
EmbError
test_convert(int test_file, int from, int to)
{
    EmbString outf;
    EmbString fname_from;
    EmbString fname_to;
    sprintf(fname_from, "test%02d%s", test_file, formatTable[from].extension);
    sprintf(fname_to, "test%02d_out%s", test_file, formatTable[to].extension);
    printf("Converting test case %d: %s to %s.\n",
        test_file, fname_from, fname_to);

    EmbPattern* p = emb_pattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    emb_pattern_addThread(p, black_thread);

    switch (test_file) {
	case 0: {
        int i;
        EmbStitch st;
		/* 10mm circle */
		for (i = 0; i < 20; i++) {
			emb_pattern_addStitchRel(p, 0.0, 1.0, JUMP, 0);
		}
		for (i = 0; i < 200; i++) {
			st.x = 10 + 10 * sin(i * (0.03141592));
			st.y = 10 + 10 * cos(i * (0.03141592));
			st.flags = NORMAL;
			st.color = 0;
			emb_pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
		}
		break;
	}
	case 1: {
        int i;
        EmbStitch st;
        /* sin wave */
        for (i = 0; i < 100; i++) {
            st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
            st.y = 10 + i * 0.1;
            st.flags = NORMAL;
            st.color = 0;
            emb_pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
        }
		break;
	}
	case 2: {
        EmbGeometry circle = emb_circle(10.0f, 1.0f, 5.0f);
        emb_array_add_geometry(p->geometry, circle);
        emb_pattern_convertGeometry(p);
		break;
	}
    default: {
		puts("This case is not covered.");
		break;
	}
    }

    sprintf(outf, "test%02d%s", test_file, formatTable[to].extension);
    emb_pattern_end(p);
    if (!emb_pattern_write(p, outf, to)) {
        emb_pattern_free(p);
        return 16;
    }

    emb_pattern_free(p);

    convert(fname_from, fname_to);
    return 0;
}

/* todo test_cross_test
 *     --cross-stitch ../images/$1.png 130 $1.svg
 */
EmbError
test_cross(void)
{
    return 0;
}

/* TODO: test_render
 *    --fill ../images/$1.png 130 $1.csv
 *    --fill $1.csv $1.png
 */
EmbError
test_fill(void)
{
    return 0;
}

/*
 * todo test_fill ../images/$1.png 130 $1.svg
 *
 * todo test_cross_test
 *     --cross-stitch ../images/$1.png 130 $1.svg
 *
 * todo test_generate_render
 *     --cross-stitch ../images/$1.png 130 $1.csv
 *     --render $1.csv $1_render.png
 *
 * all_tests
 *    fill_test donut 130
 *    fill_test logo-spirals 130
 *    fill_test berries 130
 *    fill_test snow-squirrel 130
 *    fill_test great-tit 130
 *    fill_test owl 130
 *    fill_test logo 130
 *
 *    cross_test logo
 *    render_fill_test logo
 *    render_cross_test logo
 */

/*
 * Tests for accuracy of the format table lookup and identification
 */
int
format_table_tests(void)
{
    const char*  tName = "example.zsk";
    int format = emb_identify_format(tName);

    printf("Filename   : %s\n"
       "Extension  : %s\n"
       "Description: %s\n"
       "Reader     : %c\n"
       "Writer     : %c\n"
       "Type       : %d\n\n",
        tName,
        formatTable[format].extension,
        formatTable[format].description,
        formatTable[format].reader_state,
        formatTable[format].writer_state,
        formatTable[format].type);

    if (strncmp(formatTable[format].extension, ".zsk", 200)) {
        puts("In format table test the extension lookup failed.");
		return 20;
	}
    if (strncmp(formatTable[format].description, "ZSK USA Embroidery Format", 200)) {
        puts("In format table test the description lookup failed.");
        return 21;
    }
    if (formatTable[format].reader_state != 'U') {
        puts("In format table test the reader_state lookup failed.");
		return 22;
	}
    if (formatTable[format].writer_state != ' ') {
        puts("In format table test the write_state lookup failed.");
		return 23;
	}
    if (formatTable[format].type != 1) {
        puts("In format table test the type lookup failed.");
		return 24;
	}
    return 0;
}

/* TODO: test_render
 *    --fill ../images/$1.png 130 $1.csv
 *    --fill $1.csv $1.png
 */
EmbError
test_photo(void)
{
    return 0;
}

/* todo test_generate_render
 *     --cross-stitch ../images/$1.png 130 $1.csv
 *     --render $1.csv $1_render.png
 */
int
render_tests(void)
{
    return 0;
}

/* all_tests
 *    fill_test donut 130
 *    fill_test logo-spirals 130
 *    fill_test berries 130
 *    fill_test snow-squirrel 130
 *    fill_test great-tit 130
 *    fill_test owl 130
 *    fill_test logo 130
 *
 *    cross_test logo
 *    render_fill_test logo
 *    render_cross_test logo
 */

EmbError
thread_color_tests(void)
{
    unsigned int tColor = 0xFF0d6b2f;
    /*
    EmbColor c;
    c.r = 0x0D;
    c.g = 0x6B;
    c.b = 0x2F;
    */
    int tBrand = EMB_BRAND_SVG;
    int tNum = threadColorNum(tColor, tBrand);
    char tName[50];
    strncpy(tName, threadColorName(tColor, tBrand), 49);

    printf("Color : 0x%X\n"
       "Brand : %d\n"
       "Num   : %d\n"
       "Name  : %s\n\n",
        tColor,
        tBrand,
        tNum, /* Solution: 29 */
        tName); /* Solution: Dark Olive Green */
    return EMB_NO_ERR;
}

EmbError
vector_tests(void)
{
    float epsilon = 0.0000000001;
    EmbVector v1 = emb_vector(1.6, 3.21);
    EmbVector v2 = emb_vector(1.64, 3.11);
    EmbVector result_add = emb_vector(3.24, 6.32);

    if (!test_vadd(v1, v2, result_add, epsilon)) {
        return 1;
    }

    return EMB_NO_ERR;
}

/* . */
EmbError
test_vadd(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence)
{
    EmbVector testResult = emb_vector_add(v1, v2);
    double xerror = fabs(testResult.x - result.x);
    double yerror = fabs(testResult.y - result.y);
    printf("errors: %f %f\n", xerror, yerror);
    if (tolerence < xerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    if (tolerence < yerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    return 0;
}

/* . */
EmbError
test_vsubtract(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence)
{
    EmbVector testResult = emb_vector_subtract(v1, v2);
    double xerror = fabs(testResult.x - result.x);
    double yerror = fabs(testResult.y - result.y);
    printf("errors: %f %f\n", xerror, yerror);
    if (tolerence < xerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    if (tolerence < yerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    return 0;
}

/*
#!/bin/bash
#
# needle
# 1.0.0-alpha
# Copyright 2018-2025 The Embroidermodder Team
# This file is part of libembroidery.
# Under the zlib license.
#

function basic_help_msg () {

    cat <<EOF
needle
1.0.0-alpha
Copyright 2018-2025 The Embroidermodder Team
This program is part of libembroidery.
License: Zlib

A tool for creating and altering machine embroidery files. For a full list of
commands available use "--commands".

Needle extends the functionality of the basic emb-convert tool and it assumes
you have imagemagick and python installed and are running in a bash terminal. During
operation it creates temporary files in the current working directory, then clears
them at the end of the process. These temporary files will be hidden when we are out
of alpha, but for now they are useful to have available during operation.

For a full help message, please use:

    needle --help
EOF

}

function help_msg () {

    man 1 needle

}

function list_commands () {

    cat << EOF
--circle, -c
--line, -l
--generate
--help
--render
--report, -R
--simulate
--test
--todo
EOF

}

function todo_msg () {

    cat <<EOF
Features that were in "embroider" that now are going to use some scripting.

1. Hilbert curve generation
2. Sierpinski triangle generation
3. Dragon curve generation
4. Adding geometric primatives to a pattern (which could be convert to
   SVG, add primative using text manipulation, convert to original format
   or requested format)

All features withing emb_convert need a copy here.

Check necessary dependencies are installed when they are called against.

Check the following flags are covered:
--circle, -c
--ellipse, -e
--line, -l
--polygon, -P
--polyline, -p
--render
--satin, -s
--stitch, -S
--generate hilbert
--generate sierpinski
--fill, -f
--cross-stitch
--simulate
--combine
--ps
--report, -R
EOF

}

function testing () {

    echo "."

}

if [ $# -lt 1 ]; then
    basic_help_msg
    exit
fi

while [ $# -gt 0 ]; do
    case $1 in
    --circle)
        echo "The $1 flag is not implemented yet."
        shift
        shift
        shift;;
    --line)
        echo "The $1 flag is not implemented yet."
        shift
        shift
        shift
        shift;;
    --polygon)
        echo "The $1 flag is not implemented yet."
        shift
        shift
        shift;;
    --photo-fit)
        echo "The $1 flag is not implemented yet."
        shift;;
    --generate)
        echo "The $1 flag is not implemented yet."
        shift;;
    --convert)
        emb_convert $2 $3
        shift
        shift;;
    --commands)
        list_commands;;
    --render)
        emb_convert --render $2
        shift;;
    --simulate)
        emb_convert --simulate $2
        shift;;
    --help)
        help_msg;;
    --todo)
        todo_msg;;
    --test)
        testing;;
    *)
        echo "ERROR: flag $1 not recognised, try --commands.";;
    esac
    shift
done
*/

