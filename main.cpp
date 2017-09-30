#include <QtGui/QApplication>
#include "copperfield.h"
#include "gerberreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	GerberReader gr(QString("examples/dummy-Front.gtl"),QColor(Qt::white));
	// gr.testInterpolation(); // TODO: diese interpolation funktioniert noch nicht!!!
    // gr.initPerspectiveTransform();

    CopperField w;
    w.show();
    return a.exec();
}
