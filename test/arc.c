#include "embroidery.h"

/* Caller wrapper for testing: note that this assumes that the error variable
 * is called "error".
 */
#define TEST(LINE) \
    LINE; \
    if (error) { \
        return error; \
    }

/* Debugging output */
void emb_vector_print(EmbVector v, char *label);
void emb_arc_print(EmbArc a);

/*
 * Testing if all arc attributes can be created without error.
 */
EmbError
test_arc_attributes(EmbGeometry g)
{
    EmbVector center, chordMid;
    EmbReal bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    unsigned char clockwise;
    EmbError error = EMB_NO_ERR;
    bulge = -0.414213562373095f;
    /* bulge = emb_arc_bulge(g); */
    TEST(center = emb_center(&g, &error))
    TEST(chord = emb_vector_length(emb_chord(&g, &error)))
    TEST(radius = emb_radius(&g, &error))
    TEST(diameter = emb_diameter(&g, &error))
/* FIXME:
    TEST(chordMid = emb_chord_mid(&g, &error))
*/
    TEST(sagitta = emb_sagitta(&g, &error))
/* FIXME:
    TEST(apothem = emb_apothem(&g, &error))
    TEST(incAngle = emb_inc_angle(&g, &error))
*/
    TEST(clockwise = emb_clockwise(&g, &error))

    printf("test_arc:");
// FIXME:    emb_arc_print(g);
    emb_vector_print(center, "center");
    emb_vector_print(chordMid, "chordMid");
    printf(
        "bulge     = %f\n"
        "radius    = %f\n"
        "diameter  = %f\n"
        "chord     = %f\n"
        "sagitta   = %f\n"
        "apothem   = %f\n"
        "incAngle  = %f\n"
        "clockwise = %d\n"
        "\n",
        bulge,
        radius,
        diameter,
        chord,
        sagitta,
        apothem,
        incAngle,
        clockwise);
    return 0;
}

/* TODO: a clockwise and a anti-clockwise test. */
int main(void)
{
    EmbError error;
    EmbGeometry g = emb_arc(1.0, 0.0, 0.0, 0.0, 2.0, 1.0);
    TEST(error = test_arc_attributes(g))

    g = emb_arc(4.0, 0.0, 0.0, 0.0, 5.0, 1.0);
    TEST(error = test_arc_attributes(g))

    return EMB_NO_ERR;
}


