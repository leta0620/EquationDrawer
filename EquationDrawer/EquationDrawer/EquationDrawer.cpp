#include "EquationDrawer.h"

EquationDrawer::EquationDrawer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    center.setPos(2.5, 3.7);
    factor = 100;

    connect(ui.pushButton_Add, SIGNAL(clicked()), this, SLOT(on_pushButton_Add_onclicked()));
    connect(ui.pushButton_Draw, SIGNAL(clicked()), this, SLOT(on_pushButton_Draw_onclicked()));
    connect(&inp, SIGNAL(sendInput(QString)), this, SLOT(receiveInput(QString)));

    QSize temp = ui.graphicsView->viewport()->size();
    ui.textBrowser->setText(QString::number(temp.width()));
    scene.setSceneRect(0, 0, 800, 800);
    ui.graphicsView->viewport()->installEventFilter(this);
}

void EquationDrawer::on_pushButton_Add_onclicked()
{
    inp.show();
}

void EquationDrawer::on_pushButton_Draw_onclicked()
{
    center.setPos(0, 0);
    factor = 100;
    paint();
}

void EquationDrawer::receiveDel(QListWidgetItem* toDelete)
{
    QListWidgetItem* item = toDelete;
    ui.listWidget->removeItemWidget(item);
    delete item;
}

void EquationDrawer::receiveInput(QString toInput)
{
    EquationBox *itemWidget = new EquationBox;
    QListWidgetItem *item = new QListWidgetItem;

    itemWidget->SetListItem(item);
    itemWidget->SetEquation(toInput);
    connect(itemWidget, SIGNAL(sendDel(QListWidgetItem*)), this, SLOT(receiveDel(QListWidgetItem*)));

    item->setSizeHint(QSize(301, 41));

    ui.listWidget->addItem(item);
    ui.listWidget->setItemWidget(item, itemWidget);
    ui.textBrowser->setText(QString::number(ui.listWidget->count()));
    inp.close();
}

//事件過濾器
bool EquationDrawer::eventFilter(QObject* obj, QEvent* eve)
{
    //滑鼠點擊
    if (eve->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(eve);
        QString temp = QString::number(mouseEvent->x()) + " " + QString::number(mouseEvent->y()) + " ";
        clickPos = mouseEvent->pos();
        ui.textBrowser->setText(temp);
        return true;
    }
    else if (eve->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(eve);
        if (mouseEvent->buttons())
        {
            QString temp = QString::number(mouseEvent->x()) + " " + QString::number(mouseEvent->y()) + " ";
            QPoint toPos = mouseEvent->pos();
            center.x -= (toPos.x() - clickPos.x()) / factor;
            center.y += (toPos.y() - clickPos.y()) / factor;
            clickPos = toPos;
            paint();
        }
        return true;
    }
    else if (eve->type() == QEvent::Wheel)
    {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(eve);
        int numDegrees = wheelEvent->angleDelta().y();
        //ui.textBrowser->setText(QString::number(numDegrees));
        if (numDegrees > 0)
            factor *= 1.1;
        if (numDegrees < 0)
            factor *= 0.9;
        paint();
    }
    else
    {
        return QWidget::eventFilter(obj, eve);
    }
}

Pos EquationDrawer::getPos(double onBoardX, double onBoardY)
{
    Pos temp;
    temp.setPos((onBoardX - 400) / factor + center.x, (onBoardY - 400) / factor * -1 + center.y);
    return temp;
}

void EquationDrawer::paint()
{
    scene.clear();
    ui.graphicsView->viewport()->update();
    Pos start;
    Pos origin;
    start.setPos(0, 0);
    origin.setPos(0, 0);
    double startX, startY;
    Pos leftUp;
    leftUp = getPos(0, 0);
    if (start.x > leftUp.x)
    {
        while (start.x > leftUp.x)
        {
            start.x -= 100 / factor;
        }
        start.x += 100 / factor;
    }
    else if (start.x < leftUp.x)
    {
        while (start.x < leftUp.x)
        {
            start.x += 100 / factor;
        }
        start.x -= 100 / factor;
    }
    if (start.y > leftUp.y)
    {
        while (start.y > leftUp.y)
        {
            start.y -= 100 / factor;
        }
        start.y += 100 / factor;
    }
    else if (start.y < leftUp.y)
    {
        while (start.y < leftUp.y)
        {
            start.y += 100 / factor;
        }
        start.y -= 100 / factor;
    }
    startX = (start.x - center.x) * factor + 400;
    startY = (start.y - center.y) * factor + 400;
    startY = 800 - startY;
    QPen pen;
    pen.setWidth(5);
    double originX = (origin.x - center.x) * factor + 400;
    double originY = (origin.y - center.y) * factor + 400;
    originY = 800 - originY;
    if (originX <= 800 && originX >= 0)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem;
        line->setLine(originX, 0, originX, 800);
        line->setPen(pen);
        scene.addItem(line);
    }
    if (originY <= 800 && originY >= 0)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem;
        line->setLine(0, originY, 800, originY);
        line->setPen(pen);
        scene.addItem(line);
    }
    while (startX < 800)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem;
        line->setLine(startX, 0, startX, 800);
        scene.addItem(line);
        startX += 100;
    }
    while (startY < 800)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem;
        line->setLine(0, startY, 800, startY);
        scene.addItem(line);
        startY += 100;
    }
    startX -= 800;
    startY -= 800;
    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 8; b++)
        {
            Pos temp;
            temp = getPos(startX + a * 100, startY + b * 100);
            //if (temp.x == origin.x || temp.y == origin.y)
            //{
            QString p = QString::number(temp.x) + " , " + QString::number(temp.y);
            QGraphicsTextItem* text = scene.addText(p);
            text->setPos(startX + a * 100, startY + b * 100);
            scene.addItem(text);
            //}
        }
    }
    ui.graphicsView->setScene(&scene);
    ui.graphicsView->show();
}