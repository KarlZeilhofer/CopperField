#include "view.h"
#include "crosshair.h"
#include "scene.h"

#include <QtWidgets>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QWheelEvent>
#include <QObject>
#include "DrawingItem.h"
#include <QPaintEvent>

#include "copperfield.h"


View::View(QWidget* parent):QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing);
	setViewport(new QWidget());
	setMouseTracking(true); // enable mouse tracking for positioning the cross hair
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::RubberBandDrag); // enable selecting items by "rubber band"
	//setCursor(Qt::BlankCursor); // set curosr invisible
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new Scene(this);

	crossHair = new CrossHair(NULL,NULL);
	scene->addItem(crossHair);


    setScene(scene);

    //connect(this, SIGNAL(scaleChanged(qreal)),scene->grid(), SLOT(setViewScale(qreal)));

    drawingState=0; // Zustand für Grafik-Objekte zeichnen: idle
}

/*
 * handles zooming of the view.
 * keeps the same scene-point under the cursor while zooming in and out
 */
void View::wheelEvent(QWheelEvent *event)
{
    int degrees = event->delta()/8;

    if(degrees > 0) // wheel from user away (zoom in)
    {
		if(matrix().m11() < 10000) // limit zoom factor
        {
            scale(zoomFactor, zoomFactor);
            // scroll values:
            int sX = (scene->snapToGrid(event->pos()).x() - viewport()->width()/2)*(zoomFactor - 1);
            int sY = (scene->snapToGrid(event->pos()).y() - viewport()->height()/2)*(zoomFactor - 1);
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()+sX);
            verticalScrollBar()->setValue(verticalScrollBar()->value()+sY);
        }
    }
    if(degrees < 0) // wheel turned to user (zoom out)
    {
        if(matrix().m11() > 1./10.) // limit zoom factor
        {
            scale((qreal)(1./zoomFactor), (qreal)(1./zoomFactor));
            // scroll values:
            int sX = (scene->snapToGrid(event->pos()).x() - viewport()->width()/2)*(1.0/zoomFactor - 1);
            int sY = (scene->snapToGrid(event->pos()).y() - viewport()->height()/2)*(1.0/zoomFactor - 1);
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()+sX);
            verticalScrollBar()->setValue(verticalScrollBar()->value()+sY);
        }
    }
    emit scaleChanged((qreal)(matrix().m11()));
}



void View::mouseMoveEvent(QMouseEvent *event)
{
    crossHair->setPos(scene->snapToGrid(mapToScene(event->pos())));

	// print coordinate position in status bar
	currentPos = mapToScene(event->pos());
	updateCoordinates();


	QGraphicsView::mouseMoveEvent(event); // call standard implementation
}


void View::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Space){
		relativeOrigin = currentPos;
		updateCoordinates();
	}
}

void View::updateCoordinates()
{
	QPointF p = currentPos;

	QString abs = QString("POS: %1/%2").
			arg(p.x(), 8, 'f', 3).
			arg(-p.y(), 8, 'f', 3);// inverted y-axis
	QString rel = QString("REL: %1/%2").
			arg(p.x()-relativeOrigin.x(), 8, 'f', 3).
			arg(-(p.y()-relativeOrigin.y()), 8, 'f', 3);// inverted y-axis

	CopperField::app->statusText.setText(abs + "  " + rel); // inverted y-axis
}

// slot:
void View::zoomAll()
{
	fitInView(scene->boundingRect(), Qt::KeepAspectRatio);

	qDebug() << scene->boundingRect();
}

























