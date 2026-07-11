/*
 * Data Stitch Embroidery Format (.stx)
 * The Data Stitch stx format is stitch-only.
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

int stxReadThread(StxThread *thread, FILE *file)
{
    int j, colorNameLength, sectionNameLength;
    int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors;       /* TODO: determine what these represent */
    int codeLength = 0;
    int8_t *codeBuff = 0;
    int8_t *codeNameBuff = 0;
    EmbColor col;
    int8_t *sectionNameBuff = 0;

    if (!thread) {
        printf
            ("ERROR: format-stx.c stxReadThread(), thread argument is null\n");
        return 0;
    }
    if (!file) {
        printf("ERROR: format-stx.c stxReadThread(), file argument is null\n");
        return 0;
    }

    codeLength = fgetc(file);
    codeBuff = (char *)malloc(codeLength);
    if (!codeBuff) {
        printf
            ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeBuff\n");
        return 0;
    }
    /* TODO: check return value */
    fread(codeBuff, 1, codeLength, file);
    thread->colorCode = codeBuff;
    colorNameLength = fgetc(file);
    codeNameBuff = (char *)malloc(colorNameLength);
    if (!codeNameBuff) {
        printf
            ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeNameBuff\n");
        return 0;
    }
    fread((uint8_t *) codeNameBuff, 1, colorNameLength, file);  /* TODO: check return value */
    thread->colorName = codeNameBuff;

    embColor_read(file, &col, 4);
    if (emb_verbose > 1) {
        printf("col red: %d\n", col.r);
        printf("col green: %d\n", col.g);
        printf("col blue: %d\n", col.b);
    }

    sectionNameLength = fgetc(file);
    sectionNameBuff = (char *)malloc(sectionNameLength);
    if (!sectionNameBuff) {
        printf
            ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
        return 0;
    }
    fread((uint8_t *) sectionNameBuff, 1, sectionNameLength, file);     /* TODO: check return value */
    thread->sectionName = sectionNameBuff;

    somethingSomething = emb_read_i32(file);
    somethingSomething2 = emb_read_i32(file);
    somethingElse = emb_read_i32(file);
    numberOfOtherDescriptors = emb_read_i16(file);
    thread->subDescriptors =
        (SubDescriptor *) malloc(sizeof(SubDescriptor) *
                                 numberOfOtherDescriptors);
    if (!thread->subDescriptors) {
        printf
            ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors\n");
        return 0;
    }
    for (j = 0; j < numberOfOtherDescriptors; j++) {
        SubDescriptor sd;
        int8_t *subCodeBuff, *subColorNameBuff;
        int subCodeLength, subColorNameLength;

        sd.someNum = emb_read_i16(file);
        /* Debug.Assert(sd.someNum == 1); TODO: review */
        sd.someInt = emb_read_i32(file);
        subCodeLength = fgetc(file);
        subCodeBuff = (char *)malloc(subCodeLength);
        if (!subCodeBuff) {
            printf
                ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subCodeBuff\n");
            return 0;
        }
        fread((uint8_t *) subCodeBuff, 1, subCodeLength, file); /* TODO: check return value */
        sd.colorCode = subCodeBuff;
        subColorNameLength = fgetc(file);
        subColorNameBuff = (char *)malloc(subColorNameLength);
        if (!subColorNameBuff) {
            printf
                ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff\n");
            return 0;
        }
        fread((uint8_t *) subColorNameBuff, 1, subColorNameLength, file);       /* TODO: check return value */
        sd.colorName = subColorNameBuff;
        sd.someOtherInt = emb_read_i32(file);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

int8_t readStx(EmbPattern *pattern, FILE *file)
{
    int i, threadCount;
    uint8_t *gif = 0;
    /* public Bitmap Image; */
    StxThread *stxThreads = 0;
    uint8_t headerBytes[7];
    int8_t *header = 0;
    int8_t stor;
    int8_t filetype[4], version[5];
    int paletteLength, imageLength, something1, stitchDataOffset, something3;
    int threadDescriptionOffset, stitchCount, left, right, colors;
    int val[12];
    int bottom, top;

    if (!check_header_present(file, 15)) {
        puts("ERROR: header is not present.");
        return 0;
    }

    /* bytes 0-6 */
    if (!read_n_bytes(file, headerBytes, 7)) {
        return 0;
    }
    header = (char *)headerBytes;

    /* bytes 7-9 */
    memcpy(filetype, &header[0], 3);
    /* bytes 10-13 */
    memcpy(version, &header[3], 4);
    filetype[3] = '\0';
    version[4] = '\0';
    /* byte 14 */
    stor = (char)fgetc(file);
    if (emb_verbose > 1) {
        printf("stor: %d\n", stor);
    }

    /* bytes 15- */
    paletteLength = emb_read_i32(file);
    imageLength = emb_read_i32(file);
    something1 = emb_read_i32(file);
    stitchDataOffset = emb_read_i32(file);
    something3 = emb_read_i32(file);
    threadDescriptionOffset = emb_read_i32(file);
    stitchCount = emb_read_i32(file);
    colors = emb_read_i32(file);
    right = emb_read_i16(file);
    left = emb_read_i16(file);
    bottom = emb_read_i16(file);
    top = emb_read_i16(file);
    gif = (uint8_t *) malloc(imageLength);
    if (!gif) {
        printf
            ("ERROR: format-stx.c readStx(), unable to allocate memory for gif\n");
        return 0;
    }
    if (!read_n_bytes(file, gif, imageLength)) {
        return 0;
    }
    /*Stream s2 = new MemoryStream(gif); TODO: review */
    /*Image = new Bitmap(s2); TODO: review */

    threadCount = emb_read_i16(file);
    stxThreads = (StxThread *) malloc(sizeof(StxThread) * threadCount);
    if (!stxThreads) {
        printf("ERROR: format-stx.c readStx(), unable ");
        printf("to allocate memory for stxThreads\n");
        return 0;
    }
    for (i = 0; i < threadCount; i++) {
        EmbThread t;
        StxThread st;
        stxReadThread(&st, file);

        t.color = st.stxColor;
        strcpy(t.description, st.colorName);
        strcpy(t.catalogNumber, st.colorCode);
        emb_add_thread(pattern, t);
        stxThreads[i] = st;
    }

    fseek(file, 15, SEEK_CUR);

    for (i = 0; i < 12; i++) {
        val[i] = emb_read_i16(file);
        if (emb_verbose > 1) {
            printf("identify val[%d] = %d", i, val[i]);
        }
    }
    if (emb_verbose > 1) {
        puts("val[4] == val[5] == 0");
        puts("val[10] == val[11] == 0");
    }
    fseek(file, 8, SEEK_CUR);   /* 0 0 */
    /* br.BaseStream.Position = stitchDataOffset; TODO: review */
    for (i = 1; i < stitchCount;) {
        int8_t b0 = (char)fgetc(file);
        int8_t b1 = (char)fgetc(file);
        if (b0 == -128) {
            switch (b1) {
            case 1:
                b0 = (char)fgetc(file);
                b1 = (char)fgetc(file);
                /*emb_add_stitch(b0, b1, STOP); TODO: review */

                i++;
                break;
            case 2:
                b0 = (char)fgetc(file);
                b1 = (char)fgetc(file);
                emb_add_stitch(pattern, b0 / 10.0, b1 / 10.0, JUMP, 1);
                i++;
                break;
            case -94:
                /* TODO: Is this a synchronize?
                   If so document it in the comments. */
                break;
            default:
                /*Debugger.Break(); TODO: review */
                break;
            }
        } else {
            emb_add_stitch(pattern, b0 / 10.0, b1 / 10.0, NORMAL, 1);
            i++;
        }
    }
    emb_flip_vertical(pattern);
    return 1;
}

int8_t writeStx(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: writeStx is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void *)pattern, (void *)file);
    }
    return 0;                   /*TODO: finish writeStx */
}

