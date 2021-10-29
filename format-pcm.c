#include "embroidery.h"

static const int pcmThreadCount = 65;
static const EmbThread pcmThreads[] = {
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
    {{0xFF, 0xFF, 0xFF}, "PCM Color 16", ""}};


static double pcmDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if(res > 0x7FFFFF)
    {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return res;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readPcm(EmbPattern* pattern, const char* fileName)
{
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    EmbFile* file = 0;

    if(!pattern) { printf("ERROR: format-pcm.c readPcm(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: format-pcm.c readPcm(), fileName argument is null\n"); return 0; }

    file = embFile_open(fileName, "rb", 0);
    if(!file) return 0;

    embFile_seek(file, 4, SEEK_SET);

    for(i = 0; i < 16; i++)
    {
        int colorNumber;
        (void)embFile_getc(file); /* zero */
        colorNumber = embFile_getc(file);
        embPattern_addThread(pattern, pcmThreads[colorNumber]);
    }
    st = binaryReadUInt16BE(file);
    /* READ STITCH RECORDS */
    for(i = 0; i < st; i++)
    {
        flags = NORMAL;
        if(embFile_read(b, 1, 9, file) != 9)
            break;

        if(b[8] & 0x01)
        {
            flags = STOP;
        }
        else if(b[8] & 0x04)
        {
            flags = TRIM;
        }
        else if(b[8] != 0)
        {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pcmDecode(b[2], b[1], b[0]);
        dy = pcmDecode(b[6], b[5], b[4]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embFile_close(file);
    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writePcm(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writePcm")) {
        return 0;
    }

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writePcm */
}

