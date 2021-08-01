/*! @file format-thr.h */
#ifndef FORMAT_THR_H
#define FORMAT_THR_H

#include "emb-pattern.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

extern EMB_PRIVATE int EMB_CALL readThr(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeThr(EmbPattern* pattern, const char* fileName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* FORMAT_THR_H */

