/********************************************************************************
** Form generated from reading UI file 'gcodesettings.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCODESETTINGS_H
#define UI_GCODESETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GCodeSettings
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit_zClearance;
    QCheckBox *checkBox_mirror;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_millFeedrate;
    QLabel *label_4;
    QLineEdit *lineEdit_millPlungeFeedrate;
    QLineEdit *lineEdit_millDiameter;
    QLineEdit *lineEdit_millZDepth;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QLineEdit *lineEdit_drillPlungeFeedrate;
    QLineEdit *lineEdit_drillDepth;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *GCodeSettings)
    {
        if (GCodeSettings->objectName().isEmpty())
            GCodeSettings->setObjectName(QString::fromUtf8("GCodeSettings"));
        GCodeSettings->resize(305, 354);
        gridLayout_4 = new QGridLayout(GCodeSettings);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(GCodeSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        lineEdit_zClearance = new QLineEdit(groupBox);
        lineEdit_zClearance->setObjectName(QString::fromUtf8("lineEdit_zClearance"));

        gridLayout_2->addWidget(lineEdit_zClearance, 2, 1, 1, 1);

        checkBox_mirror = new QCheckBox(groupBox);
        checkBox_mirror->setObjectName(QString::fromUtf8("checkBox_mirror"));

        gridLayout_2->addWidget(checkBox_mirror, 3, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 3);

        groupBox_2 = new QGroupBox(GCodeSettings);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        lineEdit_millFeedrate = new QLineEdit(groupBox_2);
        lineEdit_millFeedrate->setObjectName(QString::fromUtf8("lineEdit_millFeedrate"));

        gridLayout->addWidget(lineEdit_millFeedrate, 4, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        lineEdit_millPlungeFeedrate = new QLineEdit(groupBox_2);
        lineEdit_millPlungeFeedrate->setObjectName(QString::fromUtf8("lineEdit_millPlungeFeedrate"));

        gridLayout->addWidget(lineEdit_millPlungeFeedrate, 5, 1, 1, 1);

        lineEdit_millDiameter = new QLineEdit(groupBox_2);
        lineEdit_millDiameter->setObjectName(QString::fromUtf8("lineEdit_millDiameter"));

        gridLayout->addWidget(lineEdit_millDiameter, 3, 1, 1, 1);

        lineEdit_millZDepth = new QLineEdit(groupBox_2);
        lineEdit_millZDepth->setObjectName(QString::fromUtf8("lineEdit_millZDepth"));

        gridLayout->addWidget(lineEdit_millZDepth, 2, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 3);

        groupBox_3 = new QGroupBox(GCodeSettings);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        lineEdit_drillPlungeFeedrate = new QLineEdit(groupBox_3);
        lineEdit_drillPlungeFeedrate->setObjectName(QString::fromUtf8("lineEdit_drillPlungeFeedrate"));

        gridLayout_3->addWidget(lineEdit_drillPlungeFeedrate, 2, 1, 1, 1);

        lineEdit_drillDepth = new QLineEdit(groupBox_3);
        lineEdit_drillDepth->setObjectName(QString::fromUtf8("lineEdit_drillDepth"));

        gridLayout_3->addWidget(lineEdit_drillDepth, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 2, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 3, 0, 1, 1);

        pushButton = new QPushButton(GCodeSettings);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_4->addWidget(pushButton, 3, 1, 1, 1);


        retranslateUi(GCodeSettings);

        QMetaObject::connectSlotsByName(GCodeSettings);
    } // setupUi

    void retranslateUi(QDialog *GCodeSettings)
    {
        GCodeSettings->setWindowTitle(QApplication::translate("GCodeSettings", "G-Code Settings", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("GCodeSettings", "Common Settings", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GCodeSettings", "z Clearance [mm]:", 0, QApplication::UnicodeUTF8));
        lineEdit_zClearance->setText(QApplication::translate("GCodeSettings", "0,5", 0, QApplication::UnicodeUTF8));
        checkBox_mirror->setText(QApplication::translate("GCodeSettings", "Mirror about y-Axis", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GCodeSettings", "Milling", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GCodeSettings", "Mill Feedrate [mm/s]:", 0, QApplication::UnicodeUTF8));
        lineEdit_millFeedrate->setText(QApplication::translate("GCodeSettings", "2", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GCodeSettings", "Plunge Feedrate [mm/s]:", 0, QApplication::UnicodeUTF8));
        lineEdit_millPlungeFeedrate->setText(QApplication::translate("GCodeSettings", "2", 0, QApplication::UnicodeUTF8));
        lineEdit_millDiameter->setText(QApplication::translate("GCodeSettings", "0,25", 0, QApplication::UnicodeUTF8));
        lineEdit_millZDepth->setText(QApplication::translate("GCodeSettings", "-0,150", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GCodeSettings", "Mill Diameter [mm]:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GCodeSettings", "z Depth [mm]:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("GCodeSettings", "Drilling", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GCodeSettings", "Plunge Feedrate [mm/s]:", 0, QApplication::UnicodeUTF8));
        lineEdit_drillPlungeFeedrate->setText(QApplication::translate("GCodeSettings", "2", 0, QApplication::UnicodeUTF8));
        lineEdit_drillDepth->setText(QApplication::translate("GCodeSettings", "-1,9", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("GCodeSettings", "Drill Depth [mm]:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("GCodeSettings", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GCodeSettings: public Ui_GCodeSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCODESETTINGS_H
