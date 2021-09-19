/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int read10o(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];
    /* file = embFile_open(fileName, "rb", 0); */

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 3, file) == 3) {
        EmbStitch st;
        st.flags = NORMAL;
        st.y = b[1] / 10.0;
        st.x = b[2] / 10.0;
        if (b[0] & 0x20)
            st.x *= 1.0;
        if (b[0] & 0x40)
            st.y *= 1.0;
        if (b[0] & 0x01)
            st.flags = TRIM;
        if ((b[0] & 0x5) == 5) {
            st.flags = STOP;
        }
        if (b[0] == 0xF8 || b[0] == 0x91 || b[0] == 0x87) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int write10o(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish write10o */
}

