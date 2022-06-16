#pragma once

#include <QtWidgets/QWidget>
#include <QListWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>
#include <QEvent>
#include <QMouseEvent>
#include "ui_EquationDrawer.h"
#include "Pos.h"
#include "EquationBox.h"
#include "Input.h"
#include "MainFuntionProcess.h"

class EquationDrawer : public QWidget
{
    Q_OBJECT

public:
    EquationDrawer(QWidget *parent = Q_NULLPTR);
    Pos getPos(double, double);
private slots:
    void on_pushButton_Add_onclicked();
    void on_pushButton_Draw_onclicked();
    void on_pushButton_Back_onclicked();
    void receiveDel(QListWidgetItem*);
    void receiveInput(QString);
private:
    Ui::EquationDrawerClass ui;
    bool eventFilter(QObject* obj, QEvent* eve);
    void paint();
    void drawLines();
    void drawEquations();
    QGraphicsScene scene;
    double factor;
    Pos center;
    QPoint clickPos;
    Input inp;
};
