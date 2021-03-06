#pragma once
#include <QtWidgets/QWidget>
#include <QlistWidget>
#include <QColorDialog>
#include <QEvent>
#include <QKeyEvent>
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
    bool getVisible();
private slots:
    void on_pushButton_Visible_onclicked();
    void on_pushButton_Delete_onclicked();
    void on_pushButton_Color_onclicked();
private:
    bool eventFilter(QObject* obj, QEvent* eve);
    Ui::Form ui;
    QListWidgetItem* listItem;
    QColorDialog col;
    QColor selCol;
    bool isVisible;
signals:
    void sendDel(QListWidgetItem*);
    void reDraw();
};
