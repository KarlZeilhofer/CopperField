#ifndef GERBERELEMENT_H
#define GERBERELEMENT_H

#include <QPolygonF>
#include <gerberaperture.h>
#include <QGraphicsItem>

class GerberElement : public QPolygonF
{
public:
	explicit GerberElement(GerberAperture ap);
	QGraphicsPathItem* getItem();

	void highlight(bool flag);
	QPolygonF polygon();

	void setVisible(bool flag);




public:
	GerberAperture aperture;
	QColor color;
	enum Type{None, Outline, Polygon, Flash, Drill} elementType;

private:
	QGraphicsPathItem* graphicsItem;
};

#endif // GERBERELEMENT_H
