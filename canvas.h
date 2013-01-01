#ifndef CANVAS_H
#define CANVAS_H

#include <QTime>
#include <QWidget>
#include <QGLWidget>
#include "note.h"
#include "midi.h"

class Canvas : public QGLWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = 0);
    void setMidi(Midi);
    void setTotalTime(int t);

public slots:
    void animate();

private:
    int window_height;
    int window_width;

    bool is_pressing[6];
    int last_pressing[6];
    bool is_picking;
    int last_picking;
    bool last_picking_with[6];

    QTime start_time;
    int total_time;
    int real_elapsed;
    int last_good;

    double ms_pixel_ratio;
    int video_pre_ms;
    int string_positions[6];
    int current_note;

    int score;
    bool is_good;
    int combo;
    bool showing_combo;
    int combo_start;
    int inarow_count; // how many good presses in a row

    Midi midi;

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

protected:
    int wtop() const;
    int wbottom() const;
    int wleft() const;
    int wright() const;
    int stringW(int key) const;
    double btnD() const;
    int beatToMs(int beats) const;
    int elapsed() const;

    void paintEvent(QPaintEvent *event);
    void drawScore(QPainter *painter);
    void drawDebug(QPainter *painter);
    void drawStrings(QPainter *painter);
    void drawButtons(QPainter *painter);
    void drawBars(QPainter *painter);
    void drawCombos(QPainter *painter);
    void drawEnd(QPainter *painter);

    void drawText(QPainter*& painter, const QColor& word_color, const char text[],
                  const int& fontSize, const char fontName[], const int& top_left_x,
                  const int& top_left_y, const int& width, const int& height);
    void drawText(QPainter*& painter, const QColor& word_color, const char text[],
                  const int& fontSize, const char fontName[], const int& top_left_x, const int& top_left_y);
    void drawText(QPainter*& painter, const QColor& word_color, const QString text,
                  const int& fontSize, const char fontName[], const int& top_left_x, const int& top_left_y);

    void setPressing(int, bool);
    void playGuileSound();
    bool isGood() const;
};

bool inRange(int number, int value, int threshold);

#endif // CANVAS_H
