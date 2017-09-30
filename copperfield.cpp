/*
  this project was coppied on 27.1.2012
  of the project QWire
*/

#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QtGui>
#include <QToolBar>

#include "copperfield.h"
#include "view.h"
#include "scene.h"
#include "netsviewer.h"

#include <QDebug>

#include "gerberreader.h"
#include "progresssplashscreen.h"

/*
  Information about the software:

  Dieses Programm liest mehrere Gerberdatein, produziert von Kicad, ein, und stellt diese am
  Bildschirm dar. Die Layer-Zuordnung erfolgt durch die Datei-Endung.
	gtl -> Top
	gbl	-> Bottom
	gbr -> Contours
	drl -> Drill

  Gleichzeitig werden die einzelnen Linien zu Netzen zusammengefasst. Ausgenommen Texte.
  Anschließend kann man Fräskonturen berechnen lassen, die als G-Code exportiert werden.
  Dies geschieht, indem jedes einzelne Netz in eine Pixelgraphik gerendert wird, und daraus
  mit einer Dillate-Pixel-Operation eine Grafik erzeugt wird, die an den konturen um den halben fräserdurchmesser
  vergrößert ist. Dann wir daraus die Fräsbahn berechnet.
  Texte werden direkt gefräst, und nicht freigestellt.

  Zum fräsen selbst muss eine Oberflächen-Kompensation verwendet werden, um eine konstante
  Eintauchtiefe zu erreichen.

*/

/* TODO:
 * Cutter Diameter wird aus gerberSettings nicht übernommen... k.A. warum.
 */


CopperField* CopperField::app = NULL;

CopperField::CopperField(QWidget *parent)
    : QMainWindow(parent)
{
    app = this;
	yScale = -1; // redo the mirroring due to the monitor-coordinate system.
	alpha = 128;

    view = new View(this);
    setCentralWidget(view);

	gCodeSettings.setVisible(false);
	gCodeSettings.setParent(this, Qt::Tool);
	layerSettings.setVisible(false);
	layerSettings.setParent(this, Qt::Tool);

	netsViewer = new NetsViewer(this);
	addDockWidget(Qt::LeftDockWidgetArea, netsViewer, Qt::Vertical);
	statusBar()->addPermanentWidget(&coordinateText, 1);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

	readSettings();

//    connect(textEdit->document(), SIGNAL(contentsChanged()),
//            this, SLOT(documentWasModified()));

    setCurrentFile("");
}

CopperField::~CopperField()
{
}

void CopperField::closeEvent(QCloseEvent *event)
{
	writeSettings();
}

void CopperField::newFile()
{
//    if (maybeSave()) {
//        //textEdit->clear();
//        setCurrentFile("");
//    }

	netsViewer->clear();

	delete(gerberTop);
	delete(gerberBot);
	delete(gerberDrill);
	delete(gerberContour);
}

void CopperField::open()
{
//    if (maybeSave()) {
//        QString fileName = QFileDialog::getOpenFileName(this);
//        if (!fileName.isEmpty())
//            loadFile(fileName);

//    }
	curFile = QFileDialog::getOpenFileName(this,
		 tr("Open Gerber/Drill File"), curDir.absolutePath(), tr("Gerber Files (*.gtl *.gbl *.gbr *.drl)"));

	QFileInfo f(curFile);
	curDir.setPath(f.absolutePath());

	qDebug(f.suffix().toAscii());


	GerberReader* gr = 0;
	if(f.suffix().toLower() == "gbl"){ // bottom layer
		gerberBot = new GerberReader(curFile, QColor(50,155,50, alpha)); // just display the gerber drawing, by adding the elements to the scene
		gr = gerberBot;
		layerSettings.setGerberReader(LayerWidget::BOT, gr);
		layerSettings.setGerberReader(LayerWidget::BOT_MILL, gr);
	}else if(f.suffix().toLower() == "gtl"){ // top layer
		gerberTop = new GerberReader(curFile,QColor(155,50,50, alpha)); // just display the gerber drawing, by adding the elements to the scene
		gr = gerberTop;
		layerSettings.setGerberReader(LayerWidget::TOP, gr);
		layerSettings.setGerberReader(LayerWidget::TOP_MILL, gr);
	}else if(f.suffix().toLower() == "gbr"){ // contour layer
		gerberContour = new GerberReader(curFile, QColor(155,155,50, alpha)); // just display the gerber drawing, by adding the elements to the scene
		gr = gerberContour;
		layerSettings.setGerberReader(LayerWidget::CONTOUR, gr);
		layerSettings.setGerberReader(LayerWidget::CONTOUR_MILL, gr);
	}else if(f.suffix().toLower() == "drl"){ // drill layer
		gerberDrill = new GerberReader(curFile, QColor(50,50,155, alpha)); // just display the gerber drawing, by adding the elements to the scene
		gr = gerberDrill;
		layerSettings.setGerberReader(LayerWidget::DRILLS, gr);
	}else{
		// unsupported file extension
	}

	if(gr){
		qDebug("Adding GerberElements to the Scene...");
		QVector<GerberElement*> elements = gr->elements();
		//qDebug("got elements");
		//qDebug(QString("size of elements: %1").arg(elements.size()).toAscii());
		for(int n=0; n<elements.size(); n++){

			QGraphicsItem* item = elements.at(n)->getItem();
			if(item){
				//qDebug(QString("adding element #%1 to the scene").arg(n).toAscii());
				view->scene->addItem(item);
			}
		}

		// enlargen the scene rect, to make intuitive zooming possible
		QRectF sr = view->scene->sceneRect();
		qreal k = 5;
		qreal w = sr.width();
		qreal h = sr.height();
		sr.setX(sr.x()+w/2*(1-k)); // redefines x, without changing the right edge --> width is changed
		sr.setY(sr.y()+h/2*(1-k)); // redefines y, without changing the bottom edge --> height is changed
		sr.setWidth(w*k);
		sr.setHeight(h*k);
		view->scene->setSceneRect(sr);

		view->zoomAll();
	}
}



void CopperField::about()
{
    QMessageBox::about(this, tr("About Application"),
                       tr("The <b>Application</b> example demonstrates how to "
                          "write modern GUI applications using Qt, with a menu bar, "
                          "toolbars, and a status bar."));
}

void CopperField::documentWasModified()
{
    //setWindowModified(textEdit->document()->isModified());
}

void CopperField::createActions()
{
	// File:
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
	newAct->setStatusTip(tr("Create a new pcb project"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
	openAct->setStatusTip(tr("Open a Gerber file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	exportAct = new QAction(QIcon(":/images/save.png"), tr("&Export"), this);
	exportAct->setShortcut(tr("Ctrl+E"));
	exportAct->setStatusTip(tr("Export GCode to file"));
	connect(exportAct, SIGNAL(triggered()), this, SLOT(exportGCode()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	// View:
	zoomAllAct = new QAction(tr("Zoom All"), this);
	zoomAllAct->setStatusTip(tr("Set zoom, to view all items"));
	zoomAllAct->setShortcut(Qt::Key_Home);
	connect(zoomAllAct, SIGNAL(triggered()), view, SLOT(zoomAll()));

	// Edit:
	showGCodeSettingsAct = new QAction(tr("GCode Settings (G)"), this);
	showGCodeSettingsAct->setStatusTip(tr("Open G-Code Settings Dialog"));
	showGCodeSettingsAct->setShortcut(Qt::Key_G);
	connect(showGCodeSettingsAct, SIGNAL(triggered()), this, SLOT(showGCodeSettings()));

	showLayerSettingsAct = new QAction(tr("Layer Settings (L)"), this);
	showLayerSettingsAct->setStatusTip(tr("Open Layer Settings Dialog"));
	showLayerSettingsAct->setShortcut(Qt::Key_L);
	connect(showLayerSettingsAct, SIGNAL(triggered()), this, SLOT(showLayerSettings()));

	// Process:
	clearMillingPathsAct = new QAction(tr("Clear Mill Paths"), this);
	clearMillingPathsAct->setStatusTip(tr("Use the current G-Code Settings, and calculate all milling paths"));
	//clearMillingPathsAct->setShortcut(Qt::Key_M);
	connect(clearMillingPathsAct, SIGNAL(triggered()), this, SLOT(calearMillingPaths()));

	calculateMillingPathsAct = new QAction(tr("Calc Mill Paths (M)"), this);
	calculateMillingPathsAct->setStatusTip(tr("Use the current G-Code Settings, and calculate all milling paths"));
	calculateMillingPathsAct->setShortcut(Qt::Key_M);
	connect(calculateMillingPathsAct, SIGNAL(triggered()), this, SLOT(calculateMillingPaths()));

	// Help:
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void CopperField::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
	fileMenu->addAction(exportAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(showGCodeSettingsAct);
	editMenu->addAction(showLayerSettingsAct);

	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(zoomAllAct);

	processMenu = menuBar()->addMenu(tr("&Process"));
	processMenu->addAction(clearMillingPathsAct);
	processMenu->addAction(calculateMillingPathsAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void CopperField::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
	fileToolBar->addAction(exportAct);

    editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(showGCodeSettingsAct);

	processToolBar = addToolBar(tr("Process"));
	processToolBar->addAction(calculateMillingPathsAct);
}

void CopperField::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void CopperField::readSettings()
{
	QSettings settings("Mechatronik Zeilhofer", "CopperField");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
	curDir.setPath(settings.value("currentDirectory", QDir::currentPath()).toString());
    resize(size);
    move(pos);
}

void CopperField::writeSettings()
{
	QSettings settings("Mechatronik Zeilhofer", "CopperField");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
	settings.setValue("currentDirectory", curDir.absolutePath());
}

bool CopperField::maybeSave()
{
//    if (textEdit->document()->isModified()) {
//        QMessageBox::StandardButton ret;
//        ret = QMessageBox::warning(this, tr("Application"),
//                                   tr("The document has been modified.\n"
//                                      "Do you want to save your changes?"),
//                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//        if (ret == QMessageBox::Save)
//            return save();
//        else if (ret == QMessageBox::Cancel)
//            return false;
//    }
    return true;
}

// read gerber file into data block strings
void CopperField::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);

	QTextStream in(&file);
	QString line = in.readLine();
	QString dataBlock; // gerber term, ends with an asterisk
	QStringList blocks;
	bool parameterFlag = false; // true, when just parsing a parameter (surrounded by '%')
	bool nextBlock = false; // flag, to go start a new block

	while(!line.isNull()){

		for(int n=0; n<line.size(); n++){ // every character in the line
			if(line.at(n) == '%'){ // if parameter ends or starts
				if(parameterFlag){
					parameterFlag = false;
					nextBlock = true;
				}
				else{
					parameterFlag = true;
				}
			}

			if(line.at(n) == '*' && parameterFlag==false){
				nextBlock = true;
			}

			dataBlock.append(line.at(n));
			if(nextBlock){
				nextBlock = false;
				blocks.append(dataBlock);
				dataBlock.clear();
			}
		}
		line = in.readLine();
	}

	for(int n=0; n<blocks.size(); n++){
		qDebug() << blocks.at(n);
	}

	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool CopperField::saveFile(const QString &fileName)
{
//    QFile file(fileName);
//    if (!file.open(QFile::WriteOnly | QFile::Text)) {
//        QMessageBox::warning(this, tr("Application"),
//                             tr("Cannot write file %1:\n%2.")
//                             .arg(fileName)
//                             .arg(file.errorString()));
//        return false;
//    }
//
//    QTextStream out(&file);
//    QApplication::setOverrideCursor(Qt::WaitCursor);
//    out << textEdit->toPlainText();
//    QApplication::restoreOverrideCursor();
//
//    setCurrentFile(fileName);
//    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void CopperField::setCurrentFile(const QString &fileName)
{
//    curFile = fileName;
//    textEdit->document()->setModified(false);
//    setWindowModified(false);
//
//    QString shownName;
//    if (curFile.isEmpty())
//        shownName = "untitled.txt";
//    else
//        shownName = strippedName(curFile);
//
//    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}

QString CopperField::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}









//QPointF CopperField::getNormalUnityVector(const QPointF& p)
//{
//	QPointF n(p.y(), -p.x()); // rotate vector in positive mathematical direction
//	n = n/getLength(n); // scale to unity vector
//	return n;
//}


void CopperField::showGCodeSettings()
{
	GerberReader* gr=0;
	switch(layerSettings.activeLayer()){
	case LayerWidget::TOP_MILL:
	case LayerWidget::TOP:
	{
		gr = gerberTop;
	}break;
	case LayerWidget::BOT_MILL:
	case LayerWidget::BOT:
	{
		gr = gerberBot;
	}break;
	case LayerWidget::CONTOUR:
	{
		gr = gerberContour;
	}break;
	case LayerWidget::DRILLS:
	{
		gr = gerberDrill;
	}break;
	default:
		qDebug("no active layer");
	}
	if(gr){
		gr->gCodeSettings.show();
	}
}

void CopperField::showLayerSettings()
{
	layerSettings.show();
}

// slot, connected to a qAction
void CopperField::calculateMillingPaths(){

	qDebug("Calculate Milling Contours with Dilation...");


	GerberReader* gr = 0;

	switch(layerSettings.activeLayer()){
	case LayerWidget::TOP:
	{
		gr = gerberTop;
		layerSettings.setActiveLayer(LayerWidget::TOP_MILL);
	}break;
	case LayerWidget::BOT:
	{
		gr = gerberBot;
		layerSettings.setActiveLayer(LayerWidget::BOT_MILL);
	}break;
	case LayerWidget::CONTOUR:
	{
		gr = gerberContour;
		layerSettings.setActiveLayer(LayerWidget::CONTOUR_MILL);
	}break;
	case LayerWidget::DRILLS:
	{

	}break;
	default:
		qDebug("no active layer");
	}

	if(gr){
		pss.show();
		connect(gr, SIGNAL(calculaltionProgressed(QString,qreal)), &pss, SLOT(changeProgress(QString,qreal)), Qt::QueuedConnection);
		connect(gr, SIGNAL(finished()), this, SLOT(calculationFinished()), Qt::QueuedConnection);
		gerberCurrentlyProcessing = gr;
		gr->setCutterRadius(gCodeSettings.millDiameter()/2);
		qDebug("start calculation");
		gr->start();
	}
}

// slot for thread:
void CopperField::calculationFinished()
{
	if(gerberCurrentlyProcessing){ // test for valid pointer
		QVector<QGraphicsPathItem*> items;
		items = gerberCurrentlyProcessing->getMillingGraphicItems();
		qDebug(QString("Add %1 MillingPolygons to scene...").arg(items.size()).toAscii());
		//add polygons to the scene
		for(int n=0; n<items.size(); n++){
			view->scene->addItem(items.at(n));
		}
		qDebug("Finished");
		disconnect(gerberCurrentlyProcessing, SIGNAL(calculaltionProgressed(QString,qreal)), &pss, SLOT(changeProgress(QString,qreal)));
		disconnect(gerberCurrentlyProcessing, SIGNAL(finished()), this, SLOT(calculationFinished()));

		gerberCurrentlyProcessing = 0; // set pointer to zero
		pss.hide();
	}
}

// TODO!
void CopperField::calearMillingPaths(){
//	for(int n=0; n<millingPolygons->size(); n++){
//		delete(millingPolygons->at(n));
//	}
//	delete(millingPolygons);
}


void CopperField::exportGCode()
{
	qDebug("exporting G-Code");

	GerberReader* gr = 0;

	// TODO: show gcode-settings dialog before exporting

	if(gCodeSettings.mirror()){
		qDebug("export wird gespiegelt");
	}else{
		qDebug("export wird NICHT gespiegelt");
	}

	switch(layerSettings.activeLayer()){
	case LayerWidget::TOP_MILL:
	case LayerWidget::TOP:
	{
		gr = gerberTop;
		if(gr) gr->exportGCode(gCodeSettings.mirror());
	}break;
	case LayerWidget::BOT_MILL:
	case LayerWidget::BOT:
	{
		gr = gerberBot;
		if(gr) gr->exportGCode(gCodeSettings.mirror()); // mirror bottom mills
	}break;
	case LayerWidget::CONTOUR:
	{
		gr = gerberContour;
		if(gr) gr->exportGCode(gCodeSettings.mirror()); // mill contours from the bottom side --> mirror
	}break;
	case LayerWidget::DRILLS:
	{
		gr = gerberDrill;
		if(gr) gr->exportGCode(gCodeSettings.mirror()); // drill from bottom side, due to surface-probing
	}break;
	default:
		qDebug("no active layer");
	}
}






