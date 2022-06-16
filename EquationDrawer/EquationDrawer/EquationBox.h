#pragma once
#include <QtWidgets/QWidget>
#include <QlistWidget>
#include <QColorDialog>
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
    QColor getColor();
    void setError(int);
private slots:
    void on_pushButton_Visible_onclicked();
    void on_pushButton_Delete_onclicked();
    void on_pushButton_Color_onclicked();
private:
    Ui::Form ui;
    QListWidgetItem* listItem;
    QColorDialog col;
    QColor selCol;
signals:
    void sendDel(QListWidgetItem*);
};
