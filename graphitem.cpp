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
    //С индексами быстрее и проще вернуться в место взятия файла в treeView
    fileIndex = index;
    dirModel = model;
    //Задаем заголовку нода имя вставляемого файла/папки и смещаем его в центр
    nameText->setPlainText(model->fileInfo(fileIndex).fileName());
    nameText->setPos(QPointF(boundingRect().width() - nameText->boundingRect().width()/2,-10));
}

QString GraphItem::fileName(QDirModel *model)
{
    return model->fileInfo(fileIndex).fileName();
}

void GraphItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseDoubleClickEvent(event);
    //Тут надо как-то реализовать перемещение в mainwindow у treeView к fileIndex

}
