#include "EquationDrawer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EquationDrawer w;
    w.show();
    //��w�����j�p
    w.setFixedSize(QSize(1400, 810));
    return a.exec();
}
