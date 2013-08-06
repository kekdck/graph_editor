#include "graphitem.h"
#include "graphedge.h"

GraphItem::GraphItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent):
    QGraphicsRectItem(x, y, width, height, parent)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    brush().setColor(Qt::red);
    nameText = new QGraphicsTextItem("New item", this);
    QPointF thisPos(boundingRect().width()/2,-10);
    nameText->setPos(thisPos);
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    foreach (GraphEdge *edge, inEdges)
    {
        edge->paint(painter, option, widget);
    }
    foreach (GraphEdge *edge, outEdges)
    {
        edge->paint(painter, option, widget);
    }
    prepareGeometryChange();
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRect(rect());
}

void GraphItem::setFile(QModelIndex index, QFileSystemModel *model)
{
    //Saving
    fileIndex = index;
    fileModel = model;
    //setting color so that we can recognize files/dirs
    if (fileModel->isDir(fileIndex))
    {
        setBrush(QBrush(Qt::green));
    }
    else
    {
        setBrush(QBrush(Qt::cyan));
    }
    //making view props
    nameText->setPlainText(model->fileName(fileIndex));
    nameText->setPos(QPointF(boundingRect().width() - nameText->boundingRect().width()/2,-10));
}

QString GraphItem::fileName()
{
    return fileModel->fileInfo(fileIndex).fileName();
}

void GraphItem::addOutEdge(GraphEdge * edge)
{
    outEdges << edge;
    edge->setSource(this);
}

void GraphItem::addInEdge(GraphEdge *edge)
{
    inEdges << edge; 
    edge->setDest(this);
}


void GraphItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseDoubleClickEvent(event);
    //Here is better to implement scrolling to this->fileIndex in mainwindow->treeView

}

QRectF GraphItem::boundingRect() const
{
    return rect();
}

QVariant GraphItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        {
            foreach (GraphEdge *edge, inEdges)
            {
                edge->update();
            }
            foreach (GraphEdge *edge, outEdges)
            {
                edge->update();
            }
            scene()->update();
        } break;
    case ItemSelectedChange:
        {
            if (value == true)
            {
                QBrush br = brush();
                QColor col = br.color();
                col.setAlpha(100);
                br.setColor(col);
                setBrush(br);
            }
            else
            {
                QBrush br = brush();
                QColor col = br.color();
                col.setAlpha(255);
                br.setColor(col);
                setBrush(br);
            }
        } break;
    default:
        {
#ifdef QT_DEBUG
            //qDebug() << "Unknown GraphItem change, can\'t handle";
#endif
        } break;
    }
    
    return QGraphicsItem::itemChange(change, value);
}
