/********************************************************************************
** Form generated from reading UI file 'progresssplashscreen.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSSPLASHSCREEN_H
#define UI_PROGRESSSPLASHSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgressSplashScreen
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *ProgressSplashScreen)
    {
        if (ProgressSplashScreen->objectName().isEmpty())
            ProgressSplashScreen->setObjectName(QString::fromUtf8("ProgressSplashScreen"));
        ProgressSplashScreen->resize(489, 64);
        verticalLayout = new QVBoxLayout(ProgressSplashScreen);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ProgressSplashScreen);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(ProgressSplashScreen);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(ProgressSplashScreen);

        QMetaObject::connectSlotsByName(ProgressSplashScreen);
    } // setupUi

    void retranslateUi(QWidget *ProgressSplashScreen)
    {
        ProgressSplashScreen->setWindowTitle(QApplication::translate("ProgressSplashScreen", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProgressSplashScreen", "Cleaning Polygons...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProgressSplashScreen: public Ui_ProgressSplashScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSSPLASHSCREEN_H
