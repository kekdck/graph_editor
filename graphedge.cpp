#include "graphedge.h"
#include "graphitem.h"

GraphEdge::GraphEdge(GraphItem *source, GraphItem *destin, QGraphicsItem *parent):
    QGraphicsLineItem(source->boundingRect().center().x(), source->boundingRect().center().y(),
                      destin->boundingRect().center().x(), destin->boundingRect().center().y(), parent)
{
    src = source;
    dest = destin;
    setAcceptedMouseButtons(0);
    setPen(QPen(Qt::black));
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
#ifdef QT_DEBUG
    qDebug() << "called paint graphedge from"
             << src->fileName() << "(" << src->boundingRect() << ") to "
             << dest->fileName() << "(" << src->boundingRect() << ")";
    qDebug() << "drawing graphedge from "
             << src->x() << src->y()
             << " to "
             << dest->x() << dest->y();
#endif //QT_DEBUG
    painter->drawLine(src->x()+src->rect().width()/2, src->y()+src->rect().height()/2,
                      dest->x()+dest->rect().width()/2, dest->y()+src->rect().height()/2);
}

QRectF GraphEdge::boundingRect() const
{
    qreal penWidth = 1;
    qreal extra = 1;

    qDebug() << QRectF(src->x(), src->y(), dest->x(), dest->y())
                .normalized()
                .adjusted(-extra, -extra, extra, extra);
    return QRectF(src->x(), src->y(), dest->x(), dest->y())
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}


