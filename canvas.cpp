#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include "mainwindow.h"
#include "canvas.h"

const Qt::GlobalColor string_colors[6] = {Qt::black, Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::magenta};

const int combo_max = 4;
const int combo_inarow = 10;
const int press_threshold = 250;
const int nopick_threshold = 250;
const double guile_vol = 0.4;
const int once_upon_a_time = -1314;

Canvas::Canvas(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    is_picking(false),
    last_picking(once_upon_a_time),
    real_elapsed(0),
    last_good(once_upon_a_time),
    finished(false),
    current_note(0),
    score(0),
    is_good(true),
    combo(1),
    showing_combo(false),
    combo_start(0),
    inarow_count(0),
    midi("")
{
    start_time.start();
    for (int i = 1; i <= 5; ++i)
    {
        is_pressing[i] = false;
        last_pressing[i] = once_upon_a_time;
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

void Canvas::setTotalTime(int t)
{
    total_time = t;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    resize(((MainWindow *)parent())->size());
    window_width = size().width();
    window_height = size().height();
    painter.setWindow(wleft(), wtop(), window_width, window_height);
    int w = 30 + window_width / 20;
    for (int i = 1; i <= 5; ++i)
        string_positions[i] = (-3 + i) * w;

    if (elapsed() <= total_time)
    {
        drawScore(&painter);
        drawDebug(&painter);
        drawStrings(&painter);
        if (midi.notes[current_note].end)
            drawBars(&painter);
        drawButtons(&painter);

        if ((elapsed() - combo_start) >= 255 * 3)
            showing_combo = false;
        if (showing_combo)
            drawCombos(&painter);
    }
    else
    {
        drawEnd(&painter);
    }
}

void Canvas::drawScore(QPainter *painter)
{
    drawText(painter, Qt::black, QString("Score: %1").arg(score), 20, "Gill Sans",
             wleft() + 30, wtop() + 50);
}

void Canvas::drawDebug(QPainter *painter)
{
    QString debug_text[10];
    debug_text[0] = QString("In a Row:\t%1").arg(inarow_count);
    debug_text[1] = QString("Combo:\t%1").arg(combo);
    debug_text[2] = QString("Elapsed:\t%1").arg(elapsed());
    debug_text[3] = QString("Curnote:\t%1").arg(current_note);
    debug_text[4] = QString("Picking:\t%1").arg(is_picking);
    const int y = 100;
    const int line_height = 20;
    for (int i = 0; i < 5; ++i)
        drawText(painter, Qt::black, debug_text[i], 12, "Menlo",
                 wleft() + 30, wtop() + y + line_height * i);
}

int Canvas::stringW(int key) const
{
    return 7 + window_width / 100 - key;
}

double Canvas::btnD() const
{
    return stringW(0) * 2.5;
}

void Canvas::drawStrings(QPainter *painter)
{
    QPen pen(Qt::black, 10, Qt::SolidLine);
    for (int i = 1; i <= 5; ++i)
    {
        pen.setColor(Qt::gray);
        pen.setWidth(stringW(i));
        painter->setPen(pen);
        painter->drawLine(string_positions[i] + stringW(i) / 5, wtop(),
                          string_positions[i] + stringW(i) / 5, wbottom());

        pen.setColor(string_colors[i]);
        painter->setPen(pen);
        painter->drawLine(string_positions[i], wtop(),
                          string_positions[i], wbottom());
    }
}

void Canvas::drawButtons(QPainter *painter)
{
    QPen pen(Qt::black, stringW(0) / 2, Qt::SolidLine, Qt::RoundCap);
    QBrush brush(Qt::black, Qt::SolidPattern);
    for (int i = 1; i <= 5; ++i)
    {
        if (is_pressing[i])
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
        painter->drawEllipse(string_positions[i] - btnD() / 2, wbottom() - btnD() * 1.5,
                             btnD(), btnD());
    }
}

int Canvas::beatToMs(int beats) const
{
    return (int)((double)beats / midi.bpm * 60 * 1000 / division);
}

void Canvas::drawBars(QPainter *painter)
{
    QPen pen(Qt::white, 32, Qt::SolidLine, Qt::FlatCap);

    for (int i = current_note; (beatToMs(midi.notes[i].start) - elapsed()) / ms_pixel_ratio <= window_height; ++i)
    {
        int start_ms = beatToMs(midi.notes[i].start);
        int end_ms = beatToMs(midi.notes[i].end);
        int key = midi.notes[i].key;
        int height = (end_ms - start_ms) / ms_pixel_ratio;
        int note_bottom = wtop() + 100 / ms_pixel_ratio +
                (elapsed() - start_ms) / ms_pixel_ratio +
                (window_height - btnD() * 1.5 + stringW(0) / 2);
        int note_top = note_bottom - height;
        bool in_bar;
        if (note_bottom >= wbottom() - btnD() * 1.5 && note_top <= wbottom() - btnD() * 0.5)
            in_bar = true;
        else
            in_bar = false;
        pen.setColor(Qt::white);
        if (in_bar && is_pressing[key] && is_picking)
        {
            if ((inRange(last_picking, start_ms, press_threshold) &&
                last_picking_with[key]) ||
                (inRange(last_good, start_ms, nopick_threshold) &&
                (inRange(last_pressing[key], start_ms, press_threshold))) ||
                midi.notes[i].pressed())
            {
                if (!midi.notes[i].pressed())
                {
                    midi.notes[i].setPressed(true);
                    is_good = true;
                    inarow_count += 1;
                    if (inarow_count >= combo_inarow && inarow_count % combo_inarow == 0 &&
                            combo < combo_max && !showing_combo)
                    {
                        combo += 1;
                        showing_combo = true;
                        combo_start = elapsed();
                    }
                }
                last_good = elapsed();
                score += combo;
            }
        }
        if (midi.notes[i].pressed())
            pen.setColor(Qt::gray);
        pen.setWidth(stringW(0));
        painter->setPen(pen);
        painter->drawLine(string_positions[key], note_top,
                          string_positions[key], note_bottom);
        double r = stringW(0) / 2;
        painter->drawEllipse(string_positions[key] - r, note_bottom,
                r * 2, r * 2);
        if (elapsed() > start_ms + press_threshold)
        {
            if (!midi.notes[current_note].pressed())
            {
                if (is_good)
                {
                    playGuileSound();
                    is_good = false;
                }
                inarow_count = 0;
                combo = 1;
            }
        }
        if (note_top > wbottom())
        {
            current_note += 1;
        }
    }
}

void Canvas::drawCombos(QPainter *painter)
{
    drawText(painter, QColor(255, 0, 0, 255 - (elapsed() - combo_start) / 3),
             QString("Combo x %1").arg(combo),
             50 + ((elapsed() - combo_start) / 3), "Gill Sans",
             wleft(), wtop(), window_width, window_height);
}

void Canvas::setPressing(int which, bool pressing)
{
    if (which >= 1 && which <= 5)
    {
        is_pressing[which] = pressing;
    }
}

void Canvas::setMidi(Midi new_midi)
{
    midi = new_midi;
    ms_pixel_ratio = 8.0 - midi.bpm / 27.0;
    video_pre_ms = size().height() * ms_pixel_ratio;
    printf("ms_pixel_ratio: %.2lf\n", ms_pixel_ratio);
}

int Canvas::elapsed() const
{
    return real_elapsed - video_pre_ms;
}

bool Canvas::isFinished() const
{
    return finished;
}

void Canvas::animate()
{
    real_elapsed = start_time.elapsed();
    repaint();
    if (elapsed() > 0)
        ((MainWindow *)parent())->play_music();
    if (isGood())
        ((MainWindow *)parent())->setGuitarMuted(false);
    else
        ((MainWindow *)parent())->setGuitarMuted(true);
}

bool Canvas::isGood() const
{
    return is_good;
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
   if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_5)
   {
       int key = event->key() - Qt::Key_1 + 1;
       if (!is_pressing[key])
       {
           setPressing(key, true);
           last_pressing[key] = elapsed();
       }
   }
   else if ((event->key() == Qt::Key_Return) && !is_picking)
   {
       is_picking = true;
       last_picking = elapsed();
       for (int i = 1; i <= 5; ++i)
       {
           last_picking_with[i] = is_pressing[i];
       }
   }
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
   if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_5)
   {
       setPressing(event->key() - Qt::Key_1 + 1, false);
   }
   else if (event->key() == Qt::Key_Return)
   {
       is_picking = false;
   }
}

void Canvas::drawEnd(QPainter *painter)
{
    if ((elapsed() - total_time) < 4000)
    {
        drawText(painter, QColor(255, 0, 0, std::min(255, (elapsed() - total_time) / 5)),
                 QString("Score: %1").arg(score),
                 std::min(120, 20 + (elapsed() - total_time) / 10), "Gill Sans",
                 wleft(), wtop(), window_width, window_height);
    }
    else
    {
        finished = true;
    }
}

void Canvas::drawText(QPainter*& painter, const QColor& word_color, const QString text,
                      const int& fontSize, const char fontName[],
                      const int& top_left_x, const int& top_left_y,
                      const int& width, const int& height)
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

void Canvas::drawText(QPainter*& painter, const QColor& word_color, const QString text,
                      const int& fontSize, const char fontName[],
                      const int& top_left_x, const int& top_left_y)
{
    QPen pen(word_color, 2);
    QFont font;
    font.setPixelSize(fontSize);
    font.setFamily(fontName);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(top_left_x, top_left_y, text);
}

void Canvas::playGuileSound()
{
    Phonon::MediaObject *guile = new Phonon::MediaObject(this);
    int which_sound = qrand() % 6 + 1;
    guile->setCurrentSource(Phonon::MediaSource(QString(":/sound/screwup%1.mp3").arg(which_sound)));
    Phonon::AudioOutput *guile_output =
        new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(guile, guile_output);

    guile_output->setVolume(guile_vol);
    guile->play();
}

bool inRange(int number, int value, int threshold)
{
    return (number <= value + threshold &&
            number >= value - threshold);
}
