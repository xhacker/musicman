#include <QPainter>
#include <QTimer>
#include "canvas.h"

const int string_positions[6] = {0, -150, -75, 0, 75, 150};
const Qt::GlobalColor string_colors[6] = {Qt::black, Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::magenta};

const int window_height = 480;
const int window_width = 640;

Note notes[200] =
{
    {1, 0, 450},
    {2, 480, 930},
    {3, 960, 1410},
    {1, 1440, 2370},
    {2, 2400, 2850},
    {3, 2880, 3330},
    {1, 3360, 4290},
    {2, 4320, 4770},
    {3, 4800, 5250},
    {1, 528, 621},
    {2, 624, 669},
    {3, 672, 717},
    {1, 720, 765},
    {2, 768, 813},
    {3, 816, 861},
    {4, 864, 909},
    {4, 1056, 1101},
    {4, 1248, 1293},
    {4, 1440, 1485},
    {4, 2016, 2061}
};

//void Canvas::setNotes(Note **notes_input)
//{
//    notes = notes_input;
//}

Canvas::Canvas(QWidget *parent) : QWidget(parent), score(0), combo(0), combo_start(0), in_combo(false), elapsed(0), current_note(0)
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
    painter.setRenderHint(QPainter::Antialiasing);
    drawScore(&painter);
    drawStrings(&painter);
    drawBars(&painter);
    drawButtons(&painter);
    if (isPressing[5] && !in_combo)
    {
        combo += 1;
        in_combo = true;
        combo_start = elapsed;
    }
    if ((elapsed - combo_start) >= 255)
        in_combo = false;
    if (in_combo)
        drawCombos(&painter);
}

void Canvas::drawScore(QPainter *painter)
{
    QPen pen(Qt::black, 2);
    QFont font;
    font.setPixelSize(20);
//    font.setFamily("");
    painter->setPen(pen);
    painter->setFont(font);
    for (int i = 1; i <= 5; ++i)
        if (isPressing[i])
            score += 10;
    char score_text[20];
    sprintf(score_text, "Score: %d", score);
    painter->drawText(-window_width/2 + 30, -window_height/2 + 50, score_text);
}

void Canvas::drawStrings(QPainter *painter)
{
    QPen pen(Qt::black, 10, Qt::SolidLine);
    for (int i = 1; i <= 5; ++i)
    {
        pen.setColor(Qt::gray);
        pen.setWidth(6 - i);
        painter->setPen(pen);
        painter->drawLine(string_positions[i] + (10-i)/2, -window_height/2, string_positions[i] + (10-i)/2, window_height/2);

        pen.setColor(string_colors[i]);
        pen.setWidth(10 - i);
        painter->setPen(pen);
        painter->drawLine(string_positions[i], -window_height/2, string_positions[i], window_height/2);
    }
}

void Canvas::drawButtons(QPainter *painter)
{
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

void Canvas::drawBars(QPainter *painter)
{
    QPen pen(Qt::white, 40, Qt::SolidLine, Qt::RoundCap);
    bool onKey = false;
    for (int i = current_note; notes[i].start <= elapsed + 100; ++i)
    {
        int duration = (notes[i].end - notes[i].start)/10;
        int bottom = -window_height/2 + elapsed / 10 - notes[i].start / 10;
        int top = bottom - duration;
        if (bottom >= window_height/2-100 && top <= window_height/2)
            onKey = true;
        else
            onKey = false;
        pen.setColor(Qt::white);
        if (onKey&& isPressing[notes[i].key])
            pen.setColor(Qt::gray);
        painter->setPen(pen);
        painter->drawLine(string_positions[notes[i].key], top,
                string_positions[notes[i].key], bottom);

    }
}

void Canvas::setPressing(int which, bool pressing)
{
    if (which >= 1 && which <= 5)
    {
        isPressing[which] = pressing;
    }
}

void Canvas::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    repaint();
}

void Canvas::drawCombos(QPainter *painter)
{
    QPen pen(QColor(255, 0, 0, 255 - (elapsed-combo_start)));
    QBrush brush(QColor(0, 0, 0, 0));
    QFont font;
    font.setPixelSize(50 + (elapsed-combo_start));
//    font.setFamily("");
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->setFont(font);
    char combo_text[20];
    sprintf(combo_text, "Combo x %d", combo);
    painter->drawText(QRect(-window_width/2, -window_height/2, window_width, window_height), Qt::AlignCenter, combo_text);
}
