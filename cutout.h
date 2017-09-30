
/*
 * cutout.h
 *
 *  Created on: 18.01.2012
 *      Author: Karl Zeilhofer
 */

#ifndef CUTOUT_H
#define CUTOUT_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>
#include "DrawingItem.h"
#include <QStyleOptionGraphicsItem> // needed in painter method for setClipRect()
#include <QPainterPath>

/*
 * Grafik-Objekt: Rechteck
 * Definiert durch 4 Eckpunkte
 * Größe, Position und Rotation werden approximiert.
 */

class Cutout : public DrawingItem
{
public:
	Cutout(QGraphicsItem *parent, QGraphicsScene *scene) :
		DrawingItem(parent, scene) { // automatischer Aufruf des übergeordneten-Konstruktors
		neededPoints = 4;

		setPos(QPointF(0, 0));
		setFlag(QGraphicsItem::ItemIsMovable, true);
		setFlag(QGraphicsItem::ItemIsSelectable, true);
	};

	// TODO: Snap Item to Grid on Move per Drag'n'Drop (mouseMoveEvent() and mousePressEvent())


	// zu überladende funktionen
	// schlüsselwort "virtual" ist nicht notwendig, aber besser lesbar.
	virtual int addPoint(QPointF p);
	virtual void updateLastPoint(QPointF p);
	virtual int pointsLeft() {
		return neededPoints - points.size();
	};

	// überladen
	QRectF boundingRect() const {
		if(points.size()==0)
			return QRectF(QPointF(0,0),QPointF(0,0));
		else
			return QRectF(points.at(0), points.last());
	}

	// überladen:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			   QWidget *widget);

	QPainterPath shape() const; // TODO: check for corret PaiterPath. hint: circle is not filled

private:
//	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//	void mousePressEvent(QGraphicsSceneMouseEvent *event);
//	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void sortPoints(); // sort points into correct order.
	void estimateCoordinates();
	qreal getInclination(QPointF p);

private:
	//QPoint p1; // is set via x,y inherited from QGraphicsItem
	// QPointF p2,p3,p4;
	qreal cX, cY, w, h, phi; // center, size, rotation of the estemated rect
	QList<QPointF> rectPoints;
};

#endif // CUTOUT_H
