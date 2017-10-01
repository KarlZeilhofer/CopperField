#include "copperfield.h"

#include "gerberreader.h"
#include "gerberaperture.h"
#include "netsviewer.h"

#include <QTextStream>
#include <QMessageBox>
#include <QFile>

#include <QGraphicsPathItem>

#include <QtDebug>
#include <cmath>

#include <QGraphicsScene>
#include <QPainter>
#include <QFileDialog>
#include <QDate>
#include <QTime>
#include "matrix.h"

// this class represents a gerber layer!

// reads a gerber-file
// reads all it's appertures, and coordinates.
// all elements are stored in
//		QVector<GerberElement*> gElements; // all elements read from the gerber-file
// and all electrical-nets in
//		QVector<QVector<GerberElement*>*> nets; // list of element-lists, each element-list represents an electrical net
// Gerber-Lines with the Aperture D11 are interpreted as Text.
// TODO 4: allow other apertures to be defined as text by GUI

// use the function start() to calculate the milling polygons.

// implement useful layer-settings (for visible ON/OFF)

GerberReader::GerberReader(QString fileName, QColor c)
{
	bool brushOn=true;
	int alpha = 128;
	finishedElement = true;
	setLayerColor(c);

	gCodeSettings.setWindowTitle(fileName.split('\\').last());

	hasDrills = false;
	hasMills = false;

	gFileName = fileName;

	scale = 1;
	unitScale = 1; // default = mm
	yScale = -1; // adoption between monitor and cad coordinate system

	nCoordinates=0;
	nElements=0;
	outlineActive = false;

	nLine=0; // line number
	failed = false;
	bool ok; // useed for reading numbers from strings

	QFile f(fileName);
	if(!f.open(QFile::ReadOnly)){
		qDebug("cannot open file");
		return;
	}
	QTextStream stream(&f);
	QString line;

	while(!stream.atEnd() && !failed)
	{
		line = stream.readLine();
		nLine++;

		qDebug() << QString("Scanning line %1...").arg(nLine);

		// skip comments:
		if(line.startsWith("G04", Qt::CaseInsensitive))
		{
			// skip all other ifs
		}else if(line.startsWith("%FS", Qt::CaseInsensitive))
		{ // Formatspecification
			qDebug("Found Format Specification");
			line = line.mid(3); // remove %FS

			switch(line.at(0).toLatin1())
			{
			case 'L': // leading zeros are omitted
				// can be ignored
				break;
			case 'T': // trailing zeros are omitted
				// can be ignored
				break;
			default:
				qDebug("Error in L/T Format-Character");
				failed = true;
			}

			switch(line.at(1).toLatin1())
			{
			case 'A': // absolute format
				// TODO 4: interpret this format
				// absolute format is assumed by default
				break;
			case 'I': // incremental format
				// TODO 4: support Incermental Format
				qDebug() << "Error: Unsupported Incremental Number Format!";
				failed = true;
				break;
			default:
				qDebug("Error in A/I Format-Character");
				failed = true;
			}

			line = line.mid(2); // skip T/L and A/I chars

			if(line.at(0).toUpper() == 'X')
			{
				line = line.mid(1); // skip 'X'
				int temp = readNumber(&line, &ok);
				if(ok)
				{
					leftDigits = temp/10;
					rightDigits = temp%10;
					scale = 1.0/pow(10,rightDigits);
				}else{
					failed = true;
				}
			}else{
				qDebug("Error in Format String. Missing X");
				failed = true;
			}
		}else if(line.startsWith("%MO", Qt::CaseInsensitive))
		{
			qDebug("Found Unit Definition");
			line = line.mid(3); // remove %MO

			if(line.startsWith("IN")){
				qDebug("Using Inch");
				unitScale = 25.4;
			}else if(line.startsWith("MM")){
				qDebug("Using Millimeters");
				unitScale = 1.0;
			}
		}else if(line.startsWith("%ADD", Qt::CaseInsensitive))
		{
			qDebug("Found Aperture Definition");

			GerberAperture A;
			line = line.mid(4); // remove %ADD


			// READ APERTURE-ID
			qDebug("reading Aperture ID...");
			A.id = readNumber(&line, &ok);
			if(!ok)
			{
				failed = true;
				break;
			}else{
				qDebug(QString("ID = %1").arg(A.id).toLatin1());
			}

			// READ APERTURE TYPE
			qDebug("reading Aperture Type...");
			switch(line.at(0).toLatin1())
			{
			case 'c':
			case 'C':
				A.type = GerberAperture::Circle;
				qDebug("Type = Circle");
				break;
			case 'o':
			case 'O':
				A.type = GerberAperture::Oval;
				qDebug("Type = Oval");
				break;
			case 'r':
			case 'R':
				A.type = GerberAperture::Rect;
				qDebug("Type = Rect");
				break;
			default:
				QMessageBox::warning(0, "Error on reading file",
									 QString("Invalid Aperture Type ('%1') in line %2.").arg(line.at(0)).arg(nLine));
				failed = true;
				break;
			}
			line = line.mid(1); // delete type character from string

			// SKIP COLON (,)
			if(line.at(0)==',')
			{
				line = line.mid(1); // delete colon from string
			}else
			{
				qDebug("Colon is missing");
				failed=true;
			}

			// READ FIRST ARGUMENT (sizeX)
			qDebug("reading sizeX...");
			A.sizeX = readNumber(&line, &ok)*unitScale;
			if(!ok)
			{
				failed = true;
			}else{
				qDebug(QString("sizeX = %1").arg(A.sizeX).toLatin1());
			}

			if(line.at(0)=='X' || line.at(0)=='x') // if rect or oval
			{
				qDebug("found X");
				line = line.mid(1); // skip 'X'

				// READ sizeY
				qDebug("reading sizeY...");
				A.sizeY = readNumber(&line, &ok)*unitScale;
				if(!ok)
				{
					failed = true;
				}else{
					qDebug(QString("sizeY = %1").arg(A.sizeY).toLatin1());
				}
			}else{
				qDebug("no X found");
				A.sizeY=A.sizeX; //
			}

			// FINISHED READING APERTURE DEFINITION!
			apertures[A.id] = A;
			definedApertureIDs.append(A.id);
		}
		else if(line.startsWith("T", Qt::CaseInsensitive)) // distinguish Drill definition and drill switch
		{
			qDebug("Found Drill Definition/Switch");
			nDrills++;

			GerberAperture A;
			line = line.mid(1); // remove T


			// READ APERTURE-ID
			qDebug("reading Aperture ID...");
			A.id = readNumber(&line, &ok);
			if(!ok)
			{
				failed = true;
				break;
			}else{
				qDebug(QString("ID = %1").arg(A.id).toLatin1());
			}

			if(line.isEmpty()){
				// SET DRILL TOOL
				qDebug("Set current Drill Tool...");
				currentDrillID = A.id;
				curDrill = &drillTools[currentDrillID];
			}else{
				// READ DRILL TYPE
				qDebug("reading Drill Type...");
				switch(line.at(0).toLatin1())
				{
				case 'c':
				case 'C':
					A.type = GerberAperture::Circle;
					qDebug("Type = Circle");
					break;
				default:
					QMessageBox::warning(0, "Error on reading file",
										 QString("Invalid Drill Type ('%1') in line %2.").arg(line.at(0)).arg(nLine));
					failed = true;
					break;
				}

				line = line.mid(1); // remove C

				// READ ARGUMENT (dimeter)
				qDebug("reading diameter...");
				A.sizeX = readNumber(&line, &ok)*unitScale;
				if(!ok)
				{
					failed = true;
				}else{
					qDebug(QString("diameter = %1").arg(A.sizeX).toLatin1());
				}

				// FINISHED READING DRILL-TOOL DEFINITION!
				drillTools[A.id] = A;

				definedDrillToolIDs.append(A.id);
			}
		}
		else if(line.startsWith("G54D", Qt::CaseInsensitive))
		{ // Aperture change
			qDebug("Found G54 (Change Apperture)");
			line = line.mid(4); // remove G54
			currentApertureID = readNumber(&line, &ok);
			if(!ok)
			{
				failed = true;
			}else{
				qDebug(QString("Current Aperture ID = %1").arg(currentApertureID).toLatin1());
				finishedElement = true;
			}

			if(currentApertureID>=0 && currentApertureID<1000)
			{
				curAp = &(apertures[currentApertureID]);
			}else{
				qDebug(QString("Apperture ID is out of range! (line %1)").arg(nLine).toLatin1());
			}
		}
		else if(line.startsWith("D", Qt::CaseInsensitive)) // new aperture change format
		{ // Aperture change
			qDebug("Found D (Change Apperture)");
			line = line.mid(1); // remove G54
			currentApertureID = readNumber(&line, &ok);
			if(!ok)
			{
				failed = true;
			}else{
				qDebug(QString("Current Aperture ID = %1").arg(currentApertureID).toLatin1());
				finishedElement = true;
			}

			if(currentApertureID>=0 && currentApertureID<1000)
			{
				curAp = &(apertures[currentApertureID]);
			}else{
				qDebug(QString("Apperture ID is out of range! (line %1)").arg(nLine).toLatin1());
			}
		}
		else if(line.startsWith("X", Qt::CaseInsensitive))
		{ // Coordinates
			nCoordinates++;
			qDebug("Found Coordinate");
			line = line.mid(1); // remove "X" from string

			qreal x,y;
			enum Mode d;
			// Read x-Coordinate
			x = readNumber(&line, &ok)*scale*unitScale;
			if(ok)
			{
				qDebug(QString("X = %1").arg(x).toLatin1());
			}else{
				failed = true;
				break;
			}

			// Read y-Coordinate
			if(line.at(0) != 'Y')
			{
				failed = true;
				qDebug(QString("Y character is missing in coordinate in line %1").arg(nLine).toLatin1());
				break;
			}
			line = line.mid(1); // skip Y
			y = readNumber(&line, &ok)*scale*unitScale*yScale;
			if(ok)
			{
				qDebug(QString("Y = %1").arg(y).toLatin1());
			}else{
				failed = true;
				break;
			}

			// Read Command
			if(line.startsWith("D0")) // Photo-command
			{
				line = line.mid(2); // skip 'D0'
				d = (GerberReader::Mode)((int)(readNumber(&line, &ok)));
				if(ok)
				{
					qDebug(QString("Y = %1").arg(y).toLatin1());
				}else{
					failed = true;
					break;
				}
			}else if(line.isEmpty()){ // drill command
				qDebug("It is a Drill Coordinate");
				d = Drill;
			}else{
				failed = true;
				qDebug(QString("Error in coordinate in line %1").arg(nLine).toLatin1());
				break;
			}


			QPainterPath p;

			switch(d)
			{
			case GerberReader::Draw_ON:
			{
				hasMills = true;

				if(outlineActive)
				{
					curOL->append(QPointF(x,y));
				}else{
					if(finishedElement){
						finishedElement = false;
						curElement = new GerberElement(*curAp);
						curElement->elementType = GerberElement::Polygon;
						if(currentApertureID == 11){ // TODO 2: set this number in the gui!
							curElement->color = colorText;
						}else{
							curElement->color = colorLine;
						}
						curElement->append(lastPoint);
						gElements.append(curElement);
					}
					curElement->append(QPointF(x,y)); // add current point

					nElements++;
					qDebug(QString("Draw from (%1/%2) to (%3,%4) with D%5").arg(lastPoint.x()).arg(lastPoint.y()).arg(x).arg(y).arg(currentApertureID).toLatin1());
				}
			}break;
			case GerberReader::Draw_OFF:
			{
				qDebug(QString("Move to (%1/%2)").arg(x).arg(y).toLatin1());
				if(outlineActive)
				{
					if(curOL->size()>0)
					{
						qWarning("A MoveTo is not supported in an outline!");
					}else{
						curOL->append(QPointF(x,y)); // set first point of outline
					}
				}else{
					finishedElement = true;
				}
			}break;
			case GerberReader::Flash:
			{
				hasMills = true;

				curElement = new GerberElement(*curAp);
				curElement->elementType = GerberElement::Flash;
				curElement->color = colorFlash;
				curElement->append(QPointF(x,y)); // add current point
				gElements.append(curElement);
				finishedElement = true;

				nElements++;
				qDebug(QString("Flash at (%1/%2) with D%3").arg(x).arg(y).arg(currentApertureID).toLatin1());
			}break;
			case GerberReader::Drill:
			{
				hasDrills = true;

				curElement = new GerberElement(*curDrill);
				curElement->elementType = GerberElement::Drill;
				curElement->color = colorFlash;
				curElement->append(QPointF(x,y)); // add current point
				gElements.append(curElement);
				finishedElement = true;

				nElements++;
				qDebug(QString("Drill at (%1/%2) with T%3").arg(x).arg(y).arg(currentDrillID).toLatin1());

			}break;
			} // end switch()

			lastPoint = QPointF(x,y); // save this point
		}else if(line.startsWith("G36", Qt::CaseInsensitive))
		{
			qDebug(QString("Start Outline").toLatin1());
			outlineActive = true;
			curOL = new QPolygonF();			
		}else if(line.startsWith("G37", Qt::CaseInsensitive))
		{
			qDebug(QString("End Outline").toLatin1());
			outlineActive = false;
			if(!curOL->isClosed()){
				qWarning("Outline isn't closed!");
			}

			QVector<QPolygonF>* polygons = splitOutline(*curOL);

			for(int n=0; n<polygons->size(); n++){
				curElement = new GerberElement(*curAp);
				curElement->elementType = GerberElement::Outline;
				curElement->color = colorLine;
				// copy points to curElement
				for(int p=0; p<polygons->at(n).size(); p++){
					curElement->append(polygons->at(n).at(p));
				}
				gElements.append(curElement);
			}
			finishedElement = true;

			qDebug(QString("Splitted the Outline into %1 Polygons").arg(polygons->size()).toLatin1());

		}else if(line.startsWith("M02", Qt::CaseInsensitive))
		{
			qDebug(QString("End of File").toLatin1());
		}else if(line.startsWith("FMAT,2", Qt::CaseInsensitive))
		{
			qDebug("Drill File, using format 3.3");
			leftDigits = 3;
			rightDigits = 3;
			scale = 1.0/pow(10,rightDigits);
		}else {
			qWarning(QString("Unsupported Command in line %1: '%2'").arg(nLine).arg(line).toLatin1());
		}
	}

	if(!failed)
	{
		qDebug(QString("Finished (%1 Apertures, %2 Elements, %3 Coordinates)").arg(definedApertureIDs.size()).arg(nElements).arg(nCoordinates).toLatin1());

		// TODO 4: remove dublicate lines:
		buildNetsByPoints(); // only copper lines and pads
	}

	gCodeSettings.show();
}

// TODO 0: app crashes on delete!!
// kann nicht mehr nachvollzogen werden...
GerberReader::~GerberReader()
{
	// delete all allocated objects:
	for(int n=0; n<nets.size(); n++){
		QVector<GerberElement*>* net = nets.at(n);
		delete(net);
	}
}

qreal GerberReader::readNumber(QString* str, bool* ok)
{
	// find next non-digit
	int x=0;
	while(x<str->length() &&( str->at(x).isDigit() || str->at(x)=='.' || str->at(x)=='-' || str->at(x)=='+')){
		x++;
	}

	// READ number
	QString numStr = str->left(x);
	qDebug(QString("reading number from String = %1").arg(numStr).toLatin1());
	qreal number = numStr.toDouble(ok);
	if(!(*ok))
	{
		QMessageBox::warning(0, "Error on reading file", QString("Cannot read number (string = \"%1\") in line %2.").arg(numStr).arg(nLine));
	}

	*str = str->mid(numStr.length()); // remove number from string

	return number;
}

// split a complex outline into separate polygons (remove helper-edges)
// instructions:
// check each line against every other line. if 2 lines are
// identical (identical start/end-points), then split the
// polygon up into 2 separate polygons.
// do this recursively until no identical lines are found any more.
QVector<QPolygonF>* GerberReader::splitOutline(QPolygonF& p)
{
	if(!p.isClosed()){
		qWarning("Cannot split unclosed outline!");
		return 0;
	}

	QVector<QPolygonF>* pList = new QVector<QPolygonF>;

	// remove this, this skips the splitting algorithm (just for testing)
//	pList->append(p);
//	return pList;

	QPolygonF p1;
	QPolygonF p2;
	bool splitted = false;

	for(int n=0; !splitted && n<p.size()-3; n++){
		for(int m=n+2; !splitted && m<p.size()-1; m++){
			if(p.at(n) == p.at(m+1) && p.at(n+1) == p.at(m)){ // if identical lines found
				// then split the polygon into two

				// copy first part of first closed path to p1:
				for(int i=0; i<=n; i++){
					p1.append(p.at(i));
				}
				// copy second part of first closed path to p1:
				for(int i=m+2; i<p.size(); i++){
					p1.append(p.at(i));
				}

				// copy first closed path to p1:
				for(int i=n+1; i<=m; i++){
					p2.append(p.at(i));
				}


				QVector<QPolygonF>* ret1 = splitOutline(p1);
				QVector<QPolygonF>* ret2 = splitOutline(p2);

				for(int n=0; n<ret1->size(); n++){
					pList->append(ret1->at(n));
				}
				for(int n=0; n<ret2->size(); n++){
					pList->append(ret2->at(n));
				}
				delete(ret1);
				delete(ret2);

				splitted = true;
			}
		}
	}

	if(pList->isEmpty()){ // if no splitt has happended
		pList->append(p); // just return the original polygon
	}

	return pList;
}


// build nets with start/end/flash-Points
void GerberReader::buildNetsByPoints()
{
	QVector<GerberElement*> elements;

	// filter out the copper items:
	for(int n=0; n<gElements.size(); n++){
		if(gElements.at(n)->elementType == GerberElement::Polygon ||
				gElements.at(n)->elementType == GerberElement::Flash) // todo: expand it to outlines if needed.
			if(gElements.at(n)->aperture.id != 11){ // TODO 2: set text aperture in gui
				elements.append(gElements.at(n));
			}
	}

	int numElements = elements.size();
	QVector<GerberElement*> *baseNet;

	qDebug("Start building nets...");

	int baseCounter=0;
	int netCounter = 0;


	// make a temp item
	// make the first item in elements to the temp-item
	// remove this item from elements-list
	// iterate over all items
	// check for common points
	// if overlapping, remove the itme from the elements-list, fuse them
	// start iterating over elements again.
	// do until no more overlaping elements are found.
	// add the temp-item to the fused-list.


	while(!elements.isEmpty()){
		baseCounter++;
		netCounter = 0;

		qDebug(QString("baseCounter = %1").arg(baseCounter).toLatin1());

		baseNet = new QVector<GerberElement*>; // make new net,
		baseNet->append(elements.first());
		nets.append(baseNet);  // and put the first item from elements into it.
		elements.remove(0); // remove this item from elements-list

//		QRectF r = baseItem->sceneBoundingRect();
//		qDebug(QString("baseItem.boundingRect = (%1,%2,%3,%4)").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).toLatin1());

		int n=0;
		while(n<elements.size()){ // for all remaining elements
			GerberElement* testingItem = elements.at(n); // just a synonym for elements.at(n)

			//r = testingItem.boundingRect();
			//qDebug(QString("elements.at(n)->shape().boundingRect = (%1,%2,%3,%4)").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).toLatin1());

			// check if baseNet collides with testingItem:
			bool collides = false;
			for(int k=0; k<baseNet->size() && !collides; k++){ // for all elements in the base-net until collision
				// check, if any point is the same as in the testingItem:
				for(int pb=0; pb<baseNet->at(k)->size(); pb++){ // for all points in the baseNet-Element
					if(testingItem->contains(baseNet->at(k)->at(pb))){
						collides = true;
						break;
					}
				}
			}
			if(collides){ // then fuse testingItem to the baseItem
				netCounter++;
				qDebug(QString("netCounter = %1.%2 (remaining elements: %3)").arg(baseCounter).arg(netCounter).arg(elements.size()).toLatin1());
//				r = testingItem->sceneBoundingRect();
//				qDebug(QString("testingItem.boundingRect = (%1,%2,%3,%4)").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).toLatin1());

				baseNet->append(testingItem);
				elements.remove(n); // remove testingItem

				n = 0; // reset for-loop // TODO 4: is here a more efficient algorithm possible?? i think so!
			}else{
				n++;
			}
		}// end for(elements)
	}

	//cleanOutlinePathNets(); // TODO 4 cleanOutlinePathNets

	qDebug(QString("Fused %1 elements to %2 different nets!").arg(numElements).arg(nets.size()).toLatin1());

	// TODO 1: make netsViewer threadsave! (was ist hier genau gemeint?
	//CopperField::app->netsViewer->setNets(nets);
}


void GerberReader::setLayerColor(QColor c)
{
	color = c;

	// TODO 4: set different colors
	colorLine = c;
	colorFlash = c;
	colorText = c;
}

QVector<GerberElement*> GerberReader::elements()
{
	return gElements;
}


/*
	this is internally called by run()

	algorithm:
	 for all nets:
	 put all items into a separate QGraphicsScene and render it into an QImage.
		(leave space for the contour-enlargement)

	 walk through all edge-pixels,
		Do the Dilation (pixelwise)

	 convert the new edge-pixels to a closed polygon

	 simplify the polygon:
		combine colinear segments
		reduce the number of vertices (min edge-length)

	 transform the polygons into the original scene-coordinates
	 add the polygons to millingPolygons

	 TODO 5: make use of multiple CPUs by paralleling this task
  */
void GerberReader::calculateMillingPolygons(qreal offset)
{
	millingPolygons.clear();
	bool dbg=true;

	QVector<GerberElement*>* net; // currently processed net
//	QVector<QPolygonF*>* polygons = new QVector<QPolygonF*>; // to be calculated!
//	QVector<QPolygonF> subpolys;
//	const qreal f=10; // factor, which should correspond to the grade of details
	const qreal resolution = 100; // pixels per mm

	const unsigned int black = QColor(Qt::black).rgb();
	const unsigned int white = QColor(Qt::white).rgb();

//	copperPolygons = new QVector<QGraphicsPolygonItem*>;
//	int numEdges = 0;
//	int numPolygons = 0;

	qreal progress = 0;

	for(int n=0; n<nets.size(); n++){ // for all nets
		net = nets.at(n);

		QGraphicsScene s; // temporary scene for rendering
		GerberElement* element; // element

		for(int e=0; e<net->size(); e++){ // for all elements of the net
			element = net->at(e);
			QGraphicsPathItem* tempItem;
			tempItem = new QGraphicsPathItem(element->getItem()->path());

			QPen pen;
			pen.setColor(white);
			pen.setWidth(0);

			tempItem->setPen(pen);
			tempItem->setBrush(QBrush(white));
			s.addItem(tempItem); // TODO 4: Speicher: this heap-objects should be deleted at the end of this function
				// becaus they will be childed by the scene s.
		}

		QRectF oR = s.sceneRect(); // original rect
		QRectF eR = QRectF(oR.x()-offset, oR.y()-offset, oR.width()+2.0*offset, oR.height()+2.0*offset); // extended rectangle
		QRectF eRP = QRectF(0, 0, eR.width()*resolution, eR.height()*resolution); // extended rectangle in pixels

		QImage image((int)(eRP.width() + 2),
					 (int)(eRP.height() + 2), QImage::Format_RGB32);

		image.fill(black); // clear image to remove artefact pixels

		QPainter painter(&image);

		s.render(&painter, eRP, eR); // TODO 0: there are artefacts in the images: muss geprüft werden!

		//convert to black/white:
		QImage imBW(image.size(), QImage::Format_RGB32);
		QRgb bg = image.pixel(0,0); // get background color

		for(int x=0; x<image.size().width(); x++){
			for(int y=0; y<image.size().height(); y++){
				if(image.pixel(x,y) == bg){ // if background
					imBW.setPixel(x,y,black);
				}else{
					imBW.setPixel(x,y,white);
				}
			}
		}

		if(dbg)
			imBW.save(QString("image_%1_A_net.bmp").arg(n)); // just for debugging

		QImage imDil(imBW); // dilated image
		QPainter painter2(&imDil);

		painter2.setBrush(QBrush(Qt::white));

		QPen pen;
		pen.setColor(white);
		pen.setWidth(0);
		painter2.setPen(pen);

		int rP = offset*resolution; // radius in pixels

		for(int x=1; x<image.size().width()-1; x++){ // for all x exept border pixels
			for(int y=1; y<image.size().height()-1; y++){ // for all y exept border pixels
				if(imBW.pixel(x,y) == white &&
						isEdgePixel(&imBW, x,y)){ // if it is a foreground edge-pixel
					painter2.drawEllipse(QPoint(x,y), rP, rP);
				}
			}
		}

		if(dbg)
			imDil.save(QString("image_%1_B_dilated.bmp").arg(n)); // just for debugging

		// Get Edge-Pixels only!
		QImage imDilEd(imBW); // dilated edge image
		imDilEd.fill(black); // clear new image

		for(int x=0; x<image.size().width(); x++){ // for all x pixels
			for(int y=0; y<image.size().height(); y++){ // for all y pixels
				if(imDil.pixel(x,y) == white &&
						isEdgePixel(&imDil, x,y)){ // if it is a foreground edge-pixel
					imDilEd.setPixel(x,y,white);
				}
			}
		}

		if(dbg)
			imDilEd.save(QString("image_%1_C_edge.bmp").arg(n)); // just for debugging



		// Get Polygons:
		for(int x=0; x<image.size().width(); x++){ // for all x pixels
			for(int y=0; y<image.size().height(); y++){ // for all y pixels
				if(imDilEd.pixel(x,y) == white){ // start polygon here
					//imDilEd.setPixel(x,y,black); // dont clear first visited pixel, it is the end
					int xStart = x;
					int yStart = y;
					QPolygonF poly;
					poly.append(QPointF(x,y));

					do{
						// find neighbour-pixel
						if(x!=image.width()-1 && imDilEd.pixel(x+1,y) == white){
							x = x+1; y=y;
						}else if(x!=0 && imDilEd.pixel(x-1,y) == white){
							x = x-1; y=y;
						}else if(y!=image.height()-1 && imDilEd.pixel(x,y+1) == white){
							x = x; y=y+1;
						}else if(y!=0 && imDilEd.pixel(x,y-1) == white){
							x = x; y=y-1;
						}else if(x!=image.width()-1 && y!=image.height()-1 && imDilEd.pixel(x+1,y+1) == white){
							x = x+1; y=y+1;
						}else if(x!=image.width()-1 && y!=0 && imDilEd.pixel(x+1,y-1) == white){
							x = x+1; y=y-1;
						}else if(y!=image.height()-1 && x!=0 && imDilEd.pixel(x-1,y+1) == white){
							x = x-1; y=y+1;
						}else if(x!=0 && y!=0 && imDilEd.pixel(x-1,y-1) == white){
							x = x-1; y=y-1;
						}else{
							qDebug("found non-closed edge-path! Force close");
							x=xStart; y=yStart;
						}

						poly.append(QPointF(x,y));
						imDilEd.setPixel(x,y,black); // clear visited pixel
					}while(!(x==xStart && y==yStart));


					//#### transform coordinates back into the gerber-drawing ####

					// correct the initial image translation (offset):
					poly.translate(-(offset*resolution), -(offset*resolution));
					// scale the polygon:
					for(int n=0; n<poly.size(); n++){
						poly.replace(n, poly.at(n)/resolution);
					}
					// translate the polygon back in the scene coordinate:
					poly.translate(oR.x(), oR.y());

					// #### simplify polygon: ####
					// clean polygon from lines with very short length
					for(int n=0; n<poly.size()-1; n++)
					{
						QPointF v = poly.at(n+1)-poly.at(n);
						qreal LIMIT = offset; // TODO 3: make the limit dynamic!!!
						if(getLength(v) < LIMIT)
						{
							poly.remove(n+1, 1);
							n--;
						}
					}

					millingPolygons.append(poly);
				}
			} // end for all y-pixels
		} // end for all x-pixels

		progress = (qreal)n/nets.size();
		emit calculaltionProgressed("Offsetting by Dilation", progress);

	} // end for all nets


	// TODO 1: Clean the polygons from colinear segments!
	// DON'T use this on zMap correction!
//	progress = 0;
//	for(int mp=0; mp<millingPolygons.size(); mp++){ // for all polygons
//		QPolygonF poly = millingPolygons.at(mp);
//		//qDebug(QString("Polygon[%1].size() = %2, before cleaning").arg(mp).arg(poly.size()).toLatin1());
//		for(int v=0; v<poly.size()-2; v++){ // for all vertices
//			QPointF d1 = poly.at(v+1)-poly.at(v); // first line
//			QPointF d2 = poly.at(v+2)-poly.at(v+1); // second line

//			// this lines are colinear, when the crossproduct is zero
//			// and they are in the same direction, when the scalar pruduct is positive

//			qreal e = 1e-5; // epsilon about zero.  TODO 3: make this limit dynamic!
//			if((fabs(d1.y()*d2.x() - d1.x()*d2.y()) < e) && ((d1.x()*d2.x() + d1.y()*d2.y()) > 0)){
//				poly.remove(v+1); // remove middle point.
//				v--; // compensate the for-loop v++
//			}
//		}
//		millingPolygons.replace(mp, poly);
//		//qDebug(QString("Polygon[%1].size() = %2, after cleaning").arg(mp).arg(poly.size()).toLatin1());

//		progress = (qreal)mp/millingPolygons.size();
//		emit calculaltionProgressed("Removing colinear Segments", progress);
//	}

	// Add milling Paths of the text-elements:
	for(int n=0; n<gElements.size(); n++){
		if(gElements.at(n)->aperture.id==11 && gElements.at(n)->elementType!=GerberElement::Drill){
			millingPolygons.append(gElements.at(n)->polygon());
		}

		progress = (qreal)n/gElements.size();
		emit calculaltionProgressed("Adding Text Elements", progress);
	}

	millingPolygons = sortPaths(millingPolygons, true);

	getLengthOfMillingPaths();
}

QVector<QPolygonF> GerberReader::getMillingPolygons()
{
	if(millingPolygons.size() == 0){
		calculateMillingPolygons(gCodeSettings.millDiameter()/2);
		qDebug("using default cutter diameter of 0.25mm");
	}
	return millingPolygons;
}


// the output can be mirrored about the y-axis
// --> invert all x-values
bool GerberReader::exportGCode() // tODO: remove unsused parameter
{
	bool mirror = gCodeSettings.mirror();

	bool doPerspectiveTransform = false; // TODO 5: set this flag in GUI

	qreal xMirrorScale=1;
	if(gCodeSettings.mirror()){
		xMirrorScale = -1;
	}

	if(hasMills){

		// load zMap,xVector,yVector
		// qDebug("using zMap correction!");
		// loadZMap(); // TODO 4: use Z-Map Corrections again, write GUI elements for it!

		qreal idealZ = gCodeSettings.millZDepth();


		QString millFileName = gFileName + ".mill.ngc";
		qDebug("exporting to " + millFileName.toLatin1());
		QFile file(millFileName);
		file.open(QFile::WriteOnly);

		// use
		//		file.write(QString("Hello World").toLatin1());
		// for writing to the file.

		// get all this informations...
		file.write(QString("(G-Code for Milling a PCB)\n").toLatin1());
		file.write(QString("(Generated with CopperField)\n").toLatin1());
		file.write(QString("(Date: %1    Time: %2)\n").
				   arg(QDate::currentDate().toString("dd.MM.yyyy")).
					   arg(QTime::currentTime().toString("HH:mm:ss")).toLatin1());
		file.write("\n");
		file.write("(All units in Millimeters)\n");
		file.write("\n");
		file.write(QString("(Cutter Diameter: %1 mm)\n").
				   arg(gCodeSettings.millDiameter()).toLatin1());
		file.write(QString("(Cutter z-Depth: %1 mm)\n").
				   arg(idealZ).toLatin1());
		file.write(QString("(Cutter z-Clearance: %1 mm)\n").
				   arg(gCodeSettings.zClearance()).toLatin1());
		file.write(QString("(Mill Feedrate: %1 mm/s)\n").
				   arg(gCodeSettings.millFeedrate()).toLatin1());
		file.write(QString("(Plunge Feedrate: %1 mm/s)\n").
				   arg(gCodeSettings.millPlungeFeedrate()).toLatin1());
		file.write("\n");

		for(int n=0; n<millingPolygons.size(); n++){
			QPolygonF p = millingPolygons.at(n);
			// get compensation from zMap;
			qreal mapZLevel = interpolateMap(QPointF(p.first().x()*xMirrorScale, p.first().y()*yScale)); // don't forgett to mirror coordinates

			file.write("\n\n");
			file.write(QString("G0 x%1 y%2\n").
					   arg(QString::number(p.at(0).x()*xMirrorScale, 'f', 4)).
					   arg(QString::number(yScale * p.at(0).y(), 'f', 4)).toLatin1()); // goto first point of polygon

			file.write(QString("G0 z%1\n").arg(QString::number(0 + mapZLevel, 'f', 4)).toLatin1()); // fast down to plane
			file.write(QString("F%1\n").arg(QString::number(gCodeSettings.millPlungeFeedrate()*60, 'f', 4)).toLatin1()); // set plunge feed rate in mm/min


			file.write(QString("G1 z%1\n").arg(QString::number(idealZ + mapZLevel, 'f', 4)).toLatin1()); // plunge slowly

			// mill:
			file.write(QString("F%1\n").arg(QString::number(gCodeSettings.millFeedrate()*60, 'f', 4)).toLatin1()); // set mill feed rate in mm/min
			for(int v=1; v<p.size(); v++){
				mapZLevel = interpolateMap(QPointF(p.at(v).x()*xMirrorScale, p.at(v).y()*yScale));
				file.write(QString("G1 x%1 y%2 z%3\n").
						   arg(QString::number(p.at(v).x()*xMirrorScale, 'f', 4)).
						   arg(QString::number(yScale * p.at(v).y(), 'f', 4)).
						   arg(QString::number(idealZ+mapZLevel, 'f', 4)).toLatin1()); // mill slowly to current point
			}

			// goto save z:
			file.write(QString("G0 z%1\n").arg(QString::number(gCodeSettings.zClearance(), 'f', 4)).toLatin1()); // goto save z
		}

		file.write("\n");
		file.write("\n");

		file.write("(End of File)\n");
		file.write("M2"); // end of file

		file.flush();
		file.close();
	}


	// generate separate drill-file for each diameter
	if(hasDrills){

		if(doPerspectiveTransform){
			initPerspectiveTransform();
		}

		for(int T=1; T<=definedDrillToolIDs.size(); T++){ // for all drill-tools
			qreal drillDiameter = drillTools[T].sizeX;

			QString drillFileName = gFileName + QString(".drill_T%1_").arg(T) + QString::number(drillDiameter, 'f', 2) + "mm.ngc";
			qDebug("exporting " + drillFileName.toLatin1());
			QFile file(drillFileName);
			file.open(QFile::WriteOnly);

			file.write(QString("(G-Code for Drilling a PCB)\n").toLatin1());
			file.write(QString("(Generated with CopperField)\n").toLatin1());
			file.write(QString("(Date: %1    Time: %2)\n").
					   arg(QDate::currentDate().toString("dd.MM.yyyy")).
						   arg(QTime::currentTime().toString("HH:mm:ss")).toLatin1());
			file.write("\n");
			file.write("(All units in Millimeters)\n");
			file.write("\n");
			file.write(QString("(Drill Diameter: %1 mm)\n").
					   arg(drillDiameter).toLatin1());
			file.write(QString("(Drill z-Depth: %1 mm)\n").
					   arg(gCodeSettings.drillDepth()).toLatin1());
			file.write(QString("(Cutter z-Clearance: %1 mm)\n").
					   arg(gCodeSettings.zClearance()).toLatin1());
			file.write(QString("(Plunge Feedrate: %1 mm/s)\n").
					   arg(gCodeSettings.drillPlungeFeedrate()).toLatin1());
			if(doPerspectiveTransform)
				file.write(QString("(Coordinates are Perspective-Transformed)\n").toLatin1());
			file.write("\n");
			file.write(QString("G0 z%1\n").arg(gCodeSettings.zClearance()).toLatin1()); // goto save z

			QVector<QPolygonF> pointsList;
			for(int n=0; n<gElements.size(); n++){ // for all drill points with tool Tx
				GerberElement p = *(gElements.at(n));

				if(p.elementType == GerberElement::Drill && p.aperture.id == T){
					QPolygonF tempPoly;
					tempPoly.append(p.first());
					pointsList.append(tempPoly);
				}
			}
			QVector<QPolygonF> pointsListSorted = sortPaths(pointsList, false);

			for(int n=0; n<pointsListSorted.size(); n++)
			{
				QPolygonF p = pointsListSorted.at(n);
				if(doPerspectiveTransform){
					QPointF pCad = QPointF(p.first().x()*xMirrorScale, p.first().y()*yScale);
					QPointF pCnc = perspectiveTransform(pCad);
					p.replace(0, QPointF(pCnc.x()/xMirrorScale, pCnc.y()/yScale));
				}

				file.write("\n\n");
				file.write(QString("G0 x%1 y%2\n").
						   arg(p.at(0).x()*xMirrorScale).
						   arg(yScale * p.at(0).y()).toLatin1()); // goto drill point

				file.write(QString("G0 z0.000\n").toLatin1()); // fast down to plane
				file.write(QString("F%1\n").arg(gCodeSettings.drillPlungeFeedrate()*60).toLatin1()); // set plunge feed rate in mm/min
				file.write(QString("G1 z%1\n").arg(gCodeSettings.drillDepth()).toLatin1()); // plunge slowly

				// goto save z:
				file.write(QString("G0 z%1\n").arg(gCodeSettings.zClearance()).toLatin1()); // goto save z

			}

			file.write("\n");
			file.write("\n");

			file.write("(End of File)\n");
			file.write("M2"); // end of file

			file.flush();
			file.close();
		}
	}

	return true;
}


// returns true, if the pixel pointed to by (x,y) has a 4-neighbour
// pixel of different color.
// it is assumed, that the pixel isnt't on the border of the image

// Example for (C)enter and (E)dge-pixels:
//
//	 EEEE
//	ECCCCE
//	ECCCCCEEE
//	 ECCCCCCE
//	ECCCCCCCEE
//	EEEEEEEE
//
bool GerberReader::isEdgePixel(QImage* im, int x, int y)
{
	unsigned int c = im->pixel(x,y);

	if(x==0 || y==0 || x==im->width()-1 || y==im->height()-1)
		return true;

	if(im->pixel(x,y-1) != c) return true; // 2-neighbour
	if(im->pixel(x,y+1) != c) return true; // 8-neighbour
	if(im->pixel(x-1,y) != c) return true; // 4-neighbour
	if(im->pixel(x+1,y) != c) return true; // 6-neighbour

	return false;
}

qreal GerberReader::getLength(const QPointF& vector)
{
	return (qreal)(sqrt(pow(vector.x(),2) + pow(vector.y(),2)));
}

void GerberReader::setVisible(bool flag)
{
	for(int n=0; n<gElements.size(); n++){
		gElements.at(n)->setVisible(flag);
	}
}

QVector<QGraphicsPathItem*> GerberReader::getMillingGraphicItems()
{
	qreal millDiameter = gCodeSettings.millDiameter();

	if(millingPolygons.size()>0 && millingItems.size()==0){
		millingItems.clear();
		for(int p=0; p<millingPolygons.size(); p++){
			QPainterPath path;
			path.addPolygon(millingPolygons.at(p));
			QGraphicsPathItem* item = new QGraphicsPathItem(path);

			QColor negative;
			negative.setRed(255-color.red());
			negative.setGreen(255-color.green());
			negative.setBlue(255-color.blue());
			negative.setAlpha(200);

			QPen pen;
			pen.setColor(negative);
			//pen.setWidth(0); // used for geometry analysis
			pen.setWidthF(millDiameter); // TODO 1: set correct line width
			pen.setStyle(Qt::SolidLine);
			pen.setCapStyle(Qt::RoundCap);
			pen.setJoinStyle(Qt::RoundJoin);


			item->setPen(pen);
			//item->setPen(QPen(QBrush(negative), millDiameter, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

			item->setBrush(Qt::NoBrush);
			millingItems.append(item);
		}
	}

	return millingItems;
}

void GerberReader::setMillPathsVisible(bool flag)
{
	for(int n=0; n<millingItems.size(); n++){
		millingItems.at(n)->setVisible(flag);
	}
}

qreal GerberReader::getLengthOfMillingPaths()
{
	qreal totalLength=0;
	// Clean the polygons from colinear segments!
	for(int mp=0; mp<millingPolygons.size(); mp++){ // for all polygons
		QPolygonF poly = millingPolygons.at(mp);
		qreal polyLength=0;
		for(int v=0; v<poly.size()-1; v++){ // for all vertices
			QPointF d1 = poly.at(v+1)-poly.at(v); // first line
			polyLength+=getLength(d1);
		}
		qDebug(QString("Polygon[%1].length() = %2mm").arg(mp).arg(polyLength).toLatin1());
		totalLength+=polyLength;
	}
	qDebug(QString("Total Length of milling-paths = %1mm").arg(totalLength).toLatin1());
	return totalLength;
}


// reorders all polygons in input
// and tries to get get the shortest moveTo-paths
// if spreadFirstItems=ture, first elements to mill/drill are in 9 sectors over the layout
QVector<QPolygonF> GerberReader::sortPaths(QVector<QPolygonF> input, bool spreadFirstItems)
{
	QVector<QPolygonF> output;
	QPointF recentEnd(0,0);


	// get bounding box;
	// generate 9 points spread over the bounding box
	// this will be used for checking the cutting depth

	QRectF bb;
    QVector<QPointF> testingPoints;

	if(spreadFirstItems){
		bb.setBottom(millingPolygons.first().first().y());
		bb.setLeft(millingPolygons.first().first().x());
		for(int mp=0; mp<millingPolygons.size(); mp++){ // for all polygons
			QPolygonF poly = millingPolygons.at(mp);
			for(int n=0; n<poly.size(); n++){ // for all points in the polygon
				QPointF p = poly.at(n);

				if(p.x()<bb.left()){
					bb.setLeft(p.x());
				}
				if(p.x()>bb.right()){
					bb.setRight(p.x());
				}

				// top and bottom are in screen-coordinates!
				if(p.y()>bb.bottom()){
					bb.setBottom(p.y());
				}
				if(p.y()<bb.top()){
					bb.setTop(p.y());
				}
			}
		}
		qDebug("got bounding box");
		qDebug() << "BoundingBox: (l,r,b,t,w,h) " << bb.left() << bb.right() << bb.bottom() << bb.top() << bb.width() << bb.height();

		const int NP = 3;
		for(qreal kx=0.5/NP; kx<1; kx+=1.0/NP){
			for(qreal ky=0.5/NP; ky<1; ky+=1.0/NP){
				// top and bottom are in screen-coordinates!
				testingPoints.append(QPointF(bb.left()+kx*bb.width(), bb.bottom()-ky*(bb.height()))); // Mirror y, due to coordinatesystem inconsistency (LCD, CNC)
				qDebug() << "TestingPoint[" << testingPoints.size()-1 << "] = (" << testingPoints.last().x()<<"/"<<testingPoints.last().y()<<")";
			}
		}
		qDebug("testingPoints calculated");

		recentEnd = testingPoints.first();
	}else{
		recentEnd = QPointF(0,0);
	}

	while(input.size()>0){
		// calculate all distances from the recent end-point to all start-points in input.
		int nearestPolyIndex = INT_MAX;
		qreal nearestDistance = 1000;
		for(int n=0; n<input.size(); n++){ // for all remaining polygons in input
			qreal d = getLength(recentEnd - input.at(n).first()); // distance between recentEnd and current start
			if(d<nearestDistance){
				// store the polygonindex of the polygon with the smallest distance.
				nearestDistance = d;
				nearestPolyIndex = n;
			}

		}

		// move the found polygon from input to output
		output.append(input.at(nearestPolyIndex));
		input.remove(nearestPolyIndex);
		// use teseting point or store the endpoint from this polygon in recentEnd
		if(spreadFirstItems && output.size()<testingPoints.size()){
			recentEnd = testingPoints.at(output.size());
		}else{
			recentEnd = output.last().last();
		}

		qreal progress = (qreal)output.size()/millingPolygons.size();
		emit calculaltionProgressed("Sorting Milling Paths", progress);
	}

	// write output vector back to millingPolygons
	return output;
}


// override run()
void GerberReader::run()
{
	calculateMillingPolygons(gCodeSettings.millDiameter()/2);
	//exec();
	qDebug("finished run()");
	//exec();

	// calling CopperField::calculationFinished() now
}

// TODO 4: Z-Map: dies sollte entweder gelöscht werden, oder in ein spezielles menü gepackt werden
void GerberReader::loadZMap()
{
	testInterpolation();


	QString fn("surface-bot-6-2x.txt");


	qDebug() << "reading zMap from " << fn;
	QFile file(fn);
	file.open(QFile::ReadOnly);

	bool readAllX = false;

	file.readLine(); // skip first line

	while(!file.atEnd()){
		QString line = file.readLine(); // read top zLevel

        QList<QString> numStrings = line.split(' ');

		if(numStrings.size()==9){ // do nothing with the last line, which is empty

			double xValue = numStrings.at(0).toDouble();
			double yValue = numStrings.at(1).toDouble();
			double zValue = numStrings.at(2).toDouble();

			if(xVector.size()>0 && xValue == xVector.at(0)){
				readAllX = true;
			}

			if(xVector.size()==0 || xVector.size()>0 && xValue == xVector.at(0)){ // save y-values
				yVector.append(yValue);
			}

			if(!readAllX){
				xVector.append(xValue);
			}

			zMap.append(zValue);

			file.readLine(); // skip every second line (bottom zLevel)
		}
	}

	qDebug("xVector:");
	for(int n=0; n<xVector.size(); n++){
		qDebug() << "\t" << xVector.at(n);
	}
	qDebug("yVector:");
	for(int n=0; n<yVector.size(); n++){
		qDebug() << "\t" << yVector.at(n);
	}
}

void GerberReader::testInterpolation()
{
	qDebug("Testing Interpolation...");
	xVector.clear();
	xVector << 0 << 1 << 2 << 3 << 4;
	yVector.clear();
	yVector << 0 << 1 << 2 << 3 << 4 << 5 << 6;

	qreal kx = 0.1;
	qreal ky = 0.3;

	zMap.clear();

	// simple plane
	for(int ny=0; ny<yVector.size(); ny++){
		for(int nx=0; nx<xVector.size(); nx++){
			zMap << xVector[nx]*kx + yVector[ny]*ky;
		}
	}



	QString millFileName = "testinterpolation.txt";
	qDebug("exporting to " + millFileName.toLatin1());
	QFile file(millFileName);
	file.open(QFile::WriteOnly);

	// use
	//		file.write(QString("Hello World").toLatin1());
	// for writing to the file.


	for(qreal y=0; y<yVector.last(); y+=0.2){
		for(qreal x=0; x<xVector.last(); x+=0.1){
			file.write(QString("%1 %2 %3\n").arg(x).arg(y).arg(interpolateMap(QPointF(x,y))).toLatin1());
			file.write(QString("%1 %2 %3\n").arg(x).arg(y).arg(interpolateMap(QPointF(x,y))).toLatin1());
		}
	}

	file.close();
	qDebug("finished");

	xVector.clear();
	yVector.clear();
	zMap.clear();
}

// for now, only rectangular point-matrix is supported!
// TODO 5: funktioniert noch nicht richtig!!
// siehe matlab und testinterpolation.txt
qreal GerberReader::interpolateMap(QPointF p)
{
	// get the four neighbour Points and indizes
	if(xVector.isEmpty() || yVector.isEmpty()){
		return 0;
	}

	if(p.x() < xVector.first() || p.x() > xVector.last()){
		qDebug(QString("out of x-Range: left = %1, p.x = %2, right = %3").arg(xVector.first()).arg(p.x()).arg(xVector.last()).toLatin1());
		return 0;
	}
	if(p.y() < yVector.first() || p.y() > yVector.last()){
		qDebug(QString("out of y-Range: bot = %1, p.y = %2, top = %3").arg(yVector.first()).arg(p.y()).arg(yVector.last()).toLatin1());
		return 0;
	}

	int nX=0;
	int nY=0;

	while(xVector.at(nX) < p.x()){
		nX++;
	}
	nX--; // now nX is the index of the left-x-line
	nX = nX<0?0:nX;
	nX = nX<(xVector.size()-1)?nX:(xVector.size()-1);

	while(yVector.at(nY) < p.y()){
		nY++;
	}
	nY--; // now nY is the index of the bottom-y-line
	nY = nY<0?0:nY;
	nY = nY<(yVector.size()-1)?nY:(yVector.size()-1);


	qreal P_BL[3]; // bottom left point
	P_BL[0] = xVector.at(nX+0);
	P_BL[1] = yVector.at(nY+0);
	P_BL[2] = zMap.at((nX+0)+ yVector.size()*(nY+0));

	qreal P_BR[3];// bottom right
	P_BR[0] = xVector.at(nX+1);
	P_BR[1] = yVector.at(nY+0);
	P_BR[2] = zMap.at((nX+1)+ yVector.size()*(nY+0));

	qreal P_TL[3]; // top left
	P_TL[0] = xVector.at(nX+0);
	P_TL[1] = yVector.at(nY+1);
	P_TL[2] = zMap.at((nX+0)+ yVector.size()*(nY+1));

	qreal P_TR[3];// top right
	P_TR[0] = xVector.at(nX+1);
	P_TR[1] = yVector.at(nY+1);
	P_TR[2] = zMap.at((nX+1)+ yVector.size()*(nY+1));


	// source of algorithm: wikipedia
	qreal botZ =	(P_BR[0]-p.x())/(P_BR[0]-P_BL[0]) * P_BL[2] +
					(p.x()-P_BL[0])/(P_BR[0]-P_BL[0]) * P_BR[2];
	qreal topZ =	(P_TR[0]-p.x())/(P_TR[0]-P_TL[0]) * P_TL[2] +
					(p.x()-P_TL[0])/(P_TR[0]-P_TL[0]) * P_TR[2];

	qreal midZ =	(P_TL[1]-p.y())/(P_TL[1]-P_BL[1]) * botZ +
					(p.y()-P_BL[1])/(P_TL[1]-P_BL[1]) * topZ;

	return midZ;
}


/*
P_CAD = [2,-1; 120,3; 110,130; 2,149] % soll position laut CAD
P_CNC = [2,-1.625; 120.209,2.491; 110.137,130.049; 2,149] % ist position, vermessen im CNC-KoSy

% Perspektiven-Transformation mit bilinearem Ansatz laut Josef Scharinger
% Skript:
% xCNC = kx1*xCAD + kx2*yCAD + kx3*xCAD*yCAD + kx4
% yCNC = ky1*xCAD + ky2*yCAD + ky3*xCAD*yCAD + ky4
% diese 2 zeilen werden in 2 gleichungssysteme mit je 4 unbekannten gegeben.

M = [P_CAD(:,1), P_CAD(:,2), P_CAD(:,1).*P_CAD(:,2), ones(4,1)];
xCNC = P_CNC(:,1);
% M*kx = xCNC
% --> kx = M^-1 * xCNC
kx = M^-1 * xCNC

yCNC = P_CNC(:,2);
ky = M^-1 * yCNC

*/
void GerberReader::initPerspectiveTransform()
{
	Matrix P_CAD(4,2);
	Matrix P_CNC(4,2);
	k = Matrix(4,2);
	Matrix M(4,4);

	//P_CAD = [2,-1; 120,3; 110,130; 2,149] % soll position laut CAD
	//P_CNC = [2,-1.625; 120.209,2.491; 110.137,130.049; 2,149] % ist position, vermessen im CNC-KoSy

	// ACHTUNG: bei der initialisierung unbedingt double-werte angeben! d.h. Komma 0 anhängen bei ganzen zahlen.
	P_CAD.init(8, 2.0,120.0,110.0,2.0, -1.0,3.0,130.0,149.0);
	P_CNC.init(8, 2.0,120.209,110.137,2.0, -1.625,2.491,130.049,149.0);

	qDebug(("P_CAD = " + P_CAD.toString()).toLatin1());
	qDebug(("P_CNC = " + P_CNC.toString()).toLatin1());

	for(int row=0; row<4; row++){
		M(row,0) = P_CAD(row,0);
		M(row,1) = P_CAD(row,1);
		M(row,2) = P_CAD(row,0)*P_CAD(row,1);
		M(row,3) = 1;
	}

	// M*k = P_CNC
	// k = M^-1*P_CNC

	k = M.inv() * P_CNC;
	qDebug(("k = " + k.toString()).toLatin1());
}

// Transforms a CAD-Point into a CNC-Point for exporting drill coordinates.
QPointF GerberReader::perspectiveTransform(QPointF pCAD)
{
	qreal x = k(0,0)*pCAD.x() + k(1,0)*pCAD.y() + k(2,0)*pCAD.x()*pCAD.y() + k(3,0);
	qreal y = k(0,1)*pCAD.x() + k(1,1)*pCAD.y() + k(2,1)*pCAD.x()*pCAD.y() + k(3,1);
	return QPointF(x,y);
}

void GerberReader::deleteMillingPolygons()
{
	millingPolygons.clear();

	foreach(QGraphicsPathItem* i, millingItems){
		delete(i);
	}
	millingItems.clear();
}

