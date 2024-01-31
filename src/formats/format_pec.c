/*
 * PES FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
\subsection Brother Embroidery Format (.pec)
\addindex pec
\addindex Brother

The Brother pec format is stitch-only.

 */

void
readPecStitches(EmbPattern* pattern, FILE* file)
{
    FILE *f = file;
    unsigned char b[2];

    while (fread(b, 1, 2, f)==2) {
        int val1 = (int)b[0];
        int val2 = (int)b[1];

        int stitchType = NORMAL;
        if (b[0] == 0xFF && b[1] == 0x00) {
            embPattern_end(pattern);
            return;
        }
        if (b[0] == 0xFE && b[1] == 0xB0) {
            (void)fgetc(f);
            embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
            continue;
        }
        /* High bit set means 12-bit offset, otherwise 7-bit signed delta */
        if (val1 & 0x80) {
            if (val1 & 0x20) stitchType = TRIM;
            if (val1 & 0x10) stitchType = JUMP;
            val1 = ((val1 & 0x0F) << 8) + val2;

            /* Signed 12-bit arithmetic */
            if (val1 & 0x800) {
                val1 -= 0x1000;
            }
        }
        else if (val1 >= 0x40) {
            val1 -= 0x80;
        }
        if (val2 & 0x80) {
            if (val2 & 0x20) stitchType = TRIM;
            if (val2 & 0x10) stitchType = JUMP;
            val2 = ((val2 & 0x0F) << 8) + fgetc(file);

            /* Signed 12-bit arithmetic */
            if (val2 & 0x800) {
                val2 -= 0x1000;
            }
        }
        else if (val2 >= 0x40) {
            val2 -= 0x80;
        }

        embPattern_addStitchRel(pattern, val1 / 10.0,
                val2 / 10.0, stitchType, 1);
    }
}

void
pecEncodeJump(FILE* file, int x, int types)
{
    int outputVal = abs(x) & 0x7FF;
    unsigned int orPart = 0x80;
    unsigned char toWrite;

    if (!file) {
        printf("ERROR: format-pec.c pecEncodeJump(), file argument is null\n");
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

void
pecEncodeStop(FILE* file, unsigned char val)
{
    if (!file) {
        printf("ERROR: format-pec.c pecEncodeStop(), file argument is null\n");
        return;
    }
    fwrite("\xFE\xB0", 1, 2, file);
    fwrite(&val, 1, 1, file);
}

char
readPec(EmbPattern* pattern, const char *fileName, FILE* file)
{
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;

    if (emb_verbose>1) {
        printf("fileName: %s\n", fileName);
    }

    if (!check_header_present(file, 0x20A)) {
        return 0;
    }

    fseek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)(char)fgetc(file);
    for (i = 0; i <= colorChanges; i++) {
        embPattern_addThread(pattern, pecThreads[(char)fgetc(file) % 65]);
    }

    /* Get Graphics offset */
    fseek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(fgetc(file));
    graphicsOffset |= (fgetc(file) << 8);
    graphicsOffset |= (fgetc(file) << 16);

    (void)(char)fgetc(file); /* 0x31 */
    (void)(char)fgetc(file); /* 0xFF */
    (void)(char)fgetc(file); /* 0xF0 */
    /* Get X and Y size in .1 mm */
    /* 0x210 */
    fread_int16(file); /* x size */
    fread_int16(file); /* y size */

    fread_int16(file); /* 0x01E0 */
    fread_int16(file); /* 0x01B0 */
    fread_int16(file); /* distance left from start */
    fread_int16(file); /* distance up from start */

    /* Begin Stitch Data */
    /* 0x21C */
    /*unsigned int end = graphicsOffset + 0x208; */
    readPecStitches(pattern, file);
    embPattern_flipVertical(pattern);
    return 1;
}

void
pecEncode(FILE* file, EmbPattern* p)
{
    EmbReal thisX = 0.0;
    EmbReal thisY = 0.0;
    unsigned char stopCode = 2;
    int i;

    if (!file) {
        printf("ERROR: format-pec.c pecEncode(), file argument is null\n");
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
        thisX += (EmbReal)deltaX;
        thisY += (EmbReal)deltaY;

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
        } else if (deltaX < 63 && deltaX > -64 && deltaY < 63 && deltaY > -64 && (!(s.flags & (JUMP | TRIM)))) {
            unsigned char out[2];
            if (deltaX < 0) {
                out[0] = (unsigned char)(deltaX + 0x80);
            }
            else {
                out[0] = (unsigned char)deltaX;
            }
            if (deltaY < 0) {
                out[1] = (unsigned char)(deltaY + 0x80);
            }
            else {
                out[1] = (unsigned char)deltaY;
            }
            fwrite(out, 1, 2, file);
        }
        else {
            pecEncodeJump(file, deltaX, s.flags);
            pecEncodeJump(file, deltaY, s.flags);
        }
    }
}

void writeImage(FILE* file, unsigned char image[][48]);

void
writePecStitches(EmbPattern* pattern, FILE* file, const char *fileName)
{
    EmbRect bounds;
    unsigned char image[38][48], toWrite;
    int i, j, flen, graphicsOffsetLocation;
    int graphicsOffsetValue, height, width;
    EmbReal xFactor, yFactor;
    const char* forwardSlashPos = strrchr(fileName, '/');
    const char* backSlashPos = strrchr(fileName, '\\');
    const char* dotPos = strrchr(fileName, '.');
    const char* start = 0;

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
    fpad(file, 0x20, 16-flen);
    fwrite("\x0D", 1, 1, file);
    fpad(file, 0x20, 12);
    fwrite("\xff\x00\x06\x26", 1, 4, file);

    fpad(file, 0x20, 12);
    toWrite = (unsigned char)(pattern->thread_list->count-1);
    fwrite(&toWrite, 1, 1, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor thr = pattern->thread_list->thread[i].color;
        unsigned char color = (unsigned char)
            embThread_findNearestThread(thr,
            (EmbThread*)pecThreads, pecThreadCount);
        fwrite(&color, 1, 1, file);
    }
    fpad(file, 0x20, (int)(0x1CF - pattern->thread_list->count));
    fpad(file, 0x00, 2);

    graphicsOffsetLocation = ftell(file);
    /* placeholder bytes to be overwritten */
    fpad(file, 0x00, 3);

    fwrite("\x31\xff\xf0", 1, 3, file);

    bounds = embPattern_calcBoundingBox(pattern);

    height = (int)emb_round(bounds.bottom - bounds.top);
    width = (int)emb_round(bounds.right - bounds.left);
    /* write 2 byte x size */
    binaryWriteShort(file, (short)width);
    /* write 2 byte y size */
    binaryWriteShort(file, (short)height);

    /* Write 4 miscellaneous int16's */
    fwrite("\x01\xe0\x01\xb0", 1, 4, file);

    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -(int)emb_round(bounds.left)));
    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -(int)emb_round(bounds.top)));

    pecEncode(file, pattern);
    graphicsOffsetValue = ftell(file) - graphicsOffsetLocation + 2;
    fseek(file, graphicsOffsetLocation, SEEK_SET);

    fputc((unsigned char)(graphicsOffsetValue & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 8) & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 16) & 0xFF), file);

    fseek(file, 0x00, SEEK_END);

    /* Writing all colors */
    memcpy(image, imageWithFrame, 48*38);

    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        int x = (int)emb_round((st.x - bounds.left) * xFactor) + 3;
        int y = (int)emb_round((st.y - bounds.top) * yFactor) + 3;
        if (x<=0 || x>48) continue;
        if (y<=0 || y>38) continue;
        image[y][x] = 1;
    }
    writeImage(file, image);

    /* Writing each individual color */
    j = 0;
    for (i = 0; i < pattern->thread_list->count; i++) {
        memcpy(image, imageWithFrame, 48*38);
        for (; j < pattern->stitch_list->count; j++) {
            EmbStitch st = pattern->stitch_list->stitch[j];
            int x = (int)emb_round((st.x - bounds.left) * xFactor) + 3;
            int y = (int)emb_round((st.y - bounds.top) * yFactor) + 3;
            if (x<=0 || x>48) continue;
            if (y<=0 || y>38) continue;
            if (st.flags & STOP) {
                break;
            }
            image[y][x] = 1;
        }
        writeImage(file, image);
    }
}

char
writePec(EmbPattern* pattern, const char* fileName, FILE* file)
{
    /* TODO: There needs to be a matching flipVertical() call after the write
        to ensure multiple writes from the same pattern work properly */
    embPattern_flipVertical(pattern);
    embPattern_fixColorCount(pattern);
    embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    embPattern_scale(pattern, 10.0);
    fwrite("#PEC0001", 1, 8, file);
    writePecStitches(pattern, file, fileName);
    return 1;
}

