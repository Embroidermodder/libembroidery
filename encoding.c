/*
 * This file is part of libembroidery.
 *
 * Copyright 2021-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * The functions in this file are grouped together to aid the developer's
 * understanding of the similarities between the file formats. This also helps
 * reduce errors between reimplementation of the same idea.
 *
 * For example: the Tajima ternary encoding of positions is used by at least 4
 * formats and the only part that changes is the flag encoding.
 */

#include "embroidery.h"

#include <stdio.h>

void write_24bit(FILE *file, int dx);

int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags) {
    decode_tajima_ternary(b, x, y);

    if (b[2] == 0xF3) {
        *flags = END;
    }
    else {
        switch (b[2] & 0xC3) {
        case 0x03:
            *flags = NORMAL;
            break;
        case 0x83:
            *flags = TRIM;
            break;
        case 0xC3:
            *flags = STOP;
            break;
        default:
            *flags = NORMAL;
            break;
        }
    }
    return 1;
}

void encode_t01_record(unsigned char b[3], int x, int y, int flags) {
    if (!encode_tajima_ternary(b, x, y)) {
        return;
    }

    b[2] |= (unsigned char)3;
    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (unsigned char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (unsigned char)(b[2] | 0xC3);
    }
}

int encode_tajima_ternary(unsigned char b[3], int x, int y)
{
    b[0] = 0;
    b[1] = 0;
    b[2] = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121) {
        printf("ERROR: format-t01.c encode_record(), ");
        printf("x is not in valid range [-121,121] , x = %d\n", x);
        return 0;
    }
    if (y > 121 || y < -121) {
        printf("ERROR: format-t01.c encode_record(), ");
        printf("y is not in valid range [-121,121] , y = %d\n", y);
        return 0;
    }

    if (x >= +41) {
        b[2] |= EMB_BIT_2;
        x -= 81;
    }
    if (x <= -41) {
        b[2] |= EMB_BIT_3;
        x += 81;
    }
    if (x >= +14) {
        b[1] |= EMB_BIT_2;
        x -= 27;
    }
    if (x <= -14) {
        b[1] |= EMB_BIT_3;
        x += 27;
    }
    if (x >= +5) {
        b[0] |= EMB_BIT_2;
        x -= 9;
    }
    if (x <= -5) {
        b[0] |= EMB_BIT_3;
        x += 9;
    }
    if (x >= +2) {
        b[1] |= EMB_BIT_0;
        x -= 3;
    }
    if (x <= -2) {
        b[1] |= EMB_BIT_1;
        x += 3;
    }
    if (x >= +1) {
        b[0] |= EMB_BIT_0;
        x -= 1;
    }
    if (x <= -1) {
        b[0] |= EMB_BIT_1;
        x += 1;
    }
    if (x != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("x should be zero yet x = %d\n", x);
        return 0;
    }
    if (y >= +41) {
        b[2] |= EMB_BIT_5;
        y -= 81;
    }
    if (y <= -41) {
        b[2] |= EMB_BIT_4;
        y += 81;
    }
    if (y >= +14) {
        b[1] |= EMB_BIT_5;
        y -= 27;
    }
    if (y <= -14) {
        b[1] |= EMB_BIT_4;
        y += 27;
    }
    if (y >= +5) {
        b[0] |= EMB_BIT_5;
        y -= 9;
    }
    if (y <= -5) {
        b[0] |= EMB_BIT_4;
        y += 9;
    }
    if (y >= +2) {
        b[1] |= EMB_BIT_7;
        y -= 3;
    }
    if (y <= -2) {
        b[1] |= EMB_BIT_6;
        y += 3;
    }
    if (y >= +1) {
        b[0] |= EMB_BIT_7;
        y -= 1;
    }
    if (y <= -1) {
        b[0] |= EMB_BIT_6;
        y += 1;
    }
    if (y != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("y should be zero yet y = %d\n", y);
        return 0;
    }
    return 1;
}

void decode_tajima_ternary(unsigned char b[3], int *x, int *y)
{
    *x = 0;
    *y = 0;
    if (b[0] & EMB_BIT_0) {
        *x += 1;
    }
    if (b[0] & EMB_BIT_1) {
        *x -= 1;
    }
    if (b[0] & EMB_BIT_2) {
        *x += 9;
    }
    if (b[0] & EMB_BIT_3) {
        *x -= 9;
    }
    if (b[0] & EMB_BIT_7) {
        *y += 1;
    }
    if (b[0] & EMB_BIT_6) {
        *y -= 1;
    }
    if (b[0] & EMB_BIT_5) {
        *y += 9;
    }
    if (b[0] & EMB_BIT_4) {
        *y -= 9;
    }
    if (b[1] & EMB_BIT_0) {
        *x += 3;
    }
    if (b[1] & EMB_BIT_1) {
        *x -= 3;
    }
    if (b[1] & EMB_BIT_2) {
        *x += 27;
    }
    if (b[1] & EMB_BIT_3) {
        *x -= 27;
    }
    if (b[1] & EMB_BIT_7) {
        *y += 3;
    }
    if (b[1] & EMB_BIT_6) {
        *y -= 3;
    }
    if (b[1] & EMB_BIT_5) {
        *y += 27;
    }
    if (b[1] & EMB_BIT_4) {
        *y -= 27;
    }
    if (b[2] & EMB_BIT_2) {
        *x += 81;
    }
    if (b[2] & EMB_BIT_3) {
        *x -= 81;
    }
    if (b[2] & EMB_BIT_5) {
        *y += 81;
    }
    if (b[2] & EMB_BIT_4) {
        *y -= 81;
    }
}

void pfaffEncode(FILE* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) { printf("ERROR: format-pcs.c pcsEncode(), file argument is null\n"); return; }

    write_24bit(file, dx);
    write_24bit(file, dy);

    if (flags & STOP)
    {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM)
    {
        flagsToWrite |= 0x04;
    }
    binaryWriteByte(file, flagsToWrite);
}

double pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3) {
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return res;
}

unsigned char mitEncodeStitch(double value) {
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

int mitDecodeStitch(unsigned char value) {
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

int decodeNewStitch(unsigned char value) {
    return (int)value;
}

