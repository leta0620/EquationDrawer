/********************************************************************************
** Form generated from reading UI file 'Input.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUT_H
#define UI_INPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTextBrowser *textBrowser;
    QPushButton *pushButton_Enter;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 83);
        textBrowser = new QTextBrowser(Dialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 0, 381, 41));
        pushButton_Enter = new QPushButton(Dialog);
        pushButton_Enter->setObjectName(QString::fromUtf8("pushButton_Enter"));
        pushButton_Enter->setGeometry(QRect(140, 40, 121, 41));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton_Enter->setText(QCoreApplication::translate("Dialog", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_H
