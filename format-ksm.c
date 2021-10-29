#include "embroidery.h"

static void ksmEncode(unsigned char* b, char dx, char dy, int flags)
{
    if(!b)
    {
        printf("ERROR: format-ksm.c ksmEncode(), b argument is null\n");
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
char readKsm(EmbPattern* pattern, const char* fileName)
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
char writeKsm(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file = 0;
    EmbStitchList* stitches = 0;
    double xx = 0, yy = 0, dx = 0, dy = 0;
    int flags = 0;
    int i = 0;
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
    stitches = pattern->stitchList;
    while(stitches)
    {
        dx = stitches->stitch.x - xx;
        dy = stitches->stitch.y - yy;
        xx = stitches->stitch.x;
        yy = stitches->stitch.y;
        flags = stitches->stitch.flags;
        ksmEncode(b, (char)(dx * 10.0), (char)(dy * 10.0), flags);
        embFile_printf(file, "%c%c", b[0], b[1]);
        stitches = stitches->next;
    }
    embFile_printf(file, "\x1a");
    embFile_close(file);
    return 1;
}

