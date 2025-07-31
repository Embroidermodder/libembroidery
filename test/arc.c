/*
 * Testing if all arc attributes can be created without error.
 */

#include <string.h>
#include <math.h>

#include "../src/embroidery.h"

int arc_attributes(EmbGeometry arc);

void emb_vector_print(EmbVector v, char *label);
void emb_arc_print(EmbArc a);

/* TODO: a clockwise and a anti-clockwise test. */
int
main(void)
{
    EmbGeometry g = emb_arc(1.0, 0.0, 0.0, 0.0, 2.0, 1.0);
    if (arc_attributes(g)) {
        return 1;
    }

    g = emb_arc(4.0, 0.0, 0.0, 0.0, 5.0, 1.0);
    if (arc_attributes(g)) {
        return 1;
    }

    return 0;
}

/* . */
int
arc_attributes(EmbGeometry g)
{
    EmbVector center, chordMid;
    EmbReal bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    unsigned char clockwise;
    int error = EMB_NO_ERR;
    bulge = -0.414213562373095f;
    /* bulge = emb_arc_bulge(g); */
    center = emb_center(&g, &error);
    if (error) {
        return 1;
    }
    chord = emb_vector_length(emb_chord(&g, &error));
    if (error) {
        return 1;
    }
    radius = emb_radius(&g, &error);
    if (error) {
        return 1;
    }
    diameter = emb_diameter(&g, &error);
    if (error) {
        return 1;
    }
/* FIXME:
    chordMid = emb_chord_mid(&g, &error);
    if (error) {
        return 1;
    }
*/
    sagitta = emb_sagitta(&g, &error);
    if (error) {
        return 1;
    }
/* FIXME:
    apothem = emb_apothem(&g, &error);
    if (error) {
        return 1;
    }
    incAngle = emb_inc_angle(&g, &error);
    if (error) {
        return 1;
    }
*/
    clockwise = emb_clockwise(&g, &error);
    if (error) {
        return 1;
    }

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
}
