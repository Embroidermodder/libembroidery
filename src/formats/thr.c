/*
 * ThredWorks Embroidery Format (.thr)
 * The ThreadWorks thr format is stitch-only.
 *
 * bit definitions for attributes of stitch
 * 0-3     stitch color
 * 4-14    form pointer
 * 15-18   spares
 * 19      not a form stitch
 * 20      center walk stitch
 * 21      edge walk stitch
 * 22      underlay stitch
 * 23      knot stitch
 * 24      feather stitch
 * 25-27   layer
 * 28      spare
 * 29-30   stitch type
 *             00=not a form stitch,
 *             01=form fill,
 *             10=form border fill,
 *             11=applique stitches
 * 31      set for user edited stitches
 */

#include <string.h>

#include "embroidery.h"

int8_t readThr(EmbPattern *pattern, FILE *file)
{
    ThredHeader header;
    EmbColor background;
    int currentColor;
    int i;

    header.sigVersion = emb_read_i32(file);
    header.length = emb_read_i32(file);
    header.numStiches = emb_read_i16(file);
    header.hoopSize = emb_read_u16(file);
    for (i = 0; i < 7; i++) {
        header.reserved[i] = emb_read_u16(file);
        printf("header.reserved[%d] = %d\n", i, header.reserved[i]);
    }

    if ((header.sigVersion & 0xffffff) == 0x746872) {
        uint32_t verVar = (header.sigVersion & 0xff000000) >> 24;
        switch (verVar) {
        case 0:
            break;
        case 1:
        case 2:
            /* skip the file header extension */
            fseek(file, 144, SEEK_CUR);
            break;
        default:
            return 0;           /* unsupported version */
        }
    }
    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x, y;
        uint32_t color;
        x = emb_read_i32(file);
        y = emb_read_i32(file);
        color = emb_read_i32(file);
        x /= 10.0;
        y /= 10.0;

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            emb_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        emb_add_stitch_abs(pattern, x, y, type, 0);
    }
    fseek(file, 16, SEEK_CUR);  /* skip bitmap name (16 chars) */

    embColor_read(file, &background, 4);
    if (emb_verbose > 1) {
        printf("background: %c %c %c\n", background.r, background.g,
               background.b);
    }
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        strcpy(thread.description, "NULL");
        strcpy(thread.catalogNumber, "NULL");
        embColor_read(file, &(thread.color), 4);
        emb_add_thread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */
    return 1;
}

int8_t writeThr(EmbPattern *pattern, FILE *file)
{
    int i, stitchCount;
    uint8_t version = 0;
    ThredHeader header;
    ThredExtension extension;
    int8_t bitmapName[16];

    stitchCount = pattern->stitch_list->count;

    memset(&header, 0, sizeof(ThredHeader));
    header.sigVersion = 0x746872 | (version << 24);
    header.length = stitchCount * 12 + 16;
    if (version == 1 || version == 2) {
        header.length = header.length + sizeof(ThredHeader);
    }
    header.numStiches = (uint16_t) stitchCount; /* number of stitches in design */
    header.hoopSize = 5;

    emb_write_u32(file, header.sigVersion);
    emb_write_u32(file, header.length);
    emb_write_u16(file, header.numStiches);
    emb_write_u16(file, header.hoopSize);
    for (i = 0; i < 7; i++) {
        emb_write_u16(file, header.reserved[i]);
    }

    if (version == 1 || version == 2) {
        memset(&extension, 0, sizeof(ThredExtension));
        extension.auxFormat = 1;
        extension.hoopX = 640;
        extension.hoopY = 640;

        emb_write_i32(file, extension.hoopX);
        emb_write_i32(file, extension.hoopY);
        emb_write_i32(file, extension.stitchGranularity);
        fwrite(extension.creatorName, 1, 50, file);
        fwrite(extension.modifierName, 1, 50, file);
        fputc(extension.auxFormat, file);
        fwrite(extension.reserved, 1, 31, file);
    }

    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        uint32_t NOTFRM = 0x00080000;
        EmbStitch st = pattern->stitch_list->stitch[i];
        float x, y;
        x = (float)(st.x * 10.0);
        y = (float)(st.y * 10.0);
        emb_write_i32(file, x);
        emb_write_i32(file, y);
        emb_write_u32(file, NOTFRM | (st.color & 0x0F));
    }
    fwrite(bitmapName, 1, 16, file);
    /* background color */
    fwrite("\xFF\xFF\xFF\x00", 1, 4, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        embColor_write(file, c, 4);
        if (i >= 16)
            break;
    }

    /* write remaining colors if not yet 16 */
    fpad(file, 0, 4 * (16 - i));

    fpad(file, '4', 16);
    return 1;
}
