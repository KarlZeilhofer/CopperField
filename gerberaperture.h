#ifndef GERBERAPERTURE_H
#define GERBERAPERTURE_H


/*
a gerber aperture is originally an optical mask, for defining tools.
it is defined with the AD-Block.
for example:
	%ADD17C,0.01000*%
		here a circular aperture was defined, with the ID-number 17 (D17), and a diameter of 0.01 (inch or mm).
	%ADD13R,0.062000X0.090000*%
		here a rectangular aperture was defined with sizeX 0.062 and sizeY of 0.09
	%ADD16O,0.110000X0.062000*%
		here an oval aperture was defined with sizeX of 0.11 and sizeY of 0.062
for now, only these three types are supported
holes are not supported
*/

#include <QObject>

class QPainterPath;
class QPointF;

class GerberAperture
{
public:
	enum Type{Circle, Oval, Rect}; // static definition of TYPE enum


public:
	GerberAperture(){};
	GerberAperture(int id, enum Type type, qreal sizeX, qreal sizeY)
	{
		this->id = id;
		this->type = type;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
	};

	QPainterPath getPath() const;
	QPainterPath getLinePath(const QPointF& delta) const;

public:
	int id; // aperture number
	enum Type type;
	qreal sizeX;
	qreal sizeY;
};

#endif // GERBERAPERTURE_H
