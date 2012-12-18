#include <QPainter>
#include <QTimer>
#include "canvas.h"

const int string_positions[6] = {0, -150, -75, 0, 75, 150};
const Qt::GlobalColor string_colors[6] = {Qt::black, Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::magenta};

const int window_height = 480;
const int window_width = 640;

Canvas::Canvas(QWidget *parent) : QWidget(parent),
    score(0), combo(0), combo_start(0), in_combo(false), elapsed(0), current_note(0), midi("")
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
    if (midi.notes[current_note].end)
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
    for (int i = current_note; midi.notes[i].start * 60 / midi.bpm * 1000 / division <= elapsed; ++i)
    {
        int duration = (midi.notes[i].end - midi.notes[i].start) / 3;
        int bottom = -window_height/2 + (elapsed - midi.notes[i].start * 60 / midi.bpm * 1000 / division) / 3;
        int top = bottom - duration;
        if (bottom >= window_height/2-100 && top <= window_height/2)
            onKey = true;
        else
            onKey = false;
        pen.setColor(Qt::white);
        if (onKey&& isPressing[midi.notes[i].key])
            pen.setColor(Qt::gray);
        painter->setPen(pen);
        painter->drawLine(string_positions[midi.notes[i].key], top,
                string_positions[midi.notes[i].key], bottom);
    }
//    if (midi.notes[current_note].end <= elapsed * midi.bpm / 1000 / 60)
//        ++current_note;
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

void Canvas::setPressing(int which, bool pressing)
{
    if (which >= 1 && which <= 5)
    {
        isPressing[which] = pressing;
    }
}

void Canvas::setMidi(Midi new_midi)
{
    midi = new_midi;
}

void Canvas::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    repaint();
}

