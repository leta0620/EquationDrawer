#include "EquationBox.h"

EquationBox::EquationBox(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton_Visible, SIGNAL(clicked()), this, SLOT(on_pushButton_Visible_onclicked()));
    connect(ui.pushButton_Delete, SIGNAL(clicked()), this, SLOT(on_pushButton_Delete_onclicked()));
}

void EquationBox::on_pushButton_Visible_onclicked()
{
    ui.textEdit->setText("gg");
}

void EquationBox::on_pushButton_Delete_onclicked()
{
    emit sendDel(listItem);
}

void EquationBox::SetListItem(QListWidgetItem* item)
{
    listItem = item;
}

void EquationBox::SetEquation(QString str)
{
    ui.textEdit->setText(str);
}

