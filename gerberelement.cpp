#include "gerberelement.h"
#include <QGraphicsPathItem>
#include <QBrush>
#include <QPen>
#include <qdebug.h>

GerberElement::GerberElement(GerberAperture ap)
{
	aperture = ap;
	graphicsItem = 0;
}

QGraphicsPathItem* GerberElement::getItem()
{
	if(graphicsItem == 0){
		QGraphicsPathItem* item=0;

		switch(elementType){
		case Outline:
		{
			// TODO 3: elementType Outline implementieren
			qDebug() << "Info: Unsupported Element Type: Outline";
		}break;
		case Polygon:
		{
			QPainterPath p;
			p.setFillRule(Qt::WindingFill);

			for(int n=1; n<size(); n++){ // for all points in this polygon
				QLineF cl = QLineF(at(n-1), at(n)); // current line
				QPainterPath linePath = aperture.getLinePath(cl.p2() - cl.p1());
				linePath.translate(cl.p1().x(), cl.p1().y());
				p.addPath(linePath);
			}
			item = new QGraphicsPathItem(p);
		}break;

		case Flash:
		case Drill:
		{
			QPainterPath p = aperture.getPath();
			p.translate(at(0));
			item = new QGraphicsPathItem(p);
		}break;
		default:
			qDebug() << QString("Error: unhandled Element Type: ") <<  (int)elementType;
		}

		if(item){
			QPen p;
			p.setColor(color);
			p.setWidth(0);
			item->setPen(p);

			item->setBrush(QBrush(color));
		}
		graphicsItem = item;
	}

	return graphicsItem;
}

void GerberElement::highlight(bool flag)
{
	if(graphicsItem){
		if(flag){
			QColor c = color;
			c = c.lighter(200);
			c.setAlpha(255);
			graphicsItem->setBrush(c);
		}else{
			graphicsItem->setBrush(color);
		}
	}
}


// TODO 5: check if there is a better way to get the points out of this class
QPolygonF GerberElement::polygon()
{
	QPolygonF p;
	for(int n=0; n<size(); n++){
		p.append(at(n));
	}
	return p;
}

void GerberElement::setVisible(bool flag)
{
	if(graphicsItem){
		graphicsItem->setVisible(flag);
	}
}

