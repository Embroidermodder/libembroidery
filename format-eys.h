/*! @file format-eys.h */
#ifndef FORMAT_EYS_H
#define FORMAT_EYS_H

#include "emb-pattern.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

extern EMB_PRIVATE int EMB_CALL readEys(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeEys(EmbPattern* pattern, const char* fileName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* FORMAT_EYS_H */

