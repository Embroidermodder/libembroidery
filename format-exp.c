#include "embroidery.h"
#include <stdio.h>

static char expDecode(unsigned char a1)
{
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

static void expEncode(unsigned char* b, char dx, char dy, int flags)
{
    if(!b)
    {
        printf("ERROR: format-exp.c expEncode(), b argument is null\n");
        return;
    }

    switch (flags) {
    case STOP:
        b[0] = 0x80;
        b[1] = 0x01;
        b[2] = 0x00;
        b[3] = 0x00;
        break;
    case JUMP:
        b[0] = 0x80;
        b[1] = 0x04;
        b[2] = dx;
        b[3] = dy;
        break;
    case TRIM:
        b[0] = 0x80;
        b[1] = 0x80;
        b[2] = 0x07;
        b[3] = 0x00;
        break;
    default: /* STITCH */
        b[0] = dx;
        b[1] = dy;
        break;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readExp(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;
    unsigned char b[2];

    if (!validateReadPattern(pattern, fileName, "readExp")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 2, file) == 2) {
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (b[0] == 0x80) {
            if (b[1] == 0x01) {
                if (embFile_read(b, 1, 2, file) != 2) break;
                /* b0=0x00 and b1=0x00, but accept any, not worth crashing over. */
                flags = STOP;
            }
            else if (b[1] == 0x04) {
                if (embFile_read(b, 1, 2, file) != 2) break;
                flags = JUMP;
            }
            else if (b[1] == 0x80) {
                if (embFile_read(b, 1, 2, file) != 2) break;
                /* b0=0x07 and b1=0x00, but accept any, not worth crashing over. */
                flags = TRIM;
            }
        }
        dx = expDecode(b[0]);
        dy = expDecode(b[1]);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeExp(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file = 0;
    EmbStitchList* stitches = 0;
    double dx = 0.0, dy = 0.0;
    double xx = 0.0, yy = 0.0;
    int flags = 0;
    unsigned char b[4];
    EmbStitch st;

    if (!validateWritePattern(pattern, fileName, "writeExp")) return 0;

    file = embFile_open(fileName, "wb", 0);
    if (!file) return 0;

    /* write stitches */
    stitches = pattern->stitchList;
    while (stitches) {
        st = stitches->stitch;
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        flags = st.flags;
        expEncode(b, (char)roundDouble(dx), (char)roundDouble(dy), flags);
        if((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10)))
        {
            embFile_printf(file, "%c%c%c%c", b[0], b[1], b[2], b[3]);
        }
        else
        {
            embFile_printf(file, "%c%c", b[0], b[1]);
        }
        stitches = stitches->next;
    }
    embFile_printf(file, "\x1a");
    embFile_close(file);
    return 1;
}

