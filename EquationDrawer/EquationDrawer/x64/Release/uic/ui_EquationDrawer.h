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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EquationDrawerClass
{
public:
    QListWidget *listWidget;
    QPushButton *pushButton_Draw;
    QPushButton *pushButton_Add;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *EquationDrawerClass)
    {
        if (EquationDrawerClass->objectName().isEmpty())
            EquationDrawerClass->setObjectName(QString::fromUtf8("EquationDrawerClass"));
        EquationDrawerClass->resize(1200, 800);
        listWidget = new QListWidget(EquationDrawerClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(830, 90, 351, 541));
        pushButton_Draw = new QPushButton(EquationDrawerClass);
        pushButton_Draw->setObjectName(QString::fromUtf8("pushButton_Draw"));
        pushButton_Draw->setGeometry(QRect(940, 710, 141, 61));
        QFont font;
        font.setPointSize(18);
        pushButton_Draw->setFont(font);
        pushButton_Add = new QPushButton(EquationDrawerClass);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));
        pushButton_Add->setGeometry(QRect(830, 10, 351, 71));
        QFont font1;
        font1.setPointSize(30);
        pushButton_Add->setFont(font1);
        textBrowser = new QTextBrowser(EquationDrawerClass);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(830, 640, 351, 61));
        QFont font2;
        font2.setPointSize(16);
        textBrowser->setFont(font2);

        retranslateUi(EquationDrawerClass);

        QMetaObject::connectSlotsByName(EquationDrawerClass);
    } // setupUi

    void retranslateUi(QWidget *EquationDrawerClass)
    {
        EquationDrawerClass->setWindowTitle(QCoreApplication::translate("EquationDrawerClass", "EquationDrawer", nullptr));
        pushButton_Draw->setText(QCoreApplication::translate("EquationDrawerClass", "\347\271\252\350\243\275", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("EquationDrawerClass", "\346\226\260\345\242\236", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("EquationDrawerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'PMingLiU'; font-size:16pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Test</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EquationDrawerClass: public Ui_EquationDrawerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUATIONDRAWER_H
