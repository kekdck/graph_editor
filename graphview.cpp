#include "graphview.h"

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent)
{
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
