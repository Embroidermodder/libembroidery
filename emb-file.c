#include "embroidery.h"
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct reader_writer_prototype {
    char file_ext[10];
    int (*reader)(EmbPattern*, const char*);
    int (*writer)(EmbPattern*, const char*);
} reader_writer_proto;

reader_writer_proto file_type_list[] = {
    {".10o", read10o, write10o},
    {".100", read100, write100},
    {".art", readArt, writeArt},
    {".bmc", readBmc, writeBmc},
    {".bro", readBro, writeBro},
    {".cnd", readCnd, writeCnd},
    {".col", readCol, writeCol},
    {".csd", readCsd, writeCsd},
    {".csv", readCsv, writeCsv},
    {".dat", readDat, writeDat},
    {".dem", readDem, writeDem},
    {".dsb", readDsb, writeDsb},
    {".dst", readDst, writeDst},
    {".dsz", readDsz, writeDsz},
    {".dxf", readDxf, writeDxf},
    {".edr", readEdr, writeEdr},
    {".emd", readEmd, writeEmd},
    {".exp", readExp, writeExp},
    {".exy", readExy, writeExy},
    {".eys", readEys, writeEys},
    {".fxy", readFxy, writeFxy},
    {".gc", readGc, writeGc},
    {".gnc", readGnc, writeGnc},
    {".gt", readGt, writeGt},
    {".hus", readHus, writeHus},
    {".inb", readInb, writeInb},
    {".inf", readInf, writeInf},
    {".jef", readJef, writeJef},
    {".ksm", readKsm, writeKsm},
    {".max", readMax, writeMax},
    {".mit", readMit, writeMit},
    {".new", readNew, writeNew},
    {".ofm", readOfm, writeOfm},
    {".pcd", readPcd, writePcd},
    {".pcm", readPcm, writePcm},
    {".pcq", readPcq, writePcq},
    {".pcs", readPcs, writePcs},
    {".pec", readPec, writePec},
    {".pel", readPel, writePel},
    {".pem", readPem, writePem},
    {".pes", readPes, writePes},
    {".phb", readPhb, writePhb},
    {".phc", readPhc, writePhc},
    {".plt", readPlt, writePlt},
    {".rgb", readRgb, writeRgb},
    {".sew", readSew, writeSew},
    {".shv", readShv, writeShv},
    {".sst", readSst, writeSst},
    {".stx", readStx, writeStx},
    {".svg", readSvg, writeSvg},
    {".t01", readT01, writeT01},
    {".t09", readT09, writeT09},
    {".tap", readTap, writeTap},
    {".thr", readThr, writeThr},
    {".txt", readTxt, writeTxt},
    {".u00", readU00, writeU00},
    {".u01", readU01, writeU01},
    {".vip", readVip, writeVip},
    {".vp3", readVp3, writeVp3},
    {".xxx", readXxx, writeXxx},
    {".zsk", readZsk, writeZsk},
    {"END", 0, 0}
};

/* TODO: This list needs reviewed in case some stitch formats also can contain object data (EMBFORMAT_STCHANDOBJ). */

EmbFormatList formatTable[100] = {
    {".10o", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY},
    {".100", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY},
    {".art", "Bernina Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".bmc", "Bitmap Cache Embroidery Format",     ' ', ' ', EMBFORMAT_STITCHONLY},
    {".bro", "Bits & Volts Embroidery Format",     'U', ' ', EMBFORMAT_STITCHONLY},
    {".cnd", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY},
    {".col", "Embroidery Thread Color Format",     'U', 'U', EMBFORMAT_STITCHONLY},
    {".csd", "Singer Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY},
    {".csv", "Comma Separated Values Format",      'U', 'U', EMBFORMAT_STITCHONLY},
    {".dat", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".dem", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY},
    {".dsb", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".dst", "Tajima Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".dsz", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".dxf", "Drawing Exchange Format",            ' ', ' ', EMBFORMAT_OBJECTONLY},
    {".edr", "Embird Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".emd", "Elna Embroidery Format",             'U', ' ', EMBFORMAT_STITCHONLY},
    {".exp", "Melco Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".exy", "Eltac Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".eys", "Sierra Expanded Embroidery Format",  ' ', ' ', EMBFORMAT_STITCHONLY},
    {".fxy", "Fortron Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".gc",  "Smoothie G-Code Format",             ' ', ' ', EMBFORMAT_STITCHONLY},
    {".gnc", "Great Notions Embroidery Format",    ' ', ' ', EMBFORMAT_STITCHONLY},
    {".gt",  "Gold Thread Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY},
    {".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY},
    {".inb", "Inbro Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".inf", "Embroidery Color Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".jef", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".ksm", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".max", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".mit", "Mitsubishi Embroidery Format",       'U', ' ', EMBFORMAT_STITCHONLY},
    {".new", "Ameco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".ofm", "Melco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".pcd", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".pcm", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".pcq", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".pcs", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".pec", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY},
    {".pel", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".pem", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".pes", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY},
    {".phb", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".phc", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".plt", "AutoCAD Plot Drawing Format",        'U', 'U', EMBFORMAT_STITCHONLY},
    {".rgb", "RGB Embroidery Format",              'U', 'U', EMBFORMAT_STITCHONLY},
    {".sew", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY},
    {".sst", "Sunstar Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".stx", "Data Stitch Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY},
    {".svg", "Scalable Vector Graphics",           'U', 'U', EMBFORMAT_OBJECTONLY},
    {".t01", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".t09", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".tap", "Happy Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".thr", "ThredWorks Embroidery Format",       'U', 'U', EMBFORMAT_STITCHONLY},
    {".txt", "Text File",                          ' ', 'U', EMBFORMAT_STITCHONLY},
    {".u00", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".u01", "Barudan Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".vip", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".vp3", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".xxx", "Singer Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".zsk", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {"END",  "END",                                ' ', ' ', 0,                  }
};

int numberOfFormats = 61;
const unsigned int NumberOfDifatEntriesInHeader = 109;
const unsigned int sizeOfFatEntry = sizeof(unsigned int);
static const unsigned int sizeOfDifatEntry = 4;
static const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
static const unsigned int sizeOfDirectoryEntry = 128;
static const int supportedMinorVersion = 0x003E;
static const int littleEndianByteOrderMark = 0xFFFE;

/**
 * Argument validator and stitchList checker.
 * Saves making these 4 checks seperately for every file type.
 */
int validateWritePattern(EmbPattern *pattern, const char* fileName, const char *function)
{
    if (!pattern) {
        embLog_error("%s(), pattern argument is null\n", function);
        return 0;
    }
    if (!fileName) {
        embLog_error("%s(), fileName argument is null\n", function);
        return 0;
    }

    if (!pattern->stitchList) {
        embLog_error("%s(), pattern contains no stitches\n", function);
        return 0;
    }

    if (!pattern->stitchList->count) {
        embLog_error("%s(), pattern contains no stitches\n", function);
        return 0;
    }

    embPattern_end(pattern);

    return 1;
}

/**
 * Argument validator for reading patterns.
 */
int validateReadPattern(EmbPattern *pattern, const char* fileName, const char *function)
{
    if (!pattern) {
        embLog_error("%s(), pattern argument is null\n", function);
        return 0;
    }
    if (!fileName) {
        embLog_error("%s(), fileName argument is null\n", function);
        return 0;
    }
    return 1;
}

EmbFile* embFile_open(const char* fileName, const char* mode, int optional)
{
#ifdef ARDUINO
    return inoFile_open(fileName, mode);
#else
    EmbFile* eFile = 0;
    FILE* oFile = fopen(fileName, mode);
    if (!oFile) {
        if (!optional) {
            embLog_error("Cannot open %s in mode %s.", fileName, mode);
        }
        return 0;
    }

    eFile = (EmbFile*)malloc(sizeof(EmbFile));
    if (!eFile) {
        if (!optional) {
            embLog_error("Cannot allocate memory for EmbFile with arguments (%s, %s, 0).",
                fileName, mode);
        }
        fclose(oFile);
        return 0;
    }

    eFile->file = oFile;
    return eFile;
#endif
}

int embFile_close(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_close(stream);
#else /* ARDUINO */
    int retVal = fclose(stream->file);
    free(stream);
    stream = 0;
    return retVal;
#endif /* ARDUINO */
}

int embFile_eof(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_eof(stream);
#else /* ARDUINO */
    return feof(stream->file);
#endif /* ARDUINO */
}

char embFile_getc(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_getc(stream);
#else /* ARDUINO */
    return fgetc(stream->file);
#endif /* ARDUINO */
}

void embFile_readline(EmbFile* stream, char *line, int maxLength)
{
    int state = 0, i;
    char c;
    for (i=0; i<maxLength-1; i++) {
        c = embFile_getc(stream);
        if (embFile_eof(stream)) {
            break;
        }
        if (c == '\r') {
            c = embFile_getc(stream);
            if (c != '\n') {
                embFile_seek(stream, -1L, SEEK_CUR);
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
}

/**
 * In order to remove uses of printf (which use more memory and variable
 * arguments which is bad for embedded systems) call this instead whenever
 * possible.
 *
 * Note that fputs does not append a \n like puts does.
 */
int embFile_puts(EmbFile* stream, char *buff)
{
#ifdef ARDUINO
    return inoFile_printf(stream, buff);
#else /* ARDUINO */
    return fputs(buff, stream->file);
#endif /* ARDUINO */
}

size_t embFile_read(void* ptr, size_t size, size_t nmemb, EmbFile* stream)
{
#ifdef ARDUINO
    /* ARDUINO TODO: SD File read() doesn't appear to return the same way as fread(). This will need work. */
    return 0;
#else /* ARDUINO */
    return fread(ptr, size, nmemb, stream->file);
#endif /* ARDUINO */
}

size_t embFile_write(const void* ptr, size_t size, size_t nmemb, EmbFile* stream)
{
#ifdef ARDUINO
    return 0; /* ARDUINO TODO: Implement inoFile_write. */
#else /* ARDUINO */
    return fwrite(ptr, size, nmemb, stream->file);
#endif /* ARDUINO */
}

int embFile_seek(EmbFile* stream, long offset, int origin)
{
#ifdef ARDUINO
    return inoFile_seek(stream, offset, origin);
#else /* ARDUINO */
    return fseek(stream->file, offset, origin);
#endif /* ARDUINO */
}

long embFile_tell(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_tell(stream);
#else /* ARDUINO */
    return ftell(stream->file);
#endif /* ARDUINO */
}

EmbFile* embFile_tmpfile(void)
{
#ifdef ARDUINO
    return inoFile_tmpfile();
#else
    EmbFile* eFile = 0;
    FILE* tFile = tmpfile();
    if (!tFile)
        return 0;

    eFile = (EmbFile*)malloc(sizeof(EmbFile));
    if (!eFile) {
        fclose(tFile);
        return 0;
    }

    eFile->file = tFile;
    return eFile;
#endif
}

int embFile_putc(int ch, EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_putc(ch, stream);
#else /* ARDUINO */
    return fputc(ch, stream->file);
#endif /* ARDUINO */
}

int embFile_printf(EmbFile* stream, const char* format, ...)
{
#ifdef ARDUINO /* ARDUINO */
    char buff[256];
    va_list args;
    va_start(args, format);
    vsprintf(buff, format, args);
    va_end(args);
    return inoFile_printf(stream, buff);
#else /* ARDUINO */
    int retVal;
    va_list args;
    va_start(args, format);
    retVal = vfprintf(stream->file, format, args);
    va_end(args);
    return retVal;
#endif /* ARDUINO */
}

static unsigned int sectorSize(bcf_file* bcfFile)
{
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    } else if (bcfFile->header.majorVersion == 4) {
        return 4096;
    }
    return 4096;
}

static int haveExtraDIFATSectors(bcf_file* file)
{
    return (int)(numberOfEntriesInDifatSector(file->difat) > 0);
}

static int seekToOffset(EmbFile* file, const unsigned int offset)
{
    return embFile_seek(file, offset, SEEK_SET);
}

static int seekToSector(bcf_file* bcfFile, EmbFile* file, const unsigned int sector)
{
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return seekToOffset(file, offset);
}

static void parseDIFATSectors(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int numberOfDifatEntriesStillToRead = bcfFile->header.numberOfFATSectors - NumberOfDifatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &numberOfDifatEntriesStillToRead);
    }
}

int bcfFile_read(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int i, numberOfDirectoryEntriesPerSector, directorySectorToReadFrom;

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

EmbFile* GetFile(bcf_file* bcfFile, EmbFile* file, char* fileToFind)
{
    int filesize, sectorSize, currentSector, sizeToWrite, currentSize, totalSectors, i;
    char* input = 0;
    EmbFile* fileOut = embFile_tmpfile();
    bcf_directory_entry* pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (strcmp(fileToFind, pointer->directoryEntryName) == 0)
            break;
        pointer = pointer->next;
    }
    filesize = pointer->streamSize;
    sectorSize = bcfFile->difat->sectorSize;
    input = (char*)malloc(sectorSize);
    if (!input) {
        embLog_error("compound-file.c GetFile(), cannot allocate memory for input\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    currentSize = 0;
    currentSector = pointer->startingSectorLocation;
    totalSectors = (int)ceil((float)filesize / sectorSize);
    for (i = 0; i < totalSectors; i++) {
        seekToSector(bcfFile, file, currentSector);
        sizeToWrite = filesize - currentSize;
        if (sectorSize < sizeToWrite) {
            sizeToWrite = sectorSize;
        }
        embFile_read(input, 1, sizeToWrite, file);
        embFile_write(input, 1, sizeToWrite, fileOut);
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    free(input);
    input = 0;
    return fileOut;
}

void bcf_file_free(bcf_file* bcfFile)
{
    bcf_file_difat_free(bcfFile->difat);
    bcfFile->difat = 0;
    bcf_file_fat_free(bcfFile->fat);
    bcfFile->fat = 0;
    bcf_directory_free(bcfFile->directory);
    bcfFile->directory = 0;
    free(bcfFile);
    bcfFile = 0;
}

bcf_file_difat* bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize)
{
    unsigned int i;
    bcf_file_difat* difat = 0;
    unsigned int sectorRef;

    difat = (bcf_file_difat*)malloc(sizeof(bcf_file_difat));
    if (!difat) {
        embLog_error("compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat\n");
    } /* TODO: avoid crashing. null pointer will be accessed */

    difat->sectorSize = sectorSize;
    if (fatSectors > NumberOfDifatEntriesInHeader) {
        fatSectors = NumberOfDifatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        sectorRef = binaryReadUInt32(file);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < NumberOfDifatEntriesInHeader; ++i) {
        sectorRef = binaryReadUInt32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            embLog_error("compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n", sectorRef, i);
        }
    }
    return difat;
}

unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat)
{
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

unsigned int readFullSector(EmbFile* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead)
{
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
        sectorRef = binaryReadUInt32(file);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < numberOfEntriesInDifatSector(bcfFile); ++i) {
        sectorRef = binaryReadUInt32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            embLog_error("compound-file-difat.c readFullSector(), Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    nextDifatSectorInChain = binaryReadUInt32(file);
    return nextDifatSectorInChain;
}

void bcf_file_difat_free(bcf_file_difat* difat)
{
    free(difat);
    difat = 0;
}

static void parseDirectoryEntryName(EmbFile* file, bcf_directory_entry* dir)
{
    int i;
    unsigned short unicodechar;
    for (i = 0; i < 32; ++i) {
        unicodechar = binaryReadUInt16(file);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

static void readCLSID(EmbFile* file, bcf_directory_entry* dir)
{
    int i;
    unsigned char scratch;
    const int guidSize = 16;
    for (i = 0; i < guidSize; ++i) {
        scratch = binaryReadByte(file);
        dir->CLSID[i] = scratch;
    }
}

bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries)
{
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        embLog_error("compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

EmbTime parseTime(EmbFile* file)
{
    EmbTime returnVal;
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    ft_low = binaryReadInt32(file);
    ft_high = binaryReadInt32(file);
    /* TODO: translate to actual date time */
    return returnVal;
}

bcf_directory_entry* CompoundFileDirectoryEntry(EmbFile* file)
{
    bcf_directory_entry* dir = (bcf_directory_entry*)malloc(sizeof(bcf_directory_entry));
    if (!dir) {
        embLog_error("compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = binaryReadUInt16(file);
    dir->objectType = (unsigned char)binaryReadByte(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        embLog_error("compound-file-directory.c CompoundFileDirectoryEntry(), unexpected object type: %d\n", dir->objectType);
        return 0;
    }
    dir->colorFlag = (unsigned char)binaryReadByte(file);
    dir->leftSiblingId = binaryReadUInt32(file);
    dir->rightSiblingId = binaryReadUInt32(file);
    dir->childId = binaryReadUInt32(file);
    readCLSID(file, dir);
    dir->stateBits = binaryReadUInt32(file);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    dir->startingSectorLocation = binaryReadUInt32(file);
    dir->streamSize = binaryReadUInt32(file); /* This should really be __int64 or long long, but for our uses we should never run into an issue */
    dir->streamSizeHigh = binaryReadUInt32(file); /* top portion of int64 */
    return dir;
}

void readNextSector(EmbFile* file, bcf_directory* dir)
{
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

void bcf_directory_free(bcf_directory* dir)
{
    bcf_directory_entry* pointer = dir->dirEntries;
    bcf_directory_entry* entryToFree = 0;
    while (pointer) {
        entryToFree = pointer;
        pointer = pointer->next;
        free(entryToFree);
        entryToFree = 0;
    }
    if (dir) {
        free(dir);
        dir = 0;
    }
}

bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize)
{
    bcf_file_fat* fat = (bcf_file_fat*)malloc(sizeof(bcf_file_fat));
    if (!fat) {
        embLog_error("compound-file-fat.c bcfFileFat_create(), cannot allocate memory for fat\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
    fat->fatEntryCount = 0;
    return fat;
}

void loadFatFromSector(bcf_file_fat* fat, EmbFile* file)
{
    unsigned int i;
    unsigned int currentNumberOfFatEntries = fat->fatEntryCount;
    unsigned int newSize = currentNumberOfFatEntries + fat->numberOfEntriesInFatSector;
    for (i = currentNumberOfFatEntries; i < newSize; ++i) {
        unsigned int fatEntry = binaryReadUInt32(file);
        fat->fatEntries[i] = fatEntry;
    }
    fat->fatEntryCount = newSize;
}

void bcf_file_fat_free(bcf_file_fat* fat)
{
    free(fat);
    fat = 0;
}

bcf_file_header bcfFileHeader_read(EmbFile* file)
{
    bcf_file_header header;
    binaryReadBytes(file, header.signature, 8);
    binaryReadBytes(file, header.CLSID, 16);
    header.minorVersion = binaryReadUInt16(file);
    header.majorVersion = binaryReadUInt16(file);
    header.byteOrder = binaryReadUInt16(file);
    header.sectorShift = binaryReadUInt16(file);
    header.miniSectorShift = binaryReadUInt16(file);
    header.reserved1 = binaryReadUInt16(file);
    header.reserved2 = (unsigned int)binaryReadUInt32(file);
    header.numberOfDirectorySectors = (unsigned int)binaryReadUInt32(file);
    header.numberOfFATSectors = (unsigned int)binaryReadUInt32(file);
    header.firstDirectorySectorLocation = (unsigned int)binaryReadUInt32(file);
    header.transactionSignatureNumber = (unsigned int)binaryReadUInt32(file);
    header.miniStreamCutoffSize = (unsigned int)binaryReadUInt32(file);
    header.firstMiniFATSectorLocation = (unsigned int)binaryReadUInt32(file);
    header.numberOfMiniFatSectors = (unsigned int)binaryReadUInt32(file);
    header.firstDifatSectorLocation = (unsigned int)binaryReadUInt32(file);
    header.numberOfDifatSectors = (unsigned int)binaryReadUInt32(file);
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

/**************************************************/
/* EmbFormatList                                  */
/**************************************************/

int embFormat_getExtension(const char *fileName, char *ending)
{
    int i;
    const char *offset;

    if (!fileName) {
        embLog_error("emb-format.c embFormat_getExtension(), fileName argument is null\n");
        return 0;
    }

    if (strlen(fileName) == 0) {
        return 0;
    }
    
    offset = strrchr(fileName, '.');
    if (offset==0) {
        return 0;
    }

    i = 0;
    while (offset[i] != '\0') {
        ending[i] = (char)tolower(offset[i]);
        ++i;
    }
    ending[i] = 0; /* terminate the string */

    return 1;
}

const char* embFormat_extensionFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    const char* extension = 0;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            extension = formatTable[i].extension;
            break;
        }
    }

    return extension;
}

const char* embFormat_descriptionFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    const char* description = 0;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            description = formatTable[i].description;
            break;
        }
    }

    return description;
}

char embFormat_readerStateFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    char readerState = ' ';

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            readerState = formatTable[i].reader;
            break;
        }
    }

    return readerState;
}

char embFormat_writerStateFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    char writerState = ' ';

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            writerState = formatTable[i].writer;
            break;
        }
    }

    return writerState;
}

int embFormat_typeFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    int type = EMBFORMAT_UNSUPPORTED;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            type = formatTable[i].type;
            break;
        }
    }

    return type;
}

/*! Returns a pointer to an EmbReaderWriter if the \a fileName is a supported file type. */
EmbReaderWriter* embReaderWriter_getByFileName(const char* fileName)
{
    int i = 0;
    char ending[5];
    EmbReaderWriter* rw = 0;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    rw = (EmbReaderWriter*)malloc(sizeof(EmbReaderWriter));
    if(!rw) { embLog_error("emb-reader-writer.c embReaderWriter_getByFileName(), cannot allocate memory for rw\n"); return 0; }

    #ifdef ARDUINO /* ARDUINO TODO: This is temporary. Remove when complete. */
    if(!strcmp(ending, ".exp"))
    {
        rw->reader = readExp;
        rw->writer = writeExp;
        return rw;
    }
    #else /* ARDUINO TODO: This is temporary. Remove when complete. */        
    /* checks the first character to see if it is the end symbol */
    for (i=0; file_type_list[i].file_ext[0]!='E'; i++) {
        if (!strcmp(ending, file_type_list[i].file_ext))
        {
            rw->reader = file_type_list[i].reader;
            rw->writer = file_type_list[i].writer;
            return rw;
        }
    }
    #endif /* ARDUINO TODO: This is temporary. Remove when complete. */

    embLog_error("emb-reader-writer.c embReaderWriter_getByFileName(), unsupported file type: %s\n", ending);
    return 0;
}

