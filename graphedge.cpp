#include "graphedge.h"
#include "graphitem.h"

GraphEdge::GraphEdge(GraphItem *source, GraphItem *destin, QGraphicsItem *parent):
    QGraphicsLineItem(source->boundingRect().center().x(), source->boundingRect().center().y(),
                      destin->boundingRect().center().x(), destin->boundingRect().center().y(), parent)
{
    src = source;
    dest = destin;
    setAcceptedMouseButtons(0);
    setPen(QPen(QBrush(Qt::black), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(1);
}

void GraphEdge::setSource(GraphItem *source)
{
    prepareGeometryChange();
    src = source;
}


void GraphEdge::setDest(GraphItem *destin)
{
    prepareGeometryChange();
    dest = destin;
}

void GraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    QPoint begin(src->x()+src->rect().width(),
                 src->y()+src->rect().height()),
            end(dest->x()+dest->rect().width(),
                dest->y()+src->rect().height());
#ifdef QT_DEBUG
//    qDebug() << "called paint graphedge from" << *src << " to " << *dest;
//    qDebug() << "drawing graphedge from " << begin << " to " << end;
#endif //QT_DEBUG
    painter->drawLine(begin, end);
}

QRectF GraphEdge::boundingRect() const
{
    qreal extra = 1;

    return QRectF(src->x(), src->y(), dest->x(), dest->y())
            .normalized()
            .adjusted(-extra, extra, extra, -extra);
}


QDebug operator<< (QDebug d, GraphEdge &edge)
{
    d << "Edge(" << *edge.src << ";" << *edge.dest << ")";
    return d;
}
