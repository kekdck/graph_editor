#include "graphitem.h"
#include <QGraphicsScene>

GraphItem::GraphItem(qreal x, qreal y, qreal width, qreal height, QString name, QGraphicsItem * parent):
    QGraphicsRectItem(x, y, width, height, parent)
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);

    brush().setColor(Qt::blue);
    nameText = new QGraphicsTextItem(name, this);
    QPointF thisPos(boundingRect().width()/2,-10);
    nameText->setPos(thisPos);
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();
    painter->drawRect(rect());
}

void GraphItem::setFile(QString file)
{
    path = file;
}

void static GraphItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);   
}
