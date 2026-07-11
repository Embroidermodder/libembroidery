/* Melco Embroidery Format (.ofm)
 *
 * Stitch Only Format.
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

int8_t writeDst(EmbPattern *pattern, FILE *file);

int8_t *ofmReadLibrary(FILE *file)
{
    int stringLength = 0;
    int8_t *libraryName = 0;
    /* FF FE FF */
    uint8_t leadIn[3];

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n");
        return 0;
    }

    fread(leadIn, 1, 3, file);  /* TODO: check return value */
    uint8_t a;
    fread(&a, 1, 1, file);
    stringLength = a;
    libraryName = (char *)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) {
        printf
            ("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n");
        return 0;
    }
    fread((uint8_t *) libraryName, 1, stringLength * 2, file);  /* TODO: check return value */
    return libraryName;
}

static int ofmReadClass(FILE *file)
{
    int len;
    EmbString s;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
        return 0;
    }

    emb_read_i16(file);
    len = emb_read_i16(file);

    fread((uint8_t *) s, 1, len, file);
    /* TODO: check return value */
    s[len] = '\0';
    if (!strcmp(s, "CExpStitch")) {
        return 0x809C;
    }
    if (!strcmp(s, "CColorChange")) {
        return 0xFFFF;
    }
    return 0;
}

void ofmReadBlockHeader(FILE *file)
{
    int val[10], i;             /* TODO: determine what these represent */
    uint8_t len;
    int8_t *s = 0;
    uint16_t short1;
    short unknown1;
    /* TODO: determine what the unknown variables represent */
    int unknown3, unknown2;
    /* TODO: determine what this represents */

    if (!file) {
        printf
            ("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
        return;
    }

    unknown1 = emb_read_i16(file);
    unknown2 = emb_read_i32(file);
    unknown3 = emb_read_i32(file);
    /* int v = fread(&v, 1, 3, file)?; TODO: review */
    emb_read_i16(file);
    fseek(file, 1, SEEK_CUR);
    len = (char)fgetc(file);
    s = (char *)malloc(2 * len);
    if (!s) {
        printf
            ("ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s\n");
        return;
    }
    fread((uint8_t *) s, 1, 2 * len, file);
    /* TODO: check return value */
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i = 0; i < 10; i++) {
        val[i] = emb_read_i32(file);
        printf("%d", val[i]);
    }
    short1 = emb_read_i16(file);      /*  0 */
}

/* . */
void ofmReadColorChange(FILE *file, EmbPattern *pattern)
{
    if (!file) {
        printf
            ("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n");
        return;
    }
    if (!pattern) {
        printf
            ("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    emb_add_stitch(pattern, 0.0, 0.0, STOP, 1);
}

void ofmReadThreads(FILE *file, EmbPattern *p)
{
    int i, numberOfColors, stringLen, numberOfLibraries;
    int8_t *primaryLibraryName = 0;
    int8_t *expandedString = 0;

    if (!file) {
        printf("ERROR: ofm_read_threads(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: ofm_read_threads(), p argument is null\n");
        return;
    }

    /* FF FE FF 00 */
    fseek(file, 4, SEEK_CUR);

    numberOfColors = emb_read_i16(file);

    fseek(file, 4, SEEK_CUR);
    stringLen = emb_read_i16(file);
    expandedString = (char *)malloc(stringLen);
    if (!expandedString) {
        printf
            ("ERROR: format-ofm.c ofm_read_threads(), unable to allocate memory for expandedString\n");
        return;
    }
    fread((uint8_t *) expandedString, 1, stringLen, file);
    /* TODO: check return value */
    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        int8_t colorNumberText[11], colorName[512];
        int threadLibrary, colorNameLength, colorNumber;
        embColor_read(file, &(thread.color), 4);
        threadLibrary = emb_read_i16(file);
        fseek(file, 2, SEEK_CUR);
        colorNumber = emb_read_i32(file);
        fseek(file, 3, SEEK_CUR);
        colorNameLength = emb_read_i8(file);
        fread(colorName, 1, colorNameLength * 2, file);
        /* TODO: check return value */
        fseek(file, 2, SEEK_CUR);
        sprintf(colorNumberText, "%10d", colorNumber);
        strcpy(thread.catalogNumber, colorNumberText);
        strcpy(thread.description, colorName);
        emb_add_thread(p, thread);
    }
    fseek(file, 2, SEEK_CUR);
    primaryLibraryName = ofmReadLibrary(file);
    numberOfLibraries = emb_read_i16(file);

    if (emb_verbose > 1) {
        printf("primary library name: %s\n", primaryLibraryName);
    }

    for (i = 0; i < numberOfLibraries; i++) {
        /*libraries.Add( TODO: review */
        int8_t *libName = ofmReadLibrary(file);
        safe_free(libName);
    }
}

EmbReal ofmDecode(uint8_t b1, uint8_t b2)
{
    EmbReal val = (EmbReal) (int16_t) (b1 << 8 | b2);
    return val;
}

void ofmReadExpanded(FILE *file, EmbPattern *p)
{
    int i, numberOfStitches = 0;

    if (!file) {
        printf
            ("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    numberOfStitches = emb_read_i32(file);

    for (i = 0; i < numberOfStitches; i++) {
        uint8_t stitch[5];
        fread(stitch, 1, 5, file);      /* TODO: check return value */
        if (stitch[0] == 0) {
            EmbReal x = ofmDecode(stitch[1], stitch[2]) / 10.0;
            EmbReal y = ofmDecode(stitch[3], stitch[4]) / 10.0;
            emb_add_stitch_abs(p, x, y, i == 0 ? JUMP : NORMAL, 1);
        } else if (stitch[0] == 32) {
            EmbReal x = ofmDecode(stitch[1], stitch[2]) / 10.0;
            EmbReal y = ofmDecode(stitch[3], stitch[4]) / 10.0;
            emb_add_stitch_abs(p, x, y, i == 0 ? TRIM : NORMAL, 1);
        }
    }
}

int8_t readOfm(EmbPattern *pattern, FILE *fileCompound)
{
    int unknownCount, key = 0, classNameLength;
    int8_t *s = 0;
    FILE *file;
    bcf_file *bcfFile = 0;

    if (emb_verbose > 1) {
        puts("Overridden during development.");
        return 0;
    }

    bcfFile = (bcf_file *) malloc(sizeof(bcf_file));
    if (!bcfFile) {
        printf
            ("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n");
        return 0;
    }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    bcfFile = 0;
    fseek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    fseek(file, 0x110, SEEK_CUR);
    fseek(file, 0x4, SEEK_CUR); /* EMB_INT32_LITTLE */
    classNameLength = emb_read_i16(file);
    s = (char *)malloc(sizeof(char) * classNameLength);
    if (!s) {
        printf
            ("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n");
        return 0;
    }
    fread((uint8_t *) s, 1, classNameLength, file);     /* TODO: check return value */
    unknownCount = emb_read_i16(file);
    /* TODO: determine what unknown count represents */
    if (emb_verbose > 1) {
        printf("unknownCount = %d\n", unknownCount);
    }

    emb_read_i16(file);
    key = ofmReadClass(file);
    while (1) {
        if (key == 0xFEFF) {
            break;
        }
        if (key == 0x809C) {
            ofmReadExpanded(file, pattern);
        } else {
            ofmReadColorChange(file, pattern);
        }
        key = emb_read_u16(file);
        if (key == 0xFFFF) {
            ofmReadClass(file);
        }
    }

    emb_flip(pattern, 1, 1);

    return 1;
}

int8_t writeOfm(EmbPattern *pattern, FILE *file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0;                   /*TODO: finish writeOfm */
}
