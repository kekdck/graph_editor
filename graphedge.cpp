#include "graphedge.h"

GraphEdge::GraphEdge(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent):
    QGraphicsLineItem(x1, y1, x2, y2, parent)
{
    sourcePoint.setX(x1);
    sourcePoint.setY(y2);
    destPoint.setX(x2);
    destPoint.setY(y2);

    setAcceptedMouseButtons(0);
}

void GraphEdge::adjustSource(QPointF &source)
{
    prepareGeometryChange();
    sourcePoint = source;
}

void GraphEdge::adjustDest(QPointF &dest)
{
    prepareGeometryChange();
    sourcePoint = dest;
}

void GraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    QLineF line(sourcePoint, destPoint);

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

}

QRectF GraphEdge::boundingRect() const
{
    qreal penWidth = 1;
    qreal extra = 1;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}


