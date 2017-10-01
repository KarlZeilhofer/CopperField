#include "copperfield.h"
#include "griditem.h"
#include <QGraphicsScene>
#include <QPointF>
#include "scene.h"
#include <cmath>
#include <QtWidgets>



Scene::Scene(QObject *parent)
        :QGraphicsScene(parent)
{
    myGrid = new GridItem(0);
    myGrid->setSpacing(2);
	//addItem(myGrid);
	snapOn = false;

}

GridItem* Scene::grid() const{
    return myGrid;
}

QPointF Scene::snapToGrid(QPointF p) const
{
	if(snapOn){
		QPointF pG; // point on grid
		qreal spacing = myGrid->spacing();

		pG.setX(spacing*qRound(p.x()/spacing));
		pG.setY(spacing*qRound(p.y()/spacing));

		return pG;
	}else{
		return p;
	}
}

QRectF Scene::boundingRect()
{
	QRectF bb;

	int n=0;
	foreach(QGraphicsItem* i,items()){
		if(n>0){ // skip cross hair // TODO 5: replace this dirty hack
			QRectF ri = i->boundingRect();
			bb = bb.united(ri);
		}
		n++;
	}

	return bb;
}

void Scene::clearAllButCrosshair()
{
	int n=0;
	foreach(QGraphicsItem* i,items()){
		if(n>0){ // skip cross hair // TODO 5: replace this dirty hack
			removeItem(i);
		}
		n++;
	}
}


