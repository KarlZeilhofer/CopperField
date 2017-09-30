#ifndef GCODESETTINGS_H
#define GCODESETTINGS_H

#include <QDialog>

namespace Ui {
    class GCodeSettings;
}

class GCodeSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GCodeSettings(QWidget *parent = 0);
    ~GCodeSettings();

	qreal zClearance(){return myZClearance;} // common for milling/drilling
	bool mirror(){return myMirrorFlag;} // common for milling/drilling

	qreal millDiameter(){return myMillDiameter;}
	qreal millZDepth(){return myMillZDepth;}  // returns positive value
	qreal millFeedrate(){return myMillFeedrate;}
	qreal millPlungeFeedrate(){return myMillPlungeFeedrate;}

	qreal drillDepth(){return myDrillDepth;}
	qreal drillPlungeFeedrate(){return myDrillPlungeFeedrate;}

private: // functions
	void updateValuesFromTextfields();

private slots:
	void on_lineEdit_millDiameter_editingFinished();

	void on_pushButton_clicked();

private:
    Ui::GCodeSettings *ui;

	qreal myZClearance;
	bool myMirrorFlag;

	qreal myMillDiameter;
	qreal myMillZDepth;
	qreal myMillFeedrate;
	qreal myMillPlungeFeedrate;

	qreal myDrillDepth;
	qreal myDrillPlungeFeedrate;
};

#endif // GCODESETTINGS_H
