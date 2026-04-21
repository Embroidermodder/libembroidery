/**
 * @file melco.c
 *
 * Melco Embroidery Format (.exp)
 * Stitch Only Format.
 */

#include "embroidery.h"

char readDst(EmbPattern *pattern, FILE *file);
char writeDst(EmbPattern *pattern, FILE *file);

/* The Melco Embroidery Format (.cnd)
 *
 * The Melco cnd format is a stitch-only format.
 *
 * We don't know much about this format.
 *
 * \todo Find a source.
 */
char readCnd(EmbPattern *pattern, FILE *file)
{
        puts("readCnd is not implemented");
        printf("Cannot read %p %p\n", pattern, file);
        return 0;               /*TODO: finish readCnd */
}

char writeCnd(EmbPattern *pattern, FILE *file)
{
        puts("writeCnd is not implemented");
        printf("Cannot write %p %p\n", pattern, file);
        return 0;               /*TODO: finish writeCnd */
}

/* The Melco Embroidery Format (.dem)
 *
 * Stitch Only Format
 */
char readDem(EmbPattern *pattern, FILE *file)
{
        puts("readDem is not implemented.");
        puts("Overridden, defaulting to dst.");
        return readDst(pattern, file);  /*TODO: finish readDem */
}

char writeDem(EmbPattern *pattern, FILE *file)
{
        puts("writeDem is not implemented.");
        puts("Overridden, defaulting to dst.");
        return writeDst(pattern, file); /*TODO: finish writeDem */
}

char expDecode(unsigned char a1)
{
        return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

char readExp(EmbPattern *pattern, FILE *file)
{
        unsigned char b[2];

        while (fread(b, 1, 2, file) == 2) {
                char dx = 0, dy = 0;
                int flags = NORMAL;
                if (b[0] == 0x80) {
                        if (b[1] == 0x01) {
                                if (fread(b, 1, 2, file) != 2)
                                        break;
                                /* b0=0x00 and b1=0x00, but accept any,
                                   not worth crashing over. */
                                flags = STOP;
                        } else if (b[1] == 0x04) {
                                if (fread(b, 1, 2, file) != 2) {
                                        break;
                                }
                                flags = JUMP;
                        } else if (b[1] == 0x80) {
                                if (fread(b, 1, 2, file) != 2) {
                                        break;
                                }
                                /* b0=0x07 and b1=0x00, but accept any,
                                   not worth crashing over. */
                                flags = TRIM;
                        }
                }
                dx = expDecode(b[0]);
                dy = expDecode(b[1]);
                embp_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        return 1;
}

char writeExp(EmbPattern *pattern, FILE *file)
{
        EmbVector pos;
        int i;

        /* write stitches */
        pos.x = 0.0;
        pos.y = 0.0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                char b[4];
                char dx, dy;
                EmbStitch st = pattern->stitch_list->stitch[i];
                dx = (char)emb_round(10.0 * (st.x - pos.x));
                dy = (char)emb_round(10.0 * (st.y - pos.y));
                pos.x += 0.1 * dx;
                pos.y += 0.1 * dy;
                switch (st.flags) {
                case STOP:
                        b[0] = (char)(0x80);
                        b[1] = 0x01;
                        b[2] = 0x00;
                        b[3] = 0x00;
                        fwrite(b, 1, 4, file);
                        break;
                case JUMP:
                        b[0] = (char)(0x80);
                        b[1] = 0x04;
                        b[2] = dx;
                        b[3] = dy;
                        fwrite(b, 1, 4, file);
                        break;
                case TRIM:
                        b[0] = (char)(0x80);
                        b[1] = (char)(0x80);
                        b[2] = 0x07;
                        b[3] = 0x00;
                        fwrite(b, 1, 4, file);
                        break;
                default:       /* STITCH */
                        b[0] = dx;
                        b[1] = dy;
                        fwrite(b, 1, 2, file);
                        break;
                }
        }
        fprintf(file, "\x1a");
        return 1;
}
