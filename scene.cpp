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


