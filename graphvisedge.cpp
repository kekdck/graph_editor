#include "graphedge.h"
#include "graphvisedge.h"
#include "graphnode.h"

GraphVisEdge::GraphVisEdge(GraphEdge *_data, QGraphicsItem *parent) :
    QGraphicsLineItem(parent), mdata(_data), src(_data->getSrc()->mdata), dest(_data->getDest()->mdata)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptedMouseButtons(0);
    setPen(QPen(QBrush(Qt::black), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void GraphVisEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    QPoint begin(mdata->getSrc()->mdata->x()+mdata->getSrc()->mdata->rect().width()/2,
                 mdata->getSrc()->mdata->y()+mdata->getSrc()->mdata->rect().height()/2),
            end(mdata->getDest()->mdata->x()+mdata->getDest()->mdata->rect().width()/2,
                mdata->getDest()->mdata->y()+mdata->getDest()->mdata->rect().height()/2);

#ifdef QT_DEBUG
    qDebug() << "called paint graphedge from" << *src << " to " << *dest;
    qDebug() << "drawing graphedge from " << begin << " to " << end;
#endif //QT_DEBUG
    painter->drawLine(begin, end);
}

QRectF GraphVisEdge::boundingRect() const
{
    qreal extra = 1;

    return QRectF(src->x(), src->y(), dest->x(), dest->y())
            .normalized()
            .adjusted(-extra, extra, extra, -extra);
}


QDebug operator<<(QDebug d, GraphVisEdge &edge)
{
    d << "Edge: " << edge.mdata;
    return d;
}
