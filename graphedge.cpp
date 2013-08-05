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
    qDebug() << "called paint graphedge from" << src->fileName() << " to " << dest->fileName();
    qDebug() << "drawing from " << src->boundingRect().center() << " to " << dest->boundingRect().center();
#endif //QT_DEBUG
    painter->drawLine(src->boundingRect().center(), dest->boundingRect().center());
}

