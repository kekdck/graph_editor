#include "graphnode.h"
#include "graphvisnode.h"
#include "graphedge.h"

GraphVisNode::GraphVisNode(GraphNode *data, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent) :
    QGraphicsRectItem(x, y, w, h, parent), mdata(data), fileInfo(data->getFileInfo())
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);

    setBrush(QBrush( (fileInfo->isDir()) ? Qt::green : Qt::yellow));

    nameText = new QGraphicsTextItem(this);
    nameText->setAcceptedMouseButtons(Qt::NoButton);
    setNameText(fileInfo->fileName());
}

GraphVisNode::~GraphVisNode()
{
    scene()->removeItem(nameText);
}

void GraphVisNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRect(rect());
}

void GraphVisNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseDoubleClickEvent(event);
}

QRectF GraphVisNode::boundingRect() const
{
    return QGraphicsRectItem::boundingRect();
}

QString GraphVisNode::fileName()
{
    return mdata->fileName();
}

QString GraphVisNode::filePath()
{
    return mdata->filePath();
}

void GraphVisNode::addOutEdge(GraphEdge *edge)
{
    mdata->addOutEdge(edge);
}

QDebug operator<< (QDebug d, GraphVisNode &item)
{
    d << "VisNode: " << item.fileName()
      << ", pos: " << item.pos();
    return d;
}

QVariant GraphVisNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
    {
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();

        foreach(GraphEdge *e, mdata->getInEdges())
        {
            e->mdata->refreshGeometry();
        }
        foreach(GraphEdge *e, mdata->getOutEdges())
        {
            e->mdata->refreshGeometry();
        }
        if (!rect.contains(newPos))
        {
            //Save node inside scene
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
        scene()->update();
    } break;
    case ItemSelectedChange:
    {
#ifdef QT_DEBUG
        //qDebug() << "changed selection of " << *this;
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

    return QGraphicsRectItem::itemChange(change, value);
}


void GraphVisNode::eraseEdges()
{
    mdata->eraseEdges();
}

void GraphVisNode::setNameText(QString s)
{
    mdata->name = s;
    if (s.length()>15)
    {
        s.chop(s.length()-12);
        s.append("...");
    }

    nameText->setHtml("<div style='background-color:#FFFFFF;'>" + s + "</div>");
    QPointF thisPos(QPointF(boundingRect().width()/2 - nameText->boundingRect().width()/2, -25));
    nameText->setPos(thisPos);
}

void GraphVisNode::setColor(QColor col)
{
    QBrush br = brush();
    br.setColor(col);
    setBrush(br);
}

void GraphVisNode::removeEdge(GraphEdge *edge)
{
    mdata->removeEdge(edge);
}


int GraphVisNode::connections()
{
    return mdata->connections();
}


GraphEdge *GraphVisNode::connectedDirectlyTo(GraphNode *g)
{
    return mdata->connectedDirectlyTo(g);
}


void GraphVisNode::addInEdge(GraphEdge *edge)
{
    mdata->addInEdge(edge);
}
