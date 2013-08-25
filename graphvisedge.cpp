#include "graphedge.h"
#include "graphvisedge.h"
#include "graphnode.h"

GraphVisEdge::GraphVisEdge(GraphEdge *_data, QGraphicsItem *parent):QGraphicsLineItem(parent)
{
    mdata = _data;
    src = _data->getSrc()->mdata;
    dest = _data->getDest()->mdata;
    refreshGeometry();
    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptedMouseButtons(0);
    setPen(QPen(QBrush(Qt::black), 9, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void GraphVisEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
#ifdef QT_DEBUG
    //qDebug() << *this;
    //qDebug() << "called paint graphedge from" << *src << " to " << *dest;
    //qDebug() << "drawing graphedge from " << begin << " to " << end;
#endif //QT_DEBUG
    painter->translate(-x(), -y());
    painter->drawLine(line());
}

QVariant GraphVisEdge::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug() << "Change" << *this;
    switch (change)
    {
    case QGraphicsItem::ItemSelectedChange:
        qDebug() << "Selection change!!!";
        QPen p = pen();
        QBrush b = p.brush();
        if (value == true)
        {
            b.setColor(QColor(80, 80, 80));
            scene()->update(boundingRect());
        }
        else
        {
            b.setColor(QColor(0, 0, 0));
            scene()->update(boundingRect());
        }
        p.setBrush(b);
        setPen(p);
    }
    return QGraphicsLineItem::itemChange(change, value);
}

void GraphVisEdge::refreshGeometry()
{
    prepareGeometryChange();
    setLine(src->x() + src->boundingRect().width()/2,
            src->y() + src->boundingRect().width()/2,
            dest->x() + dest->boundingRect().center().x(),
            dest->y() + dest->boundingRect().center().y());
    qDebug() << "Src: " << src->pos() << ", Dest: " << dest->pos() << ", LINE: " << line();
    setX( (line().x1() + line().x2()) / 2 );
    setY( (line().y1() + line().y2()) / 2 );
}

QRectF GraphVisEdge::boundingRect() const
{
    qreal   extra = pen().width() / 2 + 1;
    QPointF p1 = line().p1(),
            p2 = line().p2();
    qreal   left = p1.x(),
            top = p1.y(),
            width = p2.x() - left,
            height = p2.y() - top;
    return  QRectF(left, top, width, height)
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath GraphVisEdge::shape() const
{
    QPainterPath path;
    QPainterPathStroker str;
    str.setWidth(pen().width() + 2);
    path.moveTo(line().p1());
    path.lineTo(line().p2());
    return str.createStroke(path);
}

QDebug operator<<(QDebug d, GraphVisEdge &edge)
{
    d << "EdgeVis: "    << edge.line()
      //<< ", path: "     << edge.shape()
      << ", bound: "    << edge.boundingRect().top() << " to " << edge.boundingRect().bottom() << " by Y (height: " << edge.boundingRect().height() << ") & "
                        << edge.boundingRect().left() << " to " << edge.boundingRect().right() << " by X (width: " << edge.boundingRect().width()
      << "), color: "    << edge.pen().color();
    return d;
}
