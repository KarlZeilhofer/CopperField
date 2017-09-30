#include "layerwidget.h"
#include "ui_layerwidget.h"



QStringList LayerWidget::LayerNames = QString("None,Bottom,Bottom Mill,Top,Top Mill,PCB Edge,PCB Edge Mill,Drills").split(',');

LayerWidget::LayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerWidget)
{
    ui->setupUi(this);
	layerType = NONE;
	firstActivation = true;

	setEnabled(false);
	gr = 0;
}

LayerWidget::~LayerWidget()
{
    delete ui;
}

void LayerWidget::setActive()
{
	ui->radioButton->setChecked(true);
	setEnabled(true);
	if(firstActivation){
		firstActivation = false;
		ui->checkBox_visible->setChecked(true);
	}
}

void LayerWidget::setActive(GerberReader* grObj)
{
	gr = grObj;
	if(ui->radioButton->text().endsWith("mill", Qt::CaseInsensitive)==false){
		setActive();
	}
}


void LayerWidget::setLayerType(LayerType t)
{
	layerType = t;
	ui->radioButton->setText(LayerNames.at(t));
}

QRadioButton* LayerWidget::radioButton()
{
	return ui->radioButton;
}



void LayerWidget::on_checkBox_visible_toggled(bool checked)
{
	if(gr){
		if(ui->radioButton->text().endsWith("mill", Qt::CaseInsensitive)){
			gr->setMillPathsVisible(checked);
		}else{
			gr->setVisible(checked);
		}
	}
}
