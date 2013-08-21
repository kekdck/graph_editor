#include "graphnode.h"
#include "graphedge.h"

GraphNode::GraphNode(QFileInfo _fileInfo, qreal x, qreal y):
    QGraphicsRectItem(x, y, WIDTH, HEIGHT, 0)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);

    propModel = new QStandardItemModel(10, 2);
    QStandardItem *item = new QStandardItem();
    propModel->setItem(0, item);

    //Set file properties for node
    fileInfo = _fileInfo;

    //Check if Node's name is too long and cut it if so
    QString fn =
        (fileInfo.isRoot()) ?
        fileInfo.absolutePath() :
        fileInfo.fileName();
    if (fn.length()>15)
    {
        fn.chop(fn.length()-12);
        fn.append("...");
    }
    propModel->setItem(0, 1, new QStandardItem(fileInfo.isDir() ? "Directory" : "File"));
    propModel->setItem(1, 1, new QStandardItem(fileInfo.fileName()));
    propModel->setItem(2, 1, new QStandardItem(fileInfo.filePath()));

    nameText = new QGraphicsTextItem("New item", this);
    nameText->setHtml("<div style='background-color:#FFFFFF;'>" + fn + "</div>");

    QPointF thisPos(QPointF(boundingRect().width()/2 - nameText->boundingRect().width()/2,-25));
    nameText->setPos(thisPos);
}

QStandardItemModel* GraphNode::model()
{
    return propModel;
}

void GraphNode::eraseEdges()
{
    foreach(GraphEdge *edge, inEdges)
    {
        scene()->removeItem(edge);
        edge->getSrc()->removeEdge(edge);
    }
    inEdges.erase(inEdges.begin(), inEdges.end());
    foreach(GraphEdge *edge, outEdges)
    {
        scene()->removeItem(edge);
        edge->getDest()->removeEdge(edge);
    }
    outEdges.erase(outEdges.begin(), outEdges.end());
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRect(rect());
}

QString GraphNode::fileName()
{
    return fileInfo.fileName();
}

QString GraphNode::filePath()
{
    return fileInfo.filePath();
}

void GraphNode::addOutEdge(GraphEdge * edge)
{
    outEdges << edge;
    //edge->setSource(this);
}

void GraphNode::addInEdge(GraphEdge *edge)
{
    inEdges << edge; 
    //edge->setDest(this);
}

void GraphNode::removeEdge(GraphEdge *edge)
{
    if (!inEdges.removeOne(edge))
        outEdges.removeOne(edge);
}

void GraphNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseDoubleClickEvent(event);
    //Here is better to implement scrolling to this->fileIndex in mainwindow->treeView

}

QRectF GraphNode::boundingRect() const
{
    return rect();
}

QDebug operator<< (QDebug d, GraphNode &item)
{
    d << item.fileName() << "(" << item.x() << ";" << item.y() << ")"
      << "connections: " << item.inEdges.count()+item.outEdges.count();
    return d;
}


QVariant GraphNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        {
            scene()->update();
        } break;
    case ItemSelectedChange:
        {
#ifdef QT_DEBUG
        qDebug() << "changed selection of " << *this;
#endif //QT_DEBUG
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
            scene()->update();
        } break;
    default:
        {
#ifdef QT_DEBUG
            //qDebug() << "Unknown GraphNode change, can\'t handle";
#endif
        } break;
    }
    
    return QGraphicsItem::itemChange(change, value);
}
