#include <math.h>

#include "embroidery.h"

int test_convert(int test_file, int from, int to);

/* Conversion Testing */
int
convert_tests(void)
{
    int i;
    for (i=0; i<3; i++) {
        int result = test_convert(i, EMB_FORMAT_CSV, EMB_FORMAT_DST);
        if (result) {
            return result;
        }
        result = test_convert(i, EMB_FORMAT_CSV, EMB_FORMAT_SVG);
        if (result) {
            return result;
        }
    }
    return 0;
}

/* Currently just crash testing. */
int
test_convert(int test_file, int from, int to)
{
    EmbString outf;
    EmbString fname_from;
    EmbString fname_to;
    sprintf(fname_from, "test%02d%s", test_file, formatTable[from].extension);
    sprintf(fname_to, "test%02d_out%s", test_file, formatTable[to].extension);
    printf("Converting test case %d: %s to %s.\n",
        test_file, fname_from, fname_to);

    EmbPattern* p = embp_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    embp_addThread(p, black_thread);

    switch (test_file) {
	case 0: {
        int i;
        EmbStitch st;
		/* 10mm circle */
		for (i = 0; i < 20; i++) {
			embp_addStitchRel(p, 0.0, 1.0, JUMP, 0);
		}
		for (i = 0; i < 200; i++) {
			st.x = 10 + 10 * sin(i * (0.03141592));
			st.y = 10 + 10 * cos(i * (0.03141592));
			st.flags = NORMAL;
			st.color = 0;
			embp_addStitchAbs(p, st.x, st.y, st.flags, st.color);
		}
		break;
	}
	case 1: {
        int i;
        EmbStitch st;
        /* sin wave */
        for (i = 0; i < 100; i++) {
            st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
            st.y = 10 + i * 0.1;
            st.flags = NORMAL;
            st.color = 0;
            embp_addStitchAbs(p, st.x, st.y, st.flags, st.color);
        }
		break;
	}
	case 2: {
        EmbCircle circle = emb_circle(10.0f, 1.0f, 5.0f);
        emb_array_add_circle(p->geometry, circle);
        embp_convertGeometry(p);
		break;
	}
    default: {
		puts("This case is not covered.");
		break;
	}
    }

    sprintf(outf, "test%02d%s", test_file, formatTable[to].extension);
    embp_end(p);
    if (!embp_write(p, outf, to)) {
        embp_free(p);
        return 16;
    }

    embp_free(p);

    convert(fname_from, fname_to);
    return 0;
}

int main(void)
{
    /* test_convert(); */
    return 0;
}

