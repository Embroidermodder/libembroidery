static int mitDecodeStitch(unsigned char value)
{
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readMit(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char data[2];

    /* embPattern_loadExternalColorFile(pattern, fileName); TODO: review this and uncomment or remove it */

    while (binaryReadBytes(file, data, 2) == 2) {
        embPattern_addStitchRel(pattern, mitDecodeStitch(data[0]) / 10.0, mitDecodeStitch(data[1]) / 10.0, NORMAL, 1);
    }

    return 1;
}

static unsigned char mitEncodeStitch(double value)
{
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeMit(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    double xx = 0, yy = 0, dx = 0, dy = 0;
    int flags = 0, i;

    embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        flags = st.flags;
        embFile_putc(mitEncodeStitch(dx), file);
        embFile_putc(mitEncodeStitch(dy), file);
    }
    return 1;
}

