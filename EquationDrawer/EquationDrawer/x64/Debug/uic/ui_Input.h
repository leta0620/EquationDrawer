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
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButton_Enter;
    QTextEdit *textEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 83);
        pushButton_Enter = new QPushButton(Dialog);
        pushButton_Enter->setObjectName(QString::fromUtf8("pushButton_Enter"));
        pushButton_Enter->setGeometry(QRect(140, 40, 121, 41));
        QFont font;
        font.setPointSize(16);
        pushButton_Enter->setFont(font);
        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 0, 381, 41));
        textEdit->setFont(font);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton_Enter->setText(QCoreApplication::translate("Dialog", "\347\242\272\350\252\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_H
