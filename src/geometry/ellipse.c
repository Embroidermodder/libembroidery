#include "embroidery.h"

/*
 */
EmbEllipse emb_ellipse_init(void)
{
    EmbEllipse ellipse;
    ellipse.center.x = 0.0;
    ellipse.center.y = 0.0;
    ellipse.radius.x = 1.0;
    ellipse.radius.y = 2.0;
    ellipse.rotation = 0.0;
    return ellipse;
}

/* . */
EmbReal emb_ellipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

EmbReal emb_ellipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

/*
void emb_ellipse_init(EmbEllipse ellipse, uint32_t rgb, int lineType)
{
    printf("%f %d %d", ellipse.radius.x, rgb, lineType);
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Ellipse");

    setFlag(ItemIsSelectable, true);

    setSize(width, height);
    setCenter(centerX, centerY);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
}
*/

void emb_ellipse_setSize(float width, float height)
{
    printf("%f %f", width, height);
    /*
       EmbRect elRect = rect();
       elRect.setWidth(width);
       elRect.setHeight(height);
       elRect.moveCenter(EmbVector(0,0));
       setRect(elRect);
     */
}

