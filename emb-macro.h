/* MACRO LIBRARY
 *
 * These macros aren't intended for users of the library.
 *
 * In order to reduce the number of function calls and definitions for embedded
 * compatibility some macros can serve as multiple function definitions.
 *
 * For example here we have a way of turning an arbitrary point in a header
 * that may contain, say, 512 bytes into an int without determining what
 * sign that int is as that will be done by the type of the variable.
 *
 * If we need to pass in, say, 30 bytes in then if we pass:
 *     EMB_GET_INT(header+30)
 * then the macro becomes:
 *     (*(header+30) | *(buff+31) << 8 | *(buff+32) << 16 | *(buff+33) << 24)
 * aka:
 *     (header[30] | header[31] << 8 | header[32] << 16 | header[33] << 24)
 */
#define EMB_GET_INT(buff) \
    (*(buff) | *(buff+1) << 8 | *(buff+2) << 16 | *(buff+3) << 24)

#define EMB_GET_SHORT(buff) \
    (*(buff) | *(buff+1) << 8)

#define EMB_GET_INT_BE(buff) \
    (*(buff+3) | *(buff+2) << 8 | *(buff+1) << 16 | *(buff) << 24)

#define EMB_GET_SHORT_BE(buff) \
    (*(buff+1) | *(buff) << 8)

/* This should replace the need for many embFile_readType(file) functions.
 *
 * This also means that we don't need to "skip" padding variables while reading
 * etc as we just read the whole block.
 *
 * The right shift operator works differently with respect to sign so we cast
 * first. Also endianness matters as before.
 */
 
#define EMB_WRITE_INT(buff, a) \
    *(buff+0) = (unsigned int)a & 0x000000FF; \
    *(buff+1) = ((unsigned int)a & 0x0000FF00)>>8; \
    *(buff+2) = ((unsigned int)a & 0x00FF0000)>>16; \
    *(buff+3) = ((unsigned int)a & 0xFF000000)>>24;

#define EMB_WRITE_SHORT(buff, a) \
    *(buff+0) = (unsigned int)a & 0x00FF; \
    *(buff+1) = ((unsigned int)a & 0xFF00)>>8;

#define EMB_WRITE_INT_BE(buff, a) \
    *(buff+3) = (unsigned int)a & 0x000000FF; \
    *(buff+2) = ((unsigned int)a & 0x0000FF00)>>8; \
    *(buff+1) = ((unsigned int)a & 0x00FF0000)>>16; \
    *(buff+0) = ((unsigned int)a & 0xFF000000)>>24;

#define EMB_WRITE_SHORT_BE(buff, a) \
    *(buff+1) = (unsigned int)a & 0x00FF; \
    *(buff+0) = ((unsigned int)a & 0xFF00)>>8;

/* MATHS MACROS
 *
 * Rather than having to call a max function multiple times these macros allow
 * us to stack the variables up, this is particularly useful for bounding box
 * calculations.
 *
 * This also saves having int, float, double, etc. versions.
 */
#define EMB_MAX_2(a, b) \
    ((a > b) ? a : b)

#define EMB_MAX_3(a, b, c) \
    ((a > b) ? EMB_MAX_2(a, c) : EMB_MAX_2(b, c))

#define EMB_MAX_4(a, b, c, d) \
    EMB_MAX_2(EMB_MAX_2(a, b), EMB_MAX_2(c, d))

#define EMB_MIN_2(a, b) \
    ((a < b) ? a : b)

#define EMB_MIN_3(a, b, c) \
    ((a < b) ? EMB_MIN_2(a, c) : EMB_MIN_2(b, c))

#define EMB_MIN_4(a, b, c, d) \
    EMB_MIN_2(EMB_MIN_2(a, b), EMB_MIN_2(c, d))

