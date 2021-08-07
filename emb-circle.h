/*! @file emb-circle.h */
#ifndef EMB_CIRCLE_H
#define EMB_CIRCLE_H

#include "emb-color.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

#define CHUNK_SIZE 128

typedef struct EmbCircle_
{
    double centerX;
    double centerY;
    double radius;
} EmbCircle;

typedef struct EmbCircleArray_
{
    EmbCircle *circle;
    int *lineType;
    EmbColor *color;
    int count;
    int length;
} EmbCircleArray;

extern EMB_PUBLIC EmbCircleArray* EMB_CALL embCircleArray_create();
extern EMB_PUBLIC int EMB_CALL embCircleArray_add(
    EmbCircleArray* pointer, EmbCircle circle, int linetype, EmbColor color);
extern EMB_PUBLIC void EMB_CALL embCircleArray_free(EmbCircleArray* pointer);

extern EMB_PUBLIC int EMB_CALL getCircleCircleIntersections(
    /* The circle */
    EmbCircle c0, EmbCircle c1,
    /* Intersection Point */
    double* px3, double* py3,
    /* Intersection Point */
    double* px4, double* py4);

extern EMB_PUBLIC int EMB_CALL getCircleTangentPoints(
    /* The circle */
    EmbCircle c,
    /* Point to determine tangency */
    double  px,  double  py,
    /* Tangent Point 0 */
    double* tx0, double* ty0,
    /* Tangent Point 1 */
    double* tx1, double* ty1);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* EMB_CIRCLE_H */

