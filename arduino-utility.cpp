#include "ino-event.h"
#include "emb-logging.h"
#include "ino-file.h"
#include "ino-logging.h"

#include "SD.h"
#include "Arduino.h"

struct InoFile_
{
    File file;
};

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
