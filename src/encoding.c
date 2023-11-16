/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * This file contains all the read and write functions for the
 * library.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "embroidery_internal.h"

void write_24bit(FILE* file, int);

/**
 * \file encoding.c
 *
 * The functions in this file are grouped together to aid the developer's
 * understanding of the similarities between the file formats. This also helps
 * reduce errors between reimplementation of the same idea.
 *
 * For example: the Tajima ternary encoding of positions is used by at least 4
 * formats and the only part that changes is the flag encoding.
 */

/*  */

/**
 * @brief Converts a 6 digit hex string (I.E. "00FF00")
 * into an EmbColor and returns it.
 *
 * \a val 6 byte code describing the color as a hex string, doesn't require null termination.
 * @return EmbColor the same color as our internal type.
 */
EmbColor
embColor_fromHexStr(char* val)
{
    EmbColor color;
    char r[3];
    char g[3];
    char b[3];

    r[0] = val[0];
    r[1] = val[1];
    r[2] = 0;

    g[0] = val[2];
    g[1] = val[3];
    g[2] = 0;

    b[0] = val[4];
    b[1] = val[5];
    b[2] = 0;

    color.r = (unsigned char)strtol(r, 0, 16);
    color.g = (unsigned char)strtol(g, 0, 16);
    color.b = (unsigned char)strtol(b, 0, 16);
    return color;
}

/**
 * Reverses the byte order of \a bytes number of bytes
 * at memory location \a b. Only works for 2 or 4 byte arrays.
 */
void
reverse_byte_order(void *b, int bytes)
{
    char swap;
    if (bytes == 2) {
        swap = *((char*)b+0);
        *((char*)b+0) = *((char*)b+1);
        *((char*)b+1) = swap;
    }
    else {
        swap = *((char*)b+0);
        *((char*)b+0) = *((char*)b+3);
        *((char*)b+3) = swap;
        swap = *((char*)b+1);
        *((char*)b+1) = *((char*)b+2);
        *((char*)b+2) = swap;
    }
}

/**
 * \a b \a x \a y \a flags .
 *
 * \todo remove the unused return argument.
 */
int
decode_t01_record(unsigned char b[3], int *x, int *y, int *flags)
{
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

/**
 * Encode into bytes \a b the values of the x-position \a x,
 * y-position \a y and the \a flags.
 */
void
encode_t01_record(unsigned char b[3], int x, int y, int flags)
{
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

/**
 * Encode the signed ternary of the tajima format into
 * \a b the position values \a x and \a y.
 *
 * If the values of \a x or \a y fall outside of the
 * valid range of -121 and +121 then it returns 0 and
 * 1.
 */
int
encode_tajima_ternary(unsigned char b[3], int x, int y)
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
        b[2] |= 0x04;
        x -= 81;
    }
    if (x <= -41) {
        b[2] |= 0x08;
        x += 81;
    }
    if (x >= +14) {
        b[1] |= 0x04;
        x -= 27;
    }
    if (x <= -14) {
        b[1] |= 0x08;
        x += 27;
    }
    if (x >= +5) {
        b[0] |= 0x04;
        x -= 9;
    }
    if (x <= -5) {
        b[0] |= 0x08;
        x += 9;
    }
    if (x >= +2) {
        b[1] |= 0x01;
        x -= 3;
    }
    if (x <= -2) {
        b[1] |= 0x02;
        x += 3;
    }
    if (x >= +1) {
        b[0] |= 0x01;
        x -= 1;
    }
    if (x <= -1) {
        b[0] |= 0x02;
        x += 1;
    }
    if (x != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("x should be zero yet x = %d\n", x);
        return 0;
    }
    if (y >= +41) {
        b[2] |= 0x20;
        y -= 81;
    }
    if (y <= -41) {
        b[2] |= 0x10;
        y += 81;
    }
    if (y >= +14) {
        b[1] |= 0x20;
        y -= 27;
    }
    if (y <= -14) {
        b[1] |= 0x10;
        y += 27;
    }
    if (y >= +5) {
        b[0] |= 0x20;
        y -= 9;
    }
    if (y <= -5) {
        b[0] |= 0x10;
        y += 9;
    }
    if (y >= +2) {
        b[1] |= 0x80;
        y -= 3;
    }
    if (y <= -2) {
        b[1] |= 0x40;
        y += 3;
    }
    if (y >= +1) {
        b[0] |= 0x80;
        y -= 1;
    }
    if (y <= -1) {
        b[0] |= 0x40;
        y += 1;
    }
    if (y != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("y should be zero yet y = %d\n", y);
        return 0;
    }
    return 1;
}

/**
 * Decode the signed ternary of the tajima format from
 * \a b to the position values \a x and \a y.
 *
 * There is no return argument.
 */
void
decode_tajima_ternary(unsigned char b[3], int *x, int *y)
{
    *x = 0;
    *y = 0;
    if (b[0] & 0x01) {
        *x += 1;
    }
    if (b[0] & 0x02) {
        *x -= 1;
    }
    if (b[0] & 0x04) {
        *x += 9;
    }
    if (b[0] & 0x08) {
        *x -= 9;
    }
    if (b[0] & 0x80) {
        *y += 1;
    }
    if (b[0] & 0x40) {
        *y -= 1;
    }
    if (b[0] & 0x20) {
        *y += 9;
    }
    if (b[0] & 0x10) {
        *y -= 9;
    }
    if (b[1] & 0x01) {
        *x += 3;
    }
    if (b[1] & 0x02) {
        *x -= 3;
    }
    if (b[1] & 0x04) {
        *x += 27;
    }
    if (b[1] & 0x08) {
        *x -= 27;
    }
    if (b[1] & 0x80) {
        *y += 3;
    }
    if (b[1] & 0x40) {
        *y -= 3;
    }
    if (b[1] & 0x20) {
        *y += 27;
    }
    if (b[1] & 0x10) {
        *y -= 27;
    }
    if (b[2] & 0x04) {
        *x += 81;
    }
    if (b[2] & 0x08) {
        *x -= 81;
    }
    if (b[2] & 0x20) {
        *y += 81;
    }
    if (b[2] & 0x10) {
        *y -= 81;
    }
}

/**
 * \a file \a dx \a dy \a flags
 */
void pfaffEncode(FILE* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) {
        printf("ERROR: format-pcs.c pcsEncode(), file argument is null\n");
        return;
    }

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
    fwrite(&flagsToWrite, 1, 1, file);
}

/**
 * Decode the bytes \a a1, \a a2 and \a a3 .
 * Returns the EmbReal floating-point value.
 */
EmbReal
pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return res;
}

/**
 * @brief
 *
 * \a value
 * @return unsigned char
 */
unsigned char
mitEncodeStitch(EmbReal value)
{
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

/**
 * @brief
 *
 * \a value
 * @return int
 */
int
mitDecodeStitch(unsigned char value)
{
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

/**
 * @brief
 *
 * \a value
 * @return int
 */
int
decodeNewStitch(unsigned char value)
{
    return (int)value;
}

/**
 * \a f \a label \a b \a mode
 *
 * Read and write system for multiple byte types.
 *
 * The caller passes the function to read/write from, the
 * memory location as a void pointer and a mode identifier that describes
 * the type. This way we can abstract out the endianness of the
 * system running the library and don't have to maintain many functions,
 * just two.
 */
void
embInt_read(FILE* f, char *label, void *b, int mode)
{
    int endian = mode & 0x01;
    int length = mode - endian;
    fread(b, 1, length, f);
    if (endian != ENDIAN_HOST) {
        reverse_byte_order(b, length);
    }

    if (emb_verbose>1) {
        switch (mode) {
        case EMB_INT16_LITTLE:
            printf("read int16_le %s: %d\n", label, *((short*)b));
            break;
        case EMB_INT16_BIG:
            printf("read int16_be %s: %d\n", label, *((short*)b));
            break;
        case EMB_INT32_LITTLE:
            printf("read int32_le %s: %d\n", label, *((int*)b));
            break;
        case EMB_INT32_BIG:
            printf("read int32_be %s: %d\n", label, *((int*)b));
            break;
        default:
            puts("ERROR: the mode supplied to fread_int is invalid.");
            break;
        }
    }
}

/**
 * \a f \a label \a b \a mode
 */
void
embInt_write(FILE* f, char *label, void *b, int mode)
{
    int endian = mode & 0x01;
    int length = mode - endian;
    if (endian != ENDIAN_HOST) {
        reverse_byte_order(b, length);
    }
    if (emb_verbose>1) {
        switch (mode) {
        case EMB_INT16_LITTLE:
            printf("write int16_le %s: %d\n", label, *((short*)b));
            break;
        case EMB_INT16_BIG:
            printf("write int16_be %s: %d\n", label, *((short*)b));
            break;
        case EMB_INT32_LITTLE:
            printf("write int32_le %s: %d\n", label, *((int*)b));
            break;
        case EMB_INT32_BIG:
            printf("write int32_be %s: %d\n", label, *((int*)b));
            break;
        default:
            puts("ERROR: the mode supplied to fwrite_int is invalid.");
            break;
        }
    }

    fwrite(b, 1, length, f);
}

