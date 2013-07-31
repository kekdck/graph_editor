#include "graphitem.h"

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

void GraphItem::setFile(QModelIndex index, QDirModel *model)
{
    //Вообще вставляется не только файл, но и вообще все что угодно, возможно не стоит использовать индексы
    fileIndex = index;
    treeModel = model;
    //Задаем заголовку нода имя вставляемого файла и смещаем его в центр
    nameText->setPlainText(model->fileInfo(fileIndex).fileName());
    nameText->setPos(QPointF(boundingRect().width() - nameText->boundingRect().width()/2,-10));
}

QString GraphItem::fileName(QDirModel *model)
{
    return model->fileInfo(fileIndex).fileName();
}

//void static GraphItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsItem::mousePressEvent(event);
//}
