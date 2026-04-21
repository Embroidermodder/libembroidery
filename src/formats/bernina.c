/**
 * @file bernina.c
 */

#include "embroidery.h"

/**
 * @brief Reader for Bernina "art" files.
 *
 * @param pattern The memory for the pattern to be read into.
 * @param file The file to read the pattern from.
 *
 * The Bernina Embroidery Format (.art)
 *
 * We don't know much about this format.
 *
 * @todo Find a source.
 *
 * @return 1 if successful, 0 otherwise.
 */
char readArt(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: readArt is not supported yet.");
        printf("Cannot read %p %p\n", pattern, file);
        return 0;
}

/**
 * @brief Writer for Bernina "art" files.
 *
 * @param pattern The memory for the pattern to be read from.
 * @param file The file to write the pattern into.
 *
 * The Bernina Embroidery Format (.art)
 *
 * We don't know much about this format.
 *
 * @todo Find a source.
 *
 * @return 1 if successful, 0 otherwise.
 */
char writeArt(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writeArt is not supported yet.");
        printf("Cannot write %p %p\n", pattern, file);
        return 0;
}
