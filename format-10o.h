/*! @file format-10o.h */
#ifndef FORMAT_10O_H
#define FORMAT_10O_H

#include "emb-pattern.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

extern EMB_PRIVATE int EMB_CALL read10o(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL write10o(EmbPattern* pattern, const char* fileName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* FORMAT_10O_H */

/* kate: bom off; indent-mode cstyle; indent-width 4; replace-trailing-space-save on; */
