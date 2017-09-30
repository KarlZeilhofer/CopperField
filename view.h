#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>

#include <QObject> // wird für selbst gemachte SLOTS benötigt!

class QGraphicsScene;
class QGraphicsItem;
class CrossHair;
class Scene;

class View : public QGraphicsView
{
	Q_OBJECT // wird für selbst gemachte SLOTS benötigt!

public:
    View(QWidget *parent);

private:
    void wheelEvent(QWheelEvent *event); // überladen von QGraphicsItem::wheelEvent()
    void mouseMoveEvent(QMouseEvent *event);

public slots:
	void zoomAll();

signals:
    void scaleChanged(qreal scale);

protected:

public:
	Scene *scene;

private:
    CrossHair *crossHair;
    static const qreal zoomFactor=1.2;
    int drawingState; // todo: allgemeine Statemachine definieren
						// allgemein in bezug auf alle möglichen figuren.
};

#endif // VIEW_H
