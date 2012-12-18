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
protected:
    void paintEvent(QPaintEvent *event);
    void drawScore(QPainter *qp);
    void drawStrings(QPainter *qp);
    void drawButtons(QPainter *qp);
    void drawBars(QPainter *qp);
    void drawCombos(QPainter *qp);
};

#endif // CANVAS_H
