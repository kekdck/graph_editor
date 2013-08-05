#include "graphitem.h"

GraphItem::GraphItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent):
    QGraphicsRectItem(x, y, width, height, parent)
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    brush().setColor(Qt::blue);
    nameText = new QGraphicsTextItem(0, this);
    QPointF thisPos(boundingRect().width()/2,-10);
    nameText->setPos(thisPos);
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRect(rect());
}

void GraphItem::setFile(QModelIndex index, QDirModel *model)
{
    //Saving
    fileIndex = index;
    dirModel = model;
    //making view props
    nameText->setPlainText(model->fileInfo(fileIndex).fileName());
    nameText->setPos(QPointF(boundingRect().width() - nameText->boundingRect().width()/2,-10));
}

QString GraphItem::fileName()
{
    return dirModel->fileInfo(fileIndex).fileName();
}

void GraphItem::addOutEdge(GraphEdge * edge)
{
    outEdges << edge;
}

void GraphItem::addInEdge(GraphEdge *edge)
{
    inEdges << edge; 
}


void GraphItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseDoubleClickEvent(event);
    //Here is better to implement scrolling to this->fileIndex in mainwindow->treeView

}


QVariant GraphItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    
    
    if (change == ItemPositionHasChanged)
    {
        QPointF pos = mapToScene(boundingRect().center());
        
        if (!inEdges.isEmpty())
        {
            foreach(GraphEdge *edge, inEdges)
            {
                edge->adjustDest(pos);
            }
        }
        if (!outEdges.isEmpty())
        {
            foreach(GraphEdge *edge, outEdges)
            {
                edge->adjustSource(pos);
            }
        }
        
    }
    
    return QGraphicsItem::itemChange(change, value);
}
