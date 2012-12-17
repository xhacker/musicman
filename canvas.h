#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "note.h"
#include "button.h"

class Canvas : public QWidget
{
public:
    Canvas(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void drawStrings(QPainter *qp);
    void drawNote(QPainter *qp, Note&);
    void drawNotePressed(QPainter *qp, Note&);
    void drawButton(QPainter *qp, Button&);
    void drawButtonPressed(QPainter *qp, Button&);
};

#endif // CANVAS_H
