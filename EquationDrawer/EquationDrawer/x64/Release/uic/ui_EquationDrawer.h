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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EquationDrawerClass
{
public:

    void setupUi(QWidget *EquationDrawerClass)
    {
        if (EquationDrawerClass->objectName().isEmpty())
            EquationDrawerClass->setObjectName(QString::fromUtf8("EquationDrawerClass"));
        EquationDrawerClass->resize(600, 400);

        retranslateUi(EquationDrawerClass);

        QMetaObject::connectSlotsByName(EquationDrawerClass);
    } // setupUi

    void retranslateUi(QWidget *EquationDrawerClass)
    {
        EquationDrawerClass->setWindowTitle(QCoreApplication::translate("EquationDrawerClass", "EquationDrawer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EquationDrawerClass: public Ui_EquationDrawerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUATIONDRAWER_H
