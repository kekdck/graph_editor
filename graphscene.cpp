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

void GraphScene::addNode(QFileInfo *_fileinfo)
{
    GraphNode *node = graphModel->addNode(_fileinfo);
    GraphVisNode *visNode = new GraphVisNode(node, 0, 0, 20, 20);

    node->mdata = visNode;
    addItem(visNode);
}

void GraphScene::addEdge(GraphVisNode *source, GraphVisNode *destin)
{
    GraphEdge *edge = graphModel->addEdge(source->mdata, destin->mdata);
    GraphVisEdge *visEdge = new GraphVisEdge(edge);

    edge->mdata = visEdge;
    addItem(visEdge);
    update();
}

void GraphScene::addComment(GraphVisNode *node)
{
    QGraphicsTextItem* comment = new QGraphicsTextItem("Type text here", node);
    node->mdata->comment = comment->document();
    comment->setPos(node->boundingRect().center().x() + 30,
                    node->boundingRect().center().y() + 30);
    comment->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    //Item is already added when created by passing parent
}

void GraphScene::addComment(GraphVisEdge *edge)
{
    QGraphicsTextItem* comment = new QGraphicsTextItem("Type text here", edge);
    edge->mdata->comment = comment->document();
    comment->setPos(edge->boundingRect().center().x() + 10,
                    edge->boundingRect().center().y() + 15);
    comment->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void GraphScene::init()
{

}
