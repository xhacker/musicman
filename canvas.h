#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
public:
    Canvas(QWidget *parent = 0);
    void setPressing(int, bool);

private:
    bool isPressing[6];
protected:
    void paintEvent(QPaintEvent *event);
    void drawStrings(QPainter *qp);
    void drawButtons(QPainter *qp);
};

#endif // CANVAS_H
