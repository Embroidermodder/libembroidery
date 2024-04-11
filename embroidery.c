/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * ---------------------------------------------------------
 *
 * Copyright 2018-2024 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 */

#include "embroidery.h"

/* System-specific functions.
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 *
 * ---------------------------------------------------------
 *
 * In order to support embedded systems and WASM these need to
 * be replaced, see the #else block below.
 */
#ifndef EMB_EMBEDDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void *
emb_fopen(const char *fname, const char *mode)
{
    return (void *)fopen(fname, mode);
}

int
emb_fread(void *data, int length, void *file_pointer)
{
    return fread((unsigned char *)data, 1, length, (void*)file_pointer);
}

int
emb_fwrite(void *data, int length, void *file_pointer)
{
    return fwrite((unsigned char *)data, 1, length, (void*)file_pointer);
}

int
emb_fseek(void *file, int offset, int from)
{
    return emb_fseek((FILE*)file, offset, from);
}

void
emb_fclose(void *f)
{
    fclose((void*)f);
}
#else
/* For other systems, file i/o functions like emb_fread/emb_fwrite have
 * to be defined by the includer. So this list of functions defines what
 * a new platform would have to define.
 *
 * Emscripten doesn't use this, it's not considered "EMB_EMBEDDED".
 */
typedef long unsigned int size_t;

static const int stdin = 0;
static const int EOF = -1;
static const int SEEK_SET = 2;

#define NULL ((void*)0)

void *malloc(long unsigned int);
void *realloc(void *, long unsigned int);
void *calloc(long unsigned int, long unsigned int);
void free(void *);

/* These often have in-built assembly commands: so it's very chip-specific. */
double fabs(double);
double cos(double);
double sin(double);
double sqrt(double);
double ceil(double);
double floor(double);
float fmodf(float, float);
double atan2(double, double);
double atan(double);

int puts(const char *);
int printf(const char *, ...);

void *emb_fopen(const char *fname, const char *mode);
int emb_fread(void *data, int length, void *file_pointer);
int emb_fwrite(void *data, int length, void *file_pointer);
void emb_fclose(void *f);
int emb_fseek(void *file, int offset, int from);
#endif

/* Internal function declarations.
 * ----------------------------------------------------------------------------
 */

/* Utility Functions: merge first three with string library */
int stringInArray(const char *s, const char **array);
char *copy_trim(char const *s);
char* emb_optOut(EmbReal num, char* str);
void safe_free(void *data);

int testMain(int);

/* DIFAT functions */
unsigned int entriesInDifatSector(bcf_file_difat* fat);
bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
void loadFatFromSector(bcf_file_fat* fat, void* file);
void bcf_file_fat_free(bcf_file_fat** fat);
bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
void bcf_directory_free(bcf_directory** dir);
unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
void bcf_file_difat_free(bcf_file_difat* difat);
bcf_file_header bcfFileHeader_read(void* file);
int bcfFileHeader_isValid(bcf_file_header header);
void bcf_file_free(bcf_file* bcfFile);

static EmbPattern *focussed_pattern = NULL;

void
printArcResults(
    EmbReal bulge,
    EmbArc arc,
    EmbVector center,
    EmbReal radius,
    EmbReal diameter,
    EmbReal chord,
    EmbVector chordMid,
    EmbReal sagitta,
    EmbReal apothem,
    EmbReal incAngle,
    char clockwise);
void testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1);
int create_test_file(int test_file, const char* outf);

/* Encoding/decoding and compression functions. */
int hus_compress(char* input, int size, char* output, int *out_size);
int hus_decompress(char* input, int size, char* output, int *out_size);

void huffman_build_table(huffman *h);
int *huffman_table_lookup(huffman *h, int byte_lookup, int *lengths);

int compress_get_bits(compress *c, int length);
int compress_pop(compress *c, int bit_count);
int compress_read_variable_length(compress *c);
void compress_load_character_length_huffman(compress *c);
void compress_load_character_huffman(compress *c);
void compress_load_distance_huffman(compress *c);
void compress_load_block(compress *c);
int compress_get_token(compress *c);
int compress_get_position(compress *c);

EmbReal pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3);

int decodeNewStitch(unsigned char value);

unsigned char mitEncodeStitch(EmbReal value);
int mitDecodeStitch(unsigned char value);

void encode_t01_record(unsigned char b[3], int x, int y, int flags);
int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags);

int encode_tajima_ternary(unsigned char b[3], int x, int y);
void decode_tajima_ternary(unsigned char b[3], int *x, int *y);

/*
 * Note that this file only has to exist because we cannot necessary include
 * any of the C standard library on all platforms. For example, "void *" and
 * "printf" aren't universal. See the "Supported Platforms" section of
 * the reference manual.
 */

/* Function Declarations */
void readPecStitches(EmbPattern* pattern, void* file);
void writePecStitches(EmbPattern* pattern, void* file, const char* filename);

void pfaffEncode(void* file, int x, int y, int flags);

void readPESHeaderV5(void* file, EmbPattern* pattern);
void readPESHeaderV6(void* file, EmbPattern* pattern);
void readPESHeaderV7(void* file, EmbPattern* pattern);
void readPESHeaderV8(void* file, EmbPattern* pattern);
void readPESHeaderV9(void* file, EmbPattern* pattern);
void readPESHeaderV10(void* file, EmbPattern* pattern);

void readDescriptions(void* file, EmbPattern* pattern);
void readHoopName(void* file, EmbPattern* pattern);
void readImageString(void* file, EmbPattern* pattern);
void readProgrammableFills(void* file, EmbPattern* pattern);
void readMotifPatterns(void* file, EmbPattern* pattern);
void readFeatherPatterns(void* file, EmbPattern* pattern);
void readThreads(void* file, EmbPattern* pattern);

void emb_read(void* f, void *b, int mode);
void emb_write(void* f, void *b, int mode);
int emb_readline(void* file, char *line, int maxLength);

int bcfFile_read(void* file, bcf_file* bcfFile);
void* GetFile(bcf_file* bcfFile, void* file, char* fileToFind);

void binaryReadString(void* file, char *buffer, int maxLength);
void binaryReadUnicodeString(void* file, char *buffer, const int stringLength);

void fpad(void *f, char c, int n);

void write_24bit(void* file, int);
int check_header_present(void* file, int minimum_header_length);

unsigned short fread_uint16(void *file);
short fread_int16(void* f);

void binaryWriteUIntBE(void* f, unsigned int data);
void binaryWriteUInt(void* f, unsigned int data);
void binaryWriteIntBE(void* f, int data);
void binaryWriteInt(void* f, int data);
void binaryWriteUShort(void* f, unsigned short data);
void binaryWriteUShortBE(void* f, unsigned short data);
void binaryWriteShort(void* f, short data);

bcf_file_difat* bcf_difat_create(void* file, unsigned int fatSectors, const unsigned int sectorSize);
unsigned int readFullSector(void* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
bcf_directory_entry* CompoundFileDirectoryEntry(void* file);
void readNextSector(void* file, bcf_directory* dir);

void embColor_read(void *f, EmbColor *c, int toRead);
void embColor_write(void *f, EmbColor c, int toWrite);

unsigned char toyota_position_encode(EmbReal a);
EmbReal toyota_position_decode(unsigned char a);

void toyota_100_encode(EmbVector *position, EmbStitch *st, unsigned char *b);
void toyota_100_decode(EmbVector *position, EmbStitch *st, unsigned char *b);
void toyota_10o_encode(EmbVector *position, EmbStitch *st, unsigned char *b);
void toyota_10o_decode(EmbVector *position, EmbStitch *st, unsigned char *b);
void bernina_art_encode(EmbVector *position, EmbStitch *st, unsigned char *b);
void bernina_art_decode(EmbVector *position, EmbStitch *st, unsigned char *b);

char read_stitch_block(
    EmbPattern *,
    void *file,
    void (*stitch_encoder)(EmbVector *, EmbStitch *, unsigned char *),
    int stitch_data_size,
    int mode
);
char write_stitch_block(
    EmbPattern *,
    void *file,
    void (*stitch_encoder)(EmbVector *, EmbStitch *, unsigned char *),
    int stitch_data_size,
    int mode
);

char readBmc(EmbPattern *pattern, void* file);
char writeBmc(EmbPattern *pattern, void* file);
char readBro(EmbPattern *pattern, void* file);
char writeBro(EmbPattern *pattern, void* file);
char readCnd(EmbPattern *pattern, void* file);
char writeCnd(EmbPattern *pattern, void* file);
char readCol(EmbPattern *pattern, void* file);
char writeCol(EmbPattern *pattern, void* file);
char readCsd(EmbPattern *pattern, void* file);
char writeCsd(EmbPattern *pattern, void* file);
char readCsv(EmbPattern *pattern, void* file);
char writeCsv(EmbPattern *pattern, void* file);
char readDat(EmbPattern *pattern, void* file);
char writeDat(EmbPattern *pattern, void* file);
char readDem(EmbPattern *pattern, void* file);
char writeDem(EmbPattern *pattern, void* file);
char readDsb(EmbPattern *pattern, void* file);
char writeDsb(EmbPattern *pattern, void* file);
char readDst(EmbPattern *pattern, void* file);
char writeDst(EmbPattern *pattern, void* file);
char readDsz(EmbPattern *pattern, void* file);
char writeDsz(EmbPattern *pattern, void* file);
char readDxf(EmbPattern *pattern, void* file);
char writeDxf(EmbPattern *pattern, void* file);
char readEdr(EmbPattern *pattern, void* file);
char writeEdr(EmbPattern *pattern, void* file);
char readEmd(EmbPattern *pattern, void* file);
char writeEmd(EmbPattern *pattern, void* file);
char readExp(EmbPattern *pattern, void* file);
char writeExp(EmbPattern *pattern, void* file);
char readExy(EmbPattern *pattern, void* file);
char writeExy(EmbPattern *pattern, void* file);
char readEys(EmbPattern *pattern, void* file);
char writeEys(EmbPattern *pattern, void* file);
char readFxy(EmbPattern *pattern, void* file);
char writeFxy(EmbPattern *pattern, void* file);
char readGc(EmbPattern *pattern, void* file);
char writeGc(EmbPattern *pattern, void* file);
char readGnc(EmbPattern *pattern, void* file);
char writeGnc(EmbPattern *pattern, void* file);
char readGt(EmbPattern *pattern, void* file);
char writeGt(EmbPattern *pattern, void* file);
char readHus(EmbPattern *pattern, void* file);
char writeHus(EmbPattern *pattern, void* file);
char readInb(EmbPattern *pattern, void* file);
char writeInb(EmbPattern *pattern, void* file);
char readInf(EmbPattern *pattern, void* file);
char writeInf(EmbPattern *pattern, void* file);
char readJef(EmbPattern *pattern, void* file);
char writeJef(EmbPattern *pattern, void* file);
char readKsm(EmbPattern *pattern, void* file);
char writeKsm(EmbPattern *pattern, void* file);
char readMax(EmbPattern *pattern, void* file);
char writeMax(EmbPattern *pattern, void* file);
char readMit(EmbPattern *pattern, void* file);
char writeMit(EmbPattern *pattern, void* file);
char readNew(EmbPattern *pattern, void* file);
char writeNew(EmbPattern *pattern, void* file);
char readOfm(EmbPattern *pattern, void* file);
char writeOfm(EmbPattern *pattern, void* file);
char readPcd(EmbPattern *pattern, const char *fileName, void* file);
char writePcd(EmbPattern *pattern, void* file);
char readPcm(EmbPattern *pattern, void* file);
char writePcm(EmbPattern *pattern, void* file);
char readPcq(EmbPattern *pattern, const char *fileName, void* file);
char writePcq(EmbPattern *pattern, void* file);
char readPcs(EmbPattern *pattern, const char *fileName, void* file);
char writePcs(EmbPattern *pattern, void* file);
char readPec(EmbPattern *pattern, const char *fileName, void* file);
char writePec(EmbPattern *pattern, const char *fileName,  void* file);
char readPel(EmbPattern *pattern, void *file);
char writePel(EmbPattern *pattern, void *file);
char readPem(EmbPattern *pattern, void *file);
char writePem(EmbPattern *pattern, void *file);
char readPes(EmbPattern *pattern, const char *fileName, void* file);
char writePes(EmbPattern *pattern, const char *fileName, void* file);
char readPhb(EmbPattern *pattern, void* file);
char writePhb(EmbPattern *pattern, void *file);
char readPhc(EmbPattern *pattern, void* file);
char writePhc(EmbPattern *pattern, void *file);
char readPlt(EmbPattern *pattern, void* file);
char writePlt(EmbPattern *pattern, void* file);
char readRgb(EmbPattern *pattern, void* file);
char writeRgb(EmbPattern *pattern, void* file);
char readSew(EmbPattern *pattern, void* file);
char writeSew(EmbPattern *pattern, void* file);
char readShv(EmbPattern *pattern, void* file);
char writeShv(EmbPattern *pattern, void *file);
char readSst(EmbPattern *pattern, void* file);
char writeSst(EmbPattern *pattern, void *file);
char readStx(EmbPattern *pattern, void* file);
char writeStx(EmbPattern *pattern, void *file);
char readSvg(EmbPattern *pattern, void* file);
char writeSvg(EmbPattern *pattern, void* file);
char readT01(EmbPattern *pattern, void* file);
char writeT01(EmbPattern *pattern, void* file);
char readT09(EmbPattern *pattern, void* file);
char writeT09(EmbPattern *pattern, void* file);
char readTap(EmbPattern *pattern, void* file);
char writeTap(EmbPattern *pattern, void* file);
char readThr(EmbPattern *pattern, void* file);
char writeThr(EmbPattern *pattern, void* file);
char readTxt(EmbPattern *pattern, void* file);
char writeTxt(EmbPattern *pattern, void* file);
char readU00(EmbPattern *pattern, void* file);
char writeU00(EmbPattern *pattern, void *file);
char readU01(EmbPattern *pattern, void* file);
char writeU01(EmbPattern *pattern, void *file);
char readVip(EmbPattern *pattern, void* file);
char writeVip(EmbPattern *pattern, void* file);
char readVp3(EmbPattern *pattern, void* file);
char writeVp3(EmbPattern *pattern, void* file);
char readXxx(EmbPattern *pattern, void* file);
char writeXxx(EmbPattern *pattern, void* file);
char readZsk(EmbPattern *pattern, void* file);
char writeZsk(EmbPattern *pattern, void* file);

void write_24bit(void* file, int);

/* Replacing functions that compilers complain about.
 * In some cases, this is due to valid concerns about
 * functions not returning (like a string without null-termination).
 *
 * We don't use size_t because it's system-specific.
 *
 * IDEA: don't rely on "sizeof" because it's system and
 * compiler-specific, depending on how the struct is packed.
 * We could manually pack out structs and then know exactly
 * how much space they need.
 *
 * TODO: UTF-8 support.
 */
void string_copy(char *dst, const char *src);
int string_equals(const char *s1, const char *s2);
int string_len(const char *src);
void string_cat(char *dst, const char *src);
int string_rchar(const char *s1, char c);
void char_ptr_to_string(char *dst, char *src);
void memory_copy(void *dst, const void *src, int n);
char memory_cmp(void *dst, const void *src, int n);

/* Internal Data
 * ----------------------------------------------------------------------------
 *
 * This file contains all the read and write functions for the
 * library.
 *
 * .. todo::
 *    This list needs reviewed in case some stitch
 *    formats also can contain object data (EMBFORMAT_STCHANDOBJ). *
 */
EmbFormatList formatTable[numberOfFormats] = {
    {".10o", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".100", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".art", "Bernina Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".bmc", "Bitmap Cache Embroidery Format",     ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".bro", "Bits & Volts Embroidery Format",     'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".cnd", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".col", "Embroidery Thread Color Format",     'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".csd", "Singer Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".csv", "Comma Separated Values Format",      'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".dat", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dem", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".dsb", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dst", "Tajima Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dsz", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dxf", "Drawing Exchange Format",            ' ', ' ', EMBFORMAT_OBJECTONLY, 0, 0, 0},
    {".edr", "Embird Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".emd", "Elna Embroidery Format",             'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".exp", "Melco Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".exy", "Eltac Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".eys", "Sierra Expanded Embroidery Format",  ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".fxy", "Fortron Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".gc",  "Smoothie G-Code Format",             ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".gnc", "Great Notions Embroidery Format",    ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".gt",  "Gold Thread Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".inb", "Inbro Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".inf", "Embroidery Color Format",            'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".jef", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".ksm", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".max", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".mit", "Mitsubishi Embroidery Format",       'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".new", "Ameco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".ofm", "Melco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcd", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcm", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcq", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcs", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pec", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pel", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pem", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pes", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".phb", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".phc", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".plt", "AutoCAD Plot Drawing Format",        'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".rgb", "RGB Embroidery Format",              'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".sew", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".sst", "Sunstar Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".stx", "Data Stitch Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".svg", "Scalable Vector Graphics",           'U', 'U', EMBFORMAT_OBJECTONLY, 0, 0, 0},
    {".t01", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".t09", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".tap", "Happy Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".thr", "ThredWorks Embroidery Format",       'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".txt", "Text File",                          ' ', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".u00", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".u01", "Barudan Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".vip", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".vp3", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".xxx", "Singer Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".zsk", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0}
};

const char *help_msg[] = {
    "Usage: embroider [OPTIONS] fileToRead... ",
    "",
    "Conversion:",
    "    -t, --to        Convert all files given to the format specified",
    "                    by the arguments to the flag, for example:",
    "                        $ embroider -t dst input.pes",
    "                    would convert \"input.pes\" to \"input.dst\"",
    "                    in the same directory the program runs in.",
    "",
    "                    The accepted input formats are (TO BE DETERMINED).",
    "                    The accepted output formats are (TO BE DETERMINED).",
    "",
    "Output:",
    "    -h, --help       Print this message.",
    "    -F, --formats     Print help on the formats that embroider can deal with.",
    "    -q, --quiet      Only print fatal errors.",
    "    -V, --verbose    Print everything that has reporting.",
    "    -v, --version    Print the version.",
    "",
    "Modify patterns:",
    "    --combine        takes 3 arguments and combines the first",
    "                     two by placing them atop each other and",
    "                     outputs to the third",
    "                        $ embroider --combine a.dst b.dst output.dst",
    "",
    "Graphics:",
    "    -c, --circle     Add a circle defined by the arguments given to the current pattern.",
    "    -e, --ellipse    Add a circle defined by the arguments given to the current pattern.",
    "    -l, --line       Add a line defined by the arguments given to the current pattern.",
    "    -P, --polyline   Add a polyline.",
    "    -p, --polygon    Add a polygon.",
    "    -r, --render     Create an image in PNG format of what the embroidery should look like.",
    "    -s, --satin      Fill the current geometry with satin stitches according",
    "                     to the defined algorithm.",
    "    -S, --stitch     Add a stitch defined by the arguments given to the current pattern.",
    "",
    "Quality Assurance:",
    "        --test N           Run the test number N.",
    "        --convert-test A N M Test conversion of test file A from format N to format M.",
    "        --full-test-suite  Run all tests, even those we expect to fail.",
    "EOF"
};

/* EmbString table of flags. */
const EmbString flag_list[] = {
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
    "--convert-test",
    "--hilbert-curve",
    "--sierpinski-triangle",
    "--fill",
    "-f",
    "--simulate",
    "--combine",
    "--cross-stitch"
};

const char *version_string = "embroider v0.1";

const char *welcome_message = "EMBROIDER\n"
    "    A command line program for machine embroidery.\n"
    "    Copyright 2013-2022 The Embroidermodder Team\n"
    "    Licensed under the terms of the zlib license.\n"
    "\n"
    "    https://github.com/Embroidermodder/libembroidery\n"
    "    https://embroidermodder.org\n";


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

/* Based on the DraftSight color table. It doesn't appear to be authoratitive
 * and there isn't much said in the official manual about colors 8-255:
 * http://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf
 *
 * A possible "standard" solution here is to use xterm ESC color codes with the first
 * 8 overridden for compatibility. That way a curious user may be able to guess
 * and be _almost_ right. See this script for how simple those codes are:
 * https://gist.github.com/hSATAC/1095100
 */
const unsigned char _dxfColorTable[][3] = {
    {   0,   0,   0 }, /*   '0' (BYBLOCK)    */
    { 255,   0,   0 }, /*   '1' (red)        */
    { 255, 255,   0 }, /*   '2' (yellow)     */
    {   0, 255,   0 }, /*   '3' (green)      */
    {   0, 255, 255 }, /*   '4' (cyan)       */
    {   0,   0, 255 }, /*   '5' (blue)       */
    { 255,   0, 255 }, /*   '6' (magenta)    */
    { 255, 255, 255 }, /*   '7' (white)      */
    { 128, 128, 128 }, /*   '8' (dark gray)  */
    { 192, 192, 192 }, /*   '9' (light gray) */
    { 255,   0,   0 }, /*  '10' */
    { 255, 127, 127 }, /*  '11' */
    { 204,   0,   0 }, /*  '12' */
    { 204, 102, 102 }, /*  '13' */
    { 153,   0,   0 }, /*  '14' */
    { 153,  76,  76 }, /*  '15' */
    { 127,   0,   0 }, /*  '16' */
    { 127,  63,  63 }, /*  '17' */
    {  76,   0,   0 }, /*  '18' */
    {  76,  38,  38 }, /*  '19' */
    { 255,  63,   0 }, /*  '20' */
    { 255, 159, 127 }, /*  '21' */
    { 204,  51,   0 }, /*  '22' */
    { 204, 127, 102 }, /*  '23' */
    { 153,  38,   0 }, /*  '24' */
    { 153,  95,  76 }, /*  '25' */
    { 127,  31,   0 }, /*  '26' */
    { 127,  79,  63 }, /*  '27' */
    {  76,  19,   0 }, /*  '28' */
    {  76,  47,  38 }, /*  '29' */
    { 255, 127,   0 }, /*  '30' */
    { 255, 191, 127 }, /*  '31' */
    { 204, 102,   0 }, /*  '32' */
    { 204, 153, 102 }, /*  '33' */
    { 153,  76,   0 }, /*  '34' */
    { 153, 114,  76 }, /*  '35' */
    { 127,  63,   0 }, /*  '36' */
    { 127,  95,  63 }, /*  '37' */
    {  76,  38,   0 }, /*  '38' */
    {  76,  57,  38 }, /*  '39' */
    { 255, 191,   0 }, /*  '40' */
    { 255, 223, 127 }, /*  '41' */
    { 204, 153,   0 }, /*  '42' */
    { 204, 178, 102 }, /*  '43' */
    { 153, 114,   0 }, /*  '44' */
    { 153, 133,  76 }, /*  '45' */
    { 127,  95,   0 }, /*  '46' */
    { 127, 111,  63 }, /*  '47' */
    {  76,  57,   0 }, /*  '48' */
    {  76,  66,  38 }, /*  '49' */
    { 255, 255,   0 }, /*  '50' */
    { 255, 255, 127 }, /*  '51' */
    { 204, 204,   0 }, /*  '52' */
    { 204, 204, 102 }, /*  '53' */
    { 153, 153,   0 }, /*  '54' */
    { 153, 153,  76 }, /*  '55' */
    { 127, 127,   0 }, /*  '56' */
    { 127, 127,  63 }, /*  '57' */
    {  76,  76,   0 }, /*  '58' */
    {  76,  76,  38 }, /*  '59' */
    { 191, 255,   0 }, /*  '60' */
    { 223, 255, 127 }, /*  '61' */
    { 153, 204,   0 }, /*  '62' */
    { 178, 204, 102 }, /*  '63' */
    { 114, 153,   0 }, /*  '64' */
    { 133, 153,  76 }, /*  '65' */
    {  95, 127,   0 }, /*  '66' */
    { 111, 127,  63 }, /*  '67' */
    {  57,  76,   0 }, /*  '68' */
    {  66,  76,  38 }, /*  '69' */
    { 127, 255,   0 }, /*  '70' */
    { 191, 255, 127 }, /*  '71' */
    { 102, 204,   0 }, /*  '72' */
    { 153, 204, 102 }, /*  '73' */
    {  76, 153,   0 }, /*  '74' */
    { 114, 153,  76 }, /*  '75' */
    {  63, 127,   0 }, /*  '76' */
    {  95, 127,  63 }, /*  '77' */
    {  38,  76,   0 }, /*  '78' */
    {  57,  76,  38 }, /*  '79' */
    {  63, 255,   0 }, /*  '80' */
    { 159, 255, 127 }, /*  '81' */
    {  51, 204,   0 }, /*  '82' */
    { 127, 204, 102 }, /*  '83' */
    {  38, 153,   0 }, /*  '84' */
    {  95, 153,  76 }, /*  '85' */
    {  31, 127,   0 }, /*  '86' */
    {  79, 127,  63 }, /*  '87' */
    {  19,  76,   0 }, /*  '88' */
    {  47,  76,  38 }, /*  '89' */
    {   0, 255,   0 }, /*  '90' */
    { 127, 255, 127 }, /*  '91' */
    {   0, 204,   0 }, /*  '92' */
    { 102, 204, 102 }, /*  '93' */
    {   0, 153,   0 }, /*  '94' */
    {  76, 153,  76 }, /*  '95' */
    {   0, 127,   0 }, /*  '96' */
    {  63, 127,  63 }, /*  '97' */
    {   0,  76,   0 }, /*  '98' */
    {  38,  76,  38 }, /*  '99' */
    {   0, 255,  63 }, /* '100' */
    { 127, 255, 159 }, /* '101' */
    {   0, 204,  51 }, /* '102' */
    { 102, 204, 127 }, /* '103' */
    {   0, 153,  38 }, /* '104' */
    {  76, 153,  95 }, /* '105' */
    {   0, 127,  31 }, /* '106' */
    {  63, 127,  79 }, /* '107' */
    {   0,  76,  19 }, /* '108' */
    {  38,  76,  47 }, /* '109' */
    {   0, 255, 127 }, /* '110' */
    { 127, 255, 191 }, /* '111' */
    {   0, 204, 102 }, /* '112' */
    { 102, 204, 153 }, /* '113' */
    {   0, 153,  76 }, /* '114' */
    {  76, 153, 114 }, /* '115' */
    {   0, 127,  63 }, /* '116' */
    {  63, 127,  95 }, /* '117' */
    {   0,  76,  38 }, /* '118' */
    {  38,  76,  57 }, /* '119' */
    {   0, 255, 191 }, /* '120' */
    { 127, 255, 223 }, /* '121' */
    {   0, 204, 153 }, /* '122' */
    { 102, 204, 178 }, /* '123' */
    {   0, 153, 114 }, /* '124' */
    {  76, 153, 133 }, /* '125' */
    {   0, 127,  95 }, /* '126' */
    {  63, 127, 111 }, /* '127' */
    {   0,  76,  57 }, /* '128' */
    {  38,  76,  66 }, /* '129' */
    {   0, 255, 255 }, /* '130' */
    { 127, 255, 255 }, /* '131' */
    {   0, 204, 204 }, /* '132' */
    { 102, 204, 204 }, /* '133' */
    {   0, 153, 153 }, /* '134' */
    {  76, 153, 153 }, /* '135' */
    {   0, 127, 127 }, /* '136' */
    {  63, 127, 127 }, /* '137' */
    {   0,  76,  76 }, /* '138' */
    {  38,  76,  76 }, /* '139' */
    {   0, 191, 255 }, /* '140' */
    { 127, 223, 255 }, /* '141' */
    {   0, 153, 204 }, /* '142' */
    { 102, 178, 204 }, /* '143' */
    {   0, 114, 153 }, /* '144' */
    {  76, 133, 153 }, /* '145' */
    {   0,  95, 127 }, /* '146' */
    {  63, 111, 127 }, /* '147' */
    {   0,  57,  76 }, /* '148' */
    {  38,  66,  76 }, /* '149' */
    {   0, 127, 255 }, /* '150' */
    { 127, 191, 255 }, /* '151' */
    {   0, 102, 204 }, /* '152' */
    { 102, 153, 204 }, /* '153' */
    {   0,  76, 153 }, /* '154' */
    {  76, 114, 153 }, /* '155' */
    {   0,  63, 127 }, /* '156' */
    {  63,  95, 127 }, /* '157' */
    {   0,  38,  76 }, /* '158' */
    {  38,  57,  76 }, /* '159' */
    {   0,  63, 255 }, /* '160' */
    { 127, 159, 255 }, /* '161' */
    {   0,  51, 204 }, /* '162' */
    { 102, 127, 204 }, /* '163' */
    {   0,  38, 153 }, /* '164' */
    {  76,  95, 153 }, /* '165' */
    {   0,  31, 127 }, /* '166' */
    {  63,  79, 127 }, /* '167' */
    {   0,  19,  76 }, /* '168' */
    {  38,  47,  76 }, /* '169' */
    {   0,   0, 255 }, /* '170' */
    { 127, 127, 255 }, /* '171' */
    {   0,   0, 204 }, /* '172' */
    { 102, 102, 204 }, /* '173' */
    {   0,   0, 153 }, /* '174' */
    {  76,  76, 153 }, /* '175' */
    {   0,   0, 127 }, /* '176' */
    {  63,  63, 127 }, /* '177' */
    {   0,   0,  76 }, /* '178' */
    {  38,  38,  76 }, /* '179' */
    {  63,   0, 255 }, /* '180' */
    { 159, 127, 255 }, /* '181' */
    {  51,   0, 204 }, /* '182' */
    { 127, 102, 204 }, /* '183' */
    {  38,   0, 153 }, /* '184' */
    {  95,  76, 153 }, /* '185' */
    {  31,   0, 127 }, /* '186' */
    {  79,  63, 127 }, /* '187' */
    {  19,   0,  76 }, /* '188' */
    {  47,  38,  76 }, /* '189' */
    { 127,   0, 255 }, /* '190' */
    { 191, 127, 255 }, /* '191' */
    { 102,   0, 204 }, /* '192' */
    { 153, 102, 204 }, /* '193' */
    {  76,   0, 153 }, /* '194' */
    { 114,  76, 153 }, /* '195' */
    {  63,   0, 127 }, /* '196' */
    {  95,  63, 127 }, /* '197' */
    {  38,   0,  76 }, /* '198' */
    {  57,  38,  76 }, /* '199' */
    { 191,   0, 255 }, /* '200' */
    { 223, 127, 255 }, /* '201' */
    { 153,   0, 204 }, /* '202' */
    { 178, 102, 204 }, /* '203' */
    { 114,   0, 153 }, /* '204' */
    { 133,  76, 153 }, /* '205' */
    {  95,   0, 127 }, /* '206' */
    { 111,  63, 127 }, /* '207' */
    {  57,   0,  76 }, /* '208' */
    {  66,  38,  76 }, /* '209' */
    { 255,   0, 255 }, /* '210' */
    { 255, 127, 255 }, /* '211' */
    { 204,   0, 204 }, /* '212' */
    { 204, 102, 204 }, /* '213' */
    { 153,   0, 153 }, /* '214' */
    { 153,  76, 153 }, /* '215' */
    { 127,   0, 127 }, /* '216' */
    { 127,  63, 127 }, /* '217' */
    {  76,   0,  76 }, /* '218' */
    {  76,  38,  76 }, /* '219' */
    { 255,   0, 191 }, /* '220' */
    { 255, 127, 223 }, /* '221' */
    { 204,   0, 153 }, /* '222' */
    { 204, 102, 178 }, /* '223' */
    { 153,   0, 114 }, /* '224' */
    { 153,  76, 133 }, /* '225' */
    { 127,   0,  95 }, /* '226' */
    { 127,  63, 111 }, /* '227' */
    {  76,   0,  57 }, /* '228' */
    {  76,  38,  66 }, /* '229' */
    { 255,   0, 127 }, /* '230' */
    { 255, 127, 191 }, /* '231' */
    { 204,   0, 102 }, /* '232' */
    { 204, 102, 153 }, /* '233' */
    { 153,   0,  76 }, /* '234' */
    { 153,  76, 114 }, /* '235' */
    { 127,   0,  63 }, /* '236' */
    { 127,  63,  95 }, /* '237' */
    {  76,   0,  38 }, /* '238' */
    {  76,  38,  57 }, /* '239' */
    { 255,   0,  63 }, /* '240' */
    { 255, 127, 159 }, /* '241' */
    { 204,   0,  51 }, /* '242' */
    { 204, 102, 127 }, /* '243' */
    { 153,   0,  38 }, /* '244' */
    { 153,  76,  95 }, /* '245' */
    { 127,   0,  31 }, /* '246' */
    { 127,  63,  79 }, /* '247' */
    {  76,   0,  19 }, /* '248' */
    {  76,  38,  47 }, /* '249' */
    {  51,  51,  51 }, /* '250' */
    {  91,  91,  91 }, /* '251' */
    { 132, 132, 132 }, /* '252' */
    { 173, 173, 173 }, /* '253' */
    { 214, 214, 214 }, /* '254' */
    { 255, 255, 255 }, /* '255' */
    {   0,   0,   0 }  /* '256' (BYLAYER) */
};


/* HUS Colors */
const EmbThread husThreads[] = {
    {{   0,   0,   0 }, "Black",        "TODO:HUS_CATALOG_NUMBER"},
    {{   0,   0, 255 }, "Blue",         "TODO:HUS_CATALOG_NUMBER"},
    {{   0, 255,   0 }, "Light Green",  "TODO:HUS_CATALOG_NUMBER"},
    {{ 255,   0,   0 }, "Red",          "TODO:HUS_CATALOG_NUMBER"},
    {{ 255,   0, 255 }, "Purple",       "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 255,   0 }, "Yellow",       "TODO:HUS_CATALOG_NUMBER"},
    {{ 127, 127, 127 }, "Gray",         "TODO:HUS_CATALOG_NUMBER"},
    {{  51, 154, 255 }, "Light Blue",   "TODO:HUS_CATALOG_NUMBER"},
    {{  51, 204, 102 }, "Green",        "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 127,   0 }, "Orange",       "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 160, 180 }, "Pink",         "TODO:HUS_CATALOG_NUMBER"},
    {{ 153,  75,   0 }, "Brown",        "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 255, 255 }, "White",        "TODO:HUS_CATALOG_NUMBER"},
    {{   0,   0, 127 }, "Dark Blue",    "TODO:HUS_CATALOG_NUMBER"},
    {{   0, 127,   0 }, "Dark Green",   "TODO:HUS_CATALOG_NUMBER"},
    {{ 127,   0,   0 }, "Dark Red",     "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 127, 127 }, "Light Red",    "TODO:HUS_CATALOG_NUMBER"},
    {{ 127,   0, 127 }, "Dark Purple",  "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 127, 255 }, "Light Purple", "TODO:HUS_CATALOG_NUMBER"},
    {{ 200, 200,   0 }, "Dark Yellow",  "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 255, 153 }, "Light Yellow", "TODO:HUS_CATALOG_NUMBER"},
    {{  60,  60,  60 }, "Dark Gray",    "TODO:HUS_CATALOG_NUMBER"},
    {{ 192, 192, 192 }, "Light Gray",   "TODO:HUS_CATALOG_NUMBER"},
    {{ 232,  63,   0 }, "Dark Orange",  "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 165,  65 }, "Light Orange", "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 102, 122 }, "Dark Pink",    "TODO:HUS_CATALOG_NUMBER"},
    {{ 255, 204, 204 }, "Light Pink",   "TODO:HUS_CATALOG_NUMBER"},
    {{ 115,  40,   0 }, "Dark Brown",   "TODO:HUS_CATALOG_NUMBER"},
    {{ 175,  90,  10 }, "Light Brown",  "TODO:HUS_CATALOG_NUMBER"}
};

const EmbThread jefThreads[] = {
    {{0, 0, 0}, "Placeholder", "000"},
    {{0, 0, 0}, "Black", "002"},
    {{255, 255, 255}, "White", "001"},
    {{255, 255, 23}, "Yellow", "204"},
    {{255, 102, 0}, "Orange", "203"},
    {{47, 89, 51}, "Olive Green", "219"},
    {{35, 115, 54}, "Green", "226"},
    {{101, 194, 200}, "Sky", "217"},
    {{171, 90, 150}, "Purple", "208"},
    {{246, 105, 160}, "Pink", "201"},
    {{255, 0, 0}, "Red", "225"},
    {{177, 112, 78}, "Brown", "214"},
    {{11, 47, 132}, "Blue", "207"},
    {{228, 195, 93}, "Gold", "003"},
    {{72, 26, 5}, "Dark Brown", "205"},
    {{172, 156, 199}, "Pale Violet", "209"},
    {{252, 242, 148}, "Pale Yellow", "210"},
    {{249, 153, 183}, "Pale Pink", "211"},
    {{250, 179, 129}, "Peach", "212"},
    {{201, 164, 128}, "Beige", "213"},
    {{151, 5, 51}, "Wine Red", "215"},
    {{160, 184, 204}, "Pale Sky", "216"},
    {{127, 194, 28}, "Yellow Green", "218"},
    {{229, 229, 229}, "Silver Gray", "220"},
    {{136, 155, 155}, "Gray", "221"},
    {{152, 214, 189}, "Pale Aqua", "227"},
    {{178, 225, 227}, "Baby Blue", "228"},
    {{54, 139, 160}, "Powder Blue", "229"},
    {{79, 131, 171}, "Bright Blue", "230"},
    {{56, 106, 145}, "Slate Blue", "231"},
    {{7, 22, 80}, "Navy Blue", "232"},
    {{249, 153, 162}, "Salmon Pink", "233"},
    {{249, 103, 107}, "Coral", "234"},
    {{227, 49, 31}, "Burnt Orange", "235"},
    {{226, 161, 136}, "Cinnamon", "236"},
    {{181, 148, 116}, "Umber", "237"},
    {{228, 207, 153}, "Blond", "238"},
    {{255, 203, 0}, "Sunflower", "239"},
    {{225, 173, 212}, "Orchid Pink", "240"},
    {{195, 0, 126}, "Peony Purple", "241"},
    {{128, 0, 75}, "Burgundy", "242"},
    {{84, 5, 113}, "Royal Purple", "243"},
    {{177, 5, 37}, "Cardinal Red", "244"},
    {{202, 224, 192}, "Opal Green", "245"},
    {{137, 152, 86}, "Moss Green", "246"},
    {{92, 148, 26}, "Meadow Green", "247"},
    {{0, 49, 20}, "Dark Green", "248"},
    {{93, 174, 148}, "Aquamarine", "249"},
    {{76, 191, 143}, "Emerald Green", "250"},
    {{0, 119, 114}, "Peacock Green", "251"},
    {{89, 91, 97}, "Dark Gray", "252"},
    {{255, 255, 242}, "Ivory White", "253"},
    {{177, 88, 24}, "Hazel", "254"},
    {{203, 138, 7}, "Toast", "255"},
    {{152, 108, 128}, "Salmon", "256"},
    {{152, 105, 45}, "Cocoa Brown", "257"},
    {{77, 52, 25}, "Sienna", "258"},
    {{76, 51, 11}, "Sepia", "259"},
    {{51, 32, 10}, "Dark Sepia", "260"},
    {{82, 58, 151}, "Violet Blue", "261"},
    {{13, 33, 126}, "Blue Ink", "262"},
    {{30, 119, 172}, "Sola Blue", "263"},
    {{178, 221, 83}, "Green Dust", "264"},
    {{243, 54, 137}, "Crimson", "265"},
    {{222, 100, 158}, "Floral Pink", "266"},
    {{152, 65, 97}, "Wine", "267"},
    {{76, 86, 18}, "Olive Drab", "268"},
    {{76, 136, 31}, "Meadow", "269"},
    {{228, 222, 121}, "Mustard", "270"},
    {{203, 138, 26}, "Yellow Ocher", "271"},
    {{203, 162, 28}, "Old Gold", "272"},
    {{255, 152, 5}, "Honey Dew", "273"},
    {{252, 178, 87}, "Tangerine", "274"},
    {{0xFF, 0xE5, 0x05}, "Canary Yellow", "275"},
    {{0xF0, 0x33, 0x1F}, "Vermilion", "202"},
    {{0x1A, 0x84, 0x2D}, "Bright Green", "206"},
    {{0x38, 0x6C, 0xAE}, "Ocean Blue", "222"},
    {{0xE3, 0xC4, 0xB4}, "Beige Gray", "223"},
    {{0xE3, 0xAC, 0x81}, "Bamboo", "224"}
};

/* SHV Colors */
const int shvThreadCount = 42;
const EmbThread shvThreads[] = {
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0, 255 }, "Blue",         "TODO:CATALOG_NUMBER"},
    {{  51, 204, 102 }, "Green",        "TODO:CATALOG_NUMBER"},
    {{ 255,   0,   0 }, "Red",          "TODO:CATALOG_NUMBER"},
    {{ 255,   0, 255 }, "Purple",       "TODO:CATALOG_NUMBER"},
    {{ 255, 255,   0 }, "Yellow",       "TODO:CATALOG_NUMBER"},
    {{ 127, 127, 127 }, "Grey",         "TODO:CATALOG_NUMBER"},
    {{  51, 154, 255 }, "Light Blue",   "TODO:CATALOG_NUMBER"},
    {{   0, 255,   0 }, "Light Green",  "TODO:CATALOG_NUMBER"},
    {{ 255, 127,   0 }, "Orange",       "TODO:CATALOG_NUMBER"},
    {{ 255, 160, 180 }, "Pink",         "TODO:CATALOG_NUMBER"},
    {{ 153,  75,   0 }, "Brown",        "TODO:CATALOG_NUMBER"},
    {{ 255, 255, 255 }, "White",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{ 255, 127, 127 }, "Light Red",    "TODO:CATALOG_NUMBER"},
    {{ 255, 127, 255 }, "Light Purple", "TODO:CATALOG_NUMBER"},
    {{ 255, 255, 153 }, "Light Yellow", "TODO:CATALOG_NUMBER"},
    {{ 192, 192, 192 }, "Light Grey",   "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{ 255, 165,  65 }, "Light Orange", "TODO:CATALOG_NUMBER"},
    {{ 255, 204, 204 }, "Light Pink",   "TODO:CATALOG_NUMBER"},
    {{ 175,  90,  10 }, "Light Brown",  "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0, 127 }, "Dark Blue",    "TODO:CATALOG_NUMBER"},
    {{   0, 127,   0 }, "Dark Green",   "TODO:CATALOG_NUMBER"},
    {{ 127,   0,   0 }, "Dark Red",     "TODO:CATALOG_NUMBER"},
    {{ 127,   0, 127 }, "Dark Purple",  "TODO:CATALOG_NUMBER"},
    {{ 200, 200,   0 }, "Dark Yellow",  "TODO:CATALOG_NUMBER"},
    {{  60,  60,  60 }, "Dark Gray",    "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{   0,   0,   0 }, "Black",        "TODO:CATALOG_NUMBER"},
    {{ 232,  63,   0 }, "Dark Orange",  "TODO:CATALOG_NUMBER"},
    {{ 255, 102, 122 }, "Dark Pink",    "TODO:CATALOG_NUMBER"}
};

const EmbThread pcmThreads[] = {
    {{0x00, 0x00, 0x00}, "PCM Color 1", ""},
    {{0x00, 0x00, 0x80}, "PCM Color 2", ""},
    {{0x00, 0x00, 0xFF}, "PCM Color 3", ""},
    {{0x00, 0x80, 0x80}, "PCM Color 4", ""},
    {{0x00, 0xFF, 0xFF}, "PCM Color 5", ""},
    {{0x80, 0x00, 0x80}, "PCM Color 6", ""},
    {{0xFF, 0x00, 0xFF}, "PCM Color 7", ""},
    {{0x80, 0x00, 0x00}, "PCM Color 8", ""},
    {{0xFF, 0x00, 0x00}, "PCM Color 9", ""},
    {{0x00, 0x80, 0x00}, "PCM Color 10", ""},
    {{0x00, 0xFF, 0x00}, "PCM Color 11", ""},
    {{0x80, 0x80, 0x00}, "PCM Color 12", ""},
    {{0xFF, 0xFF, 0x00}, "PCM Color 13", ""},
    {{0x80, 0x80, 0x80}, "PCM Color 14", ""},
    {{0xC0, 0xC0, 0xC0}, "PCM Color 15", ""},
    {{0xFF, 0xFF, 0xFF}, "PCM Color 16", ""}
};

const int pecThreadCount = 65;
const EmbThread pecThreads[] = {
    {{  0,   0,   0}, "Unknown",         ""}, /* Index  0 */
    {{ 14,  31, 124}, "Prussian Blue",   ""}, /* Index  1 */
    {{ 10,  85, 163}, "Blue",            ""}, /* Index  2 */
/* TODO: Verify RGB value is correct */
    {{  0, 135, 119}, "Teal Green",      ""}, /* Index  3 */
    {{ 75, 107, 175}, "Cornflower Blue", ""}, /* Index  4 */
    {{237,  23,  31}, "Red",             ""}, /* Index  5 */
    {{209,  92,   0}, "Reddish Brown",   ""}, /* Index  6 */
    {{145,  54, 151}, "Magenta",         ""}, /* Index  7 */
    {{228, 154, 203}, "Light Lilac",     ""}, /* Index  8 */
    {{145,  95, 172}, "Lilac",           ""}, /* Index  9 */
/* TODO: Verify RGB value is correct */
    {{158, 214, 125}, "Mint Green",      ""}, /* Index 10 */
    {{232, 169,   0}, "Deep Gold",       ""}, /* Index 11 */
    {{254, 186,  53}, "Orange",          ""}, /* Index 12 */
    {{255, 255,   0}, "Yellow",          ""}, /* Index 13 */
    {{112, 188,  31}, "Lime Green",      ""}, /* Index 14 */
    {{186, 152,   0}, "Brass",           ""}, /* Index 15 */
    {{168, 168, 168}, "Silver",          ""}, /* Index 16 */
/* TODO: Verify RGB value is correct */
    {{125, 111,   0}, "Russet Brown",    ""}, /* Index 17 */
    {{255, 255, 179}, "Cream Brown",     ""}, /* Index 18 */
    {{ 79,  85,  86}, "Pewter",          ""}, /* Index 19 */
    {{  0,   0,   0}, "Black",           ""}, /* Index 20 */
    {{ 11,  61, 145}, "Ultramarine",     ""}, /* Index 21 */
    {{119,   1, 118}, "Royal Purple",    ""}, /* Index 22 */
    {{ 41,  49,  51}, "Dark Gray",       ""}, /* Index 23 */
    {{ 42,  19,   1}, "Dark Brown",      ""}, /* Index 24 */
    {{246,  74, 138}, "Deep Rose",       ""}, /* Index 25 */
    {{178, 118,  36}, "Light Brown",     ""}, /* Index 26 */
/* TODO: Verify RGB value is correct */
    {{252, 187, 197}, "Salmon Pink",     ""}, /* Index 27 */
    {{254,  55,  15}, "Vermillion",      ""}, /* Index 28 */
    {{240, 240, 240}, "White",           ""}, /* Index 29 */
    {{106,  28, 138}, "Violet",          ""}, /* Index 30 */
    {{168, 221, 196}, "Seacrest",        ""}, /* Index 31 */
    {{ 37, 132, 187}, "Sky Blue",        ""}, /* Index 32 */
    {{254, 179,  67}, "Pumpkin",         ""}, /* Index 33 */
    {{255, 243, 107}, "Cream Yellow",    ""}, /* Index 34 */
    {{208, 166,  96}, "Khaki",           ""}, /* Index 35 */
    {{209,  84,   0}, "Clay Brown",      ""}, /* Index 36 */
    {{102, 186,  73}, "Leaf Green",      ""}, /* Index 37 */
    {{ 19,  74,  70}, "Peacock Blue",    ""}, /* Index 38 */
    {{135, 135, 135}, "Gray",            ""}, /* Index 39 */
/* TODO: Verify RGB value is correct */
    {{216, 204, 198}, "Warm Gray",       ""}, /* Index 40 */
    {{ 67,  86,   7}, "Dark Olive",      ""}, /* Index 41 */
/* TODO: Verify RGB value is correct */
    {{253, 217, 222}, "Flesh Pink",      ""}, /* Index 42 */
    {{249, 147, 188}, "Pink",            ""}, /* Index 43 */
    {{  0,  56,  34}, "Deep Green",      ""}, /* Index 44 */
    {{178, 175, 212}, "Lavender",        ""}, /* Index 45 */
    {{104, 106, 176}, "Wisteria Violet", ""}, /* Index 46 */
    {{239, 227, 185}, "Beige",           ""}, /* Index 47 */
    {{247,  56, 102}, "Carmine",         ""}, /* Index 48 */
/* TODO: Verify RGB value is correct */
    {{181,  75, 100}, "Amber Red",       ""}, /* Index 49 */
    {{ 19,  43,  26}, "Olive Green",     ""}, /* Index 50 */
/* TODO: Verify RGB value is correct */
    {{199,   1,  86}, "Dark Fuschia",    ""}, /* Index 51 */
    {{254, 158,  50}, "Tangerine",       ""}, /* Index 52 */
    {{168, 222, 235}, "Light Blue",      ""}, /* Index 53 */
/* TODO: Verify RGB value is correct */
    {{  0, 103,  62}, "Emerald Green",   ""}, /* Index 54 */
    {{ 78,  41, 144}, "Purple",          ""}, /* Index 55 */
    {{ 47, 126,  32}, "Moss Green",      ""}, /* Index 56 */
/* TODO: Verify RGB value is correct */
/* TODO: Flesh Pink is Index 42, is this Index incorrect? */
    {{255, 204, 204}, "Flesh Pink",      ""}, /* Index 57 */
    {{255, 217,  17}, "Harvest Gold",    ""}, /* Index 58 */
    {{  9,  91, 166}, "Electric Blue",   ""}, /* Index 59 */
    {{240, 249, 112}, "Lemon Yellow",    ""}, /* Index 60 */
    {{227, 243,  91}, "Fresh Green",     ""}, /* Index 61 */
/* TODO: Verify RGB value is correct */
/* TODO: Orange is Index 12, is this Index incorrect? */
    {{255, 153,   0}, "Orange",          ""}, /* Index 62 */
/* TODO: Verify RGB value is correct */
/* TODO: Cream Yellow is Index 34, is this Index incorrect? */
    {{255, 240, 141}, "Cream Yellow",    ""}, /* Index 63 */
    {{255, 200, 200}, "Applique",        ""}  /* Index 64 */
};

/* Converted from the table at:
 *     https://www.w3.org/TR/SVGb/types.html#ColorKeywords
 * NOTE: This supports both UK and US English names, so the repeated values
 * aren't an error.
 */
thread_color svg_color_codes[] = {
    {"aliceblue", 0xFFf0f8ff, 0},
    {"antiquewhite", 0xFFfaebd7, 1},
    {"aqua", 0xFF00ffff, 2},
    {"aquamarine", 0xFF7fffd4, 3},
    {"azure", 0xFFf0ffff, 4},
    {"beige", 0xFFf5f5dc, 5},
    {"bisque", 0xFFffe4c4, 6},
    {"black", 0xFF000000, 7},
    {"blanchedalmond", 0xFFffebcd, 8},
    {"blue", 0xFF0000ff, 9},
    {"blueviolet", 0xFF8a2be2, 10},
    {"brown", 0xFFa52a2a, 11},
    {"burlywood", 0xFFdeb81b, 12},
    {"cadetblue", 0xFF5f9ea0, 13},
    {"chartreuse", 0xFF7fff00, 14},
    {"chocolate", 0xFFd22d1e, 15},
    {"coral", 0xFFFF7f0e, 16},
    {"cornflowerblue", 0xFF1c5fed, 17},
    {"cornsilk", 0xFFfff8dc, 18},
    {"crimson", 0xFFdc0e3c, 19},
    {"cyan", 0xFF00ffff, 20},
    {"darkblue", 0xFF00008b, 21},
    {"darkcyan", 0xFF008b8b, 22},
    {"darkgoldenrod", 0xFFb81a0b, 23},
    {"darkgray", 0xFFa9a9a9, 24},
    {"darkgreen", 0xFF001c00, 25},
    {"darkgrey", 0xFFa9a9a9, 26},
    {"darkkhaki", 0xFFbdb76b, 27},
    {"darkmagenta", 0xFF8b008b, 28},
    {"darkolivegreen", 0xFF0d6b2f, 29},
    {"darkorange", 0xFFff8c00, 30},
    {"darkorchid", 0xFF3f0ecc, 31},
    {"darkred", 0xFF8b0000, 32},
    {"darksalmon", 0xFFe93c7a, 33},
    {"darkseagreen", 0xFF8fbc8f, 34},
    {"darkslateblue", 0xFF1e3d8b, 35},
    {"darkslategray", 0xFF2f4f4f, 36},
    {"darkslategrey", 0xFF2f4f4f, 37},
    {"darkturquoise", 0xFF00ced1, 38},
    {"darkviolet", 0xFF5e00d3, 39},
    {"deeppink", 0xFFff0e5d, 40},
    {"deepskyblue", 0xFF00bfff, 41},
    {"dimgray", 0xFF2d2d2d, 42},
    {"dimgrey", 0xFF2d2d2d, 43},
    {"dodgerblue", 0xFF1e5aff, 44},
    {"firebrick", 0xFFb20a0a, 45},
    {"floralwhite", 0xFFfffaf0, 46},
    {"forestgreen", 0xFF0a8b0a, 47},
    {"fuchsia", 0xFFff00ff, 48},
    {"gainsboro", 0xFFdcdcdc, 49},
    {"ghostwhite", 0xFFf8f8ff, 50},
    {"gold", 0xFFffd700, 51},
    {"goldenrod", 0xFFdaa50e, 52},
    {"gray", 0xFF0e0e0e, 53},
    {"grey", 0xFF0e0e0e, 54},
    {"green", 0xFF000e00, 55},
    {"greenyellow", 0xFFadff2f, 56},
    {"honeydew", 0xFFf0fff0, 57},
    {"hotpink", 0xFFff2db4, 58},
    {"indianred", 0xFFcd5c5c, 59},
    {"indigo", 0xFF4b000a, 60},
    {"ivory", 0xFFfffff0, 61},
    {"khaki", 0xFFf0e68c, 62},
    {"lavender", 0xFFe6e6fa, 63},
    {"lavenderblush", 0xFFfff0f5, 64},
    {"lawngreen", 0xFF7cfc00, 65},
    {"lemonchiffon", 0xFFfffacd, 66},
    {"lightblue", 0xFFadd8e6, 67},
    {"lightcoral", 0xFFf00e0e, 68},
    {"lightcyan", 0xFFe0ffff, 69},
    {"lightgoldenrodyellow", 0xFFfafad2, 70},
    {"lightgray", 0xFFd3d3d3, 71},
    {"lightgreen", 0xFF5aee5a, 72},
    {"lightgrey", 0xFFd3d3d3, 73},
    {"lightpink", 0xFFffb6c1, 74},
    {"lightsalmon", 0xFFffa07a, 75},
    {"lightseagreen", 0xFF0eb2aa, 76},
    {"lightskyblue", 0xFF1bcefa, 77},
    {"lightslategray", 0xFF4d3a3f, 78},
    {"lightslategrey", 0xFF4d3a3f, 79},
    {"lightsteelblue", 0xFFb0c4de, 80},
    {"lightyellow", 0xFFffffe0, 81},
    {"lime", 0xFF00ff00, 82},
    {"limegreen", 0xFF0ecd0e, 83},
    {"linen", 0xFFfaf0e6, 84},
    {"magenta", 0xFFff00ff, 85},
    {"maroon", 0xFF0e0000, 86},
    {"mediumaquamarine", 0xFF2acdaa, 87},
    {"mediumblue", 0xFF0000cd, 88},
    {"mediumorchid", 0xFFba0dd3, 89},
    {"mediumpurple", 0xFF5d2edb, 90},
    {"mediumseagreen", 0xFF3cb32f, 91},
    {"mediumslateblue", 0xFF7b2cee, 92},
    {"mediumspringgreen", 0xFF00fa9a, 93},
    {"mediumturquoise", 0xFF1ed1cc, 94},
    {"mediumvioletred", 0xFFc70f0d, 95},
    {"midnightblue", 0xFF0d0d2e, 96},
    {"mintcream", 0xFFf5fffa, 97},
    {"mistyrose", 0xFFffe4e1, 98},
    {"moccasin", 0xFFffe4b5, 99},
    {"navajowhite", 0xFFffdead, 100},
    {"navy", 0xFF00000e, 101},
    {"oldlace", 0xFFfdf5e6, 102},
    {"olive", 0xFF0e0e00, 103},
    {"olivedrab", 0xFF6b8e0b, 104},
    {"orange", 0xFFffa500, 105},
    {"orangered", 0xFFff2d00, 106},
    {"orchid", 0xFFda2ed6, 107},
    {"palegoldenrod", 0xFFeee8aa, 109},
    {"palegreen", 0xFF3efb3e, 110},
    {"paleturquoise", 0xFFafeeee, 111},
    {"palevioletred", 0xFFdb2e5d, 112},
    {"papayawhip", 0xFFffefd5, 113},
    {"peachpuff", 0xFFffdab9, 114},
    {"peru", 0xFFcd0d3f, 115},
    {"pink", 0xFFffc0cb, 116},
    {"plum", 0xFFdda0dd, 117},
    {"powderblue", 0xFFb0e0e6, 118},
    {"purple", 0xFF0e000e, 119},
    {"red", 0xFFff0000, 120},
    {"rosybrown", 0xFFbc8f8f, 121},
    {"royalblue", 0xFF1d2de1, 122},
    {"saddlebrown", 0xFF8b2d0d, 123},
    {"salmon", 0xFFfa0e1e, 124},
    {"sandybrown", 0xFFf4a43c, 125},
    {"seagreen", 0xFF2e8b1b, 126},
    {"seashell", 0xFFfff5ee, 127},
    {"sienna", 0xFFa00a2d, 128},
    {"silver", 0xFFc0c0c0, 129},
    {"skyblue", 0xFF1bceeb, 130},
    {"slateblue", 0xFF6a5acd, 131},
    {"slategray", 0xFF2e0e5a, 132},
    {"slategrey", 0xFF2e0e5a, 133},
    {"snow", 0xFFfffafa, 134},
    {"springgreen", 0xFF00ff7f, 135},
    {"steelblue", 0xFF2e0ab4, 136},
    {"tan", 0xFFd2b48c, 137},
    {"teal", 0xFF000e0e, 138},
    {"thistle", 0xFFd8bfd8, 139},
    {"tomato", 0xFFff3f2f, 140},
    {"turquoise", 0xFF1ce0d0, 141},
    {"violet", 0xFFee0aee, 142},
    {"wheat", 0xFFf5deb3, 143},
    {"white", 0xFFffffff, 144},
    {"whitesmoke", 0xFFf5f5f5, 145},
    {"yellow", 0xFFffff00, 146},
    {"yellowgreen", 0xFF9acd0e, 147},
    {"END", 0, -1}
};

/* Thread colors that are subject to change are loaded at runtime,
 * allowing us to update them as they change.
 *
 * However, in-builts that use indicies like the DXF, SVG or HUS
 * tables are compiled in. This should help with embedded compatibility
 * in both cases.
 */
typedef struct BRAND {
    thread_color *codes;
    int length;
    EmbString label;
} EmbBrand;

EmbBrand brand_codes[100];

/* Internally, we use fixed-point arithmetic because it can be made more
 * consistent.
 *
 * The maximum integer value is 32767, so with a place value of 0.1 the
 * maximum distance is 3276.7 mm which is around 3 metres. In longer
 * calculations this means that we can have stacked errors that cause issues.
 *
 * However, since 2 byte, fixed-point real types are appropriate for most
 * scenarios: if this is a issue for a specific calculation then we recommend
 * that authors scale up then scale down what they're working on. If it
 * continues to be an issue please describe your use case, along with a
 * description of your art, to us at the issues page on:
 *     https://github.com/embroidermodder/libembroidery
 */
#define DEFAULT_PLACE_VALUE        (0.1)

/* INTERNAL POSTSCRIPT INTERPRETER
 * -------------------------------
 *
 * Eventually we want all dependencies of libembroidery to be only c standard
 * libraries and we also need the interpreter to integrate well with our
 * own virtual machine. So this experiment is to establish that this works.
 */

/* PostScript data types */
#define STRING_TYPE                    0
#define ARRAY_TYPE                     1
#define REAL_TYPE                      2
#define INT_TYPE                       3
#define BOOL_TYPE                      4
#define NAME_TYPE                      5
#define DICTIONARY_TYPE                6

static char postscript_data_type[][20] = {
    "string",
    "array",
    "real",
    "int",
    "bool",
    "name",
    "dictionary"
};

/* Attributes */
#define LITERAL_ATTR                   0
#define EXEC_ATTR                      1

typedef struct EmbStackElement_ {
    int data_type;
    int attribute;
    int i;
    float r;
    char s[100];
} EmbStackElement;

/* This uses about 100kb per instance because it's not dynamic. */
typedef struct EmbStack_ {
    EmbStackElement stack[1000];
    int position;
} EmbStack;

int emb_repl(void);
void execute_postscript(EmbStack *stack, char line[200]);
void analyse_stack(EmbStack *stack);

static char in_built_functions[][20] = {
    "add",
    "mul",
    "quit",
    ""
};

/* .
 */
void
analyse_stack(EmbStack *stack)
{
    int i;
    for (i=0; i<stack->position; i++) {
        EmbStackElement element = stack->stack[i];
        printf("%d ", i);
        if ((element.data_type >= 0) && (element.data_type <= DICTIONARY_TYPE)) {
            printf("%s", postscript_data_type[element.data_type]);
        }
        else {
            printf("unknown");
        }
        printf(" ");
        if (element.attribute) {
            printf("exec");
        }
        else {
            printf("literal");
        }
        printf(" %s\n", element.s);
    }
}

/* .
 */
int
identify_token(EmbStackElement *element)
{
    int i, j;
    int all_digits = 1;
    int decimal_place_present = 0;
    i = 0;
    j = 0;
    for (j=0; in_built_functions[j][0]; j++) {
        if (string_equals(in_built_functions[j], element->s)) {
            element->data_type = NAME_TYPE;
            element->attribute = EXEC_ATTR;
            return NAME_TYPE;
        }
    }

    element->attribute = LITERAL_ATTR;

    if (element->s[0] == '-') {
        i++;
    }
    if (element->s[0] == '"') {
        element->data_type = STRING_TYPE;
        return STRING_TYPE;
    }
    for (; element->s[i] && (i < 200); i++) {
        if ((element->s[i] < '0') || (element->s[i] > '9')) {
            all_digits = 0;
        }
        if (element->s[i] == '.') {
            decimal_place_present++;
        }
    }
    if (all_digits) {
        if (decimal_place_present == 0) {
            element->data_type = INT_TYPE;
            return INT_TYPE;
        }
        if (decimal_place_present == 1) {
            element->data_type = REAL_TYPE;
            return REAL_TYPE;
        }
        /* Multiple decimal points in one float error. */
        return -2;
    }
    /* ERROR CODE */
    return -1;
}

/* .
 */
void
append_token(EmbStack *stack, char token[200])
{
    if (token[0] == 0) {
        return;
    }
    string_copy(stack->stack[stack->position].s, token);
    identify_token(stack->stack + stack->position);
    stack->position++;    
}

/* .
 */
void
tokenize_line(EmbStack *stack, char line[200])
{
    char current_token[200];
    int i, j;
    j = 0;
    for (i=0; line[i]; i++) {
        if (line[i] == ' ') {
            current_token[j] = 0;
            append_token(stack, current_token);
            j = 0;
        }
        else {
            current_token[j] = line[i];
            j++;
        }
    }
    if (string_len(line) > 0) {
        current_token[j] = 0;
        append_token(stack, current_token);
    }
}

/* .
 */
void
execute_postscript(EmbStack *stack, char line[200])
{
    tokenize_line(stack, line);
    analyse_stack(stack);
}

/* .
 */
int
emb_repl(void)
{
    EmbStack stack;
    stack.position = 0;

    puts("embroider 1.0.0-alpha");
    puts("    Copyright 2018-2024 The Embroidermodder Team.");
    puts("    Licensed under the terms of the zlib license.");
    puts("");
    puts("    https://www.libembroidery.org");
    puts("");
    puts("                             WARNING");
    puts("-----------------------------------------------------------------------");
    puts("    embroider is under active development and is not yet");
    puts("    ready for any serious use. Please only use in experimental contexts");
    puts("    not as part of your general workflow.");
    puts("");
    puts("    This interpreter has only just been started, try using the");
    puts("    --help flag for other features.");
    puts("-----------------------------------------------------------------------");
    puts("");

    int running = 1;
    while (running) {
        char line[200];
        int i = 0;
        unsigned char c = 0;
        printf("emb> ");
        while (c != EOF) {
            c = fgetc(stdin);
            /* Any non-printable character breaks the "getting characters from
             * the terminal loop".
             */
            if ((c < 0x20) || (c >= 0x80)) {
                break;
            }
            line[i] = c;
            i++;
            if (i == 200) {
                puts("Error: input line too long, please break up your command.");
            }
        }
        line[i] = 0;
        execute_postscript(&stack, line);
        if (string_equals(line, "quit")) {
            running = 0;
        }
    }
    return 0;
}

static int
emb_int_from_bytes(const char *program, int i)
{
    return 256*program[i] + program[i+1];
}

static EmbReal
emb_real_from_bytes(const char *program, int i)
{
    return DEFAULT_PLACE_VALUE * emb_int_from_bytes(program, i);
}

static EmbVector
emb_vector_from_bytes(const char *program, int i)
{
    EmbVector v;
    v.x = emb_real_from_bytes(program, i);
    v.y = emb_real_from_bytes(program, i+2);
    return v;
}

/* Our virtual machine
 * -------------------
 *
 * Program state is altered via this function, all other functions
 * pass the program state back and forth to keep it thread-safe.
 *
 * Variables are packed into and removed from this state, the stack is embedded
 * into it. To manage memory each stack item names its successor, or is a negative
 * number indicating that the stack terminates there.
 *
 * DATA TYPE FLAG
 * --------------
 *
 * STRING (any value <=100): which is also the length of the string.
 * INT (101): integer in the range (-32767, 32767).
 * REAL (102): fixed-point real number in the range (-3276.7, 3276.7).
 * FUNCTION (103): interpret the data as an index in the predefined function
 *                 table.
 * VARIABLE (104): reference to memory location outside of the stack.
 *
 * EXAMPLE STACK
 * -------------
 *
 * Stack element 0:
 *     description: (3, BYTE, "a")
 *     literally: {3, , 97}
 *
 * Stack element 1:
 *     description: (6, BYTE, 0)
 *     literally: {6, 0, 0}
 *
 * Stack element 2:
 *     description: (10, REAL, 21.1)
 *     literally: {10, 1, 0, 211}
 *
 * Stack element 3:
 *     description: (-1, REAL, 32.1)
 *     literally: {-1, 1, 1, 55}
 *
 * Altogether, this stack is: ("a", 21.1, 32.1)
 * Literally: {3, 0, 97, 6, 0, 0
 *
 * In order to ensure that the processor is running correctly, each processor
 * call can be alternated with a full stack analysis printout that looks like
 * this.
 */
void
emb_processor(char *state, const char *program, int program_length)
{
    int i;
    for (i=0; i<program_length; i++) {
        switch (program[i]) {
        case EMB_CMD_ARC: {
            if (focussed_pattern == NULL) {
                puts("ERROR: there is no focussed pattern, so the arc command cannot be run.");
                return;
            }
            EmbVector p1 = emb_vector_from_bytes(program, i+1);
            EmbVector p2 = emb_vector_from_bytes(program, i+5);
            
            i += 8;
            break;
        }
        case EMB_CMD_CIRCLE: {
            if (focussed_pattern == NULL) {
                puts("ERROR: there is no focussed pattern, so the circle command cannot be run.");
                return;
            }
            EmbVector center = emb_vector_from_bytes(program, i+1);
            EmbReal r = emb_real_from_bytes(program, i+5);

            i += 6;
            break;
        }
        default: {
            puts("Program command not defined.");
            break;
        }
        }
    }
}

/*
 *
 */
void
emb_postscript_compiler(const char *program, char *compiled_program)
{

}

/* The actuator works by creating an on-the-fly EmbProgramState so external
 * callers don't have to manage memory over longer sessions.
 *
 * It also compiles down our command line arguments, postscript and SVG
 * defines etc. into a common "machine code" like program.
 */
int
emb_compiler(const char *program, int language, char *compiled_program)
{
    int i = 0;
    int output_length = 0;
    compiled_program[i] = 0;
    switch (language) {
    case LANG_PS: {
        emb_postscript_compiler(program, compiled_program);
        break;
    }
    default: {
        break;
    }
    }
    return output_length;
}

/* Calls the compiler, then runs the compiled program. */
void
emb_actuator(const char *program, int language)
{
    char *state = malloc(1000);
    char *compiled_program = malloc(1000);
    int output_length = emb_compiler(program, language, compiled_program);
    emb_processor(state, compiled_program, output_length);
    safe_free(compiled_program);
    safe_free(state);
}

/*
 *
 */
void
string_copy(char *dst, const char *src)
{
    int i;
    for (i=0; i<200; i++) {
        dst[i] = src[i];
        if (src[i] == 0) {
            break;
        }
    }
    dst[199] = 0;
}

/* Finds the location of the first non-whitespace character
 * in the string and returns it.
 */
int
string_whitespace(const char *s)
{
    int i;
    for (i=0; i<200; i++) {
        if (s[i] == ' ') continue;
        if (s[i] == '\t') continue;
        if (s[i] == '\r') continue;
        if (s[i] == '\n') continue;
        return i;
    }
    return i;
}

/* Note that our version of strlen can tell us that
 * the string is not null-terminated by returning -1.
 */
int
string_len(const char *src)
{
    int i;
    for (i=0; i<200; i++) {
        if (src[i] == 0) {
            return i;
        }
    }
    return -1;
}

/* Replacement for strcat that is only to be used for
 * short strings, otherwise use memory_copy.
 */
void
string_cat(char *dst, const char *src)
{
    int i, j, src_len;
    j = string_len(dst);
    src_len = string_len(src)+1;
    for (i=0; i<src_len; i++) {
        dst[j+i] = src[i];
        if (src[i] == 0) {
            return;
        }
        if (i+j == 200) {
            break;
        }
    }
    puts("ERROR: string_cat failed to concatenate because the source string");
    puts("    was too long.");
    dst[199] = 0;
}

/*
 */
int
string_equals(const char *s1, const char *s2)
{
    int i;
    for (i=0; i<200; i++) {
        if (s1[i] != s2[i]) {
            return 0;
        }
        if (s1[i] == 0) {
            if (s2[i] == 0) {
                return 1;
            }
            return 0;
        }
    }
	/* Strings which aren't null-terminated are treated as unequal.
	 * The caller should be warned with an arror string.
     */
    return 0;
}

/*
 */
int
string_rchar(const char *s, char c)
{
	int i;
	int n = string_len(s);
	for (i=n-1; i>=0; i++) {
		if (s[i] == c) {
			return i;
		}
	}
	return 0;
}

/* Replacement for memcpy. To allow us to take out
 * "string.h" entirely.
 */
void
memory_copy(void *dst, const void *src, int n)
{
    int i;
    char *dst_, *src_;
    dst_ = (char *)dst;
    src_ = (char *)src;
    for (i=0; i<n; i++) {
        dst_[i] = src_[i];
    }
}

/* Replacement for memcmp. To allow us to take out
 * "string.h" entirely.
 */
char
memory_cmp(void *dst, const void *src, int n)
{
    size_t i;
    char *dst_, *src_;
    dst_ = (char *)dst;
    src_ = (char *)src;
    for (i=0; i<n; i++) {
        char result = dst_[i] - src_[i];
        if (result) {
            return result;
        }
    }
    return 0;
}

/* Replacement for memset. To allow us to take out
 * "string.h" entirely. 
 */
char
memory_set(void *dst, char value, int n)
{
    int i;
    char *dst_ = (char*)dst;
    for (i=0; i<n; i++) {
        dst_[i] = value;
    }
}

/* ENCODING SECTION
 * ----------------------------------------------------------------------------
 *
 * The functions in this section are grouped together to aid the developer's
 * understanding of the similarities between the file formats. This also helps
 * reduce errors between reimplementation of the same idea.
 *
 * For example: the Tajima ternary encoding of positions is used by at least 4
 * formats and the only part that changes is the flag encoding.
 *
 * Converts a 6 digit hex string (I.E. "00FF00")
 * into an EmbColor and returns it.
 *
 * a val 6 byte code describing the color as a hex string, doesn't require null termination.
 * Returns EmbColor the same color as our internal type.
 */
EmbColor
embColor_fromHexStr(char* val)
{
    EmbColor color;
    char r[3];
    char g[3];
    char b[3];

    r[0] = val[0];
    r[1] = val[1];
    r[2] = 0;

    g[0] = val[2];
    g[1] = val[3];
    g[2] = 0;

    b[0] = val[4];
    b[1] = val[5];
    b[2] = 0;

    color.r = (unsigned char)strtol(r, 0, 16);
    color.g = (unsigned char)strtol(g, 0, 16);
    color.b = (unsigned char)strtol(b, 0, 16);
    return color;
}

EmbColor
embColor_make(unsigned char red, unsigned char green, unsigned char blue)
{
    EmbColor c;
    c.r = red;
    c.b = green;
    c.g = blue;
    return c;
}

/* Reverses the byte order of a bytes number of bytes
 * at memory location a b. Only works for 2 or 4 byte arrays.
 */
void
reverse_byte_order(void *b, int bytes)
{
    char swap;
    if (bytes == 2) {
        swap = *((char*)b+0);
        *((char*)b+0) = *((char*)b+1);
        *((char*)b+1) = swap;
    }
    else {
        swap = *((char*)b+0);
        *((char*)b+0) = *((char*)b+3);
        *((char*)b+3) = swap;
        swap = *((char*)b+1);
        *((char*)b+1) = *((char*)b+2);
        *((char*)b+2) = swap;
    }
}

/* a b a x a y a flags .
 *
 * \todo remove the unused return argument.
 */
int
decode_t01_record(unsigned char b[3], int *x, int *y, int *flags)
{
    decode_tajima_ternary(b, x, y);

    if (b[2] == 0xF3) {
        *flags = END;
    }
    else {
        switch (b[2] & 0xC3) {
        case 0x03:
            *flags = NORMAL;
            break;
        case 0x83:
            *flags = TRIM;
            break;
        case 0xC3:
            *flags = STOP;
            break;
        default:
            *flags = NORMAL;
            break;
        }
    }
    return 1;
}

/* Encode into bytes a b the values of the x-position a x,
 * y-position a y and the a flags.
 */
void
encode_t01_record(unsigned char b[3], int x, int y, int flags)
{
    if (!encode_tajima_ternary(b, x, y)) {
        return;
    }

    b[2] |= (unsigned char)3;
    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (unsigned char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (unsigned char)(b[2] | 0xC3);
    }
}

/* Encode the signed ternary of the tajima format into
 * a b the position values a x and a y.
 *
 * If the values of a x or a y fall outside of the
 * valid range of -121 and +121 then it returns 0 and
 * 1.
 */
int
encode_tajima_ternary(unsigned char b[3], int x, int y)
{
    b[0] = 0;
    b[1] = 0;
    b[2] = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121) {
        printf("ERROR: format-t01.c encode_record(), ");
        printf("x is not in valid range [-121,121] , x = %d\n", x);
        return 0;
    }
    if (y > 121 || y < -121) {
        printf("ERROR: format-t01.c encode_record(), ");
        printf("y is not in valid range [-121,121] , y = %d\n", y);
        return 0;
    }

    if (x >= +41) {
        b[2] |= 0x04;
        x -= 81;
    }
    if (x <= -41) {
        b[2] |= 0x08;
        x += 81;
    }
    if (x >= +14) {
        b[1] |= 0x04;
        x -= 27;
    }
    if (x <= -14) {
        b[1] |= 0x08;
        x += 27;
    }
    if (x >= +5) {
        b[0] |= 0x04;
        x -= 9;
    }
    if (x <= -5) {
        b[0] |= 0x08;
        x += 9;
    }
    if (x >= +2) {
        b[1] |= 0x01;
        x -= 3;
    }
    if (x <= -2) {
        b[1] |= 0x02;
        x += 3;
    }
    if (x >= +1) {
        b[0] |= 0x01;
        x -= 1;
    }
    if (x <= -1) {
        b[0] |= 0x02;
        x += 1;
    }
    if (x != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("x should be zero yet x = %d\n", x);
        return 0;
    }
    if (y >= +41) {
        b[2] |= 0x20;
        y -= 81;
    }
    if (y <= -41) {
        b[2] |= 0x10;
        y += 81;
    }
    if (y >= +14) {
        b[1] |= 0x20;
        y -= 27;
    }
    if (y <= -14) {
        b[1] |= 0x10;
        y += 27;
    }
    if (y >= +5) {
        b[0] |= 0x20;
        y -= 9;
    }
    if (y <= -5) {
        b[0] |= 0x10;
        y += 9;
    }
    if (y >= +2) {
        b[1] |= 0x80;
        y -= 3;
    }
    if (y <= -2) {
        b[1] |= 0x40;
        y += 3;
    }
    if (y >= +1) {
        b[0] |= 0x80;
        y -= 1;
    }
    if (y <= -1) {
        b[0] |= 0x40;
        y += 1;
    }
    if (y != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("y should be zero yet y = %d\n", y);
        return 0;
    }
    return 1;
}

/* Decode the signed ternary of the tajima format from
 * a b to the position values a x and a y.
 *
 * There is no return argument.
 */
void
decode_tajima_ternary(unsigned char b[3], int *x, int *y)
{
    *x = 0;
    *y = 0;
    if (b[0] & 0x01) {
        *x += 1;
    }
    if (b[0] & 0x02) {
        *x -= 1;
    }
    if (b[0] & 0x04) {
        *x += 9;
    }
    if (b[0] & 0x08) {
        *x -= 9;
    }
    if (b[0] & 0x80) {
        *y += 1;
    }
    if (b[0] & 0x40) {
        *y -= 1;
    }
    if (b[0] & 0x20) {
        *y += 9;
    }
    if (b[0] & 0x10) {
        *y -= 9;
    }
    if (b[1] & 0x01) {
        *x += 3;
    }
    if (b[1] & 0x02) {
        *x -= 3;
    }
    if (b[1] & 0x04) {
        *x += 27;
    }
    if (b[1] & 0x08) {
        *x -= 27;
    }
    if (b[1] & 0x80) {
        *y += 3;
    }
    if (b[1] & 0x40) {
        *y -= 3;
    }
    if (b[1] & 0x20) {
        *y += 27;
    }
    if (b[1] & 0x10) {
        *y -= 27;
    }
    if (b[2] & 0x04) {
        *x += 81;
    }
    if (b[2] & 0x08) {
        *x -= 81;
    }
    if (b[2] & 0x20) {
        *y += 81;
    }
    if (b[2] & 0x10) {
        *y -= 81;
    }
}

/* a file a dx a dy a flags
 */
void pfaffEncode(void* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) {
        printf("ERROR: format-pcs.c pcsEncode(), file argument is null\n");
        return;
    }

    write_24bit(file, dx);
    write_24bit(file, dy);

    if (flags & STOP)
    {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM)
    {
        flagsToWrite |= 0x04;
    }
    emb_fwrite(&flagsToWrite, 1, file);
}

/* Decode the bytes a a1, a a2 and a a3 .
 * Returns the EmbReal floating-point value.
 */
EmbReal
pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return 1.0f * res;
}

/*  * a value
 * Returns unsigned char
 */
unsigned char
mitEncodeStitch(EmbReal value)
{
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

/*  * a value
 * Returns int
 */
int
mitDecodeStitch(unsigned char value)
{
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

/*  * a value
 * Returns int
 */
int
decodeNewStitch(unsigned char value)
{
    return (int)value;
}

/* Read and write system for multiple byte types.
 *
 * The caller passes the function to read/write from, the
 * memory location as a void pointer and a mode identifier that describes
 * the type. This way we can abstract out the endianness of the
 * system running the library and don't have to maintain many functions,
 * just two.
 */
void
emb_read(void* f, void *b, int mode)
{
    int endian = mode & 0x01;
    int length = mode - endian;
    int read_bytes = emb_fread(b, length, f);
    if (read_bytes < length) {
        printf("emb_read failed to read enough bytes for type %d.", mode);
        return;
    }
    if (endian != ENDIAN_HOST) {
        reverse_byte_order(b, length);
    }

    if (emb_verbose>1) {
        switch (mode) {
        case EMB_INT16_LITTLE:
            printf("read int16_le: %d\n", *((short*)b));
            break;
        case EMB_INT16_BIG:
            printf("read int16_be: %d\n", *((short*)b));
            break;
        case EMB_INT32_LITTLE:
            printf("read int32_le: %d\n", *((int*)b));
            break;
        case EMB_INT32_BIG:
            printf("read int32_be: %d\n", *((int*)b));
            break;
        default:
            puts("ERROR: the mode supplied to fread_int is invalid.");
            break;
        }
    }
}

/* Wrapper for fwrite that ensures that the endianness is correct. */
void
emb_write(void* f, void *b, int mode)
{
    int endian = mode & 0x01;
    int length = mode - endian;
    if (endian != ENDIAN_HOST) {
        reverse_byte_order(b, length);
    }
    if (emb_verbose>1) {
        switch (mode) {
        case EMB_INT16_LITTLE:
            printf("write int16_le: %d\n", *((short*)b));
            break;
        case EMB_INT16_BIG:
            printf("write int16_be: %d\n", *((short*)b));
            break;
        case EMB_INT32_LITTLE:
            printf("write int32_le: %d\n", *((int*)b));
            break;
        case EMB_INT32_BIG:
            printf("write int32_be: %d\n", *((int*)b));
            break;
        default:
            puts("ERROR: the mode supplied to fwrite_int is invalid.");
            break;
        }
    }

    emb_fwrite(b, length, f);
}

/* end of encoding section. */

/*
 * This is section on compression is a work in progress.
 *
 * Thanks to Jason Weiler for describing the binary formats of the HUS and
 * VIP formats at:
 *
 * http://www.jasonweiler.com/HUSandVIPFileFormatInfo.html
 *
 * Further thanks to github user tatarize for solving the mystery of the
 * compression in:
 *
 * https://github.com/EmbroidePy/pyembroidery
 *
 * with a description of that work here:
 *
 * https://stackoverflow.com/questions/7852670/greenleaf-archive-library
 *
 * This is based on their work.
 */

int huffman_lookup_data[2];

/* Compress data "data" of length "length" to "output" with length "output_length".
 * Returns whether it was successful as an int.
 *
 * This avoids the now unnecessary compression by placing a
 * minimal header of 6 bytes and using only literals in the
 * huffman compressed part (see the sources above).
 */
int hus_compress(char *data, int length, char *output, int *output_length)
{
    unsigned char *a = (unsigned char*)output;
    a[0] = length%256;
    a[1] = (length/256)%256;
    a[2] = 0x02;
    a[3] = 0xA0;
    a[4] = 0x01;
    a[5] = 0xFE;
    memory_copy(output+6, data, length);
    *output_length = length+6;
    return 0;
}

/* These next 2 functions represent the Huffman class in tartarize's code.
 */
void
huffman_build_table(huffman *h)
{
    int bit_length, i, max_length, size;
    max_length = 0;
    size = 1 << h->table_width;
    for (i = 0; i < h->table_width; i++) {
        if (h->lengths[i] > max_length) {
            max_length = h->lengths[i];
        }
    }
    for (bit_length=1; bit_length<=h->table_width; bit_length++) {
        int j;
        size /= 2;
        for (j=0; j < h->nlengths; j++) {
            if (h->lengths[j] == bit_length) {
                int k;
                for (k=0; k<size; k++) {
                    h->table[h->ntable+k] = j;
                    h->ntable++;
                }
            }
        }
    }
}

/* Lookup a byte_lookup in huffman table a h return result
 * as two bytes using the memory huffman_lookup_data.
 */
int *huffman_lookup(huffman h, int byte_lookup)
{
    int *out = huffman_lookup_data;
    if (h.table_width == 0) {
        out[0] = h.default_value;
        out[1] = 0;
        return out;
    }
    out[0] = h.table[byte_lookup >> (16-h.table_width)];
    out[1] = h.lengths[out[0]];
    return out;
}

/* These functions represent the EmbCompress class. */
void compress_init()
{

}

/* Return bits from compress struct pointed to by "c" of length "length". */
int
compress_get_bits(compress *c, int length)
{
    int i, end_pos_in_bits, start_pos_in_bytes,
        end_pos_in_bytes, value, mask_sample_bits,
        unused_bits, original;

    end_pos_in_bits = c->bit_position + length - 1;
    start_pos_in_bytes = c->bit_position / 8;
    end_pos_in_bytes = end_pos_in_bits / 8;
    value = 0;

    for (i=start_pos_in_bytes; i < end_pos_in_bytes+1; i++) {
        value <<= 8;
        if (i > c->input_length) {
            break;
        }
        value |= (c->input_data[i]) & 0xFF;
    }

    unused_bits = (7 - end_pos_in_bits) % 8;
    mask_sample_bits = (1<<length) - 1;
    original = (value >> unused_bits) & mask_sample_bits;
    return original;
}

/* a c a bit_count . Returns.
 */
int
compress_pop(compress *c, int bit_count)
{
    int value = compress_get_bits(c, bit_count);
    c->bit_position += bit_count;
    return value;
}

/* a c a bit_count. Returns.
 */
int
compress_peek(compress *c, int bit_count)
{
    return compress_get_bits(c, bit_count);
}

/* a c. Returns.
 */
int
compress_read_variable_length(compress *c)
{
    int q, m, s;
    m = compress_pop(c, 3);
    if (m!=7) {
        return m;
    }
    for (q=0; q<13; q++) {
        s = compress_pop(c, 1);
        if (s) {
            m++;
        }
        else {
            break;
        }
    }
    return m;
}

/* a c  . Returns.
 */
void
compress_load_character_length_huffman(compress *c)
{
    int count;
    count = compress_pop(c, 5);
    if (count == 0) {
        c->character_length_huffman.default_value = compress_pop(c, 5);
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            c->character_length_huffman.lengths[i] = 0;
        }
        for (i = 0; i < count; i++) {
            if (i==3) {
                i += compress_pop(c, 2);
            }
            c->character_length_huffman.lengths[i] = compress_read_variable_length(c);
        }
    }
    huffman_build_table(&(c->character_length_huffman));
}

/* Load character table to compress struct a c. Returns nothing.
 */
void
compress_load_character_huffman(compress *c)
{
    int count;
    count = compress_pop(c, 9);
    if (count == 0) {
        c->character_huffman.default_value = compress_pop(c, 9);
    }
    else {
        int i = 0;
        while (i < count) {
            int *h = huffman_lookup(c->character_length_huffman,
                compress_peek(c, 16));
            c->bit_position += h[1];
            if (h[0]==0) {
                i += h[0];
            }
            else if (h[0]==1) {
                i += 3 + compress_pop(c, 4);
            }
            else if (h[0]==2) {
                i += 20 + compress_pop(c, 9);
            }
            else {
                c->character_huffman.lengths[i] = h[0] - 2;
                i++;
            }
        }
    }
    huffman_build_table(&(c->character_huffman));
}

/* a c . Returns nothing.
 */
void
compress_load_distance_huffman(compress *c)
{
    int count;
    count = compress_pop(c, 5);
    if (count == 0) {
        c->distance_huffman.default_value = compress_pop(c, 5);
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            c->distance_huffman.lengths[i] = compress_read_variable_length(c);
        }
    }
    huffman_build_table(&(c->distance_huffman));
}

/* a c . Returns nothing.
 */
void
compress_load_block(compress *c)
{
    c->block_elements = compress_pop(c, 16);
    compress_load_character_length_huffman(c);
    compress_load_character_huffman(c);
    compress_load_distance_huffman(c);
}

/* a c . Returns the token as an int.
 */
int
compress_get_token(compress *c)
{
    int *h;
    if (c->block_elements <= 0) {
        compress_load_block(c);
    }
    c->block_elements--;
    h = huffman_lookup(c->character_huffman, compress_peek(c, 16));
    c->bit_position += h[1];
    return h[0];
}

/* a c . Returns the position as an int.
 */
int
compress_get_position(compress *c)
{
    int *h, v;
    h = huffman_lookup(c->distance_huffman, compress_peek(c, 16));
    c->bit_position += h[1];
    if (h[0] == 0) {
        return 0;
    }
    v = h[0] - 1;
    v = (1<<v) + compress_pop(c, v);
    return v;
}

/* a data a length a output a output_length .
 * Returns whether the decompression was successful.
 */
int
hus_decompress(char *data, int length, char *output, int *output_length)
{
    int character, i, j;
    compress *c = (compress*)malloc(sizeof(compress));
    c->bit_position = 0;
    c->input_data = data;
    c->input_length = length;
    c->bits_total = length*8;
    i = 0;
    while (c->bits_total > c->bit_position && i < *output_length) {
        /* process token */
        character = 0; /* fix this */
        if (character < 0x100) {
            output[i] = (char)character;
            i++;
        }
        else if (character == 510) {
            break;
        }
        else {
            length = character - 253;
            /* not sure about i here */
            c->bit_position = i - compress_get_position(c) - 1;
            for (j=c->bit_position; j < c->bit_position+length; j++) {
                output[i] = output[j];
                i++;
            }
        }
    }
    safe_free(c);
    return 0;
}

/* End of compression section. */

/* The array management for libembroidery's arrays.
 */

/* Allocates memory for an EmbArray of the type determined by
 * the argument a type.
 */
EmbArray*
emb_array_create(int type)
{
    EmbArray *a;
    a = (EmbArray*)malloc(sizeof(EmbArray));
    a->type = type;
    a->length = CHUNK_SIZE;
    a->count = 0;
    switch (type) {
    case EMB_STITCH:
        a->stitch = (EmbStitch*)malloc(CHUNK_SIZE*sizeof(EmbStitch));
        break;
    case EMB_THREAD:
        a->thread = (EmbThread*)malloc(CHUNK_SIZE*sizeof(EmbThread));
        break;
    default:
        a->geometry = (EmbGeometry*)malloc(CHUNK_SIZE*sizeof(EmbGeometry));
        break;
    }
    return a;
}

/* Resizes the array a a to be CHUNK_SIZE entries longer
 * if and only if the amount of room left is less than
 * 3 entries.
 */
int
emb_array_resize(EmbArray *a)
{
    if (a->count < a->length - 3) {
        return 1;
    }
    a->length += CHUNK_SIZE;
    switch (a->type) {
    case EMB_STITCH:
        a->stitch = (EmbStitch*)realloc(a->stitch, a->length*sizeof(EmbStitch));
        if (!a->stitch) {
            /* TODO: Error reporting */
            return 0;
        }
        break;
    case EMB_THREAD:
        a->thread = (EmbThread*)realloc(a->thread, a->length*sizeof(EmbThread));
        if (!a->thread) {
            /* TODO: Error reporting */
            return 0;
        }
        break;
    default:
        a->geometry = (EmbGeometry *)realloc(a->geometry, a->length*sizeof(EmbGeometry));
        if (!a->geometry) {
            /* TODO: Error reporting */
            return 0;
        }
        break;
    }

    return 1;
}

/* Copies all entries in the EmbArray struct from a src to a dst.
 */
void
emb_array_copy(EmbArray *dst, EmbArray *src)
{
    dst = emb_array_create(src->type);
    dst->length = src->length;
    dst->count = src->count;
    emb_array_resize(dst);
    /* BUG: Potential failure to copy path memory, only copy pointers? */

    switch (dst->type) {
    case EMB_STITCH:
        memory_copy(dst->stitch, src->stitch, sizeof(EmbStitch)*src->count);
        break;
    case EMB_THREAD:
        memory_copy(dst->thread, src->thread, sizeof(EmbThread)*src->count);
        break;
    default:
        memory_copy(dst->geometry, src->geometry, sizeof(EmbGeometry)*src->count);
        break;
    }
}

/* Add an arc a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addArc(EmbArray *a, EmbArc b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.arc = b;
    a->geometry[a->count - 1].type = EMB_ARC;
    return 1;
}

/* Add a circle a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addCircle(EmbArray *a, EmbCircle b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.circle = b;
    a->geometry[a->count - 1].type = EMB_CIRCLE;
    return 1;
}

/* Add an ellipse a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addEllipse(EmbArray *a, EmbEllipse b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.ellipse = b;
    a->geometry[a->count - 1].type = EMB_ELLIPSE;
    return 1;
}

/* Add a flag a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addFlag(EmbArray *a, EmbFlag b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].flag = b;
    a->geometry[a->count - 1].type = EMB_FLAG;
    return 1;
}

/* Add a line a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addLine(EmbArray *a, EmbLine b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.line = b;
    a->geometry[a->count - 1].type = EMB_LINE;
    return 1;
}

/* Add a path a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPath(EmbArray *a, EmbPath b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.path = b;
    a->geometry[a->count - 1].type = EMB_PATH;
    return 1;
}

/* Add a point a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPoint(EmbArray *a, EmbPoint b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.point = b;
    a->geometry[a->count - 1].type = EMB_POINT;
    return 1;
}

/* Add a polyline a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPolyline(EmbArray *a, EmbPolyline b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.polyline = b;
    a->geometry[a->count - 1].type = EMB_POLYLINE;
    return 1;
}

/* Add a polygon a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPolygon(EmbArray *a, EmbPolygon b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.polygon = b;
    a->geometry[a->count - 1].type = EMB_POLYGON;
    return 1;
}

/* Add a rectangle a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addRect(EmbArray *a, EmbRect b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.rect = b;
    a->geometry[a->count - 1].type = EMB_RECT;
    return 1;
}

/* Add a stitch a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addStitch(EmbArray *a, EmbStitch b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->stitch[a->count - 1] = b;
    return 1;
}

/* Add a vector a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addVector(EmbArray *a, EmbVector b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.vector = b;
    a->geometry[a->count - 1].type = EMB_VECTOR;
    return 1;
}

/* Free the memory of EmbArray a a, recursively if necessary.
 */
void
emb_array_free(EmbArray* a)
{
    int i;
    if (!a) {
        return;
    }
    switch (a->type) {
    case EMB_STITCH:
        safe_free(a->stitch);
        break;
    case EMB_THREAD:
        safe_free(a->thread);
        break;
    default:
        for (i = 0; i < a->count; i++) {
            EmbGeometry g = a->geometry[i];
            switch (a->geometry[i].type) {
            case EMB_PATH: {
                emb_array_free(g.object.path.pointList);
                break;
            }
            case EMB_POLYGON: {
                emb_array_free(g.object.polygon.pointList);
                break;
            }
            case EMB_POLYLINE: {
                emb_array_free(g.object.polyline.pointList);
                break;
            }
            default:
                break;
            }
        }
        safe_free(a->geometry);
        break;
    }
    safe_free(a);
}

/* Print the vector "v2 with the name "label". */
void emb_vector_print(EmbVector v, char *label)
{
    printf("%sX = %f\n", label, v.x);
    printf("%sY = %f\n", label, v.y);
}

/* Print the arc "arc". */
void emb_arc_print(EmbArc arc)
{
    emb_vector_print(arc.start, "start");
    emb_vector_print(arc.mid, "middle");
    emb_vector_print(arc.end, "end");
}

/* Checks that there are enough bytes to interpret the header,
 * stops possible segfaults when reading in the header bytes.
 *
 * Returns 0 if there aren't enough, or the length of the file
 * if there are.
 */
int
check_header_present(void* file, int minimum_header_length)
{
    int length;
    emb_fseek(file, 0, SEEK_END);
    length = ftell(file);
    emb_fseek(file, 0, SEEK_SET);
    if (length < minimum_header_length) {
        return 0;
    }
    return length;
}

/* sectorSize based on the bcfFile version. */
unsigned int
sectorSize(bcf_file* bcfFile)
{
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    }
    return 4096;
}

/* . */
int
haveExtraDIFATSectors(bcf_file* file)
{
    return (int)(entriesInDifatSector(file->difat) > 0);
}

/* . */
int
seekToSector(bcf_file* bcfFile, void* file, const unsigned int sector)
{
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return emb_fseek(file, offset, SEEK_SET);
}

/* . */
void
parseDIFATSectors(void* file, bcf_file* bcfFile)
{
    unsigned int difatEntriesToRead = bcfFile->header.numberOfFATSectors - difatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (difatEntriesToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &difatEntriesToRead);
    }
}

/* . */
int
bcfFile_read(void* file, bcf_file* bcfFile)
{
    unsigned int i, numberOfDirectoryEntriesPerSector;
    unsigned int directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (memory_cmp(bcfFile->header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1", 8) != 0) {
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

/* Get the File object. */
void*
GetFile(bcf_file* bcfFile, void* file, char* fileToFind)
{
    int filesize, sectorSize, currentSector;
    int sizeToWrite, currentSize, totalSectors, i, j;
    void* fileOut = tmpfile();
    bcf_directory_entry* pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (string_equals(fileToFind, pointer->directoryEntryName)) {
            break;
        }
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
            if (emb_fread(&input, 1, file) != 1) {
                /* TODO: Needs an error code. */
                puts("ERROR: GetFile failed to read byte.");
                return fileOut;
            }
            if (emb_fwrite(&input, 1, fileOut) != 1) {
                /* TODO: Needs an error code. */
                puts("ERROR: GetFile failed to read byte.");
                return fileOut;
            }
        }
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    return fileOut;
}

/* . */
void
bcf_file_free(bcf_file* bcfFile)
{
    safe_free(bcfFile->difat);
    safe_free(bcfFile->fat);
    bcf_directory_free(&bcfFile->directory);
    safe_free(bcfFile);
}

/* . */
bcf_file_difat*
bcf_difat_create(void* file, unsigned int fatSectors, const unsigned int sectorSize)
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
        emb_read(file, &sectorRef, EMB_INT32_LITTLE);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < difatEntriesInHeader; ++i) {
        emb_read(file, &sectorRef, EMB_INT32_LITTLE);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n", sectorRef, i);
        }
    }
    return difat;
}

/* . */
unsigned int
entriesInDifatSector(bcf_file_difat* fat)
{
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

/* . */
unsigned int
readFullSector(
    void* file,
    bcf_file_difat* bcfFile,
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
        emb_read(file, &sectorRef, EMB_INT32_LITTLE);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < entriesInDifatSector(bcfFile); ++i) {
        emb_read(file, &sectorRef, EMB_INT32_LITTLE);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c readFullSector(), ");
            printf("Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    emb_read(file, &nextDifatSectorInChain, EMB_INT32_LITTLE);
    return nextDifatSectorInChain;
}

/* . */
void
parseDirectoryEntryName(void* file, bcf_directory_entry* dir)
{
    int i;
    for (i = 0; i < 32; ++i) {
        unsigned short unicodechar;
        emb_read(file, &unicodechar, EMB_INT16_LITTLE);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

/* . */
bcf_directory*
CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries)
{
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
        return NULL;
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

/* . */
EmbTime
parseTime(void* file)
{
    EmbTime returnVal;
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    emb_read(file, &ft_low, EMB_INT32_LITTLE);
    emb_read(file, &ft_high, EMB_INT32_LITTLE);
    /* TODO: translate to actual date time */
    returnVal.day = 1;
    returnVal.hour = 2;
    returnVal.minute = 3;
    returnVal.month = 4;
    returnVal.second = 5;
    returnVal.year = 6;
    return returnVal;
}

/* . */
bcf_directory_entry*
CompoundFileDirectoryEntry(void* file)
{
    const int guidSize = 16;
    bcf_directory_entry* dir = malloc(sizeof(bcf_directory_entry));
    if (dir == NULL) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
        return NULL;
    }
    memory_set(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = fread_uint16(file);
    dir->objectType = (unsigned char)fgetc(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry()");
        printf(", unexpected object type: %d\n", dir->objectType);
        return NULL;
    }
    dir->colorFlag = (unsigned char)fgetc(file);
    emb_read(file, &(dir->leftSiblingId), EMB_INT32_LITTLE);
    emb_read(file, &(dir->rightSiblingId), EMB_INT32_LITTLE);
    emb_read(file, &(dir->childId), EMB_INT32_LITTLE);
    if (fread(dir->CLSID, 1, guidSize, file) < guidSize) {
        printf("ERROR: Failed to read guidSize bytes for CLSID");
        return dir;
    }
    emb_read(file, &(dir->stateBits), EMB_INT32_LITTLE);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    emb_read(file, &(dir->startingSectorLocation), EMB_INT32_LITTLE);
    /* StreamSize should really be __int64 or long long,
     * but for our uses we should never run into an issue */
    emb_read(file, &(dir->streamSize), EMB_INT32_LITTLE);
    /* top portion of int64 */
    emb_read(file, &(dir->streamSizeHigh), EMB_INT32_LITTLE);
    return dir;
}

/* . */
void
readNextSector(void* file, bcf_directory* dir)
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

/* . */
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
        safe_free(entryToFree);
    }
    safe_free(*dir);
}

/* . */
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

/* . */
void
loadFatFromSector(bcf_file_fat* fat, void* file)
{
    unsigned int i;
    unsigned int current_fat_entries = fat->fatEntryCount;
    unsigned int newSize = current_fat_entries + fat->numberOfEntriesInFatSector;
    for (i = current_fat_entries; i < newSize; ++i) {
        int fatEntry;
        emb_read(file, &fatEntry, EMB_INT32_LITTLE);
        fat->fatEntries[i] = fatEntry;
    }
    fat->fatEntryCount = newSize;
}

/* . */
bcf_file_header
bcfFileHeader_read(void* file)
{
    bcf_file_header header;
    if (fread(header.signature, 1, 8, file) < 8) {
        puts("ERROR: failed to read signature bytes from bcf file.");
        return header;
    }
    if (fread(header.CLSID, 1, 16, file) < 16) {
        puts("ERROR: failed to read CLSID bytes from bcf file.");
        return header;
    }
    header.minorVersion = fread_uint16(file);
    header.majorVersion = fread_uint16(file);
    header.byteOrder = fread_uint16(file);
    header.sectorShift = fread_uint16(file);
    header.miniSectorShift = fread_uint16(file);
    header.reserved1 = fread_uint16(file);
    emb_read(file, &(header.reserved2), EMB_INT32_LITTLE);
    emb_read(file, &(header.numberOfDirectorySectors), EMB_INT32_LITTLE);
    emb_read(file, &(header.numberOfFATSectors), EMB_INT32_LITTLE);
    emb_read(file, &(header.firstDirectorySectorLocation), EMB_INT32_LITTLE);
    emb_read(file, &(header.transactionSignatureNumber), EMB_INT32_LITTLE);
    emb_read(file, &(header.miniStreamCutoffSize), EMB_INT32_LITTLE);
    emb_read(file, &(header.firstMiniFATSectorLocation), EMB_INT32_LITTLE);
    emb_read(file, &(header.numberOfMiniFatSectors), EMB_INT32_LITTLE);
    emb_read(file, &(header.firstDifatSectorLocation), EMB_INT32_LITTLE);
    emb_read(file, &(header.numberOfDifatSectors), EMB_INT32_LITTLE);
    return header;
}

/* . */
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
    outline.side1 = emb_array_create(EMB_VECTOR);
    if (!outline.side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side1\n");
        return;
    }
    outline.side2 = emb_array_create(EMB_VECTOR);
    if (!outline.side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side2\n");
        return;
    }

    for (i = 1; i < lines->count; i++) {
        line.start = lines->geometry[i - 1].object.vector;
        line.end = lines->geometry[i].object.vector;

        v1 = emb_line_normalVector(line, 1);

        temp = emb_vector_scale(v1, halfThickness);
        temp = emb_vector_add(temp, lines->geometry[i-1].object.vector);
        emb_array_addVector(outline.side1, temp);
        temp = emb_vector_add(temp, lines->geometry[i].object.vector);
        emb_array_addVector(outline.side1, temp);

        temp = emb_vector_scale(v1, -halfThickness);
        temp = emb_vector_add(temp, lines->geometry[i - 1].object.vector);
        emb_array_addVector(outline.side2, temp);
        temp = emb_vector_add(temp, lines->geometry[i].object.vector);
        emb_array_addVector(outline.side2, temp);
    }

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), result argument is null\n");
        return;
    }
    result->side1 = emb_array_create(EMB_VECTOR);
    if (!result->side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side1\n");
        return;
    }
    result->side2 = emb_array_create(EMB_VECTOR);
    if (!result->side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side2\n");
        return;
    }

    emb_array_addVector(result->side1, outline.side1->geometry[0].object.vector);
    emb_array_addVector(result->side2, outline.side2->geometry[0].object.vector);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.start = outline.side1->geometry[i - 3].object.vector;
        line1.end = outline.side1->geometry[i - 2].object.vector;
        line2.start = outline.side1->geometry[i - 1].object.vector;
        line2.end = outline.side1->geometry[i].object.vector;
        out = emb_line_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        emb_array_addVector(result->side1, out);

        line1.start = outline.side2->geometry[i - 3].object.vector;
        line1.end = outline.side2->geometry[i - 2].object.vector;
        line2.start = outline.side2->geometry[i - 1].object.vector;
        line2.end = outline.side2->geometry[i].object.vector;
        out = emb_line_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        emb_array_addVector(result->side2, out);
    }

    emb_array_addVector(result->side1, outline.side1->geometry[2 * lines->count - 3].object.vector);
    emb_array_addVector(result->side2, outline.side2->geometry[2 * lines->count - 3].object.vector);
    result->length = lines->count;
}

/* . */
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
            topDiff = emb_vector_subtract(g10->object.vector, g11->object.vector);
            bottomDiff = emb_vector_subtract(g21->object.vector, g20->object.vector);

            midLeft = emb_vector_average(g10->object.vector, g20->object.vector);
            midRight = emb_vector_average(g11->object.vector, g21->object.vector);

            midDiff = emb_vector_subtract(midLeft, midRight);
            midLength = emb_vector_length(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            topStep = emb_vector_scale(topDiff, 1.0/numberOfSteps);
            bottomStep = emb_vector_scale(bottomDiff, 1.0/numberOfSteps);
            currTop = g10->object.vector;
            currBottom = g20->object.vector;

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = emb_array_create(EMB_VECTOR);
                }
                emb_array_addVector(stitches, currTop);
                emb_array_addVector(stitches, currBottom);
                currTop = emb_vector_add(currTop, topStep);
                currBottom = emb_vector_add(currBottom, bottomStep);
            }
        }
        emb_array_addVector(stitches, currTop);
        emb_array_addVector(stitches, currBottom);
    }
    return stitches;
}

/* . */
void
write_24bit(void* file, int x)
{
    unsigned char a[4];
    a[0] = (unsigned char)0;
    a[1] = (unsigned char)(x & 0xFF);
    a[2] = (unsigned char)((x >> 8) & 0xFF);
    a[3] = (unsigned char)((x >> 16) & 0xFF);
    emb_fwrite(a, 4, file);
}

/* . */
int
embColor_distance(EmbColor a, EmbColor b)
{
    int t;
    t = (a.r-b.r)*(a.r-b.r);
    t += (a.g-b.g)*(a.g-b.g);
    t += (a.b-b.b)*(a.b-b.b);
    return t;
}

/* . */
void
embColor_read(void *f, EmbColor *c, int toRead)
{
    unsigned char b[4];
    if (fread(b, 1, toRead, f) < toRead) {
        puts("ERROR: Failed to read embColor bytes.");
        return;
    }
    c->r = b[0];
    c->g = b[1];
    c->b = b[2];
}

/* . */
void
embColor_write(void *f, EmbColor c, int toWrite)
{
    unsigned char b[4];
    b[0] = c.r;
    b[1] = c.g;
    b[2] = c.b;
    b[3] = 0;
    emb_fwrite(b, toWrite, f);
}

/* Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * a color  The EmbColor color to match.
 * a colors The EmbThreadList pointer to start the search at.
 * a mode   Is the argument an array of threads (0) or colors (1)?
 * Returns closestIndex The entry in the ThreadList that matches.
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

/* . */
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

/*
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * Returns c The resulting color.
 */
EmbThread
embThread_getRandom(void)
{
    EmbThread c;
    c.color.r = rand()%256;
    c.color.g = rand()%256;
    c.color.b = rand()%256;
    string_copy(c.description, "random");
    string_copy(c.catalogNumber, "");
    return c;
}

/* . */
void
binaryReadString(void* file, char* buffer, int maxLength)
{
    int i = 0;
    while(i < maxLength) {
        buffer[i] = (char)fgetc(file);
        if (buffer[i] == '\0') break;
        i++;
    }
}

/* . */
void
binaryReadUnicodeString(void* file, char *buffer, const int stringLength)
{
    int i = 0;
    for (i = 0; i < stringLength * 2; i++) {
        char input = (char)fgetc(file);
        if (input != 0) {
            buffer[i] = input;
        }
    }
}

/*
 * Tests for the presence of a string a s in the supplied
 * a array.
 *
 * The end of the array is marked by an empty string.
 *
 * Returns 0 if not present 1 if present.
 */
int
stringInArray(const char *s, const char **array)
{
    int i;
    for (i = 0; string_len(array[i]); i++) {
        if (string_equals(s, array[i])) {
            return 1;
        }
    }
    return 0;
}

/* . */
int
emb_readline(void* file, char *line, int maxLength)
{
    int i;
    char c;
    for (i = 0; i < maxLength-1; i++) {
        if (!fread(&c, 1, 1, file)) {
            break;
        }
        if (c == '\r') {
            if (fread(&c, 1, 1, file) != 1) {
                /* Incomplete Windows-style line ending. */
                break;
            }
            if (c != '\n') {
                emb_fseek(file, -1L, SEEK_CUR);
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

/* TODO: description */

/* Get the trim bounds object. */
void
get_trim_bounds(char const *s, char const **firstWord, char const **trailingSpace)
{
    char const* lastWord = 0;
    *firstWord = lastWord = s + string_whitespace(s);
    do {
        *trailingSpace = lastWord + string_whitespace(lastWord);
        lastWord = *trailingSpace + string_whitespace(*trailingSpace);
    } while (*lastWord != '\0');
}

/* . */
char*
copy_trim(char const *s)
{
    char const *firstWord = 0, *trailingSpace = 0;
    char* result = 0;
    size_t newLength;

    get_trim_bounds(s, &firstWord, &trailingSpace);
    newLength = trailingSpace - firstWord;

    result = (char*)malloc(newLength + 1);
    memory_copy(result, firstWord, newLength);
    result[newLength] = '\0';
    return result;
}

/* Optimizes the number (a num) for output to a text file and returns
 * it as a string (a str).
 */
char*
emb_optOut(EmbReal num, char* str)
{
    char *str_end;
    /* Convert the number to a string */
    sprintf(str, "%.10f", num);
    /* Remove trailing zeroes */
    str_end = str + string_len(str);
    while (*--str_end == '0');
    str_end[1] = 0;
    /* Remove the decimal point if it happens to be an integer */
    if (*str_end == '.') {
        *str_end = 0;
    }
    return str;
}

/* . */
void
embTime_initNow(EmbTime* t)
{
    /*
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
    */
}

/* . */
EmbTime
embTime_time(EmbTime* t)
{
    int divideByZero = 0;
    divideByZero = divideByZero/divideByZero;
    /* TODO: wrap time() from time.h and verify it works consistently */

    return *t;
}

/* Currently just crash testing.
 */
int
test_convert(int test_case, int from, int to)
{
	EmbString fname_from;
	EmbString fname_to;
	sprintf(fname_from, "test%02d.%s", test_case, formatTable[from].extension);
	sprintf(fname_from, "test%02d_out.%s", test_case, formatTable[to].extension);
	printf("Converting test case %d: %s to %s.", test_case, fname_from, fname_to);
	int result = create_test_file(test_case, fname_from);
	if (result) {
		return result;
	}
	convert(fname_from, fname_to);
	return 0;
}


/* . */
int
testMain(int test_index)
{
    switch (test_index) {
    case 0: {
        EmbReal error;
        EmbReal epsilon = 0.001f;
        EmbVector p0, p1;
        /* Problem */
        EmbCircle c1 = emb_circle_init(0.0f, 0.0f, 3.0f);
        /* Solution */
        EmbVector t0 = {2.2500f, 1.9843f};
        EmbVector t1 = {2.2500f, -1.9843f};
        EmbVector p = {4.0f, 0.0f};
        /* Test */
        testTangentPoints(c1, p, &p0, &p1);
        error = emb_vector_distance(p0, t0) + emb_vector_distance(p1, t1);
        if (error > epsilon) {
            printf("Error larger than tolerance, circle test 1: %f.\n\n", error);
            return 1;
        }

        return 0;
    }
    case 1: {
        EmbReal error;
        EmbReal epsilon = 0.001f;
        EmbVector p0, p1;
        EmbCircle c2 = {{20.1762f, 10.7170f}, 6.8221f};
        /* Solution */
        EmbVector s0 = {19.0911f, 17.4522f};
        EmbVector s1 = {26.4428f, 13.4133f};
        EmbVector p = {24.3411f, 18.2980f};
        /* Test */
        testTangentPoints(c2, p, &p0, &p1);
        error = emb_vector_distance(p0, s0) + emb_vector_distance(p1, s1);
        if (error > epsilon) {
            printf("Error larger than tolerance, circle test 2: %f.\n\n", error);
            return 2;
        }

        return 0;
    }
    case 2: {
        unsigned int tColor = 0xFFD25F00;
        EmbColor c;
        c.r = 0xD2;
        c.g = 0x5F;
        c.b = 0x00;
        int tBrand = 0; /*EMB_BRAND_SULKY_RAYON; */
        int tNum = threadColorNum(tColor, tBrand);
        char tName[50];
        string_copy(tName, threadColorName(tColor, tBrand));

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
    case 3: {
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

        if (!string_equals(formatTable[format].extension, ".zsk")) {
   			return 20;
		}
        if (!string_equals(formatTable[format].description, "ZSK USA Embroidery Format")) {
            return 21;
        }
        if (formatTable[format].reader_state != 'U') {
			return 22;
		}
        if (formatTable[format].writer_state != ' ') {
			return 23;
		}
        if (formatTable[format].type != 1) {
			return 24;
		}
        return 0;
    }
    case 4: {
        EmbArc arc;
        EmbVector center, chordMid;
        EmbReal bulge, radius, diameter, chord, sagitta, apothem, incAngle;
        char clockwise;

        bulge = -0.414213562373095f;
        arc.start.x = 1.0f;
        arc.start.y = 0.0f;
        arc.mid.x = 0.0f; /* FIXME */
        arc.mid.y = 0.0f;
        arc.end.x = 2.0f;
        arc.end.y = 1.0f;
        center = emb_arc_center(arc);
        chord = emb_arc_chord(arc);
        radius = emb_arc_radius(arc);
        diameter = emb_arc_diameter(arc);
        chordMid = emb_arc_chordMid(arc);
        sagitta = emb_arc_sagitta(arc);
        apothem = emb_arc_apothem(arc);
        incAngle = emb_arc_incAngle(arc);
        clockwise = emb_arc_clockwise(arc);
        /* bulge = emb_arc_bulge(arc); */
        if (emb_verbose > 0) {
            fprintf(stdout, "Clockwise Test:\n");
            printArcResults(bulge, arc, center,
                        radius, diameter,
                        chord, chordMid,
                        sagitta,   apothem,
                        incAngle,  clockwise);
        }

        bulge  = 2.414213562373095f;
        arc.start.x = 4.0f;
        arc.start.y = 0.0f;
        arc.mid.x = 0.0f; /* FIXME */
        arc.mid.y = 0.0f;
        arc.end.x = 5.0f;
        arc.end.y = 1.0f;
        center = emb_arc_center(arc);
        chord = emb_arc_chord(arc);
        radius = emb_arc_radius(arc);
        diameter = emb_arc_diameter(arc);
        chordMid = emb_arc_chordMid(arc);
        sagitta = emb_arc_sagitta(arc);
        apothem = emb_arc_apothem(arc);
        incAngle = emb_arc_incAngle(arc);
        clockwise = emb_arc_clockwise(arc);
        /* bulge = emb_arc_bulge(arc); */
        if (emb_verbose > 0) {
            fprintf(stdout, "Counter-Clockwise Test:\n");
            printArcResults(bulge, arc, center,
                        radius, diameter, chord,
                        chordMid, sagitta,   apothem,
                        incAngle, clockwise);
        }

        return 0;
    }
    case 5: {
        return create_test_file(0, "test01.csv");
    }
    case 6: {
        return create_test_file(1, "test02.csv");
    }
    case 7: {
        return create_test_file(2, "test03.csv");
    }
    case 8: {
        return test_convert(0, EMB_FORMAT_CSV, EMB_FORMAT_SVG);
    }
    case 9: {
        return test_convert(0, EMB_FORMAT_CSV, EMB_FORMAT_DST);
    }
    case 10: {
        return test_convert(1, EMB_FORMAT_CSV, EMB_FORMAT_SVG);
    }
    case 11: {
        return test_convert(1, EMB_FORMAT_CSV, EMB_FORMAT_DST);
    }
    case 12: {
        return test_convert(2, EMB_FORMAT_CSV, EMB_FORMAT_SVG);
    }
    case 13: {
        return test_convert(2, EMB_FORMAT_CSV, EMB_FORMAT_DST);
    }
    case 14: {
        EmbPattern *pattern = emb_pattern_create();
        int hilbertCurveResult = hilbert_curve(pattern, 3);
        int renderResult = emb_pattern_render(pattern, "hilbert_level_3.png");
        int simulateResult = emb_pattern_simulate(pattern, "hilbert_level_3.avi");
        emb_pattern_free(pattern);
        return hilbertCurveResult;
    }
    default: break;
    }
    return 10;
}

/* . */
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

/* . */
void
printArcResults(
    EmbReal bulge,
    EmbArc arc,
    EmbVector center,
    EmbReal radius,
    EmbReal diameter,
    EmbReal chord,
    EmbVector chordMid,
    EmbReal sagitta,
    EmbReal apothem,
    EmbReal incAngle,
    char clockwise)
{
    emb_arc_print(arc);
    emb_vector_print(center, "center");
    emb_vector_print(chordMid, "chordMid");
    fprintf(stdout, "bulge     = %f\n"
                    "radius    = %f\n"
                    "diameter  = %f\n"
                    "chord     = %f\n"
                    "sagitta   = %f\n"
                    "apothem   = %f\n"
                    "incAngle  = %f\n"
                    "clockwise = %d\n"
                    "\n",
                    bulge,
                    radius,
                    diameter,
                    chord,
                    sagitta,
                    apothem,
                    incAngle,
                    clockwise);
}

/* Create a test file 1 object. */
int
create_test_file(int test_file, const char* outf)
{
    int i;
    EmbPattern* p;
    EmbStitch st;

    p = emb_pattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    switch (test_file) {
	case 0: {
		/* 10mm circle */
		for (i = 0; i < 20; i++) {
			emb_pattern_addStitchRel(p, 0.0, 1.0, JUMP, 0);
		}
		for (i = 0; i < 200; i++) {
			st.x = 10 + 10 * sin(i * (0.03141592));
			st.y = 10 + 10 * cos(i * (0.03141592));
			st.flags = NORMAL;
			st.color = 0;
			emb_pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
		}

		emb_pattern_addThread(p, black_thread);
		emb_pattern_end(p);

		if (!emb_pattern_writeAuto(p, outf)) {
            emb_pattern_free(p);
			return 16;
		}
		break;
	}
	case 1: {
        /* sin wave */
        for (i = 0; i < 100; i++) {
            st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
            st.y = 10 + i * 0.1;
            st.flags = NORMAL;
            st.color = 0;
            emb_pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
        }

        emb_pattern_addThread(p, black_thread);
        emb_pattern_end(p);

        if (!emb_pattern_writeAuto(p, outf)) {
            emb_pattern_free(p);
            return 16;
        }
		break;
	}
	case 2: {
        EmbCircle circle = emb_circle_init(10.0f, 1.0f, 5.0f);
        emb_pattern_addCircleAbs(p, circle);

        emb_pattern_addThread(p, black_thread);
        emb_pattern_convertGeometry(p);
        emb_pattern_end(p);

        if (!emb_pattern_writeAuto(p, outf)) {
            emb_pattern_free(p);
            return 16;
        }
		break;
	}
    default: {
		puts("This case is not covered.");
		break;
	}
    }

    emb_pattern_free(p);
    return 0;
}

/* TODO: Add capability for converting multiple files of various types to a single format.
Currently, we only convert a single file to multiple formats. */

/* construct from tables above somehow, like how getopt_long works,
 * but we're avoiding that for compatibility
 * (C90, standard libraries only) */
void
usage(void)
{
	int i;
    puts(welcome_message);
    for (i=0; !string_equals(help_msg[i], "EOF"); i++) {
        puts(help_msg[i]);
    }
}

/* . */
void
formats(void)
{
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
		if (formatTable[i].reader_state != ' ') {
			numReaders++;
		}
		if (formatTable[i].writer_state != ' ') {
			numWriters++;
		}
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n",
     		formatTable[i].extension,
			formatTable[i].reader_state,
			formatTable[i].writer_state,
			formatTable[i].description);
    }

    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");
    printf("| Total: |  %3d  |  %3d  |                                                    |\n", numReaders, numWriters);
    printf("|________|_______|_______|____________________________________________________|\n");
    puts("");
}

/* . */
void
to_flag(char **argv, int argc, int i)
{
    if (i + 2 < argc) {
        int j;
        EmbString output_fname;
        int format;
        sprintf(output_fname, "example.%s", argv[i+1]);
        format = emb_identify_format(output_fname);
        if (format < 0) {
            puts("Error: format unrecognised.");
        }
        for (j=i+2; j<argc; j++) {
            int length = string_len(argv[j]);
            output_fname[0] = 0;
            string_copy(output_fname, argv[j]);
            output_fname[length-4] = 0;
            string_cat(output_fname, formatTable[format].extension);
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

/* . */
int
command_line_interface(int argc, char* argv[])
{
    EmbPattern *current_pattern = emb_pattern_create();
    int i, j, result;
    /* If no argument is given, drop into the postscript interpreter. */
    if (argc == 1) {
        return emb_repl();
    }

    char *script = (char *)malloc(argc*100);
    int flags = argc - 1;
    for (i=1; i < argc; i++) {
        result = -1;
        /* identify what flag index the user may have entered */
        for (j=0; j < NUM_FLAGS; j++) {
            if (string_equals(flag_list[j], argv[i])) {
                result = j;
                break;
            }
        }
        /* apply the flag */
        switch (result) {
        case FLAG_TO:
        case FLAG_TO_SHORT: {
            to_flag(argv, argc, i);
            break;
        }
        case FLAG_HELP:
        case FLAG_HELP_SHORT: {
            usage();
            break;
        }
        case FLAG_FORMATS:
        case FLAG_FORMATS_SHORT: {
            formats();
            break;
        }
        case FLAG_QUIET:
        case FLAG_QUIET_SHORT: {
            emb_verbose = -1;
            break;
        }
        case FLAG_VERBOSE:
        case FLAG_VERBOSE_SHORT: {
            emb_verbose = 1;
            break;
        }
        case FLAG_CIRCLE:
        case FLAG_CIRCLE_SHORT: {
            char script[200];
            if (i + 3 >= argc) {
                puts("Not enough arguments supplied to circle command: 3 required.");
                i = argc - 1;
                break;
            }
            sprintf(script, "%s %s %s circle", argv[i+1], argv[i+2], argv[i+3]);
            emb_actuator(current_pattern, script);
            break;
        }
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
                emb_pattern_horizontal_fill(current_pattern, &image, atoi(argv[i]));
                embImage_free(&image);
                i++;
                emb_pattern_writeAuto(current_pattern, argv[i]);
            }
            break;
        case FLAG_RENDER:
        case FLAG_RENDER_SHORT:
            if (i + 2 < argc) {
                /* the user appears to have entered filenames after render */
                emb_pattern_readAuto(current_pattern, argv[i+1]);
                printf("%d\n", current_pattern->stitch_list->count);
                emb_pattern_render(current_pattern, argv[i+2]);
                i += 2;
                break;
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.png'.");
                    emb_pattern_render(current_pattern, "output.png");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    emb_pattern_render(current_pattern, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.png'.");
                emb_pattern_render(current_pattern, "output.png");
            }
            break;
        case FLAG_SIMULATE:
            if (i + 1 < argc) {
                /* the user appears to have entered a filename after render */
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.avi'.");
                    emb_pattern_simulate(current_pattern, "output.avi");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    emb_pattern_simulate(current_pattern, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.avi'.");
                emb_pattern_simulate(current_pattern, "output.avi");
            }
            break;
        case FLAG_COMBINE:
            if (i + 3 < argc) {
                EmbPattern *out;
                EmbPattern *p1 = emb_pattern_create();
                EmbPattern *p2 = emb_pattern_create();
                emb_pattern_readAuto(p1, argv[i+1]);
                emb_pattern_readAuto(p2, argv[i+2]);
                out = emb_pattern_combine(p1, p2);
                emb_pattern_writeAuto(out, argv[i+3]);
                emb_pattern_free(p1);
                emb_pattern_free(p2);
                emb_pattern_free(out);
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
            current_pattern = emb_pattern_create();
            hilbert_curve(current_pattern, 3);
            break;
        case FLAG_TEST:
            if (i + 1 < argc) {
                emb_pattern_free(current_pattern);
                return testMain(atoi(argv[i+1]));
            }
            break;
        case FLAG_FULL_TEST_SUITE: {
            /* Ideally we use ctest, this is just for crash testing. */
			int t;
			emb_pattern_free(current_pattern);
            for (t=0; t<10; t++) {
                if (testMain(t)) {
                    printf("Failed test %d.\n", t);
					return 1;
                }
            }
			return 0;
		}
        case FLAG_CONVERT_TEST: {
			emb_pattern_free(current_pattern);
            if (i + 3 < argc) {
                return test_convert(atoi(argv[i+1]), atoi(argv[i+2]), atoi(argv[i+3]));
            }
			return 0;
		}
        case FLAG_CROSS_STITCH:
            if (i + 3 < argc) {
                EmbImage image;
                /* the user appears to have entered the needed arguments */
                image = embImage_create(2000, 2000);
                /* to stb command */
                embImage_read(&image, argv[i]);
                emb_pattern_crossstitch(current_pattern, &image, atoi(argv[i+1]));
                embImage_free(&image);
                emb_pattern_writeAuto(current_pattern, argv[i+2]);
                i += 3;
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
    emb_pattern_free(current_pattern);
    safe_free(script);
    return 0;
}

/* FILL ALGORITHMS
 */

const char *rules[] = {"+BF-AFA-FB+", "-AF+BFB+FA-"};

L_system hilbert_curve_l_system = {
    'A', "AB", "F+-", (char**)rules
};

/* a L a state a iterations a complete
 * Returns int
 *
 * This is a slow generation algorithm.
 */
int lindenmayer_system(L_system L, char *state, int iterations, int complete)
{
    /* We know that the full length of the curve has to fit within
     * the number of stitches and we can cancel consecutive +-, -+
     * etc.
     *

Potential reference:

@book{Prusinkiewicz1996Mar,
    author = {Prusinkiewicz, Przemyslaw and Lindenmayer, Aristid and Hanan, J. S. and Fracchia, F. D. and Fowler, D. R. and de Boer, M. J. M. and Mercer, L.},
    title = {{The Algorithmic Beauty of Plants (The Virtual Laboratory)}},
    year = {1996},
    month = {Mar},
    publisher = {Springer}
}
     */
    char *new_state;
    int j;

    if (complete == 0) {
        state[0] = L.axiom;
        state[1] = 0;
        lindenmayer_system(L, state, iterations, complete+1);
        return 0;
    }

    new_state = state + MAX_STITCHES*5;

    new_state[0] = 0;

    /* replace letters using rules by copying to new_state */
    for (j=0; j < (int)string_len(state); j++) {
        if (state[j] >= 'A' && state[j] < 'F') {
            string_cat(new_state, L.rules[state[j]-'A']);
        }
        if (state[j] == 'F') {
            string_cat(new_state, "F");
        }
        if (state[j] == '+') {
            string_cat(new_state, "+");
        }
        if (state[j] == '-') {
            string_cat(new_state, "-");
        }
    }
    memory_copy(state, new_state, string_len(new_state)+1);

    if (complete < iterations) {
        lindenmayer_system(L, state, iterations, complete+1);
    }
    return 0;
}

/* a points a n_points a width a tolerence
 *
 * Remove points that lie in the middle of two short stitches that could
 * be one longer stitch. Repeat until none are found.
 */
static void
join_short_stitches(int *points, int *n_points, int width, int tolerence)
{
    int found = 1;
    while (found > 0) {
        int i;
        found = 0;
        for (i=*n_points-2; i>=0; i--) {
            int st1 = points[i+1]%width - points[i]%width;
            int st2 = points[i+2]%width - points[i+1]%width;
            int same_line = (points[i+1]/width == points[i]/width)
                            && (points[i+2]/width == points[i+1]/width);
            if (st1 < tolerence && st2 < tolerence && same_line) {
                found++;
                break;
            }
        }
        if (found) {
            /* Remove the point. */
            i++;
            for (; i<*n_points; i++) {
                points[i] = points[i+1];
            }
            (*n_points)--;
        }
    }
}

/* a image a n_points a subsample_width a subsample_height
 * a threshold
 * Returns int*
 *
 * Identify darker pixels to put stitches in.
 */
static int *
threshold_method(EmbImage *image, int *n_points,
    int subsample_width, int subsample_height, int threshold)
{
    int i, j;
    int *points;
    int height = image->height;
    int width = image->width;
    points = (int *)malloc((height/subsample_height)
        *(width/subsample_width) * sizeof(int));
    *n_points = 0;
    for (i=0; i<height/subsample_height; i++)
    for (j=0; j<width/subsample_width; j++) {
        EmbColor color;
        int index = subsample_height*i*width+subsample_width*j;
        color.r = image->data[3*index+0];
        color.g = image->data[3*index+1];
        color.b = image->data[3*index+2];
        if (color.r+color.g+color.b < threshold) {
            points[*n_points] = index;
            (*n_points)++;
        }
    }
    return points;
}

/* a points a n_points a width a bias
 *
 * Greedy Algorithm
 * ----------------
 * For each point in the list find the shortest distance to
 * any possible neighbour, then perform a swap to make that
 * neighbour the next item in the list.
 *
 * To make the stitches lie more on one axis than the other
 * bias the distance operator to prefer horizontal direction.
 */
static void
greedy_algorithm(int *points, int n_points, int width, EmbReal bias)
{
    int i, j;
    printf("points[0] = %d\n", points[0]);
    printf("n_points = %d\n", n_points);
    printf("width = %d\n", width);
    printf("bias = %f\n", bias);

    for (i=0; i<n_points-1; i++) {
        int stor;
        EmbReal shortest = 1.0e20;
        int next = i+1;
        /* Find nearest neighbour. */
        int x1 = points[i]%width;
        int y1 = points[i]/width;
        for (j=i+1; j<n_points; j++) {
            int x, y;
            EmbReal distance;
            x = x1 - (points[j]%width);
            if (x*x > shortest) {
                continue;
            }
            y = y1 - (points[j]/width);
            distance = x*x + bias*y*y;
            if (distance < shortest) {
                next = j;
                shortest = distance;
            }
        }
        if (i%100 == 0) {
            printf("%2.1f%%\n", (100.0*i)/(1.0*n_points));
        }
        /* swap points */
        stor = points[next];
        points[next] = points[i+1];
        points[i+1] = stor;
    }
}

/* a pattern a points a n_points
 * a scale a width a height
 */
static void
save_points_to_pattern(
    EmbPattern *pattern, int *points, int n_points, EmbReal scale, int width, int height)
{
    int i;
    for (i=0; i<n_points; i++) {
        int x, y;
        x = points[i]%width;
        y = height - points[i]/width;
        emb_pattern_addStitchAbs(pattern, scale*x, scale*y, NORMAL, 0);
    }
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * lines in the fill.
 *
 * Needs to pass a "donut test", i.e. an image with black pixels where:
 *     10 < x*x + y*y < 20
 * over the area (-30, 30) x (-30, 30).
 *
 * Use render then image difference to see how well it passes.
 */
void
emb_pattern_horizontal_fill(EmbPattern *pattern, EmbImage *image, int threshhold)
{
    /* Size of the crosses in millimeters. */
    EmbReal scale = 0.1;
    int sample_w = 3;
    int sample_h = 3;
    EmbReal bias = 1.2;
    int *points;
    int n_points;

    points = threshold_method(image, &n_points, sample_w, sample_h, threshhold);
    greedy_algorithm(points, n_points, image->width, bias);
    join_short_stitches(points, &n_points, image->width, 40);
    save_points_to_pattern(pattern, points, n_points, scale, image->width, image->height);

    emb_pattern_end(pattern);
    safe_free(points);
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * crosses in the fill.
 *
 * To improve this, we can remove the vertical stitches when two crosses
 * neighbour. Currently the simple way to do this is to chain crosses
 * that are neighbours exactly one ahead.
 */
void
emb_pattern_crossstitch(EmbPattern *pattern, EmbImage *image, int threshhold)
{
    int i;
    /* Size of the crosses in millimeters. */
    EmbReal scale = 0.1;
    int sample_w = 5;
    int sample_h = 5;
    EmbReal bias = 1.0;
    int *points;
    int n_points;
    int width = 1000;
    points = threshold_method(image, &n_points, sample_w, sample_h, threshhold);
    greedy_algorithm(points, n_points, width, bias);

    for (i=0; i<n_points; i++) {
        EmbReal x, y;
        x = points[i]%width;
        y = points[i]/width;
        printf("%f %f\n", x, y);
        emb_pattern_addStitchAbs(pattern, scale*x, scale*y, NORMAL, 0);
        emb_pattern_addStitchAbs(pattern, scale*(x+sample_w), scale*(y+sample_h), NORMAL, 0);
        emb_pattern_addStitchAbs(pattern, scale*x, scale*(y+sample_h), NORMAL, 0);
        emb_pattern_addStitchAbs(pattern, scale*(x+sample_w), scale*y, NORMAL, 0);
    }

    emb_pattern_end(pattern);
}

/* a pattern a iterations
 *
 * https://en.wikipedia.org/wiki/Hilbert_curve
 *
 * Using the Lindenmayer System, so we can save work across
 * different functions.
 */
int
hilbert_curve(EmbPattern *pattern, int iterations)
{
    char *state;
    int i, position[2], direction;
    EmbReal scale = 1.0;

    /* Make the n-th iteration. */
    state = malloc(MAX_STITCHES*10);
    lindenmayer_system(hilbert_curve_l_system, state, iterations, 0);

    /* Convert to an embroidery pattern. */
    position[0] = 0;
    position[1] = 0;
    direction = 0;

    for (i = 0; i < (int)string_len(state); i++) {
        if (state[i] == '+') {
            direction = (direction + 1) % 4;
            continue;
        }
        if (state[i] == '-') {
            direction = (direction + 3) % 4;
            continue;
        }
        if (state[i] == 'F') {
            int flags = NORMAL;
            switch (direction) {
            case 0:
            default:
                position[0]--;
                break;
            case 1:
                position[1]++;
                break;
            case 2:
                position[0]++;
                break;
            case 3:
                position[1]--;
                break;
            }
            emb_pattern_addStitchAbs(pattern, position[0]*scale, position[1]*scale, flags, 0);
        }
    }
    safe_free(state);
    emb_pattern_end(pattern);
    return 0;
}

/* a state a iterations
 *
 * using the "paper folding" method
 * \todo find citation for paper folding method
 */
void generate_dragon_curve(char *state, int iterations)
{
    int i, length;
    if (iterations == 1) {
        state[0] = 'R';
        state[1] = 0;
        return;
    }
    length = string_len(state);
    for (i=length-1; i>=0; i--) {
        state[2*i+1] = state[i];
        if (i%2 == 0) {
            state[2*i] = 'R';
        } else {
            state[2*i] = 'L';
        }
    }
    state[2*length+1] = 0;
    generate_dragon_curve(state, iterations-1);
}

/* Create the dragon curve for a iterations.
 *
 * Returns 0 if the number of iterations is greater than 10
 * and 1 otherwise.
 */
int
dragon_curve(int iterations)
{
    char *state;
    if (iterations > 10) {
        puts("The dragon curve is only supported up to 10 iterations.");
        return 0;
    }
    state = malloc(1<<(iterations+1));
    generate_dragon_curve(state, iterations);
    safe_free(state);
    return 1;
}

#if 0
/* a pattern
 * Returns StitchBlock*
 */
StitchBlock*
BreakIntoColorBlocks(EmbPattern *pattern)
{
    int i;
    int sa2 = new StitchBlock();
    int oldColor = pattern->stitch_list->stitch[0].color;
    int color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
        if (s.color != oldColor) {
            yield return sa2;
            sa2 = new StitchBlock();
            color = pattern.ColorList[s.ColorIndex];
            sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
            oldColor = s.ColorIndex;
        }
        int vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color = s.ColorIndex };
        sa2.Stitches.Add(vs);
    }
    yield return sa2;
}

/* a blocks
 * Returns StitchBlock*
 */
StitchBlock *
BreakIntoSeparateObjects(EmbStitchBlock* blocks)
{
    int i, block;
    EmbReal previousAngle = 0.0;
    for (block=0; block<blocks->length; block++) {
        int stitches = new List<VectorStitch>();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches.Count - 1].Type = VectorStitchType.Contour;

        for (int i = 0; i < block.Stitches.Count - 2; i++) { /* step 0 */
            EmbReal dx = (emb_vector_relativeX(block.Stitches[i].Xy, block.Stitches[i + 1].Xy, block.Stitches[i + 2].Xy));
            block.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
            block.Stitches[i].Angle = GetAngle(block.Stitches[i], block.Stitches[i + 1]);
            stitches.Add(block.Stitches[i].Clone());
            if (i > 0) {
                if ((block.Stitches[i].Type == VectorStitchType.Contour) && fabs(block.Stitches[i].Angle - previousAngle) > (20/180*embConstantPi)) {
                    yield return
                        new StitchBlock
                            {
                                Stitches = stitches,
                                Angle = stitches.Average(x => x.Angle),
                                Thread = new Thread(block.Thread.Red, block.Thread.Blue, block.Thread.Green)
                            };
                    stitches = new List<VectorStitch>();

                }
            }
        }

        /* step 1 */
        for (i = 1; i < sa.Stitches.Count - 3; i++) {
            if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                float dy = emb_vector_relativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                float dy2 = emb_vector_relativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                float dy3 = emb_vector_relativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                if (dy)
                if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run) {
                    sa.Stitches[i].Type = VectorStitchType.Tatami;
                }
                else {
                    sa.Stitches[i].Type = VectorStitchType.Satin;
                }
            }
        }
    }
}

/* a stitchData
 * Returns StitchObject*
 */
StitchObject *
FindOutline(EmbStitchBlock* stitchData)
{
    int currColorIndex = 0, sa;
    int pOdd = new List<Point>();
    int pEven = new List<Point>();
    for (sa=0; sa<stitchData->count; sa++) {
        if (sa.Stitches.Count > 0) {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches.Count - 1].Type = VectorStitchType.Contour;
            /* step 0 */
            for (int i = 0; i < sa.Stitches.Count - 2; i++) {
                float dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle = emb_vector_angle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (int i = 1; i < sa.Stitches.Count - 3; i++) {
                if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                    float dy = emb_vector_relativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                    float dy2 = emb_vector_relativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                    float dy3 = emb_vector_relativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                    if (dy)
                    if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run) {
                        sa.Stitches[i].Type = VectorStitchType.Tatami;
                    }
                    else {
                        sa.Stitches[i].Type = VectorStitchType.Satin;
                    }
                }
            }
        }


        int oddEven = 0;
        foreach (VectorStitch t in sa.Stitches) {
            if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 0) {
                pEven.Add(t.Xy);

                oddEven++;
            }
            else if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 1) {
                pOdd.Add(t.Xy);
                oddEven++;
            }
        }
        currColorIndex++;
        int so = new StitchObject { SideOne = pEven, SideTwo = pOdd, ColorIndex = currColorIndex };
        yield return so;
        pEven = new List<Point>();
        pOdd = new List<Point>();
        /* break; */
    }
}

/* a p
 * Returns EmbPattern
 */
EmbPattern
DrawGraphics(EmbPattern p)
{
    int stitchData = BreakIntoColorBlocks(p);

    int outBlock = new List<StitchBlock>(BreakIntoSeparateObjects(stitchData));
    foreach(var block in stitchData) {
        foreach (var stitch in block.Stitches) {
            if (stitch.Angle != 0) {
                int aaa = 1;
            }
        }
    }
    int xxxxx = outBlock;
    int objectsFound = FindOutline(stitchData);
    int outPattern = new Pattern();
    outPattern.AddColor(new Thread(255, 0, 0, "none", "None"));
    int colorIndex = outPattern.ColorList.Count - 1;
    int r = new Random();
    foreach (StitchObject stitchObject in objectsFound) {
        if (stitchObject.SideOne.Count > 1 && stitchObject.SideTwo.Count > 1) {
            outPattern.AddColor(new Thread((byte) (r.Next()%256), (byte) (r.Next()%256), (byte) (r.Next()%256),
                                           "none", "None"));
            colorIndex++;
            outPattern.AddStitchRelative(0, 0, StitchTypes.Stop);
            int points = stitchObject.Generate2(75);
            foreach (var point in points) {
                outPattern.AddStitchAbsolute(point.X, point.Y, StitchTypes.Normal);
            }
            break;
            StitchObject stitchObject = objectsFound[1];))
            if (stitchObject.SideOne.Count > 0) {
                outPattern.stitch_list.Add(new Stitch(stitchObject.SideOne[0].X, stitchObject.SideOne[0].Y,
                                                     StitchType.Jump, colorIndex));
            }
            foreach (Point t in stitchObject.SideOne) {

                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
                                                     StitchType.Normal, colorIndex));
            }
            foreach (Point t in stitchObject.SideTwo) {
                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
                                                     StitchType.Normal, colorIndex));
            }
            break;
        }
    }
    outPattern.AddStitchRelative(0, 0, StitchTypes.End);
    return outPattern;
    /*
    return (SimplifyOutline(outPattern));
    */
}

/* a pattern
 * Returns EmbPattern
 */
EmbPattern
SimplifyOutline(EmbPattern pattern)
{
    int v = new Vertices();
    v.AddRange(pattern.stitch_list.Select(point => new Vector2(point.X, point.Y)));
    int output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
    int patternOut = new Pattern();
    foreach (var color in pattern.ColorList)
    {
        patternOut.AddColor(color);
    }

    foreach (var vertex in output)
    {
        patternOut.AddStitchAbsolute(vertex.X, vertex.Y, StitchTypes.Normal);
    }
    patternOut.AddStitchRelative(0, 0, StitchTypes.End);
    return patternOut;
}

bool[] _usePt;
EmbReal _distanceTolerance;

/* Removes all collinear points on the polygon.
 *
 * a vertices
 * a collinearityTolerance
 * Returns Vertices
 */
Vertices CollinearSimplify(Vertices vertices, float collinearityTolerance)
{
    /* We can't simplify polygons under 3 vertices */
    if (vertices.Count < 3)
        return vertices;

    int simplified = new Vertices();

    for (int i = 0; i < vertices.Count; i++) {
        int prevId = vertices.PreviousIndex(i);
        int nextId = vertices.NextIndex(i);

        Vector2 prev = vertices[prevId];
        Vector2 current = vertices[i];
        Vector2 next = vertices[nextId];

        /* If they collinear, continue */
        if (emb_vector_collinear(ref prev, ref current, ref next, collinearityTolerance))
            continue;

        simplified.Add(current);
    }

    return simplified;
}

/* vertices
 * Returns Vertices
 *
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * param vertices: The polygon that needs simplification.
 * returns: A simplified polygon.
 */
Vertices
CollinearSimplify(Vertices vertices)
{
    return CollinearSimplify(vertices, 0);
}

/* vertices
 * a distanceTolerance
 * Returns Vertices
 *
 * Ramer-Douglas-Peucker polygon simplification algorithm.
 * This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points.
 *
 * \todo Ramer-Douglas-Peucker citation
 */
Vertices
DouglasPeuckerSimplify(Vertices vertices, float distanceTolerance)
{
    _distanceTolerance = distanceTolerance;

    _usePt = new bool[vertices.Count];
    for (int i = 0; i < vertices.Count; i++)
    {
        _usePt[i] = true;
    }
    SimplifySection(vertices, 0, vertices.Count - 1);
    int result = new Vertices();
    result.AddRange(vertices.Where((t, i) => _usePt[i]));
    return result;
}

/*  vertices a i a j */
void
SimplifySection(Vertices vertices, int i, int j)
{
    if ((i + 1) == j)
        return;

    Vector2 a = vertices[i];
    Vector2 b = vertices[j];
    EmbReal maxDistance = -1.0;
    int maxIndex = i;
    for (int k = i + 1; k < j; k++)
    {
        EmbReal distance = DistancePointLine(vertices[k], a, b);

        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= _distanceTolerance) {
        for (int k = i + 1; k < j; k++) {
            _usePt[k] = 0;
        }
    }
    else {
        SimplifySection(vertices, i, maxIndex);
        SimplifySection(vertices, maxIndex, j);
    }
}

/* p a a a b
 * Returns EmbReal
 */
EmbReal
DistancePointLine(EmbVector p, EmbVector a, EmbVector b)
{
    /* if start == end, then use point-to-point distance */
    if (a.X == b.X && a.Y == b.Y)
        return DistancePointPoint(p, a);

    /* otherwise use comp.graphics.algorithms Frequently Asked Questions method */
    /* (1)               AC dot AB
                r =   ---------
                      ||AB||^2

                r has the following meaning:
                r=0 Point = A
                r=1 Point = B
                r<0 Point is on the backward extension of AB
                r>1 Point is on the forward extension of AB
                0<r<1 Point is interior to AB
    */

    EmbReal r = ((p.X - a.X) * (b.X - a.X) + (p.Y - a.Y) * (b.Y - a.Y))
               /
               ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    if (r <= 0.0) return DistancePointPoint(p, a);
    if (r >= 1.0) return DistancePointPoint(p, b);


    /* (2)
                    (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
                s = -----------------------------
                                Curve^2

                Then the distance from C to Point = |s|*Curve.
    */

    EmbReal s = ((a.Y - p.Y) * (b.X - a.X) - (a.X - p.X) * (b.Y - a.Y))
               /
               ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    return fabs(s) * sqrt(((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y)));
}

/* vertices a areaTolerance
 * Returns public
 *
 * From physics2d.net.
 */
public Vertices
ReduceByArea(Vertices vertices, float areaTolerance)
{
    if (vertices.Count <= 3)
        return vertices;

    if (areaTolerance < 0)
    {
        throw new ArgumentOutOfRangeException("areaTolerance", "must be equal to or greater then zero.");
    }

    int result = new Vertices();
    Vector2 v3;
    Vector2 v1 = vertices[vertices.Count - 2];
    Vector2 v2 = vertices[vertices.Count - 1];
    areaTolerance *= 2;
    for (int index = 0; index < vertices.Count; ++index, v2 = v3)
    {
        if (index == vertices.Count - 1)
        {
            if (result.Count == 0)
            {
                throw new ArgumentOutOfRangeException("areaTolerance", "The tolerance is too high!");
            }
            v3 = result[0];
        }
        else
        {
            v3 = vertices[index];
        }
        float old1, old2, new1;
        MathUtils.Cross(ref v1, ref v2, out old1);
        MathUtils.Cross(ref v2, ref v3, out old2);
        MathUtils.Cross(ref v1, ref v3, out new1);
        if (fabs(new1 - (old1 + old2)) > areaTolerance)
        {
            result.Add(v2);
            v1 = v2;
        }
    }
    return result;
}

/* vertices a tolerance
 *
 * From Eric Jordan's convex decomposition library.
 * Merges all parallel edges in the list of vertices.
 */
void
MergeParallelEdges(EmbArray *vertices, float tolerance)
{
    int i;
    if (vertices.Count <= 3) {
        /* Can't do anything useful here to a triangle. */
        return;
    }

    int mergeMe = new bool[vertices.Count];
    int newNVertices = vertices.Count;

    /* Gather points to process */
    for (i = 0; i < vertices->count; i++) {
        EmbVector delta0, delta1;
        int lower = (i == 0) ? (vertices.Count - 1) : (i - 1);
        int upper = (i == vertices.Count - 1) ? (0) : (i + 1);

        delta0 = emb_vector_subtract(vertices[i], vertices[lower]);
        delta1 = emb_vector_subtract(vertices[upper], vertices[i]);
        float norm0 = emb_vector_length(delta0);
        float norm1 = emb_vector_length(delta0);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            mergeMe[i] = 1;
            newNVertices--;
        }

        delta0 = emb_vector_normalize(delta0);
        delta1 = emb_vector_normalize(delta1);
        float cross = emb_vector_cross(delta0, delta1);
        float dot = emb_vector_dot(delta0, delta1);

        if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            mergeMe[i] = 1;
            newNVertices--;
        }
        else {
            mergeMe[i] = 0;
        }
    }

    if (newNVertices == vertices.Count || newNVertices == 0)
        return;

    int currIndex = 0;

    /* Copy the vertices to a new list and clear the old */
    int oldVertices = new Vertices(vertices);
    vertices.Clear();

    for (i = 0; i < oldVertices.Count; i++) {
        if (mergeMe[i] || newNVertices == 0 || currIndex == newNVertices)
            continue;

        vertices.Add(oldVertices[i]);
        currIndex++;
    }
}
#endif

void embPolygon_reduceByDistance(EmbArray *vertices, EmbArray *simplified, float distance);
void embPolygon_reduceByNth(EmbArray *vertices, EmbArray *out, int nth);

/* vertices a simplified a distance
 *
 * Reduces the polygon by distance.
 *
 * This is a non-destructive function, so the caller is responsible for
 * freeing "vertices" if they choose to keep "simplified".
 */
void embPolygon_reduceByDistance(EmbArray *vertices, EmbArray *simplified, float distance)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        emb_array_copy(simplified, vertices);
        return;
    }

    for (i = 0; i < vertices->count; i++) {
        EmbVector delta;
        int nextId = (i + 1) % vertices->count;

        delta = emb_vector_subtract(
            vertices->geometry[nextId].object.vector,
            vertices->geometry[i].object.vector);

        /* If they are closer than the distance, continue */
        if (emb_vector_length(delta) < distance) {
            continue;
        }

        emb_array_addVector(simplified, vertices->geometry[i].object.vector);
    }
}

/* vertices a out a nth
 *
 * Reduces the polygon by removing the Nth vertex in the vertices list.
 * This is a non-destructive function, so the caller is responsible for
 * freeing vertices if they choose to keep out.
 */
void
embPolygon_reduceByNth(EmbArray *vertices, EmbArray *out, int nth)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        emb_array_copy(out, vertices);
        return;
    }

    for (i=0; i<vertices->count; i++) {
        if (i!=nth) {
            emb_array_addVector(out, vertices->geometry[i].object.vector);
        }
    }
}

/* p1 a p2
 * Returns EmbPattern*
 */
EmbPattern *
emb_pattern_combine(EmbPattern *p1, EmbPattern *p2)
{
    int i;
    EmbPattern *out = emb_pattern_create();
    for (i=0; i<p1->stitch_list->count; i++) {
        emb_array_addStitch(out->stitch_list, p1->stitch_list->stitch[i]);
    }
    for (i=0; i<p2->stitch_list->count; i++) {
        emb_array_addStitch(out->stitch_list, p2->stitch_list->stitch[i]);
    }
    /* These need to be merged, not appended. */
    for (i=0; i<p1->thread_list->count; i++) {
        emb_pattern_addThread(out, p1->thread_list->thread[i]);
    }
    for (i=0; i<p2->thread_list->count; i++) {
        emb_pattern_addThread(out, p2->thread_list->thread[i]);
    }
    return out;
}

/* p a arc a thread_index a style
 */
void
emb_pattern_stitchArc(EmbPattern *p, EmbArc arc, int thread_index, int style)
{
    printf("DEBUG stitchArc (unfinished): %f %f %d %d\n",
        p->home.x, arc.start.x, thread_index, style);
}

/* p a circle a thread_index a style
 *
 * style determines:
 *     stitch density
 *     fill pattern
 *     outline or fill
 *
 * For now it's a straight fill of 1000 stitches of the whole object by
 * default.
 *
 * Consider the intersection of a line in direction "d" that passes through
 * the disc with center "c", radius "r". The start and end points are:
 *
 *     $(c-r(d/|d|), c + r(d/|d|))$
 *
 * Lines that are above and below this with an even seperation $s$ can be
 * found by taking the point on the line to be c+sn where the $n$ is the
 * unit normal vector to $d$ and the vector to be $d$ again. The
 * intersection points are therefore a right angled triangle, with one side
 * r, another s and the third the length to be solved, by Pythagoras we
 * have:
 *
 *    $(c + sn - \sqrt{r^2-s^2}(d/|d|), c + sn + \sqrt{r^2-s^2}(d/|d|))$
 *
 * repeating this process gives us all the end points and the fill only
 * alters these lines by splitting the ones longer than some tolerence.
 */
void
emb_pattern_stitchCircle(EmbPattern *p, EmbCircle circle, int thread_index, int style)
{
    float s;
    float seperation = 0.1;
    EmbVector direction = {1.0, 1.0};
    EmbVector normal = {-1.0, 1.0};
    direction = emb_vector_normalize(direction);
    normal = emb_vector_normalize(normal);
    for (s=-circle.radius; s<circle.radius; s += seperation) {
        EmbLine line;
        float length = sqrt(circle.radius*circle.radius - s*s);
        EmbVector scaled = emb_vector_scale(normal, s);
        line.start = emb_vector_add(circle.center, scaled);
        scaled = emb_vector_scale(direction, length);
        line.start = emb_vector_subtract(line.start, scaled);
        scaled = emb_vector_scale(normal, s);
        line.end = emb_vector_add(circle.center, scaled);
        scaled = emb_vector_scale(direction, length);
        line.end = emb_vector_add(line.end, scaled);
        /* Split long stitches here. */
        emb_pattern_addStitchAbs(p, line.start.x, line.start.y, NORMAL, thread_index);
        emb_pattern_addStitchAbs(p, line.end.x, line.end.y, NORMAL, thread_index);
    }
}

/* a p a ellipse a thread_index a style
 *
 * \todo finish stitchEllipse
 */
void
emb_pattern_stitchEllipse(EmbPattern *p, EmbEllipse ellipse, int thread_index, int style)
{
    printf("DEBUG stitchEllipse: %f %f %d %d\n",
        p->home.x, ellipse.center.x, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch path
 */
void
emb_pattern_stitchPath(EmbPattern *p, EmbPath path, int thread_index, int style)
{
    printf("DEBUG stitchPath: %f %d %d %d\n",
        p->home.x, path.pointList->count, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch polygon
 */
void
emb_pattern_stitchPolygon(EmbPattern *p, EmbPolygon polygon, int thread_index, int style)
{
    printf("DEBUG stitchPolygon: %f %d %d %d\n",
        p->home.x, polygon.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * \todo finish stitch polyline
 */
void
emb_pattern_stitchPolyline(EmbPattern *p, EmbPolyline polyline, int thread_index, int style)
{
    printf("DEBUG stitchPolyline: %f %d %d %d\n",
        p->home.x, polyline.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * Here we just stitch the rectangle in the direction of it's longer side.
 */
void
emb_pattern_stitchRect(EmbPattern *p, EmbRect rect, int thread_index, int style)
{
    EmbReal seperation = 0.1;
    EmbReal width = rect.right - rect.left;
    EmbReal height = rect.bottom - rect.top;
    if (width > height) {
        float s;
        for (s=rect.top; s<rect.bottom; s += seperation) {
            /* Split long stitches here. */
            emb_pattern_addStitchAbs(p, rect.top, s, NORMAL, thread_index);
            emb_pattern_addStitchAbs(p, rect.bottom, s, NORMAL, thread_index);
        }
    }
    else {
        float s;
        for (s=rect.left; s<rect.right; s += seperation) {
            /* Split long stitches here. */
            emb_pattern_addStitchAbs(p, s, rect.left, NORMAL, thread_index);
            emb_pattern_addStitchAbs(p, s, rect.right, NORMAL, thread_index);
        }
    }
}

/* a p a rect a thread_index a style
 */
void
emb_pattern_stitchText(EmbPattern *p, EmbRect rect, int thread_index, int style)
{
    printf("DEBUG: %f %f %d %d",
        p->home.x, rect.top, thread_index, style);
}

/* a p
 */
void
emb_pattern_convertGeometry(EmbPattern* p)
{
    int i;
    for (i=0; i<p->geometry->count; i++) {
        EmbGeometry g = p->geometry->geometry[i];
        switch (g.type) {
        case EMB_ARC: {
            /* To Do make the thread up here. */
            emb_pattern_stitchArc(p, g.object.arc, 0, 0);
            break;
        }
        case EMB_CIRCLE: {
            /* To Do make the thread up here. */
            emb_pattern_stitchCircle(p, g.object.circle, 0, 0);
            break;
        }
        case EMB_ELLIPSE: {
            /* To Do make the thread up here. */
            emb_pattern_stitchEllipse(p, g.object.ellipse, 0, 0);
            break;
        }
        case EMB_RECT: {
            /* To Do make the thread up here. */
            emb_pattern_stitchRect(p, g.object.rect, 0, 0);
            break;
        }
        default:
            break;
        }
    }
    /* Now ignore the geometry when writing. */
    p->geometry->count = 0;
}

/*
 * Frame for PES formats
 */
const char imageWithFrame[38][48] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

/* Check that the pointer isn't NULL before freeing. */
void
safe_free(void *data)
{
    if (data) {
        free(data);
        data = 0;
    }
}

unsigned char
char_to_lower(unsigned char a)
{
    if (a >= 'A' && a <= 'Z') {
        a = a - 'A' + 'a';
    }
    return a;
}

/* Get extension from file name. */
int
embFormat_getExtension(const char *fileName, char ending[5])
{
    int i;
    const char *offset;

    if (!fileName) {
        printf("ERROR: emb-format.c embFormat_getExtension(), fileName argument is null\n");
        return 0;
    }

    if (string_len(fileName) == 0) {
        return 0;
    }

    offset = fileName + string_rchar(fileName, '.');
    if (offset == fileName) {
        return 0;
    }

    i = 0;
    while (offset[i] != '\0') {
        ending[i] = char_to_lower(offset[i]);
        ++i;
    }
    ending[i] = 0; /* terminate the string */
    return 1;
}

/* Identify format from the file name. */
int
emb_identify_format(const char *fileName)
{
    int i;
    char ending[5];
    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }
    for (i = 0; i < numberOfFormats; i++) {
        if (string_equals(ending, formatTable[i].extension)) {
            return i;
        }
    }
    return -1;
}

/* TODO: Replace with embInt_read macros. */
short
fread_int16(void* f)
{
    short x;
    emb_read(f, &x, EMB_INT16_LITTLE);
    return x;
}

/* \todo replace with embInt_read
 */
unsigned short
fread_uint16(void* f)
{
    unsigned short x;
    emb_read(f, &x, EMB_INT16_LITTLE);
    return x;
}

/* . */
void
fpad(void* file, char c, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        emb_fwrite(&c, 1, file);
    }
}

/* \todo replace with embInt_read
 */
void
binaryWriteShort(void* f, short data)
{
    emb_write(f, &data, EMB_INT16_LITTLE);
}

/* \todo replace with embInt_read
 */
void
binaryWriteUShort(void* f, unsigned short data)
{
    emb_write(f, &data, EMB_INT16_LITTLE);
}

/* \todo replace with embInt_read
 */
void
binaryWriteUShortBE(void* f, unsigned short data)
{
    emb_write(f, &data, EMB_INT16_BIG);
}

/* \todo replace with embInt_read
 */
void
binaryWriteInt(void* f, int data)
{
    emb_write(f, &data, EMB_INT32_LITTLE);
}

/* \todo replace with embInt_read
 */
void
binaryWriteIntBE(void* f, int data)
{
    emb_write(f, &data, EMB_INT32_BIG);
}

/* \todo replace with embInt_read
 */
void
binaryWriteUInt(void* f, unsigned int data)
{
    emb_write(f, &data, EMB_INT32_LITTLE);
}

/* \todo replace with embInt_read
 */
void
binaryWriteUIntBE(void* f, unsigned int data)
{
    emb_write(f, &data, EMB_INT32_BIG);
}

/* . */
char
emb_pattern_read(EmbPattern* pattern, const char *fileName, int format)
{
    int result;
    void *file;
    result = 0;
    if (!pattern) {
        printf("ERROR: emb_pattern_read(), pattern argument is null.\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: emb_pattern_read(), fileName argument is null.\n");
        return 0;
    }
    file = emb_fopen(fileName, "rb");
    if (!file) {
        if ((format != EMB_FORMAT_EDR) &&
            (format != EMB_FORMAT_RGB) &&
            (format != EMB_FORMAT_COL) &&
            (format != EMB_FORMAT_INF)) {
            printf("ERROR: Failed to open file with name: %s.\n", fileName);
        }
        return 0;
    }
    if (formatTable[format].check_for_color_file) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    switch (format) {
    case EMB_FORMAT_100:
        result = read_stitch_block(pattern, file, toyota_100_decode, 4, 0);
        break;
    case EMB_FORMAT_10O:
        result = read_stitch_block(pattern, file, toyota_10o_decode, 3, 0);
        break;
    case EMB_FORMAT_ART:
        result = read_stitch_block(pattern, file, bernina_art_decode, 1, 0);
        break;
    case EMB_FORMAT_BMC:
        result = readBmc(pattern, file);
        break;
    case EMB_FORMAT_BRO:
        result = readBro(pattern, file);
        break;
    case EMB_FORMAT_CND:
        result = readCnd(pattern, file);
        break;
    case EMB_FORMAT_COL:
        result = readCol(pattern, file);
        break;
    case EMB_FORMAT_CSD:
        result = readCsd(pattern, file);
        break;
    case EMB_FORMAT_CSV:
        result = readCsv(pattern, file);
        break;
    case EMB_FORMAT_DAT:
        result = readDat(pattern, file);
        break;
    case EMB_FORMAT_DEM:
        result = readDem(pattern, file);
        break;
    case EMB_FORMAT_DSB:
        result = readDsb(pattern, file);
        break;
    case EMB_FORMAT_DST:
        result = readDst(pattern, file);
        break;
    case EMB_FORMAT_DSZ:
        result = readDsz(pattern, file);
        break;
    case EMB_FORMAT_DXF:
        result = readDxf(pattern, file);
        break;
    case EMB_FORMAT_EDR:
        result = readEdr(pattern, file);
        break;
    case EMB_FORMAT_EMD:
        result = readEmd(pattern, file);
        break;
    case EMB_FORMAT_EXP:
        result = readExp(pattern, file);
        break;
    case EMB_FORMAT_EXY:
        result = readExy(pattern, file);
        break;
    case EMB_FORMAT_EYS:
        result = readEys(pattern, file);
        break;
    case EMB_FORMAT_FXY:
        result = readFxy(pattern, file);
        break;
    case EMB_FORMAT_GC:
        result = readGc(pattern, file);
        break;
    case EMB_FORMAT_GNC:
        result = readGnc(pattern, file);
        break;
    case EMB_FORMAT_GT:
        result = readGt(pattern, file);
        break;
    case EMB_FORMAT_HUS:
        result = readHus(pattern, file);
        break;
    case EMB_FORMAT_INB:
        result = readInb(pattern, file);
        break;
    case EMB_FORMAT_INF:
        result = readInf(pattern, file);
        break;
    case EMB_FORMAT_JEF:
        result = readJef(pattern, file);
        break;
    case EMB_FORMAT_KSM:
        result = readKsm(pattern, file);
        break;
    case EMB_FORMAT_MAX:
        result = readMax(pattern, file);
        break;
    case EMB_FORMAT_MIT:
        result = readMit(pattern, file);
        break;
    case EMB_FORMAT_NEW:
        result = readNew(pattern, file);
        break;
    case EMB_FORMAT_OFM:
        result = readOfm(pattern, file);
        break;
    case EMB_FORMAT_PCD:
        result = readPcd(pattern, fileName, file);
        break;
    case EMB_FORMAT_PCM:
        result = readPcm(pattern, file);
        break;
    case EMB_FORMAT_PCQ:
        result = readPcq(pattern, fileName, file);
        break;
    case EMB_FORMAT_PCS:
        result = readPcs(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEC:
        result = readPec(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEL:
        result = readPel(pattern, file);
        break;
    case EMB_FORMAT_PEM:
        result = readPem(pattern, file);
        break;
    case EMB_FORMAT_PES:
        result = readPes(pattern, fileName, file);
        break;
    case EMB_FORMAT_PHB:
        result = readPhb(pattern, file);
        break;
    case EMB_FORMAT_PHC:
        result = readPhc(pattern, file);
        break;
    case EMB_FORMAT_PLT:
        result = readPlt(pattern, file);
        break;
    case EMB_FORMAT_RGB:
        result = readRgb(pattern, file);
        break;
    case EMB_FORMAT_SEW:
        result = readSew(pattern, file);
        break;
    case EMB_FORMAT_SHV:
        result = readShv(pattern, file);
        break;
    case EMB_FORMAT_SST:
        result = readSst(pattern, file);
        break;
    case EMB_FORMAT_STX:
        result = readStx(pattern, file);
        break;
    case EMB_FORMAT_SVG:
        result = readSvg(pattern, file);
        break;
    case EMB_FORMAT_T01:
        result = readT01(pattern, file);
        break;
    case EMB_FORMAT_T09:
        result = readT09(pattern, file);
        break;
    case EMB_FORMAT_TAP:
        result = readTap(pattern, file);
        break;
    case EMB_FORMAT_THR:
        result = readThr(pattern, file);
        break;
    case EMB_FORMAT_TXT:
        result = readTxt(pattern, file);
        break;
    case EMB_FORMAT_U00:
        result = readU00(pattern, file);
        break;
    case EMB_FORMAT_U01:
        result = readU01(pattern, file);
        break;
    case EMB_FORMAT_VIP:
        result = readVip(pattern, file);
        break;
    case EMB_FORMAT_VP3:
        result = readVp3(pattern, file);
        break;
    case EMB_FORMAT_XXX:
        result = readXxx(pattern, file);
        break;
    case EMB_FORMAT_ZSK:
        result = readZsk(pattern, file);
        break;
    default:
        break;
    }
    fclose(file);
    if (!formatTable[format].color_only) {
        emb_pattern_end(pattern);
    }
    return result;
}

/* . */
char
emb_pattern_write(EmbPattern* pattern, const char *fileName, int format)
{
    void *file;
    int result = 0;
    if (!pattern) {
        printf("ERROR: emb_pattern_write(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: emb_pattern_write(), fileName argument is null\n");
        return 0;
    }
    if (pattern->stitch_list->count == 0) {
        printf("ERROR: emb_pattern_write(), pattern contains no stitches\n");
        return 0;
    }
    if (!formatTable[format].color_only) {
        emb_pattern_end(pattern);
    }

    file = emb_fopen(fileName, "wb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }
    switch (format) {
    case EMB_FORMAT_100:
        result = write_stitch_block(pattern, file, toyota_100_encode, 4, 0);
        break;
    case EMB_FORMAT_10O:
        result = write_stitch_block(pattern, file, toyota_10o_encode, 3, 0);
        break;
    case EMB_FORMAT_ART:
        result = write_stitch_block(pattern, file, bernina_art_encode, 1, 0);
        break;
    case EMB_FORMAT_BMC:
        result = writeBmc(pattern, file);
        break;
    case EMB_FORMAT_BRO:
        result = writeBro(pattern, file);
        break;
    case EMB_FORMAT_CND:
        result = writeCnd(pattern, file);
        break;
    case EMB_FORMAT_COL:
        result = writeCol(pattern, file);
        break;
    case EMB_FORMAT_CSD:
        result = writeCsd(pattern, file);
        break;
    case EMB_FORMAT_CSV:
        result = writeCsv(pattern, file);
        break;
    case EMB_FORMAT_DAT:
        result = writeDat(pattern, file);
        break;
    case EMB_FORMAT_DEM:
        result = writeDem(pattern, file);
        break;
    case EMB_FORMAT_DSB:
        result = writeDsb(pattern, file);
        break;
    case EMB_FORMAT_DST:
        result = writeDst(pattern, file);
        break;
    case EMB_FORMAT_DSZ:
        result = writeDsz(pattern, file);
        break;
    case EMB_FORMAT_DXF:
        result = writeDxf(pattern, file);
        break;
    case EMB_FORMAT_EDR:
        result = writeEdr(pattern, file);
        break;
    case EMB_FORMAT_EMD:
        result = writeEmd(pattern, file);
        break;
    case EMB_FORMAT_EXP:
        result = writeExp(pattern, file);
        break;
    case EMB_FORMAT_EXY:
        result = writeExy(pattern, file);
        break;
    case EMB_FORMAT_EYS:
        result = writeEys(pattern, file);
        break;
    case EMB_FORMAT_FXY:
        result = writeFxy(pattern, file);
        break;
    case EMB_FORMAT_GC:
        result = writeGc(pattern, file);
        break;
    case EMB_FORMAT_GNC:
        result = writeGnc(pattern, file);
        break;
    case EMB_FORMAT_GT:
        result = writeGt(pattern, file);
        break;
    case EMB_FORMAT_HUS:
        result = writeHus(pattern, file);
        break;
    case EMB_FORMAT_INB:
        result = writeInb(pattern, file);
        break;
    case EMB_FORMAT_INF:
        result = writeInf(pattern, file);
        break;
    case EMB_FORMAT_JEF:
        result = writeJef(pattern, file);
        break;
    case EMB_FORMAT_KSM:
        result = writeKsm(pattern, file);
        break;
    case EMB_FORMAT_MAX:
        result = writeMax(pattern, file);
        break;
    case EMB_FORMAT_MIT:
        result = writeMit(pattern, file);
        break;
    case EMB_FORMAT_NEW:
        result = writeNew(pattern, file);
        break;
    case EMB_FORMAT_OFM:
        result = writeOfm(pattern, file);
        break;
    case EMB_FORMAT_PCD:
        result = writePcd(pattern, file);
        break;
    case EMB_FORMAT_PCM:
        result = writePcm(pattern, file);
        break;
    case EMB_FORMAT_PCQ:
        result = writePcq(pattern, file);
        break;
    case EMB_FORMAT_PCS:
        result = writePcs(pattern, file);
        break;
    case EMB_FORMAT_PEC:
        result = writePec(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEL:
        result = writePel(pattern, file);
        break;
    case EMB_FORMAT_PEM:
        result = writePem(pattern, file);
        break;
    case EMB_FORMAT_PES:
        result = writePes(pattern, fileName, file);
        break;
    case EMB_FORMAT_PHB:
        result = writePhb(pattern, file);
        break;
    case EMB_FORMAT_PHC:
        result = writePhc(pattern, file);
        break;
    case EMB_FORMAT_PLT:
        result = writePlt(pattern, file);
        break;
    case EMB_FORMAT_RGB:
        result = writeRgb(pattern, file);
        break;
    case EMB_FORMAT_SEW:
        result = writeSew(pattern, file);
        break;
    case EMB_FORMAT_SHV:
        result = writeShv(pattern, file);
        break;
    case EMB_FORMAT_SST:
        result = writeSst(pattern, file);
        break;
    case EMB_FORMAT_STX:
        result = writeStx(pattern, file);
        break;
    case EMB_FORMAT_SVG:
        result = writeSvg(pattern, file);
        break;
    case EMB_FORMAT_T01:
        result = writeT01(pattern, file);
        break;
    case EMB_FORMAT_T09:
        result = writeT09(pattern, file);
        break;
    case EMB_FORMAT_TAP:
        result = writeTap(pattern, file);
        break;
    case EMB_FORMAT_THR:
        result = writeThr(pattern, file);
        break;
    case EMB_FORMAT_TXT:
        result = writeTxt(pattern, file);
        break;
    case EMB_FORMAT_U00:
        result = writeU00(pattern, file);
        break;
    case EMB_FORMAT_U01:
        result = writeU01(pattern, file);
        break;
    case EMB_FORMAT_VIP:
        result = writeVip(pattern, file);
        break;
    case EMB_FORMAT_VP3:
        result = writeVp3(pattern, file);
        break;
    case EMB_FORMAT_XXX:
        result = writeXxx(pattern, file);
        break;
    case EMB_FORMAT_ZSK:
        result = writeZsk(pattern, file);
        break;
    default:
        break;
    }
    if (formatTable[format].write_external_color_file) {
        char externalFileName[1000];
        int stub_length;
        string_copy(externalFileName, fileName);
        stub_length = string_len(fileName)-string_len(formatTable[format].extension);
        externalFileName[stub_length] = 0;
        string_cat(externalFileName, ".rgb");
        emb_pattern_write(pattern, externalFileName, EMB_FORMAT_RGB);
    }
    fclose(file);
    return result;
}

/* . */
char
emb_pattern_readAuto(EmbPattern* pattern, const char* fileName)
{
    int format = emb_identify_format(fileName);
    if (format < 0) {
        printf("ERROR: convert(), unsupported read file type: %s\n", fileName);
        emb_pattern_free(pattern);
        return 0;
    }
    return emb_pattern_read(pattern, fileName, format);
}

/* . */
char
emb_pattern_writeAuto(EmbPattern* pattern, const char* fileName)
{
    int format = emb_identify_format(fileName);
    if (format < 0) {
        printf("ERROR: convert(), unsupported write file type: %s\n", fileName);
        emb_pattern_free(pattern);
        return 0;
    }
    return emb_pattern_write(pattern, fileName, format);
}

/*
 * TO DO: NEEDS ERROR REPORTING.
 */
unsigned char
toyota_position_encode(EmbReal x)
{
    if (x < 0.0) {
        return 0x80 + (-((char)emb_round(10.0*x)));
    }
    return (unsigned char)emb_round(10.0*x);
}

/*
 * .
 */
EmbReal
toyota_position_decode(unsigned char a)
{
    if (a > 0x80) {
        return - 0.1 * (a - 0x80);
    }
    return 0.1 * a;
}

/* The Toyota 100 format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 4 byte chunks.
 */
void
toyota_100_encode(EmbVector *head_position, EmbStitch *st, unsigned char *b)
{
        EmbVector delta;
        delta.x = st->x - head_position->x;
        delta.y = st->y - head_position->y;
        *head_position = emb_vector_add(*head_position, delta);
        b[0] = 0;
        b[1] = 0;
        b[2] = toyota_position_encode(delta.x);
        b[3] = toyota_position_encode(delta.y);
        if (!(st->flags & STOP)) {
            b[0] |= 0x01;
        }
        if (st->flags & END) {
            b[0] = 0x1F;
        }
}

void
toyota_100_decode(EmbVector *head_position, EmbStitch *st, unsigned char *b)
{
        int stitchType;
        st->x = toyota_position_decode(b[2]);
        st->y = toyota_position_decode(b[3]);
        st->flags = NORMAL;
        /*
        if (!(b[0] & 0xFC)) {
            st.flags = JUMP;
            TODO: review & fix
        }
        */
        if (!(b[0] & 0x01)) {
            st->flags = STOP;
        }
        if (b[0] == 0x1F) {
            st->flags = END;
        }
}

/* The Toyota 10o format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 3 byte chunks.
 */
void
toyota_10o_encode(EmbVector *head_position, EmbStitch *st, unsigned char *b)
{
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        if (st->x < 0) {
            b[2] |= 0x20;
            b[0] = -st->x;
        }
        else {
            b[0] = st->x;
        }
        if (st->y < 0) {
            b[2] |= 0x40;
            b[1] = -st->y;
        }
        else {
            b[1] = st->y;
        }
        if (st->flags == TRIM) {
            b[2] |= 1;
        }
        if (st->flags == STOP) {
            b[2] |= 5;
        }
        if (st->flags == END) {
            b[2] = 0xF8;
        }
}

void
toyota_10o_decode(EmbVector *head_position, EmbStitch *st, unsigned char *b)
{
        st->flags = NORMAL;
        unsigned char ctrl = b[0];
        st->y = 0.1 * b[1];
        st->x = 0.1 * b[2];
        if (ctrl & 0x20) {
            st->x = -st->x;
        }
        if (ctrl & 0x40) {
            st->y = -st->y;
        }
        if (ctrl & 0x01) {
            st->flags = TRIM;
        }
        if ((ctrl & 0x5) == 5) {
            st->flags = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            st->flags = END;
        }
}

/* The Bernina Embroidery Format (.art)
 *
 * We don't know much about this format. \todo Find a source.
 */
void
bernina_art_encode(EmbVector *position, EmbStitch *st, unsigned char *b)
{
    puts("ERROR: bernina_art_encode is not supported.");
    b[0] = 0;
}

void
bernina_art_decode(EmbVector *position, EmbStitch *st, unsigned char *b)
{
    puts("ERROR: bernina_art_decode is not supported.");
    st->flags = NORMAL;
}

/* A generic reader loop for any format that uses a binary block representing
 * an array of stitches.
 */
char
read_stitch_block(
    EmbPattern *pattern,
    void *file,
    void (*stitch_decoder)(EmbVector *, EmbStitch *, unsigned char *),
    int stitch_data_size,
    int mode
)
{
    unsigned char b[10];
    while (fread(b, 1, stitch_data_size, file) == stitch_data_size) {
        EmbVector position;
        EmbStitch st;
        st.flags = NORMAL;
        st.x = 0.0;
        st.y = 0.0;
        position.x = 0.0;
        position.y = 0.0;
        stitch_decoder(&position, &st, b);
        emb_pattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }
    return 1;
}

/* A generic writer loop for any format that uses a binary block representing
 * an array of stitches.
 */
char
write_stitch_block(
    EmbPattern *pattern,
    void *file,
    void (*stitch_encoder)(EmbVector *, EmbStitch *, unsigned char *),
    int stitch_data_size,
    int mode
)
{
    int i;
    EmbVector position;

    position = pattern->home;
    for (i=0; i<pattern->stitch_list->count; i++) {
        unsigned char b[10];
        EmbStitch st = pattern->stitch_list->stitch[i];
        stitch_encoder(&position, &st, b);
        int bytes_written = emb_fwrite(b, stitch_data_size, file);
        if (bytes_written != stitch_data_size) {
            return 0;
        }
    }
    return 1;
}

/* The Bitmap Cache Embroidery Format (.bmc)
 *
 * We don't know much about this format. \todo Find a source.
 */
char
readBmc(EmbPattern* pattern, void* file)
{
    puts("readBmc is not implemented");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish readBmc */
}

char
writeBmc(EmbPattern* pattern, void* file)
{
    puts("writeBmc is not implemented");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeBmc */
}

/* The Bits and Volts Embroidery Format (.bro)
 *
 * The Bits and Volts bro format is a stitch-only format that
 * uses an external color file.
 *
 * The header is 256 bytes.
 * There's a series of unknown variables in the header.
 *
 * The stitch list uses a variable length encoding which is
 * 2 bytes for any stitch.
 */

#define READ_BYTES(dest, n) \
    read_bytes = emb_fread(dest, n, file); \
    if (!read_bytes) { \
	    return 0; \
    }

char
readBro(EmbPattern* pattern, void* file)
{
    unsigned char x55;
    short unknown1, unknown2, unknown3, unknown4, moreBytesToEnd;
    char name[8];
    int stitchType;
    int read_bytes;
    READ_BYTES(&x55, 1);
    /* TODO: determine what this unknown data is */
    READ_BYTES(&unknown1, 2);

    READ_BYTES(name, 8);
    /* TODO: determine what this unknown data is */
    READ_BYTES(&unknown2, 2);
    /* TODO: determine what this unknown data is */
    READ_BYTES(&unknown3, 2);
    /* TODO: determine what this unknown data is */
    READ_BYTES(&unknown4, 2);
    READ_BYTES(&moreBytesToEnd, 2);

    emb_fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        short b1, b2;
        stitchType = NORMAL;
        b1 = (unsigned char)fgetc(file);
        b2 = (unsigned char)fgetc(file);
        if (b1 == -128) {
            unsigned char bCode = (unsigned char)fgetc(file);
            if (fread(&b1, 2, 1, file) != 1) {
                puts("ERROR");
                return 0;
            }
            if (fread(&b2, 2, 1, file) != 1) {
                puts("ERROR");
                return 0;
            }
            /* Embird uses 0x02 and Wilcom uses 0xE1 */
            if (bCode == 0x02 || bCode == 0xE1) {
                stitchType = STOP;
            } else if (bCode == 3) {
                stitchType = TRIM;
            } else if (bCode == 0x7E) {
                emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            }
        }
        emb_pattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }
    return 1;
}

#undef READ_BYTES

char
writeBro(EmbPattern* pattern, void* file)
{
    puts("writeBro is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeBro */
}

/* The Melco Embroidery Format (.cnd)
 *
 * The Melco cnd format is a stitch-only format.
 *
 * We don't know much about this format.
 *
 * \todo Find a source.
 */
char
readCnd(EmbPattern* pattern, void* file)
{
    puts("readCnd is not implemented");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readCnd */
}

char
writeCnd(EmbPattern* pattern, void* file)
{
    puts("writeCnd is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeCnd */
}

/* The Embroidery Thread Color Format (.col)
 *
 * An external color file format for formats that do not record
 * their own colors.
 *
 * It is a human-readable format that has a header that is
 * a single line containing only the number of threads in decimal
 * followed by the windows line break  `\textbackslash{}r\textbackslash{}n}.
 *
 * Then the rest of the file is a comma seperated value list of
 * all threads with 4 values per line: the index of the thread
 * then the red, green and blue channels of the color in that order.
 *
 * \subsubsection col-example Example
 *
 * If we had a pattern called "example" with four colors:
 * black, red, magenta and cyan in that order then the file is
 * (with the white space written out):
 *
 *    example.col
 *
 *    4\r\n
 *    0,0,0,0\r\n
 *    1,255,0,0\r\n
 *    2,0,255,0\r\n
 *    3,0,0,255\r\n
 */
char
readCol(EmbPattern* pattern, void* file)
{
    int numberOfColors, i;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    pattern->thread_list->count = 0;

    emb_readline(file, line, 30);
    numberOfColors = atoi(line);
    if (numberOfColors < 1) {
        printf("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < numberOfColors; i++) {
        emb_readline(file, line, 30);
        if (string_len(line) < 1) {
            printf("ERROR: Empty line in col file.");
            return 0;
        }
        /* TODO: replace all scanf code */
        if (sscanf(line,"%d,%d,%d,%d", &num, &blue, &green, &red) != 4) {
            break;
        }
        t.color.r = (unsigned char)red;
        t.color.g = (unsigned char)green;
        t.color.b = (unsigned char)blue;
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        emb_pattern_addThread(pattern, t);
    }
    return 1;
}

char
writeCol(EmbPattern* pattern, void* file)
{
    int i;

    fprintf(file, "%d\r\n", pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c;
        c = pattern->thread_list->thread[i].color;
        fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
    }
    return 1;
}

/* The Singer Embroidery Format (.csd)
 *
 * Stitch Only Format.
 */
#define CsdSubMaskSize  479
#define CsdXorMaskSize  501

char _subMask[CsdSubMaskSize];
char _xorMask[CsdXorMaskSize];

const unsigned char csd_decryptArray[] = {
    0x43, 0x6E, 0x72, 0x7A, 0x76, 0x6C, 0x61, 0x6F, 0x7C, 0x29, 0x5D, 0x62, 0x60, 0x6E, 0x61, 0x62,
    0x20, 0x41, 0x66, 0x6A, 0x3A, 0x35, 0x5A, 0x63, 0x7C, 0x37, 0x3A, 0x2A, 0x25, 0x24, 0x2A, 0x33,
    0x00, 0x10, 0x14, 0x03, 0x72, 0x4C, 0x48, 0x42, 0x08, 0x7A, 0x5E, 0x0B, 0x6F, 0x45, 0x47, 0x5F,
    0x40, 0x54, 0x5C, 0x57, 0x55, 0x59, 0x53, 0x3A, 0x32, 0x6F, 0x53, 0x54, 0x50, 0x5C, 0x4A, 0x56,
    0x2F, 0x2F, 0x62, 0x2C, 0x22, 0x65, 0x25, 0x28, 0x38, 0x30, 0x38, 0x22, 0x2B, 0x25, 0x3A, 0x6F,
    0x27, 0x38, 0x3E, 0x3F, 0x74, 0x37, 0x33, 0x77, 0x2E, 0x30, 0x3D, 0x34, 0x2E, 0x32, 0x2B, 0x2C,
    0x0C, 0x18, 0x42, 0x13, 0x16, 0x0A, 0x15, 0x02, 0x0B, 0x1C, 0x1E, 0x0E, 0x08, 0x60, 0x64, 0x0D,
    0x09, 0x51, 0x25, 0x1A, 0x18, 0x16, 0x19, 0x1A, 0x58, 0x10, 0x14, 0x5B, 0x08, 0x15, 0x1B, 0x5F,
    0xD5, 0xD2, 0xAE, 0xA3, 0xC1, 0xF0, 0xF4, 0xE8, 0xF8, 0xEC, 0xA6, 0xAB, 0xCD, 0xF8, 0xFD, 0xFB,
    0xE2, 0xF0, 0xFE, 0xFA, 0xF5, 0xB5, 0xF7, 0xF9, 0xFC, 0xB9, 0xF5, 0xEF, 0xF4, 0xF8, 0xEC, 0xBF,
    0xC3, 0xCE, 0xD7, 0xCD, 0xD0, 0xD7, 0xCF, 0xC2, 0xDB, 0xA4, 0xA0, 0xB0, 0xAF, 0xBE, 0x98, 0xE2,
    0xC2, 0x91, 0xE5, 0xDC, 0xDA, 0xD2, 0x96, 0xC4, 0x98, 0xF8, 0xC9, 0xD2, 0xDD, 0xD3, 0x9E, 0xDE,
    0xAE, 0xA5, 0xE2, 0x8C, 0xB6, 0xAC, 0xA3, 0xA9, 0xBC, 0xA8, 0xA6, 0xEB, 0x8B, 0xBF, 0xA1, 0xAC,
    0xB5, 0xA3, 0xBB, 0xB6, 0xA7, 0xD8, 0xDC, 0x9A, 0xAA, 0xF9, 0x82, 0xFB, 0x9D, 0xB9, 0xAB, 0xB3,
    0x94, 0xC1, 0xA0, 0x8C, 0x8B, 0x8E, 0x95, 0x8F, 0x87, 0x99, 0xE7, 0xE1, 0xA3, 0x83, 0x8B, 0xCF,
    0xA3, 0x85, 0x9D, 0x83, 0xD4, 0xB7, 0x83, 0x84, 0x91, 0x97, 0x9F, 0x88, 0x8F, 0xDD, 0xAD, 0x90
};


void
BuildDecryptionTable(int seed) {
    int i;
    const int mul1 = 0x41C64E6D;
    const int add1 = 0x3039;

    for (i = 0; i < CsdSubMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _subMask[i] = (char) ((seed >> 16) & 0xFF);
    }
    for (i = 0; i < CsdXorMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _xorMask[i] = (char) ((seed >> 16) & 0xFF);
    }
}

unsigned char DecodeCsdByte(long fileOffset,
        unsigned char val, int type) {
    int newOffset;

    fileOffset = fileOffset - 1;
    if (type != 0) {
        int final;
        int fileOffsetHigh = (int) (fileOffset & 0xFFFFFF00);
        int fileOffsetLow = (int) (fileOffset & 0xFF);

        newOffset = fileOffsetLow;
        fileOffsetLow = fileOffsetHigh;
        final = fileOffsetLow%0x300;
        if (final != 0x100 && final != 0x200) {
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        } else if (final != 0x100 && final == 0x200) {
            if (newOffset == 0) {
                fileOffsetHigh = fileOffsetHigh - 0x100;
            }
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        } else if (newOffset != 1 && newOffset != 0) {
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        } else {
            fileOffsetHigh = fileOffsetHigh - 0x100;
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        }
    } else {
        newOffset = (int) fileOffset;
    }
    return ((unsigned char) ((unsigned char)
        (val ^ _xorMask[newOffset%CsdXorMaskSize]) -
            _subMask[newOffset%CsdSubMaskSize]));
}

char
readCsd(EmbPattern* pattern, void* file) {
    int i, type = 0;
    unsigned char identifier[8];
    unsigned char unknown1, unknown2;
    char dx = 0, dy = 0;
    int colorChange = -1;
    int flags;
    unsigned char colorOrder[14];

    if (fread(identifier, 1, 8, file) != 8) {
        puts("ERROR");
        return 0;
    }
    /* TODO: check return value */

    if (identifier[0] != 0x7C && identifier[2] != 0xC3) {
        type = 1;
    }
    if (type == 0) {
        BuildDecryptionTable(0xC);
    } else {
        BuildDecryptionTable(identifier[0]);
    }

    for (i = 0; i < 16; i++) {
        EmbThread thread;
        thread.color.r = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        thread.color.g = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        thread.color.b = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        string_copy(thread.catalogNumber, "");
        string_copy(thread.description, "");
        emb_pattern_addThread(pattern, thread);
    }
    unknown1 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    unknown2 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    if (emb_verbose>1) {
        printf("unknown bytes to decode: %c %c", unknown1, unknown2);
    }

    for (i = 0; i < 14; i++) {
        colorOrder[i] = (unsigned char) DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    }
    for (i = 0; !feof(file); i++) {
        char negativeX, negativeY;
        unsigned char b0 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        unsigned char b1 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        unsigned char b2 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);

        if (b0 == 0xF8 || b0 == 0x87 || b0 == 0x91) {
            break;
        }
        negativeX = ((b0 & 0x20) > 0);
        negativeY = ((b0 & 0x40) > 0);
        b0 = (unsigned char)(b0 & (0xFF ^ 0xE0));

        if ((b0 & 0x1F) == 0) {
            flags = NORMAL;
        } else if ((b0 & 0x0C) > 0) {
            flags = STOP;
            if (colorChange >= 14) {
                printf("Invalid color change detected\n");
            }
            emb_pattern_changeColor(pattern, colorOrder[colorChange  % 14]);
            colorChange += 1;
        } else if ((b0 & 0x1F) > 0) {
            flags = TRIM;
        } else {
            flags = NORMAL;
        }
        dx = (char) b2;
        dy = (char) b1;
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        if (flags == STOP) {
            emb_pattern_addStitchRel(pattern, 0, 0, flags, 1);
        } else {
            emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
    }
    return 1;
}

char
writeCsd(EmbPattern* pattern, void* file) {
    puts("writeCsd is not implemented.");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeCsd */
}

/* Comma Separated Values (.csv)
 *
 * Comma Seperated Values files aren't a universal system, here we aim to
 * offer a broad support. The dialect is detected based on the opening lines,
 * as each manufacturer should label their CSV files there.
 *
 * \subsubsection emb-2-csv-dialect Embroidermodder 2.0 CSV Dialect
 *
 * Our own version has the identifier comment line:
 *
 * | Control Symbol | Type | Description |
 * |---|---|
 * | `#` | `COMMENT` | |
 * | `>` | `VARIABLE` | To store records of a pattern's width, height etc. This means that data stored in the header of say a .dst file is preserved. |
 * | `$` | `THREAD` | |
 * | `*` | `STITCH` | |
 * | `*` | `JUMP` | |
 * | `*` | `COLOR` | To change a color: used for trim as well |
 * | `*` | `END` | To end a pattern. |
 * | `*` | `UNKNOWN` | For any feature that we can't identify.
 *
 * ## EmBird CSV Dialect
 *
 */

char* csvStitchFlagToStr(int flags)
{
    switch (flags) {
    case NORMAL:
        return "STITCH";
        break;
    case JUMP:
        return "JUMP";
        break;
    case TRIM:
        return "TRIM";
        break;
    case STOP:
        return "COLOR";
        break;
    case END:
        return "END";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

int csvStrToStitchFlag(const char* str)
{
    if (!str) {
        printf("ERROR: format-csv.c csvStrToStitchFlag(), str argument is null\n");
        return -1;
    }
    if (string_equals(str, "STITCH")) {
        return NORMAL;
    } else if (string_equals(str, "JUMP")) {
        return JUMP;
    } else if (string_equals(str, "TRIM")) {
        return TRIM;
    } else if (string_equals(str, "COLOR")) {
        return STOP;
    } else if (string_equals(str, "END")) {
        return END;
    } else if (string_equals(str, "UNKNOWN")) {
        return STOP;
    }
    return -1;
}

char
readCsv(EmbPattern* pattern, void* file) {
    int numColorChanges = 0;
    int pos = 0;
    int c = 0;
    int cellNum = 0;
    int process = 0;
    int csvMode = CSV_MODE_NULL;
    int expect = CSV_EXPECT_QUOTE1;
    int flags = 0;
    EmbReal xx = 0.0;
    EmbReal yy = 0.0;
    unsigned char r = 0, g = 0, b = 0;
    EmbString buff;

    pos = 0;
    while (!feof(file)) {
        c = fgetc(file);
        switch(c) {
            case '"':
                if (expect == CSV_EXPECT_QUOTE1) {
                    expect = CSV_EXPECT_QUOTE2;
                } else if (expect == CSV_EXPECT_QUOTE2) {
                    expect = CSV_EXPECT_COMMA;
                }
                break;
            case ',':
                if (expect == CSV_EXPECT_COMMA) {
                    process = 1;
                }
                break;
            case '\n':
                if (expect == CSV_EXPECT_COMMA) {
                    process = 1;
                } else if (expect == CSV_EXPECT_QUOTE1) {
                        /* Do Nothing. We encountered a blank line. */
                } else {
                    printf("ERROR: format-csv.c readCsv(), premature newline\n");
                    return 0;
                }
                break;
            default:
                break;
        }

        if (process) {
            buff[pos] = 0;
            pos = 0;
            process = 0;
            cellNum++;
            expect = CSV_EXPECT_QUOTE1;
                if (csvMode == CSV_MODE_NULL) {
                    if     (string_equals(buff, "#")) {
                        csvMode = CSV_MODE_COMMENT;
                    } else if (string_equals(buff, ">")) {
                        csvMode = CSV_MODE_VARIABLE;
                    } else if (string_equals(buff, "$")) {
                        csvMode = CSV_MODE_THREAD;
                    } else if (string_equals(buff, "*")) {
                        csvMode = CSV_MODE_STITCH;
                    } else {/* TODO: error */
                        return 0;
                    }
                } else if (csvMode == CSV_MODE_COMMENT) {
                    /* Do Nothing */
                } else if (csvMode == CSV_MODE_VARIABLE) {
                    /* Do Nothing */
                } else if (csvMode == CSV_MODE_THREAD) {
                    if (cellNum == 2) {
                        /* Do Nothing. Ignore Thread Number */
                    } else if (cellNum == 3) {
                        r = (unsigned char)atoi(buff);
                    } else if (cellNum == 4) {
                        g = (unsigned char)atoi(buff);
                    } else if (cellNum == 5) {
                        b = (unsigned char)atoi(buff);
                    } else if (cellNum == 6) {
                        /* TODO: Thread Description */
                    } else if (cellNum == 7) {
                        /* TODO: Thread Catalog Number */
                        EmbThread t;
                        t.color.r = r;
                        t.color.g = g;
                        t.color.b = b;
                        string_copy(t.description, "TODO:DESCRIPTION");
                        string_copy(t.catalogNumber, "TODO:CATALOG_NUMBER");
                        emb_pattern_addThread(pattern, t);
                        csvMode = CSV_MODE_NULL;
                        cellNum = 0;
                    } else {
                        /* TODO: error */
                        return 0;
                    }
                } else if (csvMode == CSV_MODE_STITCH) {
                    /* printf("%s\n", buff); */
                    if (cellNum == 2) {
                        flags = csvStrToStitchFlag(buff);
                        if (flags == STOP) {
                            numColorChanges++;
                        }
                    } else if (cellNum == 3) {
                        xx = atof(buff);
                    } else if (cellNum == 4) {
                        yy = atof(buff);
                        /* printf("%d %d %f %f\n",
                            pattern->stitch_list->count, flags, xx, yy); */
                        emb_pattern_addStitchAbs(pattern, xx, yy, flags, 1);
                        csvMode = CSV_MODE_NULL;
                        cellNum = 0;
                    } else {
                        /* TODO: error */
                        return 0;
                    }
                }
                if (c == '\n') {
                    csvMode = CSV_MODE_NULL;
                    cellNum = 0;
                }
            } else {
                if (expect == CSV_EXPECT_QUOTE2 && c != '"') {
                    buff[pos++] = (char)c;
                }
            }
    }

    return 1;
}

char
writeCsv(EmbPattern* pattern, void* file)
{
    EmbRect boundingRect;
    int i;

    boundingRect = emb_pattern_calcBoundingBox(pattern);

    fprintf(file, "\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n");
    fprintf(file, "\"#\",\"http://embroidermodder.github.io\"\n");
    fprintf(file, "\"#\",\" \"\n");
    fprintf(file, "\"#\",\"General Notes:\"\n");
    fprintf(file, "\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with # are comments.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n");
    fprintf(file, "\"#\",\" \"\n");
    fprintf(file, "\"#\",\"Stitch Entry Notes:\"\n");
    fprintf(file, "\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n");
    fprintf(file, "\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n");
    fprintf(file, "\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n");
    fprintf(file, "\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n");
    fprintf(file, "\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n");
    fprintf(file, "\"#\",\" \"\n");

    /* write variables */
    fprintf(file,"\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
    fprintf(file, "\">\",\"STITCH_COUNT:\",\"%u\"\n", (unsigned int)pattern->stitch_list->count);
    fprintf(file, "\">\",\"THREAD_COUNT:\",\"%u\"\n", (unsigned int)pattern->thread_list->count);
    fprintf(file, "\">\",\"EXTENTS_LEFT:\",\"%f\"\n",   boundingRect.left);
    fprintf(file, "\">\",\"EXTENTS_TOP:\",\"%f\"\n",    boundingRect.top);
    fprintf(file, "\">\",\"EXTENTS_RIGHT:\",\"%f\"\n",  boundingRect.right);
    fprintf(file, "\">\",\"EXTENTS_BOTTOM:\",\"%f\"\n", boundingRect.bottom);
    fprintf(file, "\">\",\"EXTENTS_WIDTH:\",\"%f\"\n",  boundingRect.right - boundingRect.left);
    fprintf(file, "\">\",\"EXTENTS_HEIGHT:\",\"%f\"\n", boundingRect.bottom - boundingRect.top);
    fprintf(file,"\n");

    /* write colors */
    fprintf(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",");
    fprintf(file, "\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n");

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbThread thr = pattern->thread_list->thread[i];
        /* TODO: fix segfault that backtraces here when
            libembroidery-convert from dst to csv. */
        fprintf(file, "\"$\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n",
            i+1,
            (int)thr.color.r,
            (int)thr.color.g,
            (int)thr.color.b,
            thr.description,
            thr.catalogNumber);
    }
    fprintf(file, "\n");

    /* write stitches */
    fprintf(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n");
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
        fprintf(file, "\"*\",\"%s\",\"%f\",\"%f\"\n",
            csvStitchFlagToStr(s.flags), s.x, s.y);
    }
    return 1;
}

/* The Barudan Embroidery Format (.dat)
 *
 * Stitch Only Format.
 */
char
readDat(EmbPattern* pattern, void* file)
{
    unsigned char b0;
    int fileLength, stitchesRemaining, b1, b2, stitchType;

    emb_fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    if (fileLength < 0x100) {
        puts("ERROR: dat file too short to contain header.");
        return 0;
    }
    emb_fseek(file, 0x02, SEEK_SET);
    stitchesRemaining = fread_uint16(file);
    if (emb_verbose>1) {
        printf("stitchesRemaining: %d", stitchesRemaining);
    }
    emb_fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        b1 = (int)fgetc(file);
        b2 = (int)fgetc(file);
        b0 = fgetc(file);

        stitchType = NORMAL;

        if ((b0 & 0x02) == 0) stitchType = TRIM;

        if (b0 == 0x87) {
            stitchType = STOP;
        }
        if (b0 == 0xF8) {
            break;
        }
        if (b1 >= 0x80) {
            b1 = -(b1 & 0x7F);
        }
        if (b2 >= 0x80) {
            b2 = -(b2 & 0x7F);
        }
        emb_pattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1;
}

char
writeDat(EmbPattern* pattern, void* file)
{
    int i;
    fpad(file, 0x00, 0x100);
    for (i=0; i<pattern->stitch_list->count; i++) {
        unsigned char b[3];
        EmbStitch st = pattern->stitch_list->stitch[i];
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        if (st.flags == STOP) {
            b[2] = 0x87;
        }
        if (st.flags == END) {
            b[2] |= 0xF8;
        }
        else {
            if (st.flags != TRIM) {
                b[2] |= 0x02;
            }
        }
        /* TODO: check that this works */
        if (st.x < 0) {
            b[0] = st.x+0xFF;
        }
        if (st.y < 0) {
            b[1] = st.y+0xFF;
        }
        emb_fwrite(b, 3, file);
    }
    return 1; /*TODO: finish writeDat */
}

/* The Melco Embroidery Format (.dem)
 *
 * Stitch Only Format
 */
char
readDem(EmbPattern* pattern, void* file)
{
    puts("readDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    return readDst(pattern, file); /*TODO: finish readDem */
}

char
writeDem(EmbPattern* pattern, void* file)
{
    puts("writeDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    return writeDst(pattern, file); /*TODO: finish writeDem */
}

/* The Barudan Embroidery Format (.dsb)
 *
 * Stitch Only Format.
 * [X] Basic Read Support
 * [o] Basic Write Support
 * [o] Well Tested Read
 * [o] Well Tested Write
 */
char
readDsb(EmbPattern* pattern, void* file)
{
    char header[512+1];
    unsigned char buffer[3];

    if (fread(header, 1, 512, file) != 512) {
        puts("ERROR");
        return 0;
    }

    while (fread(buffer, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        ctrl = buffer[0];
        y = buffer[1];
        x = buffer[2];
        if (ctrl & 0x01) stitchType = TRIM;
        if (ctrl & 0x20) x = -x;
        if (ctrl & 0x40) y = -y;
        /* ctrl & 0x02 - Speed change? */ /* TODO: review this line */
        /* ctrl & 0x04 - Clutch? */       /* TODO: review this line */
        if ((ctrl & 0x05) == 0x05) {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeDsb(EmbPattern* pattern, void* file)
{
    puts("writeDsb is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeDsb */
}

/* format_dst.c
 *
 * .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.

\subsection tajima-dst-format Tajima Embroidery Format (.dst)

Stitch Only Format.
[X] Basic Read Support
[X] Basic Write Support
[ ] Well Tested Read
[ ] Well Tested Write

.DST (Tajima) embroidery file read/write routines
Format comments are thanks to [tspilman@dalcoathletic.com](tspilman@dalcoathletic.com) who's
notes appeared at [http://www.wotsit.org](http://www.wotsit.org) under Tajima Format.

Other references: \cite kde_tajima , \cite acatina .

## Header

The header contains general information about the design. It is in lines of ASCII, so if you open a DST file as a text file, it's the only part that's easy to read. The line ending symbol is  `0x0D}. The header is necessary for the file to be read by most softwares and hardwares.

The header is 125 bytes of data followed by padding spaces to make it 512 bytes in total.

The lines are as follows.

| *Label* | *Size* | *Description* | *Example* |
|----|----|----|----|
| `LA:` | 17 | The design name with no path or extension. The space reserved is 16 characters, but the name must not be longer than 8 and be padded to 16 with spaces (0x20). | `"LA:Star            "` |
| `ST:` | 8 | The stitch count. An integer in the format `%07d`, that is: a 7 digit number padded by leading zeros. This is the total accross all possible stitch flags. | |
| `CO:` | 4 | The number of color changes (not to be confused with thread count, an all black design we would have the record \textbf{000}). An integer in the format  `%03d`, that is: a 3 digit number padded by leading zeros. | |
| `+X:` | 6 | The extent of the pattern in the postitive x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit number padded by leading zeros. | |
| `-X:` | 6 | The extent of the pattern in the negative x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `+Y:` | 6 | The extent of the pattern in the postitive y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `-Y:` | 6 | The extent of the pattern in the negative y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `AX:` | 7 | The difference of the end from the start in the x direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `AY:` | 7 | The difference of the end from the start in the y direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `MX:` | 7 | The x co-ordinate of the last point in the previous file should the design span multiple files. Like AX, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
| `MY:` | 7 | The y co-ordinate of the last point in the previous file should the design span multiple files. Like AY, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
| `PD:` | 10 | Information about multivolume designs. | |

\subsubsection dst-stitch-data Stitch Data

Uses 3 byte per stitch encoding with the format as follows:

| *Bit* | *7* | *6* | *5* | *4* | *3* | *2* | *1* | *0* |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|
| Byte 0 | y+1 | y-1 | y+9 | y-9 | x-9 | x+9 | x-1 | x+1 |
| Byte 1 | y+3 | y-3 | y+27 | y-27 | x-27 | x+27 | x-3 | x+3 |
| Byte 2 | jump | color change | y+81 | y-81 | x-81 | x+81 | set | set |

T01 and Tap appear to use Tajima Ternary.

Where the stitch type is determined as:

* Normal Stitch `0b00000011 0x03`
* Jump Stitch `0b10000011 0x83`
* Stop/Change Color `0b11000011 0xC3`
* End Design `0b11110011 0xF3`

Inclusive or'ed with the last byte.

Note that the max stitch length is the largest sum of $1+3+9+27+81=121$ where the unit length is 0.1mm so 12.1mm. The coordinate system is right handed.
 *
 */

int
decode_record_flags(unsigned char b2)
{
    if (b2 == 0xF3) {
        return END;
    }
    if (b2 & 0x40) {
        return STOP;
    }
    if (b2 & 0x80) {
        return JUMP;
    }
    return NORMAL;
}

/* TODO: review this then remove since emb-pattern.c has a similar function */
/*
void
combineJumpStitches(EmbPattern* p, int jumpsPerTrim)
{
    if (!p) { printf("ERROR: format-dst.c combineJumpStitches(), p argument is null\n"); return; }
    Embstitch_list* pointer = p->stitch_list;
    int jumpCount = 0;
    Embstitch_list* jumpListStart = 0;
    char needleDown = 0;
    while (pointer) {
        if ((pointer->stitch.flags & JUMP) && !(pointer->stitch.flags & STOP)) {
            if (jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
            if (needleDown && jumpCount >= jumpsPerTrim)
            {
                Embstitch_list* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->stitch.flags |= TRIM;
                jumpListStart->next = pointer;

                jumpCount-=2;
                for (; jumpCount > 0; jumpCount--)
                {
                    Embstitch_list* tempPointer = removePointer->next;
                    jumpListStart->stitch.flags |= removePointer->stitch.flags;
                    safe_free(removePointer);
                    removePointer = 0;
                    removePointer = tempPointer;
                }
                jumpCount = 0;
                needleDown = 0;
            }
        }
        else {
            if (pointer->stitch.flags == NORMAL)
            {
                needleDown = 1;
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}
*/

void
encode_record(void* file, int x, int y, int flags)
{
    unsigned char b[3];
    encode_tajima_ternary(b, x, y);

    b[2] |= 0x03;

    if (flags & END) {
        /* 0b10001101 = -13 = 0x8D */
        b[0] = 0;
        b[1] = 0;
        b[2] = 0x8D;
    }

    /* make the variable v configurable for the pattern */
    if (flags & TRIM) {
        int dx, dy, i, v = 5;
        dx = x/v;
        dy = y/v;
        for (i = 1; i < v; i++) {
            encode_record(file, dx, dy, JUMP);
        }
        encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)), JUMP);
        return;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char) (b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char) (b[2] | 0xC3);
    }

    emb_fwrite(b, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1, c2) (c1*256+c2)

void
set_dst_variable(EmbPattern* pattern, char* var, char* val) {
    unsigned int i;
    EmbThread t;
    for (i = 0; i <= (unsigned int)string_len(var); i++) {
        /* uppercase the var */
        if (var[i] >= 'a' && var[i] <= 'z') {
            var[i] += 'A' - 'a';
        }
    }

    /* macro converts 2 characters to 1 int, allows case statement... */
    switch(cci(var[0],var[1])) {
    case cci('L','A'): /* Design Name (LA) */
        /*pattern->set_variable("Design_Name",val); TODO: review this line. */
        break;
    case cci('S','T'): /* Stitch count, 7 digits padded by leading 0's */
    case cci('C','O'): /* Color change count, 3 digits padded by leading 0's */
    case cci('+','X'): /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
    case cci('-','X'):
    case cci('+','Y'):
    case cci('-','Y'):
        /* don't store these variables, they are recalculated at save */
        break;
    case cci('A','X'): /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('A','Y'):
    case cci('M','X'): /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('M','Y'):
        /* store these variables as-is, they will be converted to numbers and back at save; */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('P','D'):
        /* store this string as-is, it will be saved as-is, 6 characters */
        if (string_len(val) != 6) {
            /*pattern->messages.add("Warning: in DST file read,
                PD is not 6 characters, but ",(int)string_len(val)); */
        }
        /*pattern->set_variable(var,val);*/
        break;
        /* Begin extended fields section */
    case cci('A','U'): /* Author string, arbitrary length */
    case cci('C','P'): /* Copyright string, arbitrary length */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
        /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB
            hex values, 2nd&3rd fields optional arbitrary length) */
    case cci('T','C'):
        /* TODO: review these lines below.
        description=split_cell_str(val,2);
        catalog_number=split_cell_str(val,3);
        */
        t.color = embColor_fromHexStr(val);
        string_copy(t.description, "");
        string_copy(t.catalogNumber, "");
        emb_pattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

/*
    * The header seems to contain information about the design.
    * Seems to be ASCII text delimited by 0x0D (carriage returns).
    * This must be in the file for most new software or hardware
    * to consider it a good file! This is much more important
    * than I originally believed. The header is 125 bytes in
    * length and padded out by 0x20 to 512 bytes total.
    * All entries in the header seem to be 2 ASCII characters
    * followed by a colon, then it's value trailed by a carriage return.
    *
    * char LA[16+1];  First is the 'LA' entry, which is the design name with no
    *                 path or extension information. The blank is 16 characters
    *                 in total, but the name must not be longer that 8 characters
    *                 and padded out with 0x20.
    *
    * char ST[7+1];   Next is the stitch count ST, this is a 7 digit number
    *                 padded by leading zeros. This is the total stitch count
    *                 including color changes, jumps, nups, and special records.
    *
    * char CO[3+1];   Next, is CO or colors, a 3 digit number padded by leading
    *                 zeros. This is the number of color change records in the file.
    *
    * char POSX[5+1]; Next is +X or the positive X extent in centimeters, a 5
    *                 digit non-decimal number padded by leading zeros.
    *
    * char NEGX[5+1]; Following is the -X or the negative X extent in millimeters,
    *                 a 5 digit non-decimal number padded by leading zeros.
    *
    * char POSY[5+1]; Again, the +Y extents.
    *
    * char NEGY[5+1]; Again, the -Y extents.
    *
    * char AX[6+1];   AX and AY should express the relative coordinates of the
    * char AY[6+1];   last point from the start point in 0.1 mm. If the start
    *                 and last points are the same, the coordinates are (0,0).
    *
    * char MX[6+1];   MX and MY should express coordinates of the last point of
    * char MY[6+1];   the previous file for a multi-volume design. A multi-
    *                 volume design means a design consisted of two or more files.
    *                 This was used for huge designs that can not be stored in a
    *                 single paper tape roll. It is not used so much (almost
    *                 never) nowadays.
    *
    * char PD[9+1];   PD is also storing some information for multi-volume design.
    */
char
readDst(EmbPattern* pattern, void* file) {
    char var[3];   /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    int i = 0, flags;

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    if (fread(header, 1, 512, file) != 512) {
        puts("ERROR: Failed to read header bytes.");
        return 0;
    }

    /*TODO:It would probably be a good idea to
        validate file before accepting it. */
    /* fill variables from header fields */
    for (i = 0; i < 512; i++) {
        if (header[i] == ':' && i > 1) {
            var[0] = header[i - 2];
            var[1] = header[i - 1];
            var[2] = '\0';
            valpos = i + 1;
            for (i++; i < 512; i++)
            {
                /* don't accept : without CR because there's a bug below: i-valpos must be > 0 which is not the case if the : is before the third character. */
                if (header[i] == 13/*||header[i]==':'*/) { /* 0x0d = carriage return */
                    /* : indicates another variable, CR was missing! */
                    if (header[i] == ':') {
                        i -= 2;
                    }
                    /* TODO: used to be strncpy, make sure this is a safe substitution. */
                    memory_copy(val, &header[valpos], (size_t)(i - valpos));
                    val[i - valpos] = '\0';
                    set_dst_variable(pattern, var, val);
                    break;
                }
            }
        }
    }

    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_record_flags(b[2]);
        if (flags == END) {
            break;
        }
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }

    /* combineJumpStitches(pattern, 5); */
    return 1;
}

char
writeDst(EmbPattern* pattern, void* file)
{
    EmbRect boundingRect;
    int i, ax, ay, mx, my;
    EmbVector pos;
    EmbString pd;

    emb_pattern_correctForMaxStitchLength(pattern, 12.1f, 12.1f);

    /* TODO: make sure that pattern->thread_list->count
     * defaults to 1 in new patterns */
    boundingRect = emb_pattern_calcBoundingBox(pattern);
    /* TODO: review the code below
    if (pattern->get_variable("design_name") != NULL) {
        char *la = stralloccopy(pattern->get_variable("design_name"));
        if (string_len(la)>16) la[16]='\0';

        fprintf(file,"LA:%-16s\x0d",la);
        safe_free(la);
    }
    */
    fprintf(file, "LA:%-16s\x0d", "Untitled");
    fprintf(file, "ST:%7d\x0d", pattern->stitch_list->count);
    /* number of color changes, not number of colors! */
    fprintf(file, "CO:%3d\x0d", pattern->thread_list->count - 1);
    fprintf(file,
        "+X:%5d\x0d"
        "-X:%5d\x0d"
        "+Y:%5d\x0d"
        "-Y:%5d\x0d",
        (int)(boundingRect.right * 10.0),
        (int)(fabs(boundingRect.left) * 10.0),
        (int)(boundingRect.bottom * 10.0),
        (int)(fabs(boundingRect.top) * 10.0));

    ax = ay = mx = my = 0;
    /* TODO: review the code below */
    /*ax=pattern->get_variable_int("ax"); */ /* will return 0 if not defined */
    /*ay=pattern->get_variable_int("ay"); */
    /*mx=pattern->get_variable_int("mx"); */
    /*my=pattern->get_variable_int("my"); */

    /*pd=pattern->get_variable("pd");*/ /* will return null pointer if not defined */
   /* pd = 0;
    if (pd == 0 || string_len(pd) != 6) { */
        /* pd is not valid, so fill in a default consisting of "******" */
        string_copy(pd, "******");
    /*}*/
    fprintf(file,
        "AX:+%5d\x0d"
        "AY:+%5d\x0d"
        "MX:+%5d\x0d"
        "MY:+%5d\x0d"
        "PD:%6s\x0d\x1a",
        ax, ay, mx, my, pd);

    /* pad out header to proper length */
    fpad(file, ' ', 512-125);

    /* write stitches */
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        int dx, dy;
        st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0f * (st.x - pos.x));
        dy = (int)emb_round(10.0f * (st.y - pos.y));
        pos.x += 0.1f * dx;
        pos.y += 0.1f * dy;
        if (emb_verbose > 0) {
            printf("%d %f %f %d %d %f %f %d\n", i, st.x, st.y, dx, dy, pos.x, pos.y, st.flags);
        }
        encode_record(file, dx, dy, st.flags);
    }

    /* Finish file with a terminator character and two zeros to
     * keep the post header part a multiple of three.
     */
    emb_fwrite("\xa1\0\0", 3, file);
    return 1;
}

/* ZSK USA Embroidery Format (.dsz)
 *
 * The ZSK USA dsz format is stitch-only.
 */

char
readDsz(EmbPattern* pattern, void* file)
{
    unsigned char b[3];

    emb_fseek(file, 0x200, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = b[0];
        x = b[1];
        ctrl = b[2];
        if (ctrl & 0x01) {
            stitchType = TRIM;
        }
        if (ctrl & 0x20) {
            y = -y;
        }
        if (ctrl & 0x40) {
            x = -x;
        }
        if (ctrl & 0x0E) {
            /*
            TODO: Add back if head number is added to the library
            int headNumber = (ctrl & 0x0E) >> 1;
            */
            stitchType = STOP;
        }
        if (ctrl & 0x10) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        emb_pattern_addStitchRel(pattern, x  / 10.0f, y  / 10.0f, stitchType, 1);
    }
    return 1;
}

/* WARNING: this is untested.
 * This is based on the readDsz function.
 */
char
writeDsz(EmbPattern* pattern, void* file)
{
    int i;
    EmbVector delta;
    EmbVector start;
    fpad(file, ' ', 200);
    start.x = 0.0;
    start.y = 0.0;
    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbVector pos;
        EmbStitch st;
        unsigned char b[3];
        st = pattern->stitch_list->stitch[i];
        pos.x = st.x;
        pos.y = st.y;
        delta = emb_vector_subtract(pos, start);
        b[2] = 0;
        if (st.flags & TRIM) {
            b[2] |= 0x01;
        }
        if (10.0*delta.x < 0.0) {
            b[2] |= 0x20;
        }
        if (10.0*delta.y < 0.0) {
            b[2] |= 0x40;
        }
        if (st.flags & STOP) {
            b[2] |= 0x0E;
        }
        if (st.flags & END) {
            b[2] |= 0x10;
        }
        b[0] = emb_round(10.0*delta.x);
        b[1] = emb_round(10.0*delta.y);
        emb_fwrite(b, 3, file);
    }
    return 1;
}

/* Drawing Exchange Format (.dxf)
 * Graphics format for drawing files designed and used by AudoDesk for their AutoCAD program. \cite{dxf_reference
 *
 */

void
readLine(void* file, char *str)
{
    int i;
    int past_leading_spaces;

    /* Remove leading spaces. */
    past_leading_spaces = 0;
    for (i=0; i<254; i++) {
        if (feof(file)) {
            str[i] = 0;
            break;
        }
        str[i] = fgetc(file);
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = 0;
            break;
        }
        if (str[i] == ' ') {
            if (!past_leading_spaces) {
                i--;
            }
        }
        else {
            past_leading_spaces = 0;
        }
    }
}

char
readDxf(EmbPattern* pattern, void* file)
{
    EmbString dxfVersion;
    EmbString section;
    EmbString tableName;
    EmbString layerName;
    EmbString entityType;
    /*char layerColorHash[100][8]; */ /* hash <layerName, EmbColor> */

    int eof = 0; /* End Of File */

    EmbString buff;
    EmbVector prev, pos, first;
    EmbReal bulge = 0.0f;
    char firstStitch = 1;
    char bulgeFlag = 0;
    int fileLength = 0;
    first.x = 0.0f;
    first.y = 0.0f;
    pos.x = 0.0f;
    pos.y = 0.0f;
    prev.x = 0.0f;
    prev.y = 0.0f;

    puts("overriding dxf. Unimplemented for now.");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0;

    emb_fseek(file, 0L, SEEK_END);

    fileLength = ftell(file);
    emb_fseek(file, 0L, SEEK_SET);

    while (ftell(file) < fileLength) {
        readLine(file, buff);
        /*printf("%s\n", buff);*/
        if ( (string_equals(buff, "HEADER"))   ||
            (string_equals(buff, "CLASSES"))  ||
            (string_equals(buff, "TABLES"))   ||
            (string_equals(buff, "BLOCKS"))   ||
            (string_equals(buff, "ENTITIES")) ||
            (string_equals(buff, "OBJECTS"))  ||
            (string_equals(buff, "THUMBNAILIMAGE"))) {
            string_copy(section, buff);
            printf("SECTION:%s\n", buff);
        }
        if (string_equals(buff, "ENDSEC")) {
            string_copy(section, "");
            printf("ENDSEC:%s\n", buff);
        }
        if ( (string_equals(buff, "ARC"))        ||
            (string_equals(buff, "CIRCLE"))     ||
            (string_equals(buff, "ELLIPSE"))    ||
            (string_equals(buff, "LINE"))       ||
            (string_equals(buff, "LWPOLYLINE")) ||
            (string_equals(buff, "POINT"))) {
            string_copy(entityType, buff);
        }
        if (string_equals(buff, "EOF")) {
            eof = 1;
        }

        if (string_equals(section, "HEADER")) {
            if (string_equals(buff, "$ACADVER"))
            {
                readLine(file, buff);
                readLine(file, dxfVersion);
                /* TODO: Allow these versions when POLYLINE is handled. */
                if ((string_equals(dxfVersion, DXF_VERSION_R10))
                || (string_equals(dxfVersion, DXF_VERSION_R11))
                || (string_equals(dxfVersion, DXF_VERSION_R12))
                || (string_equals(dxfVersion, DXF_VERSION_R13))) {
                    return 0;
                }
            }
        }
        else if (string_equals(section,"TABLES")) {
            if (string_equals(buff,"ENDTAB")) {
                tableName[0] = 0;
            }

            if (tableName[0] == 0) {
                if (string_equals(buff,"2")) { /* Table Name */
                    readLine(file, tableName);
                }
            }
            else if (string_equals(tableName, "LAYER"))
            {
                /* Common Group Codes for Tables */
                if (string_equals(buff,"5")) /* Handle */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (string_equals(buff,"330")) /* Soft Pointer */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (string_equals(buff,"100")) /* Subclass Marker */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (string_equals(buff,"70")) /* Number of Entries in Table */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equals(buff,"2")) /* Layer Name */
                {
                    readLine(file, layerName);
                }
                else if (string_equals(buff,"62")) /* Color Number */
                {
                    unsigned char colorNum;
                    EmbColor co;

                    readLine(file, buff);
                    colorNum = atoi(buff);

		/* Why is this here twice? */
                    colorNum = atoi(buff);
                    co = embColor_make(_dxfColorTable[colorNum][0], _dxfColorTable[colorNum][1], _dxfColorTable[colorNum][2]);
                    printf("inserting:%s,%d,%d,%d\n", layerName, co.r, co.g, co.b);
                    /* TODO: fix this with a lookup finish this
                    if (embHash_insert(layerColorHash, emb_strdup(layerName), co))
                    {
                         TODO: log error: failed inserting into layerColorHash
                    }
                    */
                    layerName[0] = 0;
                }
            }
        }
        else if (string_equals(section,"ENTITIES")) {
            /* Common Group Codes for Entities */
            if (string_equals(buff, "5")) /* Handle */
            {
                readLine(file, buff);
                continue;
            }
            else if (string_equals(buff, "330")) /* Soft Pointer */
            {
                readLine(file, buff);
                continue;
            }
            else if (string_equals(buff, "100")) /* Subclass Marker */
            {
                readLine(file, buff);
                continue;
            }
            else if (string_equals(buff, "8")) /* Layer Name */
            {
                readLine(file, buff);
                /* emb_pattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (string_equals(entityType,"LWPOLYLINE")) {
                /* The not so important group codes */
                if (string_equals(buff, "90")) /* Vertices */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (string_equals(buff,"70")) /* Polyline Flag */
                {
                    readLine(file, buff);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (string_equals(buff,"40")) /* Starting Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (string_equals(buff,"41")) /* Ending Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (string_equals(buff,"43")) /* Constant Width */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equals(buff,"42")) /* Bulge */
                {
                    readLine(file, buff);
                    bulge = atof(buff);
                    bulgeFlag = 1;
                }
                else if (string_equals(buff,"10")) /* X */
                {
                    readLine(file, buff);
                    pos.x = atof(buff);
                }
                else if (string_equals(buff,"20")) /* Y */
                {
                    readLine(file, buff);
                    pos.y = atof(buff);

                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = pos;
		        /*TODO: error */
		        /*
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            return 0;
                        }
			*/
			return 0;
                        if (firstStitch) {
                            /* emb_pattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        }
                        /* emb_pattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else {
                        /*if (firstStitch) emb_pattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            emb_pattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prev = pos;
                    if (firstStitch) {
                        first = pos;
                        firstStitch = 0;
                    }
                }
                else if (string_equals(buff,"0")) {
                    entityType[0] = 0;
                    firstStitch = 1;
                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = first;
		        /* TODO: error */
                        /*
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            return 0;
                        }
			*/
		        return 0;
                        prev = arc.start;
                        /* emb_pattern_addStitchAbs(pattern, prevX, prevY, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else
                    {
                        /* emb_pattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                }
            } /* end LWPOLYLINE */
        } /* end ENTITIES section */
    } /* end while loop */


    /*
    EmbColor* testColor = 0;
    testColor = embHash_value(layerColorHash, "OMEGA");
    if (!testColor) printf("NULL POINTER!!!!!!!!!!!!!!\n");
    else printf("LAYERCOLOR: %d,%d,%d\n", testColor->r, testColor->g, testColor->b);
    */

    if (!eof) {
        /* NOTE: The EOF item must be present at the end of file to be considered a valid DXF file. */
        printf("ERROR: format-dxf.c readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

char
writeDxf(EmbPattern* pattern, void* file)
{
    puts("ERROR: writeDxf not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeDxf */
}

/* Embird Embroidery Format (.edr)
 * Stitch Only Format
 */

char
readEdr(EmbPattern* pattern, void* file)
{
    /* appears identical to readRgb, so backends to that */
    return readRgb(pattern, file);
}

char
writeEdr(EmbPattern* pattern, void* file)
{
    /* appears identical to writeRgb, so backends to that */
    return writeRgb(pattern, file);
}

/* The Elna Embroidery Format (.emd)
 * Stitch Only Format.
 */

char
emdDecode(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (-~inputByte) - 1;
    }
    return inputByte;
}

char
readEmd(EmbPattern* pattern, void* file) {
    unsigned char b[2];
    unsigned char jemd0[6]; /* TODO: more descriptive name */
    int width, height, colors, length;

    emb_fseek(file, 0, SEEK_END);
    length = ftell(file);
    if (length < 0x30) {
        puts("File invalid: shorter than the header.");
        return 0;
    }
    emb_fseek(file, 0, SEEK_SET);

    if (fread(jemd0, 1, 6, file) != 6) {
        puts("ERROR: Failed to read 6 bytes for jemd0");
        return 0;
    }
    emb_read(file, &width, EMB_INT16_LITTLE);
    emb_read(file, &height, EMB_INT16_LITTLE);
    emb_read(file, &colors, EMB_INT16_LITTLE);

    emb_fseek(file, 0x30, SEEK_SET);

    while (!feof(file)) {
        char dx, dy;
        int flags = NORMAL;
        if (fread(b, 1, 2, file) != 2) {
            puts("ERROR: Failed to read 2 bytes for stitch.");
            return 0;
        }
        
        if (b[0] == 0x80) {
            if (b[1] == 0x2A) {
                emb_pattern_addStitchRel(pattern, 0, 0, STOP, 1);
                continue;
            }
            else if (b[1] == 0x80) {
                if (fread(b, 1, 2, file) != 2) {
                    puts("ERROR: Failed to read 2 bytes for stitch.");
                    return 0;
                }
                flags = TRIM;
            }
            else if (b[1] == 0xFD) {
                emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            }
            else {
                continue;
            }
        }
        dx = emdDecode(b[0]);
        dy = emdDecode(b[1]);
        emb_pattern_addStitchRel(pattern, dx / 10.0f, dy / 10.0f, flags, 1);
    }
    return 1;
}

char
writeEmd(EmbPattern* pattern, void* file) {
    puts("writeEmd not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeEmd */
}

/* Melco Embroidery Format (.exp)
 * Stitch Only Format.
 */

char
expDecode(unsigned char a1)
{
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

char
readExp(EmbPattern* pattern, void* file)
{
    unsigned char b[2];

    while (fread(b, 1, 2, file) == 2) {
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (b[0] == 0x80) {
            if (b[1] == 0x01) {
                if (fread(b, 1, 2, file) != 2) break;
                /* b0=0x00 and b1=0x00, but accept any,
                not worth crashing over. */
                flags = STOP;
            } else if (b[1] == 0x04) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = JUMP;
            } else if (b[1] == 0x80) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                /* b0=0x07 and b1=0x00, but accept any,
                not worth crashing over. */
                flags = TRIM;
            }
        }
        dx = expDecode(b[0]);
        dy = expDecode(b[1]);
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeExp(EmbPattern* pattern, void* file) {
    EmbVector pos;
    int i;

    /* write stitches */
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        char b[4];
        char dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        dx = (char)emb_round(10.0*(st.x - pos.x));
        dy = (char)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        switch (st.flags) {
            case STOP:
                b[0] = (char)(0x80);
                b[1] = 0x01;
                b[2] = 0x00;
                b[3] = 0x00;
                emb_fwrite(b, 4, file);
                break;
            case JUMP:
                b[0] = (char)(0x80);
                b[1] = 0x04;
                b[2] = dx;
                b[3] = dy;
                emb_fwrite(b, 4, file);
                break;
            case TRIM:
                b[0] = (char)(0x80);
                b[1] = (char)(0x80);
                b[2] = 0x07;
                b[3] = 0x00;
                emb_fwrite(b, 4, file);
                break;
            default: /* STITCH */
                b[0] = dx;
                b[1] = dy;
                emb_fwrite(b, 2, file);
                break;
        }
    }
    fprintf(file, "\x1a");
    return 1;
}

/* Eltac Embroidery Format (.exy)
 * Stitch Only Format.
 */

int decode_exy_flags(unsigned char b2)
{
    int returnCode = 0;
    if (b2 == 0xF3) {
        return (END);
    }
    if ((b2 & 0xC3) == 0xC3) {
        return TRIM | STOP;
    }
    if (b2 & 0x80) {
        returnCode |= TRIM;
    }
    if (b2 & 0x40) {
        returnCode |= STOP;
    }
    return returnCode;
}

char
readExy(EmbPattern* pattern, void* file)
{
    unsigned char b[3];

    emb_fseek(file, 0x100, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_exy_flags(b[2]);
        if (flags & END) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }
    return 1;
}

char
writeExy(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeExy */
}

/* Sierra Expanded Embroidery Format (.eys)
 * Stitch Only Format.
 * Smoothie G-Code Embroidery Format (.fxy)?
 */

char
readEys(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readEys */
}

char
writeEys(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeEys */
}

/* Fortron Embroidery Format (.fxy)
 * Stitch Only Format.
 */

char
readFxy(EmbPattern* pattern, void* file)
{
    /* TODO: review for combining code. This line appears
        to be the only difference from the GT format. */
    emb_fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x91) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if ((commandByte & 0x01) == 0x01)
            stitchType = TRIM;
        if ((commandByte & 0x02) == 0x02)
            stitchType = STOP;
        if ((commandByte & 0x20) == 0x20)
            b1 = -b1;
        if ((commandByte & 0x40) == 0x40)
            b2 = -b2;
        emb_pattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeFxy(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeFxy */
}

/*
 * Smoothie G-Code
 *
 * Main Reference:
 *     Machinery's Handbook Guide
 *     A Guide to Tables, Formulas, & More in the 31st Edition
 *     by John Milton Amiss, Franklin D. Jones and Henry Ryffel
 */

char
readGc(EmbPattern* pattern, void* file) {
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readGc */
}

char
writeGc(EmbPattern* pattern, void* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGc */
}

/*
 * Great Notions Embroidery Format (.gnc)
 * Stitch Only Format.
 */

char
readGnc(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readGnc */
}

char
writeGnc(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGnc */
}

/*
 * Gold Thread Embroidery Format (.gt)
 * Stitch Only Format.
 */

char
readGt(EmbPattern* pattern, void* file)
{
    /* TODO: review for combining code. This line appears
        to be the only difference from the FXY format. */
    emb_fseek(file, 0x200, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x91) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if ((commandByte & 0x01) == 0x01) {
            stitchType = TRIM;
        }
        if ((commandByte & 0x02) == 0x02) {
            stitchType = STOP;
        }
        if ((commandByte & 0x20) == 0x20) {
            b1 = -b1;
        }
        if ((commandByte & 0x40) == 0x40) {
            b2 = -b2;
        }
        emb_pattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeGt(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGt */
}

/*
 * \subsection husqvarna-hus-format Husqvarna Viking Embroidery Format (.hus)
 *
 * Stitch Only Format.
 */

int husDecodeStitchType(unsigned char b)
{
    switch(b) {
        case 0x80:
            return NORMAL;
        case 0x81:
            return JUMP;
        case 0x84:
            return STOP;
        case 0x90:
            return END;
        default:
            return NORMAL;
    }
}

unsigned char*
husDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    char* decompressedData = (char*)malloc(sizeof(char)*decompressedContentLength);
    if (!decompressedData) { printf("ERROR: husDecompressData(), cannot allocate memory for decompressedData\n"); return 0; }
    hus_decompress((char*)input, compressedInputLength, decompressedData, &decompressedContentLength);
    return (unsigned char *)decompressedData;
}

unsigned char*
husCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    char* compressedData = (char*)malloc(sizeof(char)*decompressedInputSize*2);
    if (!compressedData) { printf("ERROR: husCompressData(), cannot allocate memory for compressedData\n"); return 0; }
    hus_compress((char*)input, decompressedInputSize, compressedData, compressedSize);
    return (unsigned char *)compressedData;
}

int
husDecodeByte(unsigned char b)
{
    return (char)b;
}

unsigned char
husEncodeByte(EmbReal f)
{
    return (unsigned char)(int)emb_round(f);
}

unsigned char
husEncodeStitchType(int st)
{
    switch(st) {
        case NORMAL:
            return (0x80);
        case JUMP:
        case TRIM:
            return (0x81);
        case STOP:
            return (0x84);
        case END:
            return (0x90);
        default:
            return (0x80);
    }
}

#define READ_RAW_BYTES(ptr, size, file) \
    if (fread(ptr, 1, size, file) != size) { \
        puts("Ran out of bytes before full file read."); \
        return 0; \
    }

char
readHus(EmbPattern* pattern, void* file)
{
    int fileLength;
    int magicCode, numberOfStitches, numberOfColors;
    int positiveXHoopSize, positiveYHoopSize, negativeXHoopSize, negativeYHoopSize;
    int attributeOffset, xOffset, yOffset;
    unsigned char *attributeData, *xData , *yData;
    unsigned char* attributeDataDecompressed = 0;
    unsigned char* xDecompressed = 0;
    unsigned char* yDecompressed = 0;
    unsigned char* stringVal = 0;

    int unknown, i = 0;

    puts("ERROR: Overridden. readHus is not implemented for now.");
    return 0;

    emb_fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    emb_fseek(file, 0x00, SEEK_SET);

    emb_read(file, &magicCode, EMB_INT32_LITTLE);
    emb_read(file, &numberOfStitches, EMB_INT32_LITTLE);
    emb_read(file, &numberOfColors, EMB_INT32_LITTLE);

    /* These should be put in the EmbPattern. */
    emb_read(file, &positiveXHoopSize, EMB_INT16_LITTLE);
    emb_read(file, &positiveYHoopSize, EMB_INT16_LITTLE);
    emb_read(file, &negativeXHoopSize, EMB_INT16_LITTLE);
    emb_read(file, &negativeYHoopSize, EMB_INT16_LITTLE);

    emb_read(file, &attributeOffset, EMB_INT32_LITTLE);
    emb_read(file, &xOffset, EMB_INT32_LITTLE);
    emb_read(file, &yOffset, EMB_INT32_LITTLE);

    stringVal = (unsigned char*)malloc(sizeof(unsigned char)*8);
    if (!stringVal) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n");
        return 0;
    }
    READ_RAW_BYTES(stringVal, 8, file); /* TODO: check return value */

    emb_read(file, &unknown, EMB_INT16_LITTLE);
    for (i = 0; i < numberOfColors; i++) {
        short pos;
        emb_read(file, &pos, EMB_INT16_LITTLE);
        emb_pattern_addThread(pattern, husThreads[pos]);
    }

    attributeData = (unsigned char*)malloc(sizeof(unsigned char)*(xOffset - attributeOffset + 1));
    if (!attributeData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for attributeData\n");
        return 0;
    }
    READ_RAW_BYTES(attributeData, xOffset - attributeOffset, file);
    attributeDataDecompressed = husDecompressData(attributeData, xOffset - attributeOffset, numberOfStitches + 1);

    xData = (unsigned char*)malloc(sizeof(unsigned char)*(yOffset - xOffset + 1));
    if (!xData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for xData\n");
        return 0;
    }
    READ_RAW_BYTES(xData, yOffset - xOffset, file);
    xDecompressed = husDecompressData(xData, yOffset - xOffset, numberOfStitches);

    yData = (unsigned char*)malloc(sizeof(unsigned char)*(fileLength - yOffset + 1));
    if (!yData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for yData\n");
        return 0;
    }
    READ_RAW_BYTES(yData, fileLength - yOffset, file);
    yDecompressed = husDecompressData(yData, fileLength - yOffset, numberOfStitches);

    for (i = 0; i < numberOfStitches; i++) {
        int flag;
        EmbVector v;
        v.x = husDecodeByte(xDecompressed[i]) / 10.0;
        v.y = husDecodeByte(yDecompressed[i]) / 10.0;
        flag = husDecodeStitchType(attributeDataDecompressed[i]);
        emb_pattern_addStitchRel(pattern, v.x, v.y, flag, 1);
    }

    safe_free(stringVal);
    safe_free(xData);
    safe_free(xDecompressed);
    safe_free(yData);
    safe_free(yDecompressed);
    safe_free(attributeData);
    safe_free(attributeDataDecompressed);

    return 1;
}

char
writeHus(EmbPattern* pattern, void* file)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize, xCompressedSize, yCompressedSize, i;
    EmbReal previousX, previousY;
    short right, top, bottom, left;
    unsigned int code, colors, offset1, offset2;
    unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0,
        *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;

    stitchCount = pattern->stitch_list->count;
    /* emb_pattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->thread_list->count;
    patternColor = minColors;
    if (minColors > 24) minColors = 24;
    code = 0x00C8AF5B;
    emb_write(file, &code, EMB_INT32_LITTLE);
    emb_write(file, &stitchCount, EMB_INT32_LITTLE);
    emb_write(file, &minColors, EMB_INT32_LITTLE);

    boundingRect = emb_pattern_calcBoundingBox(pattern);
    right = (short) emb_round(boundingRect.right * 10.0);
    top = (short) -emb_round(boundingRect.top * 10.0);
    left = (short) emb_round(boundingRect.left * 10.0);
    bottom = (short) -emb_round(boundingRect.bottom * 10.0);
    emb_write(file, &right, EMB_INT16_LITTLE);
    emb_write(file, &top, EMB_INT16_LITTLE);
    emb_write(file, &left, EMB_INT16_LITTLE);
    emb_write(file, &bottom, EMB_INT16_LITTLE);

    colors = 0x2A + 2 * minColors;
    emb_write(file, &colors, EMB_INT32_LITTLE);

    xValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!xValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for xValues\n");
        return 0;
    }
    yValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!yValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for yValues\n");
        return 0;
    }
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!attributeValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues\n");
        return 0;
    }

    previousX = 0.0;
    previousY = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        st = pattern->stitch_list->stitch[i];
        xValues[i] = husEncodeByte((st.x - previousX) * 10.0);
        previousX = st.x;
        yValues[i] = husEncodeByte((st.y - previousY) * 10.0);
        previousY = st.y;
        attributeValues[i] = husEncodeStitchType(st.flags);
    }
    attributeCompressed = husCompressData(attributeValues, stitchCount, &attributeSize);
    xCompressed = husCompressData(xValues, stitchCount, &xCompressedSize);
    yCompressed = husCompressData(yValues, stitchCount, &yCompressedSize);
    /* TODO: error if husCompressData returns zero? */

    offset1 = (unsigned int) (0x2A + 2 * patternColor + attributeSize);
    offset2 = (unsigned int) (0x2A + 2 * patternColor + attributeSize + xCompressedSize);
    emb_write(file, &offset1, EMB_INT32_LITTLE);
    emb_write(file, &offset2, EMB_INT32_LITTLE);
    fpad(file, 0, 10);

    for (i = 0; i < patternColor; i++) {
        short color_index = (short)embThread_findNearestThread(pattern->thread_list->thread[i].color, (EmbThread*)husThreads, 29);
        emb_write(file, &color_index, EMB_INT16_LITTLE);
    }

    emb_fwrite(attributeCompressed, attributeSize, file);
    emb_fwrite(xCompressed, xCompressedSize, file);
    emb_fwrite(yCompressed, yCompressedSize, file);

    safe_free(xValues);
    safe_free(xCompressed);
    safe_free(yValues);
    safe_free(yCompressed);
    safe_free(attributeValues);
    safe_free(attributeCompressed);

    return 1;
}
/*
 * \subsection inbro-inb-format Inbro Embroidery Format (.inb)
 * Stitch Only Format.
 */

char
readInb(EmbPattern* pattern, void* file)
{
    /* TODO: determine what this represents */
    unsigned char fileDescription[8], nullVal, bytesUnknown[300];
    int stitchCount, x, y, i, fileLength;
    short width, height, colorCount, unknown3, unknown2,
        nullbyte, left, right, top, bottom, imageWidth, imageHeight;

    emb_fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    emb_fread(fileDescription, 8, file); /* TODO: check return value */
    nullVal = (char)fgetc(file);
    fgetc(file);
    fgetc(file);
    emb_read(file, &stitchCount, EMB_INT32_LITTLE);
    emb_read(file, &width, EMB_INT16_LITTLE);
    emb_read(file, &height, EMB_INT16_LITTLE);
    colorCount = fread_int16(file);
    unknown3 = fread_int16(file);
    unknown2 = fread_int16(file);
    imageWidth = fread_int16(file);
    imageHeight = fread_int16(file);
    emb_fread(bytesUnknown, 300, file); /* TODO: check return value */
    nullbyte = fread_int16(file);
    emb_read(file, &left, EMB_INT16_LITTLE);
    emb_read(file, &right, EMB_INT16_LITTLE);
    emb_read(file, &top, EMB_INT16_LITTLE);
    emb_read(file, &bottom, EMB_INT16_LITTLE);
    if (emb_verbose>1) {
        printf("nullVal:                 %c\n", nullVal);
        printf("colorCount:              %d\n", colorCount);
        printf("Identify the purpose of:\n");
        printf("    unknown3:            %d\n", unknown3);
        printf("    unknown2:            %d\n", unknown2);
        printf("imageWidth:              %d\n", imageWidth);
        printf("imageHeight:             %d\n", imageHeight);
        printf("This should be null:     %d\n", nullbyte);
    }

    emb_fseek(file, 0x2000, SEEK_SET);
    /* Calculate stitch count since header has been seen to be blank */
    stitchCount = (int)((fileLength - 0x2000) / 3);
    for (i = 0; i < stitchCount; i++) {
        unsigned char type;
        int stitch = NORMAL;
        x = (char)fgetc(file);
        y = (char)fgetc(file);
        type = (char)fgetc(file);
        if ((type & 0x40) > 0)
            x = -x;
        if ((type & 0x10) > 0)
            y = -y;
        if ((type & 1) > 0)
            stitch = STOP;
        if ((type & 2) > 0)
            stitch = TRIM;
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1);
    }
    emb_pattern_flipVertical(pattern);

    return 1;
}

char
writeInb(EmbPattern* pattern, void* file)
{
    puts("ERROR: writeInb not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeInb */
}

/*
 * Embroidery Color Format (.inf)
 *
 * Stitch Only Format.
 */

char
readInf(EmbPattern* pattern, void* file)
{
    int nColors, i;
    char colorType[50];
    char colorDescription[50];
    EmbThread t;

    emb_fseek(file, 12, SEEK_CUR);
    emb_read(file, &nColors, EMB_INT32_BIG);

    pattern->thread_list->count = 0;

    for (i = 0; i < nColors; i++) {
        emb_fseek(file, 4, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        emb_pattern_addThread(pattern, t);
        emb_fseek(file, 2, SEEK_CUR);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

char
writeInf(EmbPattern* pattern, void* file)
{
    int i, bytesRemaining;

    binaryWriteUIntBE(file, 0x01);
    binaryWriteUIntBE(file, 0x08);
    /* write place holder offset */
    binaryWriteUIntBE(file, 0x00);
    binaryWriteUIntBE(file, pattern->thread_list->count);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbString buffer;
        unsigned short record_length, record_number, needle_number;
        EmbColor c;
        c = pattern->thread_list->thread[i].color;
        sprintf(buffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
        record_length = 14 + string_len(buffer);
        record_number = i;
        needle_number = i;
        emb_write(file, &record_length, EMB_INT16_BIG);
        emb_write(file, &record_number, EMB_INT16_BIG);
        embColor_write(file, c, 3);
        emb_write(file, &needle_number, EMB_INT16_BIG);
        emb_fwrite("RGB\0", 4, file);
        fprintf(file, "%s", buffer);
        emb_fwrite("\0", 1, file);
    }
    /* It appears that there should be a pad here otherwise it clips into
     * the color description. */
    fpad(file, 0, 8);
    emb_fseek(file, -8, SEEK_END);
    bytesRemaining = ftell(file);
    emb_fseek(file, 8, SEEK_SET);
    binaryWriteUIntBE(file, bytesRemaining);
    return 1;
}

/*
 * Janome Embroidery Format (.jef)
 * Stitch Only Format.
 */

int
jefGetHoopSize(int width, int height)
{
    if (width < 50 && height < 50) {
        return HOOP_50X50;
    }
    if (width < 110 && height < 110) {
        return HOOP_110X110;
    }
    if (width < 140 && height < 200) {
        return HOOP_140X200;
    }
    return ((int) HOOP_110X110);
}

char
jefDecode(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

void
jefSetHoopFromId(EmbPattern* pattern, int hoopCode)
{
    if (!pattern) {
        printf("ERROR: format-jef.c jefSetHoopFromId(), pattern argument is null\n");
        return;
    }
    switch (hoopCode) {
        case HOOP_126X110:
            pattern->hoop_height = 126.0;
            pattern->hoop_width = 110.0;
            break;
        case HOOP_50X50:
            pattern->hoop_height = 50.0;
            pattern->hoop_width = 50.0;
            break;
        case HOOP_110X110:
            pattern->hoop_height = 110.0;
            pattern->hoop_width = 110.0;
            break;
        case HOOP_140X200:
            pattern->hoop_height = 140.0;
            pattern->hoop_width = 200.0;
            break;
        case HOOP_230X200:
            pattern->hoop_height = 230.0;
            pattern->hoop_width = 200.0;
            break;
    }
}

struct hoop_padding
{
    int left;
    int right;
    int top;
    int bottom;
};

void
read_hoop(void *file, struct hoop_padding *hoop, char *label)
{
    if (emb_verbose>1) {
        printf("%s\n", label);
    }
    emb_read(file, &(hoop->left), EMB_INT32_LITTLE);
    emb_read(file, &(hoop->top), EMB_INT32_LITTLE);
    emb_read(file, &(hoop->right), EMB_INT32_LITTLE);
    emb_read(file, &(hoop->bottom), EMB_INT32_LITTLE);
}

char
readJef(EmbPattern* pattern, void* file)
{
    int stitchOffset, formatFlags, numberOfColors, numberOfStitchs;
    int hoopSize, i, stitchCount;
    struct hoop_padding bounds, rectFrom110x110;
    struct hoop_padding rectFrom50x50, rectFrom200x140, rect_from_custom;
    EmbString date;
    EmbString time;

    emb_read(file, &stitchOffset, EMB_INT32_LITTLE);
    emb_read(file, &formatFlags, EMB_INT32_LITTLE); /* TODO: find out what this means */

    emb_fread((unsigned char*)date, 8, file); /* TODO: check return value */
    emb_fread((unsigned char*)time, 8, file); /* TODO: check return value */
    emb_read(file, &numberOfColors, EMB_INT32_LITTLE);
    emb_read(file, &numberOfStitchs, EMB_INT32_LITTLE);
    emb_read(file, &hoopSize, EMB_INT32_LITTLE);
    jefSetHoopFromId(pattern, hoopSize);
    if (numberOfStitchs > MAX_STITCHES) {
        numberOfStitchs = MAX_STITCHES;
        puts("ERROR: this file is corrupted or has too many stitches.");
        return 0;
    }
    if (emb_verbose>1) {
        printf("format flags = %d\n", formatFlags);
        printf("number of colors = %d\n", numberOfColors);
        printf("number of stitches = %d\n", numberOfStitchs);
    }

    read_hoop(file, &bounds, "bounds");
    read_hoop(file, &rectFrom110x110, "rectFrom110x110");
    read_hoop(file, &rectFrom50x50, "rectFrom50x50");
    read_hoop(file, &rectFrom200x140, "rectFrom200x140");
    read_hoop(file, &rect_from_custom, "rect_from_custom");

    for (i = 0; i < numberOfColors; i++) {
        int thread_num;
        emb_read(file, &thread_num, EMB_INT32_LITTLE);
        emb_pattern_addThread(pattern, jefThreads[thread_num % 79]);
    }
    emb_fseek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while (stitchCount < numberOfStitchs + 100) {
        unsigned char b[2];
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (fread(b, 1, 2, file) != 2) {
            break;
        }

        if (b[0] == 0x80) {
            if (b[1] & 1) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = STOP;
            }
            else if ((b[1] == 2) || (b[1] == 4) || b[1] == 6) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = TRIM;
            }
            else if (b[1] == 0x10) {
                emb_pattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
                break;
            }
        }
        dx = jefDecode(b[0]);
        dy = jefDecode(b[1]);
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        stitchCount++;
    }
    return 1;
}

void
jefEncode(unsigned char* b, char dx, char dy, int flags) {
    if (!b) {
        printf("ERROR: format-jef.c expEncode(), b argument is null\n");
        return;
    }
    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == END) {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    } else if (flags == TRIM || flags == JUMP) {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

char
writeJef(EmbPattern* pattern, void* file)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbTime time;
    EmbReal width, height;
    int data;
    EmbVector pos;

    emb_pattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->thread_list->count;
    minColors = EMB_MAX(colorlistSize, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    embTime_initNow(&time);

    fprintf(file, "%04d%02d%02d%02d%02d%02d", (int)(time.year + 1900),
            (int)(time.month + 1), (int)(time.day), (int)(time.hour),
            (int)(time.minute), (int)(time.second));
    fpad(file, 0, 2);
    emb_write(file, &(pattern->thread_list->count), EMB_INT32_LITTLE);
    data = pattern->stitch_list->count + EMB_MAX(0, (6 - colorlistSize) * 2) + 1;
    emb_write(file, &data, EMB_INT32_LITTLE);

    boundingRect = emb_pattern_calcBoundingBox(pattern);
    width = boundingRect.right - boundingRect.left;
    height = boundingRect.bottom - boundingRect.top;
    designWidth = (int)(width * 10.0);
    designHeight = (int)(height * 10.0);

    binaryWriteInt(file, jefGetHoopSize(designWidth, designHeight));

    /* Distance from center of Hoop */
    binaryWriteInt(file, (int) (designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (designHeight / 2)); /* bottom */

    /* Distance from default 110 x 110 Hoop */
    if (EMB_MIN(550 - designWidth / 2, 550 - designHeight / 2) >= 0) {
        binaryWriteInt(file, EMB_MAX(-1, 550 - designWidth / 2));  /* left */
        binaryWriteInt(file, EMB_MAX(-1, 550 - designHeight / 2)); /* top */
        binaryWriteInt(file, EMB_MAX(-1, 550 - designWidth / 2));  /* right */
        binaryWriteInt(file, EMB_MAX(-1, 550 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 50 x 50 Hoop */
    if (EMB_MIN(250 - designWidth / 2, 250 - designHeight / 2) >= 0) {
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designWidth / 2));  /* left */
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designHeight / 2)); /* top */
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designWidth / 2));  /* right */
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 140 x 200 Hoop */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* left */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* right */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* bottom */

    /* repeated Distance from default 140 x 200 Hoop */
    /* TODO: Actually should be distance to custom hoop */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* bottom */

    for (i = 0; i < pattern->thread_list->count; i++) {
        int j = embThread_findNearestThread(pattern->thread_list->thread[i].color, (EmbThread *)jefThreads, 79);
        binaryWriteInt(file, j);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        int a = 0x0D;
        binaryWriteInt(file, a);
    }

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[4];
        EmbStitch st;
        char dx, dy;
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        b[3] = 0;
        st = pattern->stitch_list->stitch[i];
        dx = (char)emb_round(10.0*(st.x - pos.x));
        dy = (char)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        jefEncode(b, dx, dy, st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            emb_fwrite(b, 4, file);
        } else {
            emb_fwrite(b, 2, file);
        }
    }
    return 1;
}

/*
\subsection pfaff-ksm-format Pfaff professional Design format (.ksm)

Stitch Only Format.
 */

void
ksmEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        printf("ERROR: format-ksm.c ksmEncode(), b argument is null\n");
        return;
    }
    /* TODO: How to encode JUMP stitches? JUMP must be handled.
    Also check this for the EXP format since it appears to be similar */
    if (flags == TRIM) {
        b[0] = 128;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == STOP) {
        b[0] = 128;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

char
readKsm(EmbPattern* pattern, void* file)
{
    int prevStitchType = NORMAL;
    char b[3];
    emb_fseek(file, 0x200, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int flags = NORMAL;

        if (((prevStitchType & 0x08) == 0x08) && (b[2] & 0x08) == 0x08) {
            flags = STOP;
        } else if ((b[2] & 0x1F) != 0) {
            flags = TRIM;
        }
        prevStitchType = b[2];
        if (b[2] & 0x40) {
            b[1] = -b[1];
        }
        if (b[2] & 0x20) {
            b[0] = -b[0];
        }
        emb_pattern_addStitchRel(pattern, b[1] / 10.0, b[0] / 10.0, flags, 1);
    }
    return 1;
}

char
writeKsm(EmbPattern* pattern, void* file)
{
    EmbVector pos;
    int i;

    fpad(file, 0, 0x200);
    /* write stitches */
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[4];
        char dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        dx = (char)(10.0*(st.x - pos.x));
        dy = (char)(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        ksmEncode(b, dx, dy, st.flags);
        fprintf(file, "%c%c", b[0], b[1]);
    }
    fprintf(file, "\x1a");
    return 1;
}

/* Pfaff Embroidery Format (.max)
 * Stitch Only Format.
 */
const unsigned char max_header[] = {
    0x56,0x43,0x53,0x4D,0xFC,0x03,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
    0xF6,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x05,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x33,0x37,0x38,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4D,0x61,0x64,0x65,0x69,0x72,0x61,0x20,
    0x52,0x61,0x79,0x6F,0x6E,0x20,0x34,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x01,0x38,0x09,0x31,0x33,0x30,0x2F,0x37,0x30,0x35,0x20,0x48,0xFA,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00
};


/* ---------------------------------------------------------------- */
/* format max */

/* Pfaff MAX embroidery file format */

char
readMax(EmbPattern* pattern, void* file)
{
    unsigned char b[8];

    emb_fseek(file, 0xD5, SEEK_SET);
    /* emb_read(file, &stitchCount, EMB_INT32_LITTLE); CHECK IF THIS IS PRESENT */
    /* READ STITCH RECORDS */
    while (fread(b, 1, 8, file) == 8) {
        EmbReal dx, dy;
        int flags;
        flags = NORMAL;
        dx = pfaffDecode(b[0], b[1], b[2]);
        dy = pfaffDecode(b[4], b[5], b[6]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    emb_pattern_flipVertical(pattern);
    return 1;
}

char
writeMax(EmbPattern* pattern, void* file)
{
    int i;
    EmbReal x, y;
    EmbStitch st;

    emb_fwrite(max_header, 0xD5, file);
    for (i = 0; i < pattern->stitch_list->count; i++) {
        st = pattern->stitch_list->stitch[i];
        x = (int)emb_round(st.x * 10.0);
        y = (int)emb_round(st.y * 10.0);
        write_24bit(file, x);
        write_24bit(file, y);
    }
    return 1;
}

/*
\subsection mitsubishi-mit-format Mitsubishi Embroidery Format (.mit)

Stitch Only Format.
 */

char
readMit(EmbPattern* pattern, void* file)
{
    unsigned char data[2];

    while (fread(data, 1, 2, file) == 2) {
        int x = mitDecodeStitch(data[0]);
        int y = mitDecodeStitch(data[1]);
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
    }
    return 1;
}

char
writeMit(EmbPattern* pattern, void* file)
{
    EmbReal xx, yy;
    int i;

    emb_pattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = 0;
    yy = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[2];
        EmbStitch st = pattern->stitch_list->stitch[i];
        b[0] = mitEncodeStitch(st.x - xx);
        b[1] = mitEncodeStitch(st.y - yy);
        xx = st.x;
        yy = st.y;
        emb_fwrite(b, 2, file);
    }
    return 1;
}
/*
\subsection ameco-new-format Ameco Embroidery Format (.new)

Stitch Only Format.
 */

char
readNew(EmbPattern* pattern, void* file)
{
    unsigned int stitchCount;
    unsigned char data[3];

    emb_read(file, &stitchCount, EMB_INT16_LITTLE);
    while (fread(data, 1, 3, file) == 3) {
        int x = decodeNewStitch(data[0]);
        int y = decodeNewStitch(data[1]);
        int flag = NORMAL;
        char val = data[2];
        if (data[2] & 0x40) {
            x = -x;
        }
        if (data[2] & 0x20) {
            y = -y;
        }
        if (data[2] & 0x10) {
            flag = TRIM;
        }
        if (data[2] & 0x01) {
            flag = JUMP;
        }
        if ((val & 0x1E) == 0x02) {
            flag = STOP;
        }
        /* Unknown values, possibly TRIM
        155 = 1001 1011 = 0x9B
        145 = 1001 0001 = 0x91
        */
        /*val = (data[2] & 0x1C);
        if (val != 0 && data[2] != 0x9B && data[2] != 0x91) {
            int z = 1;
        }*/
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1);
    }

    return 1;
}

char
writeNew(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeNew */
}

/*
\subsection melco-ofm-format Melco Embroidery Format (.ofm)

Stitch Only Format.
 */

char*
ofmReadLibrary(void* file)
{
    int stringLength = 0;
    char* libraryName = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    if (!file) { printf("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n"); return 0; }

    emb_fread(leadIn, 3, file); /* TODO: check return value */
    unsigned char a;
    emb_fread(&a, 1, file);
    stringLength = a;
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) { printf("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n"); return 0; }
    emb_fread((unsigned char*)libraryName, stringLength * 2, file); /* TODO: check return value */
    return libraryName;
}

static int
ofmReadClass(void* file)
{
    int len;
    EmbString s;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
        return 0;
    }

    fread_int16(file);
    len = fread_int16(file);

    emb_fread((unsigned char*)s, len, file);
    /* TODO: check return value */
    s[len] = '\0';
    if (string_equals(s, "CExpStitch")) {
        return 0x809C;
    }
    if (string_equals(s, "CColorChange")) {
        return 0xFFFF;
    }
    return 0;
}

void
ofmReadBlockHeader(void* file)
{
    int val[10], i; /* TODO: determine what these represent */
    unsigned char len;
    char* s = 0;
    unsigned short short1;
    short unknown1;
    /* TODO: determine what the unknown variables represent */
    int unknown3, unknown2;
    /* TODO: determine what this represents */

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
        return;
    }

    emb_read(file, &unknown1, EMB_INT16_LITTLE);
    emb_read(file, &unknown2, EMB_INT32_LITTLE);
    emb_read(file, &unknown3, EMB_INT32_LITTLE);

    /* int v = emb_fread(&v, 3, file)?; TODO: review */
    fread_int16(file);
    emb_fseek(file, 1, SEEK_CUR);
    len = (char)fgetc(file);
    s = (char*)malloc(2 * len);
    if (!s) {
        printf("ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s\n");
        return;
    }
    emb_fread((unsigned char *)s, 2 * len, file);
    /* TODO: check return value */
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i=0; i<10; i++) {
        emb_read(file, val+i, EMB_INT32_LITTLE);
    }
    emb_read(file, &short1, EMB_INT16_LITTLE); /*  0 */
}

void
ofmReadColorChange(void* file, EmbPattern* pattern)
{
    if (!file) {
        printf("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n");
        return;
    }
    if (!pattern) {
        printf("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    emb_pattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

void
ofmReadThreads(void* file, EmbPattern* p)
{
    int i, numberOfColors, stringLen, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString = 0;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadThreads(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-ofm.c ofmReadThreads(), p argument is null\n");
        return;
    }

    /* FF FE FF 00 */
    emb_fseek(file, 4, SEEK_CUR);

    numberOfColors = fread_int16(file);

    emb_fseek(file, 4, SEEK_CUR);
    stringLen = fread_int16(file);
    expandedString = (char*)malloc(stringLen);
    if (!expandedString) {
        printf("ERROR: format-ofm.c ofmReadThreads(), unable to allocate memory for expandedString\n");
        return;
    }
    emb_fread((unsigned char*)expandedString, stringLen, file);
    /* TODO: check return value */
    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        char colorNumberText[11], colorName[512];
        int threadLibrary, colorNameLength, colorNumber;
        embColor_read(file, &(thread.color), 4);
        emb_read(file, &threadLibrary, EMB_INT16_LITTLE);
        emb_fseek(file, 2, SEEK_CUR);
        emb_read(file, &colorNumber, EMB_INT32_LITTLE);
        emb_fseek(file, 3, SEEK_CUR);
        colorNameLength = (char)fgetc(file);
        emb_fread(colorName, colorNameLength*2, file);
        /* TODO: check return value */
        emb_fseek(file, 2, SEEK_CUR);
        sprintf(colorNumberText, "%10d", colorNumber);
        string_copy(thread.catalogNumber, colorNumberText);
        string_copy(thread.description, colorName);
        emb_pattern_addThread(p, thread);
    }
    emb_fseek(file, 2, SEEK_CUR);
    primaryLibraryName = ofmReadLibrary(file);
    numberOfLibraries = fread_int16(file);

    if (emb_verbose>1) {
        printf("primary library name: %s\n", primaryLibraryName);
    }

    for (i = 0; i < numberOfLibraries; i++) {
        /*libraries.Add( TODO: review */
        char* libName = ofmReadLibrary(file);
        safe_free(libName);
    }
}

EmbReal ofmDecode(unsigned char b1, unsigned char b2)
{
    EmbReal val = (EmbReal)(short)(b1 << 8 | b2);
    return val;
}

void
ofmReadExpanded(void* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

    if (!file) { printf("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n"); return; }
    if (!p) { printf("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n"); return; }

    ofmReadBlockHeader(file);
    emb_read(file, &numberOfStitches, EMB_INT32_LITTLE);

    for (i = 0; i < numberOfStitches; i++) {
        unsigned char stitch[5];
        emb_fread(stitch, 5, file); /* TODO: check return value */
        if (stitch[0] == 0) {
            emb_pattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? JUMP : NORMAL, 1);
        }
        else if (stitch[0] == 32) {
            emb_pattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? TRIM : NORMAL, 1);
        }
    }
}

char
readOfm(EmbPattern* pattern, void* fileCompound)
{
    int unknownCount, key = 0, classNameLength;
    char* s = 0;
    void *file;
    bcf_file* bcfFile = 0;

    if (emb_verbose>1) {
        puts("Overridden during development.");
        return 0;
    }

    bcfFile = (bcf_file*)malloc(sizeof(bcf_file));
    if (!bcfFile) {
        printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n");
        return 0;
    }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    bcfFile = 0;
    emb_fseek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    emb_fseek(file, 0x110, SEEK_CUR);
    emb_fseek(file, 0x4, SEEK_CUR); /* EMB_INT32_LITTLE */
    classNameLength = fread_int16(file);
    s = (char*)malloc(sizeof(char) * classNameLength);
    if (!s) {
        printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n");
        return 0;
    }
    emb_fread((unsigned char*)s, classNameLength, file); /* TODO: check return value */
    unknownCount = fread_int16(file);
    /* TODO: determine what unknown count represents */
    if (emb_verbose>1) {
        printf("unknownCount = %d\n", unknownCount);
    }

    fread_int16(file);
    key = ofmReadClass(file);
    while (1) {
        if (key == 0xFEFF) {
            break;
        }
        if (key == 0x809C) {
            ofmReadExpanded(file, pattern);
        }
        else {
            ofmReadColorChange(file, pattern);
        }
        key = fread_uint16(file);
        if (key == 0xFFFF) {
            ofmReadClass(file);
        }
    }

    emb_pattern_flip(pattern, 1, 1);

    return 1;
}

char
writeOfm(EmbPattern* pattern, void* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeOfm */
}
/*
\subsection pfaff-pcd-format Pfaff PCD File Format (.pcd)

Stitch Only Format.

The format uses a signed 3 byte-length number type.

See the description here ([5](5)) for the overview of the format.

For an example of the format see ([11](11)).

 */

char
readPcd(EmbPattern* pattern, const char *fileName, void* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    EmbReal dx = 0, dy = 0;
    int st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0;

    version = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    hoopSize = (char)fgetc(file);
    colorCount = fread_uint16(file);
    if (emb_verbose>1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        emb_pattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    st = fread_uint16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }
        flags = NORMAL;
        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcd(EmbPattern* pattern, void* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    emb_fwrite("2\x03", 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    fpad(file, 0, 4*(16-i));
    /* write remaining colors to reach 16 */

    binaryWriteUShort(file, (unsigned short)pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0), (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}

/*
 * Pfaff Embroidery Format (.pcm)
 *
 * The Pfaff pcm format is stitch-only.
 */
char
readPcm(EmbPattern* pattern, void* file)
{
    int i = 0, st;
    EmbReal dx = 0, dy = 0;
    int header_size = 16*2+6;

    if (emb_verbose>1) {
        printf("TODO: check header_size %d\n", header_size);
    }

    emb_fseek(file, 4, SEEK_SET);
    for (i = 0; i < 16; i++) {
        int colorNumber;
        (void)fgetc(file); /* zero */
        colorNumber = fgetc(file);
        emb_pattern_addThread(pattern, pcmThreads[colorNumber]);
    }
    emb_read(file, &st, EMB_INT16_BIG);
    st = EMB_MIN(st, MAX_STITCHES);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        unsigned char b[9];
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }
        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[2], b[1], b[0]);
        dy = pfaffDecode(b[6], b[5], b[4]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcm(EmbPattern* pattern, void* file)
{
    puts("overridden, defaulting to dst");
    writeDst(pattern, file);
    return 0; /*TODO: finish writePcm */
}

/*
 * Pfaff Embroidery Format (.pcq)
 *
 * The Pfaff pcq format is stitch-only.
 */
char
readPcq(EmbPattern* pattern, const char* fileName, void* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    EmbReal dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = (char)fgetc(file);
    hoopSize = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    colorCount = fread_uint16(file);
    if (emb_verbose>1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        emb_pattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    st = fread_uint16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }

        if (b[8] & 0x01) {
            flags = STOP;
        }
        else if (b[8] & 0x04) {
            flags = TRIM;
        }
        else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcq(EmbPattern* pattern, void* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    emb_fwrite("2\x03", 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    fpad(file, 0, (16-i)*4);

    binaryWriteUShort(file, (unsigned short)pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0), (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}

/*
 * Pfaff Embroidery Format (.pcs)
 *
 * The Pfaff pcs format is stitch-only.
 */
char
readPcs(EmbPattern* pattern, const char* fileName, void* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    EmbReal dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = (char)fgetc(file);

    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    hoopSize = (char)fgetc(file);
    switch(hoopSize) {
        case 2:
            pattern->hoop_width = 80.0;
            pattern->hoop_height = 80.0;
            break;
        case 3:
            pattern->hoop_width = 115.0;
            pattern->hoop_height = 120.0;
            break;
    }

    colorCount = fread_uint16(file);
    if (emb_verbose>1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        emb_pattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    st = fread_uint16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01) {
            flags = STOP;
        }
        else if (b[8] & 0x04) {
            flags = TRIM;
        }
        else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

char
writePcs(EmbPattern* pattern, void* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    emb_fwrite("2\x03", 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    /* fpad(file, 0, 4*(16-i)); */

    binaryWriteUShort(file, (unsigned short)pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0), (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}

/*
 * Brother Embroidery Format (.pec)
 * The Brother pec format is stitch-only.
 */
void
readPecStitches(EmbPattern* pattern, void* file)
{
    void *f = file;
    unsigned char b[2];

    while (fread(b, 1, 2, f)==2) {
        int val1 = (int)b[0];
        int val2 = (int)b[1];

        int stitchType = NORMAL;
        if (b[0] == 0xFF && b[1] == 0x00) {
            emb_pattern_end(pattern);
            return;
        }
        if (b[0] == 0xFE && b[1] == 0xB0) {
            (void)fgetc(f);
            emb_pattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
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

        emb_pattern_addStitchRel(pattern, val1 / 10.0,
                val2 / 10.0, stitchType, 1);
    }
}

void
pecEncodeJump(void* file, int x, int types)
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
    emb_fwrite(&toWrite, 1, file);
    toWrite = (unsigned char)(outputVal & 0xFF);
    emb_fwrite(&toWrite, 1, file);
}

void
pecEncodeStop(void* file, unsigned char val)
{
    if (!file) {
        printf("ERROR: format-pec.c pecEncodeStop(), file argument is null\n");
        return;
    }
    emb_fwrite("\xFE\xB0", 2, file);
    emb_fwrite(&val, 1, file);
}

char
readPec(EmbPattern* pattern, const char *fileName, void* file)
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

    emb_fseek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)(char)fgetc(file);
    for (i = 0; i <= colorChanges; i++) {
        emb_pattern_addThread(pattern, pecThreads[(char)fgetc(file) % 65]);
    }

    /* Get Graphics offset */
    emb_fseek(file, 0x20A, SEEK_SET);

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
    emb_pattern_flipVertical(pattern);
    return 1;
}

void
pecEncode(void* file, EmbPattern* p)
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
            emb_fwrite("\xFF", 1, file);
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
            emb_fwrite(out, 2, file);
        }
        else {
            pecEncodeJump(file, deltaX, s.flags);
            pecEncodeJump(file, deltaY, s.flags);
        }
    }
}

void writeImage(void* file, unsigned char image[][48]);

void
writePecStitches(EmbPattern* pattern, void* file, const char *fileName)
{
    EmbRect bounds;
    unsigned char image[38][48], toWrite;
    int i, j, flen, graphicsOffsetLocation;
    int graphicsOffsetValue, height, width;
    EmbReal xFactor, yFactor;
    const char* forwardSlashPos = fileName + string_rchar(fileName, '/');
    const char* backSlashPos = fileName + string_rchar(fileName, '\\');
    const char* dotPos = fileName + string_rchar(fileName, '.');
    const char* start = 0;

    start = fileName;
    if (forwardSlashPos) {
        start = forwardSlashPos + 1;
    }
    if (backSlashPos && backSlashPos > start) {
        start = backSlashPos + 1;
    }
    emb_fwrite("LA:", 3, file);
    flen = (int)(dotPos - start);

    while (start < dotPos) {
        emb_fwrite(start, 1, file);
        start++;
    }
    fpad(file, 0x20, 16-flen);
    emb_fwrite("\x0D", 1, file);
    fpad(file, 0x20, 12);
    emb_fwrite("\xff\x00\x06\x26", 4, file);

    fpad(file, 0x20, 12);
    toWrite = (unsigned char)(pattern->thread_list->count-1);
    emb_fwrite(&toWrite, 1, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor thr = pattern->thread_list->thread[i].color;
        unsigned char color = (unsigned char)
            embThread_findNearestThread(thr,
            (EmbThread*)pecThreads, pecThreadCount);
        emb_fwrite(&color, 1, file);
    }
    fpad(file, 0x20, (int)(0x1CF - pattern->thread_list->count));
    fpad(file, 0x00, 2);

    graphicsOffsetLocation = ftell(file);
    /* placeholder bytes to be overwritten */
    fpad(file, 0x00, 3);

    emb_fwrite("\x31\xff\xf0", 3, file);

    bounds = emb_pattern_calcBoundingBox(pattern);

    height = (int)emb_round(bounds.bottom - bounds.top);
    width = (int)emb_round(bounds.right - bounds.left);
    unsigned short top = (unsigned short)(0x9000 | -(int)emb_round(bounds.left));
    unsigned short bottom = (unsigned short)(0x9000 | -(int)emb_round(bounds.top));
    /* write 2 byte x size */
    emb_write(file, &width, EMB_INT16_LITTLE);
    /* write 2 byte y size */
    emb_write(file, &height, EMB_INT16_LITTLE);

    /* Write 4 miscellaneous int16's */
    emb_fwrite("\x01\xe0\x01\xb0", 4, file);

    /* CHECK: is this really big endian? */
    emb_write(file, &top, EMB_INT16_BIG);
    emb_write(file, &bottom, EMB_INT16_BIG);

    pecEncode(file, pattern);
    graphicsOffsetValue = ftell(file) - graphicsOffsetLocation + 2;
    emb_fseek(file, graphicsOffsetLocation, SEEK_SET);

    fputc((unsigned char)(graphicsOffsetValue & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 8) & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 16) & 0xFF), file);

    emb_fseek(file, 0x00, SEEK_END);

    /* Writing all colors */
    memory_copy(image, imageWithFrame, 48*38);

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
        memory_copy(image, imageWithFrame, 48*38);
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
writePec(EmbPattern* pattern, const char* fileName, void* file)
{
    /* TODO: There needs to be a matching flipVertical() call after the write
        to ensure multiple writes from the same pattern work properly */
    emb_pattern_flipVertical(pattern);
    emb_pattern_fixColorCount(pattern);
    emb_pattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    emb_pattern_scale(pattern, 10.0);
    emb_fwrite("#PEC0001", 8, file);
    writePecStitches(pattern, file, fileName);
    return 1;
}

/*
 * Brother Embroidery Format (.pel)
 * The Brother pel format is stitch-only.
 */

char
readPel(EmbPattern *pattern, void *file)
{
    puts("ERROR: readPel is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish readPel */
}

char
writePel(EmbPattern *pattern, void *file)
{
    puts("ERROR: writePel is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePel */
}

/*
 * Brother Embroidery Format (.pem)
 * The Brother pem format is stitch-only.
 */

char
readPem(EmbPattern *pattern, void *file)
{
    puts("ERROR: readPem is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish ReadPem */
}

char
writePem(EmbPattern *pattern, void *file)
{
    puts("ERROR: writePem is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePem */
}

/*
 * Brother Embroidery Format (.pes)
 * The Brother pes format is stitch-only.
 */

const char *pes_version_strings[] = {
    "#PES0001",
    "#PES0020",
    "#PES0022",
    "#PES0030",
    "#PES0040",
    "#PES0050",
    "#PES0055",
    "#PES0056",
    "#PES0060",
    "#PES0070",
    "#PES0080",
    "#PES0090",
    "#PES0100",
};


/* ---------------------------------------------------------------- */
/* format pes */

int pes_version = PES0001;

char
readPes(EmbPattern* pattern, const char *fileName, void* file)
{
    int pecstart, numColors, x, version, i;
    char signature[9];
    emb_fread(signature, 8, file);
    signature[8] = 0;
    emb_read(file, &pecstart, EMB_INT32_LITTLE);

    version = 0;
    for (i=0; i<N_PES_VERSIONS; i++) {
        if (string_equals(signature, pes_version_strings[i])) {
            version = i;
            break;
        }
    }

    if (version >= PES0040) {
        emb_fseek(file, 4, SEEK_CUR);
        readDescriptions(file, pattern);
    }

    switch (version) {
    case PES0100:
        readPESHeaderV10(file, pattern);
        break;
    case PES0090:
        readPESHeaderV9(file, pattern);
        break;
    case PES0080:
        readPESHeaderV8(file, pattern);
        break;
    case PES0070:
        readPESHeaderV7(file, pattern);
        break;
    case PES0060:
        readPESHeaderV6(file, pattern);
        break;
    case PES0056:
    case PES0055:
    case PES0050:
        readPESHeaderV5(file, pattern);
        break;
    default:
        break;
    }

    if (emb_verbose>1) {
        printf("debug information for reading fileName: %s\n", fileName);
        printf("pecstart = %d\n", pecstart);
    }

    /* emb_fseek(file, pecstart + 48, SEEK_SET);
     * This seems wrong based on the readPESHeader functions. */
    emb_fseek(file, pecstart, SEEK_SET);

    numColors = fgetc(file) + 1;
    for (x = 0; x < numColors; x++) {
        int color_index = fgetc(file);
        if (color_index >= pecThreadCount) {
            color_index = 0;
        }
        emb_pattern_addThread(pattern, pecThreads[color_index]);
    }

    emb_fseek(file, pecstart + 528, SEEK_SET);
    readPecStitches(pattern, file);

    emb_pattern_flipVertical(pattern);

    return 1;
}

void
readDescriptions(void *file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int DesignStringLength;
    int categoryStringLength;
    int authorStringLength;
    int keywordsStringLength;
    int commentsStringLength;
    DesignStringLength = fgetc();
    EmbString DesignName = readString(DesignStringLength);
    pattern.setName(DesignName);
    categoryStringLength = fgetc();
    EmbString Category = readString(categoryStringLength);
    pattern.setCategory(Category);
    authorStringLength = fgetc();
    EmbString Author = readString(authorStringLength);
    pattern.setAuthor(Author);
    keywordsStringLength = fgetc();
    EmbString keywords = readString(keywordsStringLength);
    pattern.setKeywords(keywords);
    commentsStringLength = fgetc();
    EmbString Comments = readString(commentsStringLength);
    pattern.setComments(Comments);
    */
}

void
readPESHeaderV5(void *file, EmbPattern* pattern)
{
    int fromImageStringLength;
    emb_fseek(file, 24, SEEK_CUR);
    fromImageStringLength = fgetc(file);
    emb_fseek(file, fromImageStringLength, SEEK_CUR);
    emb_fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV6(void *file, EmbPattern* pattern)
{
    emb_fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    emb_fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV7(void *file, EmbPattern* pattern)
{
    emb_fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    emb_fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV8(void *file, EmbPattern* pattern)
{
    emb_fseek(file, 38, SEEK_CUR);
    readImageString(file, pattern);
    emb_fseek(file, 26, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV9(void *file, EmbPattern* pattern)
{
    emb_fseek(file, 14, SEEK_CUR);
    readHoopName(file, pattern);
    emb_fseek(file, 30, SEEK_CUR);
    readImageString(file, pattern);
    emb_fseek(file, 34, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV10(void *file, EmbPattern* pattern)
{
    emb_fseek(file, 14, SEEK_CUR);
    readHoopName(file, pattern);
    emb_fseek(file, 38, SEEK_CUR);
    readImageString(file, pattern);
    emb_fseek(file, 34, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readHoopName(void* file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int hoopNameStringLength = fgetc(file);
    EmbString hoopNameString = readString(hoopNameStringLength);
    if (hoopNameString.length() != 0) {
        pattern.setMetadata("hoop_name", hoopNameString);
    }
    */
}

void
readImageString(void* file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int fromImageStringLength = fgetc(file);
    EmbString fromImageString = readString(fromImageStringLength);
    if (fromImageString.length() != 0) {
        pattern.setMetadata("image_file", fromImageString);
    }
    */
}

void
readProgrammableFills(void* file, EmbPattern* pattern)
{
    int numberOfProgrammableFillPatterns;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfProgrammableFillPatterns = fread_int16(file);
    if (numberOfProgrammableFillPatterns != 0) {
        return;
    }
}

void
readMotifPatterns(void* file, EmbPattern* pattern)
{
    int numberOfMotifPatterns;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfMotifPatterns = fread_int16(file);
    if (numberOfMotifPatterns != 0) {
        return;
    }
}

void
readFeatherPatterns(void* file, EmbPattern* pattern)
{
    int featherPatternCount;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    featherPatternCount = fread_int16(file);
    if (featherPatternCount != 0) {
        return;
    }
}

void
readThreads(void* file, EmbPattern* pattern)
{
    int numberOfColors, i;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfColors = fread_int16(file);
    for (i=0; i<numberOfColors; i++) {
        EmbThread thread;
        int color_code_length;
        int descriptionStringLength;
        int brandStringLength;
        int threadChartStringLength;
        color_code_length = fgetc(file);
        /* string_copy(thread.color_code, readString(color_code_length)); */
        thread.color.r = fgetc(file);
        thread.color.g = fgetc(file);
        thread.color.b = fgetc(file);
        emb_fseek(file, 5, SEEK_CUR);
        descriptionStringLength = fgetc(file);
        /* string_copy(thread.description, readString(descriptionStringLength)); */

        brandStringLength = fgetc(file);
        /* string_copy(thread.brand, readString(brandStringLength)); */

        threadChartStringLength = fgetc(file);
        /* string_copy(thread.threadChart, readString(threadChartStringLength)); */

        if (emb_verbose > 1) {
            printf("color code length: %d\n", color_code_length);
            printf("description string length: %d\n", descriptionStringLength);
            printf("brand string length: %d\n", brandStringLength);
            printf("thread chart string length: %d\n", threadChartStringLength);
        }
        emb_pattern_addThread(pattern, thread);
    }
}


void
pesWriteSewSegSection(EmbPattern* pattern, void* file) {
    /* TODO: pointer safety */
    short* colorInfo = 0;
    int flag = 0;
    int count = 0;
    int colorCode = -1;
    int stitchType = 0;
    int blockCount = 0;
    int colorCount = 0;
    int newColorCode = 0;
    int colorInfoIndex = 0;
    int i, j;
    EmbRect bounds = emb_pattern_calcBoundingBox(pattern);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbColor color;
        EmbStitch st = pattern->stitch_list->stitch[i];
        flag = st.flags;
        if (st.color < pattern->thread_list->count) {
            color = pattern->thread_list->thread[st.color].color;
        }
        else {
            color = pecThreads[0].color;
        }
        newColorCode = embThread_findNearestThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
            colorCount++;
            colorCode = newColorCode;
        }
        while (i < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[i];
            count++;
            i++;
        }
        blockCount++;
    }

    binaryWriteShort(file, (short)blockCount); /* block count */
    binaryWriteUShort(file, 0xFFFF);
    binaryWriteShort(file, 0x00);

    binaryWriteShort(file, 0x07); /* string length */
    emb_fwrite("CSewSeg", 7, file);

    if (colorCount > 1000) {
        puts("Color count exceeds 1000 this is likely an error. Truncating to 1000.");
        colorCount = 1000;
    }

    colorInfo = (short *) calloc(colorCount * 2, sizeof(short));
    colorCode = -1;
    blockCount = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbColor color;
        EmbStitch st;
        st = pattern->stitch_list->stitch[i];
        j = i;
        flag = st.flags;
        color = pattern->thread_list->thread[st.color].color;
        newColorCode = embThread_findNearestThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
            if (colorInfoIndex+2 > colorCount) {
                puts("Ran out of memory for color info.");
                break;
            }
            colorInfo[colorInfoIndex++] = (short)blockCount;
            colorInfo[colorInfoIndex++] = (short)newColorCode;
            colorCode = newColorCode;
        }
        count = 0;
        while (j < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[j];
            count++;
            j++;
        }
        if (flag & JUMP) {
            stitchType = 1;
        }
        else {
            stitchType = 0;
        }

        binaryWriteShort(file, (short)stitchType); /* 1 for jump, 0 for normal */
        binaryWriteShort(file, (short)colorCode); /* color code */
        binaryWriteShort(file, (short)count); /* stitches in block */
        j = i;
        while (j < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[j];
            binaryWriteShort(file, (short)(st.x - bounds.left));
            binaryWriteShort(file, (short)(st.y + bounds.top));
        }
        if (j < pattern->stitch_list->count ) {
            binaryWriteUShort(file, 0x8003);
        }
        blockCount++;
        i = j;
    }
    binaryWriteShort(file, (short)colorCount);
    for (i = 0; i < colorCount; i++) {
        binaryWriteShort(file, colorInfo[i * 2]);
        binaryWriteShort(file, colorInfo[i * 2 + 1]);
    }
    binaryWriteInt(file, 0);
    safe_free(colorInfo);
}

void
pesWriteEmbOneSection(EmbPattern* pattern, void* file) {
    /* TODO: pointer safety */
    float x, width, height;
    int hoopHeight = 1800, hoopWidth = 1300;
    EmbRect bounds;
    binaryWriteShort(file, 0x07); /* string length */
    emb_fwrite("CEmbOne", 7, file);
    bounds = emb_pattern_calcBoundingBox(pattern);

    fpad(file, 0, 16);

    /* AffineTransform */
    x = 1.0;
    emb_write(file, &x, EMB_INT32_LITTLE);
    x = 0.0;
    emb_write(file, &x, EMB_INT32_LITTLE);
    x = 0.0;
    emb_write(file, &x, EMB_INT32_LITTLE);
    x = 1.0;
    emb_write(file, &x, EMB_INT32_LITTLE);
    width = bounds.right - bounds.left;
    height = bounds.bottom - bounds.top;
    x = (float)((width - hoopWidth) / 2);
    emb_write(file, &x, EMB_INT32_LITTLE);
    x = (float)((height + hoopHeight) / 2);
    emb_write(file, &x, EMB_INT32_LITTLE);

    binaryWriteShort(file, 1);
    binaryWriteShort(file, 0); /* Translate X */
    binaryWriteShort(file, 0); /* Translate Y */
    binaryWriteShort(file, (short)width);
    binaryWriteShort(file, (short)height);

    fpad(file, 0, 8);
    /*WriteSubObjects(br, pes, SubBlocks); */
}

char
writePes(EmbPattern* pattern,  const char *fileName, void* file)
{
    int pecLocation;
    emb_pattern_flipVertical(pattern);
    emb_pattern_scale(pattern, 10.0);
    emb_fwrite("#PES0001", 8, file);
    /* WRITE PECPointer 32 bit int */
    binaryWriteInt(file, 0x00);

    binaryWriteShort(file, 0x01);
    binaryWriteShort(file, 0x01);

    /* Write object count */
    binaryWriteShort(file, 0x01);
    binaryWriteUShort(file, 0xFFFF); /* command */
    binaryWriteShort(file, 0x00); /* unknown */

    pesWriteEmbOneSection(pattern, file);
    pesWriteSewSegSection(pattern, file);

    pecLocation = ftell(file);
    emb_fseek(file, 0x08, SEEK_SET);
    fputc((unsigned char)(pecLocation & 0xFF), file);
    fputc((unsigned char)(pecLocation >> 8) & 0xFF, file);
    fputc((unsigned char)(pecLocation >> 16) & 0xFF, file);
    emb_fseek(file, 0x00, SEEK_END);
    writePecStitches(pattern, file, fileName);
    return 1;
}

/*
 * Brother Embroidery Format (.phb)
 * The Brother phb format is stitch-only.
 */

char
readPhb(EmbPattern* pattern, void* file)
{
    unsigned int fileOffset, readIn;
    short colorCount;
    int i;

    emb_fseek(file, 0x71, SEEK_SET);
    colorCount = fread_int16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t = pecThreads[fgetc(file)];
        emb_pattern_addThread(pattern, t);
    }

    /* TODO: check that file begins with #PHB */
    emb_fseek(file, 0x54, SEEK_SET);
    fileOffset = 0x52;
    emb_read(file, &readIn, EMB_INT32_LITTLE);
    fileOffset += readIn;

    emb_fseek(file, fileOffset, SEEK_SET);
    emb_read(file, &readIn, EMB_INT32_LITTLE);
    fileOffset += readIn + 2;

    emb_fseek(file, fileOffset, SEEK_SET);
    emb_read(file, &readIn, EMB_INT32_LITTLE);
    fileOffset += readIn;

    emb_fseek(file, fileOffset + 14, SEEK_SET); /* 28 */

    colorCount = (short)(char)fgetc(file);
    for (i = 0; i <  colorCount; i++) {
        char stor;
        stor = (char)fgetc(file);
        if (emb_verbose>1) {
            printf("stor: %d\n", stor);
        }
    }
    emb_fseek(file, 4, SEEK_CUR); /* bytes to end of file */
    emb_fseek(file, 17, SEEK_CUR);

    readPecStitches(pattern, file);

    emb_pattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

char
writePhb(EmbPattern* pattern, void* file)
{
    puts("ERROR: writePhb is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePhb */
}

/*
 * Brother Embroidery Format (.phc)
 * The Brother phc format is stitch-only.
 */

char
readPhc(EmbPattern* pattern, void* file)
{
    int colorChanges, version, bytesInSection2;
    unsigned int fileLength;
    unsigned short pecOffset, bytesInSection, bytesInSection3;
    char pecAdd;
    int i;

    emb_fseek(file, 0x07, SEEK_SET);
    version = (char)fgetc(file) - 0x30; /* converting from ansi number */
    emb_fseek(file, 0x4D, SEEK_SET);
    colorChanges = fread_uint16(file);

    for (i = 0; i < colorChanges; i++) {
        EmbThread t = pecThreads[(int)(char)fgetc(file)];
        emb_pattern_addThread(pattern, t);
    }
    emb_fseek(file, 0x2B, SEEK_SET);
    pecAdd = (char)fgetc(file);
    emb_read(file, &fileLength, EMB_INT32_LITTLE);
    pecOffset = fread_uint16(file);
    emb_fseek(file, pecOffset + pecAdd, SEEK_SET);
    bytesInSection = fread_uint16(file);
    emb_fseek(file, bytesInSection, SEEK_CUR);
    emb_read(file, &bytesInSection2, EMB_INT32_LITTLE);
    emb_fseek(file, bytesInSection2, SEEK_CUR);
    bytesInSection3 = fread_uint16(file);
    emb_fseek(file, bytesInSection3 + 0x12, SEEK_CUR);

    if (emb_verbose>1) {
        printf("version: %d\n", version);
    }

    readPecStitches(pattern, file);

    emb_pattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhc */
}

char
writePhc(EmbPattern* pattern, void* file)
{
    puts("ERROR: writePhc is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePhc */
}

/*
 * AutoCAD Embroidery Format (.plt)
 * The AutoCAD plt format is stitch-only.
 */
char
readPlt(EmbPattern* pattern, void* file)
{
    EmbReal x, y;
    EmbReal scalingFactor = 40;
    char input[512];

    /* TODO: replace all scanf code */
    while (emb_readline(file, input, 511)) {
        if (input[0] == 'P' && input[1] == 'D') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PD%f,%f;", &x, &y) < 2) {
                break;
            }
            emb_pattern_addStitchAbs(pattern, x / scalingFactor,
                            y / scalingFactor, NORMAL, 1);
        } else if (input[0] == 'P' && input[1] == 'U') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PU%f,%f;", &x, &y) < 2) {
                break;
            }
            emb_pattern_addStitchAbs(pattern, x / scalingFactor,
                    y / scalingFactor, STOP, 1);
        }
    }
    return 1;
}

char
writePlt(EmbPattern* pattern, void* file) {
    /* TODO: pointer safety */
    EmbReal scalingFactor = 40;
    char firstStitchOfBlock = 1;
    int i;

    fprintf(file, "IN;");
    fprintf(file, "ND;");

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch stitch;
        stitch = pattern->stitch_list->stitch[i];
        if (stitch.flags & STOP) {
            firstStitchOfBlock = 1;
        }
        if (firstStitchOfBlock) {
            fprintf(file, "PU%f,%f;", stitch.x * scalingFactor,
                    stitch.y * scalingFactor);
            fprintf(file, "ST0.00,0.00;");
            fprintf(file, "SP0;");
            fprintf(file, "HT0;");
            fprintf(file, "HS0;");
            fprintf(file, "TT0;");
            fprintf(file, "TS0;");
            firstStitchOfBlock = 0;
        } else {
            fprintf(file, "PD%f,%f;", stitch.x * scalingFactor,
                stitch.y * scalingFactor);
        }
    }
    fprintf(file, "PU0.0,0.0;");
    fprintf(file, "PU0.0,0.0;");
    return 1; /*TODO: finish WritePlt */
}

/*
 * RGB Color File (.rgb)
 * The RGB format is a color-only format to act as an external color file for other formats.
 */
char
readRgb(EmbPattern* pattern, void* file)
{
    int i, numberOfColors;

    emb_fseek(file, 0x00, SEEK_END);
    numberOfColors = ftell(file) / 4;

    pattern->thread_list->count = 0;

    printf("numberOfColors: %d\n", numberOfColors);

    emb_fseek(file, 0x00, SEEK_SET);
    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        emb_pattern_addThread(pattern, t);
    }
    return 1;
}

char
writeRgb(EmbPattern* pattern, void* file)
{
    int i;
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        embColor_write(file, c, 4);
    }
    return 1;
}

/*
 * Janome Embroidery Format (.sew)
 * The Janome sew format is stitch-only.
 */

char
sewDecode(unsigned char inputByte)
{
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char) (-~(inputByte - 1)) : (char) inputByte;
}

char
readSew(EmbPattern* pattern, void* file)
{
    int i, flags, numberOfColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    emb_fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    emb_fseek(file, 0x00, SEEK_SET);
    numberOfColors = fgetc(file);
    numberOfColors += (fgetc(file) << 8);


    for (i = 0; i < numberOfColors; i++) {
        int color = fread_int16(file);
        emb_pattern_addThread(pattern, jefThreads[color%78]);
    }
    emb_fseek(file, 0x1D78, SEEK_SET);

    for (i = 0; ftell(file) < fileLength; i++) {
        unsigned char b[2];
        emb_fread(b, 2, file);

        flags = NORMAL;
        if (thisStitchIsJump) {
            flags = TRIM;
            thisStitchIsJump = 0;
        }
        if (b[0] == 0x80) {
            if (b[1] == 1) {
                emb_fread(b, 2, file);
                flags = STOP;
            } else if ((b[1] == 0x02) || (b[1] == 0x04)) {
                thisStitchIsJump = 1;
                emb_fread(b, 2, file);
                flags = TRIM;
            } else if (b[1] == 0x10) {
               break;
            }
        }
        dx = sewDecode(b[0]);
        dy = sewDecode(b[1]);
        if (abs(dx) == 127 || abs(dy) == 127) {
            thisStitchIsJump = 1;
            flags = TRIM;
        }
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    printf("current position: %ld\n", ftell(file));
    return 1;
}

char
writeSew(EmbPattern* pattern, void* file)
{
    int i;
    EmbReal xx = 0.0, yy = 0.0;
    binaryWriteShort(file, pattern->thread_list->count);

    if (emb_verbose>1) {
        printf("Debugging Information\n");
        printf("number of colors = %d\n", pattern->thread_list->count);
        printf("number of stitches = %d\n", pattern->stitch_list->count);
    }

    for (i = 0; i < pattern->thread_list->count; i++) {
        short thr;
        EmbColor col;
        col = pattern->thread_list->thread[i].color;
        thr = embThread_findNearestThread(col, (EmbThread *)jefThreads, 79);
        binaryWriteShort(file, thr);
    }
    fpad(file, 0, 0x1D78 - 2 - pattern->thread_list->count * 2);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        unsigned char b[4];
        char dx, dy;
        st = pattern->stitch_list->stitch[i];
        dx = (char)emb_round(10.0*(st.x - xx));
        dy = (char)emb_round(10.0*(st.y - yy));
        xx += 0.1*dx;
        yy += 0.1*dy;
        if (st.flags & STOP) {
            b[0] = 0x80;
            b[1] = 0x01;
            b[2] = dx;
            b[3] = dy;
            emb_fwrite(b, 4, file);
        } else if (st.flags & END) {
            b[0] = 0x80;
            b[1] = 0x10;
            b[2] = 0;
            b[3] = 0;
            emb_fwrite(b, 4, file);
        } else if ((st.flags & TRIM) || (st.flags & JUMP)) {
            b[0] = 0x80;
            b[1] = 2;
            b[2] = dx;
            b[3] = dy;
            emb_fwrite(b, 4, file);
        } else {
            b[0] = dx;
            b[1] = dy;
            emb_fwrite(b, 2, file);
        }
    }
    return 1;
}

/*
 * Husqvarna Viking Embroidery Format (.shv)
 * The Husqvarna Viking shv format is stitch-only.
 */
char
shvDecode(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (char)-((unsigned char)((~inputByte) + 1));
    }
    return ((char)inputByte);
}

short shvDecodeShort(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return (short)-((unsigned short)((~inputByte) + 1));
    }
    return ((short)inputByte);
}

char
readShv(EmbPattern* pattern, void* file)
{
    int i;
    char inJump = 0;
    unsigned char fileNameLength, designWidth, designHeight;
    char halfDesignWidth, halfDesignHeight, halfDesignWidth2, halfDesignHeight2;
    char* headerText = "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden";
    char dx = 0, dy = 0;
    char numberOfColors;
    unsigned short magicCode;
    int something;
    short left,top,right,bottom;
    char something2, numberOfSections, something3;
    int stitchesPerColor[256];
    int stitchesSinceChange = 0;
    int currColorIndex = 0;
    unsigned short sx, sy;

    if (!check_header_present(file, 25)) {
        return 0;
    }

    emb_fseek(file, string_len(headerText), SEEK_SET);
    fileNameLength = fgetc(file);
    emb_fseek(file, fileNameLength, SEEK_CUR);
    designWidth = fgetc(file);
    designHeight = fgetc(file);
    halfDesignWidth = fgetc(file);
    halfDesignHeight = fgetc(file);
    halfDesignWidth2 = fgetc(file);
    halfDesignHeight2 = fgetc(file);
    if ((designHeight % 2) == 1) {
        emb_fseek(file, ((designHeight + 1)*designWidth)/2, SEEK_CUR);
    }
    else {
        emb_fseek(file, (designHeight*designWidth)/2, SEEK_CUR);
    }
    numberOfColors = fgetc(file);
    magicCode = fread_uint16(file);
    emb_fseek(file, 1, SEEK_CUR);
    emb_read(file, &something, EMB_INT32_LITTLE);
    left = fread_int16(file);
    top = fread_int16(file);
    right = fread_int16(file);
    bottom = fread_int16(file);

    something2 = (char)fgetc(file);
    numberOfSections = fgetc(file);
    something3 = (char)fgetc(file);

    if (emb_verbose>1) {
        printf("magicCode: %d\n", magicCode);
        printf("halfDesignWidth: %d\n", halfDesignWidth);
        printf("halfDesignHeight: %d\n", halfDesignHeight);
        printf("halfDesignWidth2: %d\n", halfDesignWidth2);
        printf("halfDesignHeight2: %d\n", halfDesignHeight2);
        printf("left: %d\n", left);
        printf("top: %d\n", top);
        printf("right: %d\n", right);
        printf("bottom: %d\n", bottom);
        printf("something2: %d\n", something2);
        printf("number of sections: %d\n", numberOfSections);
        printf("something3: %d\n", something3);
    }

    for (i = 0; i < numberOfColors; i++) {
        unsigned int stitchCount, colorNumber;
        emb_read(file, &stitchCount, EMB_INT32_BIG);
        colorNumber = fgetc(file);
        emb_pattern_addThread(pattern, shvThreads[colorNumber % 43]);
        stitchesPerColor[i] = stitchCount;
        emb_fseek(file, 9, SEEK_CUR);
    }

    emb_fseek(file, -2, SEEK_CUR);

    for (i = 0; !feof(file); i++) {
        unsigned char b0, b1;
        int flags;
        flags = NORMAL;
        if (inJump) {
            flags = JUMP;
        }
        b0 = fgetc(file);
        b1 = fgetc(file);
        if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) {
            emb_pattern_addStitchRel(pattern, 0, 0, STOP, 1);
            currColorIndex++;
            stitchesSinceChange = 0;
        }
        if (b0 == 0x80) {
            stitchesSinceChange++;
            if (b1 == 3) {
                continue;
            }
            else if (b1 == 0x02) {
                inJump = 0;
                continue;
            }
            else if (b1 == 0x01) {
                stitchesSinceChange += 2;
                sx = fgetc(file);
                sx = (unsigned short)(sx << 8 | fgetc(file));
                sy = fgetc(file);
                sy = (unsigned short)(sy << 8 | fgetc(file));
                flags = TRIM;
                inJump = 1;
                emb_pattern_addStitchRel(pattern, shvDecodeShort(sx) / 10.0, shvDecodeShort(sy) / 10.0, flags, 1);
                continue;
            }
        }
        dx = shvDecode(b0);
        dy = shvDecode(b1);
    stitchesSinceChange++;
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    emb_pattern_flipVertical(pattern);

    return 1;
}

char
writeShv(EmbPattern* pattern, void* file)
{
    puts("writeShv not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeShv */
}

/*
 * Sunstar Embroidery Format (.sst)
 * The Sunstar sst format is stitch-only.
 */
char
readSst(EmbPattern* pattern, void* file)
{
    int fileLength;

    emb_fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    emb_fseek(file, 0xA0, SEEK_SET); /* skip the all zero header */
    while (ftell(file) < fileLength) {
        int stitchType = NORMAL;

        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x04) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }

        if ((commandByte & 0x01) == 0x01)
            stitchType = STOP;
        if ((commandByte & 0x02) == 0x02)
            stitchType = JUMP;
        if ((commandByte & 0x10) != 0x10)
            b2 = -b2;
        if ((commandByte & 0x40) == 0x40)
            b1 = -b1;
        emb_pattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1; /*TODO: finish readSst */
}

char
writeSst(EmbPattern* pattern, void* file)
{
    int i;
    int head_length = 0xA0;
    for (i=0; i<head_length; i++) {
        fprintf(file, " ");
    }
    for (i=0; i<pattern->stitch_list->count; i++) {
        printf(".");
    }
    return 0; /*TODO: finish writeSst */
}

/*
 * Data Stitch Embroidery Format (.stx)
 * The Data Stitch stx format is stitch-only.
 */
int
stxReadThread(StxThread* thread, void* file)
{
    int j, colorNameLength, sectionNameLength;
    int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors; /* TODO: determine what these represent */
    int codeLength = 0;
    char* codeBuff = 0;
    char* codeNameBuff = 0;
    EmbColor col;
    char* sectionNameBuff = 0;

    if (!thread) {
        printf("ERROR: format-stx.c stxReadThread(), thread argument is null\n");
        return 0;
    }
    if (!file) { printf("ERROR: format-stx.c stxReadThread(), file argument is null\n"); return 0; }

    codeLength = fgetc(file);
    codeBuff = (char*)malloc(codeLength);
    if (!codeBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeBuff\n");
        return 0;
    }
    /* TODO: check return value */
    emb_fread(codeBuff, codeLength, file);
    thread->colorCode = codeBuff;
    colorNameLength = fgetc(file);
    codeNameBuff = (char*)malloc(colorNameLength);
    if (!codeNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeNameBuff\n");
        return 0;
    }
    emb_fread((unsigned char*)codeNameBuff, colorNameLength, file); /* TODO: check return value */
    thread->colorName = codeNameBuff;

    embColor_read(file, &col, 4);
    if (emb_verbose>1) {
        printf("col red: %d\n", col.r);
        printf("col green: %d\n", col.g);
        printf("col blue: %d\n", col.b);
    }

    sectionNameLength = fgetc(file);
    sectionNameBuff = (char*)malloc(sectionNameLength);
    if (!sectionNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
        return 0;
    }
    emb_fread((unsigned char*)sectionNameBuff, sectionNameLength, file); /* TODO: check return value */
    thread->sectionName = sectionNameBuff;

    emb_read(file, &somethingSomething, EMB_INT32_LITTLE);
    emb_read(file, &somethingSomething2, EMB_INT32_LITTLE);
    emb_read(file, &somethingElse, EMB_INT32_LITTLE);
    numberOfOtherDescriptors = fread_int16(file);
    if (emb_verbose>1) {
        printf("somethingSomething: %d", somethingSomething);
        printf("somethingSomething2: %d", somethingSomething2);
        printf("somethingElse: %d", somethingElse);
        printf("numberOfOtherDescriptors: %d", numberOfOtherDescriptors);
    }

    thread->subDescriptors = (SubDescriptor*)malloc(sizeof(SubDescriptor) * numberOfOtherDescriptors);
    if (!thread->subDescriptors) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors\n");
        return 0;
    }
    for (j = 0; j < numberOfOtherDescriptors; j++) {
        SubDescriptor sd;
        char* subCodeBuff, *subColorNameBuff;
        int subCodeLength, subColorNameLength;

        sd.someNum = fread_int16(file);
        /* Debug.Assert(sd.someNum == 1); TODO: review */
        emb_read(file, &(sd.someInt), EMB_INT32_LITTLE);
        subCodeLength = fgetc(file);
        subCodeBuff = (char*)malloc(subCodeLength);
        if (!subCodeBuff) {
            printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subCodeBuff\n");
            return 0;
        }
        emb_fread((unsigned char*)subCodeBuff, subCodeLength, file); /* TODO: check return value */
        sd.colorCode = subCodeBuff;
        subColorNameLength = fgetc(file);
        subColorNameBuff = (char*)malloc(subColorNameLength);
        if (!subColorNameBuff) {
            printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff\n");
            return 0;
        }
        emb_fread((unsigned char*)subColorNameBuff, subColorNameLength, file); /* TODO: check return value */
        sd.colorName = subColorNameBuff;
        emb_read(file, &(sd.someOtherInt), EMB_INT32_LITTLE);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

char
readStx(EmbPattern* pattern, void* file)
{
    int i, threadCount;
    unsigned char* gif = 0;
    /* public Bitmap Image; */
    StxThread* stxThreads = 0;
    unsigned char headerBytes[7];
    char* header = 0;
    char stor;
    char filetype[4], version[5];
    int paletteLength, imageLength, something1, stitchDataOffset, something3;
    int threadDescriptionOffset, stitchCount, left, right, colors;
    int val[12];
    int bottom, top;

    if (!check_header_present(file, 15)) {
        puts("ERROR: header is not present.");
        return 0;
    }

    /* bytes 0-6 */
    emb_fread(headerBytes, 7, file); /* TODO: check return value */
    header = (char*)headerBytes;

    /* bytes 7-9 */
    memory_copy(filetype, &header[0], 3);
    /* bytes 10-13 */
    memory_copy(version, &header[3], 4);
    filetype[3] = '\0';
    version[4] = '\0';
    /* byte 14 */
    stor = (char)fgetc(file);
    if (emb_verbose>1) {
        printf("stor: %d\n", stor);
    }

    /* bytes 15- */
    emb_read(file, &paletteLength, EMB_INT32_LITTLE);
    emb_read(file, &imageLength, EMB_INT32_LITTLE);
    emb_read(file, &something1, EMB_INT32_LITTLE);
    emb_read(file, &stitchDataOffset, EMB_INT32_LITTLE);
    emb_read(file, &something3, EMB_INT32_LITTLE);
    emb_read(file, &threadDescriptionOffset, EMB_INT32_LITTLE);
    emb_read(file, &stitchCount, EMB_INT32_LITTLE);
    emb_read(file, &colors, EMB_INT32_LITTLE);
    emb_read(file, &right, EMB_INT16_LITTLE);
    emb_read(file, &left, EMB_INT16_LITTLE);
    emb_read(file, &bottom, EMB_INT16_LITTLE);
    emb_read(file, &top, EMB_INT16_LITTLE);
    if (emb_verbose>1) {
        printf("paletteLength:           %d\n", paletteLength);
        printf("imageLength:             %d\n", imageLength);
        printf("something1:              %d\n", something1);
        printf("stitchDataOffset:        %d\n", stitchDataOffset);
        printf("something3:              %d\n", something3);
        printf("threadDescriptionOffset: %d\n", threadDescriptionOffset);
        printf("stitchCount:             %d\n", stitchCount);
        printf("colors:                  %d\n", colors);
        printf("right:                   %d\n", right);
        printf("left:                    %d\n", left);
        printf("bottom:                  %d\n", bottom);
        printf("top:                     %d\n", top);
    }

    gif = (unsigned char*)malloc(imageLength);
    if (!gif) {
        printf("ERROR: format-stx.c readStx(), unable to allocate memory for gif\n");
        return 0;
    }
    emb_fread(gif, imageLength, file); /* TODO: check return value */
    /*Stream s2 = new MemoryStream(gif); TODO: review */
    /*Image = new Bitmap(s2); TODO: review */

    threadCount = fread_int16(file);
    stxThreads = (StxThread*)malloc(sizeof(StxThread) * threadCount);
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
        string_copy(t.description, st.colorName);
        string_copy(t.catalogNumber, st.colorCode);
        emb_pattern_addThread(pattern, t);
        stxThreads[i] = st;
    }

    emb_fseek(file, 15, SEEK_CUR);

    for (i = 0; i < 12; i++) {
        emb_read(file, val+i, EMB_INT16_LITTLE);
        if (emb_verbose>1) {
            printf("identify val[%d] = %d", i, val[i]);
        }
    }
    if (emb_verbose>1) {
        puts("val[4] == val[5] == 0");
        puts("val[10] == val[11] == 0");
    }
    emb_fseek(file, 8, SEEK_CUR); /* 0 0 */
    /* br.BaseStream.Position = stitchDataOffset; TODO: review */
    for (i = 1; i < stitchCount; ) {
        char b0 = (char)fgetc(file);
        char b1 = (char)fgetc(file);
        if (b0 == -128) {
            switch (b1) {
                case 1:
                    b0 = (char)fgetc(file);
                    b1 = (char)fgetc(file);
                    /*emb_pattern_addStitchRel(b0, b1, STOP); TODO: review */

                    i++;
                    break;
                case 2:
                    b0 = (char)fgetc(file);
                    b1 = (char)fgetc(file);
                    emb_pattern_addStitchRel(pattern, b0 / 10.0,
                        b1 / 10.0, JUMP, 1);
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
            emb_pattern_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, NORMAL, 1);
            i++;
        }
    }
    emb_pattern_flipVertical(pattern);
    return 1;
}

char
writeStx(EmbPattern* pattern, void* file)
{
    puts("ERROR: writeStx is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeStx */
}

/*
 * Scalable Vector Graphics (.svg)
 * The scalable vector graphics (SVG) format is a graphics format maintained by ...
 */
int svgCreator;

int svgExpect;
int svgMultiValue;

int current_element_id;
SvgAttribute attributeList[1000];
int n_attributes = 0;
char
currentAttribute[1000];
char
currentValue[1000];

#if 0
int svg_identify_element(char *buff);

EmbColor svgColorToEmbColor(char* colorString)
{
    EmbColor c;
    char* pEnd = 0;
    char* colorStr = copy_trim(colorString); /* Trim out any junk spaces */
    int length = string_len(colorStr);
    int tableColor;

    /* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
    if (length == 7 && colorStr[0] == '#') /* Six digit hex — #rrggbb */ {
        while (*colorStr=='#' && *colorStr!=0) {
            colorStr++;
        }
        c = embColor_fromHexStr(colorStr);
    }
    else if (length == 4 && colorStr[0] == '#') /* Three digit hex — #rgb */ {
        /* Convert the 3 digit hex to a six digit hex */
        char hex[7];
        sprintf(hex, "%c%c%c%c%c%c", colorStr[1], colorStr[1], colorStr[2],
            colorStr[2], colorStr[3], colorStr[3]);

        c = embColor_fromHexStr(hex);
    }
    else if (strstr(colorStr, "%")) /* Float functional — rgb(R%, G%, B%) */ {
        char *s = colorStr;
        /* replace characters we aren't using with spaces */
        for (; *s; s++) {
            if (*s == 'r' || *s == 'g' || *s == 'b' || *s == ','
                || *s == '(' || *s == ')' || *s == '%') {
                *s = ' ';
            }
        }
        c.r = (unsigned char)emb_round(255.0/100.0 * strtod(colorStr, &pEnd));
        c.g = (unsigned char)emb_round(255.0/100.0 * strtod(pEnd,     &pEnd));
        c.b = (unsigned char)emb_round(255.0/100.0 * strtod(pEnd,     &pEnd));
    }
    else if (length > 3 && colorStr[0] == 'r' && colorStr[1] == 'g' && colorStr[2] == 'b') {
        /* Integer functional — rgb(rrr, ggg, bbb) */
        char *s = colorStr;
        /* replace characters we aren't using with spaces */
        for (; *s; s++) {
            if (*s == 'r' || *s == 'g' || *s == 'b' || *s == ','
                || *s == '(' || *s == ')') {
                *s = ' ';
            }
        }
        c.r = (unsigned char)strtol(colorStr, &pEnd, 10);
        c.g = (unsigned char)strtol(pEnd,     &pEnd, 10);
        c.b = (unsigned char)strtol(pEnd,     &pEnd, 10);
    }
    else /* Color keyword */ {
        tableColor = threadColor(colorStr, SVG_Colors);
        if (tableColor < 0) {
            printf("SVG color string not found: %s.\n", colorStr);
            c.r = 0;
            c.g = 0;
            c.b = 0;
        }
        else {
            c.r = (tableColor >> 16) & 0xFF;
            c.g = (tableColor >> 8) & 0xFF;
            c.b = tableColor & 0xFF;
        }
    }

    safe_free(colorStr);
    /* Returns black if all else fails */
    return c;
}

int
toUpper(char cmd)
{
    if (cmd >= 'a' && cmd <= 'z') {
        return cmd - 'a' + 'A';
    }
    return cmd;
}

int svgPathCmdToEmbPathFlag(char cmd)
{
    /* TODO: This function needs some work */
    if     (toUpper(cmd) == 'M') return MOVETO;
    else if (toUpper(cmd) == 'L') return LINETO;
    /*
    else if (toUpper(cmd) == 'C') return CUBICTOCONTROL1;
    else if (toUpper(cmd) == 'CC') return CUBICTOCONTROL2;
    else if (toUpper(cmd) == 'CCC') return CUBICTOEND;
    else if (toUpper(cmd) == 'A') return ELLIPSETORAD;
    else if (toUpper(cmd) == 'AA') return ELLIPSETOEND;
    else if (toUpper(cmd) == 'Q') return QUADTOCONTROL;
    else if (toUpper(cmd) == 'QQ') return QUADTOEND;
    else if (toUpper(cmd) == 'Z') return LINETO;
    */

    /*else if (toUpper(cmd) == 'B') return BULGETOCONTROL; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else if (toUpper(cmd) == 'BB') return BULGETOEND; */   /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else { printf("ERROR: svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

char* svgAttribute_getValue(const char* name) {
    int i;
    for (i=0; i<n_attributes; i++) {
        if (string_equals(attributeList[i].name, name)) {
            return attributeList[i].value;
        }
    }
    return "none";
}

void
parse_circle(EmbPattern *p)
{
    EmbCircle circle;
    circle.center.x = atof(svgAttribute_getValue("cx"));
    circle.center.y = atof(svgAttribute_getValue("cy"));
    circle.radius = atof(svgAttribute_getValue("r"));
    emb_pattern_addCircleAbs(p, circle);
}

void
parse_ellipse(EmbPattern *p)
{
    EmbEllipse ellipse;
    ellipse.center.x = atof(svgAttribute_getValue("cx"));
    ellipse.center.y = atof(svgAttribute_getValue("cy"));
    ellipse.radius.x = atof(svgAttribute_getValue("rx"));
    ellipse.radius.y = atof(svgAttribute_getValue("ry"));
    emb_pattern_addEllipseAbs(p, ellipse);
}

void
parse_line(EmbPattern *p)
{
    char *x1, *x2, *y1, *y2;
    x1 = svgAttribute_getValue("x1");
    y1 = svgAttribute_getValue("y1");
    x2 = svgAttribute_getValue("x2");
    y2 = svgAttribute_getValue("y2");

    /* If the starting and ending points are the same, it is a point */
    if (string_equals(x1, x2) && string_equals(y1, y2)) {
        EmbPoint point;
        point.position.x = atof(x1);
        point.position.y = atof(y1);
        emb_pattern_addPointAbs(p, point);
    }
    else {
        EmbLine line;
        line.start.x = atof(x1);
        line.start.y = atof(y1);
        line.end.x = atof(x2);
        line.end.y = atof(y2);
        emb_pattern_addLineAbs(p, line);
    }

}

void
parse_path(EmbPattern *p)
{
    /* TODO: finish */
    EmbVector position, f_point, l_point, c1_point, c2_point;
    int cmd, i, pos, reset, trip;
    EmbReal pathData[7];
    unsigned int numMoves;
    EmbColor color;
    EmbArray* flagList = 0;
    EmbPath path;
    char* pointStr = svgAttribute_getValue("d");
    char* mystrok = svgAttribute_getValue("stroke");
    int last = string_len(pointStr);
    int size = 32;
    int pendingTask = 0;
    int relative = 0;
    char* pathbuff = 0;

    EmbArray* pointList = 0;
    pos = 0;
    /* An odometer aka 'tripometer' used for stepping thru the pathData */
    trip = -1;
    /* count of float[] that has been filled.
     * 0 = first item of array
     * -1 = not filled = empty array
     */
    reset = -1;
    position.x = 0.0;
    position.y = 0.0;
    f_point.x = 0.0;
    f_point.y = 0.0;
    l_point.x = 0.0;
    l_point.y = 0.0;
    c1_point.x = 0.0;
    c1_point.y = 0.0;
    c2_point.x = 0.0;
    c2_point.y = 0.0;
    cmd = 0;
    numMoves = 0;

    pathbuff = (char*)malloc(size);
    if (!pathbuff) {
        printf("ERROR: svgAddToPattern(), cannot allocate memory for pathbuff\n");
        return;
    }

    printf("stroke:%s\n", mystrok);

    for (i = 0; i < last; i++) {
        char c = pointStr[i];
        if (emb_verbose>1) {
            printf("relative %d\n", relative);
            printf("c1.x %f\n", c1_point.x);
            printf("c2.x %f\n", c2_point.x);
        }
        switch (c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                pathbuff[pos++] = (char)c;                  /* add a more char */
                break;

            case ' ':
            case ',':

                /*printf("    ,'%s'    ~POS=%d  ~TRIP=%d  ~[pos]=%d\n", pathbuff,pos,trip, pathbuff[pos]);*/
                if (pos > 0) {         /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    ,val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                break;

            case '-':

                if (pos > 0) {
                    /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    -val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                pathbuff[pos++] = (char)c;
                /* add a more char */
                break;

            default:
                    /*** ASSUMED ANY COMMAND FOUND ***/


                    if (pos > 0) {
                        /* just make sure: append float to array,
                         * if it not yet stored
                         */
                        pathbuff[pos] = 0;
                        pos = 0;
                        printf("    >val:%s\n", pathbuff);
                        pathData[++trip] = atof(pathbuff);
                    }

                    /**** Compose Point List ****/

                    /* below "while" is for avoid losing last 'z'
                     * command that maybe never accommodated.
                     */
                    pendingTask = 1; if (i==last-1) {pendingTask = 2;}

                    while (pendingTask > 0) {
                        pendingTask -= 1;

                    /* Check whether prior command need to be saved */
                    if (trip>=0) {
                        EmbPoint test;
                        trip = -1;
                        reset = -1;

                        relative = 0;
                        /* relative to prior coordinate point
                         * or absolute coordinate? */

                        if (cmd >= 'a' && cmd <= 'z') {
                            relative = 1;
                        }

                        if (cmd == 'M' || cmd == 'm') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                            f_point = position;
                        }
                        else if (cmd == 'L' || cmd == 'l') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'H' || cmd == 'h') {
                            position.x = pathData[0];
                            position.y = l_point.y;
                        }
                        else if (cmd == 'V'  || cmd == 'v') {
                            position.x = l_point.x;
                            position.y = pathData[1];
                        }
                        else if (cmd == 'C' || cmd == 'c') {
                            position.x = pathData[4];
                            position.y = pathData[5];
                            c1_point.x = pathData[0];
                            c1_point.y = pathData[1];
                            c2_point.x = pathData[2];
                            c2_point.y = pathData[3];
                        }
                        /*
                        else if (cmd == 'S') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 's') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'Q') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'q') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'T') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 't') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'A') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'a') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        */
                        else if (cmd == 'Z' || cmd == 'z') {
                            position = f_point;
                        }

                        if (!pointList && !flagList) {
                            pointList = emb_array_create(EMB_POINT);
                            flagList = emb_array_create(EMB_FLAG);
                        }
                        test.position = position;
                        emb_array_addPoint(pointList, test);
                        emb_array_addFlag(flagList, svgPathCmdToEmbPathFlag(cmd));
                        l_point = position;

                        pathbuff[0] = (char)cmd;                  /* set the command for compare */
                        pathbuff[1] = 0;
                        pos = 0;

                        printf("*prior:%s (%f, %f,  %f, %f,     %f,%f,  %f) \n", pathbuff,
                                pathData[0],
                                pathData[1],
                                pathData[2],
                                pathData[3],
                                pathData[4],
                                pathData[5],
                                pathData[6]
                                );

                    }

                    /* assign new command */
                    if (trip == -1 && reset == -1) {
                        /* set the command for compare */
                        pathbuff[0] = (char)c;
                        pathbuff[1] = 0;

                        printf("cmd:%s\n", pathbuff);
                        if (c == 'M' || c == 'm' || c == 'L' || c == 'l') {
                            cmd = c;
                            reset = 2;
                            numMoves++;
                        }
                        else if (c == 'C' || c == 'c') {
                            cmd = c;
                            reset = 6;
                        }
                        else if (c == 'H' || c == 'h' || c == 'V' || c == 'v') {
                            cmd = c;
                            reset = 1;
                        }
                        else if (c == 'S' || c == 's' || c == 'Q' || c == 'q') {
                            cmd = c;
                            reset = 4;
                        }
                        else if (c == 'T' || c == 't') {
                            cmd = c;
                            reset = 2;
                        }
                        else if (c == 'A' || c == 'a') {
                            cmd = c;
                            reset = 7;
                        }
                        else if (c == 'Z' || c == 'z') {
                            cmd = c;
                            reset = 0;
                        }
                        else {
                            printf("ERROR: svgAddToPattern(), %s is not a valid svg path command, skipping...\n", pathbuff);
                            trip = -1;
                            reset = -1;
                        }
                    }
                    /* avoid losing 'z' command that maybe never accommodated. */
                        if (i==last-1) {
                            trip = 2;
                        }
                    } /* while pendingTask */


                    break;
        }
        if (pos >= size - 1) {
            /* increase pathbuff length - leave room for 0 */
            size *= 2;
            pathbuff = (char*)realloc(pathbuff, size);
            if (!pathbuff) {
                printf("ERROR: svgAddToPattern(), cannot re-allocate memory for pathbuff\n");
                return;
            }
        }
    }
    safe_free(pathbuff);

    /* TODO: subdivide numMoves > 1 */

    color = svgColorToEmbColor(svgAttribute_getValue("stroke"));

    path.pointList = pointList;
    path.flagList = flagList;
    path.color = color;
    path.lineType = 1;
    emb_pattern_addPathAbs(p, path);
}

EmbArray *
parse_pointlist(EmbPattern *p)
{
    char* pointStr = svgAttribute_getValue("points");
    int last = string_len(pointStr);
    int size = 32;
    int i = 0;
    int pos = 0;
    unsigned char odd = 1;
    EmbReal xx = 0.0;
    EmbReal yy = 0.0;

    EmbArray* pointList = 0;

    char* polybuff = 0;

    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }

    polybuff = (char*)malloc(size);
    if (!polybuff) {
        printf("ERROR: svgAddToPattern(), cannot allocate memory for polybuff\n");
        return pointList;
    }
    for (i = 0; i < last; i++) {
        char c = pointStr[i];
        switch (c) {
            case ' ':
                if (pos == 0) {
                    break;
                }
                polybuff[pos] = 0;
                pos = 0;
                /*Compose Point List */
                if (odd) {
                    odd = 0;
                    xx = atof(polybuff);
                }
                else {
                    EmbPoint a;
                    odd = 1;
                    yy = atof(polybuff);

                    if (!pointList) {
                        pointList = emb_array_create(EMB_POINT);
                    }
                    a.position.x = xx;
                    a.position.y = yy;
                    emb_array_addPoint(pointList, a);
                }

                break;
            default:
                polybuff[pos++] = (char)c;
                break;
        }
        if (pos >= size - 1) {
             /* increase polybuff length - leave room for 0 */
             size *= 2;
             polybuff = (char*)realloc(polybuff, size);
             if (!polybuff) {
                 printf("ERROR: svgAddToPattern(), cannot re-allocate memory for polybuff\n");
                 return NULL;
             }
        }
    }
    safe_free(polybuff);
    return pointList;
}

void
parse_polygon(EmbPattern *p)
{
    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }
    /*
    EmbPolygonObject polygonObj;
    polygonObj.pointList = emb_array_create(EMB_POINT);
    BROKEN: polygonObj.pointList = parse_pointlist(p);
    polygonObj.color = svgColorToEmbColor(svgAttribute_getValue("stroke"));
    polygonObj.lineType = 1; TODO: use lineType enum
    emb_pattern_addPolygonObjectAbs(p, &polygonObj);
    */
}

void
parse_polyline(EmbPattern *p)
{
    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }
    /* BROKEN
    EmbPolylineObject* polylineObj;
    polylineObj = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
    polylineObj->pointList = parse_pointlist(p);
    polylineObj->color = svgColorToEmbColor(svgAttribute_getValue("stroke"));
    polylineObj->lineType = 1; TODO: use lineType enum
    emb_pattern_addPolylineObjectAbs(p, polylineObj);
    */
}

void
parse_rect(EmbPattern *p)
{
    EmbRect rect;
    float width, height;
    rect.left = atof(svgAttribute_getValue("x"));
    rect.top = atof(svgAttribute_getValue("y"));
    width = atof(svgAttribute_getValue("width"));
    height = atof(svgAttribute_getValue("height"));
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;
    emb_pattern_addRectAbs(p, rect);
}

void
svgAddToPattern(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: svgAddToPattern(), p argument is null\n");
        return;
    }
    switch (current_element_id) {
    case ELEMENT_CIRCLE:
        parse_circle(p);
        break;
    case ELEMENT_ELLIPSE:
        parse_ellipse(p);
        break;
    case ELEMENT_LINE:
        parse_line(p);
        break;
    case ELEMENT_PATH:
        parse_path(p);
        break;
    case ELEMENT_POLYGON:
        parse_polygon(p);
        break;
    case ELEMENT_POLYLINE:
        parse_polygon(p);
        break;
    case ELEMENT_RECT:
        parse_rect(p);
        break;
    default:
        break;
    }
}

int svg_identify_element(char *buff)
{
    int i;
    for (i=0; svg_element_tokens[i][0]; i++) {
        if (string_equals(buff, svg_element_tokens[i])) {
            return i;
        }
    }
    return -1;
}

int svgIsElement(const char* buff) {
    if (stringInArray(buff, svg_element_tokens)) {
        return SVG_ELEMENT;
    }
    /* Attempt to identify the program that created the SVG file.
     * This should be in a comment at that occurs before the svg element. */
    else if (string_equals(buff, "Embroidermodder")) {
        svgCreator = SVG_CREATOR_EMBROIDERMODDER;
    }
    else if (string_equals(buff, "Illustrator")) {
        svgCreator = SVG_CREATOR_ILLUSTRATOR;
    }
    else if (string_equals(buff, "Inkscape")) {
        svgCreator = SVG_CREATOR_INKSCAPE;
    }

    return SVG_NULL;
}

/*
int
svgIsSvgAttribute(const char* buff)
{
    const char *inkscape_tokens[] = {
        "xmlns:dc", "xmlns:cc", "xmlns:rdf", "xmlns:svg", "xmlns", "\0"
    };
    if (stringInArray(buff, svg_attribute_tokens)) {
        return SVG_ATTRIBUTE;
    }
    if (svgCreator == SVG_CREATOR_INKSCAPE) {
        if (stringInArray(buff, inkscape_tokens)) {
            return SVG_ATTRIBUTE;
        }
    }
    printf("svgIsSvgAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}
*/

void
svgProcess(int c, const char* buff)
{
    if (svgExpect == SVG_EXPECT_ELEMENT) {
        char advance = 0;
        if (buff[0] == '/') {
            return;
        }
        advance = (char)svgIsElement(buff);
        if (advance) {
            printf("ELEMENT:\n");
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            current_element_id = svg_identify_element((char*)buff);
        } else {
            return;
        }
    } else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
        char advance = 0;
        switch (current_element_id) {
        case ELEMENT_A:
        case ELEMENT_CIRCLE:
        case ELEMENT_DEFS:
        case ELEMENT_ELLIPSE:
        case ELEMENT_FOREIGN_OBJECT:
        case ELEMENT_G:
        case ELEMENT_LINE:
        case ELEMENT_LINEAR_GRADIENT:
        case ELEMENT_PATH:
        case ELEMENT_POLYGON:
        case ELEMENT_POLYLINE:
        case ELEMENT_RADIAL_GRADIENT:
        case ELEMENT_RECT:
        case ELEMENT_SOLID_COLOR:
        case ELEMENT_STOP:
        case ELEMENT_SVG:
        case ELEMENT_SWITCH:
        case ELEMENT_TEXT:
        case ELEMENT_TEXT_AREA:
        case ELEMENT_TSPAN:
        case ELEMENT_USE:
            if (stringInArray(buff, svg_property_tokens)) {
                advance = SVG_PROPERTY;
            }
            break;
        case ELEMENT_ANIMATION:
        case ELEMENT_AUDIO:
        case ELEMENT_DESC:
        case ELEMENT_IMAGE:
        case ELEMENT_METADATA:
        case ELEMENT_TITLE:
        case ELEMENT_VIDEO:
            if (stringInArray(buff, svg_media_property_tokens)) {
                advance = SVG_MEDIA_PROPERTY;
            }
            break;
            default: break;
        }
        if (!advance) {
            if (stringInArray(buff, (const char **)svg_attribute_table[current_element_id])) {
                advance = SVG_ATTRIBUTE;
            }
            printf("ERROR %s not found in svg_attribute_table[%d].\n",
                buff, current_element_id);
        }
        if (advance) {
            printf("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            string_copy(currentAttribute, buff);
        }
    } else if (svgExpect == SVG_EXPECT_VALUE) {
        int last = string_len(buff) - 1;
        printf("VALUE:\n");

        /* single-value */
        if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            string_copy(attributeList[n_attributes].name, currentAttribute);
            string_copy(attributeList[n_attributes].value, buff);
            n_attributes++;
        } else { /* multi-value */
            svgMultiValue = 1;
            if (string_len(currentValue)==0) {
                string_copy(currentValue, buff);
            }
            else {
                string_cat(currentValue, " ");
                string_cat(currentValue, buff);
            }
            if (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
                svgMultiValue = 0;
                svgExpect = SVG_EXPECT_ATTRIBUTE;
                string_copy(attributeList[n_attributes].name, currentAttribute);
                string_copy(attributeList[n_attributes].value, currentValue);
                n_attributes++;
            }
        }
    }
    if (svgExpect != SVG_EXPECT_NULL) {
        printf("%s\n", buff);
    }
    if (c == '>') {
        svgExpect = SVG_EXPECT_NULL;
    }
}
#endif


char
readSvg(EmbPattern* pattern, void* file) {
    int size, pos, i;
    char* buff = 0, c;
    size = 1024;

    puts("Deactived readSvg for testing.");
    return 0;

#if 0
    for (i=0; i<1000; i++) {
        attributeList[i].name = (char*)malloc(size);
        attributeList[i].value = (char*)malloc(size);
    }

    buff = (char*)malloc(size);
    if (!buff) {
        printf("ERROR: readSvg(), cannot allocate memory for buff\n");
        return 0;
    }
    svgCreator = SVG_CREATOR_NULL;
    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;

    currentAttribute[0] = 0;
    currentValue[0] = 0;

    /* Pre-flip in case of multiple reads on the same pattern */
    emb_pattern_flipVertical(pattern);

    pos = 0;
    while (fread(&c, 1, 1, file)) {
        switch (c) {
        case '<':
            if (svgExpect == SVG_EXPECT_NULL) {
                svgAddToPattern(pattern);
                svgExpect = SVG_EXPECT_ELEMENT;
            }
            break;
        case '>':
            /* abnormal case that may occur in svg element where '>' is all by itself */
            if (pos == 0) {
                /*TODO: log a warning about this absurdity! */
                svgExpect = SVG_EXPECT_ELEMENT;
            }
            break;
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        case '=':
            if (pos == 0)
                break;
            buff[pos] = 0;
            pos = 0;
            svgProcess(c, buff);
            break;
        default:
            buff[pos++] = (char)c;
            break;
        }
        if (pos >= size - 1) {
            /* increase buff length - leave room for 0 */
            size *= 2;
            buff = (char*)realloc(buff, size);
            if (!buff) {
                printf("ERROR: readSvg(), cannot re-allocate memory for buff\n");
                return 0;
            }
        }
    }

    safe_free(buff);

    if (emb_verbose>1) {
        printf("OBJECT SUMMARY:\n");
        if (pattern->circles) {
            for (i = 0; i < pattern->circles->count; i++) {
                EmbCircle c = pattern->circles->circle[i];
                printf("circle %f %f %f\n", c.center.x, c.center.y, c.radius);
            }
        }
        if (pattern->ellipses) {
            for (i = 0; i < pattern->ellipses->count; i++) {
                EmbEllipse e = pattern->ellipses->ellipse[i];
                printf("ellipse %f %f %f %f\n", e.center.x, e.center.y, e.radius.x, e.radius.y);
            }
        }
        if (pattern->geometry) {
            for (i = 0; i < pattern->geometry->count; i++) {
                EmbLine li = pattern->geometry->geometry[i].object.line;
                printf("line %f %f %f %f\n", li.start.x, li.start.y, li.end.x, li.end.y);
            }
        }
        if (pattern->points) {
            for (i = 0; i < pattern->points->count; i++) {
                EmbVector po = pattern->points->point[i].position;
                printf("point %f %f\n", po.x, po.y);
            }
        }
        if (pattern->polygons) {
            for (i = 0; i < pattern->polygons->count; i++) {
                EmbArray *verts = pattern->polygons->polygon[i].pointList;
                printf("polygon %d\n", verts->count);
            }
        }
        if (pattern->polylines) {
            for (i = 0; i < pattern->polylines->count; i++) {
                EmbArray * verts = pattern->polylines->polyline[i].pointList;
                printf("polyline %d\n", verts->count);
            }
        }
        if (pattern->rects) {
            for (i = 0; i < pattern->rects->count; i++) {
                EmbRect r = pattern->rects->rect[i];
                EmbReal width = r.right - r.left;
                EmbReal height = r.bottom - r.top;
                printf("rect %f %f %f %f\n", r.left, r.top, width, height);
            }
        }
    }

    for (i=0; i<1000; i++) {
        safe_free(attributeList[i].name);
        safe_free(attributeList[i].value);
    }
    /* Flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    emb_pattern_flipVertical(pattern);
#endif
    return 1; /*TODO: finish readSvg */
}

/*! Writes the data from a pattern to a file with the given a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char
writeSvg(EmbPattern* pattern, void *file)
{
    EmbRect boundingRect;
    EmbRect rect;
    EmbColor color;
    int i, j;
    char isNormal, tmpX[32], tmpY[32];
    EmbRect border;

    /* Pre-flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    emb_pattern_flipVertical(pattern);
    boundingRect = emb_pattern_calcBoundingBox(pattern);
    fprintf(file, "<?xml version=\"1.0\"?>\n");
    fprintf(file, "<!-- Embroidermodder 2 SVG Embroidery File -->\n");
    fprintf(file, "<!-- http://embroidermodder.github.io -->\n");
    fprintf(file, "<svg ");

    /* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
    *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
    *       If the attribute values are incorrect, some applications wont open it at all.
    */

    /* Add a margin of 10%. */
    border = boundingRect;
    border.left *= 10.0;
    border.right *= 10.0;
    border.top *= 10.0;
    border.bottom *= 10.0;
    border.left -= 0.1*(border.right - border.left);
    border.right += 0.1*(border.right - border.left);
    border.top -= 0.1*(border.bottom - border.top);
    border.bottom += 0.1*(border.bottom - border.top);
    /* Sanity check here? */
    fprintf(file, "viewBox=\"%f %f %f %f\" ",
            border.left, border.top,
            border.right - border.left,
            border.bottom - border.top);

    fprintf(file, "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">");
    fprintf(file, "\n<g transform=\"scale(10)\">");
    /*TODO: Low Priority Optimization:
    *      Using %g in embFile_printf just doesn't work good enough at trimming trailing zeroes.
    *      It's precision refers to significant digits, not decimal places (which is what we want).
    *      We need to roll our own function for trimming trailing zeroes to keep
    *      the precision as high as possible if needed, but help reduce file size also. */

    /*TODO: Low Priority Optimization:
    *      Make sure that the line length that is output doesn't exceed 1000 characters. */

    /*TODO: Low Priority: Indent output properly. */

    /* write circles, ellipses and lines */
    for (i = 0; i < pattern->geometry->count; i++) {
        EmbGeometry g = pattern->geometry->geometry[i];
        switch (g.type) {
        case EMB_CIRCLE: {
            EmbCircle circle = g.object.circle;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<circle stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" r=\"%f\" />",
                g.color.r,
                g.color.g,
                g.color.b,
                circle.center.x,
                circle.center.y,
                circle.radius);
            break;
        }
        case EMB_ELLIPSE: {
            EmbEllipse ellipse = g.object.ellipse;
            color = g.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<ellipse stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" />",
                        color.r,
                        color.g,
                        color.b,
                        ellipse.center.x,
                        ellipse.center.y,
                        ellipse.radius.x,
                        ellipse.radius.y);
            break;
        }
        case EMB_LINE: {
            EmbLine line = g.object.line;
            color = g.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                color.r, color.g, color.b,
                line.start.x, line.start.y, line.end.x, line.end.y);
            break;
        }
        case EMB_POINT: {
            EmbPoint p = g.object.point;
            /* See SVG Tiny 1.2 Spec:
             * Section 9.5 The 'line' element
             * Section C.6 'path' element implementation notes */
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                p.color.r, p.color.g, p.color.b,
                p.position.x, p.position.y, p.position.x, p.position.y);
            break;
        }
        case EMB_POLYGON: {
            EmbArray *pointList = g.object.polygon.pointList;
            color = g.object.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                fprintf(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r, color.g, color.b,
                    emb_optOut(pointList->geometry[0].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[0].object.point.position.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->geometry[j].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[j].object.point.position.y, tmpY));
            }
            fprintf(file, "\"/>");
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *pointList = g.object.polyline.pointList;
            color = g.object.polyline.color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r,
                    color.g,
                    color.b,
                    emb_optOut(pointList->geometry[0].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[0].object.point.position.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->geometry[j].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[j].object.point.position.y, tmpY));
            }
            fprintf(file, "\"/>");
            break;
        }
        case EMB_RECT: {
            rect = g.object.rect;
            color = g.object.color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<rect stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" />",
                color.r, color.g, color.b,
                rect.left, rect.top,
                rect.right - rect.left,
                rect.bottom - rect.top);
            break;
        }
        default:
            break;
        }
    }

    isNormal = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* TODO:
         * #ifdef SVG_DEBUG for Josh which outputs
         * JUMPS/TRIMS instead of chopping them out.
         */
        if (st.flags == NORMAL && !isNormal) {
            isNormal = 1;
            color = pattern->thread_list->thread[st.color].color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
              fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                                color.r,
                                color.g,
                                color.b,
                                emb_optOut(st.x, tmpX),
                                emb_optOut(st.y, tmpY));
            }
            else if (st.flags == NORMAL && isNormal)
            {
                fprintf(file, " %s,%s", emb_optOut(st.x, tmpX), emb_optOut(st.y, tmpY));
            }
            else if (st.flags != NORMAL && isNormal)
            {
                isNormal = 0;
                fprintf(file, "\"/>");
            }
    }
    fprintf(file, "\n</g>\n</svg>\n");

    /* Reset the pattern so future writes(regardless of format)
     * are not flipped.
     */
    emb_pattern_flipVertical(pattern);

    return 1;
}

/*
 * Pfaff Embroidery Format (.t01)
 * The Pfaff t01 format is stitch-only.
 */

char
readT01(EmbPattern* pattern, void* file)
{
    unsigned char b[3];

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_t01_record(b, &flags, &x, &y);
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    return 1;
}

char
writeT01(EmbPattern* pattern, void* file)
{
    EmbRect boundingRect;
    int i;
    EmbVector pos;

    emb_pattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = emb_pattern_calcBoundingBox(pattern);
    if (emb_verbose>1) {
        printf("bounding rectangle with top %f not used ", boundingRect.top);
        printf("in the function writeT01\n");
    }
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[3];
        int dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        encode_t01_record(b, dx, dy, st.flags);
        emb_fwrite(b, 3, file);
    }
    return 1;
}

/*
 * Pfaff Embroidery Format (.t09)
 * The Pfaff t09 format is stitch-only.
 */

char
readT09(EmbPattern* pattern, void* file)
{
    unsigned char b[3];

    emb_fseek(file, 0x0C, SEEK_SET);

    while (fread(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        unsigned char commandByte = b[2];
        if (commandByte == 0x00) {
            break;
        }
        if (commandByte & 0x10) {
            stitchType = STOP;
        }
        if (commandByte & 0x20) {
            b1 = -b1;
        }
        if (commandByte & 0x40) {
            b2 = -b2;
        }
        emb_pattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeT09(EmbPattern* pattern, void* file)
{
    int i;
    EmbVector pos;
    fpad(file, 0x00, 0x0C);

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[3];
        int dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;

        b[0] = dx;
        b[1] = dy;
        b[2] = 0;
        if (st.flags & NORMAL) {
            /* guessing based on T01 here */
            b[2] |= 0x03;
        }
        /* inferred from readT09 */
        if (st.flags & STOP) {
            b[2] |= 0x10;
        }
        if (dx < 0) {
            b[0] = -dx;
            b[2] |= 0x20;
        }
        if (dy < 0) {
            b[0] = -dy;
            b[2] |= 0x40;
        }
        emb_fwrite(b, 3, file);
    }
    return 1;
}

/*
 * Happy Embroidery Format (.tap)
 * The Happy tap format is stitch-only.
 */

void
encode_tap_record(void* file, int x, int y, int flags)
{
    unsigned char b[3];
    encode_tajima_ternary(b, x, y);

    b[2] |= (char)3;
    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char)(b[2] | 0xC3);
    }
    emb_fwrite(b, 3, file);
}

int
decode_tap_record_flags(unsigned char b2)
{
    if (b2 == 0xF3) {
        return END;
    }
    switch (b2 & 0xC3) {
        case 0x03:
            return NORMAL;
        case 0x83:
            return TRIM;
        case 0xC3:
            return STOP;
        default:
            return NORMAL;
    }
}

char
readTap(EmbPattern* pattern, void* file) {
    unsigned char b[3];

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_tap_record_flags(b[2]);
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    return 1;
}

char
writeTap(EmbPattern* pattern, void* file)
{
    int i;
    EmbVector pos;

    emb_pattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        int dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        encode_tap_record(file, dx, dy, st.flags);
    }
    return 1;
}

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

char
readThr(EmbPattern* pattern, void* file)
{
    ThredHeader header;
    EmbColor background;
    int currentColor;
    int i;

    emb_read(file, &(header.sigVersion), EMB_INT32_LITTLE);
    emb_read(file, &(header.length), EMB_INT32_LITTLE);
    emb_read(file, &(header.numStiches), EMB_INT16_LITTLE);
    header.hoopSize    = fread_uint16(file);
    for (i=0; i<7; i++) {
        header.reserved[i] = fread_uint16(file);
    }

    if ((header.sigVersion & 0xffffff) == 0x746872) {
        unsigned int verVar = (header.sigVersion & 0xff000000) >> 24;
        switch (verVar) {
            case 0:
                break;
            case 1:
            case 2:
                /* skip the file header extension */
                emb_fseek(file, 144, SEEK_CUR);
                break;
            default:
                return 0; /* unsupported version */
        }
    }
    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x, y;
        unsigned int color;
        emb_read(file, &x, EMB_INT32_LITTLE);
        emb_read(file, &y, EMB_INT32_LITTLE);
        emb_read(file, &color, EMB_INT32_LITTLE);
        x /= 10.0;
        y /= 10.0;

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            emb_pattern_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        emb_pattern_addStitchAbs(pattern, x, y, type, 0);
    }
    emb_fseek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

    embColor_read(file, &background, 4);
    if (emb_verbose>1) {
        printf("background: %c %c %c\n", background.r, background.g, background.b);
    }
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        string_copy(thread.description, "NULL");
        string_copy(thread.catalogNumber, "NULL");
        embColor_read(file, &(thread.color), 4);
        emb_pattern_addThread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */
    return 1;
}

char
writeThr(EmbPattern* pattern, void* file)
{
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];

    stitchCount = pattern->stitch_list->count;

    memory_set(&header, 0, sizeof(ThredHeader));
    header.sigVersion = 0x746872 | (version << 24);
    header.length = stitchCount * 12 + 16;
    if (version == 1 || version == 2) {
        header.length = header.length + sizeof(ThredHeader);
    }
    header.numStiches = (unsigned short)stitchCount; /* number of stitches in design */
    header.hoopSize = 5;

    binaryWriteUInt(file, header.sigVersion);
    binaryWriteUInt(file, header.length);
    binaryWriteUShort(file, header.numStiches);
    binaryWriteUShort(file, header.hoopSize);
    for (i=0; i<7; i++) {
        binaryWriteUShort(file, header.reserved[i]);
    }

    if (version == 1 || version == 2) {
        memory_set(&extension, 0, sizeof(ThredExtension));
        extension.auxFormat = 1;
        extension.hoopX = 640;
        extension.hoopY = 640;

        emb_write(file, &(extension.hoopX), EMB_INT32_LITTLE);
        emb_write(file, &(extension.hoopY), EMB_INT32_LITTLE);
        emb_write(file, &(extension.stitchGranularity), EMB_INT32_LITTLE);
        emb_fwrite(extension.creatorName, 50, file);
        emb_fwrite(extension.modifierName, 50, file);
        fputc(extension.auxFormat, file);
        emb_fwrite(extension.reserved, 31, file);
    }

    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned int NOTFRM = 0x00080000;
        EmbStitch st = pattern->stitch_list->stitch[i];
        float x, y;
        x = (float)(st.x * 10.0);
        y = (float)(st.y * 10.0);
        emb_write(file, &x, EMB_INT32_LITTLE);
        emb_write(file, &y, EMB_INT32_LITTLE);
        binaryWriteUInt(file, NOTFRM | (st.color & 0x0F));
    }
    emb_fwrite(bitmapName, 16, file);
    /* background color */
    emb_fwrite("\xFF\xFF\xFF\x00", 4, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        embColor_write(file, c, 4);
        if (i >= 16) break;
    }

    /* write remaining colors if not yet 16 */
    fpad(file, 0, 4*(16-i));

    fpad(file, '4', 16);
    return 1;
}

/*
 * Text File (.txt)
 * The txt format is stitch-only and isn't associated with a specific company.
 */
char
readTxt(EmbPattern* pattern, void* file)
{
    EmbString line;
    int stated_count, i;
    emb_readline(file, line, 99);
    stated_count = atoi(line);
    for (i=0; i<stated_count; i++) {
        EmbStitch st;
        char *p, *y, *color, *flags;
        int state = 0;
        emb_readline(file, line, 99);
        p = line;
        y = line;
        color = line;
        flags = line;
        for (p=line; *p; p++) {
            if (*p == ',' || *p == ' ') {
                *p = 0;
                switch (state) {
                case 0:
                    y = p+1;
                    break;
                case 1:
                    color = p+7;
                    break;
                case 2:
                    flags = p+7;
                    break;
                default:
                    break;
                }
                state++;
            }
        }
        st.x = atof(line);
        st.y = atof(y);
        st.color = atoi(color);
        st.flags = atoi(flags);
        emb_pattern_addStitchAbs(pattern, st.x, st.y, st.flags, st.color);
    }
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readTxt */
}

char
writeTxt(EmbPattern* pattern, void* file)
{
    int i;
    fprintf(file, "%u\n", (unsigned int) pattern->stitch_list->count);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
        fprintf(file, "%.1f,%.1f color:%i flags:%i\n",
                s.x, s.y, s.color, s.flags);
    }
    return 1;
}

/*
 * Barudan Embroidery Format (.u00)
 * The Barudan u00 format is stitch-only.
 */

char
readU00(EmbPattern* pattern, void* file)
{
    int i;
    char dx = 0, dy = 0;
    int flags = NORMAL;
    unsigned char b[3];

    if (!check_header_present(file, 0x100)) {
        return 0;
    }

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between
        0 and 15 with index of color for each color change */
    emb_fseek(file, 0x08, SEEK_SET);
    for (i = 0; i < 16; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 3);
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        emb_pattern_addThread(pattern, t);
    }

    emb_fseek(file, 0x100, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        char negativeX , negativeY;

        if (b[0] == 0xF8 || b[0] == 0x87 || b[0] == 0x91) {
            break;
        }
        if ((b[0] & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((b[0] & 0x1f) == 1) {
            flags = JUMP;
        } else if ((b[0] & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((b[0] & 0x20) > 0);
        negativeY = ((b[0] & 0x40) > 0);

        dx = (char) b[2];
        dy = (char) b[1];
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeU00(EmbPattern* pattern, void* file)
{
    puts("writeU00 not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish WriteU00 */
}

/*
 * Barudan Embroidery Format (.u01)
 * The Barudan u01 format is stitch-only.
 */

/* TODO: AFAIK this is a duplicate of U00. Review for differences and merge files and handle accordingly. */

char
readU01(EmbPattern* pattern, void* file)
{
    int fileLength, negativeX = 0, negativeY = 0, flags = NORMAL;
    char dx, dy;
    unsigned char data[3];

    if (!check_header_present(file, 0x100)) {
        return 0;
    }

    emb_fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    emb_fseek(file, 0x100, SEEK_SET);

    if (emb_verbose>1) {
        printf("file length: %d\n", fileLength);
    }

    while (fread(data, 1, 3, file) == 3) {
        if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
            break;
        }
        if ((data[0] & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((data[0] & 0x1f) == 1) {
            flags = JUMP;
        } else if ((data[0] & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((data[0] & 0x20) > 0);
        negativeY = ((data[0] & 0x40) > 0);

        dx = (char) data[2];
        dy = (char) data[1];
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeU01(EmbPattern* pattern, void* file)
{
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeU01 */
}

/*
 * Pfaff Embroidery Format (.vip). The vip format is stitch-only.
 */

const unsigned char vipDecodingTable[] = {
    0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC, 0xFD, 0xAA, 0x8A, 0x4E,
    0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4, 0x95, 0xF0, 0x3E, 0xEF,
    0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1, 0x3A, 0x07, 0xFB, 0xCB,
    0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91, 0xD6, 0x0A, 0x5D, 0xD6,
    0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28, 0xF7, 0x5D, 0x70, 0x5E,
    0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB, 0x40, 0xC9, 0xB4, 0x00,
    0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89, 0xAF, 0xE8, 0x85, 0x4F,
    0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58, 0x1E, 0xD6, 0x84, 0x3C,
    0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC, 0xB9, 0x3D, 0x40, 0x4D,
    0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7, 0xC9, 0xC9, 0x43, 0xE4,
    0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E, 0xBD, 0x69, 0x06, 0x2A,
    0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2, 0xD6, 0xF9, 0x9A, 0x75,
    0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F, 0xD8, 0xDE, 0x33, 0xFE,
    0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66, 0x76, 0xF2, 0x5B, 0xC9,
    0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53, 0x03, 0x3B, 0x97, 0x4B,
    0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57, 0x81, 0x5D, 0x56, 0x8D,
    0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1, 0x0E, 0x96, 0x4F, 0xA1,
    0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F, 0x74, 0x20, 0x55, 0x1F,
    0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73, 0xDE, 0x01, 0xB1, 0x80,
    0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33, 0x25, 0xE2, 0x0E, 0x7A,
    0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A, 0x0E, 0xDA, 0xED, 0x6F,
    0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78, 0xE4, 0xAB, 0x6D, 0xFF,
    0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC, 0xED, 0x8F, 0x6C, 0x18,
    0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7, 0x0A, 0x14, 0x0A, 0x6B,
    0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B, 0xB5, 0x83, 0x9B, 0x37
};

int
vipDecodeByte(unsigned char b)
{
    if (b >= 0x80) return (-(unsigned char) (~b + 1));
    return b;
}

int
vipDecodeStitchType(unsigned char b)
{
    switch (b) {
        case 0x80:
            return NORMAL;
        case 0x81:
            return TRIM;
        case 0x84:
            return STOP;
        case 0x90:
            return END;
        default:
            return NORMAL;
    }
}

unsigned char*
vipDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    unsigned char* decompressedData = (unsigned char*)malloc(decompressedContentLength);
    if (!decompressedData) {
        printf("ERROR: format-vip.c vipDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    hus_decompress((char*)input, compressedInputLength, (char *)decompressedData, &decompressedContentLength);
    return decompressedData;
}

char
readVip(EmbPattern* pattern, void* file)
{
    int fileLength;
    int i;
    unsigned char prevByte = 0;
    unsigned char *attributeData = 0, *decodedColors = 0;
    unsigned char *attributeDataDecompressed = 0;
    unsigned char *xData = 0, *xDecompressed = 0, *yData = 0, *yDecompressed = 0;
    VipHeader header;

    fileLength = check_header_present(file, 32);
    if (!fileLength) {
        printf("ERROR: file shorter than header.");
        return 0;
    }

    emb_read(file, &(header.magicCode), EMB_INT32_LITTLE);
    emb_read(file, &(header.numberOfStitches), EMB_INT32_LITTLE);
    emb_read(file, &(header.numberOfColors), EMB_INT32_LITTLE);

    emb_read(file, &(header.postitiveXHoopSize), EMB_INT16_LITTLE);
    emb_read(file, &(header.postitiveYHoopSize), EMB_INT16_LITTLE);
    emb_read(file, &(header.negativeXHoopSize), EMB_INT16_LITTLE);
    emb_read(file, &(header.negativeYHoopSize), EMB_INT16_LITTLE);
    emb_read(file, &(header.attributeOffset), EMB_INT32_LITTLE);
    emb_read(file, &(header.xOffset), EMB_INT32_LITTLE);
    emb_read(file, &(header.yOffset), EMB_INT32_LITTLE);

    emb_fread(header.stringVal, 8, file); /* TODO: check return value */

    emb_read(file, &(header.unknown), EMB_INT16_LITTLE);

    emb_read(file, &(header.colorLength), EMB_INT32_LITTLE);
    decodedColors = (unsigned char*)malloc(header.numberOfColors*4);
    if (!decodedColors) {
        printf("ERROR: format-vip.c readVip(), ");
        printf("cannot allocate memory for decodedColors\n");
        return 0;
    }
    for (i = 0; i < header.numberOfColors*4; ++i) {
        unsigned char inputByte = (char)fgetc(file);
        unsigned char tmpByte = (unsigned char) (inputByte ^ vipDecodingTable[i]);
        decodedColors[i] = (unsigned char) (tmpByte ^ prevByte);
        prevByte = inputByte;
    }
    for (i = 0; i < header.numberOfColors; i++) {
        EmbThread thread;
        int startIndex = i << 2;
        thread.color.r = decodedColors[startIndex];
        thread.color.g = decodedColors[startIndex + 1];
        thread.color.b = decodedColors[startIndex + 2];
        /* printf("%d\n", decodedColors[startIndex + 3]); */
        emb_pattern_addThread(pattern, thread);
    }
    emb_fseek(file, header.attributeOffset, SEEK_SET);
    attributeData = (unsigned char*)malloc(header.xOffset - header.attributeOffset);
    if (!attributeData) {
        printf("ERROR: format-vip.c readVip(), cannot allocate memory for attributeData\n");
        return 0;
    }
    emb_fread(attributeData, header.xOffset - header.attributeOffset, file); /* TODO: check return value */
    attributeDataDecompressed = vipDecompressData(attributeData, header.xOffset - header.attributeOffset, header.numberOfStitches);

    emb_fseek(file, header.xOffset, SEEK_SET);
    xData = (unsigned char*)malloc(header.yOffset - header.xOffset);
    if (!xData) {
        printf("ERROR: format-vip.c readVip(), cannot allocate memory for xData\n");
        return 0;
    }
    emb_fread(xData, header.yOffset - header.xOffset, file); /* TODO: check return value */
    xDecompressed = vipDecompressData(xData, header.yOffset - header.xOffset, header.numberOfStitches);

    emb_fseek(file, header.yOffset, SEEK_SET);
    yData = (unsigned char*)malloc(fileLength - header.yOffset);
    if (!yData) { printf("ERROR: format-vip.c readVip(), cannot allocate memory for yData\n"); return 0; }
    emb_fread(yData, fileLength - header.yOffset, file); /* TODO: check return value */
    yDecompressed = vipDecompressData(yData, fileLength - header.yOffset, header.numberOfStitches);

    for (i = 0; i < header.numberOfStitches; i++) {
        emb_pattern_addStitchRel(pattern,
                    vipDecodeByte(xDecompressed[i]) / 10.0,
                    vipDecodeByte(yDecompressed[i]) / 10.0,
                    vipDecodeStitchType(attributeDataDecompressed[i]), 1);
    }
    emb_pattern_addStitchRel(pattern, 0, 0, END, 1);

    safe_free(attributeData);
    safe_free(xData);
    safe_free(yData);
    safe_free(attributeDataDecompressed);
    safe_free(xDecompressed);
    safe_free(yDecompressed);
    return 1;
}

unsigned char*
vipCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    unsigned char* compressedData = (unsigned char*)malloc(decompressedInputSize*2);
    if (!compressedData) {
        printf("ERROR: format-vip.c vipCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    hus_compress((char*)input, decompressedInputSize, (char *)compressedData, compressedSize);
    return compressedData;
}

unsigned char
vipEncodeByte(EmbReal f)
{
    return (unsigned char)(int)emb_round(f);
}

unsigned char
vipEncodeStitchType(int st)
{
    switch (st) {
        case NORMAL:
            return (0x80);
        case JUMP:
        case TRIM:
            return (0x81);
        case STOP:
            return (0x84);
        case END:
            return (0x90);
        default:
            return (0x80);
    }
}

char
writeVip(EmbPattern* pattern, void* file)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor;
    int attributeSize = 0;
    int xCompressedSize = 0;
    int yCompressedSize = 0;
    EmbReal previousX = 0;
    EmbReal previousY = 0;
    unsigned char* xValues = 0, *yValues = 0, *attributeValues = 0;
    EmbReal xx = 0.0;
    EmbReal yy = 0.0;
    int flags = 0;
    int i = 0;
    unsigned char* attributeCompressed = 0, *xCompressed = 0;
    unsigned char* yCompressed = 0, *decodedColors = 0, *encodedColors = 0;
    unsigned char prevByte = 0;

    puts("VIP not yet implemented.");
    return 0;

    stitchCount = pattern->stitch_list->count;
    minColors = pattern->thread_list->count;
    decodedColors = (unsigned char*)malloc(minColors << 2);
    if (!decodedColors) {
        return 0;
    }
    encodedColors = (unsigned char*)malloc(minColors << 2);
    if (!encodedColors) {
        safe_free(decodedColors);
        return 0;
    }
    /* emb_pattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */

    patternColor = minColors;
    if (emb_verbose>1) {
        printf("patternColor: %d\n", patternColor);
    }
    if (minColors > 24) {
        minColors = 24;
    }
    binaryWriteUInt(file, 0x0190FC5D);
    binaryWriteUInt(file, stitchCount);
    binaryWriteUInt(file, minColors);

    boundingRect = emb_pattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short) emb_round(boundingRect.right * 10.0));
    binaryWriteShort(file, (short) -emb_round(boundingRect.top * 10.0 - 1.0));
    binaryWriteShort(file, (short) emb_round(boundingRect.left * 10.0));
    binaryWriteShort(file, (short) -emb_round(boundingRect.bottom * 10.0 - 1.0));

    binaryWriteUInt(file, 0x38 + (minColors << 3));

    xValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    yValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (xValues && yValues && attributeValues) {
        for (i = 0; i < pattern->stitch_list->count; i++) {
            EmbStitch st;
            st = pattern->stitch_list->stitch[i];
            xx = st.x;
            yy = st.y;
            flags = st.flags;
            xValues[i] = vipEncodeByte((xx - previousX) * 10.0);
            previousX = xx;
            yValues[i] = vipEncodeByte((yy - previousY) * 10.0);
            previousY = yy;
            attributeValues[i] = vipEncodeStitchType(flags);
        }
        attributeCompressed = vipCompressData(attributeValues, stitchCount, &attributeSize);
        xCompressed = vipCompressData(xValues, stitchCount, &xCompressedSize);
        yCompressed = vipCompressData(yValues, stitchCount, &yCompressedSize);

        binaryWriteUInt(file, (unsigned int) (0x38 + (minColors << 3) + attributeSize));
        binaryWriteUInt(file, (unsigned int) (0x38 + (minColors << 3) + attributeSize + xCompressedSize));
        binaryWriteUInt(file, 0x00000000);
        binaryWriteUInt(file, 0x00000000);
        binaryWriteUShort(file, 0x0000);

        binaryWriteInt(file, minColors << 2);

        for (i = 0; i < minColors; i++) {
            int byteChunk = i << 2;
            EmbColor currentColor = pattern->thread_list->thread[i].color;
            decodedColors[byteChunk] = currentColor.r;
            decodedColors[byteChunk + 1] = currentColor.g;
            decodedColors[byteChunk + 2] = currentColor.b;
            decodedColors[byteChunk + 3] = 0x01;
        }

        for (i = 0; i < minColors << 2; ++i) {
            unsigned char tmpByte = (unsigned char) (decodedColors[i] ^ vipDecodingTable[i]);
            prevByte = (unsigned char) (tmpByte ^ prevByte);
            fputc(prevByte, file);
        }
        for (i = 0; i <= minColors; i++) {
            binaryWriteInt(file, 1);
        }
        binaryWriteUInt(file, 0); /* string length */
        binaryWriteShort(file, 0);
        emb_fwrite((char*) attributeCompressed, attributeSize, file);
        emb_fwrite((char*) xCompressed, xCompressedSize, file);
        emb_fwrite((char*) yCompressed, yCompressedSize, file);
    }

    safe_free(attributeCompressed);
    safe_free(xCompressed);
    safe_free(yCompressed);
    safe_free(attributeValues);
    safe_free(xValues);
    safe_free(yValues);
    safe_free(decodedColors);
    safe_free(encodedColors);
    return 1;
}

/*
 * VP3 FORMAT
 * Pfaff Embroidery Format (.vp3)
 *
 * The Pfaff vp3 format is stitch-only.
 */

unsigned char*
vp3ReadString(void* file)
{
    short stringLength;
    unsigned char* charString = 0;
    if (!file) {
        printf("ERROR: format-vp3.c vp3ReadString(), file argument is null\n");
        return 0;
    }
    emb_read(file, &stringLength, EMB_INT16_BIG);
    charString = (unsigned char*)malloc(stringLength);
    if (!charString) {
        printf("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n");
        return 0;
    }
    emb_fread(charString, stringLength, file); /* TODO: check return value */
    return charString;
}

int
vp3Decode(unsigned char inputByte)
{
    if (inputByte > 0x80) {
        return (int)-((unsigned char)((~inputByte) + 1));
    }
    return ((int)inputByte);
}

short
vp3DecodeInt16(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return -((short) ((~inputByte) + 1));
    }
    return ((short)inputByte);
}

vp3Hoop
vp3ReadHoopSection(void* file)
{
    vp3Hoop hoop;

    if (!file) {
        printf("ERROR: format-vp3.c vp3ReadHoopSection(), file argument is null\n");
        hoop.bottom = 0;
        hoop.left = 0;
        hoop.right = 0;
        hoop.top = 0;
        hoop.threadLength = 0;
        hoop.unknown2 = 0;
        hoop.numberOfColors = 0;
        hoop.unknown3 = 0;
        hoop.unknown4 = 0;
        hoop.numberOfBytesRemaining = 0;

        hoop.xOffset = 0;
        hoop.yOffset = 0;

        hoop.byte1 = 0;
        hoop.byte2 = 0;
        hoop.byte3 = 0;
        hoop.right2 = 0;
        hoop.left2 = 0;
        hoop.bottom2 = 0;
        hoop.top2 = 0;
        hoop.height = 0;
        hoop.width = 0;
        return hoop;
    }

    emb_read(file, &(hoop.right), EMB_INT32_BIG);
    emb_read(file, &(hoop.bottom), EMB_INT32_BIG);
    emb_read(file, &(hoop.left), EMB_INT32_BIG);
    emb_read(file, &(hoop.top), EMB_INT32_BIG);

    /* yes, it seems this is _not_ big endian */
    emb_read(file, &(hoop.threadLength), EMB_INT32_LITTLE);
    hoop.unknown2 = (char)fgetc(file);
    hoop.numberOfColors = (char)fgetc(file);
    emb_read(file, &(hoop.unknown3), EMB_INT16_BIG);
    emb_read(file, &(hoop.unknown4), EMB_INT32_BIG);
    emb_read(file, &(hoop.numberOfBytesRemaining), EMB_INT32_BIG);

    emb_read(file, &(hoop.xOffset), EMB_INT32_BIG);
    emb_read(file, &(hoop.yOffset), EMB_INT32_BIG);

    hoop.byte1 = (char)fgetc(file);
    hoop.byte2 = (char)fgetc(file);
    hoop.byte3 = (char)fgetc(file);

    /* Centered hoop dimensions */
    emb_read(file, &(hoop.right2), EMB_INT32_BIG);
    emb_read(file, &(hoop.left2), EMB_INT32_BIG);
    emb_read(file, &(hoop.bottom2), EMB_INT32_BIG);
    emb_read(file, &(hoop.top2), EMB_INT32_BIG);

    emb_read(file, &(hoop.width), EMB_INT32_BIG);
    emb_read(file, &(hoop.height), EMB_INT32_BIG);
    return hoop;
}

char
readVp3(EmbPattern* pattern, void* file)
{
    unsigned char magicString[5];
    unsigned char some;
    unsigned char* softwareVendorString = 0;
    /* unsigned char v2, ..., v18; */
    unsigned char* anotherSoftwareVendorString = 0;
    int numberOfColors;
    long colorSectionOffset;
    unsigned char magicCode[6];
    short someShort;
    unsigned char someByte;
    int bytesRemainingInFile, hoopConfigurationOffset;
    unsigned char* fileCommentString = 0; /* some software writes used settings here */
    unsigned char* anotherCommentString = 0;
    int i;

    emb_fread(magicString, 5, file); /* %vsm% */ /* TODO: check return value */
    some = (char)fgetc(file); /* 0 */
    softwareVendorString = vp3ReadString(file);
    emb_read(file, &someShort, EMB_INT16_LITTLE);
    someByte = (char)fgetc(file);
    emb_read(file, &bytesRemainingInFile, EMB_INT32_LITTLE);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)ftell(file);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    for (i = 0; i < 18; i++) {
        unsigned char v1;
        v1 = (char)fgetc(file);
        if (emb_verbose>1) {
            printf("v%d = %d\n", i, v1);
        }
    }

    /* TODO: check return value */
    /* 0x78 0x78 0x55 0x55 0x01 0x00 */
    emb_fread(magicCode, 6, file);

    anotherSoftwareVendorString = vp3ReadString(file);

    emb_read(file, &numberOfColors, EMB_INT16_BIG);
    colorSectionOffset = (int)ftell(file);
    if (emb_verbose>1) {
        puts("LIBEMBROIDERY DEBUG");
        puts("Format vp3");
        printf("    some: %d\n", some);
        printf("    softwareVendorString: %s\n", softwareVendorString);
        printf("    someByte: %d\n", someByte);
        printf("    bytesRemainingInFile: %d\n", bytesRemainingInFile);
        printf("    hoop config offset: %d\n", hoopConfigurationOffset);
        printf("    another comment string: %s\n", anotherCommentString);
        printf("    another software vendor string: %s\n", anotherSoftwareVendorString);
        printf("    number of colors: %d\n", numberOfColors);
        printf("    color section offset: %ld\n", colorSectionOffset);
    }

    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        char tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        unsigned char* threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString, numberOfBytesInColor;

        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        emb_fseek(file, colorSectionOffset, SEEK_SET);
        printf("ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n", (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n", (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n", (char)fgetc(file));
        emb_read(file, &colorSectionOffset, EMB_INT32_BIG);
        colorSectionOffset += ftell(file);
        emb_read(file, &startX, EMB_INT32_BIG);
        emb_read(file, &startY, EMB_INT32_BIG);
        emb_pattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = (char)fgetc(file);
        emb_fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        emb_pattern_addThread(pattern, t);
        emb_fseek(file, 6*tableSize - 1, SEEK_CUR);

        threadColorNumber = vp3ReadString(file);
        colorName = vp3ReadString(file);
        threadVendor = vp3ReadString(file);

        emb_read(file, &offsetToNextColorX, EMB_INT32_BIG);
        emb_read(file, &offsetToNextColorY, EMB_INT32_BIG);

        emb_read(file, &unknownThreadString, EMB_INT16_BIG);
        emb_fseek(file, unknownThreadString, SEEK_CUR);
        emb_read(file, &numberOfBytesInColor, EMB_INT32_BIG);
        emb_fseek(file, 0x3, SEEK_CUR);

        if (emb_verbose>1) {
            printf("number of bytes in color: %d\n", numberOfBytesInColor);
            printf("thread color number: %s\n", threadColorNumber);
            printf("offset to next color x: %d\n", offsetToNextColorX);
            printf("offset to next color y: %d\n", offsetToNextColorY);
            printf("color name: %s\n", colorName);
            printf("thread vendor: %s\n", threadVendor);
            printf("fileCommentString: %s\n", fileCommentString);
        }

        while (ftell(file) < colorSectionOffset - 1) {
            int lastFilePosition = ftell(file);
            int x = vp3Decode((char)fgetc(file));
            int y = vp3Decode((char)fgetc(file));
            short readIn;
            if (x == 0x80) {
                switch (y) {
                    case 0x00:
                    case 0x03:
                        break;
                    case 0x01:
                        emb_read(file, &readIn, EMB_INT16_BIG);
                        x = vp3DecodeInt16(readIn);
                        emb_read(file, &readIn, EMB_INT16_BIG);
                        y = vp3DecodeInt16(readIn);
                        emb_fseek(file, 2, SEEK_CUR);
                        emb_pattern_addStitchRel(pattern, x/ 10.0, y / 10.0, TRIM, 1);
                        break;
                    default:
                        break;
                }
            } else {
                emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
            }

            if (ftell(file) == lastFilePosition) {
                printf("ERROR: format-vp3.c could not read stitch block in entirety\n");
                return 0;
            }
        }
        if (i + 1 < numberOfColors) {
            emb_pattern_addStitchRel(pattern, 0, 0, STOP, 1);
        }
    }
    emb_pattern_flipVertical(pattern);
    return 1;
}

void
vp3WriteStringLen(void* file, const char* str, int len)
{
    binaryWriteUShortBE(file, len);
    emb_fwrite(str, len, file);
}

void
vp3WriteString(void* file, const char* str)
{
    vp3WriteStringLen(file, str, string_len(str));
}

void
vp3PatchByteCount(void* file, int offset, int adjustment)
{
    int currentPos = ftell(file);
    emb_fseek(file, offset, SEEK_SET);
    printf("Patching byte count: %d\n", currentPos - offset + adjustment);
    binaryWriteIntBE(file, currentPos - offset + adjustment);
    emb_fseek(file, currentPos, SEEK_SET);
}

char
writeVp3(EmbPattern* pattern, void* file)
{
    short a;
    EmbRect bounds;
    int a_int, remainingBytesPos, remainingBytesPos2;
    int colorSectionStitchBytes, first = 1, i, numberOfColors;
    EmbColor color;
    color.r = 0xFE;
    color.g = 0xFE;
    color.b = 0xFE;

    bounds = emb_pattern_calcBoundingBox(pattern);

    emb_pattern_correctForMaxStitchLength(pattern, 3200.0, 3200.0); /* VP3 can encode signed 16bit deltas */

    emb_pattern_flipVertical(pattern);

    emb_fwrite("%vsm%\0", 6, file);
    vp3WriteString(file, "Embroidermodder");
    emb_fwrite("\x00\x02\x00", 3, file);

    remainingBytesPos = ftell(file);
    binaryWriteInt(file, 0); /* placeholder */
    vp3WriteString(file, "");
    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);
    binaryWriteInt(file, 0); /* this would be some (unknown) function of thread length */
    fputc(0, file);

    numberOfColors = emb_pattern_color_count(pattern, color);
    fputc(numberOfColors, file);
    emb_fwrite("\x0C\x00\x01\x00\x03\x00", 6, file);

    remainingBytesPos2 = ftell(file);
    binaryWriteInt(file, 0); /* placeholder */

    binaryWriteIntBE(file, 0); /* origin X */
    binaryWriteIntBE(file, 0); /* origin Y */
    fpad(file, 0, 3);

    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);

    binaryWriteIntBE(file, (bounds.right - bounds.left) * 1000);
    binaryWriteIntBE(file, (bounds.bottom - bounds.top) * 1000);

    vp3WriteString(file, "");
    a = 25700;
    emb_write(file, &a, EMB_INT16_BIG);
    a_int = 4096;
    emb_write(file, &a_int, EMB_INT32_BIG);
    a_int = 0;
    emb_write(file, &a_int, EMB_INT32_BIG);
    emb_write(file, &a_int, EMB_INT32_BIG);
    a_int = 4096;
    emb_write(file, &a_int, EMB_INT32_BIG);

    emb_fwrite("xxPP\x01\0", 6, file);
    vp3WriteString(file, "");
    emb_write(file, &numberOfColors, EMB_INT16_BIG);

    for (i=0; i<pattern->stitch_list->count; i++) {
        char colorName[8] = { 0 };
        EmbReal lastX, lastY;
        int colorSectionLengthPos, j;
        EmbStitch s;
        int lastColor;

        j = 0;
        s.x = 0.0;
        s.y = 0.0;
        s.color = 0;
        s.flags = 0;

        if (!first) {
            fputc(0, file);
        }
        fputc(0, file);
        fputc(5, file);
        fputc(0, file);

        colorSectionLengthPos = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        /*
        pointer = mainPointer;
        color = pattern->thread_list->thread[pointer->stitch.color].color;

        if (first && pointer->stitch.flags & JUMP && pointer->next->stitch.flags & JUMP) {
            pointer = pointer->next;
        }

        s = pointer->stitch;
        */
        if (emb_verbose>1) {
            printf("%d\n", j);
            printf("format-vp3.c DEBUG %d, %f, %f\n", s.flags, s.x, s.y);
        }
        binaryWriteIntBE(file, s.x * 1000);
        binaryWriteIntBE(file, -s.y * 1000);
        /* pointer = pointer->next; */

        first = 0;

        lastX = s.x;
        lastY = s.y;
        lastColor = s.color;
        if (emb_verbose>1) {
            printf("last %f %f %d\n", lastX, lastY, lastColor);
        }

        emb_fwrite("\x01\x00", 2, file);

        printf("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n", color.r, color.g, color.b);
        embColor_write(file, color, 4);

        emb_fwrite("\x00\x00\x05", 3, file);
        fputc(40, file);

        vp3WriteString(file, "");

        sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        binaryWriteIntBE(file, 0);
        binaryWriteIntBE(file, 0);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        fputc(10, file);
        fputc(246, file);
        fputc(0, file);

        /*
        for (j=i; j<pattern->stitch_list->count; j++) {
        while (pointer) {
            short dx, dy;

            EmbStitch s = pointer->stitch;
            if (s.color != lastColor) {
                break;
            }
            if (s.flags & END || s.flags & STOP) {
                break;
            }
            dx = (s.x - lastX) * 10;
            dy = (s.y - lastY) * 10;
            // output is in ints, ensure rounding errors do not sum up.
            lastX = lastX + dx / 10.0;
            lastY = lastY + dy / 10.0;

            if (dx < -127 || dx > 127 || dy < -127 || dy > 127) {
                fputc(128, file);
                fputc(1, file);
                emb_write(file, &dx, EMB_INT16_BIG);
                emb_write(file, &dy, EMB_INT16_BIG);
                fputc(128, file);
                fputc(2, file);
            }
            else {
                char b[2];
                b[0] = dx;
                b[1] = dy;
                emb_fwrite(b, 2, file);
            }

            pointer = pointer->next;
        }
        */

        vp3PatchByteCount(file, colorSectionStitchBytes, -4);
        vp3PatchByteCount(file, colorSectionLengthPos, -3);

        /* mainPointer = pointer; */
    }

    vp3PatchByteCount(file, remainingBytesPos2, -4);
    vp3PatchByteCount(file, remainingBytesPos, -4);

    emb_pattern_flipVertical(pattern);
    return 0;
}

/*
 * Singer Embroidery Format (.xxx)
 * The Singer xxx format is stitch-only.
 */

char
xxxDecodeByte(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

char
readXxx(EmbPattern* pattern, void* file)
{
    int dx = 0, dy = 0, numberOfColors, paletteOffset, i;
    char thisStitchJump = 0;

    if (emb_verbose>1) {
        puts("readXxx has been overridden.");
        return 0;
    }

    emb_fseek(file, 0x27, SEEK_SET);
    emb_read(file, &numberOfColors, EMB_INT16_LITTLE);
    emb_fseek(file, 0xFC, SEEK_SET);
    emb_read(file, &paletteOffset, EMB_INT32_LITTLE);
    emb_fseek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        string_copy(thread.catalogNumber, "NULL");
        string_copy(thread.description, "NULL");
        emb_fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(thread.color), 3);
        emb_pattern_addThread(pattern, thread);
    }
    emb_fseek(file, 0x100, SEEK_SET);

    for (i = 0; !feof(file) && ftell(file) < paletteOffset; i++) {
        unsigned char b0, b1;
        int flags;
        flags = NORMAL;
        if (thisStitchJump) flags = TRIM;
        thisStitchJump = 0;
        b0 = (char)fgetc(file);
        b1 = (char)fgetc(file);
        /* TODO: ARE THERE OTHER BIG JUMP CODES? */
        if (b0 == 0x7E || b0 == 0x7D) {
            dx = b1 + ((char)fgetc(file) << 8);
            dx = ((short) dx);
            dy = fread_int16(file);
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
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    /* TODO: check end of pattern for multiple STOPs */
    return 1;
}

void
xxxEncodeStop(void* file, EmbStitch s)
{
    fputc((unsigned char)0x7F, file);
    fputc((unsigned char)(s.color + 8), file);
}

void
xxxEncodeStitch(void* file, EmbReal deltaX, EmbReal deltaY, int flags)
{
    if ((flags & (JUMP | TRIM)) && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        fputc(0x7E, file);
        /* Does this cast work right? */
        binaryWriteShort(file, (short)deltaX);
        binaryWriteShort(file, (short)deltaY);
    } else {
        /* TODO: Verify this works after changing this to unsigned char */
        fputc((unsigned char)emb_round(deltaX), file);
        fputc((unsigned char)emb_round(deltaY), file);
    }
}

void
xxxEncodeDesign(void* file, EmbPattern* p)
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

char
writeXxx(EmbPattern* pattern, void* file)
{
    int i;
    EmbRect rect;
    int endOfStitches;
    EmbReal width, height;
    short to_write;
    unsigned int n_stitches;
    unsigned short n_threads;

    emb_pattern_correctForMaxStitchLength(pattern, 124, 127);

    fpad(file, 0, 0x17);
    n_stitches = (unsigned int)pattern->stitch_list->count;
    emb_write(file, &n_stitches, EMB_INT32_LITTLE);

    fpad(file, 0, 0x0C);
    n_threads = (unsigned short)pattern->thread_list->count;
    emb_write(file, &n_threads, EMB_INT16_LITTLE);

    fpad(file, 0, 0x02);

    rect = emb_pattern_calcBoundingBox(pattern);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
    to_write = (short)(width * 10.0);
    emb_write(file, &to_write, EMB_INT16_LITTLE);
    to_write = (short)(height * 10.0);
    emb_write(file, &to_write, EMB_INT16_LITTLE);

    /*TODO: xEnd from start point x=0 */
    to_write = (short)(width / 2.0 * 10);
    emb_write(file, &to_write, EMB_INT16_LITTLE);
    /*TODO: yEnd from start point y=0 */
    to_write = (short)(height / 2.0 * 10);
    emb_write(file, &to_write, EMB_INT16_LITTLE);
    /*TODO: left from start x = 0     */
    to_write = (short)(width / 2.0 * 10);
    emb_write(file, &to_write, EMB_INT16_LITTLE);
    /*TODO: bottom from start y = 0   */
    to_write = (short)(height / 2.0 * 10);
    emb_write(file, &to_write, EMB_INT16_LITTLE);

    fpad(file, 0, 0xC5);

    /* place holder for end of stitches */
    binaryWriteInt(file, 0x0000);
    xxxEncodeDesign(file, pattern);
    endOfStitches = ftell(file);
    emb_fseek(file, 0xFC, SEEK_SET);
    binaryWriteUInt(file, endOfStitches);
    emb_fseek(file, 0, SEEK_END);
    /* is this really correct? */
    emb_fwrite("\x7F\x7F\x03\x14\x00\x00", 6, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        fputc(0x00, file);
        embColor_write(file, c, 3);
    }
    for (i = 0; i < (22 - pattern->thread_list->count); i++) {
        unsigned int padder = 0x01000000;
        emb_write(file, &padder, EMB_INT32_LITTLE);
    }
    emb_fwrite("\x00\x01", 2, file);
    return 1;
}

/*
 * ZSK FORMAT
 *
 * The ZSK USA Embroidery Format (.zsk)
 * The ZSK USA zsk format is stitch-only.
 */

char
readZsk(EmbPattern* pattern, void* file)
{
    char b[3];
    int stitchType;
    unsigned char colorNumber;

    emb_fseek(file, 0, SEEK_END);
    if (ftell(file) < 0x230) {
        return 0;
    }

    emb_fseek(file, 0x230, SEEK_SET);
    colorNumber = fgetc(file);
    while (colorNumber != 0) {
        EmbThread t;
        embColor_read(file, &(t.color), 3);
        string_copy(t.catalogNumber, "");
        string_copy(t.description, "");
        emb_pattern_addThread(pattern, t);
        emb_fseek(file, 0x48, SEEK_CUR);
        colorNumber = fgetc(file);
    }
    emb_fseek(file, 0x2E, SEEK_CUR);

    while (fread(b, 1, 3, file) == 3) {
        stitchType = NORMAL;
        if (b[0] & 0x04) {
            b[2] = -b[2];
        }
        if (b[0] & 0x08) {
            b[1] = -b[1];
        }
        if (b[0] & 0x02) {
            stitchType = JUMP;
        }
        if (b[0] & 0x20) {
            if (b[1] == 2) {
                stitchType = TRIM;
            } else if (b[1] == -1) {
                break;
            } else {
                if (b[2] != 0) {
                    colorNumber = b[2];
                }
                /* TODO: need to determine what b[1] is used for.*/
                stitchType = STOP;
                emb_pattern_changeColor(pattern, colorNumber - 1);
            }
            b[1] = 0;
            b[2] = 0;
        }
        emb_pattern_addStitchRel(pattern, b[1] / 10.0,
            b[2] / 10.0, stitchType, 0);
    }

    return 1;
}

/* based on the readZsk function */
char
writeZsk(EmbPattern* pattern, void* file)
{
    int i;

    fpad(file, 0x00, 0x230);

    fprintf(file, "%c", pattern->thread_list->count);
    for (i=pattern->thread_list->count; i>0; i--) {
        EmbThread t = pattern->thread_list->thread[i-1];
        embColor_write(file, t.color, 3);
        fpad(file, 0x00, 0x48);
        fprintf(file, "%c", i-1);
    }

    fpad(file, 0x00, 0x2E);

    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbStitch st;
        unsigned char b[3];
        st = pattern->stitch_list->stitch[i];
        b[0] = 0;
        b[1] = st.x;
        b[2] = st.y;
        if (st.flags & JUMP) {
            b[0] |= 0x02;
        }
        if (st.x < 0) {
            b[0] |= 0x08;
            b[1] = -st.x;
        }
        if (st.y < 0) {
            b[0] |= 0x04;
            b[2] = -st.y;
        }
        if (st.flags & TRIM) {
            b[0] |= 0x20;
            b[1] = 0x00;
            b[2] = 0x00;
        }
        if (st.flags & STOP) {
            b[0] |= 0x20;
            b[1] = 0x00;
            b[2] = st.color;
        }
        if (st.flags & END) {
            b[0] |= 0x20;
            b[1] = 0x80;
            b[2] = 0x00;
            emb_fwrite(b, 3, file);
            break;
        }
        emb_fwrite(b, 3, file);
    }
    return 1;
}
/*
 * GEOMETRY
 */

/* Our generic object interface backends to each individual type.
 * The caller defines what the type is.
 */
EmbGeometry *
embGeometry_init(int type_in)
{
    EmbGeometry *obj = (EmbGeometry*)malloc(sizeof(EmbGeometry));
    obj->type = type_in;
    obj->color.r = 0;
    obj->color.g = 0;
    obj->color.b = 0;

    /*
    // QGraphicsItem* parent
    debug_message("BaseObject Constructor()");

    objPen.setCapStyle(RoundCap);
    objPen.setJoinStyle(RoundJoin);
    lwtPen.setCapStyle(RoundCap);
    lwtPen.setJoinStyle(RoundJoin);

    objID = QDateTime::currentMSecsSinceEpoch();
    */

    switch (obj->type) {
    case EMB_ARC: {
        obj->object.arc = emb_arc_init();
        /*
        emb_arc_init(EmbArc arc_in, unsigned int rgb, int lineType)
        arc = arc_in;

        setFlag(ItemIsSelectable, true);

        calculateArcData(arc);

        setColor(rgb);
        setLineType(lineType);
        setLineWeight(0.35); //TODO: pass in proper lineweight
        setPen(objPen);
        */
        break;
    }
    }
    return obj;
}

/* Free the memory occupied by a non-stitch geometry object.
 *
 * Pointer to geometry memory.
 */
void
embGeometry_free(EmbGeometry *obj)
{
    switch (obj->type) {
    case EMB_ARC: {
        return;
    }
    case EMB_CIRCLE: {
        return;
    }
    case EMB_ELLIPSE: {
        return;
    }
    default:
        return;
    }
}

/* Translate a obj by the vector a delta.
 *
 * obj A pointer to the geometry memory.
 * delta A vector in the 0.1mm scale to offset the geometry by.
 */
void
embGeometry_move(EmbGeometry *obj, EmbVector delta)
{
    switch (obj->type) {
    case EMB_ARC: {
        EmbArc *arc = &(obj->object.arc);
        arc->start = emb_vector_add(arc->start, delta);
        arc->mid = emb_vector_add(arc->mid, delta);
        arc->end = emb_vector_add(arc->end, delta);
        return;
    }
    case EMB_CIRCLE: {
        EmbCircle *circle = &(obj->object.circle);
        circle->center = emb_vector_add(circle->center, delta);
        return;
    }
    default:
        break;
    }
}

/* Calculate the bounding box of geometry a obj based on what kind of
 * geometric object it is.
 *
 * obj A pointer to the geometry memory.
 * Returns an EmbRect, the bounding box in the same scale as the input geometry.
 *
 * In the case of a failure the bounding box returned is always the unit square
 * with top left corner at (0, 0).
 */
EmbRect
embGeometry_boundingRect(EmbGeometry *obj)
{
    EmbRect r;
    if (obj->type == EMB_ARC) {
        /*
        arcRect.setWidth(radius*2.0);
        arcRect.setHeight(radius*2.0);
        arcRect.moveCenter(EmbVector(0,0));
        setRect(arcRect);
        */
    }
    r.top = 0.0;
    r.left = 0.0;
    r.bottom = 1.0;
    r.right = 1.0;
    /*
    "Base"
    //If gripped, force this object to be drawn even if it is offscreen
    if (objectRubberMode() == OBJ_RUBBER_GRIP)
        return scene()->sceneRect();
    return path().boundingRect();
    */
    return r;
}

/* Toggle the rubber mode of the object.
 *
 * \todo Review. This could be controlled by a simple flag.
 */
void
embGeometry_vulcanize(EmbGeometry *obj)
{
    switch (obj->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_DIM_LEADER:
    case EMB_ELLIPSE:
    case EMB_IMAGE:
    case EMB_LINE:
    case EMB_POINT:
    case EMB_RECT:
    case EMB_TEXT_SINGLE:
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);
        */
        break;
    default:
        break;
    }
    if (obj->type == EMB_PATH) {
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);

        if (!normalPath.elementCount())
            critical_messagebox(0, translate("Empty Path Error"), translate("The path added contains no points. The command that created this object has flawed logic."));
        */
    }
    if (obj->type == EMB_POLYGON) {
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);

        if (!normalPath.elementCount())
            critical_messagebox(0, translate("Empty Polygon Error"), translate("The polygon added contains no points. The command that created this object has flawed logic."));
        */
    }
    if (obj->type == EMB_POLYLINE) {
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);

        if (!normalPath.elementCount())
            critical_messagebox(0, translate("Empty embPolyline Error"), translate("The embPolyline added contains no points. The command that created this object has flawed logic."));
        */
    }
}

/*
 * ARC GEOMETRY
 *
 * ------------------------------------------------------------
 *
 * The EmbArc is implicitly an elliptical arc not a circular one
 * because of our need to cover all of the SVG spec. Note that
 * the circlar arcs are a subset of the elliptical arcs.
 *
 * TODO: some of these formulae may assume that the arc is circular,
 * correct for elliptic versions.
 *
 * Returns an EmbArcObject. It is created on the stack.
 *
 * Note that the default arc is the semicircular arc of the circle of radius
 * arc.
 */
EmbArc
emb_arc_init(void)
{
    EmbArc arc;
    arc.start.x = 0.0;
    arc.start.y = -1.0;
    arc.mid.x = 1.0;
    arc.mid.y = 0.0;
    arc.end.x = 0.0;
    arc.end.y = 1.0;
    return arc;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise.
 */
char
emb_arc_clockwise(EmbArc arc)
{
    EmbReal edge1 = (arc.mid.x-arc.start.x)*(arc.mid.y+arc.start.y);
    EmbReal edge2 = (arc.end.x-arc.mid.x)*(arc.end.y+arc.mid.y);
    EmbReal edge3 = (arc.start.x-arc.end.x)*(arc.start.y+arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates the CenterPoint of the Arc */
EmbVector
emb_arc_center(EmbArc arc)
{
    EmbVector center;
    EmbVector a_vec, b_vec, aMid_vec, bMid_vec, aPerp_vec, bPerp_vec, pa, pb;
    EmbLine line1, line2;
    EmbReal paAngleInRadians, pbAngleInRadians;
    a_vec = emb_vector_subtract(arc.mid, arc.start);
    aMid_vec = emb_vector_average(arc.mid, arc.start);

    paAngleInRadians = emb_vector_angle(a_vec) + (embConstantPi/2.0);
    pa = emb_vector_unit(paAngleInRadians);
    aPerp_vec = emb_vector_add(aMid_vec, pa);

    b_vec = emb_vector_subtract(arc.end, arc.mid);
    bMid_vec = emb_vector_average(arc.end, arc.mid);

    pbAngleInRadians = emb_vector_angle(b_vec) + (embConstantPi/2.0);
    pb = emb_vector_unit(pbAngleInRadians);
    bPerp_vec = emb_vector_add(bMid_vec, pb);

    line1.start = aMid_vec;
    line1.end = aPerp_vec;
    line2.start = bMid_vec;
    line2.end = bPerp_vec;
    center = emb_line_intersectionPoint(line1, line2);
    if (emb_error) {
        puts("ERROR: no intersection, cannot find arcCenter.");
    }
    return center;
}

/* Calculate the Radius */
EmbReal
emb_arc_radius(EmbArc arc)
{
    EmbReal incAngle = emb_arc_incAngle(arc);
    EmbReal chord = emb_arc_chord(arc);
    return fabs(chord / (2.0 * sin(incAngle / 2.0)));
}

/* Calculate the Diameter */
EmbReal
emb_arc_diameter(EmbArc arc)
{
    return fabs(emb_arc_radius(arc) * 2.0);
}

/* Calculate the Chord Angle (from arc.start to arc.end). */
EmbReal
emb_arc_chordAngle(EmbArc arc)
{
    EmbVector delta = emb_vector_subtract(arc.end, arc.start);
    return atan2(delta.y, delta.x);
}

/* . */
EmbReal
emb_arc_chord(EmbArc arc)
{
    return emb_vector_distance(arc.start, arc.end);
}

/* Calculate the Chord MidPoint. */
EmbVector
emb_arc_chordMid(EmbArc arc)
{
    return emb_vector_scale(emb_vector_add(arc.start, arc.end), 0.5);
}

/* Calculate the Sagitta. */
EmbReal
emb_arc_sagitta(EmbArc arc)
{
    EmbReal chord = emb_arc_chord(arc);
    EmbReal bulge = emb_arc_bulge(arc);
    return fabs((chord / 2.0) * bulge);
}

/* Calculate the Apothem */
EmbReal
emb_arc_apothem(EmbArc arc)
{
    return fabs(emb_arc_radius(arc) - emb_arc_sagitta(arc));
}

/* Calculate the Included Angle. */
EmbReal
emb_arc_incAngle(EmbArc arc)
{
    return atan(emb_arc_bulge(arc))*4.0;
}

/* TODO: fixme */
EmbReal
emb_arc_bulge(EmbArc arc)
{
    return 1.0;
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data.
    Calculate the Sagitta Angle (from chordMid to arcMid)
    if (*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    Calculate the Arc MidPoint
    fx = emb_arc_sagitta(arc) * cos(sagittaAngleInRadians);
    fy = emb_arc_sagitta(arc) * sin(sagittaAngleInRadians);
    arc->mid.x = *chordMidX + fx;
    arc->mid.y = *chordMidY + fy;

    Convert the Included Angle from Radians to Degrees
    *incAngleInDegrees = degrees(incAngleInRadians);

    return 1;
}
 */

void
emb_arc_setCenter(EmbArc *arc, EmbVector point)
{
    EmbVector delta;
    EmbVector old_center = emb_arc_center(*arc);
    delta = emb_vector_subtract(point, old_center);
    arc->start = emb_vector_add(arc->start, delta);
    arc->mid = emb_vector_add(arc->mid, delta);
    arc->end = emb_vector_add(arc->end, delta);
}

void
emb_arc_setRadius(EmbArc *arc, float radius)
{
    EmbVector delta;
    float rad;
    if (radius <= 0.0f) {
        rad = 0.0000001f;
    }
    else {
        rad = radius;
    }

    EmbVector center = emb_arc_center(*arc);
    EmbReal delta_length;

    delta = emb_vector_subtract(arc->start, center);
    delta_length = emb_vector_length(delta);
    delta = emb_vector_scale(delta, rad/delta_length);
    arc->start = emb_vector_add(center, delta);

    delta = emb_vector_subtract(arc->mid, center);
    delta_length = emb_vector_length(delta);
    delta = emb_vector_scale(delta, rad/delta_length);
    arc->mid = emb_vector_add(center, delta);

    delta = emb_vector_subtract(arc->end, center);
    delta_length = emb_vector_length(delta);
    delta = emb_vector_scale(delta, rad/delta_length);
    arc->end = emb_vector_add(center, delta);
}

void
emb_arc_setStartAngle(EmbArc *arc, float angle)
{
    printf("%f %f", arc->start.x, angle);
    //TODO: ArcObject setStartAngle
}

void
emb_arc_setEndAngle(EmbArc *arc, float angle)
{
    printf("%f %f", arc->start.x, angle);
    //TODO: ArcObject setEndAngle
}

EmbReal
emb_arc_startAngle(EmbArc arc)
{
    EmbVector delta;
    EmbVector center = emb_arc_center(arc);
    delta = emb_vector_subtract(arc.end, center);
    float angle = emb_vector_angle(delta);
    return fmodf(angle, 360.0);
}

EmbReal
emb_arc_endAngle(EmbArc arc)
{
    EmbVector delta;
    EmbVector center = emb_arc_center(arc);
    delta = emb_vector_subtract(arc.end, center);
    float angle = emb_vector_angle(delta);
    return fmodf(angle, 360.0);
}

EmbReal
emb_arc_area(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    // Area of a circular segment
    float r = objectRadius();
    float theta = radians(objectIncludedAngle());
    return ((r*r)/2)*(theta - sin(theta));
    */
    return 0.0;
}

EmbReal
emb_arc_arcLength(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    return radians(objectIncludedAngle())*objectRadius();
    */
    return 0.0;
}

EmbReal
emb_arc_includedAngle(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    float chord = objectChord();
    float rad = objectRadius();
    if (chord <= 0 || rad <= 0) return 0; //Prevents division by zero and non-existant circles

    //NOTE: Due to floating point rounding errors, we need to clamp the quotient so it is in the range [-1, 1]
    //      If the quotient is out of that range, then the result of asin() will be NaN.
    float quotient = chord/(2.0*rad);
    if (quotient > 1.0) {
        quotient = 1.0;
    }
    if (quotient < 0.0) {
        quotient = 0.0;
    }
    // NOTE: 0 rather than -1 since we are enforcing a positive chord and radius
    return degrees(2.0*asin(quotient));
    // Properties of a Circle - Get the Included Angle - Reference: ASD9
    */
    return 0.0;
}

char Arc_clockwise()
{
    /*
    // NOTE: Y values are inverted here on purpose
    EmbArc arc2 = arc;
    arc2.start.y *= -1.0;
    arc2.mid.y *= -1.0;
    arc2.end.y *= -1.0;

    return emb_arc_clockwise(arc2);
    */
    return 0;
}

void emb_arc_updatePath(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    float startAngle = (objectStartAngle() + rotation());
    float spanAngle = objectIncludedAngle();

    if (objectClockwise()) {
        spanAngle = -spanAngle;
    }

    QPainterPath path;
    path.arcMoveTo(rect(), startAngle);
    path.arcTo(rect(), startAngle, spanAngle);
    //NOTE: Reverse the path so that the inside area isn't considered part of the arc
    path.arcTo(rect(), startAngle+spanAngle, -spanAngle);
    setPath(path);
    */
}

void emb_arc_paint(void)
{
    // QPainter* painter, QStyleOptionGraphicsItem* option, QWidget* widget
    /*
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    float startAngle = (objectStartAngle() + rotation())*16;
    float spanAngle = objectIncludedAngle()*16;

    if (objectClockwise())
        spanAngle = -spanAngle;

    float rad = objectRadius();
    EmbRect paintRect(-rad, -rad, rad*2.0, rad*2.0);
    painter->drawArc(paintRect, startAngle, spanAngle);
    */
}

void emb_arc_updateRubber(EmbArc arc, int pattern, int layer, int index)
{
    //TODO: Arc Rubber Modes

    //TODO: updateRubber() gripping for ArcObject

}

// Returns the closest snap point to the mouse point
EmbVector emb_arc_mouseSnapPoint(EmbArc arc, EmbVector mousePoint)
{
    printf("%f", arc.start.x);
    printf("%f", mousePoint.x);
    /*
    EmbVector center = objectCenter();
    EmbVector start  = objectStartPoint();
    EmbVector mid    = objectMidPoint();
    EmbVector end    = objectEndPoint();

    float cntrDist  = EmbLine(mousePoint, center).length();
    float startDist = EmbLine(mousePoint, start).length();
    float midDist   = EmbLine(mousePoint, mid).length();
    float endDist   = EmbLine(mousePoint, end).length();

    float minDist = std::min(std::min(cntrDist, startDist), std::min(midDist, endDist));

    if     (minDist == cntrDist)  return center;
    else if (minDist == startDist) return start;
    else if (minDist == midDist)   return mid;
    else if (minDist == endDist)   return end;

    return scenePos();
    */
    return mousePoint;
}

/*
std::vector<EmbVector> emb_arc_allGripPoints(EmbArc arc)
{
    EmbVector center = emb_arc_center(arc);
    std::vector<EmbVector> gripPoints = {center, arc.start, arc.mid, arc.end};
    return gripPoints;
}
*/

void emb_arc_gripEdit(EmbArc *arc, EmbVector before, EmbVector after)
{
    printf("%f %f %f", arc->start.x, before.x, after.x);
    // TODO: gripEdit() for ArcObject
}

void set_object_color(EmbGeometry *obj, EmbColor color)
{
    obj->color = color;
    /*
    objPen.setColor(color);
    lwtPen.setColor(color);
    */
}

void embGeometry_setColorRGB(EmbGeometry *obj, unsigned int rgb)
{
    printf("%d", rgb);
    /*
    objPen.setColor(QColor(rgb));
    lwtPen.setColor(QColor(rgb));
    */
}

void
embGeometry_setLineType(EmbGeometry *obj, int lineType)
{
    printf("%d", lineType);
    /*
    objPen.setStyle(lineType);
    lwtPen.setStyle(lineType);
    */
}

void
embGeometry_setLineWeight(EmbGeometry *obj, float lineWeight)
{
    printf("%f", lineWeight);
    /*
    objPen.setWidthF(0); //NOTE: The objPen will always be cosmetic

    if (lineWeight < 0) {
        if (lineWeight == OBJ_LWT_BYLAYER) {
            lwtPen.setWidthF(0.35); //TODO: getLayerLineWeight
        }
        else if (lineWeight == OBJ_LWT_BYBLOCK) {
            lwtPen.setWidthF(0.35); //TODO: getBlockLineWeight
        }
        else {
            QMessageBox::warning(0, translate("Error - Negative Lineweight"),
                                    translate("Lineweight: %1")
                                    .arg(std::string().setNum(lineWeight)));
            debug_message("Lineweight cannot be negative! Inverting sign.");
            lwtPen.setWidthF(-lineWeight);
        }
    }
    else {
        lwtPen.setWidthF(lineWeight);
    }
    */
}

EmbVector
Base_objectRubberPoint(EmbGeometry *obj, const char *key)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%s", key);
    /*
    if (objRubberPoints.contains(key)) {
        return objRubberPoints.value(key);
    }

    QGraphicsScene* gscene = scene();
    if (gscene) {
        return scene()->property("SCENE_QSNAP_POINT").toPointF();
    }
    */
    return v;
}

const char *
Base_objectRubberText(EmbGeometry *obj, const char *key)
{
    printf("%s", key);
    /*
    if (objRubberTexts.contains(key))
        return objRubberTexts.value(key);
    */
    return "";
}

/*
void embGeometry_drawRubberLine(const EmbLine& rubLine, QPainter* painter, const char* colorFromScene)
{
    if (painter) {
        QGraphicsScene* objScene = scene();
        if (!objScene) return;
        QPen colorPen = objPen;
        colorPen.setColor(QColor(objScene->property(colorFromScene).toUInt()));
        painter->setPen(colorPen);
        painter->drawLine(rubLine);
        painter->setPen(objPen);
    }
}

void embGeometry_realRender(QPainter* painter, const QPainterPath& renderPath)
{
    QColor color1 = objectColor();       //lighter color
    QColor color2  = color1.darker(150); //darker color

    //If we have a dark color, lighten it
    int darkness = color1.lightness();
    int threshold = 32; //TODO: This number may need adjusted or maybe just add it to settings.
    if (darkness < threshold) {
        color2 = color1;
        if (!darkness) { color1 = QColor(threshold, threshold, threshold); } //lighter() does not affect pure black
        else          { color1 = color2.lighter(100 + threshold); }
    }

    int count = renderPath.elementCount();
    for (int i = 0; i < count-1; ++i) {
        QPainterPath::Element elem = renderPath.elementAt(i);
        QPainterPath::Element next = renderPath.elementAt(i+1);

        if (next.isMoveTo()) continue;

        QPainterPath elemPath;
        elemPath.moveTo(elem.x, elem.y);
        elemPath.lineTo(next.x, next.y);

        QPen renderPen(QColor(0,0,0,0));
        renderPen.setWidthF(0);
        painter->setPen(renderPen);
        QPainterPathStroker stroker;
        stroker.setWidth(0.35);
        stroker.setCapStyle(RoundCap);
        stroker.setJoinStyle(RoundJoin);
        QPainterPath realPath = stroker.createStroke(elemPath);
        painter->drawPath(realPath);

        QLinearGradient grad(elemPath.pointAtPercent(0.5), elemPath.pointAtPercent(0.0));
        grad.setColorAt(0, color1);
        grad.setColorAt(1, color2);
        grad.setSpread(QGradient::ReflectSpread);

        painter->fillPath(realPath, QBrush(grad));
    }
}

void emb_circle_main()
{
    initCommand();
    clearSelection();
    view.ui_mode = "CIRCLE_MODE_1P_RAD";
    global.x1 = NaN;
    global.y1 = NaN;
    global.x2 = NaN;
    global.y2 = NaN;
    global.x3 = NaN;
    global.y3 = NaN;
    setPromptPrefix(translate("Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: "));
}
*/

void
emb_circle_prompt(const char *str)
{
    /*
    if (view.ui_mode == "CIRCLE_MODE_1P_RAD") {
        if (std::isnan(global.x1)) {
            if (str == "2P") {
                //TODO: Probably should add additional qsTr calls here.
                view.ui_mode = "CIRCLE_MODE_2P";
                setPromptPrefix(translate("Specify first end point of circle's diameter: "));
            }
            else if (str == "3P") {
                view.ui_mode = "CIRCLE_MODE_3P";
                setPromptPrefix(translate("Specify first point of circle: "));
            }
            else if (str == "T" || str == "TTR")  {
                view.ui_mode = "CIRCLE_MODE_TTR";
                setPromptPrefix(translate("Specify point on object for first tangent of circle: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: "));
                }
                else {
                    global.x1 = Number(strList[0]);
                    global.y1 = Number(strList[1]);
                    global.cx = global.x1;
                    global.cy = global.y1;
                    addRubber("CIRCLE");
                    setRubberMode("CIRCLE_1P_RAD");
                    setRubberPoint("CIRCLE_CENTER", global.cx, global.cy);
                    setPromptPrefix(translate("Specify radius of circle or [Diameter]: "));
                }
            }
        }
        else {
            if (str == "D" || str == "DIAMETER") {
                //TODO: Probably should add additional translate calls here.
                view.ui_mode = "CIRCLE_MODE_1P_DIA";
                setRubberMode("CIRCLE_1P_DIA");
                setPromptPrefix(translate("Specify diameter of circle: "));
            }
            else {
                float num = Number(str);
                if (std::isnan(num)) {
                    alert(translate("Requires numeric radius, point on circumference, or \"D\"."));
                    setPromptPrefix(translate("Specify radius of circle or [Diameter]: "));
                }
                else {
                    global.rad = num;
                    global.x2 = global.x1 + global.rad;
                    global.y2 = global.y1;
                    setRubberPoint("CIRCLE_RADIUS", global.x2, global.y2);
                    vulcanize();
                    endCommand();
                }
            }
        }
    }
    else if (view.ui_mode == MODE_1P_DIA) {
        if (std::isnan(global.x1)) {
            error("CIRCLE", translate("This should never happen."));
        }
        if (std::isnan(global.x2)) {
            float num = Number(str);
            if (std::isnan(num)) {
                alert(translate("Requires numeric distance or second point."));
                setPromptPrefix(translate("Specify diameter of circle: "));
            }
            else {
                global.dia = num;
                global.x2 = global.x1 + global.dia;
                global.y2 = global.y1;
                setRubberPoint("CIRCLE_DIAMETER", global.x2, global.y2);
                vulcanize();
                endCommand();
            }
        }
        else {
            error("CIRCLE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_2P) {
        if (std::isnan(global.x1)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first end point of circle's diameter: "));
            }
            else {
                global.x1 = Number(strList[0]);
                global.y1 = Number(strList[1]);
                addRubber("CIRCLE");
                setRubberMode("CIRCLE_2P");
                setRubberPoint("CIRCLE_TAN1", global.x1, global.y1);
                setPromptPrefix(translate("Specify second end point of circle's diameter: "));
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify second end point of circle's diameter: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                setRubberPoint("CIRCLE_TAN2", global.x2, global.y2);
                vulcanize();
                endCommand();
            }
        }
        else {
            error("CIRCLE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_3P) {
        if (std::isnan(global.x1)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first point of circle: "));
            }
            else {
                global.x1 = Number(strList[0]);
                global.y1 = Number(strList[1]);
                setPromptPrefix(translate("Specify second point of circle: "));
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify second point of circle: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                addRubber("CIRCLE");
                setRubberMode("CIRCLE_3P");
                setRubberPoint("CIRCLE_TAN1", global.x1, global.y1);
                setRubberPoint("CIRCLE_TAN2", global.x2, global.y2);
                setPromptPrefix(translate("Specify third point of circle: "));
            }
        }
        else if (std::isnan(global.x3)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify third point of circle: "));
            }
            else {
                global.x3 = Number(strList[0]);
                global.y3 = Number(strList[1]);
                setRubberPoint("CIRCLE_TAN3", global.x3, global.y3);
                vulcanize();
                endCommand();
            }
        }
        else {
            error("CIRCLE", translate("This should never happen."));
        }

    }
    else if (view.ui_mode == MODE_TTR) {
        todo("CIRCLE", "prompt() for TTR");
    }
    */
}

/*
void emb_circle_CircleObject(EmbVector center, float radius, unsigned int rgb)
{
    if (n_views == 0) {
        return;
    }

    View view = views[settings.pattern_index];

    debug_message("CircleObject Constructor()");
    init(centerX, centerY, radius, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void emb_circle_CircleObject(EmbCircle* obj)
{
    debug_message("CircleObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectRadius(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
    }
}

void emb_circle_init(EmbVector center, float radius, unsigned int rgb, int lineType)
{
    if (n_views == 0) {
        return;
    }

    View view = views[settings.pattern_index];

    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "CIRCLE");

    setFlag(ItemIsSelectable, true);

    setRadius(radius);
    setCenter(centerX, centerY);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
}

void emb_circle_setDiameter(EmbCircle *circle, float diameter)
{
    if (n_views == 0) {
        return;
    }

    View view = views[settings.pattern_index];

    circle->radius = diameter*0.5;
    EmbRect circRect;
    circRect.setWidth(diameter);
    circRect.setHeight(diameter);
    circRect.moveCenter(EmbVector(0,0));
    setRect(circRect);
    updatePath();
}
*/

void emb_circle_setArea(EmbCircle *circle, float area)
{
    circle->radius = sqrt(area / embConstantPi);
}

void emb_circle_setCircumference(EmbCircle *circle, float circumference)
{
    circle->radius = circumference / (2.0*embConstantPi);
}

/*
void emb_circle_updatePath()
{
    QPainterPath path;
    EmbRect r = rect();
    //Add the center point
    path.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    //Add the circle
    path.arcMoveTo(r, 0);
    path.arcTo(r, 0, 360);
    //NOTE: Reverse the path so that the inside area isn't considered part of the circle
    path.arcTo(r, 0, -360);
    setPath(path);
}

void emb_circle_paint(QPainter* painter)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawEllipse(rect());
}

void emb_circle_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_CIRCLE_1P_RAD) {
        EmbVector sceneCenterPoint = objectRubberPoint("CIRCLE_CENTER");
        EmbVector sceneQSnapPoint = objectRubberPoint("CIRCLE_RADIUS");
        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemQSnapPoint = mapFromScene(sceneQSnapPoint);
        EmbLine itemLine(itemCenterPoint, itemQSnapPoint);
        setCenter(sceneCenterPoint);
        EmbLine sceneLine(sceneCenterPoint, sceneQSnapPoint);
        float radius = sceneLine.length();
        setRadius(radius);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_CIRCLE_1P_DIA) {
        EmbVector sceneCenterPoint = objectRubberPoint("CIRCLE_CENTER");
        EmbVector sceneQSnapPoint = objectRubberPoint("CIRCLE_DIAMETER");
        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemQSnapPoint = mapFromScene(sceneQSnapPoint);
        EmbLine itemLine(itemCenterPoint, itemQSnapPoint);
        setCenter(sceneCenterPoint);
        EmbLine sceneLine(sceneCenterPoint, sceneQSnapPoint);
        float diameter = sceneLine.length();
        setDiameter(diameter);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_CIRCLE_2P) {
        EmbVector sceneTan1Point = objectRubberPoint("CIRCLE_TAN1");
        EmbVector sceneQSnapPoint = objectRubberPoint("CIRCLE_TAN2");
        EmbLine sceneLine(sceneTan1Point, sceneQSnapPoint);
        setCenter(sceneLine.pointAt(0.5));
        float diameter = sceneLine.length();
        setDiameter(diameter);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_CIRCLE_3P) {
        EmbVector sceneTan1Point = objectRubberPoint("CIRCLE_TAN1");
        EmbVector sceneTan2Point = objectRubberPoint("CIRCLE_TAN2");
        EmbVector sceneTan3Point = objectRubberPoint("CIRCLE_TAN3");

        float sceneCenterX;
        float sceneCenterY;
        EmbArc arc;
        EmbVector sceneCenter;
        arc.start.x = sceneTan1Point.x();
        arc.start.y = sceneTan1Point.y();
        arc.mid.x = sceneTan2Point.x();
        arc.mid.y = sceneTan2Point.y();
        arc.end.x = sceneTan3Point.x();
        arc.end.y = sceneTan3Point.y();
        emb_arc_center(arc, &sceneCenter);
        EmbVector sceneCenterPoint(sceneCenter.x, sceneCenter.y);
        EmbLine sceneLine(sceneCenterPoint, sceneTan3Point);
        setCenter(sceneCenterPoint);
        float radius = sceneLine.length();
        setRadius(radius);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == objectCenter()) {
                painter->drawEllipse(rect().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));
            }
            else {
                float gripRadius = EmbLine(objectCenter(), objectRubberPoint(std::string())).length();
                painter->drawEllipse(EmbVector(), gripRadius, gripRadius);
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector Circle_mouseSnapPoint(EmbVector& mousePoint)
{
    EmbVector center  = objectCenter();
    EmbVector quad0   = objectQuadrant0();
    EmbVector quad90  = objectQuadrant90();
    EmbVector quad180 = objectQuadrant180();
    EmbVector quad270 = objectQuadrant270();

    float cntrDist = EmbLine(mousePoint, center).length();
    float q0Dist   = EmbLine(mousePoint, quad0).length();
    float q90Dist  = EmbLine(mousePoint, quad90).length();
    float q180Dist = EmbLine(mousePoint, quad180).length();
    float q270Dist = EmbLine(mousePoint, quad270).length();

    float minDist = std::min(std::min(std::min(q0Dist, q90Dist), std::min(q180Dist, q270Dist)), cntrDist);

    if     (minDist == cntrDist) return center;
    else if (minDist == q0Dist)   return quad0;
    else if (minDist == q90Dist)  return quad90;
    else if (minDist == q180Dist) return quad180;
    else if (minDist == q270Dist) return quad270;

    return scenePos();
}
*/

/*
std::vector<EmbVector> Circle_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectCenter() << objectQuadrant0() << objectQuadrant90() << objectQuadrant180() << objectQuadrant270();
    return gripPoints;
}
*/

/*
void emb_circle_gripEdit(EmbVector& before, EmbVector& after)
{
    if (before == objectCenter()) {
        EmbVector delta = after-before;
        moveBy(delta.x(), delta.y());
    }
    else {
        setRadius(EmbLine(objectCenter(), after).length());
    }
}
*/

/*
QPainterPath Circle_objectSavePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.arcMoveTo(r, 0);
    path.arcTo(r, 0, 360);

    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(path);
}
*/

/*
void dim_leader_init(EmbLine line, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Leader Dimension");

    setFlag(ItemIsSelectable, true);

    curved = false;
    filled = true;
    setEndPoint1(x1, y1);
    setEndPoint2(x2, y2);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}
*/

/*
void dimleader_setEndPoint1(EmbVector endPt1)
{
    EmbVector delta;
    EmbVector endPt2 = objectEndPoint2();
    emb_vector_subtract(endPt2, endPt1, &delta);
    setRotation(0);
    setLine(0, 0, dx, dy);
    setPos(endPt1);
    updateLeader();
}
*/

/*
void dimleader_setEndPoint2(EmbVector endPt2)
{
    EmbVector delta;
    EmbVector endPt1 = scenePos();
    emb_vector_subtract(endPt2, endPt1, &delta);
    setRotation(0);
    setLine(0, 0, delta.x, delta.y);
    setPos(endPt1);
    updateLeader();
}
*/

/*
EmbVector dimleader_objectEndPoint1()
{
    return scenePos();
}
*/

/*
EmbVector dimleader_objectEndPoint2()
{
    EmbLine lyne = line();
    float rot = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rot = emb_vector_rotate(point2, alpha);

    return (scenePos() + rot);
}

EmbVector dimleader_objectMidPoint()
{
    EmbVector mp = line().pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);
    return scenePos() + rotMid;
}

float dimleader_objectAngle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

void dimleader_updateLeader()
{
    int arrowStyle = Closed; //TODO: Make this customizable
    float arrowStyleAngle = 15.0; //TODO: Make this customizable
    float arrowStyleLength = 1.0; //TODO: Make this customizable
    float lineStyleAngle = 45.0; //TODO: Make this customizable
    float lineStyleLength = 1.0; //TODO: Make this customizable

    EmbLine lyne = line();
    float angle = lyne.angle();
    EmbVector ap0 = lyne.p1();
    EmbVector lp0 = lyne.p2();

    //Arrow
    EmbLine lynePerp(lyne.pointAt(arrowStyleLength/lyne.length()) ,lp0);
    lynePerp.setAngle(angle + 90);
    EmbLine lyne1(ap0, lp0);
    EmbLine lyne2(ap0, lp0);
    lyne1.setAngle(angle + arrowStyleAngle);
    lyne2.setAngle(angle - arrowStyleAngle);
    EmbVector ap1;
    EmbVector ap2;
    lynePerp.intersects(lyne1, &ap1);
    lynePerp.intersects(lyne2, &ap2);

    //Math Diagram
    //                 .(ap1)                     .(lp1)
    //                /|                         /|
    //               / |                        / |
    //              /  |                       /  |
    //             /   |                      /   |
    //            /    |                     /    |
    //           /     |                    /     |
    //          /      |                   /      |
    //         /       |                  /       |
    //        /+(aSA)  |                 /+(lSA)  |
    // (ap0)./__(aSL)__|__________(lp0)./__(lSL)__|
    //       \ -(aSA)  |                \ -(lSA)  |
    //        \        |                 \        |
    //         \       |                  \       |
    //          \      |                   \      |
    //           \     |                    \     |
    //            \    |                     \    |
    //             \   |                      \   |
    //              \  |                       \  |
    //               \ |                        \ |
    //                \|                         \|
    //                 .(ap2)                     .(lp2)

    if (arrowStyle == Open) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Closed) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Dot) {
        arrowStylePath = QPainterPath();
        arrowStylePath.addEllipse(ap0, arrowStyleLength, arrowStyleLength);
    }
    else if (arrowStyle == Box) {
        arrowStylePath = QPainterPath();
        float side = EmbLine(ap1, ap2).length();
        EmbRect ar0(0, 0, side, side);
        ar0.moveCenter(ap0);
        arrowStylePath.addRect(ar0);
    }
    else if (arrowStyle == Tick) {
    }

    lineStylePath = QPainterPath();
    lineStylePath.moveTo(ap0);
    lineStylePath.lineTo(lp0);
}

void dimleader_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) {
        return;
    }

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected) {
        paintPen.setStyle(Qt::DashLine);
    }
    if (objScene->property("ENABLE_LWT").toBool()) {
        paintPen = lineWeightPen();
    }
    painter->setPen(paintPen);

    painter->drawPath(lineStylePath);
    painter->drawPath(arrowStylePath);

    if (filled) {
        painter->fillPath(arrowStylePath, objectColor());
    }
}

void dimleader_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_DIMLEADER_LINE) {
        EmbVector sceneStartPoint = objectRubberPoint("DIMLEADER_LINE_START");
        EmbVector sceneQSnapPoint = objectRubberPoint("DIMLEADER_LINE_END");

        setEndPoint1(sceneStartPoint);
        setEndPoint2(sceneQSnapPoint);
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == objectEndPoint1())
                painter->drawLine(line().p2(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectEndPoint2())
                painter->drawLine(line().p1(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectMidPoint())
                painter->drawLine(line().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector dimleader_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector endPoint1 = objectEndPoint1();
    EmbVector endPoint2 = objectEndPoint2();
    EmbVector midPoint  = objectMidPoint();

    float end1Dist = EmbLine(mousePoint, endPoint1).length();
    float end2Dist = EmbLine(mousePoint, endPoint2).length();
    float midDist  = EmbLine(mousePoint, midPoint).length();

    float minDist = std::min(end1Dist, end2Dist);

    if (curved)
        minDist = std::min(minDist, midDist);

    if     (minDist == end1Dist) return endPoint1;
    else if (minDist == end2Dist) return endPoint2;
    else if (minDist == midDist)  return midPoint;

    return scenePos();
}

std::vector<EmbVector> embDimLeader_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectEndPoint1() << objectEndPoint2();
    if (curved) {
        gripPoints << objectMidPoint();
    }
    return gripPoints;
}
*/

/*
void embDimLeader_gripEdit(const EmbVector before, const EmbVector after)
{
    if (before == objectEndPoint1()) {
        setEndPoint1(after);
    }
    else if (before == objectEndPoint2()) {
        setEndPoint2(after);
    }
    else if (before == objectMidPoint()) {
        EmbVector delta = emb_vector_subtract(after, before);
        moveBy(delta);
    }
}
*/

void embEllipse_main()
{
    /*
    initCommand();
    clearSelection();
    view.ui_mode = "ELLIPSE_MODE_MAJORDIAMETER_MINORRADIUS";
    global.x1 = NaN;
    global.y1 = NaN;
    global.x2 = NaN;
    global.y2 = NaN;
    global.x3 = NaN;
    global.y3 = NaN;
    setPromptPrefix(translate("Specify first axis start point or [Center]: "));
    */
}

void embEllipse_click(float x, float y)
{
    printf("%f %f", x, y);
    /*
    if (view.ui_mode == MODE_MAJORDIAMETER_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            global.x1 = x;
            global.y1 = y;
            addRubber("ELLIPSE");
            setRubberMode("ELLIPSE_LINE");
            setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
            appendPromptHistory();
            setPromptPrefix(translate("Specify first axis end point: "));
        }
        else if (std::isnan(global.x2)) {
            global.x2 = x;
            global.y2 = y;
            global.cx = (global.x1 + global.x2)/2.0;
            global.cy = (global.y1 + global.y2)/2.0;
            global.width = calculateDistance(global.x1, global.y1, global.x2, global.y2);
            global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
            setRubberMode("ELLIPSE_MAJORDIAMETER_MINORRADIUS");
            setRubberPoint("ELLIPSE_AXIS1_POINT1", global.x1, global.y1);
            setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
            setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
            setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
            setRubberPoint("ELLIPSE_ROT", global.rot, 0);
            appendPromptHistory();
            setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
        }
        else if (std::isnan(global.x3)) {
            global.x3 = x;
            global.y3 = y;
            global.height = perpendicularDistance(global.x3, global.y3, global.x1, global.y1, global.x2, global.y2)*2.0;
            setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
            vulcanize();
            appendPromptHistory();
            endCommand();
        }
        else {
            error("ELLIPSE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_MAJORRADIUS_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            global.x1 = x;
            global.y1 = y;
            global.cx = global.x1;
            global.cy = global.y1;
            addRubber("ELLIPSE");
            setRubberMode("ELLIPSE_LINE");
            setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
            setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
            appendPromptHistory();
            setPromptPrefix(translate("Specify first axis end point: "));
        }
        else if (std::isnan(global.x2)) {
            global.x2 = x;
            global.y2 = y;
            global.width = calculateDistance(global.cx, global.cy, global.x2, global.y2)*2.0;
            global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
            setRubberMode("ELLIPSE_MAJORRADIUS_MINORRADIUS");
            setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
            setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
            setRubberPoint("ELLIPSE_ROT", global.rot, 0);
            appendPromptHistory();
            setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
        }
        else if (std::isnan(global.x3)) {
            global.x3 = x;
            global.y3 = y;
            global.height = perpendicularDistance(global.x3, global.y3, global.cx, global.cy, global.x2, global.y2)*2.0;
            setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
            vulcanize();
            appendPromptHistory();
            endCommand();
        }
        else {
            error("ELLIPSE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_ELLIPSE_ROTATION) {
        if (std::isnan(global.x1)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x2)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x3)) {
            float angle = calculateAngle(global.cx, global.cy, x, y);
            global.height = cos(angle*Math.PI/180.0)*global.width;
            addEllipse(global.cx, global.cy, global.width, global.height, global.rot, false);
            appendPromptHistory();
            endCommand();
        }
    }
    */
}

/*
void prompt(const char *str)
{
    if (mode == MAJORDIAMETER_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            if (str == "C" || str == "CENTER") {
                view.ui_mode = MODE_MAJORRADIUS_MINORRADIUS;
                setPromptPrefix(translate("Specify center point: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify first axis start point or [Center]: "));
                }
                else {
                    global.x1 = Number(strList[0]);
                    global.y1 = Number(strList[1]);
                    addRubber("ELLIPSE");
                    setRubberMode("ELLIPSE_LINE");
                    setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
                    setPromptPrefix(translate("Specify first axis end point: "));
                }
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first axis end point: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                global.cx = (global.x1 + global.x2)/2.0;
                global.cy = (global.y1 + global.y2)/2.0;
                global.width = calculateDistance(global.x1, global.y1, global.x2, global.y2);
                global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
                setRubberMode("ELLIPSE_MAJORDIAMETER_MINORRADIUS");
                setRubberPoint("ELLIPSE_AXIS1_POINT1", global.x1, global.y1);
                setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
                setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
                setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
                setRubberPoint("ELLIPSE_ROT", global.rot, 0);
                setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
            }
        }
        else if (std::isnan(global.x3)) {
            if (str == "R" || str == "ROTATION") {//TODO: Probably should add additional qsTr calls here.
                view.ui_mode = MODE_ELLIPSE_ROTATION;
                setPromptPrefix(translate("Specify rotation: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
                }
                else {
                    global.x3 = Number(strList[0]);
                    global.y3 = Number(strList[1]);
                    global.height = perpendicularDistance(global.x3, global.y3, global.x1, global.y1, global.x2, global.y2)*2.0;
                    setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
                    vulcanize();
                    endCommand();
                }
            }
        }
    }
    else if (mode == MAJORRADIUS_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify center point: "));
            }
            else {
                global.x1 = Number(strList[0]);
                global.y1 = Number(strList[1]);
                global.cx = global.x1;
                global.cy = global.y1;
                addRubber("ELLIPSE");
                setRubberMode("ELLIPSE_LINE");
                setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
                setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
                setPromptPrefix(translate("Specify first axis end point: "));
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first axis end point: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                global.width = calculateDistance(global.x1, global.y1, global.x2, global.y2)*2.0;
                global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
                setRubberMode("ELLIPSE_MAJORRADIUS_MINORRADIUS");
                setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
                setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
                setRubberPoint("ELLIPSE_ROT", global.rot, 0);
                setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
            }
        }
        else if (std::isnan(global.x3)) {
            if (str == "R" || str == "ROTATION") {
                view.ui_mode = MODE_ELLIPSE_ROTATION;
                setPromptPrefix(translate("Specify ellipse rotation: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
                }
                else {
                    global.x3 = Number(strList[0]);
                    global.y3 = Number(strList[1]);
                    global.height = perpendicularDistance(global.x3, global.y3, global.x1, global.y1, global.x2, global.y2)*2.0;
                    setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
                    vulcanize();
                    endCommand();
                }
            }
        }
    }
    else if (view.ui_mode == MODE_ELLIPSE_ROTATION) {
        if (std::isnan(global.x1)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x2)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x3)) {
            if (std::isnan(str)) {
                alert(translate("Invalid angle. Input a numeric angle or pick a point."));
                setPromptPrefix(translate("Specify rotation: "));
            }
            else {
                float angle = Number(str);
                global.height = cos(angle*Math.PI/180.0)*global.width;
                addEllipse(global.cx, global.cy, global.width, global.height, global.rot, false);
                endCommand();
            }
        }
    }
}
*/

/*
void embEllipse_EllipseObject(float centerX, float centerY, float width, float height, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    init(centerX, centerY, width, height, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}
*/

/*
void embEllipse_EllipseObject(EllipseObject* obj, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectWidth(), obj->objectHeight(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
    }
}
*/

/*
void image_init(EmbRect rect, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Image");

    setFlag(ItemIsSelectable, true);

    setRect(rect);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}
*/

/*
void image_setRect(float x, float y, float w, float h)
{
    setPos(x, y);
    setRect(0, 0, w, h);
    updatePath();
}
*/

/*
EmbVector image_objectTopLeft()
{
    float alpha = radians(rotation());
    EmbVector tl = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(tl, alpha);
    return scenePos() + ptlrot;
}
*/

/*
EmbVector image_objectTopRight()
{
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptrrot = emb_vector_rotate(tr, alpha);
    return scenePos() + ptrrot;
}
*/

/*
EmbVector image_objectBottomLeft()
{
    float alpha = radians(rotation());
    EmbVector bl = rect().topRight() * scale();
    EmbVector pblrot = emb_vector_rotate(bl, alpha);
    return scenePos() + pblrot;
}
*/

/*
EmbVector image_objectBottomRight()
{
    float alpha = radians(rotation());
    EmbVector br = rect().topRight() * scale();
    EmbVector pbrrot = emb_vector_rotate(br, alpha);
    return scenePos() + pbrrot;
}
*/

/*
void image_updatePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.moveTo(r.bottomLeft());
    path.lineTo(r.bottomRight());
    path.lineTo(r.topRight());
    path.lineTo(r.topLeft());
    path.lineTo(r.bottomLeft());
    //NOTE: Reverse the path so that the inside area isn't considered part of the rectangle
    path.lineTo(r.topLeft());
    path.lineTo(r.topRight());
    path.lineTo(r.bottomRight());
    path.moveTo(r.bottomLeft());
    setPath(path);
}
*/

/*
void image_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawRect(rect());
}
*/

/*
void image_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_IMAGE) {
        EmbVector sceneStartPoint = objectRubberPoint("IMAGE_START");
        EmbVector sceneEndPoint = objectRubberPoint("IMAGE_END");
        float x = sceneStartPoint.x();
        float y = sceneStartPoint.y();
        float w = sceneEndPoint.x() - sceneStartPoint.x();
        float h = sceneEndPoint.y() - sceneStartPoint.y();
        setRect(x,y,w,h);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        //TODO: updateRubber() gripping for ImageObject
    }
}
*/

/*
// Returns the closest snap point to the mouse point
EmbVector image_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector ptl = objectTopLeft();     //Top Left Corner QSnap
    EmbVector ptr = objectTopRight();    //Top Right Corner QSnap
    EmbVector pbl = objectBottomLeft();  //Bottom Left Corner QSnap
    EmbVector pbr = objectBottomRight(); //Bottom Right Corner QSnap

    float ptlDist = EmbLine(mousePoint, ptl).length();
    float ptrDist = EmbLine(mousePoint, ptr).length();
    float pblDist = EmbLine(mousePoint, pbl).length();
    float pbrDist = EmbLine(mousePoint, pbr).length();

    float minDist = std::min(std::min(ptlDist, ptrDist), std::min(pblDist, pbrDist));

    if     (minDist == ptlDist) return ptl;
    else if (minDist == ptrDist) return ptr;
    else if (minDist == pblDist) return pbl;
    else if (minDist == pbrDist) return pbr;

    return scenePos();
}

std::vector<EmbVector> image_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectTopLeft() << objectTopRight() << objectBottomLeft() << objectBottomRight();
    return gripPoints;
}

void image_gripEdit(const EmbVector& before, const EmbVector& after)
{
    //TODO: gripEdit() for ImageObject
}

[Menu]
Name=Draw
Position=0

[ToolBar]
Name=Draw
Position=0

[Tips]
ToolTip=&Line
StatusTip=Creates straight line segments:  LINE

[Prompt]
Alias=L, LINE

//Command: Line

float global = {}; //Required
global.firstRun;
global.firstX;
global.firstY;
global.prevX;
global.prevY;
*/

/*
void line_main()
{
    initCommand();
    clearSelection();
    global.firstRun = true;
    global.firstX = NaN;
    global.firstY = NaN;
    global.prevX = NaN;
    global.prevY = NaN;
    setPromptPrefix(translate("Specify first point: "));
}
*/

/*
void
line_click(EmbVector p)
{
    if (global.firstRun) {
        global.firstRun = false;
        global.firstX = p.x;
        global.firstY = p.y;
        global.prevX = p.x;
        global.prevY = p.y;
        addRubber("LINE");
        setRubberMode("LINE");
        setRubberPoint("LINE_START", global.firstX, global.firstY);
        appendPromptHistory();
        setPromptPrefix(translate("Specify next point or [Undo]: "));
    }
    else {
        setRubberPoint("LINE_END", x, y);
        vulcanize();
        addRubber("LINE");
        setRubberMode("LINE");
        setRubberPoint("LINE_START", x, y);
        appendPromptHistory();
        global.prevX = x;
        global.prevY = y;
    }
}
*/

/*
void
line_prompt(const char *str)
{
    if (global.firstRun) {
        std::vector<std::string> strList = str.split(",");
        if (std::isnan(strList[0]) || isnan(strList[1])) {
            alert(translate("Invalid point."));
            setPromptPrefix(translate("Specify first point: "));
        }
        else {
            global.firstRun = false;
            global.firstX = Number(strList[0]);
            global.firstY = Number(strList[1]);
            global.prevX = global.firstX;
            global.prevY = global.firstY;
            addRubber("LINE");
            setRubberMode("LINE");
            setRubberPoint("LINE_START", global.firstX, global.firstY);
            setPromptPrefix(translate("Specify next point or [Undo]: "));
        }
    }
    else {
        if (str == "U" || str == "UNDO") {
            todo("LINE", "prompt() for UNDO");
        }
        else {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Point or option keyword required."));
                setPromptPrefix(translate("Specify next point or [Undo]: "));
            }
            else {
                float x = Number(strList[0]);
                float y = Number(strList[1]);
                setRubberPoint("LINE_END", x, y);
                vulcanize();
                addRubber("LINE");
                setRubberMode("LINE");
                setRubberPoint("LINE_START", x, y);
                global.prevX = x;
                global.prevY = y;
                setPromptPrefix(translate("Specify next point or [Undo]: "));
            }
        }
    }
}
*/

/*
void line_init(EmbLine line_in, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Line");

    line = line_in;

    setFlag(ItemIsSelectable, true);

    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}
*/

/*
void line_setEndPoint1(EmbVector point1)
{
    float dx = line.start.x - point1.x;
    float dy = line.start.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}
*/

/*
void line_setEndPoint2(EmbVector point1)
{
    float dx = line.end.x - point1.x;
    float dy = line.end.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}
*/

/*
EmbVector line_objectEndPoint2()
{
    EmbLine lyne = line();
    float alpha = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rotEnd = emb_vector_rotate(point2, alpha);

    return scenePos() + rotEnd;
}
*/

/*
EmbVector line_objectMidPoint()
{
    EmbLine lyne = line();
    EmbVector mp = lyne.pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);

    return scenePos() + rotMid;
}
*/

/*
float line_objectAngle()
{
    return std::fmodf(line().angle() - rotation(), 360.0);
}
*/

/*
void line_paint(QPainter* painter, QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  {
        paintPen.setStyle(Qt::DashLine);
    }
    if (objScene->property(ENABLE_LWT).toBool()) {
        paintPen = lineWeightPen();
    }
    painter->setPen(paintPen);

    if (objectRubberMode() != OBJ_RUBBER_LINE) painter->drawLine(line());

    if (objScene->property(ENABLE_LWT).toBool() && objScene->property("ENABLE_REAL").toBool()) {
        realRender(painter, path());
    }
}

void line_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_LINE) {
        EmbVector sceneStartPoint = objectRubberPoint("LINE_START");
        EmbVector sceneQSnapPoint = objectRubberPoint("LINE_END");

        setEndPoint1(sceneStartPoint);
        setEndPoint2(sceneQSnapPoint);

        drawRubberLine(line(), painter, VIEW_COLOR_CROSSHAIR);
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if     (gripPoint == objectEndPoint1()) painter->drawLine(line().p2(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectEndPoint2()) painter->drawLine(line().p1(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectMidPoint())  painter->drawLine(line().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}
*/

/*
// Returns the closest snap point to the mouse point
EmbVector line_mouseSnapPoint(EmbVector& mousePoint)
{
    EmbVector endPoint1 = objectEndPoint1();
    EmbVector endPoint2 = objectEndPoint2();
    EmbVector midPoint  = objectMidPoint();

    float end1Dist = EmbLine(mousePoint, endPoint1).length();
    float end2Dist = EmbLine(mousePoint, endPoint2).length();
    float midDist  = EmbLine(mousePoint, midPoint).length();

    float minDist = std::min(std::min(end1Dist, end2Dist), midDist);

    if     (minDist == end1Dist) return endPoint1;
    else if (minDist == end2Dist) return endPoint2;
    else if (minDist == midDist)  return midPoint;

    return scenePos();
}

std::vector<EmbVector> line_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectEndPoint1() << objectEndPoint2() << objectMidPoint();
    return gripPoints;
}

void line_gripEdit(EmbVector& before, EmbVector& after)
{
    if     (before == objectEndPoint1()) { setEndPoint1(after); }
    else if (before == objectEndPoint2()) { setEndPoint2(after); }
    else if (before == objectMidPoint())  { EmbVector delta = after-before; moveBy(delta.x(), delta.y()); }
}

QPainterPath line_objectSavePath()
{
    QPainterPath path;
    path.lineTo(objectDeltaX(), objectDeltaY());
    return path;
}

path_PathObject(float x, float y, const QPainterPath p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

path_PathObject(PathObject* obj, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void path_init(float x, float y, const QPainterPath& p, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Path");

    setFlag(ItemIsSelectable, true);

    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void path_updatePath(const QPainterPath& p)
{
    normalPath = p;
    QPainterPath reversePath = normalPath.toReversed();
    reversePath.connectPath(normalPath);
    setPath(reversePath);
}

void path_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPath(objectPath());
}

void path_updateRubber(QPainter* painter)
{
    //TODO: Path Rubber Modes

    //TODO: updateRubber() gripping for PathObject

}

// Returns the closest snap point to the mouse point
EmbVector path_mouseSnapPoint(const EmbVector& mousePoint)
{
    return scenePos();
}

std::vector<EmbVector> path_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << scenePos(); //TODO: loop thru all path Elements and return their points
    return gripPoints;
}

void path_gripEdit(const EmbVector& before, const EmbVector& after)
{
    //TODO: gripEdit() for PathObject
}

QPainterPath path_objectCopyPath()
{
    return normalPath;
}

QPainterPath path_objectSavePath()
{
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(normalPath);
}

void point_init(float x, float y, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Point");

    setFlag(ItemIsSelectable, true);

    setRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void point_paint(QPainter* painter, QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPoint(0,0);
}

void point_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == scenePos()) {
                EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
                drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
            }
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector point_mouseSnapPoint(EmbVector& mousePoint)
{
    return scenePos();
}

std::vector<EmbVector> point_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << scenePos();
    return gripPoints;
}

void point_gripEdit(EmbVector& before, EmbVector& after)
{
    if (before == scenePos()) { EmbVector delta = after-before; moveBy(delta.x(), delta.y()); }
}

QPainterPath point_objectSavePath()
{
    QPainterPath path;
    path.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    return path;
}

void polygon_PolygonObject(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    init(x, y, p, rgb, SolidLine); //TODO: getCurrentLineType
}

void polygon_PolygonObject(PolygonObject* obj, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void polygon_init(float x, float y, const QPainterPath& p, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polygon");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

void polygon_updatePath(const QPainterPath& p)
{
    normalPath = p;
    QPainterPath closedPath = normalPath;
    closedPath.closeSubpath();
    QPainterPath reversePath = closedPath.toReversed();
    reversePath.connectPath(closedPath);
    setPath(reversePath);
}

void polygon_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    if (normalPath.elementCount()) {
        painter->drawPath(normalPath);
        QPainterPath::Element zero = normalPath.elementAt(0);
        QPainterPath::Element last = normalPath.elementAt(normalPath.elementCount()-1);
        painter->drawLine(EmbVector(zero.x, zero.y), EmbVector(last.x, last.y));
    }
}

void polygon_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_POLYGON) {
        setPos(objectRubberPoint("POLYGON_POINT_0"));

        bool ok = false;
        const char *numStr = objectRubberText("POLYGON_NUM_POINTS");
        if (numStr.isNull()) return;
        int num = numStr.toInt(&ok);
        if (!ok) return;

        const char *appendStr;
        QPainterPath rubberPath;
        rubberPath.moveTo(mapFromScene(objectRubberPoint("POLYGON_POINT_0")));
        for (int i = 1; i <= num; i++) {
            appendStr = "POLYGON_POINT_" + std::string().setNum(i);
            EmbVector appendPoint = mapFromScene(objectRubberPoint(appendStr));
            rubberPath.lineTo(appendPoint);
        }
        //rubberPath.lineTo(0,0);
        updatePath(rubberPath);

        //Ensure the path isn't updated until the number of points is changed again
        setRubberText("POLYGON_NUM_POINTS", std::string());
    }
    else if (rubberMode == OBJ_RUBBER_POLYGON_INSCRIBE) {
        setPos(objectRubberPoint("POLYGON_CENTER"));

        quint16 numSides = objectRubberPoint("POLYGON_NUM_SIDES").x();

        EmbVector inscribePoint = mapFromScene(objectRubberPoint("POLYGON_INSCRIBE_POINT"));
        EmbLine inscribeLine = EmbLine(EmbVector(0,0), inscribePoint);
        float inscribeAngle = inscribeLine.angle();
        float inscribeInc = 360.0/numSides;

        if (painter) drawRubberLine(inscribeLine, painter, VIEW_COLOR_CROSSHAIR);

        QPainterPath inscribePath;
        //First Point
        inscribePath.moveTo(inscribePoint);
        //Remaining Points
        for (int i = 1; i < numSides; i++) {
            inscribeLine.setAngle(inscribeAngle + inscribeInc*i);
            inscribePath.lineTo(inscribeLine.p2());
        }
        updatePath(inscribePath);
    }
    else if (rubberMode == OBJ_RUBBER_POLYGON_CIRCUMSCRIBE) {
        setPos(objectRubberPoint("POLYGON_CENTER"));

        quint16 numSides = objectRubberPoint("POLYGON_NUM_SIDES").x();

        EmbVector circumscribePoint = mapFromScene(objectRubberPoint("POLYGON_CIRCUMSCRIBE_POINT"));
        EmbLine circumscribeLine = EmbLine(EmbVector(0,0), circumscribePoint);
        float circumscribeAngle = circumscribeLine.angle();
        float circumscribeInc = 360.0/numSides;

        if (painter) drawRubberLine(circumscribeLine, painter, VIEW_COLOR_CROSSHAIR);

        QPainterPath circumscribePath;
        //First Point
        EmbLine prev(circumscribeLine.p2(), EmbVector(0,0));
        prev = prev.normalVector();
        circumscribeLine.setAngle(circumscribeAngle + circumscribeInc);
        EmbLine perp(circumscribeLine.p2(), EmbVector(0,0));
        perp = perp.normalVector();
        EmbVector iPoint;
        perp.intersects(prev, &iPoint);
        circumscribePath.moveTo(iPoint);
        //Remaining Points
        for (int i = 2; i <= numSides; i++) {
            prev = perp;
            circumscribeLine.setAngle(circumscribeAngle + circumscribeInc*i);
            perp = EmbLine(circumscribeLine.p2(), EmbVector(0,0));
            perp = perp.normalVector();
            perp.intersects(prev, &iPoint);
            circumscribePath.lineTo(iPoint);
        }
        updatePath(circumscribePath);
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            int elemCount = normalPath.elementCount();
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripIndex == -1) gripIndex = findIndex(gripPoint);
            if (gripIndex == -1) return;

            int m = 0;
            int n = 0;

            if (!gripIndex) {
                m = elemCount-1;
                n = 1;
            }
            else if (gripIndex == elemCount-1) {
                m = elemCount-2;
                n = 0;
            }
            else {
                m = gripIndex-1;
                n = gripIndex+1;
            }
            QPainterPath::Element em = normalPath.elementAt(m);
            QPainterPath::Element en = normalPath.elementAt(n);
            EmbVector emPoint = EmbVector(em.x, em.y);
            EmbVector enPoint = EmbVector(en.x, en.y);
            painter->drawLine(emPoint, mapFromScene(objectRubberPoint(std::string())));
            painter->drawLine(enPoint, mapFromScene(objectRubberPoint(std::string())));

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector polygon_mouseSnapPoint(const EmbVector& mousePoint)
{
    QPainterPath::Element element = normalPath.elementAt(0);
    EmbVector closestPoint = mapToScene(EmbVector(element.x, element.y));
    float closestDist = EmbLine(mousePoint, closestPoint).length();
    int elemCount = normalPath.elementCount();
    for (int i = 0; i < elemCount; ++i) {
        element = normalPath.elementAt(i);
        EmbVector elemPoint = mapToScene(element.x, element.y);
        float elemDist = EmbLine(mousePoint, elemPoint).length();
        if (elemDist < closestDist) {
            closestPoint = elemPoint;
            closestDist = elemDist;
        }
    }
    return closestPoint;
}

std::vector<EmbVector> polygon_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    QPainterPath::Element element;
    for (int i = 0; i < normalPath.elementCount(); ++i) {
        element = normalPath.elementAt(i);
        gripPoints << mapToScene(element.x, element.y);
    }
    return gripPoints;
}

int polygon_findIndex(EmbVector point)
{
    int i = 0;
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void polygon_gripEdit(const EmbVector& before, const EmbVector& after)
{
    gripIndex = findIndex(before);
    if (gripIndex == -1) return;
    EmbVector a = mapFromScene(after);
    normalPath.setElementPositionAt(gripIndex, a.x(), a.y());
    updatePath(normalPath);
    gripIndex = -1;
}

QPainterPath polygon_objectCopyPath()
{
    return normalPath;
}

QPainterPath polygon_objectSavePath()
{
    QPainterPath closedPath = normalPath;
    closedPath.closeSubpath();
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(closedPath);
}

void embPolyline_PolylineObject(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void embPolyline_PolylineObject(PolylineObject* obj, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void embPolyline_init(float x, float y, QPainterPath *p, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polyline");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

void embPolyline_updatePath(const QPainterPath& p)
{
    normalPath = p;
    QPainterPath reversePath = normalPath.toReversed();
    reversePath.connectPath(normalPath);
    setPath(reversePath);
}

void embPolyline_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPath(normalPath);

    if (objScene->property(ENABLE_LWT).toBool() && objScene->property(ENABLE_REAL).toBool()) { realRender(painter, normalPath); }
}

void embPolyline_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_POLYLINE) {
        setPos(objectRubberPoint("POLYLINE_POINT_0"));

        EmbLine rubberLine(normalPath.currentPosition(), mapFromScene(objectRubberPoint(std::string())));
        if (painter) drawRubberLine(rubberLine, painter, VIEW_COLOR_CROSSHAIR);

        bool ok = false;
        const char *numStr = objectRubberText("POLYLINE_NUM_POINTS");
        if (numStr.isNull()) return;
        int num = numStr.toInt(&ok);
        if (!ok) return;

        const char *appendStr;
        QPainterPath rubberPath;
        for (int i = 1; i <= num; i++) {
            appendStr = "POLYLINE_POINT_" + std::string().setNum(i);
            EmbVector appendPoint = mapFromScene(objectRubberPoint(appendStr));
            rubberPath.lineTo(appendPoint);
        }
        updatePath(rubberPath);

        //Ensure the path isn't updated until the number of points is changed again
        setRubberText("POLYLINE_NUM_POINTS", std::string());
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            int elemCount = normalPath.elementCount();
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripIndex == -1) gripIndex = findIndex(gripPoint);
            if (gripIndex == -1) return;

            if (!gripIndex) { //First
                QPainterPath::Element ef = normalPath.elementAt(1);
                EmbVector efPoint = EmbVector(ef.x, ef.y);
                painter->drawLine(efPoint, mapFromScene(objectRubberPoint(std::string())));
            }
            else if (gripIndex == elemCount-1) { //Last
                QPainterPath::Element el = normalPath.elementAt(gripIndex-1);
                EmbVector elPoint = EmbVector(el.x, el.y);
                painter->drawLine(elPoint, mapFromScene(objectRubberPoint(std::string())));
            }
            else { //Middle
                QPainterPath::Element em = normalPath.elementAt(gripIndex-1);
                QPainterPath::Element en = normalPath.elementAt(gripIndex+1);
                EmbVector emPoint = EmbVector(em.x, em.y);
                EmbVector enPoint = EmbVector(en.x, en.y);
                painter->drawLine(emPoint, mapFromScene(objectRubberPoint(std::string())));
                painter->drawLine(enPoint, mapFromScene(objectRubberPoint(std::string())));
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector embPolyline_mouseSnapPoint(const EmbVector& mousePoint)
{
    QPainterPath::Element element = normalPath.elementAt(0);
    EmbVector closestPoint = mapToScene(EmbVector(element.x, element.y));
    float closestDist = EmbLine(mousePoint, closestPoint).length();
    int elemCount = normalPath.elementCount();
    for (int i = 0; i < elemCount; ++i) {
        element = normalPath.elementAt(i);
        EmbVector elemPoint = mapToScene(element.x, element.y);
        float elemDist = EmbLine(mousePoint, elemPoint).length();
        if (elemDist < closestDist) {
            closestPoint = elemPoint;
            closestDist = elemDist;
        }
    }
    return closestPoint;
}

std::vector<EmbVector> embPolyline_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    QPainterPath::Element element;
    for (int i = 0; i < normalPath.elementCount(); ++i) {
        element = normalPath.elementAt(i);
        gripPoints << mapToScene(element.x, element.y);
    }
    return gripPoints;
}

int embPolyline_findIndex(const EmbVector& point)
{
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (int i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void embPolyline_gripEdit(const EmbVector& before, const EmbVector& after)
{
    gripIndex = findIndex(before);
    if (gripIndex == -1) return;
    EmbVector a = mapFromScene(after);
    normalPath.setElementPositionAt(gripIndex, a.x(), a.y());
    updatePath(normalPath);
    gripIndex = -1;
}

QPainterPath embPolyline_objectCopyPath()
{
    return normalPath;
}

QPainterPath embPolyline_objectSavePath()
{
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(normalPath);
}

void rect_init(EmbRect rect, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Rectangle");

    setFlag(ItemIsSelectable, true);

    setRect(x, y, w, h);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

void rect_setRect(float x, float y, float w, float h)
{
    setPos(x, y);
    setRect(0, 0, w, h);
    updatePath();
}

EmbVector rect_objectTopLeft()
{
    float alpha = radians(rotation());
    EmbVector tl = rect().topLeft() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptlrot;
}

EmbVector rect_objectTopRight()
{
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptrrot;
}
*/

EmbVector embRect_bottomLeft(EmbRect rect)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
    float alpha = radians(rotation());
    EmbVector bl = rect().bottomLeft() * scale();
    EmbVector pblrot = emb_vector_rotate(b1, alpha);
    return scenePos() + pblrot;
    */
    return v;
}

EmbVector embRect_bottomRight(EmbRect rect)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
    float alpha = radians(rotation());
    EmbVector br = rect().bottomRight() * scale();
    EmbVector pbrrot = emb_vector_rotate(br, alpha);
    return scenePos() + pbrrot;
    */
    return v;
}

/*
void embRect_updatePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.moveTo(r.bottomLeft());
    path.lineTo(r.bottomRight());
    path.lineTo(r.topRight());
    path.lineTo(r.topLeft());
    path.lineTo(r.bottomLeft());
    //NOTE: Reverse the path so that the inside area isn't considered part of the rectangle
    path.lineTo(r.topLeft());
    path.lineTo(r.topRight());
    path.lineTo(r.bottomRight());
    path.moveTo(r.bottomLeft());
    setPath(path);
}

void rect_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawRect(rect());
}
*/

/*
void rect_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_RECTANGLE) {
        EmbVector sceneStartPoint = objectRubberPoint("RECTANGLE_START");
        EmbVector sceneEndPoint = objectRubberPoint("RECTANGLE_END");
        float x = sceneStartPoint.x();
        float y = sceneStartPoint.y();
        float w = sceneEndPoint.x() - sceneStartPoint.x();
        float h = sceneEndPoint.y() - sceneStartPoint.y();
        setRect(x,y,w,h);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            //TODO: Make this work with rotation & scaling
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            EmbVector after = objectRubberPoint(std::string());
            EmbVector delta = after-gripPoint;
            if (gripPoint == objectTopLeft()) {
                painter->drawPolygon(mapFromScene(EmbRect(after.x(), after.y(), objectWidth()-delta.x(), objectHeight()-delta.y())));
            }
            else if (gripPoint == objectTopRight()) {
                painter->drawPolygon(mapFromScene(EmbRect(objectTopLeft().x(), objectTopLeft().y()+delta.y(), objectWidth()+delta.x(), objectHeight()-delta.y())));
            }
            else if (gripPoint == objectBottomLeft()) {
                painter->drawPolygon(mapFromScene(EmbRect(objectTopLeft().x()+delta.x(), objectTopLeft().y(), objectWidth()-delta.x(), objectHeight()+delta.y())));
            }
            else if (gripPoint == objectBottomRight()) {
                painter->drawPolygon(mapFromScene(EmbRect(objectTopLeft().x(), objectTopLeft().y(), objectWidth()+delta.x(), objectHeight()+delta.y())));
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);

            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            EmbVector after = objectRubberPoint(std::string());
            EmbVector delta = after-gripPoint;

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector rect_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector ptl = objectTopLeft();     //Top Left Corner QSnap
    EmbVector ptr = objectTopRight();    //Top Right Corner QSnap
    EmbVector pbl = objectBottomLeft();  //Bottom Left Corner QSnap
    EmbVector pbr = objectBottomRight(); //Bottom Right Corner QSnap

    float ptlDist = EmbLine(mousePoint, ptl).length();
    float ptrDist = EmbLine(mousePoint, ptr).length();
    float pblDist = EmbLine(mousePoint, pbl).length();
    float pbrDist = EmbLine(mousePoint, pbr).length();

    float minDist = std::min(std::min(ptlDist, ptrDist), std::min(pblDist, pbrDist));

    if     (minDist == ptlDist) return ptl;
    else if (minDist == ptrDist) return ptr;
    else if (minDist == pblDist) return pbl;
    else if (minDist == pbrDist) return pbr;

    return scenePos();
}

std::vector<EmbVector> rect_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectTopLeft() << objectTopRight() << objectBottomLeft() << objectBottomRight();
    return gripPoints;
}

void rect_gripEdit(const EmbVector& before, const EmbVector& after)
{
    EmbVector delta = after-before;
    if (before == objectTopLeft()) {
        setRect(after.x(), after.y(), objectWidth()-delta.x(), objectHeight()-delta.y());
    }
    else if (before == objectTopRight()) {
        setRect(objectTopLeft().x(), objectTopLeft().y()+delta.y(), objectWidth()+delta.x(), objectHeight()-delta.y());
    }
    else if (before == objectBottomLeft()) {
        setRect(objectTopLeft().x()+delta.x(), objectTopLeft().y(), objectWidth()-delta.x(), objectHeight()+delta.y());
    }
    else if (before == objectBottomRight()) {
        setRect(objectTopLeft().x(), objectTopLeft().y(), objectWidth()+delta.x(), objectHeight()+delta.y());
    }
}

QPainterPath rect_objectSavePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.moveTo(r.bottomLeft());
    path.lineTo(r.bottomRight());
    path.lineTo(r.topRight());
    path.lineTo(r.topLeft());
    path.lineTo(r.bottomLeft());

    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(path);
}
*/

/*
 */
EmbCircle
emb_circle_init(EmbReal x, EmbReal y, EmbReal radius)
{
    EmbCircle circle;
    circle.center.x = x;
    circle.center.y = y;
    circle.radius = radius;
    return circle;
}

/*
 */
EmbReal
emb_circle_area(EmbCircle circle)
{
    return embConstantPi * circle.radius * circle.radius;
}

/*
 */
EmbReal
emb_circle_circumference(EmbCircle circle)
{
    return 2.0f * embConstantPi * circle.radius;
}

/* Computational Geometry for Circles */

/* Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 */
int
getCircleCircleIntersections(EmbCircle c0, EmbCircle c1,
                             EmbVector *p0, EmbVector *p1)
{
    EmbVector delta;
    EmbReal a, h, px2, py2, mx, my, d;
    /* Distance between centers */
    delta = emb_vector_subtract(c1.center, c0.center);
    d = emb_vector_length(delta);

    /*Circles share centers. This results in division by zero,
      infinite solutions or one circle being contained within the other. */
    if (d == 0.0) {
        return 0;
    } else if (d > (c0.radius + c1.radius)) {
        /* Circles do not touch each other */
        return 0;
    } else if (d < (c0.radius - c1.radius)) {
        /* One circle is contained within the other */
        return 0;
    }
    /*
     * Considering the two right triangles p0p2p3 and p1p2p3 we can write:
     * a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2
     *
     * BEGIN PROOF
     *
     * Remove h^2 from the equation by setting them equal to themselves:
     *     r0^2 - a^2 = r1^2 - b^2
     * Substitute b with (d - a) since it is proven that d = a + b:
     *     r0^2 - a^2 = r1^2 - (d - a)^2
     * Complete the square:
     *     r0^2 - a^2 = r1^2 - (d^2 -2da + a^2)
     * Subtract r1^2 from both sides:
     *     r0^2 - r1^2 - a^2 = -(d^2 -2da + a^2)
     * Invert the signs:
     *     r0^2 - r1^2 - a^2 = -d^2 + 2da - a^2
     * Adding a^2 to each side cancels them out:
     *     r0^2 - r1^2 = -d^2 + 2da
     * Add d^2 to both sides to shift it to the other side:
     *     r0^2 - r1^2 + d^2 = 2da
     * Divide by 2d to finally solve for a:
     *     a = (r0^2 - r1^2 + d^2)/ (2d)
     *
     * END PROOF
     */

    a = ((c0.radius*c0.radius) - (c1.radius*c1.radius) + (d*d)) / (2.0 * d);
    /* Solve for h by substituting a into a^2 + h^2 = r0^2 */
    h = sqrt((c0.radius*c0.radius) - (a*a));

    /*Find point p2 by adding the a offset in relation to line d to point p0 */
    px2 = c0.center.x + (delta.x * a/d);
    py2 = c0.center.y + (delta.y * a/d);

    /* Tangent circles have only one intersection

       TODO: using == in floating point arithmetic
       doesn't account for the machine accuracy, having
       a stated (EmbReal) tolerance value would help.
    */
    if (d == (c0.radius + c1.radius)) {
        p0->x = px2;
        p0->y = py2;
        p1->x = px2;
        p1->y = py2;
        return 1;
    }

    /* Get the perpendicular slope by multiplying by the negative reciprocal
     * Then multiply by the h offset in relation to d to get the actual offsets */
    mx = -(delta.y * h/d);
    my =  (delta.x * h/d);

    /* Add the offsets to point p2 to obtain the intersection points */
    p0->x = px2 + mx;
    p0->y = py2 + my;
    p1->x = px2 - mx;
    p1->y = py2 - my;

    return 1;
}

/* Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 */
int
getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector *t0, EmbVector *t1)
{
    EmbCircle p;
    EmbReal hyp;
    /* Distance to center of circle */
    hyp = emb_vector_distance(point, c.center);
    /* Point is inside the circle */
    if (hyp < c.radius) {
        return 0;
    } else if (hyp == c.center.y) {
        /* Point is lies on the circle, so there is only one tangent point */
        *t0 = point;
        *t1 = point;
        return 1;
    }

    /* Since the tangent lines are always perpendicular to the radius, so
     * we can use the Pythagorean theorem to solve for the missing side */
    p.center = point;
    p.radius = sqrt((hyp*hyp) - (c.radius*c.radius));
    return getCircleCircleIntersections(c, p, t0, t1);
}

/*
 */
EmbEllipse
embEllipse_init(void)
{
    EmbEllipse ellipse;
    ellipse.center.x = 0.0;
    ellipse.center.y = 0.0;
    ellipse.radius.x = 1.0;
    ellipse.radius.y = 2.0;
    ellipse.rotation = 0.0;
    return ellipse;
}

/* TODO: look up a formula. */
EmbReal
embEllipse_area(EmbEllipse ellipse)
{
    return 0.0;
}

/* TODO: Use Ramanujan's approximation here. */
EmbReal
embEllipse_perimeter(EmbEllipse ellipse)
{
    return 0.0;
}

/* . */
EmbReal
embEllipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

EmbReal
embEllipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}


/*
void embEllipse_init(EmbEllipse ellipse, unsigned int rgb, int lineType)
{
    printf("%f %d %d", ellipse.radius.x, rgb, lineType);
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Ellipse");

    setFlag(ItemIsSelectable, true);

    setSize(width, height);
    setCenter(centerX, centerY);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
}
*/

void embEllipse_setSize(float width, float height)
{
    printf("%f %f", width, height);
    /*
    EmbRect elRect = rect();
    elRect.setWidth(width);
    elRect.setHeight(height);
    elRect.moveCenter(EmbVector(0,0));
    setRect(elRect);
    */
}

void embEllipse_setRadiusMajor(float radius)
{
    printf("%f", radius);
    /*
    setDiameterMajor(radius*2.0);
    */
}

void embEllipse_setRadiusMinor(float radius)
{
    printf("%f", radius);
    /*
    setDiameterMinor(radius*2.0);
    */
}

void embEllipse_setDiameterMajor(EmbEllipse *ellipse, float diameter)
{
    printf("%f %f", ellipse->radius.x, diameter);
    /*
    EmbRect elRect = rect();
    if (elRect.width() > elRect.height())
        elRect.setWidth(diameter);
    else
        elRect.setHeight(diameter);
    elRect.moveCenter(EmbVector(0,0));
    setRect(elRect);
    */
}

void embEllipse_setDiameterMinor(EmbEllipse *ellipse, float diameter)
{
    printf("%f %f", ellipse->center.x, diameter);
    /*
    EmbRect elRect = rect();
    if (elRect.width() < elRect.height())
        elRect.setWidth(diameter);
    else
        elRect.setHeight(diameter);
    elRect.moveCenter(EmbVector(0,0));
    setRect(elRect);
    */
}

EmbVector ellipse_objectQuadrant0(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfW = objectWidth()/2.0;
    float rot = radians(rotation());
    float x = halfW*cos(rot);
    float y = halfW*sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

EmbVector ellipse_objectQuadrant90(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfH = objectHeight()/2.0;
    float rot = radians(rotation()+90.0);
    float x = halfH * cos(rot);
    float y = halfH * sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

EmbVector ellipse_objectQuadrant180(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfW = objectWidth()/2.0;
    float rot = radians(rotation()+180.0);
    float x = halfW*cos(rot);
    float y = halfW*sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

EmbVector ellipse_objectQuadrant270(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfH = objectHeight()/2.0;
    float rot = radians(rotation()+270.0);
    float x = halfH*cos(rot);
    float y = halfH*sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

void embEllipse_updatePath()
{
    /*
    QPainterPath path;
    EmbRect r = rect();
    path.arcMoveTo(r, 0);
    path.arcTo(r, 0, 360);
    //NOTE: Reverse the path so that the inside area isn't considered part of the ellipse
    path.arcTo(r, 0, -360);
    setPath(path);
    */
}

/*
void embEllipse_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawEllipse(rect());
}
*/

/*
void embEllipse_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_ELLIPSE_LINE) {
        EmbVector sceneLinePoint1 = objectRubberPoint("ELLIPSE_LINE_POINT1");
        EmbVector sceneLinePoint2 = objectRubberPoint("ELLIPSE_LINE_POINT2");
        EmbVector itemLinePoint1  = mapFromScene(sceneLinePoint1);
        EmbVector itemLinePoint2  = mapFromScene(sceneLinePoint2);
        EmbLine itemLine(itemLinePoint1, itemLinePoint2);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_ELLIPSE_MAJORDIAMETER_MINORRADIUS) {
        EmbVector sceneAxis1Point1 = objectRubberPoint("ELLIPSE_AXIS1_POINT1");
        EmbVector sceneAxis1Point2 = objectRubberPoint("ELLIPSE_AXIS1_POINT2");
        EmbVector sceneCenterPoint = objectRubberPoint("ELLIPSE_CENTER");
        EmbVector sceneAxis2Point2 = objectRubberPoint("ELLIPSE_AXIS2_POINT2");
        float ellipseWidth = objectRubberPoint("ELLIPSE_WIDTH").x();
        float ellipseRot = objectRubberPoint("ELLIPSE_ROT").x();

        //TODO: incorporate perpendicularDistance() into libcgeometry
        float px = sceneAxis2Point2.x();
        float py = sceneAxis2Point2.y();
        float x1 = sceneAxis1Point1.x();
        float y1 = sceneAxis1Point1.y();
        EmbLine line(sceneAxis1Point1, sceneAxis1Point2);
        EmbLine norm = line.normalVector();
        float dx = px-x1;
        float dy = py-y1;
        norm.translate(dx, dy);
        EmbVector iPoint;
        norm.intersects(line, &iPoint);
        float ellipseHeight = EmbLine(px, py, iPoint.x(), iPoint.y()).length()*2.0;

        setCenter(sceneCenterPoint);
        setSize(ellipseWidth, ellipseHeight);
        setRotation(-ellipseRot);

        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemAxis2Point2 = mapFromScene(sceneAxis2Point2);
        EmbLine itemLine(itemCenterPoint, itemAxis2Point2);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_ELLIPSE_MAJORRADIUS_MINORRADIUS) {
        EmbVector sceneAxis1Point2 = objectRubberPoint("ELLIPSE_AXIS1_POINT2");
        EmbVector sceneCenterPoint = objectRubberPoint("ELLIPSE_CENTER");
        EmbVector sceneAxis2Point2 = objectRubberPoint("ELLIPSE_AXIS2_POINT2");
        float ellipseWidth = objectRubberPoint("ELLIPSE_WIDTH").x();
        float ellipseRot = objectRubberPoint("ELLIPSE_ROT").x();

        //TODO: incorporate perpendicularDistance() into libcgeometry
        float px = sceneAxis2Point2.x();
        float py = sceneAxis2Point2.y();
        float x1 = sceneCenterPoint.x();
        float y1 = sceneCenterPoint.y();
        EmbLine line(sceneCenterPoint, sceneAxis1Point2);
        EmbLine norm = line.normalVector();
        float dx = px-x1;
        float dy = py-y1;
        norm.translate(dx, dy);
        EmbVector iPoint;
        norm.intersects(line, &iPoint);
        float ellipseHeight = EmbLine(px, py, iPoint.x(), iPoint.y()).length()*2.0;

        setCenter(sceneCenterPoint);
        setSize(ellipseWidth, ellipseHeight);
        setRotation(-ellipseRot);

        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemAxis2Point2 = mapFromScene(sceneAxis2Point2);
        EmbLine itemLine(itemCenterPoint, itemAxis2Point2);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        //TODO: updateRubber() gripping for EllipseObject
    }
}
*/

/*
// Returns the closest snap point to the mouse point
EmbVector ellipse_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector center  = objectCenter();
    EmbVector quad0   = objectQuadrant0();
    EmbVector quad90  = objectQuadrant90();
    EmbVector quad180 = objectQuadrant180();
    EmbVector quad270 = objectQuadrant270();

    float cntrDist = EmbLine(mousePoint, center).length();
    float q0Dist   = EmbLine(mousePoint, quad0).length();
    float q90Dist  = EmbLine(mousePoint, quad90).length();
    float q180Dist = EmbLine(mousePoint, quad180).length();
    float q270Dist = EmbLine(mousePoint, quad270).length();

    float minDist = std::min(std::min(std::min(q0Dist, q90Dist), std::min(q180Dist, q270Dist)), cntrDist);

    if     (minDist == cntrDist) return center;
    else if (minDist == q0Dist)   return quad0;
    else if (minDist == q90Dist)  return quad90;
    else if (minDist == q180Dist) return quad180;
    else if (minDist == q270Dist) return quad270;

    return scenePos();
}
*/

/*
std::vector<EmbVector> ellipse_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectCenter() << objectQuadrant0() << objectQuadrant90() << objectQuadrant180() << objectQuadrant270();
    return gripPoints;
}
*/

/*
void embEllipse_gripEdit(const EmbVector& before, const EmbVector& after)
{
    //TODO: gripEdit() for EllipseObject
}
*/

/*
QPainterPath ellipse_objectSavePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.arcMoveTo(r, 0);
    path.arcTo(r, 0, 360);

    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(path);
}
*/

/*
 * BASIC FUNCTIONS
 */

/* round is C99 and we're committed to C90 so here's a replacement.
 */
int
emb_round(EmbReal x)
{
    EmbReal y = floor(x);
    if (fabs(x-y) > 0.5) {
        return (int)ceil(x);
    }
    return (int)y;
}

EmbReal
radians(EmbReal degree)
{
    return degree*embConstantPi/180.0;
}

EmbReal
degrees(EmbReal radian)
{
    return radian*180.0/embConstantPi;
}

/* Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
EmbVector
emb_line_normalVector(EmbLine line, int clockwise)
{
    EmbVector result;
    EmbReal temp;
    result = emb_vector_subtract(line.end, line.start);
    result = emb_vector_normalize(result);
    temp = result.x;
    result.x = result.y;
    result.y = -temp;
    if (!clockwise) {
        result.x = -result.x;
        result.y = -result.y;
    }
    return result;
}

/* Returns the vector that is the same length as the line, in the same
 * direction.
 */
EmbVector
emb_line_toVector(EmbLine line)
{
    return emb_vector_subtract(line.end, line.start);
}

/*
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
EmbVector
emb_line_intersectionPoint(EmbLine line1, EmbLine line2)
{
    EmbReal det, C2, C1, tolerance;
    EmbVector vec1, vec2, result;
    emb_error = 0;
    vec1 = emb_line_toVector(line1);
    vec2 = emb_line_toVector(line2);
    C2 = emb_vector_cross(line1.start, vec1);
    C1 = emb_vector_cross(line2.start, vec2);

    tolerance = 1e-10;
    det = emb_vector_cross(vec2, vec1);

    if (fabs(det) < tolerance) {
        /* Default to the origin when an error is thrown. */
        emb_error = 1;
        result.x = 0.0;
        result.y = 0.0;
        return result;
    }
    result.x = (vec2.x * C2 - vec1.x * C1) / det;
    result.y = (vec2.y * C2 - vec1.y * C1) / det;
    return result;
}

/*
 */
EmbRect
embRect_init(void)
{
    EmbRect rect;
    rect.left = 0.0;
    rect.top = 0.0;
    rect.right = 1.0;
    rect.bottom = 1.0;
    return rect;
}

EmbReal
embRect_area(EmbRect rect)
{
    return (rect.bottom - rect.top) * (rect.right - rect.left);
}

//NOTE: This void should be used to interpret various object types and save them as polylines for stitchOnly formats.
/*
void save_toPolyline(EmbPattern* pattern, const EmbVector& objPos, const QPainterPath& objPath, const std::string& layer, const QColor& color, const std::string& lineType, const std::string& lineWeight)
{
    float startX = objPos.x();
    float startY = objPos.y();
    EmbArray *pointList = emb_array_create(EMB_POINT);
    EmbPoint lastPoint;
    QPainterPath::Element element;
    for (int i = 0; i < objPath.elementCount(); ++i) {
        element = objPath.elementAt(i);
        if (pointList->count == 0) {
            lastPoint.position.x = element.x + startX;
            lastPoint.position.y = -(element.y + startY);
            emb_array_addPoint(pointList, lastPoint);
        }
        else {
            lastPoint.position.x += element.x + startX;
            lastPoint.position.y += -(element.y + startY);
        }
    }

    EmbPolyline polyObject;
    polyObject.pointList = pointList;
    polyObject.color.r = color.red();
    polyObject.color.g = color.green();
    polyObject.color.b = color.blue();
    //TODO: proper lineType
    emb_pattern_addPolylineAbs(pattern, polyObject);
}

void textSingle_TextSingleObject(const std::string& str, float x, float y, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    init(str, x, y, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void textSingle_TextSingleObject(TextSingleObject* obj, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    if (obj) {
        setTextFont(obj->objTextFont);
        setTextSize(obj->objTextSize);
        setRotation(obj->rotation());
        setTextBackward(obj->objTextBackward);
        setTextUpsideDown(obj->objTextUpsideDown);
        setTextStyle(obj->objTextBold, obj->objTextItalic, obj->objTextUnderline, obj->objTextStrikeOut, obj->objTextOverline);
        init(obj->objText, obj->objectX(), obj->objectY(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setScale(obj->scale());
    }
}

void textSingle_init(const std::string& str, float x, float y, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Single Line Text");

    setFlag(ItemIsSelectable, true);

    objTextJustify = "Left"; //TODO: set the justification properly

    setText(str);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}
*/

/*
std::stringList text_single_objectTextJustifyList()
{
    std::stringList justifyList;
    justifyList << "Left" << "Center" << "Right" << "Middle";
    // TODO: << "Fit" << "Aligned";
    justifyList << "Top Left" << "Top Center" << "Top Right";
    justifyList << "Middle Left" << "Middle Center" << "Middle Right";
    justifyList << "Bottom Left" << "Bottom Center" << "Bottom Right";
    return justifyList;
}
*/

/*
void textSingle_setText(const std::string& str)
{
    objText = str;
    QPainterPath textPath;
    QFont font;
    font.setFamily(objTextFont);
    font.setPointSizeF(objTextSize);
    font.setBold(objTextBold);
    font.setItalic(objTextItalic);
    font.setUnderline(objTextUnderline);
    font.setStrikeOut(objTextStrikeOut);
    font.setOverline(objTextOverline);
    textPath.addText(0, 0, font, str);

    //Translate the path based on the justification
    EmbRect jRect = textPath.boundingRect();
    if (objTextJustify == "Left") {
        textPath.translate(-jRect.left(), 0);
    }
    else if (objTextJustify == "Center") {
        textPath.translate(-jRect.center().x(), 0);
    }
    else if (objTextJustify == "Right") {
        textPath.translate(-jRect.right(), 0);
    }
    else if (objTextJustify == "Aligned") {

    } //TODO: TextSingleObject Aligned Justification
    else if (objTextJustify == "Middle") {
        textPath.translate(-jRect.center()); }
    else if (objTextJustify == "Fit") {

    } //TODO: TextSingleObject Fit Justification
    else if (objTextJustify == "Top Left") {
        textPath.translate(-jRect.topLeft());
    }
    else if (objTextJustify == "Top Center") {
        textPath.translate(-jRect.center().x(), -jRect.top());
    }
    else if (objTextJustify == "Top Right") {
        textPath.translate(-jRect.topRight());
    }
    else if (objTextJustify == "Middle Left") {
        textPath.translate(-jRect.left(), -jRect.top()/2.0);
    }
    else if (objTextJustify == "Middle Center") { textPath.translate(-jRect.center().x(), -jRect.top()/2.0); }
    else if (objTextJustify == "Middle Right")  { textPath.translate(-jRect.right(), -jRect.top()/2.0); }
    else if (objTextJustify == "Bottom Left")   { textPath.translate(-jRect.bottomLeft()); }
    else if (objTextJustify == "Bottom Center") { textPath.translate(-jRect.center().x(), -jRect.bottom()); }
    else if (objTextJustify == "Bottom Right")  { textPath.translate(-jRect.bottomRight()); }

    //Backward or Upside Down
    if (objTextBackward || objTextUpsideDown) {
        float horiz = 1.0;
        float vert = 1.0;
        if (objTextBackward) horiz = -1.0;
        if (objTextUpsideDown) vert = -1.0;

        QPainterPath flippedPath;

        QPainterPath::Element element;
        QPainterPath::Element P2;
        QPainterPath::Element P3;
        QPainterPath::Element P4;
        for (int i = 0; i < textPath.elementCount(); ++i) {
            element = textPath.elementAt(i);
            if (element.isMoveTo()) {
                flippedPath.moveTo(horiz * element.x, vert * element.y);
            }
            else if (element.isLineTo()) {
                flippedPath.lineTo(horiz * element.x, vert * element.y);
            }
            else if (element.isCurveTo()) {
                                              // start point P1 is not needed
                P2 = textPath.elementAt(i);   // control point
                P3 = textPath.elementAt(i+1); // control point
                P4 = textPath.elementAt(i+2); // end point

                flippedPath.cubicTo(horiz * P2.x, vert * P2.y,
                                    horiz * P3.x, vert * P3.y,
                                    horiz * P4.x, vert * P4.y);
            }
        }
        objTextPath = flippedPath;
    }
    else {
        objTextPath = textPath;
    }

    //Add the grip point to the shape path
    QPainterPath gripPath = objTextPath;
    gripPath.connectPath(objTextPath);
    gripPath.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPath(gripPath);
}
*/

void
textSingle_setTextFont(const char *font)
{
    /*
    objTextFont = font;
    setText(objText);
    */
}

void
textSingle_setJustify(const char *justify)
{
    /*
    // Verify the string is a valid option
    objTextJustify = "Left";
    if ((justify == "Left") || (justify == "Center") || (justify == "Right")
        || (justify == "Aligned") || (justify == "Middle") || (justify == "Fit")
        || (justify == "Top Left") || (justify == "Top Center") || (justify == "Top Right")
        || (justify == "Middle Left") || (justify == "Middle Center") || (justify == "Middle Right")
        || (justify == "Bottom Left") || (justify == "Bottom Center") || (justify == "Bottom Right")) {
        objTextJustify = justify;
    }
    setText(objText);
    */
}

void textSingle_setTextSize(float size)
{
    /*
    objTextSize = size;
    setText(objText);
    */
}

void textSingle_setTextStyle(char bold, char italic, char under, char strike, char over)
{
    printf("%d %d %d %d %d", bold, italic, under, strike, over);
    /*
    objTextBold = bold;
    objTextItalic = italic;
    objTextUnderline = under;
    objTextStrikeOut = strike;
    objTextOverline = over;
    setText(objText);
    */
}

void textSingle_setTextBold(char val)
{
    printf("%d", val);
    /*
    objTextBold = val;
    setText(objText);
    */
}

void textSingle_setTextItalic(char val)
{
    printf("%d", val);
    /*
    objTextItalic = val;
    setText(objText);
    */
}

void textSingle_setTextUnderline(char val)
{
    printf("%d", val);
    /*
    objTextUnderline = val;
    setText(objText);
    */
}

void textSingle_setTextStrikeOut(char val)
{
    printf("%d", val);
    /*
    objTextStrikeOut = val;
    setText(objText);
    */
}

void textSingle_setTextOverline(char val)
{
    printf("%d", val);
    /*
    objTextOverline = val;
    setText(objText);
    */
}

void textSingle_setTextBackward(char val)
{
    printf("%d", val);
    /*
    objTextBackward = val;
    setText(objText);
    */
}

void textSingle_setTextUpsideDown(char val)
{
    printf("%d", val);
    /*
    objTextUpsideDown = val;
    setText(objText);
    */
}

void textSingle_paint() // QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).tochar()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPath(objTextPath);
    */
}

void textSingle_updateRubber() // QPainter* painter)
{
    /*
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_TEXTSINGLE) {
        setTextFont(objectRubberText("TEXT_FONT"));
        setTextJustify(objectRubberText("TEXT_JUSTIFY"));
        setPos(objectRubberPoint("TEXT_POINT"));
        EmbVector hr = objectRubberPoint("TEXT_HEIGHT_ROTATION");
        setTextSize(hr.x());
        setRotation(hr.y());
        setText(objectRubberText("TEXT_RAPID"));
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == scenePos()) {
                painter->drawPath(objectPath().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
    */
}

// Returns the closest snap point to the mouse point
EmbVector textSingle_mouseSnapPoint(EmbVector mousePoint)
{
    EmbVector v = {0.0, 0.0};
    printf("%f %f", mousePoint.x, mousePoint.y);
    //return scenePos();
    return v;
}

/*
std::vector<EmbVector> textSingle_allGripPoints()
{
    std::vector<EmbVector> gripPoints = {};
    // scenePos();
    return gripPoints;
}
*/

void textSingle_gripEdit(EmbVector before, EmbVector after)
{
    printf("%f %f", before.x, after.x);
    /*
    if (before == scenePos()) {
        EmbVector delta = after-before;
        moveBy(delta.x(), delta.y());
    }
    */
}

/*
std::vector<QPainterPath> text_single_subPathList()
{
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);

    std::vector<QPainterPath> pathList;

    QPainterPath path = objTextPath;

    QPainterPath::Element element;
    std::vector<int> pathMoves;
    int numMoves = 0;

    for (int i = 0; i < path.elementCount(); i++) {
        element = path.elementAt(i);
        if (element.isMoveTo()) {
            pathMoves << i;
            numMoves++;
        }
    }

    pathMoves << path.elementCount();

    for (int p = 0; p < pathMoves.size()-1 && p < numMoves; p++) {
        QPainterPath subPath;
        for (int i = pathMoves.value(p); i < pathMoves.value(p+1); i++) {
            element = path.elementAt(i);
            if (element.isMoveTo()) {
                subPath.moveTo(element.x, element.y);
            }
            else if (element.isLineTo()) {
                subPath.lineTo(element.x, element.y);
            }
            else if (element.isCurveTo()) {
                subPath.cubicTo(path.elementAt(i  ).x, path.elementAt(i  ).y,  //control point 1
                                path.elementAt(i+1).x, path.elementAt(i+1).y,  //control point 2
                                path.elementAt(i+2).x, path.elementAt(i+2).y); //end point
            }
        }
        pathList.append(trans.map(subPath));
    }

    return pathList;
}
*/

/* Finds the unit length vector a result in the same direction as a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{u} = \frac{v}{|\mathbf{v}|}
 * \f]
 *
 * \todo make result return argument.
 */
EmbVector
emb_vector_normalize(EmbVector vector)
{
    EmbVector result;
    EmbReal length = emb_vector_length(vector);
    result.x = vector.x / length;
    result.y = vector.y / length;
    return result;
}

/* The scalar multiple a magnitude of a vector a vector. Returned as
 * a result.
 *
 * \todo make result return argument.
 */
EmbVector
emb_vector_scale(EmbVector vector, EmbReal magnitude)
{
    EmbVector result;
    result.x = vector.x * magnitude;
    result.y = vector.y * magnitude;
    return result;
}

/* The sum of vectors a a and a b returned as a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \mathbf{a} + \mathbf{b}
 *                  = \begin{pmatrix} a_{x} + b_{x} \\ a_{y}+b_{y} \end{pmatrix}
 * \f]
 */
EmbVector
emb_vector_add(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

/* The average of vectors a v1 and a v2 returned as a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \frac{\mathbf{a} + \mathbf{b}}{2}
 *                  = \begin{pmatrix} \frac{a_{x} + b_{x}}{2} \\ \frac{a_{y}+b_{y}}{2} \end{pmatrix}
 * \f]
 */
EmbVector
emb_vector_average(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = 0.5*(a.x + b.x);
    result.y = 0.5*(a.y + b.y);
    return result;
}

/* The difference between vectors a v1 and a v2 returned as a result.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \mathbf{a} - \mathbf{b}
 *                  = \begin{pmatrix} a_{x} - b_{x} \\ a_{y}-b_{y} \end{pmatrix}
 * \f]
 */
EmbVector
emb_vector_subtract(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

/* The dot product as vectors a v1 and a v2 returned as a EmbReal.
 *
 * Equivalent to:
 *
 * \f[
 *       c = \mathbf{a} \cdot \mathbf{b}
 *         = a_x b_x + a_y b_y
 * \f]
 */
EmbReal
emb_vector_dot(EmbVector a, EmbVector b)
{
    return a.x * b.x + a.y * b.y;
}

/* @brief The "cross product" as vectors a a and a b returned as a real value.
 *
 * Technically, this is the magnitude of the cross product when the
 * embroidery is placed in the z=0 plane (since the cross product is defined for
 * 3-dimensional vectors). That is:
 *
 * \f[
 *       |c| = \left| \begin{pmatrix} a_x \\ a_y \\ 0 \end{pmatrix} \times \begin{pmatrix} b_x \\ b_y \\ 0 \end{pmatrix}\right|
 *           = \left| \begin{pmatrix} 0 \\ 0 \\ a_x b_y - a_y b_x \end{pmatrix} \right|
 *           = a_x b_y - a_y b_x
 * \f]
 */
EmbReal
emb_vector_cross(EmbVector a, EmbVector b)
{
    return a.x * b.y - a.y * b.x;
}

/* Since we aren't using full vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 */
EmbVector
emb_vector_transpose_product(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    return result;
}

/* The length or absolute value of the vector a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       |v| = \sqrt{v_{x}^{2} + v_{y}^{2}}
 * \f]
 */
EmbReal
emb_vector_length(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/* The x-component of the vector
 */
EmbReal
emb_vector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = emb_vector_subtract(a1, a2);
    c = emb_vector_subtract(a3, a2);
    return emb_vector_dot(b, c);
}

/* The y-component of the vector
 */
EmbReal
emb_vector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = emb_vector_subtract(a1, a2);
    c = emb_vector_subtract(a3, a2);
    return emb_vector_cross(b, c);
}

/* The angle, measured anti-clockwise from the x-axis, of a vector v.
 */
EmbReal
emb_vector_angle(EmbVector v)
{
    return atan2(v.y, v.x);
}

/* The unit vector in the direction a angle.
 *
 * \f[
 *       \mathbf{a}_{alpha} = \begin{pmatrix} \cos(alpha) \\ \sin(alpha) \end{pmatrix}
 * \f]
 */
EmbVector
emb_vector_unit(EmbReal alpha)
{
    EmbVector a;
    a.x = cos(alpha);
    a.y = sin(alpha);
    return a;
}

/* The distance between a a and a b returned as a real value.
 *
 * \f[
 *      d = \left|\mathbf{a}-\mathbf{b}\right|
 *        = \sqrt{(a_x-b_x)^{2} + (a_y-b_y)^{2}}
 * \f]
 */
EmbReal
emb_vector_distance(EmbVector a, EmbVector b)
{
    EmbVector delta = emb_vector_subtract(a, b);
    return emb_vector_length(delta);
}

/*
 * This file contains all the read and write functions for the
 * library.
 *
 * \file image.c
 * This backends to the stb libraries and nanosvg library.
 *
 * Use Python PEP7 for coding style.
 *
 *
 * Write a PES embedded a image to the given a file pointer.
 */

void
writeImage(void* file, unsigned char image[][48])
{
    int i, j;

    if (!file) {
        printf("ERROR: format-pec.c writeImage(), file argument is null\n");
        return;
    }
    for (i = 0; i < 38; i++) {
        for (j = 0; j < 6; j++) {
            int offset = j * 8;
            unsigned char output = 0;
            output |= (unsigned char)(image[i][offset] != 0);
            output |= (unsigned char)(image[i][offset + 1] != (unsigned char)0) << 1;
            output |= (unsigned char)(image[i][offset + 2] != (unsigned char)0) << 2;
            output |= (unsigned char)(image[i][offset + 3] != (unsigned char)0) << 3;
            output |= (unsigned char)(image[i][offset + 4] != (unsigned char)0) << 4;
            output |= (unsigned char)(image[i][offset + 5] != (unsigned char)0) << 5;
            output |= (unsigned char)(image[i][offset + 6] != (unsigned char)0) << 6;
            output |= (unsigned char)(image[i][offset + 7] != (unsigned char)0) << 7;
            emb_fwrite(&output, 1, file);
        }
    }
}

/* The distance between the arrays a a and a b of length
 * a size.
 */
float
image_diff(unsigned char *a, unsigned char *b, int size)
{
    int i;
    float total = 0.0;
    for (i=0; i<size; i++) {
        int diff = a[i] - b[i];
        total += diff*diff;
    }
    return total;
}

/* Render the pattern a p to the file with name a fname.
 * Return whether it was successful as an int.
 *
 * Basic Render
 * ------------
 *
 * Backends rendering to nanosvg/stb_image.
 *
 * The caller is responsible for the memory in p.
 */
int
emb_pattern_render(EmbPattern *p, char *fname)
{
/*
    const char *tmp_fname = "libembroidery_temp.svg";
    NSVGimage *image = NULL;
    NSVGrasterizer rast;
    unsigned char *img_data = NULL;
    emb_pattern_writeAuto(p, tmp_fname);
    image = nsvgParseFromFile(tmp_fname, "px", 96.0f);
    img_data = malloc(4*image->width*image->height);
    nsvgRasterize(
        &rast,
        image,
        0, 0, 1,
        img_data,
        image->width,
        image->height,
        4*image->width);
    stbi_write_png(
         fname,
         image->width,
        image->height,
        4,
        img_data,
        4*image->width);
*/
    return 0;
}

/* Simulate the stitching of a pattern, using the image for rendering
 * hints about how to represent the pattern.
 */
int
emb_pattern_simulate(EmbPattern *pattern, char *fname)
{
    emb_pattern_render(pattern, fname);
    return 0;
}

/* . */
EmbImage
embImage_create(int width, int height)
{
    EmbImage image;
    image.width = width;
    image.height = height;
    image.data = malloc(4*width*height);
    return image;

}

/* . */
void
embImage_read(EmbImage *image, char *fname)
{
    /*
    int channels_in_file;
    image->data = stbi_load(
        fname,
        &(image->width),
        &(image->height),
        &channels_in_file,
        3);
    */
}

/* . */
int
embImage_write(EmbImage *image, char *fname)
{
/*
    return stbi_write_png(
         fname,
         image->width,
        image->height,
        4,
        image->data,
        4*image->width);
*/
    return 0;
}

/* . */
void
embImage_free(EmbImage *image)
{
    safe_free(image->data);
}

/* The file is for the management of the main struct: EmbPattern.
 *
 * Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * emb_pattern_free().
 *
 * Returns EmbPattern*
 */
EmbPattern*
emb_pattern_create(void)
{
    EmbPattern* p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_create(), ");
        printf("unable to allocate memory for p\n");
        return 0;
    }
    p->dstJumpsPerTrim = 6;
    p->home.x = 0.0;
    p->home.y = 0.0;
    p->currentColorIndex = 0;
    p->stitch_list = emb_array_create(EMB_STITCH);
    p->thread_list = emb_array_create(EMB_THREAD);
    p->hoop_height = 0.0;
    p->hoop_width = 0.0;
    p->geometry = emb_array_create(EMB_LINE);
    return p;
}

/* a p a length
 */
void
emb_pattern_hideStitchesOverLength(EmbPattern* p, int length)
{
    EmbVector prev;
    int i;
    prev.x = 0.0;
    prev.y = 0.0;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_hideStitchesOverLength(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
        if ((fabs(p->stitch_list->stitch[i].x - prev.x) > length)
         || (fabs(p->stitch_list->stitch[i].y - prev.y) > length)) {
            p->stitch_list->stitch[i].flags |= TRIM;
            p->stitch_list->stitch[i].flags &= ~NORMAL;
        }
        prev.x = p->stitch_list->stitch[i].x;
        prev.y = p->stitch_list->stitch[i].y;
    }
}

/* a pattern a thread
 * Returns int
 */
int
emb_pattern_addThread(EmbPattern *pattern, EmbThread thread)
{
    if (pattern->thread_list->count + 1 > pattern->thread_list->length) {
        if (!emb_array_resize(pattern->thread_list)) {
            return 0;
        }
    }
    pattern->thread_list->thread[pattern->thread_list->count] = thread;
    pattern->thread_list->count++;
    return 1;
}

/* a p
 */
void
emb_pattern_fixColorCount(EmbPattern* p)
{
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_fixColorCount(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
/*        printf("%d %d\n", list->stitch.color, maxColorIndex);*/
        maxColorIndex = EMB_MAX(maxColorIndex, p->stitch_list->stitch[i].color);
    }
    if (p->thread_list->count == 0 || maxColorIndex == 0) {
        emb_pattern_addThread(p, black_thread);
    }
    else {
        if (maxColorIndex > 0) {
            while (p->thread_list->count <= maxColorIndex) {
/*        printf("%d %d\n", p->n_threads, maxColorIndex);*/
                emb_pattern_addThread(p, embThread_getRandom());
            }
        }
    }
    /*
    while (p->threadLists->count > (maxColorIndex + 1)) {
        TODO: erase last color    p->threadList.pop_back();
    }
    */
}

/* Copies all of the Embstitch_list data to
 * EmbPolylineObjectList data for pattern (a p).
 */
void
emb_pattern_copystitch_listToPolylines(EmbPattern* p)
{
    int breakAtFlags, i;
    EmbPoint point;
    EmbColor color;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_copystitch_listToPolylines(), ");
        printf("p argument is null\n");
        return;
    }

    breakAtFlags = (STOP | JUMP | TRIM);

    for (i = 0; i < p->stitch_list->count; i++) {
        EmbArray *pointList = 0;
        for (; i < p->stitch_list->count; i++) {
            EmbStitch st = p->stitch_list->stitch[i];
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    pointList = emb_array_create(EMB_POINT);
                    color = p->thread_list->thread[st.color].color;
                }
                point.position.x = st.x;
                point.position.y = st.y;
                emb_array_addPoint(pointList, point);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolyline currentPolyline;
            currentPolyline.pointList = pointList;
            currentPolyline.color = color;
            /* TODO: Determine what the correct value should be */
            currentPolyline.lineType = 1;

            emb_array_addPolyline(p->geometry, currentPolyline);
        }
    }
}

/* Copies all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void
emb_pattern_copyPolylinesTostitch_list(EmbPattern* p)
{
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_copyPolylinesTostitch_list(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->geometry->count; i++) {
        EmbPolyline currentPoly;
        EmbArray* currentPointList;
        EmbThread thread;

        if (p->geometry->geometry[i].type != EMB_POLYLINE) {
            continue;
        }

        currentPoly = p->geometry->geometry[i].object.polyline;
        currentPointList = currentPoly.pointList;

        string_copy(thread.catalogNumber, "");
        thread.color = currentPoly.color;
        string_copy(thread.description, "");
        emb_pattern_addThread(p, thread);

        if (!firstObject) {
            emb_pattern_addStitchAbs(p,
                currentPointList->geometry[0].object.point.position.x,
                currentPointList->geometry[0].object.point.position.y, TRIM, 1);
            emb_pattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        emb_pattern_addStitchAbs(p,
            currentPointList->geometry[0].object.point.position.x,
            currentPointList->geometry[0].object.point.position.y,
            JUMP,
            1);
        for (j = 1; j < currentPointList->count; j++) {
            EmbVector v = currentPointList->geometry[j].object.point.position;
            emb_pattern_addStitchAbs(p, v.x, v.y, NORMAL, 1);
        }
        firstObject = 0;
    }
    emb_pattern_addStitchRel(p, 0.0, 0.0, END, 1);
}

/* Moves all of the Embstitch_list data to EmbPolylineObjectList
 * data for pattern (a p).
 */
void
emb_pattern_movestitch_listToPolylines(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_movestitch_listToPolylines(), p argument is null\n");
        return;
    }
    emb_pattern_copystitch_listToPolylines(p);
    /* Free the stitch_list and threadList since their data has now been transferred to polylines */
    p->stitch_list->count = 0;
    p->thread_list->count = 0;
}

/* Moves all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void
emb_pattern_movePolylinesTostitch_list(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_movePolylinesTostitch_list(), p argument is null\n");
        return;
    }
    emb_pattern_copyPolylinesTostitch_list(p);
}

/* Adds a stitch to the pattern (a p) at the absolute position
 * (a x,a y). Positive y is up. Units are in millimeters.
 */
void
emb_pattern_addStitchAbs(EmbPattern* p, EmbReal x, EmbReal y,
                            int flags, int isAutoColorIndex)
{
    EmbStitch s;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addStitchAbs(), ");
        printf("p argument is null\n");
        return;
    }

    if (flags & END) {
        if (p->stitch_list->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitch_list->stitch[p->stitch_list->count - 1].flags & END) {
            printf("ERROR: emb-pattern.c emb_pattern_addStitchAbs(), found multiple END stitches\n");
            return;
        }
        emb_pattern_fixColorCount(p);
        /* HideStitchesOverLength(127); TODO: fix or remove this */
    }

    if (flags & STOP) {
        if (p->stitch_list->count == 0) {
            return;
        }
        if (isAutoColorIndex) {
            p->currentColorIndex++;
        }
    }

    /* NOTE: If the stitch_list is empty, we will create it before adding
        stitches to it. The first coordinate will be the HOME position. */
    if (p->stitch_list->count == 0) {
        /* NOTE: Always HOME the machine before starting any stitching */
        EmbStitch h;
        h.x = p->home.x;
        h.y = p->home.y;
        h.flags = JUMP;
        h.color = p->currentColorIndex;
        emb_array_addStitch(p->stitch_list, h);
    }
    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    emb_array_addStitch(p->stitch_list, s);
}

/* Adds a stitch to the pattern (a p) at the relative position
 * (a dx,a dy) to the previous stitch. Positive y is up.
 * Units are in millimeters.
 */
void
emb_pattern_addStitchRel(EmbPattern* p, EmbReal dx, EmbReal dy,
                            int flags, int isAutoColorIndex)
{
    EmbReal x, y;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addStitchRel(), p argument is null\n");
        return;
    }
    if (p->stitch_list->count > 0) {
        EmbStitch st = p->stitch_list->stitch[p->stitch_list->count - 1];
        x = st.x + dx;
        y = st.y + dy;
    } else {
        /* NOTE: The stitch_list is empty, so add it to the HOME position.
         * The embstitch_list_create function will ensure the first coordinate is at the HOME position. */
        x = p->home.x + dx;
        y = p->home.y + dy;
    }
    emb_pattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

/* Change the currentColorIndex of pattern a p to a index.
 */
void
emb_pattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_changeColor(), p argument is null\n");
        return;
    }
    p->currentColorIndex = index;
}

/* Very simple scaling of the x and y axis for every point.
 * Doesn't insert or delete stitches to preserve density.
 */
void
emb_pattern_scale(EmbPattern* p, EmbReal scale)
{
    int i;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_scale(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x *= scale;
        p->stitch_list->stitch[i].y *= scale;
    }
}

/* Returns an EmbRect that encapsulates all stitches and objects in the
 * pattern (a p).
 */
EmbRect
emb_pattern_calcBoundingBox(EmbPattern* p)
{
    EmbRect r;
    EmbStitch pt;
    int i, j;

    r.left = 0;
    r.right = 0;
    r.top = 0;
    r.bottom = 0;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_calcBoundingBox(), ");
        printf("p argument is null\n");
        return r;
    }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
            and stitches, if the rectangle isn't reasonable, then return a default rect */
    if ((p->stitch_list->count == 0) && (p->geometry->count == 0)) {
        r.top = 0.0;
        r.left = 0.0;
        r.bottom = 1.0;
        r.right = 1.0;
        return r;
    }
    r.left = 99999.0;
    r.top =  99999.0;
    r.right = -99999.0;
    r.bottom = -99999.0;

    for (i = 0; i < p->stitch_list->count; i++) {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitch_list->stitch[i];
        if (!(pt.flags & TRIM)) {
            r.left = EMB_MIN(r.left, pt.x);
            r.top = EMB_MIN(r.top, pt.y);
            r.right = EMB_MAX(r.right, pt.x);
            r.bottom = EMB_MAX(r.bottom, pt.y);
        }
    }

    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry g = p->geometry->geometry[i];
        switch (g.type) {
        case EMB_ARC: {
            /* TODO: emb_pattern_calcBoundingBox for arcs,
            for now just checks the start point */
            EmbArc arc = g.object.arc;
            r.left = EMB_MIN(r.left, arc.start.x);
            r.top = EMB_MIN(r.top, arc.start.y);
            r.right = EMB_MAX(r.right, arc.start.x);
            r.bottom = EMB_MAX(r.bottom, arc.start.y);
            break;
        }
        case EMB_CIRCLE: {
            EmbCircle circle = g.object.circle;
            r.left = EMB_MIN(r.left, circle.center.x - circle.radius);
            r.top = EMB_MIN(r.top, circle.center.y - circle.radius);
            r.right = EMB_MAX(r.right, circle.center.x + circle.radius);
            r.bottom = EMB_MAX(r.bottom, circle.center.y + circle.radius);
            break;
        }
        case EMB_ELLIPSE: {
            /* TODO: account for rotation */
            EmbEllipse ellipse = g.object.ellipse;
            r.left = EMB_MIN(r.left, ellipse.center.x - ellipse.radius.x);
            r.top = EMB_MIN(r.top, ellipse.center.y - ellipse.radius.y);
            r.right = EMB_MAX(r.right, ellipse.center.x + ellipse.radius.x);
            r.bottom = EMB_MAX(r.bottom, ellipse.center.y + ellipse.radius.y);
            break;
        }
        case EMB_LINE: {
            EmbLine line = g.object.line;
            r.left = EMB_MIN(r.left, line.start.x);
            r.left = EMB_MIN(r.left, line.end.x);
            r.top = EMB_MIN(r.top, line.start.y);
            r.top = EMB_MIN(r.top, line.end.y);
            r.right = EMB_MAX(r.right, line.start.x);
            r.right = EMB_MAX(r.right, line.end.x);
            r.bottom = EMB_MAX(r.bottom, line.start.y);
            r.bottom = EMB_MAX(r.bottom, line.end.y);
            break;
        }
        case EMB_POINT: {
            EmbVector point = g.object.point.position;
            r.left = EMB_MIN(r.left, point.x);
            r.top = EMB_MIN(r.top, point.y);
            r.right = EMB_MAX(r.right, point.x);
            r.bottom = EMB_MAX(r.bottom, point.y);
            break;
        }
        case EMB_POLYGON: {
            EmbArray *polygon = g.object.polygon.pointList;
            for (j=0; j < polygon->count; j++) {
                /* TODO: emb_pattern_calcBoundingBox for polygons */
            }
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *polyline = g.object.polyline.pointList;
            for (j=0; j < polyline->count; j++) {
                /* TODO: emb_pattern_calcBoundingBox for polylines */
            }
            break;
        }
        case EMB_RECT: {
            EmbRect rect = g.object.rect;
            r.left = EMB_MIN(r.left, rect.left);
            r.top = EMB_MIN(r.top, rect.top);
            r.right = EMB_MAX(r.right, rect.right);
            r.bottom = EMB_MAX(r.bottom, rect.bottom);
            break;
        }
        case EMB_SPLINE: {
            /* EmbBezier bezier;
            bezier = p->splines->spline[i].bezier; */
            /* TODO: emb_pattern_calcBoundingBox for splines */
            break;
        }
        default:
            break;
        }
    }

    return r;
}

/* Flips the entire pattern (a p) horizontally about the y-axis.
 */
void
emb_pattern_flipHorizontal(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_flipHorizontal(), ");
        printf("p argument is null\n");
        return;
    }
    emb_pattern_flip(p, 1, 0);
}

/* Flips the entire pattern (a p) vertically about the x-axis.
 */
void
emb_pattern_flipVertical(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_flipVertical(), ");
        printf("p argument is null\n");
        return;
    }
    emb_pattern_flip(p, 0, 1);
}

/* Flips the entire pattern (a p) horizontally about the x-axis if (a horz) is true.
 *  Flips the entire pattern (a p) vertically about the y-axis if (a vert) is true.
 */
void
emb_pattern_flip(EmbPattern* p, int horz, int vert)
{
    int i, j;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_flip(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        if (horz) {
            p->stitch_list->stitch[i].x *= -1.0;
        }
        if (vert) {
            p->stitch_list->stitch[i].y *= -1.0;
        }
    }

    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry *g = &(p->geometry->geometry[i]);
        switch (g->type) {
        case EMB_ARC: {
            if (horz) {
                g->object.arc.start.x *= -1.0;
                g->object.arc.mid.x *= -1.0;
                g->object.arc.end.x *= -1.0;
            }
            if (vert) {
                g->object.arc.start.y *= -1.0;
                g->object.arc.mid.y *= -1.0;
                g->object.arc.end.y *= -1.0;
            }
            break;
        }
        case EMB_LINE: {
            if (horz) {
                g->object.line.start.x *= -1.0;
                g->object.line.end.x *= -1.0;
            }
            if (vert) {
                g->object.line.start.y *= -1.0;
                g->object.line.end.y *= -1.0;
            }
            break;
        }
        case EMB_CIRCLE: {
            if (horz) {
                g->object.circle.center.x *= -1.0;
            }
            if (vert) {
                g->object.circle.center.y *= -1.0;
            }
            break;
        }
        case EMB_ELLIPSE:
            if (horz) {
                g->object.ellipse.center.x *= -1.0;
            }
            if (vert) {
                g->object.ellipse.center.y *= -1.0;
            }
            break;
        case EMB_PATH: {
            EmbArray *point_list = g->object.path.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[j].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[j].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_POINT:
            if (horz) {
                g->object.point.position.x *= -1.0;
            }
            if (vert) {
                g->object.point.position.y *= -1.0;
            }
            break;
        case EMB_POLYGON: {
            EmbArray *point_list = g->object.polygon.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[i].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[i].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *point_list = g->object.polygon.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[j].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[j].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_RECT: {
            if (horz) {
                g->object.rect.left *= -1.0;
                g->object.rect.right *= -1.0;
            }
            if (vert) {
                g->object.rect.top *= -1.0;
                g->object.rect.bottom *= -1.0;
            }
            break;
        }
        case EMB_SPLINE:
            /* TODO */
            break;
        default:
            break;
        }
    }
}

/* a p
 */
void
emb_pattern_combineJumpStitches(EmbPattern* p)
{
    int jumpCount = 0, i;
    EmbArray *newList;
    EmbStitch j;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_combineJumpStitches(), ");
        printf("p argument is null\n");
        return;
    }
    newList = emb_array_create(EMB_STITCH);
    for (i = 0; i < p->stitch_list->count; i++) {
        EmbStitch st = p->stitch_list->stitch[i];
        if (st.flags & JUMP) {
            if (jumpCount == 0) {
                j = st;
            } else {
                j.x += st.x;
                j.y += st.y;
            }
            jumpCount++;
        } else {
            if (jumpCount > 0) {
                emb_array_addStitch(newList, j);
            }
            emb_array_addStitch(newList, st);
        }
    }
    emb_array_free(p->stitch_list);
    p->stitch_list = newList;
}

/* \todo The params determine the max XY movement rather than the length.
 * They need renamed or clarified further.
 */
void
emb_pattern_correctForMaxStitchLength(EmbPattern* p,
                        EmbReal maxStitchLength, EmbReal maxJumpLength)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_correctForMaxStitchLength(), ");
        printf("p argument is null\n");
        return;
    }
    if (p->stitch_list->count > 1) {
        int i, j, splits;
        EmbReal maxXY, maxLen, addX, addY;
        EmbArray *newList = emb_array_create(EMB_STITCH);
        for (i=1; i < p->stitch_list->count; i++) {
            EmbStitch st = p->stitch_list->stitch[i];
            EmbReal xx = st.x;
            EmbReal yy = st.y;
            EmbReal dx = p->stitch_list->stitch[i-1].x - xx;
            EmbReal dy = p->stitch_list->stitch[i-1].y - yy;
            if ((fabs(dx) > maxStitchLength) || (fabs(dy) > maxStitchLength)) {
                maxXY = EMB_MAX(fabs(dx), fabs(dy));
                if (st.flags & (JUMP | TRIM)) {
                    maxLen = maxJumpLength;
                } else {
                    maxLen = maxStitchLength;
                }
                splits = (int)ceil((EmbReal)maxXY / maxLen);

                if (splits > 1) {
                    addX = (EmbReal)dx / splits;
                    addY = (EmbReal)dy / splits;

                    for (j = 1; j < splits; j++) {
                        EmbStitch s;
                        s = st;
                        s.x = xx + addX * j;
                        s.y = yy + addY * j;
                        emb_array_addStitch(newList, s);
                    }
                }
            }
            emb_array_addStitch(newList, st);
        }
        emb_array_free(p->stitch_list);
        p->stitch_list = newList;
    }
    emb_pattern_end(p);
}

/* Center the pattern a p.
 */
void
emb_pattern_center(EmbPattern* p)
{
    /* TODO: review this. currently not used in anywhere.
        Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_center(), p argument is null\n");
        return;
    }
    boundingRect = emb_pattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (boundingRect.right- boundingRect.left) / 2.0);
    moveTop = (int)(boundingRect.top - (boundingRect.bottom - boundingRect.top) / 2.0);

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x -= moveLeft;
        p->stitch_list->stitch[i].y -= moveTop;
    }
}

/* TODO: Description needed.
 */
void
emb_pattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
    int hasRead, stub_len, format;
    char extractName[200];

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_loadExternalColorFile(), p argument is null\n");
        return;
    }
    if (!fileName) {
        printf("ERROR: emb-pattern.c emb_pattern_loadExternalColorFile(), fileName argument is null\n");
        return;
    }

    string_copy(extractName, fileName);
    format = emb_identify_format(fileName);
    stub_len = string_len(fileName) - string_len(formatTable[format].extension);
    extractName[stub_len] = 0;
    string_cat(extractName, ".edr");
    hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_EDR);
    if (!hasRead) {
        extractName[stub_len] = 0;
        string_cat(extractName,".rgb");
        hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_RGB);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        string_cat(extractName,".col");
        hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_COL);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        string_cat(extractName,".inf");
        hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_INF);
    }
}

/* Frees all memory allocated in the pattern (a p).
 */
void
emb_pattern_free(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_free(), p argument is null\n");
        return;
    }
    emb_array_free(p->stitch_list);
    emb_array_free(p->thread_list);
    emb_array_free(p->geometry);
    safe_free(p);
}

/* Adds a circle object to pattern (a p) with its center at the absolute
 * position (a cx,a cy) with a radius of (a r). Positive y is up.
 * Units are in millimeters.
 */
void
emb_pattern_addCircleAbs(EmbPattern* p, EmbCircle circle)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addCircleObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addCircle(p->geometry, circle);
}

/* Adds an ellipse object to pattern (a p) with its center at the
 * absolute position (a cx,a cy) with radii of (a rx,a ry). Positive y is up.
 * Units are in millimeters.
 */
void
emb_pattern_addEllipseAbs(EmbPattern* p, EmbEllipse ellipse)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addEllipseObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addEllipse(p->geometry, ellipse);
}

/* Adds a line object to pattern (a p) starting at the absolute position
 * (a x1,a y1) and ending at the absolute position (a x2,a y2).
 * Positive y is up. Units are in millimeters.
 */
void
emb_pattern_addLineAbs(EmbPattern* p, EmbLine line)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addLineObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addLine(p->geometry, line);
}

/* .
 */
void
emb_pattern_addPathAbs(EmbPattern* p, EmbPath obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPathObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c emb_pattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }

    emb_array_addPath(p->geometry, obj);
}

/*! Adds a point object to pattern (a p) at the absolute position (a x,a y). Positive y is up. Units are in millimeters. */
void
emb_pattern_addPointAbs(EmbPattern* p, EmbPoint obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPointObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addPoint(p->geometry, obj);
}

void
emb_pattern_addPolygonAbs(EmbPattern* p, EmbPolygon obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolygonObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    emb_array_addPolygon(p->geometry, obj);
}

void
emb_pattern_addPolylineObjectAbs(EmbPattern* p, EmbPolyline obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolylineObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolylineObjectAbs(), obj->pointList is empty\n");
        return;
    }
    emb_array_addPolyline(p->geometry, obj);
}

/* Adds a rectangle object to pattern (a p) at the absolute position
 * (a x,a y) with a width of (a w) and a height of (a h).
 * Positive y is up. Units are in millimeters.
 */
void
emb_pattern_addRectAbs(EmbPattern* p, EmbRect rect)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addRectObjectAbs(), p argument is null\n");
        return;
    }
    emb_array_addRect(p->geometry, rect);
}

void
emb_pattern_end(EmbPattern *p)
{
    if (p->stitch_list->count == 0) {
        return;
    }
    /* Check for an END stitch and add one if it is not present */
    if (p->stitch_list->stitch[p->stitch_list->count-1].flags != END) {
        emb_pattern_addStitchRel(p, 0, 0, END, 1);
    }
}


int
emb_pattern_color_count(EmbPattern *pattern, EmbColor startColor)
{
    int numberOfColors = 0, i;
    EmbColor color = startColor;
    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbColor newColor;
        EmbStitch st;

        st = pattern->stitch_list->stitch[i];

        newColor = pattern->thread_list->thread[st.color].color;
        if (embColor_distance(newColor, color) != 0) {
            numberOfColors++;
            color = newColor;
        }
        else if (st.flags & END || st.flags & STOP) {
            numberOfColors++;
        }

        while (pattern->stitch_list->stitch[i+1].flags == st.flags) {
            i++;
            if (i >= pattern->stitch_list->count-2) {
                break;
            }
        }
    }
    return numberOfColors;
}


void
emb_pattern_designDetails(EmbPattern *pattern)
{
    int colors, num_stitches, real_stitches, jump_stitches, trim_stitches;
    int unknown_stitches;
    EmbRect bounds;

    puts("Design Details");
    bounds = emb_pattern_calcBoundingBox(pattern);

    colors = 1;
    num_stitches = pattern->stitch_list->count;
    real_stitches = 0;
    jump_stitches = 0;
    trim_stitches = 0;
    unknown_stitches = 0;
    bounds = emb_pattern_calcBoundingBox(pattern);

    if (emb_verbose > 1) {
        printf("colors: %d\n", colors);
        printf("num_stitches: %d\n", num_stitches);
        printf("real_stitches: %d\n", real_stitches);
        printf("jump_stitches: %d\n", jump_stitches);
        printf("trim_stitches: %d\n", trim_stitches);
        printf("unknown_stitches: %d\n", unknown_stitches);
        printf("num_colors: %d\n", pattern->thread_list->count);
        printf("bounds.left: %f\n", bounds.left);
        printf("bounds.right: %f\n", bounds.right);
        printf("bounds.top: %f\n", bounds.top);
        printf("bounds.bottom: %f\n", bounds.bottom);
    }
/*
    EmbReal minx = 0.0, maxx = 0.0, miny = 0.0, maxy = 0.0;
    EmbReal min_stitchlength = 999.0;
    EmbReal max_stitchlength = 0.0;
    EmbReal total_stitchlength = 0.0;
    int number_of_minlength_stitches = 0;
    int number_of_maxlength_stitches = 0;

    EmbReal xx = 0.0, yy = 0.0;
    EmbReal length = 0.0;

    if (num_stitches == 0) {
        QMessageBox::warning(this, tr("No Design Loaded"), tr("<b>A design needs to be loaded or created before details can be determined.</b>"));
        return;
    }
    QVector<EmbReal> stitchLengths;

    EmbReal totalColorLength = 0.0;
    int i;
    for (i = 0; i < num_stitches; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        EmbReal dx, dy;
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        length=sqrt(dx * dx + dy * dy);
        totalColorLength += length;
        if(i > 0 && embstitch_list_getAt(pattern->stitch_list, i-1).flags != NORMAL)
            length = 0.0; //can't count first normal stitch;
        if(!(embstitch_list_getAt(pattern->stitch_list, i).flags & (JUMP | TRIM)))
        {
            real_stitches++;
            if(length > max_stitchlength) { max_stitchlength = length; number_of_maxlength_stitches = 0; }
            if(length == max_stitchlength) number_of_maxlength_stitches++;
            if(length > 0 && length < min_stitchlength)
            {
                min_stitchlength = length;
                number_of_minlength_stitches = 0;
            }
            if(length == min_stitchlength) number_of_minlength_stitches++;
            total_stitchlength += length;
            if(xx < minx) minx = xx;
            if(xx > maxx) maxx = xx;
            if(yy < miny) miny = yy;
            if(yy > maxy) maxy = yy;
        }
        if (st.flags & JUMP) {
            jump_stitches++;
        }
        if (st.flags & TRIM) {
            trim_stitches++;
        }
        if (st.flags & STOP) {
            stitchLengths.push_back(totalColorLength);
            totalColorLength = 0;
            colors++;
        }
        if (st.flags & END) {
            stitchLengths.push_back(totalColorLength);
        }
    }

    //second pass to fill bins now that we know max stitch length
#define NUMBINS 10
    int bin[NUMBINS+1];
    int i;
    for (i = 0; i <= NUMBINS; i++) {
        bin[i]=0;
    }

    for (i = 0; i < num_stitches; i++) {
        dx = embstitch_list_getAt(pattern->stitch_list, i).xx - xx;
        dy = embstitch_list_getAt(pattern->stitch_list, i).yy - yy;
        xx = embstitch_list_getAt(pattern->stitch_list, i).xx;
        yy = embstitch_list_getAt(pattern->stitch_list, i).yy;
        if(i > 0 && embstitch_list_getAt(pattern->stitch_list, i-1).flags == NORMAL && embstitch_list_getAt(pattern->stitch_list, i).flags == NORMAL)
        {
            length=sqrt(dx * dx + dy * dy);
            bin[int(floor(NUMBINS*length/max_stitchlength))]++;
        }
    }

    EmbReal binSize = max_stitchlength / NUMBINS;

    QString str;
    int i;
    for (i = 0; i < NUMBINS; i++) {
        str += QString::number(binSize * (i), 'f', 1) + " - " + QString::number(binSize * (i+1), 'f', 1) + " mm: " +  QString::number(bin[i]) + "\n\n";
    }

    puts("Stitches: %d\n", num_stitches);
    puts("Colors: %d\n", num_colors);
    puts("Jumps: %d\n", jump_stitches);
    puts("Top: %f mm", bounds.top);
    puts("Left: %f mm", bounds.left);
    puts("Bottom: %f mm", bounds.bottom);
    puts("Right: %f mm", bounds.right);
    puts("Width: %f mm", bounds.right - bounds.left);
    puts("Height: %f mm", bounds.bottom - bounds.top);
    grid->addWidget(new QLabel(tr("\nStitch Distribution: \n")),9,0,1,2);
    grid->addWidget(new QLabel(str), 10, 0, 1, 1);
    grid->addWidget(new QLabel(tr("\nThread Length By Color: \n")),11,0,1,2);
    int currentRow = 12;

    int i;
    for (i = 0; i < num_colors; i++) {
        QFrame *frame = new QFrame();
        frame->setGeometry(0,0,30,30);
        QPalette palette = frame->palette();
        EmbColor t = embThreadList_getAt(pattern->threadList, i).color;
        palette.setColor(backgroundRole(), QColor( t.r, t.g, t.b ) );
        frame->setPalette( palette );
        frame->setAutoFillBackground(true);
        grid->addWidget(frame, currentRow,0,1,1);
        debug_message("size: %d i: %d", stitchLengths.size(), i);
        grid->addWidget(new QLabel(QString::number(stitchLengths.at(i)) + " mm"), currentRow,1,1,1);
        currentRow++;
    }

    QDialogButtonBox buttonbox(Qt::Horizontal, &dialog);
    QPushButton button(&dialog);
    button.setText("Ok");
    buttonbox.addButton(&button, QDialogButtonBox::AcceptRole);
    buttonbox.setCenterButtons(true);
    connect(&buttonbox, SIGNAL(accepted()), &dialog, SLOT(accept()));

    grid->addWidget(&buttonbox, currentRow, 0, 1, 2);
*/
}


/*
 *
 */
int
convert(const char *inf, const char *outf)
{
    EmbPattern* p = 0;
    int reader, writer;

    p = emb_pattern_create();
    if (!p) {
        printf("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    if (!emb_pattern_readAuto(p, inf)) {
        printf("ERROR: convert(), reading file was unsuccessful: %s\n", inf);
        emb_pattern_free(p);
        return 1;
    }

    reader = emb_identify_format(inf);
    writer = emb_identify_format(outf);
    if (formatTable[reader].type == EMBFORMAT_OBJECTONLY) {
        if (formatTable[writer].type == EMBFORMAT_STITCHONLY) {
            emb_pattern_movePolylinesTostitch_list(p);
        }
    }

    if (!emb_pattern_writeAuto(p, outf)) {
        printf("ERROR: convert(), writing file %s was unsuccessful\n", outf);
        emb_pattern_free(p);
        return 1;
    }

    emb_pattern_free(p);
    return 0;
}

/* The Pattern Properties
 * -----------------------------------------------------------------------------
 */

/* a pattern
 * Returns float
 */
float
emb_pattern_totalStitchLength(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    float result = 0.0;
    int i;
    for (i = 1; i < sts->count; i++) {
        EmbStitch st = sts->stitch[i];
        EmbReal length = 0.0;
        EmbVector delta;
        delta.x = st.x - sts->stitch[i-1].x;
        delta.y = st.y - sts->stitch[i-1].y;
        length = emb_vector_length(delta);
        if (st.flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            result += length;
        }
    }
    return result;
}

float emb_pattern_minimumStitchLength(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    float result = 1.0e10;
    int i;
    for (i = 1; i < sts->count; i++) {
        EmbReal length = 0.0;
        EmbVector delta;
        delta.x = sts->stitch[i].x - sts->stitch[i-1].x;
        delta.y = sts->stitch[i].y - sts->stitch[i-1].y;
        length = emb_vector_length(delta);
        if (sts->stitch[i].flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            if (length < result) {
                result = length;
            }
        }
    }
    return result;
}

float emb_pattern_maximumStitchLength(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    float result = 0.0;
    int i;
    for (i = 1; i < sts->count; i++) {
        EmbReal length = 0.0;
        EmbVector delta;
        delta.x = sts->stitch[i].x - sts->stitch[i-1].x;
        delta.y = sts->stitch[i].y - sts->stitch[i-1].y;
        length = emb_vector_length(delta);
        if (sts->stitch[i].flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            if (length > result) {
                result = length;
            }
        }
    }
    return result;
}

void emb_pattern_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS)
{
    int i;
    float max_stitch_length = emb_pattern_maximumStitchLength(pattern);
    EmbArray *sts = pattern->stitch_list;
    for (i = 0; i <= NUMBINS; i++) {
        bin[i] = 0;
    }

    for (i = 1; i < sts->count; i++) {
        if (sts->stitch[i].flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            EmbVector delta;
            float length;
            delta.x = sts->stitch[i].x - sts->stitch[i-1].x;
            delta.y = sts->stitch[i].y - sts->stitch[i-1].x;
            length = emb_vector_length(delta);
            bin[(int)(floor(NUMBINS*length/max_stitch_length))]++;
        }
    }
}

int emb_pattern_realStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int real_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (!(sts->stitch[i].flags & (JUMP | TRIM | END))) {
            real_stitches++;
        }
    }
    return real_stitches;
}

int emb_pattern_jumpStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int jump_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (sts->stitch[i].flags & JUMP) {
            jump_stitches++;
        }
    }
    return jump_stitches;
}


int emb_pattern_trimStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int trim_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (sts->stitch[i].flags & TRIM) {
            trim_stitches++;
        }
    }
    return trim_stitches;
}

/* The Thread Management System
 * -----------------------------------------------------------------------------
 */

int
threadColor(const char *name, int brand)
{
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (string_equals(brand_codes[brand].codes[i].name, name)) {
            return brand_codes[brand].codes[i].hex_code;
        }
    }
    return -1;
}

int
threadColorNum(unsigned int color, int brand)
{
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand].codes[i].hex_code == color) {
            return brand_codes[brand].codes[i].manufacturer_code;
        }
    }

    return -1;
}

const char*
threadColorName(unsigned int color, int brand)
{
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand].codes[i].hex_code == color) {
            return brand_codes[brand].codes[i].name;
        }
    }

    return "COLOR NOT FOUND";
}

/* The Geometry System
 * -----------------------------------------------------------------------------
 */

/* . */
EmbReal
emb_get_real(EmbGeometry *g, int id)
{
    switch (id) {
    case EMB_REAL_ARC_RADIUS: {
        break;
    }
    case EMB_REAL_START_ANGLE: {
        break;
    }
    case EMB_REAL_END_ANGLE: {
        break;
    }
    case EMB_REAL_ARC_DIAMETER: {
        break;
    }
    case EMB_REAL_ARC_AREA: {
        break;
    }
    case EMB_REAL_ARC_CIRCUMFERENCE: {
        break;
    }
    case EMB_REAL_ARC_LENGTH: {
        break;
    }
    case EMB_REAL_CHORD: {
        break;
    }
    case EMB_REAL_TEXT_SIZE: {
        break;
    }
    case EMB_REAL_RADIUS_MAJOR: {
        break;
    }
    case EMB_REAL_RADIUS_MINOR: {
        break;
    }
    case EMB_REAL_DIAMETER_MAJOR: {
        break;
    }
    case EMB_REAL_DIAMETER_MINOR: {
        break;
    }
    case EMB_REAL_LENGTH: {
        break;
    }
    case EMB_REAL_AREA: {
        break;
    }
    case EMB_REAL_ANGLE: {
        switch (g->type) {
        case EMB_CIRCLE: {
            puts("ERROR: CIRCLE has no REAL_ANGLE property.");
            return 0.0f;
        }
        default:
            break;
        }
        break;
    }
    case EMB_REAL_WIDTH: {
        switch (g->type) {
        case EMB_CIRCLE: {
            return 2.0f * g->object.circle.radius;
        }
        case EMB_ELLIPSE: {
            return 2.0f * g->object.ellipse.radius.x;
        }
        default:
            break;
        }
        break;
    }
    case EMB_REAL_HEIGHT: {
        switch (g->type) {
        case EMB_CIRCLE: {
            return 2.0f * g->object.circle.radius;
        }
        case EMB_ELLIPSE: {
            return 2.0f * g->object.ellipse.radius.y;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    return 0.0f;    
}

/* . */
EmbVector
emb_get_vector(EmbGeometry *g, int id)
{
    EmbVector v;
    v.x = 0.0f;
    v.y = 0.0f;
    switch (g->type) {
    case EMB_CIRCLE: {
        break;
    }
    default:
        break;
    }
    return v;
}

/* . */
int
emb_get_int(EmbGeometry *g, int id)
{
    switch (g->type) {
    case EMB_CIRCLE: {
        break;
    }
    default:
        break;
    }
    return 0;
}

/* . */
void
emb_set_real(EmbGeometry *g, int id, EmbReal r)
{
    switch (id) {
    case EMB_REAL_ARC_RADIUS: {
        break;
    }
    case EMB_REAL_START_ANGLE: {
        break;
    }
    case EMB_REAL_END_ANGLE: {
        break;
    }
    case EMB_REAL_ARC_DIAMETER: {
        break;
    }
    case EMB_REAL_ARC_AREA: {
        break;
    }
    case EMB_REAL_ARC_CIRCUMFERENCE: {
        break;
    }
    case EMB_REAL_ARC_LENGTH: {
        break;
    }
    case EMB_REAL_CHORD: {
        break;
    }
    case EMB_REAL_TEXT_SIZE: {
        break;
    }
    case EMB_REAL_RADIUS_MAJOR: {
        break;
    }
    case EMB_REAL_RADIUS_MINOR: {
        break;
    }
    case EMB_REAL_DIAMETER_MAJOR: {
        break;
    }
    case EMB_REAL_DIAMETER_MINOR: {
        break;
    }
    case EMB_REAL_LENGTH: {
        break;
    }
    case EMB_REAL_AREA: {
        break;
    }
    case EMB_REAL_ANGLE: {
        switch (g->type) {
        case EMB_CIRCLE: {
            break;
        }
        default:
            break;
        }
        break;
    }
    case EMB_REAL_WIDTH:
    case EMB_REAL_HEIGHT:
        break;
    default:
        break;
    }
}

/* . */
void
emb_set_vector(EmbGeometry *g, int id, EmbVector v)
{
    switch (id) {
    case EMB_VECTOR_ARC_START_POINT: {
        switch (g->type) {
        case EMB_CIRCLE: {
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

/* . */
void
emb_set_int(EmbGeometry *g, int id, int i)
{
    switch (g->type) {
    case EMB_CIRCLE: {
        break;
    }
    default:
        break;
    }
}
