#ifndef NETLISTWIDGET_H
#define NETLISTWIDGET_H

#include <QListWidget>
#include "gerberreader.h"

class NetListWidget : public QListWidget
{
    Q_OBJECT
public:
	explicit NetListWidget(QWidget *parent = 0);


protected:
	void contextMenuEvent ( QContextMenuEvent * e );

signals:
	void optionChanged(int netId, GerberReader::MillOption option);

public slots:
	void noMillClicked();
	void isolateClicked();
	void engraveClicked();
};

#endif // NETLISTWIDGET_H
