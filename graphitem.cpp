#include "graphitem.h"
#include "graphedge.h"

GraphItem::GraphItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent):
    QGraphicsRectItem(x, y, width, height, parent)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);

    brush().setColor(Qt::red);
    nameText = new QGraphicsTextItem("New item", this);
    QPointF thisPos(boundingRect().width()/2,-10);
    nameText->setPos(thisPos);
    propModel = new QStandardItemModel(10, 2, parentObject());
    QStandardItem *item = new QStandardItem();
    propModel->setItem(0, item);
}

QStandardItemModel* GraphItem::model()
{
    return propModel;
}

void GraphItem::eraseEdges()
{
    foreach(GraphEdge *edge, inEdges)
    {
        scene()->removeItem(edge);
    }
    inEdges.erase(inEdges.begin(), inEdges.end());
    foreach(GraphEdge *edge, outEdges)
    {
        scene()->removeItem(edge);
    }
    outEdges.erase(outEdges.begin(), outEdges.end());
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
    QString fn = model->fileName(fileIndex);
    if (fn.length()>15)
    {
        fn.chop(fn.length()-12);
        fn.append("...");
    }
    propModel->setItem(0, 0, new QStandardItem("isDir?"));
    propModel->setItem(1, 0, new QStandardItem("Name"));
    propModel->setItem(2, 0, new QStandardItem("Path"));
    propModel->setItem(0, 1, new QStandardItem(fileModel->fileInfo(fileIndex).isDir() ? "Directory" : "File"));
    propModel->setItem(1, 1, new QStandardItem(fileModel->fileName(fileIndex)));
    propModel->setItem(2, 1, new QStandardItem(fileModel->filePath(fileIndex)));
    nameText->setHtml("<div style='background-color:#FFFFFF; border: solid 3px #000000; padding: 5px 5px 5px 5px; '>" + fn + "</div>");
    nameText->setPos(QPointF(boundingRect().width() - nameText->boundingRect().width()/2,-10));
}

QModelIndex GraphItem::index()
{
    return fileIndex;
}

QString GraphItem::fileName()
{
    return fileModel->fileName(fileIndex);
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

QDebug operator<< (QDebug d, GraphItem &item)
{
    d << item.fileName() << "(" << item.x() << ";" << item.y() << ")"
      << "connections: " << item.inEdges.count()+item.outEdges.count();
    return d;
}


QVariant GraphItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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
            //qDebug() << "Unknown GraphItem change, can\'t handle";
#endif
        } break;
    }
    
    return QGraphicsItem::itemChange(change, value);
}
