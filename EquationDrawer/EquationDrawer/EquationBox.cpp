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

    isVisible = true;

    ui.textEdit->installEventFilter(this);
}

void EquationBox::on_pushButton_Visible_onclicked()
{
    if (isVisible)
    {
        ui.pushButton_Visible->setText(QString::fromLocal8Bit("不可見"));
        isVisible = false;
    }
    else
    {
        ui.pushButton_Visible->setText(QString::fromLocal8Bit("可見"));
        isVisible = true;
    }
    emit reDraw();
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
    emit reDraw();
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
        ui.label->setText("Error!");
}

QColor EquationBox::getColor()
{
    return selCol;
}

bool EquationBox::getVisible()
{
    return isVisible;
}

bool EquationBox::eventFilter(QObject* obj, QEvent* eve)
{
    if (eve->type() == QEvent::KeyPress)
    {
        //若事件為按鍵 將事件轉換為按鍵事件
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(eve);

        //檢查是否按下ENTER(兩個ENTER都算)
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            emit reDraw();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QWidget::eventFilter(obj, eve);
    }
}