#include "dialoglayers.h"
#include "ui_dialoglayers.h"
#include "qdebug.h"

//DialogLayers::FirstLayer = BOT;
//enum LayerType DialogLayers::LastLayer = DRILLS;

DialogLayers::DialogLayers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLayers)
{
    ui->setupUi(this);

	ui->layerWidget_bot->setLayerType(LayerWidget::BOT);
	ui->layerWidget_botMill->setLayerType(LayerWidget::BOT_MILL);
	ui->layerWidget_top->setLayerType(LayerWidget::TOP);
	ui->layerWidget_topMill->setLayerType(LayerWidget::TOP_MILL);
	ui->layerWidget_contour->setLayerType(LayerWidget::CONTOUR);
	ui->layerWidget_contourMill->setLayerType(LayerWidget::CONTOUR_MILL);
	ui->layerWidget_drill->setLayerType(LayerWidget::DRILLS);

	// build radio button group
	bg.addButton(ui->layerWidget_bot->radioButton(), LayerWidget::BOT);
	bg.addButton(ui->layerWidget_botMill->radioButton(), LayerWidget::BOT_MILL);
	bg.addButton(ui->layerWidget_top->radioButton(), LayerWidget::TOP);
	bg.addButton(ui->layerWidget_topMill->radioButton(), LayerWidget::TOP_MILL);
	bg.addButton(ui->layerWidget_contour->radioButton(), LayerWidget::CONTOUR);
	bg.addButton(ui->layerWidget_contourMill->radioButton(), LayerWidget::CONTOUR_MILL);
	bg.addButton(ui->layerWidget_drill->radioButton(), LayerWidget::DRILLS);

	connect(&bg, SIGNAL(buttonClicked(int)), this, SLOT(emitActiveLayer(int)));
}

DialogLayers::~DialogLayers()
{
    delete ui;
}

void DialogLayers::setActiveLayer(LayerWidget::LayerType layer)
{
	dynamic_cast<LayerWidget*>(bg.button(layer)->parent())->setActive();
}

void DialogLayers::setGerberReader(LayerWidget::LayerType layer, GerberReader* gr)
{
	dynamic_cast<LayerWidget*>(bg.button(layer)->parent())->setActive(gr);
}

void DialogLayers::resetDialog()
{
	ui->layerWidget_bot->setEnabled(false);
	ui->layerWidget_botMill->setEnabled(false);
	ui->layerWidget_top->setEnabled(false);
	ui->layerWidget_topMill->setEnabled(false);
	ui->layerWidget_contour->setEnabled(false);
	ui->layerWidget_contourMill->setEnabled(false);
	ui->layerWidget_drill->setEnabled(false);
}

void DialogLayers::disableLayerWidget(LayerWidget::LayerType layer)
{
	switch(layer){
	case LayerWidget::BOT:
		ui->layerWidget_bot->setEnabled(false);
		break;
	case LayerWidget::BOT_MILL:
		ui->layerWidget_botMill->setEnabled(false);
		break;
	case LayerWidget::TOP:
		ui->layerWidget_top->setEnabled(false);
		break;
	case LayerWidget::TOP_MILL:
		ui->layerWidget_topMill->setEnabled(false);
		break;
	case LayerWidget::CONTOUR:
		ui->layerWidget_contour->setEnabled(false);
		break;
	case LayerWidget::CONTOUR_MILL:
		ui->layerWidget_contourMill->setEnabled(false);
		break;
	case LayerWidget::DRILLS:
		ui->layerWidget_drill->setEnabled(false);
		break;
	}
}

LayerWidget::LayerType DialogLayers::activeLayer()
{
	return (LayerWidget::LayerType)(bg.checkedId());
}

void DialogLayers::emitActiveLayer(int buttonId)
{
	emit activeLayerChanged(activeLayer());
}
