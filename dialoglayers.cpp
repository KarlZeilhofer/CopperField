#include "dialoglayers.h"
#include "ui_dialoglayers.h"

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

LayerWidget::LayerType DialogLayers::activeLayer()
{
	return (LayerWidget::LayerType)(bg.checkedId());
}
