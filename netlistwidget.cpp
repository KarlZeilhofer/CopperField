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

	cm->addAction("No Mill", this, SLOT(noMillClicked()));
	cm->addAction("Isolate", this, SLOT(noMillClicked()));
	cm->addAction("Engrave", this, SLOT(noMillClicked()));
	cm->exec(e->globalPos());
}

// SLOT:
void NetListWidget::noMillClicked()
{
	qDebug("no mill clicked");
	emit optionChanged(currentRow(), GerberReader::MO_NoMill);

}

void NetListWidget::isolateClicked()
{
	qDebug("isolate clicked");
	emit optionChanged(currentRow(), GerberReader::MO_Isolate);
}

void NetListWidget::engraveClicked()
{
	qDebug("engrave clicked");
	emit optionChanged(currentRow(), GerberReader::MO_Engrave);
}
