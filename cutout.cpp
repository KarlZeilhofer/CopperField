#include "cutout.h"

/*
 * Rectangle.cpp
 *
 *  Created on: 12.01.2010
 *      Author: Karl
 */

#include "copperfield.h"
#include "cutout.h"
#include <cmath>
#include "view.h"
#include <QGraphicsSceneMouseEvent>

/*
 * Konstruktion von Circle:
 * 	P1 = Center
 * 	P2 = Element vom Umkreis
 */
int Cutout::addPoint(QPointF p) {
	if (neededPoints - points.size() > 0) {
		points.append(p);
	}

	if(points.size()==4){
		sortPoints();
		estimateCoordinates();
	}

	return neededPoints - points.size();
}

void Cutout::updateLastPoint(QPointF p) {
	if (points.size() > 0) {
		points.removeLast();
	}
	addPoint(p);
	if(points.size()==4){
		sortPoints();
		estimateCoordinates();
	}
}

QPainterPath Cutout::shape() const {
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void Cutout::paint(QPainter *painter,
						const QStyleOptionGraphicsItem *option, QWidget *widget) {

	// CMYK Pelette füllt das Rechteck
	// CMYK hat 4 unabhängige Variablen. Leider können nur 2 davon variiert werden,
	// damit eine Fläche gezeichnet werden kann.

	painter->setPen(Qt::blue);
	if(points.size()==4){
		painter->setPen(Qt::cyan);
		QPainterPath path;
		path.moveTo(rectPoints.at(0));
		for(int n=1; n<rectPoints.size(); n++){
			path.lineTo(rectPoints.at(n));
		}
		path.lineTo(rectPoints.at(0));
		painter->drawPath(path);

		QPainterPath cross;
		cross.moveTo(QPointF(-10,0));
		cross.lineTo(QPointF(10,0));
		cross.moveTo(QPointF(0,-10));
		cross.lineTo(QPointF(0,10));

		painter->setPen(Qt::red);

		for(int n=0; n<4; n++){
			painter->drawPath(cross.translated(points.at(n)));
		}
	}else if(points.size()>=1){
		QPainterPath path;
		path.moveTo(points.at(0));
		for(int n=1; n<points.size(); n++){
			path.lineTo(points.at(n));
		}
		path.lineTo(points.at(0));
		painter->drawPath(path);
	}

//	if (isSelected()) {
//		painter->setPen(QPen(Qt::gray, 0, Qt::DashLine, Qt::RoundCap,
//							 Qt::RoundJoin));
//		painter->drawRect(boundingRect());
//	}
}

void Cutout::sortPoints()
{
	// TODO: sort points like this:
	//		BotLef BotRig TopRig TopLef

}

void Cutout::estimateCoordinates()
{
	QPointF A=points.at(0);
	QPointF B=points.at(1);
	QPointF C=points.at(2);
	QPointF D=points.at(3);

	// width is mean length of AB and CD
	qreal AB = sqrt((B-A).x()*(B-A).x() + (B-A).y()*(B-A).y());
	qreal CD = sqrt((D-C).x()*(D-C).x() + (D-C).y()*(D-C).y());
	w = (AB+CD)/2;


	// height is mean length of AD and BC
	qreal AD = sqrt((D-A).x()*(D-A).x() + (D-A).y()*(D-A).y());
	qreal BC = sqrt((B-C).x()*(B-C).x() + (B-C).y()*(B-C).y());
	h = (AD+BC)/2;

	// center = center of mass
	QPointF c = (A+B+C+D)/4;
	cX = c.x();
	cY = c.y();

	// get angle
	phi = (getInclination(B-A)+getInclination(C-B) +
			getInclination(D-C) + getInclination(A-D))/4;
	//phi = getInclination(D-C);
	phi = ((getInclination(B-A)+getInclination(C-D))/2 +
		   (getInclination(C-B) + getInclination(D-A))/2 +M_PI_2)/2 ;
	rectPoints.clear();
	rectPoints.append(QPointF(cX +((- w/2)*cos(phi) - (- h/2)*sin(phi)), cY +((- w/2)*sin(phi) + (- h/2)*cos(phi)))); // A
	rectPoints.append(QPointF(cX +((+ w/2)*cos(phi) - (- h/2)*sin(phi)), cY +((+ w/2)*sin(phi) + (- h/2)*cos(phi)))); // B
	rectPoints.append(QPointF(cX +((+ w/2)*cos(phi) - (+ h/2)*sin(phi)), cY +((+ w/2)*sin(phi) + (+ h/2)*cos(phi)))); // C
	rectPoints.append(QPointF(cX +((- w/2)*cos(phi) - (+ h/2)*sin(phi)), cY +((- w/2)*sin(phi) + (+ h/2)*cos(phi)))); // D
}

// returns angle to horizontal or vertical in radians
// value is between -pi/4 to +pi/4°
qreal Cutout::getInclination(QPointF p)
{
	qreal x = p.x();
	qreal y = p.y();
	qreal alpha;

//	if(x == 0 || y == 0){
//		return 0.0;
//	}

//	if(fabs(y/x) <= 1){
//		alpha = atan(y/x);
//	}else
//	{
//		alpha = -atan(x/y);
//	}

	return atan2(y,x);

	return alpha;
}


