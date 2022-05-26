#pragma once

#include <QtWidgets/QWidget>
#include "ui_EquationDrawer.h"

class EquationDrawer : public QWidget
{
    Q_OBJECT

public:
    EquationDrawer(QWidget *parent = Q_NULLPTR);

private:
    Ui::EquationDrawerClass ui;
};
