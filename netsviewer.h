#ifndef NETSVIEWER_H
#define NETSVIEWER_H

#include <QDockWidget>
#include <QVector>
#include <QGraphicsItem>

class NetListWidget;
class GerberElement;

class NetsViewer : public QDockWidget
{
    Q_OBJECT
public:
    explicit NetsViewer(QWidget *parent = 0);
	void setNets(QVector<QVector<GerberElement*>*> list);
	void clear(); // clear the list

signals:

public slots:
	void selectNet(int net);

private:
	NetListWidget* listWidget;
	QVector<QVector<GerberElement*>*> nets;
};

#endif // NETSVIEWER_H
