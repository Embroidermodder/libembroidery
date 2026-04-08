/*
 * Pfaff professional Design format (.ksm)
 *
 * Stitch Only Format.
 */

#include "embroidery.h"

void ksmEncode(unsigned char *b, char dx, char dy, int flags)
{
        if (!b) {
                printf("ERROR: format-ksm.c ksmEncode(), b argument is null\n");
                return;
        }
        /* TODO: How to encode JUMP stitches? JUMP must be handled.
           Also check this for the EXP format since it appears to be similar */
        if (flags == TRIM) {
                b[0] = 128;
                b[1] = 2;
                b[2] = dx;
                b[3] = dy;
        } else if (flags == STOP) {
                b[0] = 128;
                b[1] = 1;
                b[2] = dx;
                b[3] = dy;
        } else {
                b[0] = dx;
                b[1] = dy;
        }
}

char readKsm(EmbPattern *pattern, FILE *file)
{
        int prevStitchType = NORMAL;
        char b[3];
        fseek(file, 0x200, SEEK_SET);
        while (fread(b, 1, 3, file) == 3) {
                int flags = NORMAL;

                if (((prevStitchType & 0x08) == 0x08) && (b[2] & 0x08) == 0x08) {
                        flags = STOP;
                } else if ((b[2] & 0x1F) != 0) {
                        flags = TRIM;
                }
                prevStitchType = b[2];
                if (b[2] & 0x40) {
                        b[1] = -b[1];
                }
                if (b[2] & 0x20) {
                        b[0] = -b[0];
                }
                embp_addStitchRel(pattern, b[1] / 10.0, b[0] / 10.0, flags, 1);
        }
        return 1;
}

char writeKsm(EmbPattern *pattern, FILE *file)
{
        EmbVector pos;
        int i;

        fpad(file, 0, 0x200);
        /* write stitches */
        pos.x = 0.0;
        pos.y = 0.0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                unsigned char b[4];
                char dx, dy;
                EmbStitch st = pattern->stitch_list->stitch[i];
                dx = (char)(10.0 * (st.x - pos.x));
                dy = (char)(10.0 * (st.y - pos.y));
                pos.x += 0.1 * dx;
                pos.y += 0.1 * dy;
                ksmEncode(b, dx, dy, st.flags);
                fprintf(file, "%c%c", b[0], b[1]);
        }
        fprintf(file, "\x1a");
        return 1;
}

/* Pfaff Embroidery Format (.max)
 * Stitch Only Format.
 */
const unsigned char max_header[] = {
        0x56, 0x43, 0x53, 0x4D, 0xFC, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00,
        0xF6, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
        0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x31, 0x33, 0x37, 0x38,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x61, 0x64, 0x65,
        0x69, 0x72, 0x61, 0x20,
        0x52, 0x61, 0x79, 0x6F, 0x6E, 0x20, 0x34, 0x30, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x01, 0x38, 0x09, 0x31, 0x33, 0x30, 0x2F, 0x37, 0x30, 0x35, 0x20, 0x48,
        0xFA, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00
};

/* ---------------------------------------------------------------- */
/* format max */

/* Pfaff MAX embroidery file format */
char readMax(EmbPattern *pattern, FILE *file)
{
        unsigned char b[8];

        fseek(file, 0xD5, SEEK_SET);
        /* stitchCount = emb_read_i32(file); CHECK IF THIS IS PRESENT */
        /* READ STITCH RECORDS */
        while (fread(b, 1, 8, file) == 8) {
                EmbReal dx, dy;
                int flags;
                flags = NORMAL;
                dx = pfaffDecode(b[0], b[1], b[2]);
                dy = pfaffDecode(b[4], b[5], b[6]);
                embp_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        embp_flipVertical(pattern);
        return 1;
}

char writeMax(EmbPattern *pattern, FILE *file)
{
        int i;
        EmbReal x, y;
        EmbStitch st;

        fwrite(max_header, 1, 0xD5, file);
        for (i = 0; i < pattern->stitch_list->count; i++) {
                st = pattern->stitch_list->stitch[i];
                x = (int)emb_round(st.x * 10.0);
                y = (int)emb_round(st.y * 10.0);
                write_24bit(file, x);
                write_24bit(file, y);
        }
        return 1;
}
