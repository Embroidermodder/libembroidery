#ifndef __TESTS_LIBEMBROIDERY
#define __TESTS_LIBEMBROIDERY

/* A list of all our tests which should be of the form:
 *     int test_NAME(const int8_t *data);
 */
int test_arc(const int8_t *data);
int test_circle(const int8_t *data);
int test_ellipse(const int8_t *data);
int test_format_table(const int8_t *data);
int test_thread_color(const int8_t *data);
int test_vadd(const int8_t *data);
int test_vsubtract(const int8_t *data);
int test_vnormalize(const int8_t *data);

int has_space(const int8_t *line);
int get_func_id(const int8_t *line);
int run_test_func(const int8_t *line);
int test(const int8_t *name, int code);

int8_t *get_real(char *ptr, EmbReal * r, int *error);
int8_t *get_vector(char *ptr, EmbVector * v, int *error);

#endif
