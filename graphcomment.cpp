#include "graphcomment.h"


GraphComment::GraphComment(const QString& text, QGraphicsItem* parent):
    QGraphicsTextItem(text, parent)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);

    QPointF parentPos(parent->boundingRect().width()*2,0);
    setPos(parentPos);

    blob = new QGraphicsRectItem(boundingRect().topLeft().x(), boundingRect().topLeft().y(),
                                 boundingRect().bottomRight().x(), boundingRect().bottomRight().y(), this);
}




