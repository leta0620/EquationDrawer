#pragma once
#include <QtWidgets/QWidget>
#include <QlistWidget>
<<<<<<< HEAD
=======
#include <QColorDialog>
#include <QEvent>
#include <QKeyEvent>
#include <string>
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
#include "ui_EquationBox.h"

class EquationBox : public QWidget
{
    Q_OBJECT

public:
    EquationBox(QWidget* parent = Q_NULLPTR);
    void SetListItem(QListWidgetItem*);
    void SetEquation(QString);
<<<<<<< HEAD
private slots:
    void on_pushButton_Visible_onclicked();
    void on_pushButton_Delete_onclicked();
private:
    Ui::Form ui;
    QListWidgetItem* listItem;
signals:
    void sendDel(QListWidgetItem*);
=======
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
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};
