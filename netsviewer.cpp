#include "netsviewer.h"
#include "netlistwidget.h"
#include <QtWidgets>
#include "gerberelement.h"

NetsViewer::NetsViewer(QWidget *parent) :
    QDockWidget(parent)
{
	listWidget = new NetListWidget(this);
	//setLayout(new QGridLayout(this));
	setWidget(listWidget);

	connect(listWidget, SIGNAL(optionChanged(int,GerberReader::MillOption)),
			this, SLOT(setOption(int,GerberReader::MillOption)));
}

void NetsViewer::setNets(QVector<QVector<GerberElement*>*> list)
{
	nets = list;
	clear();

	// add nets to the listWidget
	for(int n=0; n<nets.size(); n++){
		listWidget->addItem(new QListWidgetItem(QString("Net %1 (%2 elements)").arg(n).arg(nets.at(n)->size())));
	}

	connect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(selectNet(int)));
}

void NetsViewer::selectNet(int netID)
{
	QVector<GerberElement*>* net;


	for(int i=0; i<nets.size(); i++){
		net = nets.at(i);
		for(int n=0; n<net->size(); n++){
			net->at(n)->highlight(false);
		}
	}

	net = nets.at(netID);
	for(int n=0; n<net->size(); n++){
		net->at(n)->highlight(true);
	}
}

void NetsViewer::setOption(int netId, GerberReader::MillOption option)
{
	emit optionChanged(netId, option);
}

void NetsViewer::clear()
{
	disconnect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(selectNet(int))); // this is needed to avoid crashes
		// when a net is selected, and setNets() is called again.
	listWidget->clear();
}
