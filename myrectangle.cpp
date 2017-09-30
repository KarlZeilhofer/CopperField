/*
 * Rectangle.cpp
 *
 *  Created on: 12.01.2010
 *      Author: Karl
 */

#include "copperfield.h"
#include "MyRectangle.h"
#include <cmath>
#include "view.h"
#include <QGraphicsSceneMouseEvent>

/*
 * Konstruktion von Circle:
 * 	P1 = Center
 * 	P2 = Element vom Umkreis
 */
int MyRectangle::addPoint(QPointF p) {
	if (neededPoints - points.size() > 0) {
		points.append(p);
	}

	switch (points.size()) {
	case 1: // Punkt 1 des Rechtecks in Scene-Koordinaten
		setPos(points.at(0));
		break;
	case 2: // Punkt 2 des Kreises
		p2 = points.at(1) - points.at(0);
		break;
	}

	return neededPoints - points.size();
}

void MyRectangle::updateLastPoint(QPointF p) {
	if (points.size() > 0) {
		points.removeLast();
	}
	addPoint(p);
}

QPainterPath MyRectangle::shape() const {
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void MyRectangle::paint(QPainter *painter,
						const QStyleOptionGraphicsItem *option, QWidget *widget) {

	// CMYK Pelette füllt das Rechteck
	// CMYK hat 4 unabhängige Variablen. Leider können nur 2 davon variiert werden,
	// damit eine Fläche gezeichnet werden kann.

	painter->setPen(Qt::blue);
	painter->drawRect(0,0,p2.x(),p2.y());

	if (state == SELECTED) {
		painter->setPen(QPen(Qt::gray, 0, Qt::DashLine, Qt::RoundCap,
							 Qt::RoundJoin));
		painter->drawRect(boundingRect());

		// paint scaling handles:
		painter->setPen(QPen(Qt::gray, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		qreal x1, x2, y1, y2, h, w;
		x1 = 0;
		x2 = p2.x();
		y1 = 0;
		y2 = p2.y();

		if(x2<x1){
			qreal temp=x1;
			x1=x2;
			x2=temp;
		}
		if(y2<y1){
			qreal temp=y1;
			y1=y2;
			y2=temp;
		}

		w=x2-x1;
		h=y2-y1;

		View* view = CopperField::app->view;

		QPointF home = view->mapToScene(0,0);
		QPointF eX =  view->mapToScene(0,1);

		qreal k = sqrt((eX.x() - home.x())*(eX.x() - home.x()) +
					   (eX.y() - home.y())*(eX.y() - home.y())); // scaling factor

		qreal a = 10;
		QRectF rect(0,0, a*k, a*k);

		rect.moveCenter(QPointF(x1,y1));
		painter->drawRect(rect);
		rect.moveCenter(QPointF(x1,y2));
		painter->drawRect(rect);
		rect.moveCenter(QPointF(x2,y1));
		painter->drawRect(rect);
		rect.moveCenter(QPointF(x2,y2));
		painter->drawRect(rect);
	}
}

void MyRectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	static QPoint pStart; // screen position
	switch(state)
	{
	case DEFAULT:
		break;
	case SELECTED:
		state = DRAGING;
		pStart = event->screenPos();
		break;
	case DRAGING:

		break;
	case ROTATING:
		break;
	case SCALING:
		break;
	}
	update();
}

void MyRectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	switch(state)
	{
	case DEFAULT:
		state = SELECTED;
		break;
	case SELECTED:
		state = DEFAULT;
		break;
	case DRAGING:
		break;
	case ROTATING:
		break;
	case SCALING:
		break;
	}
	update();
}

void MyRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	switch(state)
	{
	case DEFAULT:
		break;
	case SELECTED:
		break;
	case DRAGING:
		state = SELECTED;
		break;
	case ROTATING:
		break;
	case SCALING:
		break;
	}
	update();
}
