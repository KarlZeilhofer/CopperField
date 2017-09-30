#ifndef LAYERWIDGET_H
#define LAYERWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include "gerberreader.h"

namespace Ui {
    class LayerWidget;
}

class LayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LayerWidget(QWidget *parent = 0);
    ~LayerWidget();

	enum LayerType{NONE, BOT, BOT_MILL, TOP, TOP_MILL, CONTOUR, CONTOUR_MILL, DRILLS} activeLayer;
	static const LayerType FirstLayer=BOT;
	static const LayerType LastLayer=DRILLS;
	static QStringList LayerNames;

	void setActive();
	void setActive(GerberReader* grObj);

	void setLayerType(LayerType t);
	LayerType type() const {return layerType;}
	QRadioButton* radioButton();
	void setLayerName(QString name);

public:
	LayerType layerType;

private slots:
	void on_checkBox_visible_toggled(bool checked);

private:
    Ui::LayerWidget *ui;
	bool firstActivation;
	GerberReader* gr;
};

#endif // LAYERWIDGET_H
