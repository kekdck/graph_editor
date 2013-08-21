#include "graphscene.h"

GraphScene::GraphScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

GraphScene::GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
}

void GraphScene::zoomIn()
{
    if (graphicsView->matrix().m11() > 4) return;
    graphicsView->scale(1.2, 1.2);
}

void GraphScene::zoomOut()
{
    if (graphicsView->matrix().m11() < 0.4) return;
    graphicsView->scale(1/1.2, 1/1.2);
}
