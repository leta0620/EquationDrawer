#include "EquationDrawer.h"

EquationDrawer::EquationDrawer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    center.setPos(0, 0);
    factor = 100;

    connect(ui.pushButton_Add, SIGNAL(clicked()), this, SLOT(on_pushButton_Add_onclicked()));
    connect(ui.pushButton_Draw, SIGNAL(clicked()), this, SLOT(on_pushButton_Draw_onclicked()));
    connect(ui.pushButton_Back, SIGNAL(clicked()), this, SLOT(on_pushButton_Back_onclicked()));
    connect(&inp, SIGNAL(sendInput(QString)), this, SLOT(receiveInput(QString)));

    QSize temp = ui.graphicsView->viewport()->size();
    ui.textBrowser->setText(QString::number(temp.width()));
    //scene.setSceneRect(0, 0, 800, 800);

    ui.graphicsView->viewport()->installEventFilter(this);
    ui.graphicsView->setSceneRect(0, 0, 800, 800);
    //ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

void EquationDrawer::on_pushButton_Back_onclicked()
{
    vector<string> equs;
    for (int a = 0; a < ui.listWidget->count(); a++)
    {
        QListWidgetItem* temp = ui.listWidget->item(a);
        EquationBox* tBox = dynamic_cast<EquationBox*> (ui.listWidget->itemWidget(temp));
        equs.push_back(tBox->GetEquation());
    }
    double lX = center.x - 400 / factor;
    double rX = center.x + 400 / factor;
    FuntionProcess fun(equs, lX, rX);
    vector<vector<Pos>> t = fun.GetDrawList();

    center.setPos(0, 0);
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
        if (numDegrees > 0)
        {
            factor *= 1.25;
            center.x += (wheelEvent->x() - 400) / factor * 0.5;
            center.y -= (wheelEvent->y() - 400) / factor * 0.5;
        }
        else if (numDegrees < 0)
        {
            factor *= 0.8;
        }



        paint();
        QString t = QString::number(center.x) + " , " + QString::number(center.y) + " factor: " + QString::number(factor);
        ui.textBrowser->setText(t);
        return true;
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

    drawLines();
    drawEquations();

    ui.graphicsView->setScene(&scene);
    ui.graphicsView->show();
}

void EquationDrawer::drawLines()
{
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
    /*
    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 8; b++)
        {
            Pos temp;
            temp = getPos(startX + a * 100, startY + b * 100);
            QString p = QString::number(temp.x) + " , " + QString::number(temp.y);
            QGraphicsTextItem* text = scene.addText(p);
            text->setPos(startX + a * 100, startY + b * 100);
            scene.addItem(text);
        }
    }*/
    Pos temp;
    int sta = 0, ed = 8;
    if (originX < 0)
        sta = 1;
    else if (originX > 800)
        ed = 7;
    for (int a = sta; a < ed; a++)
    {
        if (abs(startX + a * 100 - originX) > 0.000001)
        {
            temp = getPos(startX + a * 100, originY);
            QString p = QString::number(temp.x);
            QGraphicsTextItem* text = scene.addText(p);
            if (originY < 0)
                text->setPos(startX + a * 100, startY);
            else if (originY > 800)
                text->setPos(startX + a * 100, startY + 700);
            else
                text->setPos(startX + a * 100, originY);
            scene.addItem(text);
        }
    }
    sta = 0;
    ed = 8;
    if (originY < 0)
        sta = 1;
    else if (originY > 800)
        ed = 7;
    for (int a = sta; a < ed; a++)
    {
        if (abs(startY + a * 100 - originY) > 0.000001)
        {
            temp = getPos(originX, startY + a * 100);
            QString p = QString::number(temp.y);
            QGraphicsTextItem* text = scene.addText(p);
            if (originX < 0)
                text->setPos(startX, startY + a * 100);
            else if (originX > 800)
                text->setPos(startX + 700, startY + a * 100);
            else
                text->setPos(originX, startY + a * 100);
            scene.addItem(text);
        }
    }
}

void EquationDrawer::drawEquations()
{
    vector<string> equs;
    for (int a = 0; a < ui.listWidget->count(); a++)
    {
        QListWidgetItem *temp = ui.listWidget->item(a);
        EquationBox* tBox = dynamic_cast<EquationBox*> (ui.listWidget->itemWidget(temp));
        equs.push_back(tBox->GetEquation());
    }
    double lX = center.x - 400 / factor;
    double rX = center.x + 400 / factor;
    FuntionProcess fun(equs, lX, rX);
    vector<vector<Pos>> t = fun.GetDrawList();        
    for (int a = 0; a < ui.listWidget->count(); a++)
    {
        QListWidgetItem* temp = ui.listWidget->item(a);
        EquationBox* tBox = dynamic_cast<EquationBox*> (ui.listWidget->itemWidget(temp));
        tBox->setError(fun.GetErrorList()[a]);
    }
    for(int a=0;a<t.size();a++)
    {
        QPainterPath pathline;
        double prevY = 999;
        bool newline = true;
        for (int b = 0; b < t[a].size(); b++)
        {
            if (t[a][b].errorPos == false)
            {
                double x = (t[a][b].x - center.x) * factor + 400;
                double y = 800 - ((t[a][b].y - center.y) * factor + 400);                
                if (y <= 800)
                {
                    if (newline)
                    {
                        pathline.moveTo(QPointF(x, y));
                        newline = false;
                    }
                    else
                    {
                        pathline.lineTo(QPointF(x, y));
                    }
                }
                else if (b < t[a].size() - 1)
                {
                    double nextY = 800 - ((t[a][b + 1].y - center.y) * factor + 400);
                    if (prevY <= 800 && prevY >= 0)
                    {
                        pathline.lineTo(QPointF(x, 800));
                        newline = true;
                    }
                    if (nextY <= 800 && nextY >= 0)
                    {
                        pathline.moveTo(QPointF(x, 800));
                        newline = false;
                    }
                }
                prevY = y;
            }
            else
            {
                newline = true;
            }
        }

        //QPainterPath painterPath;
        //painterPath.addPolygon(polyline);
        //QGraphicsPolygonItem* eqline = scene.addPolygon(polyline);
        
        
        int toDrawIndex = fun.GetColorList()[a];
        QListWidgetItem* temp = ui.listWidget->item(toDrawIndex);
        EquationBox* tBox = dynamic_cast<EquationBox*> (ui.listWidget->itemWidget(temp));

        if(tBox->getVisible())
        { 
            QGraphicsPathItem* eqline = scene.addPath(pathline);
            QPen pen;
            pen.setColor(tBox->getColor());
            eqline->setPen(pen);
            scene.addItem(eqline);
            //scene.addPolygon(polyline);
        }
    }
}