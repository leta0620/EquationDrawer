#pragma once
#include <QtWidgets/QWidget>
#include <QlistWidget>
#include <string>
#include "ui_EquationBox.h"

class EquationBox : public QWidget
{
    Q_OBJECT

public:
    EquationBox(QWidget* parent = Q_NULLPTR);
    void SetListItem(QListWidgetItem*);
    void SetEquation(QString);
    std::string GetEquation();
private slots:
    void on_pushButton_Visible_onclicked();
    void on_pushButton_Delete_onclicked();
private:
    Ui::Form ui;
    QListWidgetItem* listItem;
signals:
    void sendDel(QListWidgetItem*);
};
