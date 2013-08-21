#include "graphedge.h"
#include "graphnode.h"

GraphEdge::GraphEdge(GraphNode *source, GraphNode *destin, QGraphicsItem *parent):
    QGraphicsLineItem(source->boundingRect().center().x(), source->boundingRect().center().y(),
                      destin->boundingRect().center().x(), destin->boundingRect().center().y(), parent)
{

    setFlags(QGraphicsItem::ItemIsSelectable
                               | QGraphicsItem::ItemSendsGeometryChanges);
    src = source;
    dest = destin;

    src->addOutEdge(this);
    dest->addInEdge(this);

    setAcceptedMouseButtons(0);
    setPen(QPen(QBrush(Qt::black), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void GraphEdge::setSource(GraphNode *source)
{
    prepareGeometryChange();
    src = source;
}


void GraphEdge::setDest(GraphNode *destin)
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
    qDebug() << "called paint graphedge from" << *src << " to " << *dest;
    qDebug() << "drawing graphedge from " << begin << " to " << end;
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
