#ifndef __EMBROIDERY_INTERNAL__
#define __EMBROIDERY_INTERNAL__

#include <stdio.h>

unsigned char setbit(int pos);
int emb_readline(FILE* file, char *line, int maxLength);
void embFile_pad(EmbFile* stream, char c, int n);

#endif

