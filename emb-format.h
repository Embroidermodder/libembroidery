#ifndef EMB_FORMAT_H
#define EMB_FORMAT_H

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

#define EMBFORMAT_UNSUPPORTED 0
#define EMBFORMAT_STITCHONLY  1
#define EMBFORMAT_OBJECTONLY  2
#define EMBFORMAT_STCHANDOBJ  3 /* binary operation: 1+2=3 */

#define EMBFORMAT_MAXEXT 3  /* maximum length of extension without dot */
#define EMBFORMAT_MAXDESC 50  /* the longest possible description string length */

typedef struct EmbFormatList_
{
    char extension[2 + EMBFORMAT_MAXEXT];
    char description[EMBFORMAT_MAXDESC];
    char reader;
    char writer;
    int type;
} EmbFormatList;

extern EmbFormatList formatTable[100];
extern int numberOfFormats;

extern EMB_PUBLIC int EMB_CALL embFormat_getExtension(const char* fileName, char *ending);
extern EMB_PUBLIC const char* EMB_CALL embFormat_extensionFromName(const char* fileName);
extern EMB_PUBLIC const char* EMB_CALL embFormat_descriptionFromName(const char* fileName);
extern EMB_PUBLIC char EMB_CALL embFormat_readerStateFromName(const char* fileName);
extern EMB_PUBLIC char EMB_CALL embFormat_writerStateFromName(const char* fileName);
extern EMB_PUBLIC int EMB_CALL embFormat_typeFromName(const char* fileName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* EMB_FORMAT_H */

