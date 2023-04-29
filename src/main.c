/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "embroidery_internal.h"

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
#define FLAG_SIMULATE                34
#define FLAG_COMBINE                 35
#define FLAG_CROSS_STITCH            36
#define NUM_FLAGS                    37

EmbThread black_thread = { { 0, 0, 0 }, "Black", "Black" };
int emb_verbose = 0;
int emb_error = 0;

const EmbReal embConstantPi = 3.1415926535;

/* Constant representing the number of EmbReal Indirect FAT
 * entries in a single header */
const unsigned int difatEntriesInHeader = 109;
const unsigned int sizeOfFatEntry = sizeof(unsigned int);
const unsigned int sizeOfDifatEntry = 4;
const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
const unsigned int sizeOfDirectoryEntry = 128;
/*
const int supportedMinorVersion = 0x003E;
const int littleEndianByteOrderMark = 0xFFFE;
*/

/**
 * @brief 
 * 
 * \a v 
 * \a label 
 *
 * move to vector.c
 */
void embVector_print(EmbVector v, char *label)
{
    printf("%sX = %f\n", label, v.x);
    printf("%sY = %f\n", label, v.y);
}

/**
 * @brief 
 * 
 * \a arc 
 *
 * \todo move to arc.c
 */
void embArc_print(EmbArc arc)
{
    embVector_print(arc.start, "start");
    embVector_print(arc.mid, "middle");
    embVector_print(arc.end, "end");
}

#ifdef LIBEMBROIDERY_CLI
/* DATA 
 *******************************************************************/

/**
 * @brief 
 * 
 */
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
    "--simulate",
    "--combine",
    "--cross-stitch"
};

/**
 * @brief 
 * 
 */
const char *version_string = "embroider v0.1";

/**
 * @brief 
 * 
 */
const char *welcome_message = "EMBROIDER\n"
    "    A command line program for machine embroidery.\n"
    "    Copyright 2013-2022 The Embroidermodder Team\n"
    "    Licensed under the terms of the zlib license.\n"
    "\n"
    "    https://github.com/Embroidermodder/libembroidery\n"
    "    https://embroidermodder.org\n";
#endif

/**
 * @brief 
 * 
 * \a file 
 * \a minimum_header_length 
 * @return int 
 *
 * Checks that there are enough bytes to interpret the header,
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

/**
 * @brief 
 * 
 * \a bcfFile 
 * @return unsigned int 
 */
unsigned int
sectorSize(bcf_file* bcfFile)
{
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    }
    return 4096;
}

/**
 * @brief 
 * 
 * \a file 
 * @return int 
 */
int
haveExtraDIFATSectors(bcf_file* file)
{
    return (int)(entriesInDifatSector(file->difat) > 0);
}

/**
 * @brief 
 * 
 * \a bcfFile 
 * \a file 
 * \a sector 
 * @return int 
 */
int
seekToSector(bcf_file* bcfFile, FILE* file, const unsigned int sector)
{
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return fseek(file, offset, SEEK_SET);
}

/**
 * @brief 
 * 
 * \a file 
 * \a bcfFile 
 */
void
parseDIFATSectors(FILE* file, bcf_file* bcfFile)
{
    unsigned int difatEntriesToRead = bcfFile->header.numberOfFATSectors - difatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (difatEntriesToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &difatEntriesToRead);
    }
}

/**
 * @brief 
 * 
 * \a file 
 * \a bcfFile 
 * @return int 
 */
int
bcfFile_read(FILE* file, bcf_file* bcfFile)
{
    unsigned int i, numberOfDirectoryEntriesPerSector;
    unsigned int directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (memcmp(bcfFile->header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1", 8) != 0) {
        printf("bad header signature\n");
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

/**
 * @brief Get the File object
 * 
 * \a bcfFile 
 * \a file 
 * \a fileToFind 
 * @return FILE* 
 */
FILE*
GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind)
{
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

/**
 * @brief 
 * 
 * \a bcfFile 
 */
void
bcf_file_free(bcf_file* bcfFile)
{
    safe_free(bcfFile->difat);
    safe_free(bcfFile->fat);
    bcf_directory_free(&bcfFile->directory);
    free(bcfFile);
}

/**
 * @brief 
 * 
 * \a file 
 * \a fatSectors 
 * \a sectorSize 
 * @return bcf_file_difat* 
 */
bcf_file_difat*
bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize)
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
    if (fatSectors > difatEntriesInHeader) {
        fatSectors = difatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        embInt_read(file, "sectorRef", &sectorRef, EMB_INT32_LITTLE);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < difatEntriesInHeader; ++i) {
        embInt_read(file, "sectorRef", &sectorRef, EMB_INT32_LITTLE);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n", sectorRef, i);
        }
    }
    return difat;
}

/**
 * @brief 
 * 
 * \a fat 
 * @return unsigned int 
 */
unsigned int
entriesInDifatSector(bcf_file_difat* fat)
{
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

/**
 * @brief 
 * 
 * \a file 
 * \a bcfFile 
 * \a difatEntriesToRead 
 * @return unsigned int 
 */
unsigned int
readFullSector(FILE* file, bcf_file_difat* bcfFile, 
                            unsigned int* difatEntriesToRead)
{
    unsigned int i;
    unsigned int sectorRef;
    unsigned int nextDifatSectorInChain;
    unsigned int entriesToReadInThisSector = 0;
    if (*difatEntriesToRead > entriesInDifatSector(bcfFile)) {
        entriesToReadInThisSector = entriesInDifatSector(bcfFile);
        *difatEntriesToRead -= entriesToReadInThisSector;
    }
    else {
        entriesToReadInThisSector = *difatEntriesToRead;
        *difatEntriesToRead = 0;
    }

    for (i = 0; i < entriesToReadInThisSector; ++i) {
        embInt_read(file, "sectorRef", &sectorRef, EMB_INT32_LITTLE);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < entriesInDifatSector(bcfFile); ++i) {
        embInt_read(file, "sectorRef", &sectorRef, EMB_INT32_LITTLE);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c readFullSector(), ");
            printf("Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    embInt_read(file, "nextDifatSectorInChain", &nextDifatSectorInChain, EMB_INT32_LITTLE);
    return nextDifatSectorInChain;
}

/**
 * @brief 
 * 
 * \a file 
 * \a dir 
 */
void
parseDirectoryEntryName(FILE* file, bcf_directory_entry* dir)
{
    int i;
    for (i = 0; i < 32; ++i) {
        unsigned short unicodechar;
        embInt_read(file, "unicode char", &unicodechar, EMB_INT16_LITTLE);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

/**
 * @brief 
 * 
 * \a maxNumberOfDirectoryEntries 
 * @return bcf_directory* 
 */
bcf_directory*
CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries)
{
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

/**
 * @brief 
 * 
 * \a file 
 * @return EmbTime 
 */
EmbTime
parseTime(FILE* file)
{
    EmbTime returnVal;
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    embInt_read(file, "ft_low", &ft_low, EMB_INT32_LITTLE);
    embInt_read(file, "ft_high", &ft_high, EMB_INT32_LITTLE);
    /* TODO: translate to actual date time */
    returnVal.day = 1;
    returnVal.hour = 2;
    returnVal.minute = 3;
    returnVal.month = 4;
    returnVal.second = 5;
    returnVal.year = 6;
    return returnVal;
}

/**
 * @brief 
 * 
 * \a file 
 * @return bcf_directory_entry* 
 */
bcf_directory_entry*
CompoundFileDirectoryEntry(FILE* file)
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
    embInt_read(file, "left sibling id", &(dir->leftSiblingId), EMB_INT32_LITTLE);
    embInt_read(file, "right sibling id", &(dir->rightSiblingId), EMB_INT32_LITTLE);
    embInt_read(file, "child id", &(dir->childId), EMB_INT32_LITTLE);
    fread(dir->CLSID, 1, guidSize, file);
    embInt_read(file, "state bits", &(dir->stateBits), EMB_INT32_LITTLE);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    embInt_read(file, "starting sector location", &(dir->startingSectorLocation), EMB_INT32_LITTLE);
    /* StreamSize should really be __int64 or long long,
     * but for our uses we should never run into an issue */
    embInt_read(file, "dir->streamSize", &(dir->streamSize), EMB_INT32_LITTLE);
    /* top portion of int64 */
    embInt_read(file, "dir->streamSizeHigh", &(dir->streamSizeHigh), EMB_INT32_LITTLE);
    return dir;
}

/**
 * @brief 
 * 
 * \a file 
 * \a dir 
 */
void
readNextSector(FILE* file, bcf_directory* dir)
{
    unsigned int i;
    for (i = 0; i < dir->maxNumberOfDirectoryEntries; ++i) {
        bcf_directory_entry* dirEntry = CompoundFileDirectoryEntry(file);
        bcf_directory_entry* pointer = dir->dirEntries;
        if (!pointer) {
            dir->dirEntries = dirEntry;
        }
        else {
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

/**
 * @brief 
 * 
 * \a dir 
 */
void
bcf_directory_free(bcf_directory** dir)
{
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
    safe_free(*dir);
}

/**
 * @brief 
 * 
 * \a sectorSize 
 * @return bcf_file_fat* 
 */
bcf_file_fat*
bcfFileFat_create(const unsigned int sectorSize)
{
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

/**
 * @brief 
 * 
 * \a fat 
 * \a file 
 */
void
loadFatFromSector(bcf_file_fat* fat, FILE* file)
{
    unsigned int i;
    unsigned int current_fat_entries = fat->fatEntryCount;
    unsigned int newSize = current_fat_entries + fat->numberOfEntriesInFatSector;
    for (i = current_fat_entries; i < newSize; ++i) {
        int fatEntry;
        embInt_read(file, "fatEntry", &fatEntry, EMB_INT32_LITTLE);
        fat->fatEntries[i] = fatEntry;
    }
    fat->fatEntryCount = newSize;
}

/**
 * @brief 
 * 
 * \a file 
 * @return bcf_file_header 
 */
bcf_file_header
bcfFileHeader_read(FILE* file)
{
    bcf_file_header header;
    fread(header.signature, 1, 8, file);
    fread(header.CLSID, 1, 16, file);
    header.minorVersion = fread_uint16(file);
    header.majorVersion = fread_uint16(file);
    header.byteOrder = fread_uint16(file);
    header.sectorShift = fread_uint16(file);
    header.miniSectorShift = fread_uint16(file);
    header.reserved1 = fread_uint16(file);
    embInt_read(file, "reserved2", &(header.reserved2), EMB_INT32_LITTLE);
    embInt_read(file, "numberOfDirectorySectors", &(header.numberOfDirectorySectors), EMB_INT32_LITTLE);
    embInt_read(file, "numberOfFATSectors", &(header.numberOfFATSectors), EMB_INT32_LITTLE);
    embInt_read(file, "first dir sector loaction", &(header.firstDirectorySectorLocation), EMB_INT32_LITTLE);
    embInt_read(file, "transaction signature number", &(header.transactionSignatureNumber), EMB_INT32_LITTLE);
    embInt_read(file, "mini stream cutoff sector", &(header.miniStreamCutoffSize), EMB_INT32_LITTLE);
    embInt_read(file, "first mini fat sector", &(header.firstMiniFATSectorLocation), EMB_INT32_LITTLE);
    embInt_read(file, "mini fat sectors", &(header.numberOfMiniFatSectors), EMB_INT32_LITTLE);
    embInt_read(file, "first difat Sector", &(header.firstDifatSectorLocation), EMB_INT32_LITTLE);
    embInt_read(file, "difat sectors", &(header.numberOfDifatSectors), EMB_INT32_LITTLE);
    return header;
}

/**
 * @brief 
 * 
 * \a lines 
 * \a thickness 
 * \a result 
 */
void
embSatinOutline_generateSatinOutline(EmbArray *lines, EmbReal thickness, EmbSatinOutline* result)
{
    int i;
    EmbLine line1, line2;
    EmbSatinOutline outline;
    EmbVector out;
    EmbVector v1;
    EmbVector temp;
    EmbLine line;

    EmbReal halfThickness = thickness / 2.0;
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
        line.start = lines->geometry[i - 1].object.vector;
        line.end = lines->geometry[i].object.vector;

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        temp = embVector_add(temp, lines->geometry[i-1].object.vector);
        embArray_addVector(outline.side1, temp);
        temp = embVector_add(temp, lines->geometry[i].object.vector);
        embArray_addVector(outline.side1, temp);

        embVector_multiply(v1, -halfThickness, &temp);
        temp = embVector_add(temp, lines->geometry[i - 1].object.vector);
        embArray_addVector(outline.side2, temp);
        temp = embVector_add(temp, lines->geometry[i].object.vector);
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

    embArray_addVector(result->side1, outline.side1->geometry[0].object.vector);
    embArray_addVector(result->side2, outline.side2->geometry[0].object.vector);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.start = outline.side1->geometry[i - 3].object.vector;
        line1.end = outline.side1->geometry[i - 2].object.vector;
        line2.start = outline.side1->geometry[i - 1].object.vector;
        line2.end = outline.side1->geometry[i].object.vector;
        out = embLine_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        embArray_addVector(result->side1, out);

        line1.start = outline.side2->geometry[i - 3].object.vector;
        line1.end = outline.side2->geometry[i - 2].object.vector;
        line2.start = outline.side2->geometry[i - 1].object.vector;
        line2.end = outline.side2->geometry[i].object.vector;
        out = embLine_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        embArray_addVector(result->side2, out);
    }

    embArray_addVector(result->side1, outline.side1->geometry[2 * lines->count - 3].object.vector);
    embArray_addVector(result->side2, outline.side2->geometry[2 * lines->count - 3].object.vector);
    result->length = lines->count;
}

/**
 * @brief 
 * 
 * \a result 
 * \a density 
 * @return EmbArray* 
 */
EmbArray*
embSatinOutline_renderStitches(EmbSatinOutline* result, EmbReal density)
{
    int i, j;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;
    int numberOfSteps;
    EmbReal midLength;

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_renderStitches(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            EmbGeometry *g10 = &(result->side1->geometry[j+0]);
            EmbGeometry *g11 = &(result->side1->geometry[j+1]);
            EmbGeometry *g20 = &(result->side2->geometry[j+0]);
            EmbGeometry *g21 = &(result->side2->geometry[j+1]);
            topDiff = embVector_subtract(g10->object.vector, g11->object.vector);
            bottomDiff = embVector_subtract(g21->object.vector, g20->object.vector);

            midLeft = embVector_average(g10->object.vector, g20->object.vector);
            midRight = embVector_average(g11->object.vector, g21->object.vector);

            midDiff = embVector_subtract(midLeft, midRight);
            midLength = embVector_length(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            embVector_multiply(topDiff, 1.0/numberOfSteps, &topStep);
            embVector_multiply(bottomDiff, 1.0/numberOfSteps, &bottomStep);
            currTop = g10->object.vector;
            currBottom = g20->object.vector;

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = embArray_create(EMB_VECTOR);
                }
                embArray_addVector(stitches, currTop);
                embArray_addVector(stitches, currBottom);
                currTop = embVector_add(currTop, topStep);
                currBottom = embVector_add(currBottom, bottomStep);
            }
        }
        embArray_addVector(stitches, currTop);
        embArray_addVector(stitches, currBottom);
    }
    return stitches;
}

/**
 * @brief 
 * 
 * \a file 
 * \a x 
 */
void
write_24bit(FILE* file, int x)
{
    unsigned char a[4];
    a[0] = (unsigned char)0;
    a[1] = (unsigned char)(x & 0xFF);
    a[2] = (unsigned char)((x >> 8) & 0xFF);
    a[3] = (unsigned char)((x >> 16) & 0xFF);
    fwrite(a, 1, 4, file);
}

/**
 * @brief 
 * 
 * \a a 
 * \a b 
 * @return int 
 */
int
embColor_distance(EmbColor a, EmbColor b)
{
    int t;
    t = (a.r-b.r)*(a.r-b.r);
    t += (a.g-b.g)*(a.g-b.g);
    t += (a.b-b.b)*(a.b-b.b);
    return t;
}

/**
 * @brief 
 * 
 * \a f 
 * \a c 
 * \a toRead 
 */
void
embColor_read(FILE *f, EmbColor *c, int toRead)
{
    unsigned char b[4];
    fread(b, 1, toRead, f);
    c->r = b[0];
    c->g = b[1];
    c->b = b[2];
}

/**
 * @brief 
 * 
 * \a f 
 * \a c 
 * \a toWrite 
 */
void
embColor_write(FILE *f, EmbColor c, int toWrite)
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
 * \a color  The EmbColor color to match.
 * \a colors The EmbThreadList pointer to start the search at.
 * \a mode   Is the argument an array of threads (0) or colors (1)?
 * @return closestIndex The entry in the ThreadList that matches.
 */
int
embThread_findNearestColor(EmbColor color, EmbColor *color_list, int n_colors)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    for (i = 0; i < n_colors; i++) {
        int delta = embColor_distance(color, color_list[i]);

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

/**
 * @brief 
 * 
 * \a color 
 * \a thread_list 
 * \a n_threads 
 * @return int 
 */
int
embThread_findNearestThread(EmbColor color, EmbThread *thread_list, int n_threads)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    for (i = 0; i < n_threads; i++) {
        int delta = embColor_distance(color, thread_list[i].color);

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
EmbThread
embThread_getRandom(void)
{
    EmbThread c;
    c.color.r = rand()%256;
    c.color.g = rand()%256;
    c.color.b = rand()%256;
    strcpy(c.description, "random");
    strcpy(c.catalogNumber, "");
    return c;
}

/**
 * @brief 
 * 
 * \a file 
 * \a buffer 
 * \a maxLength 
 */
void
binaryReadString(FILE* file, char* buffer, int maxLength)
{
    int i = 0;
    while(i < maxLength) {
        buffer[i] = (char)fgetc(file);
        if (buffer[i] == '\0') break;
        i++;
    }
}

/**
 * @brief 
 * 
 * \a file 
 * \a buffer 
 * \a stringLength 
 */
void
binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength)
{
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
int
stringInArray(const char *s, const char **array)
{
    int i;
    for (i = 0; strlen(array[i]); i++) {
        if (!strcmp(s, array[i])) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief 
 * 
 * \a file 
 * \a line 
 * \a maxLength 
 * @return int 
 */
int
emb_readline(FILE* file, char *line, int maxLength)
{
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

/**
 * @brief Get the trim bounds object
 * 
 * \a s 
 * \a firstWord 
 * \a trailingSpace 
 */
void
get_trim_bounds(char const *s, char const **firstWord, char const **trailingSpace)
{
    char const* lastWord = 0;
    *firstWord = lastWord = s + strspn(s, WHITESPACE);
    do {
        *trailingSpace = lastWord + strcspn(lastWord, WHITESPACE);
        lastWord = *trailingSpace + strspn(*trailingSpace, WHITESPACE);
    } while (*lastWord != '\0');
}

/**
 * @brief 
 * 
 * \a s 
 * @return char* 
 *
 * \todo decription
 */
char*
copy_trim(char const *s)
{
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

/**
 * @brief Optimizes the number (\a num) for output to a text file and returns it as a string (\a str).
 * 
 * \a num 
 * \a str 
 * @return char* 
 */
char*
emb_optOut(EmbReal num, char* str)
{
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

/**
 * @brief 
 * 
 * \a t 
 */
void
embTime_initNow(EmbTime* t)
{
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

/**
 * @brief 
 * 
 * \a t 
 * @return EmbTime 
 */
EmbTime
embTime_time(EmbTime* t)
{
#ifdef ARDUINO
/*TODO: arduino embTime_time */
#else

int divideByZero = 0;
divideByZero = divideByZero/divideByZero; /*TODO: wrap time() from time.h and verify it works consistently */

#endif /* ARDUINO */
    return *t;
}

#ifdef LIBEMBROIDERY_CLI

/**
 * @brief 
 * 
 * \a result 
 * \a label 
 */
void
report(int result, char *label)
{
    printf("%s Test...%*c", label, (int)(20-strlen(label)), ' ');
    if (result) {
        printf(RED_TERM_COLOR "[FAIL] [CODE=%d]\n" RESET_TERM_COLOR, result);
    }
    else {
        printf(GREEN_TERM_COLOR "[PASS]\n" RESET_TERM_COLOR);
    }
}

/**
 * @brief 
 * 
 * \a level 
 */
void
testMain(int level)
{
    EmbPattern *pattern = embPattern_create();
    int overall = 0;
    int circleResult = testEmbCircle();
    int threadResult = testThreadColor();
    int formatResult = testEmbFormat();
    int arcResult = testGeomArc();
    int create1Result = create_test_file_1("test01.csv");
    int create2Result = create_test_file_2("test02.csv");
    int create3Result = create_test_file_3("test03.csv");
    int svg1Result = convert("test01.csv", "test01.svg");
    int svg2Result = convert("test02.csv", "test02.svg");
    int svg3Result = convert("test03.csv", "test03.svg");
    int dst1Result = convert("test01.csv", "test01.dst");
    int dst2Result = convert("test02.csv", "test02.dst");
    int dst3Result = convert("test03.csv", "test03.dst");
    int hilbertCurveResult = hilbert_curve(pattern, 3);
    int renderResult = embPattern_render(pattern, "hilbert_level_3.png");
    int simulateResult = embPattern_simulate(pattern, "hilbert_level_3.avi");

    overall += circleResult;
    overall += threadResult;
    overall += formatResult;
    overall += arcResult;
    overall += create1Result;
    overall += create2Result;
    overall += create3Result;
    overall += svg1Result;
    overall += svg2Result;
    overall += svg3Result;
    overall += dst1Result;
    overall += dst2Result;
    overall += dst3Result;

    if (emb_verbose >= 0) {
        puts("SUMMARY OF RESULTS");
        puts("------------------");
        report(circleResult, "Tangent Point");
        report(threadResult, "Thread");
        report(formatResult, "Format");
        report(arcResult, "Arc");
        report(create1Result, "Create CSV 1");
        report(create2Result, "Create CSV 2");
        report(create3Result, "Create CSV 3");
        report(svg1Result, "Convert CSV-SVG 1");
        report(svg2Result, "Convert CSV-SVG 2");
        report(svg3Result, "Convert CSV-SVG 3");
        report(dst1Result, "Convert CSV-DST 1");
        report(dst2Result, "Convert CSV-DST 2");
        report(dst3Result, "Convert CSV-DST 3");
        report(hilbertCurveResult, "Generating Hilbert Curve");
        report(renderResult, "Rendering Hilbert Curve");
        report(simulateResult, "Simulating Hilbert Curve");
    }
    
    embPattern_free(pattern);
    if (level > 0) {
        puts("More expensive tests.");
        full_test_matrix("test_matrix.txt");
    }
    if (overall == 0) {
        puts("PASS");
    }
    else {
        puts("FAIL");
    }
}

/**
 * @brief 
 * 
 * \a c 
 * \a p 
 * \a t0 
 * \a t1 
 */
void
testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1)
{
    emb_error = 0;
    t0->x = 0.0;
    t0->y = 0.0;
    t1->x = 0.0;
    t1->y = 0.0;
    if (!getCircleTangentPoints(c, p, t0, t1)) {
        printf("Error calculating tangent points.\n");
        emb_error = 1;
    }
    else {
        if (emb_verbose > 0) {
            printf("Circle : cr=%f, cx=%f, cy=%f\n"
               "Point  : px=%f, py=%f\n"
               "Tangent: tx0=%f, ty0=%f\n"
               "Tangent: tx1=%f, ty1=%f\n\n",
               c.radius, c.center.x, c.center.y,
               p.x, p.y,
               t0->x, t0->y,
               t1->x, t1->y);
        }
    }
}

/**
 * @brief 
 * 
 * @return int 
 *
 * \todo decription
 * \todo move to circle.c
 */
int
testEmbCircle(void)
{
    EmbReal error;
    EmbReal epsilon = 1e-3;
    EmbVector p0, p1;
    /* Problem */
    EmbCircle c1 = {{0.0, 0.0}, 3.0};
    /* Solution */
    EmbVector t0 = {2.2500, 1.9843};
    EmbVector t1 = {2.2500, -1.9843};
    EmbVector p = {4.0, 0.0};
    /* Test */
    testTangentPoints(c1, p, &p0, &p1);
    error = embVector_distance(p0, t0) + embVector_distance(p1, t1);
    if (error > epsilon) {
        printf("Error larger than tolerance, circle test 1: %f.\n\n", error);
        return 16;
    }

    return 0;
}

/**
 * @brief 
 * 
 * @return int 
 */
int testEmbCircle_2(void) {
    EmbReal error;
    EmbReal epsilon = 1e-3;
    EmbVector p0, p1;
    EmbCircle c2 = {{20.1762, 10.7170}, 6.8221};
    /* Solution */
    EmbVector s0 = {19.0911, 17.4522};
    EmbVector s1 = {26.4428, 13.4133};
    EmbVector p = {24.3411, 18.2980};
    /* Test */
    testTangentPoints(c2, p, &p0, &p1);
    error = embVector_distance(p0, s0) + embVector_distance(p1, s1);
    if (error > epsilon) {
        printf("Error larger than tolerance, circle test 2: %f.\n\n", error);
        return 17;
    }

    return 0;
}

/**
 * @brief 
 * 
 * \a bulge 
 * \a arc 
 * \a centerX 
 * \a centerY 
 * \a radius 
 * \a diameter 
 * \a chord 
 * \a chordMidX 
 * \a chordMidY 
 * \a sagitta 
 * \a apothem 
 * \a incAngle 
 * \a clockwise 
 */
void
printArcResults(EmbReal bulge, EmbArc arc,
                     EmbReal centerX,   EmbReal centerY,
                     EmbReal radius,    EmbReal diameter,
                     EmbReal chord,
                     EmbReal chordMidX, EmbReal chordMidY,
                     EmbReal sagitta,   EmbReal apothem,
                     EmbReal incAngle,  char   clockwise)
{
    fprintf(stdout, "bulge     = %f\n"
                    "startX    = %f\n"
                    "startY    = %f\n"
                    "endX      = %f\n"
                    "endY      = %f\n"
                    "midX      = %f\n"
                    "midY      = %f\n"
                    "centerX   = %f\n"
                    "centerY   = %f\n"
                    "radius    = %f\n"
                    "diameter  = %f\n"
                    "chord     = %f\n"
                    "chordMidX = %f\n"
                    "chordMidY = %f\n"
                    "sagitta   = %f\n"
                    "apothem   = %f\n"
                    "incAngle  = %f\n"
                    "clockwise = %d\n"
                    "\n",
                    bulge,
                    arc.start.x,
                    arc.start.y,
                    arc.end.x,
                    arc.end.y,
                    arc.mid.x,
                    arc.mid.y,
                    centerX,
                    centerY,
                    radius,
                    diameter,
                    chord,
                    chordMidX,
                    chordMidY,
                    sagitta,
                    apothem,
                    incAngle,
                    clockwise);
}

/**
 * @brief 
 * 
 * @return int 
 */
int
testGeomArc(void)
{
    EmbArc arc;
    EmbVector center, chordMid;
    EmbReal bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    char clockwise;

    bulge = -0.414213562373095;
    arc.start.x = 1.0;
    arc.start.y = 0.0;
    arc.end.x   = 2.0;
    arc.end.y   = 1.0;
    if (getArcDataFromBulge(bulge, &arc,
                           &(center.x),   &(center.y),
                           &radius,    &diameter,
                           &chord,
                           &(chordMid.x), &(chordMid.y),
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise)) {
        if (emb_verbose > 0) {
            fprintf(stdout, "Clockwise Test:\n");
            printArcResults(bulge, arc, center.x, center.y,
                        radius, diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
        }
    }

    bulge  = 2.414213562373095;
    arc.start.x = 4.0;
    arc.start.y = 0.0;
    arc.end.x   = 5.0;
    arc.end.y   = 1.0;
    if (getArcDataFromBulge(bulge, &arc,
                           &(center.x),   &(center.y),
                           &radius,    &diameter,
                           &chord,
                           &(chordMid.x), &(chordMid.y),
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise)) {
        if (emb_verbose > 0) {
            fprintf(stdout, "Counter-Clockwise Test:\n");
            printArcResults(bulge, arc, center.x, center.y,
                        radius,    diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
        }
    }

    return 0;
}

/**
 * @brief 
 * 
 * @return int 
 */
int
testThreadColor(void)
{
    unsigned int tColor = 0xFFD25F00;
    int          tBrand = Sulky_Rayon;
    int          tNum   = threadColorNum(tColor, tBrand);
    const char*  tName  = threadColorName(tColor, tBrand);

    if (emb_verbose > 0) {
        printf("Color : 0x%X\n"
           "Brand : %d\n"
           "Num   : %d\n"
           "Name  : %s\n\n",
            tColor,
            tBrand,
            tNum, /* Solution: 1833 */
            tName); /* Solution: Pumpkin Pie */
    }
    return 0;
}

/**
 * @brief 
 * 
 * @return int 
 */
int
testEmbFormat(void)
{
    const char*  tName = "example.zsk";
    int format = emb_identify_format(tName);

    if (emb_verbose > 0) {
        printf("Filename   : %s\n"
           "Extension  : %s\n"
           "Description: %s\n"
           "Reader     : %c\n"
           "Writer     : %c\n"
           "Type       : %d\n\n",
            tName,
            formatTable[format].extension,
            formatTable[format].description,
            formatTable[format].reader_state,
            formatTable[format].writer_state,
            formatTable[format].type);
    }

    if (strcmp(formatTable[format].extension, ".zsk")) return 20;
    if (strcmp(formatTable[format].description, "ZSK USA Embroidery Format")) {
            return 21;
    }
    if (formatTable[format].reader_state != 'U') return 22;
    if (formatTable[format].writer_state != ' ') return 23;
    if (formatTable[format].type != 1) return 24;
    return 0;
}

/**
 * @brief Create a test file 1 object
 * 
 * \a outf 
 * @return int 
 */
int
create_test_file_1(const char* outf)
{
    int i;
    EmbPattern* p;
    EmbStitch st;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    /* 10mm circle */
    for (i = 0; i < 20; i++) {
        embPattern_addStitchRel(p, 0.0, 1.0, JUMP, 0);
    }
    for (i = 0; i < 200; i++) {
        st.x = 10 + 10 * sin(i * (0.03141592));
        st.y = 10 + 10 * cos(i * (0.03141592));
        st.flags = NORMAL;
        st.color = 0;
        embPattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
    }

    embPattern_addThread(p, black_thread);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}

/**
 * @brief Create a test file 2 object
 * 
 * \a outf 
 * @return int 
 */
int
create_test_file_2(const char* outf)
{
    int i;
    EmbPattern* p;
    EmbStitch st;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    /* sin wave */
    for (i = 0; i < 100; i++) {
        st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
        st.y = 10 + i * 0.1;
        st.flags = NORMAL;
        st.color = 0;
        embPattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
    }

    embPattern_addThread(p, black_thread);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}

/**
 * @brief Create a test file 3 object
 * 
 * \a outf 
 * @return int 
 */
int
create_test_file_3(const char* outf)
{
    EmbPattern* p;
    EmbCircle circle;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    circle.center.x = 10.0;
    circle.center.y = 1.0;
    circle.radius = 5.0;
    embPattern_addCircleAbs(p, circle);

    embPattern_addThread(p, black_thread);
    embPattern_convertGeometry(p);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}


/* TODO: Add capability for converting multiple files of various types to a single format. 
Currently, we only convert a single file to multiple formats. */
#if 0

/**
 * @brief 
 * 
 * @return int 
 */
int
testThreadColor(void)
{
    unsigned int tColor = 0xFFD25F00;
    EmbColor c;
    c.r = 0xD2;
    c.g = 0x5F;
    c.b = 0x00;
    int tBrand = Sulky_Rayon;
    int tNum = threadColorNum(c, tBrand);
    char tName[50];
    threadColorName(tName, c, tBrand);

    printf("Color : 0x%X\n"
           "Brand : %d\n"
           "Num   : %d\n"
           "Name  : %s\n\n",
        tColor,
        tBrand,
        tNum, /* Solution: 1833 */
        tName); /* Solution: Pumpkin Pie */
    return 0;
}
#endif

/*
 * Table of from/to for formats. What conversions after a from A to B conversion
 * leave a file with the same render?
 *
 * Add command "--full-test-suite" for this full matrix.
 */

/**
 * @brief 
 * 
 * \a fname 
 * @return int 
 */
int
full_test_matrix(char *fname)
{
    int i, j, success, ntests;
    FILE *f;
    f = fopen(fname, "wb");
    if (!f) {
        puts("ERROR: full_test_matrix(fname) failed to open file.");
        return 1;
    }

    success = 0;
    ntests = (numberOfFormats - 1)*(numberOfFormats - 5);
    for (i = 0; i < numberOfFormats; i++) {
        char fname[100];
        if (formatTable[i].color_only) {
            continue;
        }
        strcpy(fname, "test01");
        strcat(fname, formatTable[i].extension);
        create_test_file_1(fname);
        for (j=0; j < numberOfFormats; j++) {
            EmbPattern *pattern = 0;
            char fname_converted[100];
            char fname_image[100];
            int result;
            strcpy(fname_converted, "test01_");
            strcat(fname_converted, formatTable[i].extension+1);
            strcat(fname_converted, formatTable[j].extension);
            strcpy(fname_image, "test01_");
            strcat(fname_image, formatTable[i].extension+1);
            strcat(fname_image, "_");
            strcat(fname_image, formatTable[j].extension+1);
            strcat(fname_image, ".ppm");
            printf("Attempting: %s %s\n", fname, fname_converted);
            result = convert(fname, fname_converted);
            embPattern_readAuto(pattern, fname_converted);
            embPattern_render(pattern, fname_image);
            embPattern_free(pattern);
            fprintf(f, "%d %d %f%% ", i, j, 100*success/(1.0*ntests));
            if (!result) {
                fprintf(f, "PASS\n");
                success++;
            } else {
                fprintf(f, "FAIL\n");
            }
        }
    }

    fclose(f);
    return 0;
}

/**
 * @brief 
 * 
 */
void
usage(void)
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
    puts("    -r, --render     Create an image in PNG format of what the embroidery should look like.");
    puts("    -s, --satin      Fill the current geometry with satin stitches according");
    puts("                     to the defined algorithm.");
    puts("    -S, --stitch     Add a stitch defined by the arguments given to the current pattern.");
    puts("");
    puts("Quality Assurance:");
    puts("        --test       Run the basic test suite.");
    puts("        --full-test-suite  Run all tests, even those we expect to fail.");
}

/**
 * @brief 
 * 
 */
void
formats(void)
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

/**
 * @brief 
 * 
 * \a argv 
 * \a argc 
 * \a i 
 */
void
to_flag(char **argv, int argc, int i)
{
    if (i + 2 < argc) {
        int j;
        char output_fname[100];
        int format;
        sprintf(output_fname, "example.%s", argv[i+1]);
        format = emb_identify_format(output_fname);
        if (format < 0) {
            puts("Error: format unrecognised.");
        }
        for (j=i+2; j<argc; j++) {
            int length = strlen(argv[j]);
            output_fname[0] = 0;
            strcpy(output_fname, argv[j]);
            output_fname[length-4] = 0;
            strcat(output_fname, formatTable[format].extension);
            printf("Converting %s to %s.\n",
                argv[j], output_fname);
            convert(argv[j], output_fname);
        }
    }
    else {
        puts("Usage of the to flag is:");
        puts("    embroider -t FORMAT FILE(S)");
        puts("but it appears you entered less than 3 arguments to embroider.");
    }
}

/* TODO: Add capability for converting multiple files of various types to a single format. Currently, we only convert a single file to multiple formats. */

/**
 * @brief 
 * 
 * \a argc 
 * \a argv 
 * @return int 
 */
int
command_line_interface(int argc, char* argv[])
{
    EmbPattern *current_pattern = embPattern_create();
    int i, j, flags, result;
    if (argc == 1) {
        usage();
        return 0;
    }

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
        case FLAG_TO_SHORT:
            to_flag(argv, argc, i);
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
            if (i + 3 < argc) {
                EmbImage image;
                /* the user appears to have entered the needed arguments */
                i++;
                /* to stb command */
                image = embImage_create(2000, 2000);
                embImage_read(&image, argv[i]);
                i++;
                embPattern_horizontal_fill(current_pattern, &image, atoi(argv[i]));
                embImage_free(&image);
                i++;
                embPattern_writeAuto(current_pattern, argv[i]);
            }
            break;
        case FLAG_RENDER:
        case FLAG_RENDER_SHORT:
            if (i + 2 < argc) {
                /* the user appears to have entered filenames after render */
                embPattern_readAuto(current_pattern, argv[i+1]);
                printf("%d\n", current_pattern->stitch_list->count);
                embPattern_render(current_pattern, argv[i+2]);
                i += 2;
                break;
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.png'.");
                    embPattern_render(current_pattern, "output.png");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    embPattern_render(current_pattern, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.png'.");
                embPattern_render(current_pattern, "output.png");
            }
            break;
        case FLAG_SIMULATE:
            if (i + 1 < argc) {
                /* the user appears to have entered a filename after render */
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.avi'.");
                    embPattern_simulate(current_pattern, "output.avi");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    embPattern_simulate(current_pattern, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.avi'.");
                embPattern_simulate(current_pattern, "output.avi");
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
        case FLAG_CROSS_STITCH:
            if (i + 3 < argc) {
                EmbImage image;
                /* the user appears to have entered the needed arguments */
                image = embImage_create(2000, 2000);
                i++;
                /* to stb command */
                embImage_read(&image, argv[i]);
                i++;
                embPattern_crossstitch(current_pattern, &image, atoi(argv[i]));
                embImage_free(&image);
                i++;
                embPattern_writeAuto(current_pattern, argv[i]);
            }
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

/**
 * @brief 
 * 
 * \a argc 
 * \a argv 
 * @return int 
 */
int main(int argc, char* argv[])
{
    return command_line_interface(argc, argv);
}
#endif

