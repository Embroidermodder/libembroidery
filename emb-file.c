/**
Type of sector
*/
#define CompoundFileSector_MaxRegSector 0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector 0xFFFFFFFC
#define CompoundFileSector_FAT_Sector 0xFFFFFFFD
#define CompoundFileSector_EndOfChain 0xFFFFFFFE
#define CompoundFileSector_FreeSector 0xFFFFFFFF

/**
Type of directory object
*/
#define ObjectTypeUnknown 0x00 /*!< Probably unallocated    */
#define ObjectTypeStorage 0x01 /*!< a directory type object */
#define ObjectTypeStream 0x02 /*!< a file type object      */
#define ObjectTypeRootEntry 0x05 /*!< the root entry          */

/**
Special values for Stream Identifiers
*/
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /*!< All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream 0xFFFFFFFF /*!< There is no valid stream Id            */

/* TODO: This list needs reviewed in case some stitch formats also can contain object data (EMBFORMAT_STCHANDOBJ). */

const EmbFormatList formatTable[100] = {
    { ".10o", "Toyota Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".100", "Toyota Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".art", "Bernina Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".bmc", "Bitmap Cache Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".bro", "Bits & Volts Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".cnd", "Melco Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".col", "Embroidery Thread Color Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".csd", "Singer Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".csv", "Comma Separated Values Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".dat", "Barudan Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".dem", "Melco Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".dsb", "Barudan Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".dst", "Tajima Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".dsz", "ZSK USA Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".dxf", "Drawing Exchange Format", ' ', ' ', EMBFORMAT_OBJECTONLY },
    { ".edr", "Embird Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".emd", "Elna Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".exp", "Melco Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".exy", "Eltac Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".eys", "Sierra Expanded Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".fxy", "Fortron Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".gc", "Smoothie G-Code Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".gnc", "Great Notions Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".gt", "Gold Thread Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".inb", "Inbro Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".inf", "Embroidery Color Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".jef", "Janome Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".ksm", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".max", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".mit", "Mitsubishi Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".new", "Ameco Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".ofm", "Melco Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".pcd", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pcm", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".pcq", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pcs", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pec", "Brother Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pel", "Brother Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".pem", "Brother Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".pes", "Brother Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".phb", "Brother Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".phc", "Brother Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".plt", "AutoCAD Plot Drawing Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".rgb", "RGB Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".sew", "Janome Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".sst", "Sunstar Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".stx", "Data Stitch Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".svg", "Scalable Vector Graphics", 'U', 'U', EMBFORMAT_OBJECTONLY },
    { ".t01", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".t09", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".tap", "Happy Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".thr", "ThredWorks Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".txt", "Text File", ' ', 'U', EMBFORMAT_STITCHONLY },
    { ".u00", "Barudan Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".u01", "Barudan Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".vip", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".vp3", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".xxx", "Singer Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".zsk", "ZSK USA Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { "END", "END", ' ', ' ', 0 }
};

static bcf_file_difat* bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize);
static unsigned int readFullSector(EmbFile* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
static unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
static void bcf_file_difat_free(bcf_file_difat* difat);

static bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
static void loadFatFromSector(bcf_file_fat* fat, EmbFile* file);
static void bcf_file_fat_free(bcf_file_fat* fat);

static bcf_directory_entry* CompoundFileDirectoryEntry(EmbFile* file);
static bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
static void readNextSector(EmbFile* file, bcf_directory* dir);
static void bcf_directory_free(bcf_directory* dir);

static bcf_file_header bcfFileHeader_read(EmbFile* file);
static int bcfFileHeader_isValid(bcf_file_header header);

int numberOfFormats = 61;

/*! Constant representing the number of Double Indirect FAT entries in a single header */
static const unsigned int NumberOfDifatEntriesInHeader = 109;
static const unsigned int sizeOfFatEntry = sizeof(unsigned int);
static const unsigned int sizeOfDifatEntry = 4;
static const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
static const unsigned int sizeOfDirectoryEntry = 128;
/* static const int supportedMinorVersion = 0x003E;
static const int littleEndianByteOrderMark = 0xFFFE; */

int embPattern_write(EmbPattern* pattern, const char* fileName, int format)
{
    EmbFile *file;
    int r;

    if (!fileName) {
        embLog("ERROR: ");
        embLog(fileName);
        embLog("(), fileName argument is null\n");
        return 0;
    }

    if (!pattern->stitchList) {
        embLog("ERROR: embPattern_write(), pattern contains no stitches\n");
        return 0;
    }

    if (!pattern->stitchList->count) {
        embLog("ERROR: embPattern_write(), pattern contains no stitches\n");
        return 0;
    }

    embPattern_end(pattern);

    file = embFile_open(fileName, "wb", 0);
    if (!file) {
        embLog("ERROR: embPattern_write(), failed to open file\n");
        return 0;    
    }

    r = 0;
    switch (format) {
    case EMB_FORMAT_100:
        r = write100(pattern, file, fileName);
        break;
    case EMB_FORMAT_10O:
        r = write10o(pattern, file, fileName);
        break;
    case EMB_FORMAT_ART:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_BMC:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_BRO:
        r = writeBro(pattern, file, fileName);
        break;
    case EMB_FORMAT_CND:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_COL:
        r = writeCol(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSD:
        r = writeCsd(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSV:
        r = writeCsv(pattern, file, fileName);
        break;
    case EMB_FORMAT_DAT:
        r = writeDat(pattern, file, fileName);
        break;
    case EMB_FORMAT_DEM:
        r = writeDem(pattern, file, fileName);
        break;
    case EMB_FORMAT_DSB:
        r = writeDsb(pattern, file, fileName);
        break;
    case EMB_FORMAT_DST:
        r = writeDst(pattern, file, fileName);
        break;
    case EMB_FORMAT_DSZ:
        r = writeDsz(pattern, file, fileName);
        break;
    case EMB_FORMAT_DXF:
        r = writeDxf(pattern, file, fileName);
        break;
    case EMB_FORMAT_EDR:
        r = writeEdr(pattern, file, fileName);
        break;
    case EMB_FORMAT_EMD:
        r = writeEmd(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXP:
        r = writeExp(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXY:
        r = writeExy(pattern, file, fileName);
        break;
    case EMB_FORMAT_EYS:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_FXY:
        r = writeFxy(pattern, file, fileName);
        break;
    case EMB_FORMAT_GC:
        /* Smoothie G-Code */
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_GNC:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_GT: 
        r = writeGt(pattern, file, fileName);
        break;
    case EMB_FORMAT_HUS:
        r = writeHus(pattern, file, fileName);
        break;
    case EMB_FORMAT_INB:
        r = writeInb(pattern, file, fileName);
        break;
    case EMB_FORMAT_INF:
        r = writeInf(pattern, file, fileName);
        break;
    case EMB_FORMAT_JEF:
        r = writeJef(pattern, file, fileName);
        break;
    case EMB_FORMAT_KSM:
        r = writeKsm(pattern, file, fileName);
        break;
    case EMB_FORMAT_MAX:
        r = writeMax(pattern, file, fileName);
        break;
    case EMB_FORMAT_MIT:
        r = writeMit(pattern, file, fileName);
        break;
    case EMB_FORMAT_NEW:
        r = writeNew(pattern, file, fileName);
        break;
    case EMB_FORMAT_OFM:
        r = writeOfm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCD:
        r = writePcd(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCM:
        r = writePcm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCQ:
        r = writePcq(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCS:
        r = writePcs(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEC:
        r = writePec(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEL:
        r = writePel(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEM:
        r = writePem(pattern, file, fileName);
        break;
    case EMB_FORMAT_PES:
        r = writePes(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHB:
        r = writePhb(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHC:
        r = writePhc(pattern, file, fileName);
        break;
    case EMB_FORMAT_PLT:
        r = writePlt(pattern, file, fileName);
        break;
    case EMB_FORMAT_RGB:
        r = writeRgb(pattern, file, fileName);
        break;
    case EMB_FORMAT_SEW:
        r = writeSew(pattern, file, fileName);
        break;
    case EMB_FORMAT_SHV:
        r = writeShv(pattern, file, fileName);
        break;
    case EMB_FORMAT_SST:
        r = writeSst(pattern, file, fileName);
        break;
    case EMB_FORMAT_STX:
        r = writeStx(pattern, file, fileName);
        break;
    case EMB_FORMAT_SVG:
        r = writeSvg(pattern, file, fileName);
        break;
    case EMB_FORMAT_T01:
        r = writeT01(pattern, file, fileName);
        break;
    case EMB_FORMAT_T09:
        r = writeT09(pattern, file, fileName);
        break;
    case EMB_FORMAT_TAP:
        r = writeTap(pattern, file, fileName);
        break;
    case EMB_FORMAT_THR:
        r = writeThr(pattern, file, fileName);
        break;
    case EMB_FORMAT_TXT:
        r = writeTxt(pattern, file, fileName);
        break;
    case EMB_FORMAT_U00:
        r = writeU00(pattern, file, fileName);
        break;
    case EMB_FORMAT_U01:
        r = writeU01(pattern, file, fileName);
        break;
    case EMB_FORMAT_VIP:
        r = writeVip(pattern, file, fileName);
        break;
    case EMB_FORMAT_VP3:
        r = writeVp3(pattern, file, fileName);
        break;
    case EMB_FORMAT_XXX:
        r = writeXxx(pattern, file, fileName);
        break;
    case EMB_FORMAT_ZSK:
        r = writeZsk(pattern, file, fileName);
        break;
    default:
        embLog("Emb format not recognised.");
        break;
    }

    if (!r) {
        return r;
    }

    embFile_close(file);
    return 0;
}

int embPattern_read(EmbPattern* pattern, const char* fileName, int format)
{
    EmbFile *file;
    int r;

    if (!pattern) {
        embLog("ERROR: embPattern_read(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        embLog("ERROR: embPattern_read(), fileName argument is null\n");
        return 0;
    }

    file = embFile_open(fileName, "rb", 0);
    if (!file) {
        embLog("ERROR: embPattern_write(), failed to open file\n");
        return 0;
    }

    r = 0;
    switch (format) {
    case EMB_FORMAT_100:
        r = read100(pattern, file, fileName);
        break;
    case EMB_FORMAT_10O:
        r = read10o(pattern, file, fileName);
        break;
    case EMB_FORMAT_ART:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_BMC:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_BRO:
        r = readBro(pattern, file, fileName);
        break;
    case EMB_FORMAT_CND:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_COL:
        r = readCol(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSD:
        r = readCsd(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSV:
        r = readCsv(pattern, file, fileName);
        break;
    case EMB_FORMAT_DAT:
        r = readDat(pattern, file, fileName);
        break;
    case EMB_FORMAT_DEM:
        r = readDem(pattern, file, fileName);
        break;
    case EMB_FORMAT_DSB:
        r = readDsb(pattern, file, fileName);
        break;
    case EMB_FORMAT_DST:
        r = readDst(pattern, file, fileName);
        break;
    case EMB_FORMAT_DSZ:
        r = readDsz(pattern, file, fileName);
        break;
    case EMB_FORMAT_DXF:
        r = readDxf(pattern, file, fileName);
        break;
    case EMB_FORMAT_EDR:
        r = readEdr(pattern, file, fileName);
        break;
    case EMB_FORMAT_EMD:
        r = readEmd(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXP:
        r = readExp(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXY:
        r = readExy(pattern, file, fileName);
        break;
    case EMB_FORMAT_EYS:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_FXY:
        r = readFxy(pattern, file, fileName);
        break;
    case EMB_FORMAT_GC:
        /* Smoothie G-Code */
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_GNC:
        embLog("ERROR: This format is not implimented.");
        break;
    case EMB_FORMAT_GT:
        r = readGt(pattern, file, fileName);
        break;
    case EMB_FORMAT_HUS:
        r = readHus(pattern, file, fileName);
        break;
    case EMB_FORMAT_INB:
        r = readInb(pattern, file, fileName);
        break;
    case EMB_FORMAT_INF:
        r = readInf(pattern, file, fileName);
        break;
    case EMB_FORMAT_JEF:
        r = readJef(pattern, file, fileName);
        break;
    case EMB_FORMAT_KSM:
        r = readKsm(pattern, file, fileName);
        break;
    case EMB_FORMAT_MAX:
        r = readMax(pattern, file, fileName);
        break;
    case EMB_FORMAT_MIT:
        r = readMit(pattern, file, fileName);
        break;
    case EMB_FORMAT_NEW:
        r = readNew(pattern, file, fileName);
        break;
    case EMB_FORMAT_OFM:
        r = readOfm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCD:
        r = readPcd(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCM:
        r = readPcm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCQ:
        r = readPcq(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCS:
        r = readPcs(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEC:
        r = readPec(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEL:
        r = readPel(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEM:
        r = readPem(pattern, file, fileName);
        break;
    case EMB_FORMAT_PES:
        r = readPes(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHB:
        r = readPhb(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHC:
        r = readPhc(pattern, file, fileName);
        break;
    case EMB_FORMAT_PLT:
        r = readPlt(pattern, file, fileName);
        break;
    case EMB_FORMAT_RGB:
        r = readRgb(pattern, file, fileName);
        break;
    case EMB_FORMAT_SEW:
        r = readSew(pattern, file, fileName);
        break;
    case EMB_FORMAT_SHV:
        r = readShv(pattern, file, fileName);
        break;
    case EMB_FORMAT_SST:
        r = readSst(pattern, file, fileName);
        break;
    case EMB_FORMAT_STX:
        r = readStx(pattern, file, fileName);
        break;
    case EMB_FORMAT_SVG:
        r = readSvg(pattern, file, fileName);
        break;
    case EMB_FORMAT_T01:
        r = readT01(pattern, file, fileName);
        break;
    case EMB_FORMAT_T09:
        r = readT09(pattern, file, fileName);
        break;
    case EMB_FORMAT_TAP:
        r = readTap(pattern, file, fileName);
        break;
    case EMB_FORMAT_THR:
        r = readThr(pattern, file, fileName);
        break;
    case EMB_FORMAT_TXT:
        r = readTxt(pattern, file, fileName);
        break;
    case EMB_FORMAT_U00:
        r = readU00(pattern, file, fileName);
        break;
    case EMB_FORMAT_U01:
        r = readU01(pattern, file, fileName);
        break;
    case EMB_FORMAT_VIP:
        r = readVip(pattern, file, fileName);
        break;
    case EMB_FORMAT_VP3:
        r = readVp3(pattern, file, fileName);
        break;
    case EMB_FORMAT_XXX:
        r = readXxx(pattern, file, fileName);
        break;
    case EMB_FORMAT_ZSK:
        r = readZsk(pattern, file, fileName);
        break;
    default:
        embLog("Emb format not recognised.");
        break;
    }

    if (!r) {
        return r;
    }

    embFile_close(file);
    embPattern_end(pattern);

    return 1;
}

/**
 * TODO: documentation.
 */
EmbFile* embFile_open(const char* fileName, const char* mode, int optional)
{
#ifdef ARDUINO
    return inoFile_open(fileName, mode);
#else
    EmbFile* eFile = 0;
    FILE* oFile = fopen(fileName, mode);
    if (!oFile) {
        if (!optional) {
            embLog("ERROR: Cannot open the fileName in the given mode.");
            embLog(fileName);
            embLog(mode);
        }
        return 0;
    }

    eFile = (EmbFile*)malloc(sizeof(EmbFile));
    if (!eFile) {
        if (!optional) {
            embLog("ERROR: Cannot allocate memory for EmbFile with arguments:");
            embLog(fileName);
            embLog(mode);
        }
        fclose(oFile);
        return 0;
    }

    eFile->file = oFile;
    return eFile;
#endif
}

/**
 * TODO: documentation.
 */
int embFile_close(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_close(stream);
#else /* ARDUINO */
    int retVal = fclose(stream->file);
    free(stream);
    return retVal;
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 */
int embFile_eof(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_eof(stream);
#else /* ARDUINO */
    return feof(stream->file);
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 */
char embFile_getc(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_getc(stream);
#else /* ARDUINO */
    return fgetc(stream->file);
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 */
void embFile_readline(EmbFile* stream, char* line, int maxLength)
{
    int i;
    char c;
    for (i = 0; i < maxLength - 1; i++) {
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
 * TODO: documentation.
 */
size_t embFile_read(void* ptr, size_t size, size_t nmemb, EmbFile* stream)
{
#ifdef ARDUINO
    /* ARDUINO TODO: SD File read() doesn't appear to return the same way as fread(). This will need work. */
    return 0;
#else
    return fread(ptr, size, nmemb, stream->file);
#endif
}

/**
 * TODO: documentation.
 */
size_t embFile_write(const void* ptr, size_t size, size_t nmemb, EmbFile* stream)
{
#ifdef ARDUINO
    return 0; /* ARDUINO TODO: Implement inoFile_write. */
#else /* ARDUINO */
    return fwrite(ptr, size, nmemb, stream->file);
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 */
void embFile_pad(EmbFile* stream, char c, int n)
{
    int i;
    for (i=0; i<n; i++) {
        embFile_write(&c, 1, 1, stream);
    }
}

/**
 * TODO: documentation.
 */
int embFile_seek(EmbFile* stream, long offset, int origin)
{
#ifdef ARDUINO
    return inoFile_seek(stream, offset, origin);
#else /* ARDUINO */
    return fseek(stream->file, offset, origin);
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 */
long embFile_tell(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_tell(stream);
#else /* ARDUINO */
    return ftell(stream->file);
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
int embFile_putc(int ch, EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_putc(ch, stream);
#else /* ARDUINO */
    return fputc(ch, stream->file);
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 */
void embFile_print(EmbFile* stream, const char* str)
{
    embFile_write(str, 1, strlen(str), stream);
}

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
static int haveExtraDIFATSectors(bcf_file* file)
{
    return (int)(numberOfEntriesInDifatSector(file->difat) > 0);
}

/**
 * TODO: documentation.
 */
static int seekToOffset(EmbFile* file, const unsigned int offset)
{
    return embFile_seek(file, offset, SEEK_SET);
}

/**
 * TODO: documentation.
 */
static int seekToSector(bcf_file* bcfFile, EmbFile* file, const unsigned int sector)
{
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return seekToOffset(file, offset);
}

/**
 * TODO: documentation.
 */
static void parseDIFATSectors(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int numberOfDifatEntriesStillToRead = bcfFile->header.numberOfFATSectors - NumberOfDifatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &numberOfDifatEntriesStillToRead);
    }
}

/**
 * TODO: documentation.
 */
int bcfFile_read(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int i, numberOfDirectoryEntriesPerSector, directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (!bcfFileHeader_isValid(bcfFile->header)) {
        embLog("Failed to parse header\n");
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
 * TODO: documentation.
 */
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
        embLog("ERROR: compound-file.c GetFile(), cannot allocate memory for input\n");
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

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
bcf_file_difat* bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize)
{
    unsigned int i;
    bcf_file_difat* difat = 0;
    unsigned int sectorRef;

    difat = (bcf_file_difat*)malloc(sizeof(bcf_file_difat));
    if (!difat) {
        embLog("ERROR: compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat\n");
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
            embLog("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value\n");
            /* TODO " %x at DIFAT[%d]\n", sectorRef, i); */
        }
    }
    return difat;
}

/**
 * TODO: documentation.
 */
unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat)
{
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

/**
 * TODO: documentation.
 */
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
            embLog("ERROR: compound-file-difat.c readFullSector(), Unexpected sector value");
            /* TODO: end of message: %x at DIFAT[%d]]\n", sectorRef, i); */
        }
    }
    nextDifatSectorInChain = binaryReadUInt32(file);
    return nextDifatSectorInChain;
}

/**
 * TODO: documentation.
 */
void bcf_file_difat_free(bcf_file_difat* difat)
{
    free(difat);
}

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries)
{
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        embLog("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

/**
 * TODO: documentation.
 */
EmbTime parseTime(EmbFile* file)
{
    EmbTime returnVal;
#if 0
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    ft_low = binaryReadInt32(file);
    ft_high = binaryReadInt32(file);
    /* TODO: translate to actual date time */
#endif
    returnVal.year = 1000; /* for testing */
    return returnVal;
}

/**
 * TODO: documentation.
 */
bcf_directory_entry* CompoundFileDirectoryEntry(EmbFile* file)
{
    bcf_directory_entry* dir = (bcf_directory_entry*)malloc(sizeof(bcf_directory_entry));
    if (!dir) {
        embLog("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = binaryReadUInt16(file);
    dir->objectType = (unsigned char)binaryReadByte(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        embLog("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), unexpected object type:\n");
        /* TODO: "%d\n", dir->objectType); */
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

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
void bcf_directory_free(bcf_directory* dir)
{
    bcf_directory_entry* pointer = dir->dirEntries;
    bcf_directory_entry* entryToFree = 0;
    while (pointer) {
        entryToFree = pointer;
        pointer = pointer->next;
        free(entryToFree);
    }
    if (dir) {
        free(dir);
    }
}

/**
 * TODO: documentation.
 */
bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize)
{
    bcf_file_fat* fat = (bcf_file_fat*)malloc(sizeof(bcf_file_fat));
    if (!fat) {
        embLog("ERROR: compound-file-fat.c bcfFileFat_create(), cannot allocate memory for fat\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
    fat->fatEntryCount = 0;
    return fat;
}

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
void bcf_file_fat_free(bcf_file_fat* fat)
{
    free(fat);
    fat = 0;
}

/**
 * TODO: documentation.
 */
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

/**
 * TODO: documentation.
 */
int bcfFileHeader_isValid(bcf_file_header header)
{
    if (memcmp(header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1", 8) != 0) {
        embLog("bad header signature\n");
        return 0;
    }
    return 1;
}

/**
 * TODO: documentation.
 */
int embFormat_getExtension(const char* fileName, char* ending)
{
    int i;
    const char* offset;

    if (!fileName) {
        embLog("ERROR: emb-format.c embFormat_getExtension(), fileName argument is null\n");
        return 0;
    }

    if (strlen(fileName) == 0) {
        return 0;
    }

    offset = strrchr(fileName, '.');
    if (offset == 0) {
        return 0;
    }

    for (i=0; offset[i]; i++) {
        ending[i] = offset[i];
        if (offset[i] >= 'A' && offset[i] <= 'Z') {
            ending[i] -= 'A' + 'a';
        }
    }
    ending[i] = 0; /* terminate the string */

    return 1;
}

/**
 * TODO: documentation.
 */
const char* embFormat_descriptionFromName(const char* fileName)
{
    int format;
    format = embReaderWriter_getByFileName(fileName);
    if (format < 0) {
        return 0;
    }
    return formatTable[format].description;
}

/**
 * TODO: documentation.
 */
char embFormat_readerStateFromName(const char* fileName)
{
    int format;
    format = embReaderWriter_getByFileName(fileName);
    if (format < 0) {
        return 0;
    }
    return formatTable[format].reader;
}

/**
 * TODO: documentation.
 */
char embFormat_writerStateFromName(const char* fileName)
{
    int format;
    format = embReaderWriter_getByFileName(fileName);
    if (format < 0) {
        return 0;
    }
    return formatTable[format].writer;
}

/**
 * TODO: documentation.
 */
int embFormat_typeFromName(const char* fileName)
{
    int format;
    format = embReaderWriter_getByFileName(fileName);
    if (format < 0) {
        return EMBFORMAT_UNSUPPORTED;
    }
    return formatTable[format].type;
}

/**
 * Returns a pointer to an EmbReaderWriter if the \a fileName is a supported file type.
 */
int embReaderWriter_getByFileName(const char* fileName)
{
    int i;
    char ending[10];

    if (!embFormat_getExtension(fileName, ending)) {
        return -1;
    }

    /* checks the first character to see if it is the end symbol */
    for (i = 0; formatTable[i].extension[0] != 'E'; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            return i;
        }
    }

    embLog("ERROR: emb-reader-writer.c embReaderWriter_getByFileName(), unsupported file type:");
    embLog(ending);
    return -1;
}

