/********************************************************************************
** Form generated from reading UI file 'dialoglayers.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLAYERS_H
#define UI_DIALOGLAYERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "layerwidget.h"

QT_BEGIN_NAMESPACE

class Ui_DialogLayers
{
public:
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    LayerWidget *layerWidget_top;
    LayerWidget *layerWidget_topMill;
    LayerWidget *layerWidget_bot;
    LayerWidget *layerWidget_botMill;
    LayerWidget *layerWidget_contour;
    LayerWidget *layerWidget_contourMill;
    LayerWidget *layerWidget_drill;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DialogLayers)
    {
        if (DialogLayers->objectName().isEmpty())
            DialogLayers->setObjectName(QString::fromUtf8("DialogLayers"));
        DialogLayers->resize(396, 368);
        gridLayout_2 = new QGridLayout(DialogLayers);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        scrollArea = new QScrollArea(DialogLayers);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 374, 346));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        layerWidget_top = new LayerWidget(scrollAreaWidgetContents);
        layerWidget_top->setObjectName(QString::fromUtf8("layerWidget_top"));
        layerWidget_top->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(layerWidget_top, 0, 0, 1, 1);

        layerWidget_topMill = new LayerWidget(scrollAreaWidgetContents);
        layerWidget_topMill->setObjectName(QString::fromUtf8("layerWidget_topMill"));
        layerWidget_topMill->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(layerWidget_topMill, 1, 0, 1, 1);

        layerWidget_bot = new LayerWidget(scrollAreaWidgetContents);
        layerWidget_bot->setObjectName(QString::fromUtf8("layerWidget_bot"));
        layerWidget_bot->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(layerWidget_bot, 2, 0, 1, 1);

        layerWidget_botMill = new LayerWidget(scrollAreaWidgetContents);
        layerWidget_botMill->setObjectName(QString::fromUtf8("layerWidget_botMill"));
        layerWidget_botMill->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(layerWidget_botMill, 3, 0, 1, 1);

        layerWidget_contour = new LayerWidget(scrollAreaWidgetContents);
        layerWidget_contour->setObjectName(QString::fromUtf8("layerWidget_contour"));
        layerWidget_contour->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(layerWidget_contour, 4, 0, 1, 1);

        layerWidget_contourMill = new LayerWidget(scrollAreaWidgetContents);
        layerWidget_contourMill->setObjectName(QString::fromUtf8("layerWidget_contourMill"));
        layerWidget_contourMill->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(layerWidget_contourMill, 5, 0, 1, 1);

        layerWidget_drill = new LayerWidget(scrollAreaWidgetContents);
        layerWidget_drill->setObjectName(QString::fromUtf8("layerWidget_drill"));
        layerWidget_drill->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(layerWidget_drill, 6, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 22, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(DialogLayers);

        QMetaObject::connectSlotsByName(DialogLayers);
    } // setupUi

    void retranslateUi(QDialog *DialogLayers)
    {
        DialogLayers->setWindowTitle(QApplication::translate("DialogLayers", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogLayers: public Ui_DialogLayers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLAYERS_H
