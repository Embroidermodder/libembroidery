/*
 * Test Program 1
 *
 * Error codes:
 *     0 Passed
 *     1 Loaded old version
 */

#include "../embroidery.h"

int
main(int argc, char *argv)
{
    if (EMB_LIB_VERSION_MAJOR != 1) {
        return 1;
    }
    return 0;
}
