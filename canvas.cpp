#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <mainwindow.h>
#include "canvas.h"

const int string_positions[6] = {0, -150, -75, 0, 75, 150};
const Qt::GlobalColor string_colors[6] = {Qt::black, Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::magenta};

const int window_height = 600;
const int window_width = 800;

const int combo_max = 20;

Canvas::Canvas(QWidget *parent) : QWidget(parent),
    score(0), combo(0), combo_start(0), elapsed(0),
    showing_combo(false), current_note(0),
    inarow_count(0), midi("")
{
    starttime.start();
    for (int i = 1; i <= 5; ++i)
    {
        isPressing[i] = false;
    }
    setFocus();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setWindow(-window_width/2, -window_height/2, window_width, window_height);
    painter.setRenderHint(QPainter::Antialiasing);
    drawScore(&painter);
    drawDebug(&painter);
    drawStrings(&painter);
    if (midi.notes[current_note].end)
        drawBars(&painter);
    drawButtons(&painter);

    if ((elapsed - combo_start) >= 255 * 2)
        showing_combo = false;
    if (showing_combo)
        drawCombos(&painter);
}

void Canvas::drawScore(QPainter *painter)
{
    QPen pen(Qt::black, 2);
    QFont font;
    font.setPixelSize(20);
    font.setFamily("Gill Sans");
    painter->setPen(pen);
    painter->setFont(font);
    char score_text[20];
    sprintf(score_text, "Score: %d", score);
    painter->drawText(-window_width/2 + 30, -window_height/2 + 50, score_text);
}

void Canvas::drawDebug(QPainter *painter)
{
    QPen pen(Qt::black, 2);
    QFont font;
    font.setPixelSize(12);
    font.setFamily("Menlo");
    painter->setPen(pen);
    painter->setFont(font);
    char debug_text_1[20], debug_text_2[20], debug_text_3[20], debug_text_4[20];
    sprintf(debug_text_1, "In a Row:\t%d", inarow_count);
    sprintf(debug_text_2, "Combo:\t%d", combo);
    sprintf(debug_text_3, "Elapsed:\t%d", elapsed);
    sprintf(debug_text_4, "Curnote:\t%d", current_note);
    const int y = 100;
    const int line_height = 20;
    painter->drawText(-window_width/2 + 30, -window_height/2 + y, debug_text_1);
    painter->drawText(-window_width/2 + 30, -window_height/2 + y + line_height, debug_text_2);
    painter->drawText(-window_width/2 + 30, -window_height/2 + y + line_height * 2, debug_text_3);
    painter->drawText(-window_width/2 + 30, -window_height/2 + y + line_height * 3, debug_text_4);
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
    QPen pen(Qt::white, 32, Qt::SolidLine, Qt::RoundCap);
    bool onKey = false;
    for (int i = current_note; midi.notes[i].start * 60 / midi.bpm * 1000 / division <= elapsed + 1000; ++i)
    {
        int duration = (midi.notes[i].end - midi.notes[i].start) / 5;
        int bottom = -window_height / 2 + (elapsed - midi.notes[i].start * 60 / midi.bpm * 1000 / division) / 5;
        int top = bottom - duration;
        if (bottom >= window_height / 2 - 100 && top <= window_height / 2 - 50)
            onKey = true;
        else
            onKey = false;
        pen.setColor(Qt::white);
        if (onKey)
        {
            if (isPressing[midi.notes[i].key])
            {
                pen.setColor(Qt::gray);
                if (!midi.notes[i].pressed())
                {
                    midi.notes[i].setPressed(true);
                    inarow_count += 1;
                    if (inarow_count >= 8 && inarow_count % 8 == 0 &&
                            combo < combo_max && !showing_combo)
                    {
                        combo += 1;
                        showing_combo = true;
                        combo_start = elapsed;
                    }
                }
                score += 10 * (combo + 1);
            }
            else
            {
            }
        }
        painter->setPen(pen);
        painter->drawLine(string_positions[midi.notes[i].key], top,
                string_positions[midi.notes[i].key], bottom);
        if (top > window_height/2 - 50)
        {
            if (!midi.notes[current_note].pressed())
            {
                inarow_count = 0;
                combo = 0;
    //            play_guile_sound();
            }
            current_note += 1;
        }
    }
}

void Canvas::drawCombos(QPainter *painter)
{
    QPen pen(QColor(255, 0, 0, 255 - ((elapsed - combo_start) / 2)));
    QBrush brush(QColor(0, 0, 0, 0));
    QFont font;
    font.setPixelSize(50 + ((elapsed - combo_start) / 2));
    font.setFamily("Gill Sans");
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
    elapsed = starttime.elapsed();
    repaint();
    if (elapsed >= 2400) ((MainWindow *)parent())->play();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
   if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_5)
   {
       int key_no = event->key() - Qt::Key_1 + 1;
       setPressing(key_no, true);
   }
//   if (canvas->isGood())
//       music_song_output->setMuted(false);
//   else
//       music_song_output->setMuted(true);
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
   if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_5)
   {
       setPressing(event->key() - Qt::Key_1 + 1, false);
   }
//   if (canvas->isGood())
//       music_song_output->setMuted(false);
//   else
//       music_song_output->setMuted(true);
}

