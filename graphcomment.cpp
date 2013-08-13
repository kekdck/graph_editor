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

    blob = new QGraphicsRectItem(boundingRect(), this);
    QObject::connect(document(), SIGNAL(contentsChanged()), this, SLOT(updateBlob()));
}

void GraphComment::updateBlob()
{
    blob->setRect(boundingRect());
    qDebug() << boundingRect();
}

QVariant GraphComment::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsTextItem::itemChange(change, value);
}





