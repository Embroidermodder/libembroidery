/**
 * @file data.c
 */

#include "embroidery.h"

/* Deal with endianness of the host machine. */
void fix_endian(char *a, int bytes, int endian)
{
        if (endian != ENDIAN_HOST) {
                if (bytes == 2) {
                        emb_swap(a, 0, 1);
                }
                if (bytes == 4) {
                        emb_swap(a, 0, 3);
                        emb_swap(a, 1, 2);
                }
        }
}

/* Read a little-endian signed 16-bit integer. */
int16_t emb_read_i16(FILE *f)
{
        char data[2];
        if (fread(data, 1, 2, f) != 2) {
                puts("ERROR: Failed to read a int16_t.");
                return 0;
        }
        fix_endian(data, 2, EMB_LITTLE_ENDIAN);
        return *((int16_t *) data);
}

/* Read a little-endian unsigned 16-bit integer. */
uint16_t emb_read_u16(FILE *f)
{
        char data[2];
        if (fread(data, 1, 2, f) != 2) {
                puts("ERROR: Failed to read a uint16_t.");
                return 0;
        }
        fix_endian(data, 2, EMB_LITTLE_ENDIAN);
        return *((uint16_t *) data);
}

/* Read a little-endian signed 32-bit integer. */
int32_t emb_read_i32(FILE *f)
{
        char data[4];
        if (fread(data, 1, 4, f) != 4) {
                puts("ERROR: Failed to read a int32_t.");
                return 0;
        }
        fix_endian(data, 4, EMB_LITTLE_ENDIAN);
        return *((int32_t *) data);
}

/* Read a little-endian unsigned 32-bit integer. */
uint32_t emb_read_u32(FILE *f)
{
        char data[4];
        if (fread(data, 1, 4, f) != 4) {
                puts("ERROR: Failed to read a uint32_t.");
                return 0;
        }
        fix_endian(data, 4, EMB_LITTLE_ENDIAN);
        return *((uint32_t *) data);
}

/* Read a big-endian signed 16-bit integer. */
int16_t emb_read_i16be(FILE *f)
{
        char data[2];
        if (fread(data, 1, 2, f) != 2) {
                puts("ERROR: Failed to read a int16_t.");
                return 0;
        }
        fix_endian(data, 2, EMB_BIG_ENDIAN);
        return *((int16_t *) data);
}

/* Read a big-endian unsigned 16-bit integer. */
uint16_t emb_read_u16be(FILE *f)
{
        char data[2];
        if (fread(data, 1, 2, f) != 2) {
                puts("ERROR: Failed to read a uint16_t.");
                return 0;
        }
        fix_endian(data, 2, EMB_BIG_ENDIAN);
        return *((uint16_t *) data);
}

/* Read a big-endian signed 32-bit integer. */
int32_t emb_read_i32be(FILE *f)
{
        char data[4];
        if (fread(data, 1, 4, f) != 4) {
                puts("ERROR: Failed to read a int32_t.");
                return 0;
        }
        fix_endian(data, 4, EMB_BIG_ENDIAN);
        return *((int32_t *) data);
}

/* Read a big-endian unsigned 32-bit integer. */
uint32_t emb_read_u32be(FILE *f)
{
        char data[4];
        if (fread(data, 1, 4, f) != 4) {
                puts("ERROR: Failed to read a uint32_t.");
                return 0;
        }
        fix_endian(data, 4, EMB_BIG_ENDIAN);
        return *((uint32_t *) data);
}

/*
 * TO DO: NEEDS ERROR REPORTING.
 */
unsigned char toyota_position_encode(EmbReal x)
{
        if (x < 0.0) {
                return 0x80 + (-((char)emb_round(10.0 * x)));
        }
        return (unsigned char)emb_round(10.0 * x);
}

/*
 * .
 */
EmbReal toyota_position_decode(unsigned char a)
{
        if (a > 0x80) {
                return -0.1 * (a - 0x80);
        }
        return 0.1 * a;
}

/* a b a x a y a flags .
 *
 * \todo remove the unused return argument.
 */
int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags)
{
        decode_tajima_ternary(b, x, y);

        if (b[2] == 0xF3) {
                *flags = END;
                return 1;
        }
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
        return 1;
}

/* Encode into bytes a b the values of the x-position a x,
 * y-position a y and the a flags.
 */
void encode_t01_record(unsigned char b[3], int x, int y, int flags)
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

/* Encode the signed ternary of the tajima format into
 * a b the position values a x and a y.
 *
 * If the values of a x or a y fall outside of the
 * valid range of -121 and +121 then it returns 0 and
 * 1.
 */
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

/* Decode the signed ternary of the tajima format from
 * a b to the position values a x and a y.
 *
 * There is no return argument.
 */
void decode_tajima_ternary(unsigned char b[3], int *x, int *y)
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

/* a file a dx a dy a flags
 */
void pfaffEncode(FILE *file, int dx, int dy, int flags)
{
        unsigned char flagsToWrite = 0;

        if (!file) {
                printf
                    ("ERROR: format-pcs.c pcsEncode(), file argument is null\n");
                return;
        }

        write_24bit(file, dx);
        write_24bit(file, dy);

        if (flags & STOP) {
                flagsToWrite |= 0x01;
        }
        if (flags & TRIM) {
                flagsToWrite |= 0x04;
        }
        fwrite(&flagsToWrite, 1, 1, file);
}

/* Decode the bytes a a1, a a2 and a a3 .
 * Returns the EmbReal floating-point value.
 */
EmbReal pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
        int res = a1 + (a2 << 8) + (a3 << 16);
        if (res > 0x7FFFFF) {
                return (-((~(res) & 0x7FFFFF) - 1));
        }
        return 1.0f * res;
}

/*  * a value
 * Returns unsigned char
 */
unsigned char mitEncodeStitch(EmbReal value)
{
        if (value < 0) {
                return 0x80 | (unsigned char)(-value);
        }
        return (unsigned char)value;
}

/*  * a value
 * Returns int
 */
int mitDecodeStitch(unsigned char value)
{
        if (value & 0x80) {
                return -(value & 0x1F);
        }
        return value;
}

/*  * a value
 * Returns int
 */
int decodeNewStitch(unsigned char value)
{
        return (int)value;
}

/* . */
void fpad(FILE *file, char c, int n)
{
        int i;
        for (i = 0; i < n; i++) {
                fwrite(&c, 1, 1, file);
        }
}

/* . */
void emb_write_i16(FILE *f, int16_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 2, EMB_LITTLE_ENDIAN);
        fwrite(b, 1, 2, f);
}

/* . */
void emb_write_u16(FILE *f, uint16_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 2, EMB_LITTLE_ENDIAN);
        fwrite(b, 1, 2, f);
}

/* . */
void emb_write_i16be(FILE *f, int16_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 2, EMB_BIG_ENDIAN);
        fwrite(b, 1, 2, f);
}

/* . */
void emb_write_u16be(FILE *f, uint16_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 2, EMB_BIG_ENDIAN);
        fwrite(b, 1, 2, f);
}

/* . */
void emb_write_i32(FILE *f, int32_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 4, EMB_LITTLE_ENDIAN);
        fwrite(b, 1, 4, f);
}

/* . */
void emb_write_u32(FILE *f, uint32_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 4, EMB_LITTLE_ENDIAN);
        fwrite(b, 1, 4, f);
}

/* . */
void emb_write_i32be(FILE *f, int32_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 4, EMB_BIG_ENDIAN);
        fwrite(b, 1, 4, f);
}

/* . */
void emb_write_u32be(FILE *f, uint32_t data)
{
        char *b = (char *)(&data);
        fix_endian(b, 4, EMB_BIG_ENDIAN);
        fwrite(b, 1, 4, f);
}
