#pragma once
#include "ui_Input.h"
#include <QtWidgets/QWidget>

class Input : public QDialog
{
    Q_OBJECT

public:
    Input(QDialog* parent = Q_NULLPTR);
private slots:
    void on_pushButton_Enter_onclicked();
private:
    Ui::Dialog ui;
signals:
    void sendInput(QString);
};