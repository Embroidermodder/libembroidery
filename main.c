/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "embroidery.h"

/* same order as flag_list, to use in jump table */
#define FLAG_TO                       0
#define FLAG_TO_SHORT                 1
#define FLAG_HELP                     2
#define FLAG_HELP_SHORT               3
#define FLAG_FORMATS                  4
#define FLAG_FORMATS_SHORT            5
#define FLAG_QUIET                    6
#define FLAG_QUIET_SHORT              7
#define FLAG_VERBOSE                  8
#define FLAG_VERBOSE_SHORT            9
#define FLAG_VERSION                 10
#define FLAG_VERSION_SHORT           11
#define FLAG_CIRCLE                  12
#define FLAG_CIRCLE_SHORT            13
#define FLAG_ELLIPSE                 14
#define FLAG_ELLIPSE_SHORT           15
#define FLAG_LINE                    16
#define FLAG_LINE_SHORT              17
#define FLAG_POLYGON                 18
#define FLAG_POLYGON_SHORT           19
#define FLAG_POLYLINE                20
#define FLAG_POLYLINE_SHORT          21
#define FLAG_RENDER                  22
#define FLAG_RENDER_SHORT            23
#define FLAG_SATIN                   24
#define FLAG_SATIN_SHORT             25
#define FLAG_STITCH                  26
#define FLAG_STITCH_SHORT            27
#define FLAG_TEST                    28
#define FLAG_FULL_TEST_SUITE         29
#define FLAG_HILBERT_CURVE           30
#define FLAG_SIERPINSKI_TRIANGLE     31
#define FLAG_FILL                    32
#define FLAG_FILL_SHORT              33
#define FLAG_IMAGE_WIDTH             34
#define FLAG_IMAGE_HEIGHT            35
#define FLAG_SIMULATE                36
#define FLAG_COMBINE                 37
#define NUM_FLAGS                    38

/* DATA 
 *******************************************************************/

EmbThread black_thread = { { 0, 0, 0 }, "Black", "Black" };
int emb_verbose = 0;

const char *flag_list[] = {
    "--to",
    "-t",
    "--help",
    "-h",
    "--formats",
    "-F",
    "--quiet",
    "-q",
    "--verbose",
    "-V",
    "--version",
    "-v",
    "--circle",
    "-c",
    "--ellipse",
    "-e",
    "--line",
    "-l",
    "--polyline",
    "-P",
    "--polygon",
    "-p",
    "--render",
    "-r",
    "--satin",
    "-s",
    "--stitch",
    "-S",
    "--test",
    "--full-test-suite",
    "--hilbert-curve",
    "--sierpinski-triangle",
    "--fill",
    "-f",
    "--image-width",
    "--image-height",
    "--simulate",
    "--combine"
};

const char *version_string = "embroider v0.1";
const char *welcome_message = "EMBROIDER\n"
    "    A command line program for machine embroidery.\n"
    "    Copyright 2013-2022 The Embroidermodder Team\n"
    "    Licensed under the terms of the zlib license.\n"
    "\n"
    "    https://github.com/Embroidermodder/libembroidery\n"
    "    https://embroidermodder.org\n";

int emb_error = 0;

/*! Constant representing the number of Double Indirect FAT entries in a single header */
const unsigned int NumberOfDifatEntriesInHeader = 109;
const unsigned int sizeOfFatEntry = sizeof(unsigned int);
const unsigned int sizeOfDifatEntry = 4;
const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
const unsigned int sizeOfDirectoryEntry = 128;
/*
const int supportedMinorVersion = 0x003E;
const int littleEndianByteOrderMark = 0xFFFE;
*/

const double embConstantPi = 3.1415926535;


/* GENERATORS
 *******************************************************************/

int svg_generator(char *s, char **token_table)
{
    return 0;
}

void embVector_print(EmbVector v, char *label)
{
    fprintf(stdout, "%sX = %f\n", v.x);
    fprintf(stdout, "%sY = %f\n", v.y);
}

void embArc_print(EmbArc arc)
{
    embVector_print(arc.start, "start");
    embVector_print(arc.mid, "middle");
    embVector_print(arc.end, "end");
}

/* Checks that there are enough bytes to interpret the header,
 * stops possible segfaults when reading in the header bytes.
 *
 * Returns 0 if there aren't enough, or the length of the file
 * if there are.
 */
int check_header_present(FILE* file, int minimum_header_length)
{
    int length;
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (length < minimum_header_length) {
        return 0;
    }
    return length;
}


unsigned int sectorSize(bcf_file* bcfFile) {
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    }
    return 4096;
}

int haveExtraDIFATSectors(bcf_file* file) {
    return (int)(numberOfEntriesInDifatSector(file->difat) > 0);
}

int seekToOffset(FILE* file, const unsigned int offset) {
    return fseek(file, offset, SEEK_SET);
}

int seekToSector(bcf_file* bcfFile, FILE* file, const unsigned int sector) {
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return seekToOffset(file, offset);
}

void parseDIFATSectors(FILE* file, bcf_file* bcfFile) {
    unsigned int numberOfDifatEntriesStillToRead = bcfFile->header.numberOfFATSectors - NumberOfDifatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &numberOfDifatEntriesStillToRead);
    }
}

int bcfFile_read(FILE* file, bcf_file* bcfFile) {
    unsigned int i, numberOfDirectoryEntriesPerSector;
    unsigned int directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (!bcfFileHeader_isValid(bcfFile->header)) {
        printf("Failed to parse header\n");
        return 0;
    }

    bcfFile->difat = bcf_difat_create(file, bcfFile->header.numberOfFATSectors, sectorSize(bcfFile));
    if (haveExtraDIFATSectors(bcfFile)) {
        parseDIFATSectors(file, bcfFile);
    }

    bcfFile->fat = bcfFileFat_create(sectorSize(bcfFile));
    for (i = 0; i < bcfFile->header.numberOfFATSectors; ++i) {
        unsigned int fatSectorNumber = bcfFile->difat->fatSectorEntries[i];
        seekToSector(bcfFile, file, fatSectorNumber);
        loadFatFromSector(bcfFile->fat, file);
    }

    numberOfDirectoryEntriesPerSector = sectorSize(bcfFile) / sizeOfDirectoryEntry;
    bcfFile->directory = CompoundFileDirectory(numberOfDirectoryEntriesPerSector);
    directorySectorToReadFrom = bcfFile->header.firstDirectorySectorLocation;
    while (directorySectorToReadFrom != CompoundFileSector_EndOfChain) {
        seekToSector(bcfFile, file, directorySectorToReadFrom);
        readNextSector(file, bcfFile->directory);
        directorySectorToReadFrom = bcfFile->fat->fatEntries[directorySectorToReadFrom];
    }

    return 1;
}

FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind) {
    int filesize, sectorSize, currentSector;
    int sizeToWrite, currentSize, totalSectors, i, j;
    FILE* fileOut = tmpfile();
    bcf_directory_entry* pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (strcmp(fileToFind, pointer->directoryEntryName) == 0)
            break;
        pointer = pointer->next;
    }
    filesize = pointer->streamSize;
    sectorSize = bcfFile->difat->sectorSize;
    currentSize = 0;
    currentSector = pointer->startingSectorLocation;
    totalSectors = (int)ceil((float)filesize / sectorSize);
    for (i = 0; i < totalSectors; i++) {
        seekToSector(bcfFile, file, currentSector);
        sizeToWrite = filesize - currentSize;
        if (sectorSize < sizeToWrite) {
            sizeToWrite = sectorSize;
        }
        for (j=0; j<sizeToWrite; j++) {
            char input;
            fread(&input, 1, 1, file);
            fwrite(&input, 1, 1, fileOut);
        }
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    return fileOut;
}

void bcf_file_free(bcf_file* bcfFile)
{
    bcf_file_difat_free(bcfFile->difat);
    bcf_file_fat_free(&bcfFile->fat);
    bcf_directory_free(&bcfFile->directory);
    free(bcfFile);
}

bcf_file_difat* bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize)
{
    unsigned int i;
    bcf_file_difat* difat = 0;
    unsigned int sectorRef;

    difat = (bcf_file_difat*)malloc(sizeof(bcf_file_difat));
    if (!difat) {
        printf("ERROR: compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat\n");
        return NULL;
    }

    difat->sectorSize = sectorSize;
    if (fatSectors > NumberOfDifatEntriesInHeader) {
        fatSectors = NumberOfDifatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        sectorRef = fread_uint32(file);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < NumberOfDifatEntriesInHeader; ++i) {
        sectorRef = fread_uint32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n", sectorRef, i);
        }
    }
    return difat;
}

unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat) {
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

unsigned int readFullSector(FILE* file, bcf_file_difat* bcfFile, 
                            unsigned int* numberOfDifatEntriesStillToRead) {
    unsigned int i;
    unsigned int sectorRef;
    unsigned int nextDifatSectorInChain;
    unsigned int entriesToReadInThisSector = 0;
    if (*numberOfDifatEntriesStillToRead > numberOfEntriesInDifatSector(bcfFile)) {
        entriesToReadInThisSector = numberOfEntriesInDifatSector(bcfFile);
        *numberOfDifatEntriesStillToRead -= entriesToReadInThisSector;
    } else {
        entriesToReadInThisSector = *numberOfDifatEntriesStillToRead;
        *numberOfDifatEntriesStillToRead = 0;
    }

    for (i = 0; i < entriesToReadInThisSector; ++i) {
        sectorRef = fread_uint32(file);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < numberOfEntriesInDifatSector(bcfFile); ++i) {
        sectorRef = fread_uint32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c readFullSector(), ");
            printf("Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    nextDifatSectorInChain = fread_uint32(file);
    return nextDifatSectorInChain;
}

void bcf_file_difat_free(bcf_file_difat* difat) {
    free(difat);
    difat = 0;
}

void parseDirectoryEntryName(FILE* file, bcf_directory_entry* dir) {
    int i;
    for (i = 0; i < 32; ++i) {
        unsigned short unicodechar;
        fread_int(file, &unicodechar, EMB_INT16_LITTLE);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries) {
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

EmbTime parseTime(FILE* file)
{
    EmbTime returnVal;
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    fread_int(file, &ft_low, EMB_INT32_LITTLE);
    fread_int(file, &ft_high, EMB_INT32_LITTLE);
    /* TODO: translate to actual date time */
    returnVal.day = 1;
    returnVal.hour = 2;
    returnVal.minute = 3;
    returnVal.month = 4;
    returnVal.second = 5;
    returnVal.year = 6;
    return returnVal;
}

bcf_directory_entry* CompoundFileDirectoryEntry(FILE* file)
{
    const int guidSize = 16;
    bcf_directory_entry* dir = malloc(sizeof(bcf_directory_entry));
    if (dir == NULL) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
        return 0;
    }
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = fread_uint16(file);
    dir->objectType = (unsigned char)fgetc(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry()");
        printf(", unexpected object type: %d\n", dir->objectType);
        return 0;
    }
    dir->colorFlag = (unsigned char)fgetc(file);
    fread_int(file, &(dir->leftSiblingId), EMB_INT32_LITTLE);
    fread_int(file, &(dir->rightSiblingId), EMB_INT32_LITTLE);
    fread_int(file, &(dir->childId), EMB_INT32_LITTLE);
    fread(dir->CLSID, 1, guidSize, file);
    fread_int(file, &(dir->stateBits), EMB_INT32_LITTLE);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    fread_int(file, &(dir->startingSectorLocation), EMB_INT32_LITTLE);
    dir->streamSize = fread_uint32(file); /* This should really be __int64 or long long, but for our uses we should never run into an issue */
    dir->streamSizeHigh = fread_uint32(file); /* top portion of int64 */
    return dir;
}

void readNextSector(FILE* file, bcf_directory* dir) {
    unsigned int i;
    for (i = 0; i < dir->maxNumberOfDirectoryEntries; ++i) {
        bcf_directory_entry* dirEntry = CompoundFileDirectoryEntry(file);
        bcf_directory_entry* pointer = dir->dirEntries;
        if (!pointer) {
            dir->dirEntries = dirEntry;
        } else {
            while (pointer) {
                if (!pointer->next) {
                    pointer->next = dirEntry;
                    break;
                }
                pointer = pointer->next;
            }
        }
    }
}

void bcf_directory_free(bcf_directory** dir) {
    bcf_directory *dirptr;
    bcf_directory_entry* pointer;
    if (dir == NULL){
        return;
    }
    dirptr = *dir;
    pointer = dirptr->dirEntries;
    while (pointer) {
        bcf_directory_entry* entryToFree;
        entryToFree = pointer;
        pointer = pointer->next;
        free(entryToFree);
    }
    if (*dir) {
        free(*dir);
        *dir = NULL;
    }
}

bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize) {
    bcf_file_fat* fat = (bcf_file_fat*)malloc(sizeof(bcf_file_fat));
    if (!fat) {
        printf("ERROR: compound-file-fat.c bcfFileFat_create(), ");
        printf("cannot allocate memory for fat\n");
        return NULL;
    }
    fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
    fat->fatEntryCount = 0;
    return fat;
}

void loadFatFromSector(bcf_file_fat* fat, FILE* file) {
    unsigned int i;
    unsigned int currentNumberOfFatEntries = fat->fatEntryCount;
    unsigned int newSize = currentNumberOfFatEntries + fat->numberOfEntriesInFatSector;
    for (i = currentNumberOfFatEntries; i < newSize; ++i) {
        unsigned int fatEntry = fread_uint32(file);
        fat->fatEntries[i] = fatEntry;
    }
    fat->fatEntryCount = newSize;
}

void bcf_file_fat_free(bcf_file_fat** fat) {
    free(*fat);
    *fat = NULL;
}

bcf_file_header bcfFileHeader_read(FILE* file) {
    bcf_file_header header;
    fread(header.signature, 1, 8, file);
    fread(header.CLSID, 1, 16, file);
    header.minorVersion = fread_uint16(file);
    header.majorVersion = fread_uint16(file);
    header.byteOrder = fread_uint16(file);
    header.sectorShift = fread_uint16(file);
    header.miniSectorShift = fread_uint16(file);
    header.reserved1 = fread_uint16(file);
    header.reserved2 = (unsigned int)fread_uint32(file);
    header.numberOfDirectorySectors = (unsigned int)fread_uint32(file);
    header.numberOfFATSectors = (unsigned int)fread_uint32(file);
    header.firstDirectorySectorLocation = (unsigned int)fread_uint32(file);
    header.transactionSignatureNumber = (unsigned int)fread_uint32(file);
    header.miniStreamCutoffSize = (unsigned int)fread_uint32(file);
    header.firstMiniFATSectorLocation = (unsigned int)fread_uint32(file);
    header.numberOfMiniFatSectors = (unsigned int)fread_uint32(file);
    header.firstDifatSectorLocation = (unsigned int)fread_uint32(file);
    header.numberOfDifatSectors = (unsigned int)fread_uint32(file);
    return header;
}

int bcfFileHeader_isValid(bcf_file_header header)
{
    if (memcmp(header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1", 8) != 0) {
        printf("bad header signature\n");
        return 0;
    }
    return 1;
}

double embRect_x(EmbRect rect) {
    return rect.left;
}

double embRect_y(EmbRect rect) {
    return rect.top;
}

double embRect_width(EmbRect rect) {
    return rect.right - rect.left;
}

double embRect_height(EmbRect rect) {
    return rect.bottom - rect.top;
}

/* Sets the left edge of the rect to x. The right edge is not modified. */
void embRect_setX(EmbRect* rect, double x) {
    rect->left = x;
}

/* Sets the top edge of the rect to y. The bottom edge is not modified. */
void embRect_setY(EmbRect* rect, double y) {
    rect->top = y;
}

/* Sets the width of the rect to w. The right edge is modified. 
    The left edge is not modified. */
void embRect_setWidth(EmbRect* rect, double w) {
    rect->right = rect->left + w;
}

/* Sets the height of the rect to h. The bottom edge is modified. 
    The top edge is not modified. */
void embRect_setHeight(EmbRect* rect, double h) {
    rect->bottom = rect->top + h;
}

void embRect_setCoords(EmbRect* rect, double x1, double y1, double x2, double y2) {
    rect->left = x1;
    rect->top = y1;
    rect->right = x2;
    rect->bottom = y2;
}

void embRect_setRect(EmbRect* rect, double x, double y, double w, double h) {
    rect->left = x;
    rect->top = y;
    rect->right = x + w;
    rect->bottom = y + h;
}

/* Returns an EmbRectObject. It is created on the stack. */
EmbRectObject embRectObject_make(double x, double y, double w, double h) {
    EmbRectObject stackRectObj;
    stackRectObj.rect.left = x;
    stackRectObj.rect.top = y;
    stackRectObj.rect.right = x + w;
    stackRectObj.rect.bottom = y + h;
    stackRectObj.rotation = 0.0;
    stackRectObj.color.r = 0;
    stackRectObj.color.g = 0;
    stackRectObj.color.b = 0;
    stackRectObj.lineType = 0;
    stackRectObj.radius = 0;
    return stackRectObj;
}

void embSatinOutline_generateSatinOutline(EmbArray *lines, double thickness, EmbSatinOutline* result) {
    int i;
    EmbLine line1, line2;
    EmbSatinOutline outline;
    EmbVector out;
    EmbVector v1;
    EmbVector temp;
    EmbLine line;

    double halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->count - 2;
    outline.side1 = embArray_create(EMB_VECTOR);
    if (!outline.side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side1\n");
        return;
    }
    outline.side2 = embArray_create(EMB_VECTOR);
    if (!outline.side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side2\n");
        return;
    }

    for (i = 1; i < lines->count; i++) {
        line.start = lines->vector[i - 1];
        line.end = lines->vector[i];

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side1, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side1, temp);

        embVector_multiply(v1, -halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side2, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side2, temp);
    }

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), result argument is null\n");
        return;
    }
    result->side1 = embArray_create(EMB_VECTOR);
    if (!result->side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side1\n");
        return;
    }
    result->side2 = embArray_create(EMB_VECTOR);
    if (!result->side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side2\n");
        return;
    }

    embArray_addVector(result->side1, outline.side1->vector[0]);
    embArray_addVector(result->side2, outline.side2->vector[0]);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.start = outline.side1->vector[i - 3];
        line1.end = outline.side1->vector[i - 2];
        line2.start = outline.side1->vector[i - 1];
        line2.end = outline.side1->vector[i];
        out = embLine_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        embArray_addVector(result->side1, out);

        line1.start = outline.side2->vector[i - 3];
        line1.end = outline.side2->vector[i - 2];
        line2.start = outline.side2->vector[i - 1];
        line2.end = outline.side2->vector[i];
        out = embLine_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        embArray_addVector(result->side2, out);
    }

    embArray_addVector(result->side1, outline.side1->vector[2 * lines->count - 3]);
    embArray_addVector(result->side2, outline.side2->vector[2 * lines->count - 3]);
    result->length = lines->count;
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, double density) {
    int i, j;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;
    int numberOfSteps;
    double midLength;

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_renderStitches(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            embVector_subtract(result->side1->vector[j+1], result->side1->vector[j], &topDiff);
            embVector_subtract(result->side2->vector[j+1], result->side2->vector[j], &bottomDiff);

            embVector_average(result->side1->vector[j], result->side2->vector[j], &midLeft);
            embVector_average(result->side1->vector[j+1], result->side2->vector[j+1], &midRight);

            embVector_subtract(midLeft, midRight, &midDiff);
            midLength = embVector_length(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            embVector_multiply(topDiff, 1.0/numberOfSteps, &topStep);
            embVector_multiply(bottomDiff, 1.0/numberOfSteps, &bottomStep);
            currTop = result->side1->vector[j];
            currBottom = result->side2->vector[j];

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = embArray_create(EMB_VECTOR);
                }
                embArray_addVector(stitches, currTop);
                embArray_addVector(stitches, currBottom);
                embVector_add(currTop, topStep, &currTop);
                embVector_add(currBottom, bottomStep, &currBottom);
            }
        }
        embArray_addVector(stitches, currTop);
        embArray_addVector(stitches, currBottom);
    }
    return stitches;
}

/*! Initializes and returns an EmbSettings */
EmbSettings embSettings_init(void) {
    EmbSettings settings;
    settings.dstJumpsPerTrim = 6;
    settings.home.x = 0.0;
    settings.home.y = 0.0;
    return settings;
}

/*! Returns the home position stored in (\a settings) as an EmbPoint (\a point). */
EmbVector embSettings_home(EmbSettings* settings) {
    return settings->home;
}

/*! Sets the home position stored in (\a settings) to EmbPoint (\a point). You will rarely ever need to use this. */
void embSettings_setHome(EmbSettings* settings, EmbVector point) {
    settings->home = point;
}

void write_24bit(FILE* file, int x)
{
    unsigned char a[4];
    a[0] = (unsigned char)0;
    a[1] = (unsigned char)(x & 0xFF);
    a[2] = (unsigned char)((x >> 8) & 0xFF);
    a[3] = (unsigned char)((x >> 16) & 0xFF);
    fwrite(a, 1, 4, file);
}

int embColor_distance(EmbColor a, EmbColor b)
{
    int t;
    t = (a.r-b.r)*(a.r-b.r);
    t += (a.g-b.g)*(a.g-b.g);
    t += (a.b-b.b)*(a.b-b.b);
    return t;
}

void embColor_read(FILE *f, EmbColor *c, int toRead)
{
    unsigned char b[4];
    fread(b, 1, toRead, f);
    c->r = b[0];
    c->g = b[1];
    c->b = b[2];
}

void embColor_write(FILE *f, EmbColor c, int toWrite)
{
    unsigned char b[4];
    b[0] = c.r;
    b[1] = c.g;
    b[2] = c.b;
    b[3] = 0;
    fwrite(b, 1, toWrite, f);
}

/**
 * Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * @param color  The EmbColor color to match.
 * @param colors The EmbThreadList pointer to start the search at.
 * @param mode   Is the argument an array of threads (0) or colors (1)?
 * @return closestIndex The entry in the ThreadList that matches.
 */
int embThread_findNearestColor(EmbColor color, EmbArray* a, int mode) {
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    for (i = 0; i < a->count; i++) {
        int delta;
        if (mode == 0) { /* thread mode */
            delta = embColor_distance(color, a->thread[i].color);
        } else { /* color array mode */
            delta = embColor_distance(color, a->color[i]);
        }

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

int embThread_findNearestColor_fromThread(EmbColor color, EmbThread* a, int length) {
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;

    for (i = 0; i < length; i++) {
        int delta;
        delta = embColor_distance(color, a[i].color);

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

/**
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * @return c The resulting color.
 */
EmbThread embThread_getRandom(void) {
    EmbThread c;
    c.color.r = rand()%256;
    c.color.g = rand()%256;
    c.color.b = rand()%256;
    strcpy(c.description, "random");
    strcpy(c.catalogNumber, "");
    return c;
}

void binaryReadString(FILE* file, char* buffer, int maxLength) {
    int i = 0;
    while(i < maxLength) {
        buffer[i] = (char)fgetc(file);
        if (buffer[i] == '\0') break;
        i++;
    }
}

void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength) {
    int i = 0;
    for (i = 0; i < stringLength * 2; i++) {
        char input = (char)fgetc(file);
        if (input != 0) {
            buffer[i] = input;
        }
    }
}

/**
 * Tests for the presence of a string \a s in the supplied
 * \a array.
 *
 * The end of the array is marked by an empty string.
 *
 * @return 0 if not present 1 if present.
 */
int stringInArray(const char *s, const char **array) {
    int i;
    for (i = 0; strlen(array[i]); i++) {
        if (!strcmp(s, array[i])) {
            return 1;
        }
    }
    return 0;
}

int emb_readline(FILE* file, char *line, int maxLength) {
    int i;
    char c;
    for (i = 0; i < maxLength-1; i++) {
        if (!fread(&c, 1, 1, file)) {
            break;
        }
        if (c == '\r') {
            fread(&c, 1, 1, file);
            if (c != '\n') {
                fseek(file, -1L, SEEK_CUR);
            }
            break;
        }
        if (c == '\n') {
            break;
        }
        *line = c;
        line++;
    }
    *line = 0;
    return i;
}

/* TODO: trimming function should handle any character, not just whitespace */
char const WHITESPACE[] = " \t\n\r";

/* TODO: description */
void get_trim_bounds(char const *s,
                            char const **firstWord,
                            char const **trailingSpace) {
    char const* lastWord = 0;
    *firstWord = lastWord = s + strspn(s, WHITESPACE);
    do {
        *trailingSpace = lastWord + strcspn(lastWord, WHITESPACE);
        lastWord = *trailingSpace + strspn(*trailingSpace, WHITESPACE);
    } while (*lastWord != '\0');
}

/* TODO: description */
char* copy_trim(char const *s) {
    char const *firstWord = 0, *trailingSpace = 0;
    char* result = 0;
    size_t newLength;

    get_trim_bounds(s, &firstWord, &trailingSpace);
    newLength = trailingSpace - firstWord;

    result = (char*)malloc(newLength + 1);
    memcpy(result, firstWord, newLength);
    result[newLength] = '\0';
    return result;
}

/*! Optimizes the number (\a num) for output to a text file and returns it as a string (\a str). */
char* emb_optOut(double num, char* str) {
    char *str_end;
    /* Convert the number to a string */
    sprintf(str, "%.10f", num);
    /* Remove trailing zeroes */
    str_end = str + strlen(str);
    while (*--str_end == '0');
    str_end[1] = 0;
    /* Remove the decimal point if it happens to be an integer */
    if (*str_end == '.') {
        *str_end = 0;
    }
    return str;
}

void embTime_initNow(EmbTime* t) {
#ifdef ARDUINO
/*TODO: arduino embTime_initNow */
#else
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    t->year   = timeinfo->tm_year;
    t->month  = timeinfo->tm_mon;
    t->day    = timeinfo->tm_mday;
    t->hour   = timeinfo->tm_hour;
    t->minute = timeinfo->tm_min;
    t->second = timeinfo->tm_sec;
#endif /* ARDUINO */
}

EmbTime embTime_time(EmbTime* t) {
#ifdef ARDUINO
/*TODO: arduino embTime_time */
#else

int divideByZero = 0;
divideByZero = divideByZero/divideByZero; /*TODO: wrap time() from time.h and verify it works consistently */

#endif /* ARDUINO */
    return *t;
}

void usage(void)
{
    puts(welcome_message);
    /* construct from tables above somehow, like how getopt_long works,
     * but we're avoiding that for compatibility
     * (C90, standard libraries only) */
    puts("Usage: embroider [OPTIONS] fileToRead... \n");
    puts("");
    puts("Conversion:");
    puts("    -t, --to        Convert all files given to the format specified");
    puts("                    by the arguments to the flag, for example:");
    puts("                        $ embroider -t dst input.pes");
    puts("                    would convert \"input.pes\" to \"input.dst\"");
    puts("                    in the same directory the program runs in.");
    puts("");
    puts("                    The accepted input formats are (TO BE DETERMINED).");
    puts("                    The accepted output formats are (TO BE DETERMINED).");
    puts("");
    puts("Output:");
    puts("    -h, --help       Print this message.");
    puts("    -F, --formats     Print help on the formats that embroider can deal with.");
    puts("    -q, --quiet      Only print fatal errors.");
    puts("    -V, --verbose    Print everything that has reporting.");
    puts("    -v, --version    Print the version.");
    puts("");
    puts("Modify patterns:");
    puts("    --combine        takes 3 arguments and combines the first");
    puts("                     two by placing them atop each other and");
    puts("                     outputs to the third");
    puts("                        $ embroider --combine a.dst b.dst output.dst");
    puts("");
    puts("Graphics:");
    puts("    -c, --circle     Add a circle defined by the arguments given to the current pattern.");
    puts("    -e, --ellipse    Add a circle defined by the arguments given to the current pattern.");
    puts("    -l, --line       Add a line defined by the arguments given to the current pattern.");
    puts("    -P, --polyline   Add a polyline.");
    puts("    -p, --polygon    Add a polygon.");
    puts("    -r, --render     Create an image in PPM format of what the embroidery should look like.");
    puts("    -s, --satin      Fill the current geometry with satin stitches according");
    puts("                     to the defined algorithm.");
    puts("    -S, --stitch     Add a stitch defined by the arguments given to the current pattern.");
    puts("");
    puts("Quality Assurance:");
    puts("        --test       Run the basic test suite.");
    puts("        --full-test-suite  Run all tests, even those we expect to fail.");
}

void formats(void)
{
    const char* extension = 0;
    const char* description = 0;
    char readerState;
    char writerState;
    int numReaders = 0;
    int numWriters = 0;
    int i;
    puts("List of Formats");
    puts("---------------");
    puts("");
    puts("    KEY");
    puts("    'S' = Yes, and is considered stable.");
    puts("    'U' = Yes, but may be unstable.");
    puts("    ' ' = No.");
    puts("");
    printf("  Format   Read    Write   Description\n");
    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");

    for (i = 0; i < numberOfFormats; i++) {
        extension = formatTable[i].extension;
        description = formatTable[i].description;
        readerState = formatTable[i].reader_state;
        writerState = formatTable[i].writer_state;

        numReaders += readerState != ' '? 1 : 0;
        numWriters += writerState != ' '? 1 : 0;
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n", extension, readerState, writerState, description);
    }

    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");
    printf("| Total: |  %3d  |  %3d  |                                                    |\n", numReaders, numWriters);
    printf("|________|_______|_______|____________________________________________________|\n");
    puts("");
}

/* TODO: Add capability for converting multiple files of various types to a single format. Currently, we only convert a single file to multiple formats. */
int command_line_interface(int argc, char* argv[])
{
    EmbPattern *current_pattern = embPattern_create();
    float width, height;
    int i, j, flags, result;
    if (argc == 1) {
        usage();
        return 0;
    }

    width = 20.0;
    height = 20.0;

    flags = argc-1;
    for (i=1; i < argc; i++) {
        result = -1;
        /* identify what flag index the user may have entered */
        for (j=0; j < NUM_FLAGS; j++) {
            if (!strcmp(flag_list[j], argv[i])) {
                result = j;
                break;
            }
        }
        /* apply the flag */
        switch (result) {
        case FLAG_TO:
            /* the next argument is the format we're converting to */
            puts("This flag is not implemented.");
            break;
        case FLAG_HELP:
        case FLAG_HELP_SHORT:
            usage();
            break;
        case FLAG_FORMATS:
        case FLAG_FORMATS_SHORT:
            formats();
            break;
        case FLAG_QUIET:
        case FLAG_QUIET_SHORT:
            emb_verbose = -1;
            break;
        case FLAG_VERBOSE:
        case FLAG_VERBOSE_SHORT:
            emb_verbose = 1;
            break;
        case FLAG_CIRCLE:
        case FLAG_CIRCLE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_ELLIPSE:
        case FLAG_ELLIPSE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_LINE:
        case FLAG_LINE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_POLYGON:
        case FLAG_POLYGON_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_POLYLINE:
        case FLAG_POLYLINE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_SATIN:
        case FLAG_SATIN_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_STITCH:
        case FLAG_STITCH_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_SIERPINSKI_TRIANGLE:
            puts("This flag is not implemented.");
            break;
        case FLAG_FILL:
            puts("This flag is not implemented.");
            break;
        case FLAG_IMAGE_WIDTH:
            if (i + 1 < argc) {
                i++;
                width = atof(argv[i]);
            }
            else {
                puts("The image width flag requires an argument.");
                break;
            }
            break;
        case FLAG_IMAGE_HEIGHT:
            if (i + 1 < argc) {
                i++;
                height = atof(argv[i]);
            }
            else {
                puts("The image width flag requires an argument.");
                break;
            }
            break;
        case FLAG_RENDER:
        case FLAG_RENDER_SHORT:
            if (i + 1 < argc) {
                /* the user appears to have entered a filename after render */
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.ppm'.");
                    embImage_render(current_pattern, width, height, "output.ppm");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    embImage_render(current_pattern, width, height, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.ppm'.");
                embImage_render(current_pattern, width, height, "output.ppm");
            }
            break;
        case FLAG_SIMULATE:
            if (i + 1 < argc) {
                /* the user appears to have entered a filename after render */
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.avi'.");
                    embImage_simulate(current_pattern, width, height, "output.avi");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    embImage_simulate(current_pattern, width, height, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.avi'.");
                embImage_simulate(current_pattern, width, height, "output.avi");
            }
            break;
        case FLAG_COMBINE:
            if (i + 3 < argc) {
                EmbPattern *out;
                EmbPattern *p1 = embPattern_create();
                EmbPattern *p2 = embPattern_create();
                embPattern_readAuto(p1, argv[i+1]);
                embPattern_readAuto(p2, argv[i+2]);
                out = embPattern_combine(p1, p2);
                embPattern_writeAuto(out, argv[i+3]);
                embPattern_free(p1);
                embPattern_free(p2);
                embPattern_free(out);
            }
            else {
                puts("--combine takes 3 arguments and you have supplied <3.");
            }
            break;
        case FLAG_VERSION:
        case FLAG_VERSION_SHORT:
            puts(version_string);
            break;
        case FLAG_HILBERT_CURVE:
            current_pattern = embPattern_create();
            hilbert_curve(current_pattern, 3);
            break;
        case FLAG_TEST:
            testMain(0);
            break;
        case FLAG_FULL_TEST_SUITE:
            testMain(1);
            break;
        default:
            flags--;
            break;
        }
    }

    /* No flags set: default to simple from-to conversion. */
    if (!flags && argc == 3) {
        convert(argv[1], argv[2]);
    }
    else {
        if (!flags) {
            puts("Please enter an output format for your file, see --help.");
        }
    }
    embPattern_free(current_pattern);
    return 0;
}

#ifdef LIBEMBROIDERY_CLI
int main(int argc, char* argv[])
{
    return command_line_interface(argc, argv);
}
#endif


