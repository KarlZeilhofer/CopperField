#ifndef COPPERFIELD_H
#define COPPERFIELD_H

#include <QtGui/QMainWindow>
#include <QDir>
#include <QVector>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QLabel>
#include "gcodesettings.h"
#include "dialoglayers.h"
#include "gerberelement.h"
#include "progresssplashscreen.h"

class QAction;
class QMenu;
class QTextEdit;
class View;
class CopperField;
class GerberReader;
class NetsViewer;

/*
 * Hauptklasse
 * ist eine QMainWindow
 * Mit ceter-Widget: View
 */

class CopperField : public QMainWindow
{
    Q_OBJECT
public:
	CopperField(QWidget *parent = 0);
	~CopperField();

	void calculateMillingContours(qreal offset);


protected:
    void closeEvent(QCloseEvent *event);


private slots:
    void newFile();
    void open();
	void exportGCode();
    void about();
    void documentWasModified();
	void showGCodeSettings();
	void showLayerSettings();
	void calculateMillingPaths();
	void calearMillingPaths();

public slots:
	void calculationFinished();

public:
	static CopperField* app;
    View *view;
	NetsViewer* netsViewer;	

//	QPointF getNormalUnityVector(const QPointF& p);

	QLabel coordinateText;

	GCodeSettings gCodeSettings;
	DialogLayers layerSettings;

private:
	qreal yScale;
	int alpha; // opacity

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);


    QString curFile;
	QDir curDir;

	GerberReader* gerberTop; // top layer for copper and text
	GerberReader* gerberBot; // bottom layer for copper and text
	GerberReader* gerberDrill; // drill layer
	GerberReader* gerberContour; // contour mill layer
	GerberReader* gerberCurrentlyProcessing; // this pointer is used for the calculating milling paths in a thread
	ProgressSplashScreen pss;

    QMenu *fileMenu;
    QMenu *editMenu;
	QMenu *viewMenu;
	QMenu *processMenu;
	QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
	QToolBar *processToolBar;

	// File
    QAction *newAct;
    QAction *openAct;
	QAction *exportAct;
    QAction *exitAct;

	// Edit
	QAction *showGCodeSettingsAct;
	QAction *showLayerSettingsAct;

	// View
	QAction *zoomAllAct; // set zoom, that all items in the scene can be seen.

	// Process
	QAction *clearMillingPathsAct;
	QAction *calculateMillingPathsAct;

	// Help
    QAction *aboutAct;
    QAction *aboutQtAct;
};
#endif // COPPERFIELD_H
