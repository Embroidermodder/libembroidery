/**
 * @file brother.c
 *
 * Brother Embroidery Formats (.pec, .pes, .phb)
 * The phb and pec formats is stitch-only.
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

const int pecThreadCount = 65;

char readPhb(EmbPattern * pattern, FILE * file);
char writePhb(EmbPattern * pattern, FILE * file);
char readPem(EmbPattern * pattern, FILE * file);
char writePem(EmbPattern * pattern, FILE * file);

int read_descriptions(FILE * file, EmbPattern * pattern);
void readHoopName(FILE * file, EmbPattern * pattern);
void readImageString(FILE * file, EmbPattern * pattern);
void readProgrammableFills(FILE * file, EmbPattern * pattern);
void readMotifPatterns(FILE * file, EmbPattern * pattern);
void readFeatherPatterns(FILE * file, EmbPattern * pattern);
void readThreads(FILE * file, EmbPattern * pattern);

void readPESHeaderV5(FILE * file, EmbPattern * pattern);
void readPESHeaderV6(FILE * file, EmbPattern * pattern);
void readPESHeaderV7(FILE * file, EmbPattern * pattern);
void readPESHeaderV8(FILE * file, EmbPattern * pattern);
void readPESHeaderV9(FILE * file, EmbPattern * pattern);
void readPESHeaderV10(FILE * file, EmbPattern * pattern);

/*
 * Frame for PES formats
 */
const char imageWithFrame[38][48] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
         0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
         0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
         0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
         0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
         0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/*
 * Write a PES embedded a image to the given a file pointer.
 */
void writeImage(FILE *file, unsigned char image[][48])
{
        int i, j;

        if (!file) {
                printf
                    ("ERROR: format-pec.c writeImage(), file argument is null\n");
                return;
        }
        for (i = 0; i < 38; i++) {
                for (j = 0; j < 6; j++) {
                        int offset = j * 8;
                        unsigned char output = 0;
                        output |= (unsigned char)(image[i][offset] != 0);
                        output |=
                            (unsigned char)(image[i][offset + 1] !=
                                            (unsigned char)0) << 1;
                        output |=
                            (unsigned char)(image[i][offset + 2] !=
                                            (unsigned char)0) << 2;
                        output |=
                            (unsigned char)(image[i][offset + 3] !=
                                            (unsigned char)0) << 3;
                        output |=
                            (unsigned char)(image[i][offset + 4] !=
                                            (unsigned char)0) << 4;
                        output |=
                            (unsigned char)(image[i][offset + 5] !=
                                            (unsigned char)0) << 5;
                        output |=
                            (unsigned char)(image[i][offset + 6] !=
                                            (unsigned char)0) << 6;
                        output |=
                            (unsigned char)(image[i][offset + 7] !=
                                            (unsigned char)0) << 7;
                        fwrite(&output, 1, 1, file);
                }
        }
}

void readPecStitches(EmbPattern *pattern, FILE *file)
{
        unsigned char b[2];

        while (fread(b, 1, 2, file) == 2) {
                int val1 = (int)b[0];
                int val2 = (int)b[1];

                int stitchType = NORMAL;
                if (b[0] == 0xFF && b[1] == 0x00) {
                        embp_end(pattern);
                        return;
                }
                if (b[0] == 0xFE && b[1] == 0xB0) {
                        (void)fgetc(file);
                        embp_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
                        continue;
                }
                /* High bit set means 12-bit offset, otherwise 7-bit signed delta */
                if (val1 & 0x80) {
                        if (val1 & 0x20)
                                stitchType = TRIM;
                        if (val1 & 0x10)
                                stitchType = JUMP;
                        val1 = ((val1 & 0x0F) << 8) + val2;

                        /* Signed 12-bit arithmetic */
                        if (val1 & 0x800) {
                                val1 -= 0x1000;
                        }
                } else if (val1 >= 0x40) {
                        val1 -= 0x80;
                }
                if (val2 & 0x80) {
                        if (val2 & 0x20)
                                stitchType = TRIM;
                        if (val2 & 0x10)
                                stitchType = JUMP;
                        val2 = ((val2 & 0x0F) << 8) + fgetc(file);

                        /* Signed 12-bit arithmetic */
                        if (val2 & 0x800) {
                                val2 -= 0x1000;
                        }
                } else if (val2 >= 0x40) {
                        val2 -= 0x80;
                }

                embp_addStitchRel(pattern, val1 / 10.0,
                                  val2 / 10.0, stitchType, 1);
        }
}

void pecEncodeJump(FILE *file, int x, int types)
{
        int outputVal = abs(x) & 0x7FF;
        unsigned int orPart = 0x80;
        unsigned char toWrite;

        if (!file) {
                printf
                    ("ERROR: format-pec.c pecEncodeJump(), file argument is null\n");
                return;
        }
        if (types & TRIM) {
                orPart |= 0x20;
        }
        if (types & JUMP) {
                orPart |= 0x10;
        }
        if (x < 0) {
                outputVal = (x + 0x1000) & 0x7FF;
                outputVal |= 0x800;
        }
        toWrite = (unsigned char)(((outputVal >> 8) & 0x0F) | orPart);
        fwrite(&toWrite, 1, 1, file);
        toWrite = (unsigned char)(outputVal & 0xFF);
        fwrite(&toWrite, 1, 1, file);
}

void pecEncodeStop(FILE *file, unsigned char val)
{
        if (!file) {
                printf
                    ("ERROR: format-pec.c pecEncodeStop(), file argument is null\n");
                return;
        }
        fwrite("\xFE\xB0", 1, 2, file);
        fwrite(&val, 1, 1, file);
}

char readPec(EmbPattern *pattern, const char *fileName, FILE *file)
{
        unsigned int graphicsOffset;
        unsigned char colorChanges;
        int i;

        if (emb_verbose > 1) {
                printf("fileName: %s\n", fileName);
        }

        if (!check_header_present(file, 0x20A)) {
                return 0;
        }

        fseek(file, 0x38, SEEK_SET);
        colorChanges = (unsigned char)(char)fgetc(file);
        for (i = 0; i <= colorChanges; i++) {
                embp_addThread(pattern, pec_colors[(char)fgetc(file) % 65]);
        }

        /* Get Graphics offset */
        fseek(file, 0x20A, SEEK_SET);

        graphicsOffset = (unsigned int)(fgetc(file));
        graphicsOffset |= (fgetc(file) << 8);
        graphicsOffset |= (fgetc(file) << 16);
        REPORT_INT(graphicsOffset)
            (void)(char)fgetc(file);    /* 0x31 */
        (void)(char)fgetc(file);        /* 0xFF */
        (void)(char)fgetc(file);        /* 0xF0 */
        /* Get X and Y size in .1 mm */
        /* 0x210 */
        emb_read_i16(file);     /* x size */
        emb_read_i16(file);     /* y size */

        emb_read_i16(file);     /* 0x01E0 */
        emb_read_i16(file);     /* 0x01B0 */
        emb_read_i16(file);     /* distance left from start */
        emb_read_i16(file);     /* distance up from start */

        /* Begin Stitch Data */
        /* 0x21C */
        /*unsigned int end = graphicsOffset + 0x208; */
        readPecStitches(pattern, file);
        embp_flipVertical(pattern);
        return 1;
}

void pecEncode(FILE *file, EmbPattern *p)
{
        EmbReal thisX = 0.0;
        EmbReal thisY = 0.0;
        unsigned char stopCode = 2;
        int i;

        if (!file) {
                printf
                    ("ERROR: format-pec.c pecEncode(), file argument is null\n");
                return;
        }
        if (!p) {
                printf("ERROR: format-pec.c pecEncode(), p argument is null\n");
                return;
        }

        for (i = 0; i < p->stitch_list->count; i++) {
                int deltaX, deltaY;
                EmbStitch s = p->stitch_list->stitch[i];

                deltaX = (int)emb_round(s.x - thisX);
                deltaY = (int)emb_round(s.y - thisY);
                thisX += (EmbReal) deltaX;
                thisY += (EmbReal) deltaY;

                if (s.flags & STOP) {
                        pecEncodeStop(file, stopCode);
                        if (stopCode == (unsigned char)2) {
                                stopCode = (unsigned char)1;
                        } else {
                                stopCode = (unsigned char)2;
                        }
                } else if (s.flags & END) {
                        fwrite("\xFF", 1, 1, file);
                        break;
                } else if (deltaX < 63 && deltaX > -64 && deltaY < 63
                           && deltaY > -64 && (!(s.flags & (JUMP | TRIM)))) {
                        unsigned char out[2];
                        if (deltaX < 0) {
                                out[0] = (unsigned char)(deltaX + 0x80);
                        } else {
                                out[0] = (unsigned char)deltaX;
                        }
                        if (deltaY < 0) {
                                out[1] = (unsigned char)(deltaY + 0x80);
                        } else {
                                out[1] = (unsigned char)deltaY;
                        }
                        fwrite(out, 1, 2, file);
                } else {
                        pecEncodeJump(file, deltaX, s.flags);
                        pecEncodeJump(file, deltaY, s.flags);
                }
        }
}

void writeImage(FILE * file, unsigned char image[][48]);

void writePecStitches(EmbPattern *pattern, FILE *file, const char *fileName)
{
        EmbRect bounds;
        unsigned char image[38][48], toWrite;
        int i, j, flen, graphicsOffsetLocation;
        int graphicsOffsetValue, height, width;
        EmbReal xFactor, yFactor;
        const char *forwardSlashPos = fileName + string_rchar(fileName, '/');
        const char *backSlashPos = fileName + string_rchar(fileName, '\\');
        const char *dotPos = fileName + string_rchar(fileName, '.');
        const char *start = 0;

        start = fileName;
        if (forwardSlashPos) {
                start = forwardSlashPos + 1;
        }
        if (backSlashPos && backSlashPos > start) {
                start = backSlashPos + 1;
        }
        fwrite("LA:", 1, 3, file);
        flen = (int)(dotPos - start);

        while (start < dotPos) {
                fwrite(start, 1, 1, file);
                start++;
        }
        fpad(file, 0x20, 16 - flen);
        fwrite("\x0D", 1, 1, file);
        fpad(file, 0x20, 12);
        fwrite("\xff\x00\x06\x26", 1, 4, file);

        fpad(file, 0x20, 12);
        toWrite = (unsigned char)(pattern->thread_list->count - 1);
        fwrite(&toWrite, 1, 1, file);

        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor thr = pattern->thread_list->thread[i].color;
                unsigned char color = (unsigned char)
                    emb_find_nearest_thread(thr,
                                            (EmbThread *) pec_colors,
                                            pecThreadCount);
                fwrite(&color, 1, 1, file);
        }
        fpad(file, 0x20, (int)(0x1CF - pattern->thread_list->count));
        fpad(file, 0x00, 2);

        graphicsOffsetLocation = ftell(file);
        /* placeholder bytes to be overwritten */
        fpad(file, 0x00, 3);

        fwrite("\x31\xff\xf0", 1, 3, file);

        bounds = embp_bounds(pattern);

        height = (int)emb_round(bounds.h);
        width = (int)emb_round(bounds.w);
        unsigned short top =
            (unsigned short)(0x9000 | -(int)emb_round(bounds.x));
        unsigned short bottom =
            (unsigned short)(0x9000 | -(int)emb_round(bounds.y));
        /* write 2 byte x size */
        emb_write_i16(file, width);
        /* write 2 byte y size */
        emb_write_i16(file, height);

        /* Write 4 miscellaneous int16's */
        fwrite("\x01\xe0\x01\xb0", 1, 4, file);

        /* CHECK: is this really big endian? */
        emb_write_i16be(file, top);
        emb_write_i16be(file, bottom);

        pecEncode(file, pattern);
        graphicsOffsetValue = ftell(file) - graphicsOffsetLocation + 2;
        fseek(file, graphicsOffsetLocation, SEEK_SET);

        fputc((unsigned char)(graphicsOffsetValue & 0xFF), file);
        fputc((unsigned char)((graphicsOffsetValue >> 8) & 0xFF), file);
        fputc((unsigned char)((graphicsOffsetValue >> 16) & 0xFF), file);

        fseek(file, 0x00, SEEK_END);

        /* Writing all colors */
        memcpy(image, imageWithFrame, 48 * 38);

        yFactor = 32.0 / height;
        xFactor = 42.0 / width;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                int x = (int)emb_round((st.x - bounds.x) * xFactor) + 3;
                int y = (int)emb_round((st.y - bounds.y) * yFactor) + 3;
                if (x <= 0 || x > 48)
                        continue;
                if (y <= 0 || y > 38)
                        continue;
                image[y][x] = 1;
        }
        writeImage(file, image);

        /* Writing each individual color */
        j = 0;
        for (i = 0; i < pattern->thread_list->count; i++) {
                memcpy(image, imageWithFrame, 48 * 38);
                for (; j < pattern->stitch_list->count; j++) {
                        EmbStitch st = pattern->stitch_list->stitch[j];
                        int x = (int)emb_round((st.x - bounds.x) * xFactor) + 3;
                        int y = (int)emb_round((st.y - bounds.y) * yFactor) + 3;
                        if (x <= 0 || x > 48)
                                continue;
                        if (y <= 0 || y > 38)
                                continue;
                        if (st.flags & STOP) {
                                break;
                        }
                        image[y][x] = 1;
                }
                writeImage(file, image);
        }
}

char writePec(EmbPattern *pattern, const char *fileName, FILE *file)
{
        /* TODO: There needs to be a matching flipVertical() call after the write
           to ensure multiple writes from the same pattern work properly */
        embp_flipVertical(pattern);
        embp_fixColorCount(pattern);
        embp_correctForMaxStitchLength(pattern, 12.7, 204.7);
        embp_scale(pattern, 10.0);
        fwrite("#PEC0001", 1, 8, file);
        writePecStitches(pattern, file, fileName);
        return 1;
}

/*
 * Brother Embroidery Format (.pel)
 * The Brother pel format is stitch-only.
 */
char readPel(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: readPel is not implemented.");
        printf("%p, %p\n", pattern, file);
        return 0;               /*TODO: finish readPel */
}

char writePel(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writePel is not implemented.");
        printf("%p, %p\n", pattern, file);
        return 0;               /*TODO: finish writePel */
}

/*
 * Brother Embroidery Format (.pem)
 * The Brother pem format is stitch-only.
 */
char readPem(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: readPem is not implemented.");
        printf("%p, %p\n", pattern, file);
        return 0;               /*TODO: finish ReadPem */
}

char writePem(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writePem is not implemented.");
        printf("%p, %p\n", pattern, file);
        return 0;               /*TODO: finish writePem */
}

/*
 * Brother Embroidery Format (.pes)
 * The Brother pes format is stitch-only.
 */

const char *pes_version_strings[] = {
        "#PES0001",
        "#PES0020",
        "#PES0022",
        "#PES0030",
        "#PES0040",
        "#PES0050",
        "#PES0055",
        "#PES0056",
        "#PES0060",
        "#PES0070",
        "#PES0080",
        "#PES0090",
        "#PES0100",
};

/* ---------------------------------------------------------------- */
/* format pes */

int pes_version = PES0001;

char readPes(EmbPattern *pattern, const char *fileName, FILE *file)
{
        printf("%s", fileName);
        int pecstart, numColors, x, version, i;
        char signature[9];
        if (fread(signature, 1, 8, file) != 8) {
                puts("ERROR PES: failed to read signature.");
                return 0;
        }
        signature[8] = 0;
        pecstart = emb_read_i32(file);

        version = 0;
        for (i = 0; i < N_PES_VERSIONS; i++) {
                if (!strcmp(signature, pes_version_strings[i])) {
                        version = i;
                        break;
                }
        }

        if (version >= PES0040) {
                fseek(file, 0x10, SEEK_SET);
                if (!read_descriptions(file, pattern)) {
                        puts("ERROR PES: failed to read descriptions.");
                        return 0;
                }
        }

        switch (version) {
        case PES0100:
                readPESHeaderV10(file, pattern);
                break;
        case PES0090:
                readPESHeaderV9(file, pattern);
                break;
        case PES0080:
                readPESHeaderV8(file, pattern);
                break;
        case PES0070:
                readPESHeaderV7(file, pattern);
                break;
        case PES0060:
                readPESHeaderV6(file, pattern);
                break;
        case PES0056:
        case PES0055:
        case PES0050:
                readPESHeaderV5(file, pattern);
                break;
        default:
                break;
        }

        /* fseek(file, pecstart + 48, SEEK_SET);
         * This seems wrong based on the readPESHeader functions. */
        fseek(file, pecstart, SEEK_SET);

        numColors = fgetc(file) + 1;
        for (x = 0; x < numColors; x++) {
                int color_index = fgetc(file);
                if (color_index >= pecThreadCount) {
                        color_index = 0;
                }
                embp_addThread(pattern, pec_colors[color_index]);
        }

        fseek(file, pecstart + 528, SEEK_SET);
        readPecStitches(pattern, file);

        embp_flipVertical(pattern);

        return 1;
}

int read_descriptions(FILE *file, EmbPattern *pattern)
{
        size_t n;
        n = (size_t)fgetc(file);
        if (fread(pattern->design_name, 1, n, file) != n) {
                return 0;
        }
        n = (size_t)fgetc(file);
        if (fread(pattern->category, 1, n, file) != n) {
                return 0;
        }
        n = (size_t)fgetc(file);
        if (fread(pattern->author, 1, n, file) != n) {
                return 0;
        }
        n = (size_t)fgetc(file);
        if (fread(pattern->keywords, 1, n, file) != n) {
                return 0;
        }
        n = (size_t)fgetc(file);
        if (fread(pattern->comments, 1, n, file) != n) {
                return 0;
        }
        return 1;
}

void readPESHeaderV5(FILE *file, EmbPattern *pattern)
{
        int fromImageStringLength;
        fseek(file, 24, SEEK_CUR);
        fromImageStringLength = fgetc(file);
        fseek(file, fromImageStringLength, SEEK_CUR);
        fseek(file, 24, SEEK_CUR);
        readProgrammableFills(file, pattern);
        readMotifPatterns(file, pattern);
        readFeatherPatterns(file, pattern);
        readThreads(file, pattern);
}

void readPESHeaderV6(FILE *file, EmbPattern *pattern)
{
        fseek(file, 36, SEEK_CUR);
        readImageString(file, pattern);
        fseek(file, 24, SEEK_CUR);
        readProgrammableFills(file, pattern);
        readMotifPatterns(file, pattern);
        readFeatherPatterns(file, pattern);
        readThreads(file, pattern);
}

void readPESHeaderV7(FILE *file, EmbPattern *pattern)
{
        fseek(file, 36, SEEK_CUR);
        readImageString(file, pattern);
        fseek(file, 24, SEEK_CUR);
        readProgrammableFills(file, pattern);
        readMotifPatterns(file, pattern);
        readFeatherPatterns(file, pattern);
        readThreads(file, pattern);
}

void readPESHeaderV8(FILE *file, EmbPattern *pattern)
{
        fseek(file, 38, SEEK_CUR);
        readImageString(file, pattern);
        fseek(file, 26, SEEK_CUR);
        readProgrammableFills(file, pattern);
        readMotifPatterns(file, pattern);
        readFeatherPatterns(file, pattern);
        readThreads(file, pattern);
}

void readPESHeaderV9(FILE *file, EmbPattern *pattern)
{
        fseek(file, 14, SEEK_CUR);
        readHoopName(file, pattern);
        fseek(file, 30, SEEK_CUR);
        readImageString(file, pattern);
        fseek(file, 34, SEEK_CUR);
        readProgrammableFills(file, pattern);
        readMotifPatterns(file, pattern);
        readFeatherPatterns(file, pattern);
        readThreads(file, pattern);
}

void readPESHeaderV10(FILE *file, EmbPattern *pattern)
{
        fseek(file, 14, SEEK_CUR);
        readHoopName(file, pattern);
        fseek(file, 38, SEEK_CUR);
        readImageString(file, pattern);
        fseek(file, 34, SEEK_CUR);
        readProgrammableFills(file, pattern);
        readMotifPatterns(file, pattern);
        readFeatherPatterns(file, pattern);
        readThreads(file, pattern);
}

void readHoopName(FILE *file, EmbPattern *pattern)
{
        if (emb_verbose > 1) {
                printf("Called with: (%p, %p)", (void *)file, (void *)pattern);
        }
        /*
           int hoopNameStringLength = fgetc(file);
           EmbString hoopNameString = readString(hoopNameStringLength);
           if (hoopNameString.length() != 0) {
           pattern.setMetadata("hoop_name", hoopNameString);
           }
         */
}

void readImageString(FILE *file, EmbPattern *pattern)
{
        if (emb_verbose > 1) {
                printf("Called with: (%p, %p)", (void *)file, (void *)pattern);
        }
        /*
           int fromImageStringLength = fgetc(file);
           EmbString fromImageString = readString(fromImageStringLength);
           if (fromImageString.length() != 0) {
           pattern.setMetadata("image_file", fromImageString);
           }
         */
}

void readProgrammableFills(FILE *file, EmbPattern *pattern)
{
        int numberOfProgrammableFillPatterns;
        if (emb_verbose > 1) {
                printf("Called with: (%p, %p)", (void *)file, (void *)pattern);
        }
        numberOfProgrammableFillPatterns = emb_read_i16(file);
        if (numberOfProgrammableFillPatterns != 0) {
                return;
        }
}

void readMotifPatterns(FILE *file, EmbPattern *pattern)
{
        int numberOfMotifPatterns;
        if (emb_verbose > 1) {
                printf("Called with: (%p, %p)", (void *)file, (void *)pattern);
        }
        numberOfMotifPatterns = emb_read_i16(file);
        if (numberOfMotifPatterns != 0) {
                return;
        }
}

void readFeatherPatterns(FILE *file, EmbPattern *pattern)
{
        int featherPatternCount;
        if (emb_verbose > 1) {
                printf("Called with: (%p, %p)", (void *)file, (void *)pattern);
        }
        featherPatternCount = emb_read_i16(file);
        if (featherPatternCount != 0) {
                return;
        }
}

void readThreads(FILE *file, EmbPattern *pattern)
{
        int numberOfColors, i;
        if (emb_verbose > 1) {
                printf("Called with: (%p, %p)", (void *)file, (void *)pattern);
        }
        numberOfColors = emb_read_i16(file);
        for (i = 0; i < numberOfColors; i++) {
                EmbThread thread;
                int color_code_length;
                int descriptionStringLength;
                int brandStringLength;
                int threadChartStringLength;
                color_code_length = fgetc(file);
                /* strcpy(thread.color_code, readString(color_code_length)); */
                thread.color.r = fgetc(file);
                thread.color.g = fgetc(file);
                thread.color.b = fgetc(file);
                fseek(file, 5, SEEK_CUR);
                descriptionStringLength = fgetc(file);
                /* strcpy(thread.description, readString(descriptionStringLength)); */

                brandStringLength = fgetc(file);
                /* strcpy(thread.brand, readString(brandStringLength)); */

                threadChartStringLength = fgetc(file);
                /* strcpy(thread.threadChart, readString(threadChartStringLength)); */

                if (emb_verbose > 1) {
                        printf("color code length: %d\n", color_code_length);
                        printf("description string length: %d\n",
                               descriptionStringLength);
                        printf("brand string length: %d\n", brandStringLength);
                        printf("thread chart string length: %d\n",
                               threadChartStringLength);
                }
                embp_addThread(pattern, thread);
        }
}

void pesWriteSewSegSection(EmbPattern *pattern, FILE *file)
{
        /* TODO: pointer safety */
        short *colorInfo = 0;
        int flag = 0;
        int count = 0;
        int colorCode = -1;
        int stitchType = 0;
        int blockCount = 0;
        int colorCount = 0;
        int newColorCode = 0;
        int colorInfoIndex = 0;
        int i, j;
        EmbRect bounds = embp_bounds(pattern);

        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbColor color;
                EmbStitch st = pattern->stitch_list->stitch[i];
                flag = st.flags;
                if (st.color < pattern->thread_list->count) {
                        color = pattern->thread_list->thread[st.color].color;
                } else {
                        color = pec_colors[0].color;
                }
                newColorCode =
                    emb_find_nearest_thread(color, (EmbThread *) pec_colors,
                                            pecThreadCount);
                if (newColorCode != colorCode) {
                        colorCount++;
                        colorCode = newColorCode;
                }
                while (i < pattern->stitch_list->count && (flag == st.flags)) {
                        st = pattern->stitch_list->stitch[i];
                        count++;
                        i++;
                }
                blockCount++;
        }

        emb_write_i16(file, (int16_t) blockCount);      /* block count */
        emb_write_u16(file, 0xFFFF);
        emb_write_i16(file, 0x00);

        emb_write_i16(file, 0x07);      /* string length */
        fwrite("CSewSeg", 1, 7, file);

        if (colorCount > 1000) {
                puts("Color count exceeds 1000 this is likely an error. Truncating to 1000.");
                colorCount = 1000;
        }

        colorInfo = (short *)calloc(colorCount * 2, sizeof(int16_t));
        colorCode = -1;
        blockCount = 0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbColor color;
                EmbStitch st;
                st = pattern->stitch_list->stitch[i];
                j = i;
                flag = st.flags;
                color = pattern->thread_list->thread[st.color].color;
                newColorCode =
                    emb_find_nearest_thread(color, (EmbThread *) pec_colors,
                                            pecThreadCount);
                if (newColorCode != colorCode) {
                        if (colorInfoIndex + 2 > colorCount * 2) {
                                puts("Ran out of memory for color info.");
                                break;
                        }
                        colorInfo[colorInfoIndex++] = (int16_t) blockCount;
                        colorInfo[colorInfoIndex++] = (int16_t) newColorCode;
                        colorCode = newColorCode;
                }
                count = 0;
                while (j < pattern->stitch_list->count && (flag == st.flags)) {
                        st = pattern->stitch_list->stitch[j];
                        count++;
                        j++;
                }
                if (flag & JUMP) {
                        stitchType = 1;
                } else {
                        stitchType = 0;
                }

                emb_write_i16(file, (int16_t) stitchType);      /* 1 for jump, 0 for normal */
                emb_write_i16(file, (int16_t) colorCode);       /* color code */
                emb_write_i16(file, (int16_t) count);   /* stitches in block */
                for (j = i; j < pattern->stitch_list->count; ++j) {
                        st = pattern->stitch_list->stitch[j];
                        if (st.flags != flag) {
                                break;
                        }
                        emb_write_i16(file, (int16_t) (st.x - bounds.x));
                        emb_write_i16(file, (int16_t) (st.y + bounds.y));
                }
                if (j < pattern->stitch_list->count) {
                        emb_write_u16(file, 0x8003);
                }
                blockCount++;
                i = j;
        }
        emb_write_i16(file, (int16_t) colorCount);
        for (i = 0; i < colorCount; i++) {
                emb_write_i16(file, colorInfo[i * 2]);
                emb_write_i16(file, colorInfo[i * 2 + 1]);
        }
        emb_write_i32(file, 0);
        safe_free(colorInfo);
}

void pesWriteEmbOneSection(EmbPattern *pattern, FILE *file)
{
        /* TODO: pointer safety */
        //float x, width, height;
        int hoopHeight = 1800, hoopWidth = 1300;
        EmbRect bounds;
        emb_write_i16(file, 0x07);      /* string length */
        fwrite("CEmbOne", 1, 7, file);
        bounds = embp_bounds(pattern);

        fpad(file, 0, 16);

        /* AffineTransform */
        emb_write_i32(file, 1.0);
        emb_write_i32(file, 0.0);
        emb_write_i32(file, 0.0);
        emb_write_i32(file, 1.0);
        emb_write_i32(file, (float)((bounds.w - hoopWidth) / 2));
        emb_write_i32(file, (float)((bounds.h + hoopHeight) / 2));

        emb_write_i16(file, 1);
        emb_write_i16(file, 0); /* Translate X */
        emb_write_i16(file, 0); /* Translate Y */
        emb_write_i16(file, (int16_t) bounds.w);
        emb_write_i16(file, (int16_t) bounds.h);

        fpad(file, 0, 8);
        /*WriteSubObjects(br, pes, SubBlocks); */
}

char writePes(EmbPattern *pattern, const char *fileName, FILE *file)
{
        int pecLocation;
        embp_flipVertical(pattern);
        embp_scale(pattern, 10.0);
        fwrite("#PES0001", 1, 8, file);
        /* WRITE PECPointer 32 bit int */
        emb_write_i32(file, 0x00);

        emb_write_i16(file, 0x01);
        emb_write_i16(file, 0x01);

        /* Write object count */
        emb_write_i16(file, 0x01);
        emb_write_u16(file, 0xFFFF);    /* command */
        emb_write_i16(file, 0x00);      /* unknown */

        pesWriteEmbOneSection(pattern, file);
        pesWriteSewSegSection(pattern, file);

        pecLocation = ftell(file);
        fseek(file, 0x08, SEEK_SET);
        fputc((unsigned char)(pecLocation & 0xFF), file);
        fputc((unsigned char)(pecLocation >> 8) & 0xFF, file);
        fputc((unsigned char)(pecLocation >> 16) & 0xFF, file);
        fseek(file, 0x00, SEEK_END);
        writePecStitches(pattern, file, fileName);
        return 1;
}

char readPhb(EmbPattern *pattern, FILE *file)
{
        unsigned int fileOffset;
        short colorCount;
        int i;

        fseek(file, 0x71, SEEK_SET);
        colorCount = emb_read_i16(file);

        for (i = 0; i < colorCount; i++) {
                EmbThread t = pec_colors[fgetc(file)];
                embp_addThread(pattern, t);
        }

        /* TODO: check that file begins with #PHB */
        fseek(file, 0x54, SEEK_SET);
        fileOffset = 0x52;
        fileOffset += emb_read_i32(file);

        fseek(file, fileOffset, SEEK_SET);
        fileOffset += emb_read_i32(file) + 2;

        fseek(file, fileOffset, SEEK_SET);
        fileOffset += emb_read_i32(file);

        fseek(file, fileOffset + 14, SEEK_SET); /* 28 */

        colorCount = (int16_t) (char)fgetc(file);
        for (i = 0; i < colorCount; i++) {
                char stor;
                stor = (char)fgetc(file);
                if (emb_verbose > 1) {
                        printf("stor: %d\n", stor);
                }
        }
        fseek(file, 4, SEEK_CUR);       /* bytes to end of file */
        fseek(file, 17, SEEK_CUR);

        readPecStitches(pattern, file);

        embp_flipVertical(pattern);
        return 1;               /*TODO: finish ReadPhb */
}

char writePhb(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writePhb is not implemented.");
        if (emb_verbose > 1) {
                printf("Called with %p %p\n", (void *)pattern, (void *)file);
        }
        return 0;               /*TODO: finish writePhb */
}

/*
 * Brother Embroidery Format (.phc)
 * The Brother phc format is stitch-only.
 */

char readPhc(EmbPattern *pattern, FILE *file)
{
        int colorChanges, version, bytesInSection2;
        unsigned int fileLength;
        unsigned short pecOffset, bytesInSection, bytesInSection3;
        char pecAdd;
        int i;

        fseek(file, 0x07, SEEK_SET);
        version = (char)fgetc(file) - 0x30;     /* converting from ansi number */
        fseek(file, 0x4D, SEEK_SET);
        LOAD_U16(file, colorChanges)
            for (i = 0; i < colorChanges; i++) {
                EmbThread t = pec_colors[(int)(char)fgetc(file)];
                embp_addThread(pattern, t);
        }
        fseek(file, 0x2B, SEEK_SET);
        pecAdd = (char)fgetc(file);
        LOAD_I32(file, fileLength)
            LOAD_U16(file, pecOffset)
            fseek(file, pecOffset + pecAdd, SEEK_SET);
        LOAD_U16(file, bytesInSection)
            fseek(file, bytesInSection, SEEK_CUR);
        bytesInSection2 = emb_read_i32(file);
        fseek(file, bytesInSection2, SEEK_CUR);
        LOAD_U16(file, bytesInSection3)
            fseek(file, bytesInSection3 + 0x12, SEEK_CUR);

        if (emb_verbose > 1) {
                printf("version: %d\n", version);
        }

        readPecStitches(pattern, file);

        embp_flipVertical(pattern);
        return 1;               /*TODO: finish ReadPhc */
}

char writePhc(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writePhc is not implemented.");
        if (emb_verbose > 1) {
                printf("Called with %p %p\n", (void *)pattern, (void *)file);
        }
        return 0;               /*TODO: finish writePhc */
}
