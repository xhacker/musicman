#include <QPainter>
#include "canvas.h"

const int string_positions[6] = {0, -150, -75, 0, 75, 150};
const Qt::GlobalColor string_colors[6] = {Qt::black, Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::magenta};

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
    QPen pen(Qt::black, 10, Qt::SolidLine);
    for (int i = 1; i <= 5; ++i)
    {
        pen.setColor(string_colors[i]);
        pen.setWidth(10 - i);
        painter->setPen(pen);
        painter->drawLine(string_positions[i], -window_height/2, string_positions[i], window_height/2);
    }
}

void Canvas::drawButtons(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap);
    QBrush brush(Qt::black, Qt::SolidPattern);

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
        brush.setColor(string_colors[i]);
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawEllipse(string_positions[i] - 25, window_height/2-100, 50, 50);
    }
}

void Canvas::setPressing(int which, bool pressing)
{
    if (which >= 1 && which <= 5)
    {
        isPressing[which] = pressing;
    }
}
