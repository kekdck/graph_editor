#include "graphview.h"

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent)
{
}

GraphView::~GraphView()
{
    delete contextMenu;
}

GraphScene *GraphView::scene()
{
    return dynamic_cast<GraphScene *>(QGraphicsView::scene());
}

void GraphView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->pos());
    if (item)
    {
        openItemEdit(item);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphView::openNodeEdit(GraphVisNode *n)
{
    editNodeDialog dial(n->mdata, this);
    dial.exec();
}

void GraphView::openEdgeEdit(GraphVisEdge *e)
{

}

void GraphView::openCommEdit(QGraphicsTextItem *c)
{

}

void GraphView::contextMenuEvent(QContextMenuEvent *event)
{
    if (!contextMenu) return;
    contextMenu->exec(event->globalPos());
}

void GraphView::openItemEdit(QGraphicsItem *item)
{
    GraphVisNode *gvn = dynamic_cast<GraphVisNode *>(item);
    if (gvn)
    {
        openNodeEdit(gvn);
        return;
    }
    GraphVisEdge *gve = dynamic_cast<GraphVisEdge *>(item);
    if (gve)
    {
        openEdgeEdit(gve);
        return;
    }
    QGraphicsTextItem *comm = dynamic_cast<QGraphicsTextItem *>(item);
    if (comm)
    {
        openCommEdit(comm);
    }
}

void GraphView::openEdit()
{
    QList<QGraphicsItem *> items = scene()->selectedItems();
    if (items.size() == 0)
    {
        return;
    }
    if (items.size() == 1)
    {
        QGraphicsItem *item = items.at(0);
        openItemEdit(item);
        return;
    }
    return;
}

void GraphView::zoomIn()
{
    if (this->matrix().m11() > 4) return;
    this->scale(1.2, 1.2);
}

void GraphView::zoomOut()
{
    if (this->matrix().m11() < 0.4) return;
    this->scale(1/1.2, 1/1.2);
}

QMenu *GraphView::getContextMenu() const
{
    return contextMenu;
}

void GraphView::setContextMenu(QMenu *value)
{
    contextMenu = value;
}

void GraphView::goToCenter()
{
    centerOn(scene()->cg());
}
