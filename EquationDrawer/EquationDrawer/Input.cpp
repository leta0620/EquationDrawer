#include "Input.h"

Input::Input(QDialog* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton_Enter, SIGNAL(clicked()), this, SLOT(on_pushButton_Enter_onclicked()));
}

void Input::on_pushButton_Enter_onclicked()
{
    QString temp = ui.textEdit->toPlainText();
    ui.textEdit->clear();
    emit sendInput(temp);
}