/*! @file format-col.h */
#ifndef FORMAT_COL_H
#define FORMAT_COL_H

#include "emb-pattern.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

extern EMB_PRIVATE int EMB_CALL readCol(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeCol(EmbPattern* pattern, const char* fileName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* FORMAT_COL_H */

