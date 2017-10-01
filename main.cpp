#include <QtWidgets/QApplication>
#include "copperfield.h"
#include "gerberreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	// Following lines are for bare metal testing:
	//GerberReader gr(QString("examples/dummy-Front.gtl"),QColor(Qt::white));
	// gr.testInterpolation(); // TODO 5: diese interpolation funktioniert noch nicht!!!
    // gr.initPerspectiveTransform();

    CopperField w;
    w.show();
    return a.exec();
}
