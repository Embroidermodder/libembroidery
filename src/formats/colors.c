/**
 * @file colors.c
 *
 * The Embroidery Thread Color Formats (.col, .inf)
 *
 * An external color file format for formats that do not record
 * their own colors.
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

/* col format
 *
 * It is a human-readable format that has a header that is
 * a single line containing only the number of threads in decimal
 * followed by the windows line break "\r\n".
 *
 * Then the rest of the file is a comma seperated value list of
 * all threads with 4 values per line: the index of the thread
 * then the red, green and blue channels of the color in that order.
 *
 * ## Example
 *
 * If we had a pattern called "example" with four colors:
 * black, red, magenta and cyan in that order then the file is
 * (with the white space written out):
 *
 *    example.col
 *
 *    4\r\n
 *    0,0,0,0\r\n
 *    1,255,0,0\r\n
 *    2,0,255,0\r\n
 *    3,0,0,255\r\n
 */
int8_t readCol(EmbPattern *pattern, FILE *file)
{
        int numberOfColors, i;
        int num, blue, green, red;
        EmbThread t;
        int8_t line[30];

        pattern->thread_list->count = 0;

        emb_readline(file, line, 30);
        numberOfColors = atoi(line);
        if (numberOfColors < 1) {
                printf("ERROR: Number of colors is zero.");
                return 0;
        }
        for (i = 0; i < numberOfColors; i++) {
                emb_readline(file, line, 30);
                if (line[0] == 0) {
                        printf("ERROR: Empty line in col file.");
                        return 0;
                }
                /* TODO: replace all scanf code */
                if (sscanf(line, "%d,%d,%d,%d", &num, &blue, &green, &red) != 4) {
                        break;
                }
                t.color.r = (uint8_t)red;
                t.color.g = (uint8_t)green;
                t.color.b = (uint8_t)blue;
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                embp_addThread(pattern, t);
        }
        return 1;
}

int8_t writeCol(EmbPattern *pattern, FILE *file)
{
        int i;

        fprintf(file, "%d\r\n", pattern->thread_list->count);
        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor c;
                c = pattern->thread_list->thread[i].color;
                fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g,
                        (int)c.b);
        }
        return 1;
}

int8_t readInf(EmbPattern *pattern, FILE *file)
{
        int nColors, i;
        int8_t colorType[50];
        int8_t colorDescription[50];
        EmbThread t;

        fseek(file, 12, SEEK_CUR);
        nColors = emb_read_i32be(file);

        pattern->thread_list->count = 0;

        for (i = 0; i < nColors; i++) {
                fseek(file, 4, SEEK_CUR);
                embColor_read(file, &(t.color), 3);
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                embp_addThread(pattern, t);
                fseek(file, 2, SEEK_CUR);
                binaryReadString(file, colorType, 50);
                binaryReadString(file, colorDescription, 50);
        }
        return 1;
}

int8_t writeInf(EmbPattern *pattern, FILE *file)
{
        int i, bytesRemaining;

        emb_write_u32be(file, 0x01);
        emb_write_u32be(file, 0x08);
        /* write place holder offset */
        emb_write_u32be(file, 0x00);
        emb_write_u32be(file, pattern->thread_list->count);

        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbString buffer;
                uint16_t record_length, record_number, needle_number;
                EmbColor c;
                c = pattern->thread_list->thread[i].color;
                sprintf(buffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
                record_length = 14 + strlen(buffer);
                record_number = i;
                needle_number = i;
                emb_write_i16be(file, record_length);
                emb_write_i16be(file, record_number);
                embColor_write(file, c, 3);
                emb_write_i16be(file, needle_number);
                fwrite("RGB\0", 1, 4, file);
                fprintf(file, "%s", buffer);
                fwrite("\0", 1, 1, file);
        }
        /* It appears that there should be a pad here otherwise it clips into
         * the color description. */
        fpad(file, 0, 8);
        fseek(file, -8, SEEK_END);
        bytesRemaining = ftell(file);
        fseek(file, 8, SEEK_SET);
        emb_write_u32be(file, bytesRemaining);
        return 1;
}
