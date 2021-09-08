#include "embroidery.h"
#include <stdio.h>

static int decodeRecordFlags(unsigned char b2)
{
    if (b2 == 0xF3)
    {
        return END;
    }
    switch(b2 & 0xC3)
    {
        case 0x03:
            return NORMAL;
        case 0x83:
            return TRIM;
        case 0xC3:
            return STOP;
        default:
            return NORMAL;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readTap(EmbPattern* pattern, const char* fileName)
{
    unsigned char b[3];
    EmbFile* file = 0;

    if (!validateReadPattern(pattern, fileName, "readTap"))
        return 0;

    file = embFile_open(fileName, "rb", 0);
    if(!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    while(embFile_read(b, 1, 3, file) == 3)
    {
        int flags;
        int x = 0;
        int y = 0;
        if(b[0] & 0x01)
            x += 1;
        if(b[0] & 0x02)
            x -= 1;
        if(b[0] & 0x04)
            x += 9;
        if(b[0] & 0x08)
            x -= 9;
        if(b[0] & 0x80)
            y += 1;
        if(b[0] & 0x40)
            y -= 1;
        if(b[0] & 0x20)
            y += 9;
        if(b[0] & 0x10)
            y -= 9;
        if(b[1] & 0x01)
            x += 3;
        if(b[1] & 0x02)
            x -= 3;
        if(b[1] & 0x04)
            x += 27;
        if(b[1] & 0x08)
            x -= 27;
        if(b[1] & 0x80)
            y += 3;
        if(b[1] & 0x40)
            y -= 3;
        if(b[1] & 0x20)
            y += 27;
        if(b[1] & 0x10)
            y -= 27;
        if(b[2] & 0x04)
            x += 81;
        if(b[2] & 0x08)
            x -= 81;
        if(b[2] & 0x20)
            y += 81;
        if(b[2] & 0x10)
            y -= 81;
        flags = decodeRecordFlags(b[2]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if(flags == END)
            break;
    }
    embFile_close(file);
    embPattern_end(pattern);

    return 1;
}

static unsigned char setbit(int pos)
{
	return (unsigned char)(1 << pos);
}

static void encode_record(EmbFile* file, int x, int y, int flags)
{
	char b0, b1, b2;
	b0 = b1 = b2 = 0;

	/* cannot encode values > +121 or < -121. */
	if (x > 121 || x < -121) embLog_error("format-tap.c encode_record(), x is not in valid range [-121,121] , x = %d\n", x);
	if (y > 121 || y < -121) embLog_error("format-tap.c encode_record(), y is not in valid range [-121,121] , y = %d\n", y);

	if (x >= +41) { b2 += setbit(2); x -= 81; }
	if (x <= -41) { b2 += setbit(3); x += 81; }
	if (x >= +14) { b1 += setbit(2); x -= 27; }
	if (x <= -14) { b1 += setbit(3); x += 27; }
	if (x >= +5) { b0 += setbit(2); x -= 9; }
	if (x <= -5) { b0 += setbit(3); x += 9; }
	if (x >= +2) { b1 += setbit(0); x -= 3; }
	if (x <= -2) { b1 += setbit(1); x += 3; }
	if (x >= +1) { b0 += setbit(0); x -= 1; }
	if (x <= -1) { b0 += setbit(1); x += 1; }
	if (x != 0) { embLog_error("format-tap.c encode_record(), x should be zero yet x = %d\n", x); }
	if (y >= +41) { b2 += setbit(5); y -= 81; }
	if (y <= -41) { b2 += setbit(4); y += 81; }
	if (y >= +14) { b1 += setbit(5); y -= 27; }
	if (y <= -14) { b1 += setbit(4); y += 27; }
	if (y >= +5) { b0 += setbit(5); y -= 9; }
	if (y <= -5) { b0 += setbit(4); y += 9; }
	if (y >= +2) { b1 += setbit(7); y -= 3; }
	if (y <= -2) { b1 += setbit(6); y += 3; }
	if (y >= +1) { b0 += setbit(7); y -= 1; }
	if (y <= -1) { b0 += setbit(6); y += 1; }
	if (y != 0) { embLog_error("format-tap.c encode_record(), y should be zero yet y = %d\n", y); }

	b2 |= (char)3;

	if (flags & END)
	{
		b0 = 0;
		b1 = 0;
		b2 = 0xF3;
	}
	if (flags & (JUMP | TRIM))
	{
		b2 = (char)(b2 | 0x83);
	}
	if (flags & STOP)
	{
		b2 = (char)(b2 | 0xC3);
	}

	binaryWriteByte(file, (unsigned char)b0);
	binaryWriteByte(file, (unsigned char)b1);
	binaryWriteByte(file, (unsigned char)b2);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeTap(EmbPattern* pattern, const char* fileName)
{
	EmbRect boundingRect;
	EmbFile* file;
	int xx, yy, dx, dy, i;
	EmbStitch st;
	
    if (!validateWritePattern(pattern, fileName, "writeTap")) {
        return 0;
    }

	file = embFile_open(fileName, "wb", 0);
	if (!file) return 0;

	embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

	boundingRect = embPattern_calcBoundingBox(pattern);
	xx = yy = 0;
	for (i=0; i<pattern->stitchList->count; i++) {
		st = pattern->stitchList->stitch[i];
		/* convert from mm to 0.1mm for file format */
		dx = roundDouble(st.x * 10.0) - xx;
		dy = roundDouble(st.y * 10.0) - yy;
		xx = roundDouble(st.x * 10.0);
		yy = roundDouble(st.y * 10.0);
		encode_record(file, dx, dy, st.flags);
	}
	embFile_close(file);
	return 1;
}


