static double pcdDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static void pcdEncode(EmbFile* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) {
        embLog("ERROR: format-pcd.c pcdEncode(), file argument is null\n");
        return;
    }

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dx & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 16) & 0xFF));

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dy & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 16) & 0xFF));
    if (flags & STOP) {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM) {
        flagsToWrite |= 0x04;
    }
    binaryWriteByte(file, flagsToWrite);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPcd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char allZeroColor = 1;
    int i;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0;

    version = binaryReadByte(file);
    hoopSize = binaryReadByte(file); /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
    /* and 3 for PCS with large hoop (115x120) */
    colorCount = binaryReadUInt16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        t.color.r = (unsigned char)embFile_getc(file);
        t.color.g = (unsigned char)embFile_getc(file);
        t.color.b = (unsigned char)embFile_getc(file);
        t.catalogNumber = "";
        t.description = "";
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
        embFile_getc(file);
    }
    if (allZeroColor)
        embPattern_loadExternalColorFile(pattern, fileName);
    st = binaryReadUInt16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (embFile_read(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pcdDecode(b[1], b[2], b[3]);
        dy = pcdDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePcd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    int i;
    unsigned char colorCount;
    double xx = 0.0, yy = 0.0;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
    colorCount = (unsigned char)pattern->threads->count;
    binaryWriteUShort(file, (unsigned short)colorCount);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        binaryWriteByte(file, color.r);
        binaryWriteByte(file, color.g);
        binaryWriteByte(file, color.b);
        binaryWriteByte(file, 0);
    }

    for (; i < 16; i++) {
        binaryWriteUInt(file, 0); /* write remaining colors to reach 16 */
    }

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        pcdEncode(file, roundDouble(st.x * 10.0), roundDouble(st.y * 10.0), st.flags);
    }
    return 1;
}

