#include "netlistwidget.h"
#include <QContextMenuEvent>
#include <QMenu>

NetListWidget::NetListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void NetListWidget::contextMenuEvent ( QContextMenuEvent * e )
{
	int row = currentRow();

	QMenu* cm = new QMenu(this); // context menu

	cm->addAction("don't mill", this, SLOT(dontMillCklicked()));
	cm->addAction("central mill", this, SLOT(dontMillCklicked()));
	cm->exec(e->globalPos());
}

// SLOT:
void NetListWidget::dontMillCklicked()
{
	qDebug("don't mill clicked");
	// TODO 2: forward this slot to the netsviewer
}

void NetListWidget::centralMillCklicked()
{
	qDebug("central mill clicked");
	// TODO 2: forward this slot to the netsviewer
}
