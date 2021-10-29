#include "embroidery.h"

static int mitDecodeStitch(unsigned char value)
{
	if (value & 0x80)
	{
		return -(value & 0x1F);
	}
    return value;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readMit(EmbPattern* pattern, const char* fileName)
{
    unsigned char data[2];
    EmbFile* file = 0;

    if(!pattern) { printf("ERROR: format-mit.c readMit(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: format-mit.c readMit(), fileName argument is null\n"); return 0; }

    file = embFile_open(fileName, "rb", 0);
    if(!file)
		return 0;

    /* embPattern_loadExternalColorFile(pattern, fileName); TODO: review this and uncomment or remove it */

    while(binaryReadBytes(file, data, 2) == 2)
    {
        embPattern_addStitchRel(pattern, mitDecodeStitch(data[0]) / 10.0, mitDecodeStitch(data[1]) / 10.0, NORMAL, 1);
    }

    embFile_close(file);
    embPattern_end(pattern);

    return 1;
}

static unsigned char mitEncodeStitch(double value)
{
	if (value < 0)
	{
		return 0x80 | (unsigned char)(-value);
	}
	return (unsigned char)value;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeMit(EmbPattern* pattern, const char* fileName)
{
	EmbFile* file = 0;
	EmbStitchList* pointer = 0;
	double xx = 0, yy = 0, dx = 0, dy = 0;
	int flags = 0;

    if (!validateWritePattern(pattern, fileName, "writeMit")) {
        return 0;
    }

	file = embFile_open(fileName, "wb", 0);
	if (!file)
		return 0;

	embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
	xx = yy = 0;
	pointer = pattern->stitchList;
	while (pointer)
	{
		dx = pointer->stitch.x - xx;
		dy = pointer->stitch.y - yy;
		xx = pointer->stitch.x;
		yy = pointer->stitch.y;
		flags = pointer->stitch.flags;
		embFile_putc(mitEncodeStitch(dx), file);
		embFile_putc(mitEncodeStitch(dy), file);
		pointer = pointer->next;
	}
	embFile_close(file);
    return 1;
}

