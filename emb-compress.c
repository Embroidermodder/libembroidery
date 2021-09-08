#include "embroidery.h"
#include <stdlib.h>

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int compressionType)
{
    /* TODO: find and analyse some HUS encoded files and DST equivalents */
    output = (unsigned char*)malloc(compressedSize+1);
}

int husCompress(unsigned char* input, unsigned long _inputSize, unsigned char* output, int compressionType, int outputSize)
{
    /* TODO: find and analyse some HUS encoded files and DST equivalents */
    output = (unsigned char*)malloc(outputSize+1);
    return 0;
}
