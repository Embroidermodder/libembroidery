//libembroidery barebones example
//TODO: This is a work in progress sketch using libembroidery
//TODO: NOTE: you may need to modify the SD_CS and/or supply your own sample file

#define ARDUINO 1

#include <SPI.h>
//#include <SD.h>
#include "embroidery.h"
#include "libembroidery.c"

#define SD_CS 5 // Card select

//SPCR States (SPI Control Register)
uint8_t SPI_SDCARD = 0; // Set the SPCR to this before reading

uint32_t stitchCount = 0;

void setup(void)
{
    Serial.begin(9600);
    Serial.println(F("libembroidery barebones example"));

    Serial.print(F("Initializing SD card..."));
    if(!SD.begin(SD_CS))
    {
        Serial.println(F("failed!"));
        return;
    }
    Serial.println(F("OK!"));
    SPI_SDCARD = SPCR; //Save the state for later use
}

void loop(void)
{
    loadEmb("sample.exp");
}

void loadEmb(char* fileName)
{
    SPCR = SPI_SDCARD;

    if(!SD.exists(fileName))
    {
        Serial.println("file DOES NOT exist!.");
        return;
    }

    //==============================
    // Reading
    //==============================
    EmbPattern* p = 0;
    int successful = 0;

    p = embPattern_create();
    if(!p) { Serial.println(F("ERROR: Could not allocate memory for embroidery pattern.")); return; }

    successful = embPattern_read(p, fileName);
    if(!successful)
    {
        Serial.print("ERROR: Reading file was unsuccessful: ");
        Serial.println(fileName);
        embPattern_free(p);
        return;
    }

    //==============================
    // Report Design Info
    //==============================
    Serial.print(F("Total Stitches: "));
    Serial.println(stitchCount, DEC); //TODO: For some reason we are missing the last 2 stitches. Investigate embPattern_addStitchAbs() causing a small memory leak.
    stitchCount = 0;

    //==============================
    // Cleanup
    //==============================
    embPattern_free(p);
}

void eventHandler_addStitchAbs(EmbPattern* p, double x, double y, int flags, int isAutoColorIndex)
{
    stitchCount++;
    Serial.print(F("Adding Stitch: "));
    Serial.println(stitchCount, DEC);
}

/**************************************************/
/* EventHandlers - These need to be in the sketch */
/**************************************************/
extern void eventHandler_addStitchAbs(InoPattern*, double, double, int, int);

/**************************************************/
/* EventSenders                                   */
/**************************************************/
void inoEvent_addStitchAbs(InoPattern* p, double x, double y, int flags, int isAutoColorIndex)
{
    eventHandler_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

struct InoFile_
{
    File file;
};

InoFile* inoFile_open(const char* fileName, const char* mode)
{
    Serial.println(F("inoFile_open"));

    InoFile* iFile;

    iFile = (InoFile*)malloc(sizeof(InoFile));
    if(!iFile)
        return 0;

    iFile->file = SD.open(fileName, FILE_READ); /* ARDUINO TODO: add FILE_WRITE capability */
    if(!iFile->file)
        Serial.println(F("ERROR: SD.open() failed"));

    return iFile;
}

int inoFile_close(InoFile* stream)
{
    Serial.println(F("inoFile_close"));

    stream->file.close();
    free(stream);
    stream = 0;
    return 0;
}

int inoFile_eof(InoFile* stream)
{
    //Serial.println(F("inoFile_eof"));

    int avail = stream->file.available();
    //Serial.print(F("avail: "));
    //Serial.println(avail);
    if(avail)
    {
        return 0;
    }
    Serial.println(F("EOF"));
    return 1;
}

int inoFile_getc(InoFile* stream)
{
    //Serial.println(F("inoFile_getc"));

    return stream->file.read();
}

int inoFile_seek(InoFile* stream, long offset, int origin)
{
    Serial.println(F("TODO: inoFile_seek"));

    return 0;//TODO: fseek(stream->file, offset, origin);
}

long inoFile_tell(InoFile* stream)
{
    Serial.println(F("TODO: inoFile_tell"));

    return 0;//TODO: ftell(stream->file);
}

InoFile* inoFile_tmpfile(void)
{
    Serial.println(F("inoFile_tmpfile"));

    return 0; //TODO: finish inoFile_tmpfile()
}

int inoFile_putc(int ch, InoFile* stream)
{
    Serial.println(F("inoFile_putc"));

    return 0; //TODO: finish inoFile_putc()
}

int inoFile_printf(InoFile* stream, const char* msg)
{
    return stream->file.print(msg);
}

void inoLog_serial(const char* msg)
{
    Serial.println(msg);
}
