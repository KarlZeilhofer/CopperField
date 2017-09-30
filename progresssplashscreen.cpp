#include "progresssplashscreen.h"
#include "ui_progresssplashscreen.h"

ProgressSplashScreen::ProgressSplashScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressSplashScreen)
{
    ui->setupUi(this);
	ui->progressBar->setMaximum(1000);
}

ProgressSplashScreen::~ProgressSplashScreen()
{
    delete ui;
}

void ProgressSplashScreen::changeProgress(QString task, qreal progress) // from 0 to 1
{
	ui->label->setText(task);
	ui->progressBar->setValue(1000*progress);
}
