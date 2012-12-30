#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QTime>
#include "note.h"
#include "midi.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = 0);
    void setPressing(int, bool);
    void setMidi(Midi);
    bool isGood() const;

public slots:
    void animate();

private:
    int window_height;
    int window_width;
    int wtop() const;
    int wbottom() const;
    int wleft() const;
    int wright() const;
    int string_positions[6];

    bool isPressing[6];
    QTime starttime;
    int elapsed;
    int score;
    int combo;
    int combo_start;
    int inarow_count; // how many good presses in a row
    bool is_good;
    bool showing_combo;
    int current_note;
    Midi midi;

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void drawText(QPainter*& painter, const QColor& word_color, const char text[],
                  const int& fontSize, const char fontName[], const int& top_left_x,
                  const int& top_left_y, const int& width, const int& height);
    void drawText(QPainter*& painter, const QColor& word_color, const char text[],
                  const int& fontSize, const char fontName[], const int& top_left_x, const int& top_left_y);

protected:
    void paintEvent(QPaintEvent *event);
    void drawScore(QPainter *painter);
    void drawDebug(QPainter *painter);
    void drawStrings(QPainter *painter);
    void drawButtons(QPainter *painter);
    void drawBars(QPainter *painter);
    void drawCombos(QPainter *painter);
    void drawEnd(QPainter *painter);
};

#endif // CANVAS_H
