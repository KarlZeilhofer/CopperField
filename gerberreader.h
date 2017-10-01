#ifndef GERBERREADER_H
#define GERBERREADER_H

#include "gerberaperture.h"
#include "gerberelement.h"
#include <QVector>
#include <QColor>
#include <QThread>
#include <gcodesettings.h>
#include <matrix.h>

class QString;
class QGraphicsScene;


class GerberReader: public QThread
{
	Q_OBJECT

public:
	GerberReader(QString fileName, QColor c);
	~GerberReader();

	void run();

	void setLayerColor(QColor c);
	QVector<GerberElement*> elements();
	bool exportGCode();
	QVector<QPolygonF> getMillingPolygons();
	void setVisible(bool flag);
	void setMillPathsVisible(bool flag);
	QVector<QGraphicsPathItem*> getMillingGraphicItems();
	qreal getLengthOfMillingPaths();

	void testInterpolation(); // biliniear


	void initPerspectiveTransform();
	QPointF perspectiveTransform(QPointF pCAD);

	void deleteMillingPolygons();



private:
	QVector<QPolygonF>* splitOutline(QPolygonF& p);
	qreal readNumber(QString* str, bool* ok); // returns the number, with that the string starts, and removes the corresponding characters from the string
	void buildNets();
	void buildNetsByPoints();
	bool isEdgePixel(QImage* im, int x, int y);
	qreal getLength(const QPointF& vector);
	QVector<QPolygonF> sortPaths(QVector<QPolygonF> input, bool spreadFirstItems);
	void calculateMillingPolygons(qreal offset);

	void loadZMap();

	qreal interpolateMap(QPointF xyPos);
	QVector<qreal> zMap; // matrix for saving the measured zValues (z_x1_y1, z_x2_y1, z_x3_y1, ..., z_x1_y2, z_x2_y2, z_x3_y2, ..., z_xN_yM)
	QVector<qreal> xVector; // store x coordinates
	QVector<qreal> yVector; // store y coordinates
	qreal step;

signals:
	void calculaltionProgressed(QString currentTask, qreal progress); // from 0 to 1

public:
	enum Mode{Draw_ON=1, Draw_OFF=2, Flash=3, Drill=4};

	GCodeSettings gCodeSettings;


private:
	QColor color;
	QColor colorLine;
	QColor colorFlash;
	QColor colorText;

	QString gFileName;

	QVector<QPolygonF> millingPolygons;
	QVector<QGraphicsPathItem*> millingItems;


	bool failed; // flag, if reading file failed
	int nLine; // current processed line in the textfile
	GerberAperture apertures[1000];
	GerberAperture drillTools[1000];
    QVector<int> definedApertureIDs;
    QVector<int> definedDrillToolIDs; // this list is needed, that we know, which tools are defined in the qvector
	int currentApertureID; // currently selected aperture (selected with G54)
	int currentDrillID; // currently selected drill diameter (selected with Txx)
	GerberAperture* curAp; // pointer to currently selected aperture (selected with G54)
	GerberAperture* curDrill; // pointer to currently selected aperture (selected with G54)
	int leftDigits, rightDigits; // number of digits of the coordinate numbers. are defined in the format-string
	qreal scale; // scale = 1/10^rightDigits
	qreal unitScale; // for inch: uintScale = 25.4, for mm unitScale = 1.0
	qreal yScale; // for mirroring about x-axis, due to different coordinate systems

	GerberElement* curElement;
	QPointF lastPoint; // last position, is needed for drawing lines (D1)
	bool finishedElement;

	bool hasDrills;
	bool hasMills;

	int nDrills; // number of drill points
	int nCoordinates;
	int nElements;
	bool outlineActive;
	QPolygonF* curOL; // current outline (goes with outlineActive (G36/G37)

	// for perspective Transformation:
	Matrix k;

public:
	QVector<GerberElement*> gElements; // all elements read from the gerber-file
	QVector<QVector<GerberElement*>*> nets; // list of element-lists, each element-list represents a electrical net
};

#endif // GERBERREADER_H
