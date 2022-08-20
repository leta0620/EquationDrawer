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
<<<<<<< HEAD
=======
#include "MainFuntionProcess.h"

>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
class EquationDrawer : public QWidget
{
    Q_OBJECT

public:
    EquationDrawer(QWidget *parent = Q_NULLPTR);
    Pos getPos(double, double);
private slots:
    void on_pushButton_Add_onclicked();
    void on_pushButton_Draw_onclicked();
<<<<<<< HEAD
    void receiveDel(QListWidgetItem*);
    void receiveInput(QString);
private:
    Ui::EquationDrawerClass ui;
    bool eventFilter(QObject* obj, QEvent* eve);
    void paint();
=======
    void on_pushButton_Back_onclicked();
    void receiveDel(QListWidgetItem*);
    void receiveInput(QString);
    void paint();
private:
    Ui::EquationDrawerClass ui;
    bool eventFilter(QObject* obj, QEvent* eve);
    void drawLines();
    void drawEquations();
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
    QGraphicsScene scene;
    double factor;
    Pos center;
    QPoint clickPos;
    Input inp;
};
