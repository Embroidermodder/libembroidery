/*
 * Libembroidery Testing -- part of the sew CLI.
 *
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"
#include "test.h"

typedef struct TestFunc_ {
        const char *label;
        int (*func)(const char *data);
} TestFunc;

static TestFunc test_functions[] = {
        {.label = "arc",.func = test_arc},
        {.label = "circle",.func = test_circle},
        {.label = "ellipse",.func = test_ellipse},
        {.label = "format_table",.func = test_format_table},
        {.label = "thread_color",.func = test_thread_color},
        {.label = "vadd",.func = test_vadd},
        {.label = "vsubtract",.func = test_vsubtract},
        {.label = "vnormalize",.func = test_vnormalize},
        {.label = "_END",.func = test_arc}
};

static int test_result = 0;
static int test_index = 0;
static float epsilon = 0.000001;

const char *test_data[] = {
        "arc",
        "circle",
        "ellipse",
        "format_table",
        "thread_color",
        "vadd 1.6 3.21 1.64 3.11 3.24 6.32",
        "vsubtract 1.6 3.21 1.64 3.11 -0.04 0.1",
        "_END"
};

/* Find location of first space, if it exists then return
 * string position, otherwise return -1.
 */
int has_space(const char *line)
{
        int i;
        if (line == NULL) {
                printf("ERROR: has space called with NULL.\n");
                return -1;
        }
        for (i = 0; line[i]; i++) {
                if (line[i] == ' ') {
                        return i;
                }
        }
        return -1;
}

/* Identify test function based on label */
int get_func_id(const char *label)
{
        int i;
        for (i = 0; test_functions[i].label[0] != '_'; i++) {
                if (!strcmp(label, test_functions[i].label)) {
                        return i;
                }
        }
        return -1;
}

/* Call test function based on data. */
int run_test_func(const char *line)
{
        char function_label[100];
        int space_pos = has_space(line);
        for (int i = 0; i < 100; i++) {
                function_label[i] = 0;
        }
        if (space_pos > 0) {
                strncpy(function_label, line, space_pos);
                int func_id = get_func_id(function_label);
                if (func_id >= 0) {
                        char *data = line + space_pos + 1;
                        int code = test_functions[func_id].func(data);
                        test(line, code);
                }
        } else {
                /* Entire line is a single command, so we pass it to the identifier. */
                int func_id = get_func_id(line);
                int code = test_functions[func_id].func("");
                test(line, code);
        }
        return 0;
}

/* Get real!
 * TODO: deal with errors.
 */
char *get_real(char *ptr, EmbReal *r, int *error)
{
        char data[100];
        int space_pos = has_space(ptr);
        for (int i = 0; i < 100; i++) {
                data[i] = 0;
        }
        if (space_pos > 0) {
                strncpy(data, ptr, space_pos);
                *r = atof(data);
                return ptr + space_pos + 1;
        }
        *r = atof(ptr);
        return ptr + strlen(ptr);
}

char *get_vector(char *ptr, EmbVector *v, int *error)
{
        EmbReal r = 0.0;
        char *p = get_real(ptr, &r, error);
        v->x = r;
        p = get_real(p, &r, error);
        v->y = r;
        printf("get_vector %f %f \n", v->x, v->y);
        return p;
}

/* Run test */
int test(const char *name, int code)
{
        if (code) {
                printf("FAIL (%03d): %s\n", test_index, name);
        } else {
                test_result++;
                printf("PASS (%03d): %s\n", test_index, name);
        }
        test_index++;
}

/* We don't use fail fast in testing: all results are reported. */
int run_tests(void)
{
        /* This would amount to an accuracy of 7-8 significant figures in calculations on
         * the scale of an embroidery since our unit size is generally 0.1mm.
         */
        int i;
        for (i = 0; test_data[i][0] != '_'; i++) {
                run_test_func(test_data[i]);
        }

        printf("OVERALL RESULT: %03d/%03d\n", test_result, test_index);
        return 0;
}
