#include "graphscene.h"

GraphScene::GraphScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

GraphScene::GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
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
}
