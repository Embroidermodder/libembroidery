#include "embroidery.h"
#include <stdio.h>

static int decodeRecordFlags(unsigned char b2)
{
    if (b2 == 0xF3) {
        return END;
    }
    switch (b2 & 0xC3) {
    case 0x03:
        return NORMAL;
    case 0x83:
        return TRIM;
    case 0xC3:
        return STOP;
    default:
        return NORMAL;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readT01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 3, file) == 3) {
        int flags;
        int x = 0;
        int y = 0;
        if (b[0] & 0x01)
            x += 1;
        if (b[0] & 0x02)
            x -= 1;
        if (b[0] & 0x04)
            x += 9;
        if (b[0] & 0x08)
            x -= 9;
        if (b[0] & 0x80)
            y += 1;
        if (b[0] & 0x40)
            y -= 1;
        if (b[0] & 0x20)
            y += 9;
        if (b[0] & 0x10)
            y -= 9;
        if (b[1] & 0x01)
            x += 3;
        if (b[1] & 0x02)
            x -= 3;
        if (b[1] & 0x04)
            x += 27;
        if (b[1] & 0x08)
            x -= 27;
        if (b[1] & 0x80)
            y += 3;
        if (b[1] & 0x40)
            y -= 3;
        if (b[1] & 0x20)
            y += 27;
        if (b[1] & 0x10)
            y -= 27;
        if (b[2] & 0x04)
            x += 81;
        if (b[2] & 0x08)
            x -= 81;
        if (b[2] & 0x20)
            y += 81;
        if (b[2] & 0x10)
            y -= 81;
        flags = decodeRecordFlags(b[2]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END)
            break;
    }

    return 1;
}

static void encode_record(EmbFile* file, int x, int y, int flags)
{
    char b[4];
    b[0] = b[1] = b[2] = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121) {
        embLog("ERROR: format-t01.c encode_record(), x is not in valid range [-121,121] , x =");
        /* embLog_print("%d\n", x); */
    }
    if (y > 121 || y < -121) {
        embLog("ERROR: format-t01.c encode_record(), y is not in valid range [-121,121] , y =");
        /* embLog_print("%d\n", y); */
    }

    if (x >= +41) {
        b[2] += 1 << 2;
        x -= 81;
    }
    if (x <= -41) {
        b[2] += 1 << 3;
        x += 81;
    }
    if (x >= +14) {
        b[1] += 1 << 2;
        x -= 27;
    }
    if (x <= -14) {
        b[1] += 1 << 3;
        x += 27;
    }
    if (x >= +5) {
        b[0] += 1 << 2;
        x -= 9;
    }
    if (x <= -5) {
        b[0] += 1 << 3;
        x += 9;
    }
    if (x >= +2) {
        b[1] += 1 << 0;
        x -= 3;
    }
    if (x <= -2) {
        b[1] += 1 << 1;
        x += 3;
    }
    if (x >= +1) {
        b[0] += 1 << 0;
        x -= 1;
    }
    if (x <= -1) {
        b[0] += 1 << 1;
        x += 1;
    }
    if (x != 0) {
        embLog("ERROR: format-dst.c encode_record(), x should be zero yet x = %d\n");
    }
    if (y >= +41) {
        b[2] += 1 << 5;
        y -= 81;
    }
    if (y <= -41) {
        b[2] += 1 << 4;
        y += 81;
    }
    if (y >= +14) {
        b[1] += 1 << 5;
        y -= 27;
    }
    if (y <= -14) {
        b[1] += 1 << 4;
        y += 27;
    }
    if (y >= +5) {
        b[0] += 1 << 5;
        y -= 9;
    }
    if (y <= -5) {
        b[0] += 1 << 4;
        y += 9;
    }
    if (y >= +2) {
        b[1] += 1 << 7;
        y -= 3;
    }
    if (y <= -2) {
        b[1] += 1 << 6;
        y += 3;
    }
    if (y >= +1) {
        b[0] += 1 << 7;
        y -= 1;
    }
    if (y <= -1) {
        b[0] += 1 << 6;
        y += 1;
    }
    if (y != 0) {
        embLog("ERROR: format-dst.c encode_record(), y should be zero yet y = %d\n");
    }

    b[2] |= (char)3;

    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char)(b[2] | 0xC3);
    }

    embFile_write(b, 1, 3, file);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeT01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int xx, yy, dx, dy, i;
    EmbStitch st;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = roundDouble(st.x * 10.0) - xx;
        dy = roundDouble(st.y * 10.0) - yy;
        xx = roundDouble(st.x * 10.0);
        yy = roundDouble(st.y * 10.0);
        encode_record(file, dx, dy, st.flags);
    }
    return 1;
}

