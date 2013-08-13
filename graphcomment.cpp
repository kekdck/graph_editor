#include "graphcomment.h"


GraphComment::GraphComment(const QString& text, QGraphicsItem* parent):
    QGraphicsTextItem(text, parent)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | ItemSendsGeometryChanges);

    setTextInteractionFlags(Qt::TextEditorInteraction);


    QPointF parentPos(parent->boundingRect().width()*2,0);
    setPos(parentPos);

    blob = new QGraphicsRectItem(boundingRect(), this);

    blob->setFlag(QGraphicsItem::ItemIsMovable);
    blob->setZValue(-1);
}

//QVariant GraphComment::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//    QVariant textChange = QGraphicsTextItem::itemChange(change, value);
//    return textChange;
//}





