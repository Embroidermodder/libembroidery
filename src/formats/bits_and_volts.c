/**
 * @file bits_and_volts.c
 *
 * The Bits and Volts Embroidery Format (.bro)
 *
 * The Bits and Volts bro format is a stitch-only format that
 * uses an external color file.
 *
 * The header is 256 bytes.
 * There's a series of unknown variables in the header.
 *
 * The stitch list uses a variable length encoding which is
 * 2 bytes for any stitch.
 */

#include "embroidery.h"

char readBro(EmbPattern *pattern, FILE *file)
{
        unsigned char header[19];
        unsigned char *ptr = header;
        if (fread(header, 1, 19, file) != 19) {
                return 0;
        }
        /* TODO: determine what this unknown data is.
         * In positions 0x0-0x4, 0xC-0xC+0x8
         */
        ptr += 3;
        char *name = (char *)ptr;       /* 8 chars long */
        printf("readBro: %s\n", name);

        fseek(file, 0x100, SEEK_SET);

        while (!feof(file)) {
                short b1, b2;
                int stitchType = NORMAL;
                b1 = (unsigned char)fgetc(file);
                b2 = (unsigned char)fgetc(file);
                if (b1 == -128) {
                        unsigned char bCode = (unsigned char)fgetc(file);
                        if (fread(&b1, 2, 1, file) != 1) {
                                puts("ERROR");
                                return 0;
                        }
                        if (fread(&b2, 2, 1, file) != 1) {
                                puts("ERROR");
                                return 0;
                        }
                        /* Embird uses 0x02 and Wilcom uses 0xE1 */
                        if (bCode == 0x02 || bCode == 0xE1) {
                                stitchType = STOP;
                        } else if (bCode == 3) {
                                stitchType = TRIM;
                        } else if (bCode == 0x7E) {
                                embp_addStitchRel(pattern, 0, 0, END, 1);
                                break;
                        }
                }
                embp_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
        }
        return 1;
}

char writeBro(EmbPattern *pattern, FILE *file)
{
        puts("writeBro is not implemented");
        printf("Cannot write %p %p\n", pattern, file);
        return 0;               /*TODO: finish writeBro */
}
