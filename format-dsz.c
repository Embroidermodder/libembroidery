/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readDsz(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);

    embFile_seek(file, 0x200, SEEK_SET);
    while (1) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = embFile_getc(file);
        if (embFile_eof(file))
            break;
        x = embFile_getc(file);
        if (embFile_eof(file))
            break;
        ctrl = (unsigned char)embFile_getc(file);
        if (embFile_eof(file))
            break;
        if (ctrl & 0x01)
            stitchType = TRIM;
        if (ctrl & 0x20)
            y = -y;
        if (ctrl & 0x40)
            x = -x;

        if (ctrl & 0x0E) {
            int headNumber = (ctrl & 0x0E) >> 1;
            stitchType = STOP;
        }
        if (ctrl & 0x10) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeDsz(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDsz */
}

