#ifndef DIALOGLAYERS_H
#define DIALOGLAYERS_H

#include <QDialog>
#include "layerwidget.h"
#include <QButtonGroup>
#include <layerwidget.h>

namespace Ui {
    class DialogLayers;
}

class DialogLayers : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLayers(QWidget *parent = 0);
    ~DialogLayers();


	void setActiveLayer(LayerWidget::LayerType layer);
	void setGerberReader(LayerWidget::LayerType layer, GerberReader* gr);

	LayerWidget::LayerType activeLayer();


private slots:


private:
    Ui::DialogLayers *ui;

	LayerWidget* layers[8];
	QButtonGroup bg;
};

#endif // DIALOGLAYERS_H
