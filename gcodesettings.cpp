#include "gcodesettings.h"
#include "ui_gcodesettings.h"
#include <QMessageBox>
#include <QDebug>

GCodeSettings::GCodeSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCodeSettings)
{
	qDebug() << "new GCodeSettings";

	ui->setupUi(this);

    ui->lineEdit_drillDepth->setText(QString::number(-2.1));
    ui->lineEdit_drillPlungeFeedrate->setText(QString::number(1.0));
	ui->lineEdit_millDiameter->setText(QString::number(0.25));
    ui->lineEdit_millFeedrate->setText(QString::number(5.0));
    ui->lineEdit_millPlungeFeedrate->setText(QString::number(2.0));
    ui->lineEdit_millZDepth->setText(QString::number(-0.1));
    ui->lineEdit_zClearance->setText(QString::number(1.0));
	updateValuesFromTextfields();
}

GCodeSettings::~GCodeSettings()
{
    delete ui;
}

void GCodeSettings::on_lineEdit_millDiameter_editingFinished()
{

}

void GCodeSettings::updateValuesFromTextfields()
{
	bool ok;
	bool error = false;
	qreal tempZClearance = ui->lineEdit_zClearance->text().toDouble(&ok); if(!ok){error = true;}

	qreal tempMillDiameter = ui->lineEdit_millDiameter->text().toDouble(&ok); if(!ok){error = true;}
	qreal tempMillZDepth = ui->lineEdit_millZDepth->text().toDouble(&ok); if(!ok){error = true;}
	qreal tempMillFeedrate = ui->lineEdit_millFeedrate->text().toDouble(&ok); if(!ok){error = true;}
	qreal tempMillPlungeFeedrate = ui->lineEdit_millPlungeFeedrate->text().toDouble(&ok); if(!ok){error = true;}

	qreal tempDrillDepth = ui->lineEdit_drillDepth->text().toDouble(&ok); if(!ok){error = true;}
	qreal tempDrillPlungeFeedrate = ui->lineEdit_drillPlungeFeedrate->text().toDouble(&ok); if(!ok){error = true;}

	if(error){
		QMessageBox::warning(this, "Error on reading values", "Using the old values");
		return;
	}

	if(tempMillZDepth>=0){
		int ret = QMessageBox::question(this, tr("Positive z-Value"), "You are milling with a positive z-Level!\n"
				  "Do you want to convert the z-Level to a negative one?", QMessageBox::Yes, QMessageBox::No);
		if(ret == QMessageBox::Yes){
			tempMillZDepth *= -1;
			ui->lineEdit_millZDepth->setText(QString::number(tempMillZDepth, 'g', 3));
		}
	}

	if(tempDrillDepth>=0){
		int ret = QMessageBox::question(this, tr("Positive z-Value"), "You are drilling to a positive z-Level!\n"
				  "Do you want to convert the z-Level to a negative one?", QMessageBox::Yes, QMessageBox::No);
		if(ret == QMessageBox::Yes){
			tempDrillDepth *= -1;
			ui->lineEdit_drillDepth->setText(QString::number(tempDrillDepth, 'g', 3));
		}
	}


	myZClearance = tempZClearance;
	myMirrorFlag = ui->checkBox_mirror->isChecked();

	myMillDiameter = tempMillDiameter;
    qDebug() << "updated myMillDiameter = " << myMillDiameter;

	myMillZDepth = tempMillZDepth;
	myMillFeedrate = tempMillFeedrate;
	myMillPlungeFeedrate = tempMillPlungeFeedrate;

	myDrillDepth = tempDrillDepth;
	myDrillPlungeFeedrate = tempDrillPlungeFeedrate;
}

void GCodeSettings::on_pushButton_clicked()
{
	hide();
	updateValuesFromTextfields();
	setResult(QDialog::Accepted);
}
