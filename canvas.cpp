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

void drawButtons(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap);
    QBrush brush(Qt::green, Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(Heavy, window_height-100, 50, 50);

    brush.setColor(Qt::red);
    painter->setBrush(brush);
    painter->drawEllipse(Medium, window_height-100, 50, 50);

    brush.setColor(Qt::yellow);
    painter->setBrush(brush);
    painter->drawEllipse(MediumLight, window_height-100, 50, 50);

    brush.setColor(Qt::blue);
    painter->setBrush(brush);
    painter->drawEllipse(Light, window_height-100, 50, 50);

    brush.setColor(Qt::magenta);
    painter->setBrush(brush);
    painter->drawEllipse(ExtraLight, window_height-100, 50, 50);

}
