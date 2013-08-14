#include "graphcomment.h"

GraphComment::GraphComment(const QString& text, QGraphicsItem* parent):
    QGraphicsTextItem(text, parent)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | ItemSendsGeometryChanges);

    setTextInteractionFlags(Qt::TextEditorInteraction);
    setZValue(1);

    QPointF parentPos(parent->boundingRect().width()*2,parent->boundingRect().height());
    setPos(parentPos);
}


void GraphComment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter, option, widget);
    painter->drawRect(boundingRect());

}






