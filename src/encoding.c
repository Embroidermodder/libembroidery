#include "embroidery.h"

/*
 * TO DO: NEEDS ERROR REPORTING.
 */
unsigned char
toyota_position_encode(EmbReal x)
{
    if (x < 0.0) {
        return 0x80 + (-((char)emb_round(10.0*x)));
    }
    return (unsigned char)emb_round(10.0*x);
}

/*
 * .
 */
EmbReal
toyota_position_decode(unsigned char a)
{
    if (a > 0x80) {
        return - 0.1 * (a - 0x80);
    }
    return 0.1 * a;
}

