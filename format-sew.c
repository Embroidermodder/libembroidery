#include "embroidery.h"
#include <stdio.h>
#include <stdlib.h>
#include "emb-macro.h"

static char sewDecode(unsigned char inputByte)
{
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char)(-~(inputByte - 1)) : (char)inputByte;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readSew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, flags, numberOfColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    embFile_seek(file, 0x00, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x00, SEEK_SET);
    numberOfColors = binaryReadByte(file);
    numberOfColors += (binaryReadByte(file) << 8);

    for (i = 0; i < numberOfColors; i++) {
        embPattern_addThread(pattern, jefThreads[binaryReadInt16(file)]);
    }
    embFile_seek(file, 0x1D78, SEEK_SET);

    for (i = 0; embFile_tell(file) < fileLength; i++) {
        unsigned char b0 = binaryReadByte(file);
        unsigned char b1 = binaryReadByte(file);

        flags = NORMAL;
        if (thisStitchIsJump) {
            flags = TRIM;
            thisStitchIsJump = 0;
        }
        if (b0 == 0x80) {
            if (b1 == 1) {
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
                flags = STOP;
            } else if ((b1 == 0x02) || (b1 == 0x04)) {
                thisStitchIsJump = 1;
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
                flags = TRIM;
            } else if (b1 == 0x10) {
                break;
            }
        }
        dx = sewDecode(b0);
        dy = sewDecode(b1);
        if (abs(dx) == 127 || abs(dy) == 127) {
            thisStitchIsJump = 1;
            flags = TRIM;
        }

        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    printf("current position: %ld\n", embFile_tell(file));

    return 1;
}

static void sewEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        embLog("ERROR: format-exp.c expEncode(), b argument is null\n");
        return;
    }
    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == END) {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    } else if (flags == TRIM || flags == JUMP) {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}
/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeSew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int colorlistSize, minColors, i, thr;
    EmbStitch st;
    EmbColor col;
    double dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    colorlistSize = pattern->threads->count;

    minColors = EMB_MAX_2(pattern->threads->count, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    for (i = 0; i < pattern->threads->count; i++) {
        col = pattern->threads->thread[i].color;
        thr = embThread_findNearestColor_fromThread(col, jefThreads, 79);
        binaryWriteInt(file, thr);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        binaryWriteInt(file, 0x0D);
    }

    for (i = 2; i < 7538; i++) {
        embFile_print(file, " ");
    }

    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        sewEncode(b, (char)roundDouble(dx), (char)roundDouble(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            embFile_write(b, 1, 4, file);
        } else {
            embFile_write(b, 1, 2, file);
        }
    }
    return 1;
}

