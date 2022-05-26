/********************************************************************************
** Form generated from reading UI file 'EquationDrawer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUATIONDRAWER_H
#define UI_EQUATIONDRAWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EquationDrawerClass
{
public:
    QListWidget *listWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *EquationDrawerClass)
    {
        if (EquationDrawerClass->objectName().isEmpty())
            EquationDrawerClass->setObjectName(QString::fromUtf8("EquationDrawerClass"));
        EquationDrawerClass->resize(1200, 800);
        listWidget = new QListWidget(EquationDrawerClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(830, 90, 351, 541));
        pushButton = new QPushButton(EquationDrawerClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(940, 710, 141, 61));
        QFont font;
        font.setPointSize(18);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(EquationDrawerClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(830, 10, 351, 71));
        QFont font1;
        font1.setPointSize(30);
        pushButton_2->setFont(font1);

        retranslateUi(EquationDrawerClass);

        QMetaObject::connectSlotsByName(EquationDrawerClass);
    } // setupUi

    void retranslateUi(QWidget *EquationDrawerClass)
    {
        EquationDrawerClass->setWindowTitle(QCoreApplication::translate("EquationDrawerClass", "EquationDrawer", nullptr));
        pushButton->setText(QCoreApplication::translate("EquationDrawerClass", "\347\271\252\350\243\275", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EquationDrawerClass", "\346\226\260\345\242\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EquationDrawerClass: public Ui_EquationDrawerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUATIONDRAWER_H
