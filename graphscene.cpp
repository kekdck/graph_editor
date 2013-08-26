#include "graphscene.h"

GraphScene::GraphScene(QObject *parent) :
    QGraphicsScene(parent)
{
    init();
}

GraphScene::GraphScene(GraphModel *mod, qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent), graphModel(mod)
{
    init();
}

QFileSystemModel *GraphScene::getFileModel() const
{
    return fileModel;
}

void GraphScene::setFileModel(QFileSystemModel *value)
{
    fileModel = value;
}

GraphVisNode *GraphScene::addNode(QFileInfo *_fileinfo)
{
    GraphNode *node = graphModel->addNode(_fileinfo);
    GraphVisNode *visNode = new GraphVisNode(node, 0, 0, 20, 20);

    node->mdata = visNode;
    addItem(visNode);

    return visNode;
}

GraphVisEdge *GraphScene::addEdge(GraphVisNode *source, GraphVisNode *destin)
{
    GraphEdge *edge = graphModel->addEdge(source->mdata, destin->mdata);
    GraphVisEdge *visEdge = new GraphVisEdge(edge);

    edge->mdata = visEdge;
    addItem(visEdge);
    update();

    return visEdge;
}

void GraphScene::addComment(GraphVisNode *node, QString commentText, QPointF pos)
{
    QGraphicsTextItem* comment = new QGraphicsTextItem(commentText, node);
    node->mdata->comment = comment->document();
    comment->setPos(pos);
    comment->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    //Item is already added when created by passing parent
}

void GraphScene::addComment(GraphVisEdge *edge, QString commentText, QPointF pos)
{
    QGraphicsTextItem* comment = new QGraphicsTextItem(commentText, edge);
    edge->mdata->comment = comment->document();
    comment->setPos(pos);
    comment->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void GraphScene::init()
{

}

GraphModel *GraphScene::getGraphModel() const
{
    return graphModel;
}

void GraphScene::setGraphModel(GraphModel *value)
{
    graphModel = value;
}
