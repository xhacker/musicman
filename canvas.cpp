#include <QPainter>
#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
}

void Canvas::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    drawLines(&qp);
}

void Canvas::drawLines(QPainter *qp)
{
    QPen pen(Qt::black, 2, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(20, 40, 250, 40);

    pen.setStyle(Qt::DashLine);
    qp->setPen(pen);
    qp->drawLine(20, 80, 250, 80);

    pen.setStyle(Qt::DashDotLine);
    qp->setPen(pen);
    qp->drawLine(20, 120, 250, 120);

    pen.setStyle(Qt::DotLine);
    qp->setPen(pen);
    qp->drawLine(20, 160, 250, 160);

    pen.setStyle(Qt::DashDotDotLine);
    qp->setPen(pen);
    qp->drawLine(20, 200, 250, 200);

    QVector<qreal> dashes;
    qreal space = 4;

    dashes << 1 << space << 5 << space;

    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    qp->setPen(pen);
    qp->drawLine(20, 240, 250, 240);
}
