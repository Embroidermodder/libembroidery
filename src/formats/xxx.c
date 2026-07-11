/*
 * Singer Embroidery Format (.xxx)
 * The Singer xxx format is stitch-only.
 */

#include <string.h>
#include <math.h>

#include "embroidery.h"

int8_t xxxDecodeByte(uint8_t inputByte)
{
    if (inputByte >= 0x80) {
        return (char)((-~inputByte) - 1);
    }
    return ((char)inputByte);
}

int8_t readXxx(EmbPattern *pattern, FILE *file)
{
    int dx = 0, dy = 0, numberOfColors, paletteOffset, i;
    int8_t thisStitchJump = 0;

    if (emb_verbose > 1) {
        puts("readXxx has been overridden.");
        return 0;
    }

    fseek(file, 0x27, SEEK_SET);
    numberOfColors = emb_read_i16(file);
    fseek(file, 0xFC, SEEK_SET);
    paletteOffset = emb_read_i32(file);
    fseek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        strcpy(thread.catalogNumber, "NULL");
        strcpy(thread.description, "NULL");
        fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(thread.color), 3);
        emb_add_thread(pattern, thread);
    }
    fseek(file, 0x100, SEEK_SET);

    for (i = 0; !feof(file) && ftell(file) < paletteOffset; i++) {
        uint8_t b0, b1;
        int flags;
        flags = NORMAL;
        if (thisStitchJump)
            flags = TRIM;
        thisStitchJump = 0;
        b0 = (char)fgetc(file);
        b1 = (char)fgetc(file);
        /* TODO: ARE THERE OTHER BIG JUMP CODES? */
        if (b0 == 0x7E || b0 == 0x7D) {
            dx = b1 + ((char)fgetc(file) << 8);
            dx = ((int16_t) dx);
            dy = emb_read_i16(file);
            flags = TRIM;
        } else if (b0 == 0x7F) {
            /* TODO: LOOKS LIKE THESE CODES ARE IN THE HEADER */
            if (b1 != 0x17 && b1 != 0x46 && b1 >= 8) {
                b0 = 0;
                b1 = 0;
                thisStitchJump = 1;
                flags = STOP;
            } else if (b1 == 1) {
                flags = TRIM;
                b0 = (char)fgetc(file);
                b1 = (char)fgetc(file);
            } else {
                continue;
            }
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        } else {
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        }
        emb_add_stitch(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    /* TODO: check end of pattern for multiple STOPs */
    return 1;
}

void xxxEncodeStop(FILE *file, EmbStitch s)
{
    fputc((uint8_t) 0x7F, file);
    fputc((uint8_t) (s.color + 8), file);
}

void xxxEncodeStitch(FILE *file, EmbReal deltaX, EmbReal deltaY, int flags)
{
    if ((flags & (JUMP | TRIM))
        && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        fputc(0x7E, file);
        /* Does this cast work right? */
        emb_write_i16(file, (int16_t) deltaX);
        emb_write_i16(file, (int16_t) deltaY);
    } else {
        /* TODO: Verify this works after changing this to uint8_t */
        fputc((uint8_t) emb_round(deltaX), file);
        fputc((uint8_t) emb_round(deltaY), file);
    }
}

void xxxEncodeDesign(FILE *file, EmbPattern *p)
{
    int i;
    EmbReal thisX = 0.0f;
    EmbReal thisY = 0.0f;

    if (p->stitch_list->count > 0) {
        thisX = (float)p->stitch_list->stitch[0].x;
        thisY = (float)p->stitch_list->stitch[0].y;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
        EmbStitch s = p->stitch_list->stitch[i];
        EmbReal deltaX, deltaY;
        EmbReal previousX = thisX;
        EmbReal previousY = thisY;
        thisX = s.x;
        thisY = s.y;
        deltaX = thisX - previousX;
        deltaY = thisY - previousY;
        if (s.flags & STOP) {
            xxxEncodeStop(file, s);
        } else if (s.flags & END) {
        } else {
            xxxEncodeStitch(file, deltaX * 10.0f, deltaY * 10.0f, s.flags);
        }
    }
}

int8_t writeXxx(EmbPattern *pattern, FILE *file)
{
    int i;
    EmbRect rect;
    int endOfStitches;
    EmbReal width, height;
    //short to_write;
    //uint32_t n_stitches;
    //uint16_t n_threads;

    emb_correctForMaxStitchLength(pattern, 124, 127);

    fpad(file, 0, 0x17);
    emb_write_i32(file, (uint32_t) pattern->stitch_list->count);

    fpad(file, 0, 0x0C);
    emb_write_i16(file, (uint16_t) pattern->thread_list->count);

    fpad(file, 0, 0x02);

    rect = emb_bounds(pattern);
    width = rect.w;
    height = rect.h;
    emb_write_i16(file, (int16_t) (width * 10.0));
    emb_write_i16(file, (int16_t) (height * 10.0));

    /* TODO: xEnd from start point x=0 */
    emb_write_i16(file, (int16_t) (width / 2.0 * 10));
    /* TODO: yEnd from start point y=0 */
    emb_write_i16(file, (int16_t) (height / 2.0 * 10));
    /* TODO: left from start x = 0 */
    emb_write_i16(file, (int16_t) (width / 2.0 * 10));
    /* TODO: bottom from start y = 0 */
    emb_write_i16(file, (int16_t) (height / 2.0 * 10));

    fpad(file, 0, 0xC5);

    /* place holder for end of stitches */
    emb_write_i32(file, 0x0000);
    xxxEncodeDesign(file, pattern);
    endOfStitches = ftell(file);
    fseek(file, 0xFC, SEEK_SET);
    emb_write_u32(file, endOfStitches);
    fseek(file, 0, SEEK_END);
    /* is this really correct? */
    fwrite("\x7F\x7F\x03\x14\x00\x00", 1, 6, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        fputc(0x00, file);
        embColor_write(file, c, 3);
    }
    for (i = 0; i < (22 - pattern->thread_list->count); i++) {
        emb_write_u32(file, 0x01000000);
    }
    fwrite("\x00\x01", 1, 2, file);
    return 1;
}
