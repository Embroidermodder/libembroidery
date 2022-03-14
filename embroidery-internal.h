/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#ifndef __EMBROIDERY_INTERNAL_HEADER__
#define __EMBROIDERY_INTERNAL_HEADER__

#define EMB_MIN(A, B) (((A) < (B)) ? (A) : (B))
#define EMB_MAX(A, B) (((A) > (B)) ? (A) : (B))

#define MAX_STITCHES             1000000

#define EMB_BIG_ENDIAN                          0
#define EMB_LITTLE_ENDIAN                       1

#define ENDIAN_HOST                             EMB_LITTLE_ENDIAN

#define EMB_INT16_BIG                           2
#define EMB_INT16_LITTLE                        3
#define EMB_INT32_BIG                           4
#define EMB_INT32_LITTLE                        5

/* INTERNAL STRUCTS AND ENUMS
 *******************************************************************/

/* double-indirection file allocation table references */
typedef struct _bcf_file_difat
{
    unsigned int fatSectorCount;
    unsigned int fatSectorEntries[109];
    unsigned int sectorSize;
} bcf_file_difat;

typedef struct _bcf_file_fat
{
    int          fatEntryCount;
    unsigned int fatEntries[255]; /* maybe make this dynamic */
    unsigned int numberOfEntriesInFatSector;
} bcf_file_fat;

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

typedef struct _bcf_file
{
    bcf_file_header header;   /*! The header for the CompoundFile */
    bcf_file_difat* difat;    /*! The "Double Indirect FAT" for the CompoundFile */
    bcf_file_fat* fat;        /*! The File Allocation Table for the Compound File */
    bcf_directory* directory; /*! The directory for the CompoundFile */
} bcf_file;

typedef enum
{
    CSV_EXPECT_NULL,
    CSV_EXPECT_QUOTE1,
    CSV_EXPECT_QUOTE2,
    CSV_EXPECT_COMMA
} CSV_EXPECT;

typedef enum
{
    CSV_MODE_NULL,
    CSV_MODE_COMMENT,
    CSV_MODE_VARIABLE,
    CSV_MODE_THREAD,
    CSV_MODE_STITCH
} CSV_MODE;

typedef struct SvgAttribute_
{
    char* name;
    char* value;
} SvgAttribute;

typedef struct Huffman {
    int default_value;
    int *lengths;
    int nlengths;
    int *table;
    int table_width;
    int ntable;
} huffman;

typedef struct Compress {
    int bit_position;
    char *input_data;
    int input_length;
    int bits_total;
    int block_elements;
    huffman *character_length_huffman;
    huffman *character_huffman;
    huffman *distance_huffman;
} compress;


/* INTERNAL FUNCTION PROTOTYPES
 *******************************************************************/
void huffman_init(huffman *h, int lengths, int value);
void huffman_build_table(huffman *h);
void huffman_table_lookup(huffman *h, int byte_lookup, int *value, int *lengths);
void huffman_free(huffman *h);

int compress_get_bits(compress *c, int length);
int compress_pop(compress *c, int bit_count);
int compress_read_variable_length(compress *c);
int compress_load_character_length_huffman(compress *c);
void compress_load_character_huffman(compress *c);
void compress_load_distance_huffman(compress *c);
void compress_load_block(compress *c);
int compress_get_token(compress *c);
int compress_get_position(compress *c);

void binaryReadString(FILE* file, char *buffer, int maxLength);
void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength);

void binaryWriteShort(FILE* file, short data);
void binaryWriteUShort(FILE* file, unsigned short data);
void binaryWriteUShortBE(FILE* file, unsigned short data);
void binaryWriteInt(FILE* file, int data);
void binaryWriteIntBE(FILE* file, int data);
void binaryWriteUInt(FILE* file, unsigned int data);
void binaryWriteUIntBE(FILE* file, unsigned int data);

int stringInArray(const char *s, const char **array);
void fpad(FILE *f, char c, int n);
char *copy_trim(char const *s);
char* emb_optOut(double num, char* str);

void write_24bit(FILE* file, int);
int check_header_present(FILE* file, int minimum_header_length);

void fread_int(FILE* f, void *b, int mode);
void fwrite_int(FILE* f, void *b, int mode);
short fread_int16(FILE* f);
unsigned short fread_uint16(FILE* f);
int fread_int32(FILE* f);
unsigned int fread_uint32(FILE* f);
short fread_int16_be(FILE* f);
unsigned short fread_uint16_be(FILE* f);
int fread_int32_be(FILE* f);
unsigned int fread_uint32_be(FILE* f);

bcf_file_difat* bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize);
unsigned int readFullSector(FILE* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
void bcf_file_difat_free(bcf_file_difat* difat);

bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
void loadFatFromSector(bcf_file_fat* fat, FILE* file);
void bcf_file_fat_free(bcf_file_fat** fat);

bcf_directory_entry* CompoundFileDirectoryEntry(FILE* file);
bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
void readNextSector(FILE* file, bcf_directory* dir);
void bcf_directory_free(bcf_directory** dir);

bcf_file_header bcfFileHeader_read(FILE* file);
int bcfFileHeader_isValid(bcf_file_header header);

int bcfFile_read(FILE* file, bcf_file* bcfFile);
FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind);
void bcf_file_free(bcf_file* bcfFile);

void readPecStitches(EmbPattern* pattern, FILE* file);
void writePecStitches(EmbPattern* pattern, FILE* file, const char* filename);

int emb_readline(FILE* file, char *line, int maxLength);

int decodeNewStitch(unsigned char value);

void pfaffEncode(FILE* file, int x, int y, int flags);
double pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3);

unsigned char mitEncodeStitch(double value);
int mitDecodeStitch(unsigned char value);

int encode_tajima_ternary(unsigned char b[3], int x, int y);
void decode_tajima_ternary(unsigned char b[3], int *x, int *y);

void encode_t01_record(unsigned char b[3], int x, int y, int flags);
int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags);

void testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1);
void printArcResults(double bulge, EmbArc arc,
                     double centerX,   double centerY,
                     double radius,    double diameter,
                     double chord,
                     double chordMidX, double chordMidY,
                     double sagitta,   double apothem,
                     double incAngle,  char   clockwise);
void report(int result, char *label);
int create_test_file_1(const char* outf);
int create_test_file_2(const char* outf);
int testEmbCircle(void);
int testEmbCircle_2(void);
int testGeomArc(void);
int testThreadColor(void);
int testEmbFormat(void);
int full_test_matrix(char *fname);

/* Global variables within library scope
 ****************************************
 */

extern EmbThread black_thread;
extern int emb_verbose;

#endif

