/*! @file format-cnd.h */
#ifndef FORMAT_CND_H
#define FORMAT_CND_H

#include "emb-pattern.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

extern EMB_PRIVATE int EMB_CALL readCnd(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeCnd(EmbPattern* pattern, const char* fileName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* FORMAT_CND_H */

