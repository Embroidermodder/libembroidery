/*! @file emb-file.h */
#ifndef EMB_FILE_H
#define EMB_FILE_H

#include <stdio.h>

#include "emb-pattern.h"
#include "emb-time.h"
#include "emb-file.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ARDUINO
#include "utility/ino-file.h"
#else
typedef struct EmbFile_
{
    FILE* file;
} EmbFile;
#endif /* ARDUINO */

int validateWritePattern(EmbPattern* pattern, const char* fileName, const char *function);
int validateReadPattern(EmbPattern* pattern, const char* fileName, const char *function);

extern EMB_PUBLIC EmbFile* EMB_CALL embFile_open(const char* fileName, const char* mode);
extern EMB_PUBLIC int EMB_CALL embFile_close(EmbFile* stream);
extern EMB_PUBLIC int EMB_CALL embFile_eof(EmbFile* stream);
extern EMB_PUBLIC int EMB_CALL embFile_getc(EmbFile* stream);
extern EMB_PUBLIC size_t EMB_CALL embFile_read(void* ptr, size_t size, size_t nmemb, EmbFile* stream);
extern EMB_PUBLIC size_t EMB_CALL embFile_write(const void* ptr, size_t size, size_t nmemb, EmbFile* stream);
extern EMB_PUBLIC int EMB_CALL embFile_seek(EmbFile* stream, long offset, int origin);
extern EMB_PUBLIC long EMB_CALL embFile_tell(EmbFile* stream);
extern EMB_PUBLIC EmbFile* EMB_CALL embFile_tmpfile(void);
extern EMB_PUBLIC int EMB_CALL embFile_putc(int ch, EmbFile* stream);

extern EMB_PUBLIC int EMB_CALL embFile_printf(EmbFile* stream, const char* format, ...);

/* double-indirection file allocation table references */
typedef struct _bcf_file_difat
{
    unsigned int fatSectorCount;
    unsigned int fatSectorEntries[109];
    unsigned int sectorSize;
} bcf_file_difat;

extern EMB_PRIVATE bcf_file_difat* EMB_CALL bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize);
extern EMB_PRIVATE unsigned int EMB_CALL readFullSector(EmbFile* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
extern EMB_PRIVATE unsigned int EMB_CALL numberOfEntriesInDifatSector(bcf_file_difat* fat);
extern EMB_PRIVATE void EMB_CALL bcf_file_difat_free(bcf_file_difat* difat);

/*! Constant representing the number of Double Indirect FAT entries in a single header */
static const unsigned int NumberOfDifatEntriesInHeader = 109;

typedef struct _bcf_file_fat
{
    int          fatEntryCount;
    unsigned int fatEntries[255]; /* maybe make this dynamic */
    unsigned int numberOfEntriesInFatSector;
} bcf_file_fat;

extern EMB_PRIVATE bcf_file_fat* EMB_CALL bcfFileFat_create(const unsigned int sectorSize);
extern EMB_PRIVATE void EMB_CALL loadFatFromSector(bcf_file_fat* fat, EmbFile* file);
extern EMB_PRIVATE void EMB_CALL bcf_file_fat_free(bcf_file_fat* fat);

typedef struct _bcf_directory_entry
{
    char                         directoryEntryName[32];
    unsigned short               directoryEntryNameLength;
    unsigned char                objectType;
    unsigned char                colorFlag;
    unsigned int                 leftSiblingId;
    unsigned int                 rightSiblingId;
    unsigned int                 childId;
    unsigned char                CLSID[16];
    unsigned int                 stateBits;
    EmbTime                      creationTime;
    EmbTime                      modifiedTime;
    unsigned int                 startingSectorLocation;
    unsigned long                streamSize; /* should be long long but in our case we shouldn't need it, and hard to support on c89 cross platform */
    unsigned int                 streamSizeHigh; /* store the high int of streamsize */
    struct _bcf_directory_entry* next;
} bcf_directory_entry;

typedef struct _bcf_directory
{
    bcf_directory_entry* dirEntries;
    unsigned int         maxNumberOfDirectoryEntries;
    /* TODO: possibly add a directory tree in the future */

} bcf_directory;

extern EMB_PRIVATE bcf_directory_entry* EMB_CALL CompoundFileDirectoryEntry(EmbFile* file);
extern EMB_PRIVATE bcf_directory* EMB_CALL CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
extern EMB_PRIVATE void EMB_CALL readNextSector(EmbFile* file, bcf_directory* dir);
extern EMB_PRIVATE void EMB_CALL bcf_directory_free(bcf_directory* dir);

typedef struct _bcf_file_header
{
    unsigned char  signature[8];
    unsigned char  CLSID[16]; /* TODO: this should be a separate type */
    unsigned short minorVersion;
    unsigned short majorVersion;
    unsigned short byteOrder;
    unsigned short sectorShift;
    unsigned short miniSectorShift;
    unsigned short reserved1;
    unsigned int   reserved2;
    unsigned int   numberOfDirectorySectors;
    unsigned int   numberOfFATSectors;
    unsigned int   firstDirectorySectorLocation;
    unsigned int   transactionSignatureNumber;
    unsigned int   miniStreamCutoffSize;
    unsigned int   firstMiniFATSectorLocation;
    unsigned int   numberOfMiniFatSectors;
    unsigned int   firstDifatSectorLocation;
    unsigned int   numberOfDifatSectors;
} bcf_file_header;

extern EMB_PRIVATE bcf_file_header EMB_CALL bcfFileHeader_read(EmbFile* file);
extern EMB_PRIVATE int EMB_CALL bcfFileHeader_isValid(bcf_file_header header);

typedef struct _bcf_file
{
    bcf_file_header header;   /*! The header for the CompoundFile */
    bcf_file_difat* difat;    /*! The "Double Indirect FAT" for the CompoundFile */
    bcf_file_fat* fat;        /*! The File Allocation Table for the Compound File */
    bcf_directory* directory; /*! The directory for the CompoundFile */
} bcf_file;

extern EMB_PRIVATE int EMB_CALL bcfFile_read(EmbFile* file, bcf_file* bcfFile);
extern EMB_PRIVATE EmbFile* EMB_CALL GetFile(bcf_file* bcfFile, EmbFile* file, char* fileToFind);
extern EMB_PRIVATE void EMB_CALL bcf_file_free(bcf_file* bcfFile);

/**
  Type of sector
*/
#define CompoundFileSector_MaxRegSector 0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector 0xFFFFFFFC
#define CompoundFileSector_FAT_Sector   0xFFFFFFFD
#define CompoundFileSector_EndOfChain   0xFFFFFFFE
#define CompoundFileSector_FreeSector   0xFFFFFFFF

/**
  Type of directory object
*/
#define ObjectTypeUnknown   0x00 /*!< Probably unallocated    */
#define ObjectTypeStorage   0x01 /*!< a directory type object */
#define ObjectTypeStream    0x02 /*!< a file type object      */
#define ObjectTypeRootEntry 0x05 /*!< the root entry          */

/**
  Special values for Stream Identifiers
*/
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /*!< All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream           0xFFFFFFFF /*!< There is no valid stream Id            */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* EMB_FILE_H */


