#ifndef __TESTS_LIBEMBROIDERY
#define __TESTS_LIBEMBROIDERY

/* A list of all our tests which should be of the form:
 *     int test_NAME(const char *data);
 */
int test_arc(const char *data);
int test_circle(const char *data);
int test_ellipse(const char *data);
int test_format_table(const char *data);
int test_thread_color(const char *data);
int test_vadd(const char *data);
int test_vsubtract(const char *data);
int test_vnormalize(const char *data);

int has_space(const char *line);
int get_func_id(const char *line);
int run_test_func(const char *line);
int test(const char *name, int code);

char *get_real(char *ptr, EmbReal * r, int *error);
char *get_vector(char *ptr, EmbVector * v, int *error);

#endif
