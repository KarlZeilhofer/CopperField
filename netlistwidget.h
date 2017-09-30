#ifndef NETLISTWIDGET_H
#define NETLISTWIDGET_H

#include <QListWidget>

class NetListWidget : public QListWidget
{
    Q_OBJECT
public:
	explicit NetListWidget(QWidget *parent = 0);


protected:
	void contextMenuEvent ( QContextMenuEvent * e );

signals:


public slots:
	void dontMillCklicked();
	void centralMillCklicked();
};

#endif // NETLISTWIDGET_H
