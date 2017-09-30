#include "crosshair.h"
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>
#include <Qt>

CrossHair::CrossHair(QGraphicsItem *parent, QGraphicsScene *scene)
		:QGraphicsPathItem(parent)
{
    QPainterPath path;

	QPen pen;
	pen.setColor(Qt::blue);
	pen.setWidth(0);

	setPen(QPen(pen));

    const int size = 100000;

    path.moveTo(-size, 0);
    path.lineTo(size,0);
    path.moveTo(0,-size);
    path.lineTo(0,size);


    //const QPainterPath &refPath = path;
    setPath(path);

    setZValue(1000);
}
