#ifndef __EMBROIDERY_INTERNAL__
#define __EMBROIDERY_INTERNAL__

#include <stdio.h>

#define EMB_DEBUG    1

#define EMB_BIT_0    1
#define EMB_BIT_1    2
#define EMB_BIT_2    4
#define EMB_BIT_3    8
#define EMB_BIT_4   16
#define EMB_BIT_5   32
#define EMB_BIT_6   64
#define EMB_BIT_7  128

unsigned char setbit(int pos);
int emb_readline(FILE* file, char *line, int maxLength);
void embFile_pad(EmbFile* stream, char c, int n);

#endif

