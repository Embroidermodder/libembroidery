#include "embroidery.h"

static void ksmEncode(unsigned char* b, char dx, char dy, int flags)
{
    if(!b)
    {
        embLog("ERROR: format-ksm.c ksmEncode(), b argument is null\n");
        return;
    }
    /* TODO: How to encode JUMP stitches? JUMP must be handled. Also check this for the EXP format since it appears to be similar */
    if(flags == TRIM)
    {
        b[0] = 128;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    }
    else if(flags == STOP)
    {
        b[0] = 128;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    }
    else
    {
        b[0] = dx;
        b[1] = dy;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readKsm(EmbPattern* pattern, const char* fileName)
{
    int prevStitchType = NORMAL;
    char b[3];
    EmbFile* file = 0;

    if (!validateReadPattern(pattern, fileName, "readKsm"))
        return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) {
        return 0;
    }

    embFile_seek(file, 0x200, SEEK_SET);

    while(embFile_read(b, 1, 3, file) == 3)
    {
        int flags = NORMAL;

        if(((prevStitchType & 0x08) == 0x08) && (b[2] & 0x08) == 0x08)
        {
            flags = STOP;
        }
        else if((b[2] & 0x1F) != 0)
        {
            flags = TRIM;
        }
        prevStitchType = b[2];
        if(b[2] & 0x40)
            b[1] = -b[1];
        if(b[2] & 0x20)
            b[0] = -b[0];
        embPattern_addStitchRel(pattern, b[1] / 10.0, b[0] / 10.0, flags, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeKsm(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;
    EmbStitch st;
    double xx, yy, dx, dy;
    int i;
    unsigned char b[4];

    if (!validateWritePattern(pattern, fileName, "writeKsm"))
        return 0;

    file = embFile_open(fileName, "wb", 0);
    if(!file) {
        return 0;
    }
    for(i = 0; i < 0x80; i++)
    {
        binaryWriteInt(file, 0);
    }
    /* write stitches */
    xx = yy = 0;
    for(i=0; i<pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        ksmEncode(b, (char)(dx * 10.0), (char)(dy * 10.0), st.flags);
        embFile_write(b, 1, 2, file);
    }
    embFile_printf(file, "\x1a");
    embFile_close(file);
    return 1;
}

