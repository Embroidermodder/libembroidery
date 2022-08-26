/*
 * EmbroiderBot
 * Copyright 2021-2022 The Embroidermodder Team
 * Distributed under the terms of the zlib license (see LICENSE).
 */

/* The Macro library is crucial to keeping the executable size under
 * 32kb and suitable for Arduino Uno.
 *
 * If a function is expressible as one or two lines of code, by
 * expressing it as a macro:
 *     o if it is never called then it uses no storage
 *     o if it is called then it uses as much, if not less storage
 *     o it cuts the call/return overhead
 *
 * For longer functions it is less storage to have have the function
 * not be a macro, unless the likelihood that it is called is low.
 *
 * For example we could have a macro system that interprets file types
 * conditionally, so if the user needs DST and JEF but no others then we
 * can just have DST_READ, DST_WRITE, JEF_READ, JEF_WRITE as macros and
 * therefore all the other formats aren't compiled in.
 * 
 */
#define EMB_MIN(A, B) ((A < B) ? (A) : (B))
#define EMB_MAX(A, B) ((A > B) ? (A) : (B))
#define EMB_ABS(A, B) ((A < 0.0) ? (-A) : (A))

#define FREAD16(file, data)     fread(&data, 2, 1, file)
#define FWRITE16(file, data)    fwrite(&data, 2, 1, file)
#define FREAD32(file, data)     fread(&data, 4, 1, file)
#define FWRITE32(file, data)    fwrite(&data, 4, 1, file)

#define FREAD_INT16_BE(file, data) \
    FREAD16(file, data); \
    reverse_byte_order(&data, 2)
#define FWRITE_INT16_BE(file, data) \
    FWRITE16(file, data); \
    reverse_byte_order(&data, 2)
#define FREAD_INT32_BE(file, data) \
    FREAD32(file, data); \
    reverse_byte_order(&data, 4)
#define FWRITE_INT32_BE(file, data) \
    FREAD16(file, data); \
    reverse_byte_order(&data, 4)

typedef struct EmbVector_ {
    double x;
    double y;
} EmbVector;

typedef struct EmbCircle_ {
    EmbVector center;
    double radius;
} EmbCircle;

typedef struct EmbColor_ {
    char r;
    char g;
    char b;
} EmbColor;

void embVector_add(EmbVector a, EmbVector b, EmbVector *out);
void embVector_average(EmbVector a, EmbVector b, EmbVector *out);
double embVector_distance(EmbVector a, EmbVector b);
double embVector_dot(EmbVector a, EmbVector b);
void embVector_subtract(EmbVector a, EmbVector b, EmbVector *out);
double embVector_getLength(EmbVector a);
void embVector_multiply(EmbVector a, float c, EmbVector *out);

void reverse_byte_order(void *data, int bytes);

EmbColor embColor_fromHexStr(char* val);

