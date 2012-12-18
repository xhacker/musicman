#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = 0);
    void setPressing(int, bool);

public slots:
    void animate();

private:
    bool isPressing[6];
    int elapsed;
    int score;
    int combo;
    int combo_start;
    bool in_combo;

protected:
    void paintEvent(QPaintEvent *event);
    void drawScore(QPainter *painter);
    void drawStrings(QPainter *painter);
    void drawButtons(QPainter *painter);
    void drawBars(QPainter *painter);
    void drawCombos(QPainter *painter);
};

#endif // CANVAS_H
