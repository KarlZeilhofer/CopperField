#ifndef PROGRESSSPLASHSCREEN_H
#define PROGRESSSPLASHSCREEN_H

#include <QWidget>

namespace Ui {
    class ProgressSplashScreen;
}

class ProgressSplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressSplashScreen(QWidget *parent = 0);
    ~ProgressSplashScreen();

public slots:
	void changeProgress(QString task, qreal progress); // from 0 to 1

private:
    Ui::ProgressSplashScreen *ui;
};

#endif // PROGRESSSPLASHSCREEN_H
