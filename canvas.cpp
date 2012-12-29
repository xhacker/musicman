#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <mainwindow.h>
#include "canvas.h"

const Qt::GlobalColor string_colors[6] = {Qt::black, Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::magenta};

const int combo_max = 20;

Canvas::Canvas(QWidget *parent) : QWidget(parent),
    score(0), elapsed(0), combo(0), combo_start(0),
    inarow_count(0), showing_combo(false),
    current_note(0), midi("")
{
    starttime.start();
    for (int i = 1; i <= 5; ++i)
    {
        isPressing[i] = false;
    }
    setFocus();
}

int Canvas::wtop() const
{
    return - window_height / 2;
}

int Canvas::wbottom() const
{
    return window_height / 2;
}

int Canvas::wleft() const
{
    return - window_width / 2;
}

int Canvas::wright() const
{
    return window_width / 2;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    resize(((MainWindow *)parent())->size());
    window_width = size().width();
    window_height = size().height();
    int w = window_width / 10;
    for (int i = 1; i <= 5; ++i)
        string_positions[i] = (-3 + i) * w;
    painter.setWindow(wleft(), wtop(), window_width, window_height);
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
    char score_text[20];
    sprintf(score_text, "Score: %d", score);
    drawText(painter, Qt::black, score_text, 20, "Gill Sans", wleft() + 30, wtop() + 50);
}

void Canvas::drawDebug(QPainter *painter)
{
    char debug_text[5][30];
    sprintf(debug_text[0], "In a Row:\t%d", inarow_count);
    sprintf(debug_text[1], "Combo:\t%d", combo);
    sprintf(debug_text[2], "Elapsed:\t%d", elapsed);
    sprintf(debug_text[3], "Curnote:\t%d", current_note);
    const int y = 100;
    const int line_height = 20;
    for (int i = 0; i < 4; ++i)
        drawText(painter, Qt::black, debug_text[i], 12, "Menlo", wleft() + 30, wtop() + y + line_height*i);
}

void Canvas::drawStrings(QPainter *painter)
{
    QPen pen(Qt::black, 10, Qt::SolidLine);
    for (int i = 1; i <= 5; ++i)
    {
        pen.setColor(Qt::gray);
        pen.setWidth(6 - i);
        painter->setPen(pen);
        painter->drawLine(string_positions[i] + (10-i)/2, wtop(), string_positions[i] + (10-i)/2, wbottom());

        pen.setColor(string_colors[i]);
        pen.setWidth(10 - i);
        painter->setPen(pen);
        painter->drawLine(string_positions[i], wtop(), string_positions[i], wbottom());
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
        painter->drawEllipse(string_positions[i] - 25, window_height / 2 - 100, 50, 50);
    }
}

void Canvas::drawBars(QPainter *painter)
{
    QPen pen(Qt::white, 32, Qt::SolidLine, Qt::RoundCap);
    bool onKey = false;

    for (int i = current_note; midi.notes[i].start * 60 / midi.bpm * 1000 / division <= elapsed + 1000; ++i)
    {
        int duration = (midi.notes[i].end - midi.notes[i].start) / 5;
        int note_bottom = -window_height / 2 + (elapsed - midi.notes[i].start * 60 / midi.bpm * 1000 / division) / 5;
        int note_top = note_bottom - duration;
        if (note_bottom >= window_height / 2 - 100 && note_top <= window_height / 2 - 45)
            onKey = true;
        else
            onKey = false;
        pen.setColor(Qt::white);
        if (onKey)
        {
            if (isPressing[midi.notes[i].key])
            {
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
        }
        if (midi.notes[i].pressed())
        {
            pen.setColor(Qt::gray);
        }
        painter->setPen(pen);
        painter->drawLine(string_positions[midi.notes[i].key], note_top,
                string_positions[midi.notes[i].key], note_bottom);
        if (note_top > window_height/2)
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
    char combo_text[40];
    sprintf(combo_text, "Combo x %d", combo);
    drawText(painter, QColor(255, 0, 0, 255-((elapsed - combo_start) / 2)), combo_text, 50+((elapsed - combo_start) / 2), "Gill Sans", wleft(), wtop(), window_width, window_height);
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

bool Canvas::isGood() const
{
    // TODO
    return true;
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

void Canvas::drawEnd(QPainter *painter)
{
    char score_text[40];
    sprintf(score_text, "Your Score: %d", score);
    drawText(painter, QColor(0, 255, 0, 255), score_text, 50, "Gill Sans", -window_width/2, -window_height/2, window_width, window_height);
}

void Canvas::drawText(QPainter*& painter, const QColor& word_color, const char text[], const int& fontSize, const char fontName[], const int& top_left_x, const int& top_left_y, const int& width, const int& height)
{
    QPen pen(word_color, 2);
    QBrush brush(QColor(0, 0, 0, 0));
    QFont font;
    font.setPixelSize(fontSize);
    font.setFamily(fontName);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->setFont(font);
    painter->drawText(QRect(top_left_x, top_left_y, width, height), Qt::AlignCenter, text);
}

void Canvas::drawText(QPainter *&painter, const QColor &word_color, const char text[], const int &fontSize, const char fontName[], const int &top_left_x, const int &top_left_y)
{
    QPen pen(word_color, 2);
    QFont font;
    font.setPixelSize(fontSize);
    font.setFamily(fontName);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(top_left_x, top_left_y, text);
}
