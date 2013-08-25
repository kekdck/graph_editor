#include "graphview.h"

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent)
{
}

GraphView::~GraphView()
{
    delete contextMenu;
}

void GraphView::openEdit()
{

}

void GraphView::contextMenuEvent(QContextMenuEvent *event)
{
    if (!contextMenu) return;
    contextMenu->exec(event->globalPos());
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
