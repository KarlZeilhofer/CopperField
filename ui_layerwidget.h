/********************************************************************************
** Form generated from reading UI file 'layerwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYERWIDGET_H
#define UI_LAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LayerWidget
{
public:
    QGridLayout *gridLayout;
    QRadioButton *radioButton;
    QCheckBox *checkBox_visible;
    QPushButton *pushButton_color;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_delete;

    void setupUi(QWidget *LayerWidget)
    {
        if (LayerWidget->objectName().isEmpty())
            LayerWidget->setObjectName(QString::fromUtf8("LayerWidget"));
        LayerWidget->resize(353, 41);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LayerWidget->sizePolicy().hasHeightForWidth());
        LayerWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(LayerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(-1, 0, -1, 0);
        radioButton = new QRadioButton(LayerWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        gridLayout->addWidget(radioButton, 0, 0, 1, 1);

        checkBox_visible = new QCheckBox(LayerWidget);
        checkBox_visible->setObjectName(QString::fromUtf8("checkBox_visible"));

        gridLayout->addWidget(checkBox_visible, 0, 1, 1, 1);

        pushButton_color = new QPushButton(LayerWidget);
        pushButton_color->setObjectName(QString::fromUtf8("pushButton_color"));

        gridLayout->addWidget(pushButton_color, 0, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        pushButton_delete = new QPushButton(LayerWidget);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));

        gridLayout->addWidget(pushButton_delete, 0, 5, 1, 1);


        retranslateUi(LayerWidget);

        QMetaObject::connectSlotsByName(LayerWidget);
    } // setupUi

    void retranslateUi(QWidget *LayerWidget)
    {
        LayerWidget->setWindowTitle(QApplication::translate("LayerWidget", "Form", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("LayerWidget", "Layername", 0, QApplication::UnicodeUTF8));
        checkBox_visible->setText(QApplication::translate("LayerWidget", "visible", 0, QApplication::UnicodeUTF8));
        pushButton_color->setText(QApplication::translate("LayerWidget", "Color", 0, QApplication::UnicodeUTF8));
        pushButton_delete->setText(QApplication::translate("LayerWidget", "Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LayerWidget: public Ui_LayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERWIDGET_H
