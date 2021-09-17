#include "embroidery.h"
#include <stdio.h>

static char expDecode(unsigned char a1)
{
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

static void expEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        embLog("ERROR: format-exp.c expEncode(), b argument is null\n");
        return;
    }

    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 0x01;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == JUMP) {
        b[0] = 0x80;
        b[1] = 0x04;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == TRIM || flags == END) {
        b[0] = 0x80;
        b[1] = 0x80;
        b[2] = 0;
        b[3] = 0;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readExp(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i = 0;
    unsigned char b0 = 0, b1 = 0;
    char dx = 0, dy = 0;
    int flags = 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    for (i = 0; !embFile_eof(file); i++) {
        flags = NORMAL;
        b0 = (unsigned char)embFile_getc(file);
        if (embFile_eof(file))
            break;
        b1 = (unsigned char)embFile_getc(file);
        if (embFile_eof(file))
            break;
        if (b0 == 0x80) {
            if (b1 & 1) {
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                flags = STOP;
            } else if ((b1 == 2) || (b1 == 4) || b1 == 6) {
                flags = TRIM;
                if (b1 == 2)
                    flags = NORMAL;
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
            } else if (b1 == 0x80) {
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                /* Seems to be b0=0x07 and b1=0x00
                 * Maybe used as extension functions */
                b0 = 0;
                b1 = 0;
                flags = TRIM;
            }
        }
        dx = expDecode(b0);
        dy = expDecode(b1);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeExp(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    double dx, dy, xx, yy;
    int flags = 0, i;
    unsigned char b[4];
    EmbStitch st;

    /* write stitches */
    xx = yy = 0.0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        flags = st.flags;
        expEncode(b, (char)roundDouble(dx), (char)roundDouble(dy), flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            embFile_write(b, 1, 4, file);
        } else {
            embFile_write(b, 1, 2, file);
        }
    }
    embFile_print(file, "\x1a");
    return 1;
}

