/*
 * Pfaff Embroidery Format (.pcq)
 *
 * The Pfaff pcq format is stitch-only.
 */

#include <string.h>

#include "embroidery.h"

int8_t readPcq(EmbPattern *pattern, const int8_t *fileName, FILE *file)
{
    int8_t allZeroColor = 1;
    int i = 0;
    uint8_t b[9];
    EmbReal dx = 0, dy = 0;
    int flags = 0, st = 0;
    uint8_t version, hoopSize;
    uint16_t colorCount;

    version = (char)fgetc(file);
    hoopSize = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    colorCount = emb_read_u16(file);
    if (emb_verbose > 1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        emb_add_thread(pattern, t);
    }
    if (allZeroColor) {
        emb_loadExternalColorFile(pattern, fileName);
    }
    st = emb_read_u16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }

        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        emb_add_stitch_abs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

int8_t writePcq(EmbPattern *pattern, FILE *file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    emb_write_u16(file, (uint16_t) pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    fpad(file, 0, (16 - i) * 4);

    emb_write_u16(file, (uint16_t) pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0),
                    (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}

