#include "EquationDrawer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EquationDrawer w;
    w.show();
    //鎖定視窗大小
    w.setFixedSize(QSize(1200, 810));
    return a.exec();
}
