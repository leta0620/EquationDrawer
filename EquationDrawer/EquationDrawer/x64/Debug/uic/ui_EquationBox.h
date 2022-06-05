/********************************************************************************
** Form generated from reading UI file 'EquationBox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUATIONBOX_H
#define UI_EQUATIONBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton_Visible;
    QPushButton *pushButton_Change;
    QPushButton *pushButton_Delete;
    QTextEdit *textEdit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(351, 41);
        pushButton_Visible = new QPushButton(Form);
        pushButton_Visible->setObjectName(QString::fromUtf8("pushButton_Visible"));
        pushButton_Visible->setGeometry(QRect(230, 0, 41, 41));
        pushButton_Change = new QPushButton(Form);
        pushButton_Change->setObjectName(QString::fromUtf8("pushButton_Change"));
        pushButton_Change->setGeometry(QRect(270, 0, 41, 41));
        pushButton_Delete = new QPushButton(Form);
        pushButton_Delete->setObjectName(QString::fromUtf8("pushButton_Delete"));
        pushButton_Delete->setGeometry(QRect(310, 0, 41, 41));
        textEdit = new QTextEdit(Form);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 231, 41));
        QFont font;
        font.setPointSize(18);
        textEdit->setFont(font);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton_Visible->setText(QCoreApplication::translate("Form", "\345\217\257\350\246\213", nullptr));
        pushButton_Change->setText(QCoreApplication::translate("Form", "\344\277\256\346\224\271", nullptr));
        pushButton_Delete->setText(QCoreApplication::translate("Form", "\345\210\252\351\231\244", nullptr));
        textEdit->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'PMingLiU'; font-size:18pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Test</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUATIONBOX_H
