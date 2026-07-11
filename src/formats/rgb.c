/*
 * RGB Color File (.rgb)
 * The RGB format is a color-only format to act as an external color file for other formats.
 */

#include <string.h>

#include "embroidery.h"

int8_t readRgb(EmbPattern *pattern, FILE *file)
{
    int i, numberOfColors;

    fseek(file, 0x00, SEEK_END);
    numberOfColors = ftell(file) / 4;

    pattern->thread_list->count = 0;

    printf("numberOfColors: %d\n", numberOfColors);

    fseek(file, 0x00, SEEK_SET);
    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        emb_add_thread(pattern, t);
    }
    return 1;
}

int8_t writeRgb(EmbPattern *pattern, FILE *file)
{
    int i;
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        embColor_write(file, c, 4);
    }
    return 1;
}

