#include "EquationBox.h"

EquationBox::EquationBox(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton_Visible, SIGNAL(clicked()), this, SLOT(on_pushButton_Visible_onclicked()));
    connect(ui.pushButton_Delete, SIGNAL(clicked()), this, SLOT(on_pushButton_Delete_onclicked()));
    connect(ui.pushButton_Color, SIGNAL(clicked()), this, SLOT(on_pushButton_Color_onclicked()));

    selCol = QColor(0, 0, 0);
    QString temp = "background-color: " + selCol.name();
    ui.pushButton_Color->setStyleSheet(temp);
}

void EquationBox::on_pushButton_Visible_onclicked()
{
    ui.textEdit->setText("gg");
}

void EquationBox::on_pushButton_Delete_onclicked()
{
    emit sendDel(listItem);
}

void EquationBox::on_pushButton_Color_onclicked()
{
    selCol = col.getColor();
    QString temp = "background-color: " + selCol.name();
    ui.pushButton_Color->setStyleSheet(temp);
}

void EquationBox::SetListItem(QListWidgetItem* item)
{
    listItem = item;
}

void EquationBox::SetEquation(QString str)
{
    ui.textEdit->setText(str);
}

std::string EquationBox::GetEquation()
{
    QString temp = ui.textEdit->toPlainText();
    return temp.toStdString();
}
void EquationBox::setError(int err)
{
    if (err == 0)
    {
        ui.label->setText("No Error");
    }
    else
        ui.label->setText(QString::number(err));
}
