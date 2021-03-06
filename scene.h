#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class GridItem;

/*
 * Scene st vorläufig eine Klasse, die einer Zeichnung entspricht.
 * Sie beinhaltet alle Zeichenobjekte und besitzt ein vom Bildschirm unabhängiges
 * Koordinatensystem.
 * Dargestellt wird Scene mit der Klasse View.
 * TODO 5: Layer-Implementierung
 */

class Scene : public QGraphicsScene
{
public:
    Scene(QObject *parent);
    GridItem* grid() const;
    QPointF snapToGrid(QPointF p) const;

    //void drawBackground ( QPainter * painter, const QRectF & rect );

private:
    GridItem* myGrid;
	bool snapOn;

public:
	QRectF boundingRect();
	void clearAllButCrosshair();
};

#endif // SCENE_H
