#include <stdlib.h>

#include "embroidery.h"

/* Tests if int8_t * matches a fixed string, often from compiled-in program
 * data.
 */
bool string_equal(int8_t *a, const char *b)
{
    int i;
    for (i = 0; b[i] && i < MAX_STRING_LENGTH; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    if (a[i] == b[i]) {
        return 1;
    }
    return 0;
}

void string_copy(int8_t *a, int8_t *b)
{
    int i;
    for (i = 0; a[i] && i < MAX_STRING_LENGTH; i++) {
        a[i] = b[i];
    }
    a[i] = 0;
}

/* . */
int parse_floats(const int8_t *line, float result[], int n)
{
    int8_t substring[MAX_STRING_LENGTH];
    const int8_t *c;
    int i = 0;
    int pos = 0;
    for (c = line; *c; c++) {
        substring[pos] = *c;
        if (*c == ',' || *c == ' ') {
            substring[pos] = 0;
            result[i] = atof(substring);
            pos = 0;
            i++;
            if (i > n - 1) {
                return -1;
            }
        } else {
            pos++;
        }
    }
    substring[pos] = 0;
    result[i] = atof(substring);
    return i + 1;
}

int parse_vector(const int8_t *line, EmbVector *v)
{
    float v_[2];
    if (parse_floats(line, v_, 2) == 2) {
        return 0;
    }
    v->x = v_[0];
    v->y = v_[1];
    return 1;
}
