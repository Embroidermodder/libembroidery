/**
 * 
 */

static void encode_u00_stitch(EmbStitch st, unsigned char *data)
{
    char dx, dy;
    dx = (char)roundDouble(10.0*st.x);
    dy = (char)roundDouble(10.0*st.y);
    data[2] = dx;
    data[1] = dy;
    data[0] = 0;
    if (dx < 0.0) {
        data[0] |= 0x20;
    }
    if (dy < 0.0) {
        data[0] |= 0x40;
    }
    switch (st.flags) {
    case JUMP:
        data[0] |= 0x10;
        break;
    case STOP:
        data[0] |= 0x01;
        break;
    case END:
        data[0] = 0xF8;
        break;
    case NORMAL:
    default:
        break;
    }
}

static EmbStitch decode_u00_stitch(unsigned char *data)
{
    EmbStitch st;
    st.flags = NORMAL;
    if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
        st.flags = END;
    }
    if ((data[0] & 0x0F) == 0) {
        st.flags = NORMAL;
    } else if ((data[0] & 0x1f) == 1) {
        st.flags = JUMP;
    } else if ((data[0] & 0x0F) > 0) {
        st.flags = STOP;
    }

    st.x = data[2]/10.0;
    st.y = data[1]/10.0;
    if ((data[0] & 0x20) > 0)
        st.x *= -1.0;
    if ((data[0] & 0x40) > 0)
        st.y *= -1.0;
    return st;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbThread t;
    EmbStitch st;
    unsigned char b[4], i;

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between 0 and 15 with index of color for each color change */
    embFile_seek(file, 0x08, SEEK_SET);

    for (i = 0; i < 16; i++) {
        embFile_read(b, 1, 3, file);
        t.color = embColor_fromStr(b);
        embPattern_addThread(pattern, t);
    }

    embFile_seek(file, 0x100, SEEK_SET);
    while (embFile_read(b, 1, 3, file) == 3) {
        st = decode_u00_stitch(b);
        if (st.flags == END) {
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[4], i;

    embFile_pad(file, ' ', 8);

    for (i = 0; i < pattern->threads->count; i++) {
        embColor_toStr(pattern->threads->thread[i].color, b);
        embFile_write(b, 1, 3, file);
    }

    /* this should pad to 512 bytes */
    embFile_pad(file, ' ', 0x100 - 3*pattern->threads->count - 8);

    for (i = 0; i < pattern->stitchList->count; i++) {
        encode_u00_stitch(pattern->stitchList->stitch[i], b);
        embFile_write(b, 1, 3, file);
    }
    return 1;
}

