#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
public:
    Canvas(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
};

#endif // CANVAS_H
