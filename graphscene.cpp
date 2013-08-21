#include "graphscene.h"

<<<<<<< HEAD
GraphScene::GraphScene(qreal x, qreal y, qreal width, qreal height, QObject * parent)
    :QGraphicsScene(x, y, width, height, parent)
{
}

void GraphScene::addNode(QFileInfo _fileinfo)
{
    GraphNode* node = new GraphNode(_fileinfo);

    addItem(node);
}

void GraphScene::addEdge(GraphNode *source, GraphNode *destin)
{
    GraphEdge* edge = new GraphEdge(source, destin);

    addItem(edge);
}

void GraphScene::addComment(QGraphicsItem *node)
{
    GraphComment* comment = new GraphComment("default", node);

    addItem(comment);

=======
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
>>>>>>> b261cf3054b31b0477d9c90fd98ea0b393a413d7
}
