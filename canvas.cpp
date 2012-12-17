#include <QPainter>
#include "canvas.h"

const int Heavy = -150;
const int Medium = -75;
const int MediumLight = 0;
const int Light = 75;
const int ExtraLight = 150;

const int window_height = 480;
const int window_width = 640;

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    for (int i = 1; i <= 5; ++i)
    {
        isPressing[i] = false;
    }
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setWindow(-window_width/2, -window_height/2, window_width, window_height);
    drawStrings(&painter);
    drawButtons(&painter);
}

void Canvas::drawStrings(QPainter *painter)
{
    QPen pen(Qt::green, 9, Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(Heavy, -window_height/2, Heavy, window_height/2);

    pen.setColor(Qt::red);
    pen.setWidth(8);
    painter->setPen(pen);
    painter->drawLine(Medium, -window_height/2, Medium, window_height/2);

    pen.setColor(Qt::yellow);
    pen.setWidth(7);
    painter->setPen(pen);
    painter->drawLine(MediumLight, -window_height/2, MediumLight, window_height/2);

    pen.setColor(Qt::blue);
    pen.setWidth(6);
    painter->setPen(pen);
    painter->drawLine(Light, -window_height/2, Light, window_height/2);

    pen.setColor(Qt::magenta);
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawLine(ExtraLight, -window_height/2, ExtraLight, window_height/2);
}

void Canvas::drawButtons(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap);
    QBrush brush(Qt::green, Qt::SolidPattern);

    int colors[6] = {0, Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::magenta};
    for (int i = 1; i <= 5; ++i)
    {
        if (isPressing[i])
        {
            pen.setColor(Qt::gray);
        }
        else
        {
            pen.setColor(Qt::white);
        }
        brush.setColor(colors[i]);
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawEllipse(-250 + 75 * i, window_height/2-100, 50, 50);
    }
}

void Canvas::setPressing(int which, bool pressing)
{
    if (which >= 1 && which <= 5)
    {
        isPressing[which] = pressing;
    }
}
