#include "embroidery.h"

void testTangentPoints(EmbCircle c, double px, double py,
        EmbPoint *, EmbPoint *);
int testEmbCircle(void);
int testThreadColor(void);
int create_test_csv_file(char *fname, int type);
int full_test_matrix(char *fname);
int create_test_file_1(const char* outf, int mode);
int create_test_file_2(const char* outf, int mode);
void testMain(int level);
int testEmbFormat(void);
int testGeomArc(void);
