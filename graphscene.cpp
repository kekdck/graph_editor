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
    commentText = "<div style='background-color:#FFFFFF;'>" + commentText + "</div>";
    QGraphicsTextItem* comment = new QGraphicsTextItem(node);
    comment->setHtml(commentText);
    node->mdata->comment = comment->document();
    comment->setPos(pos);
    comment->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    //Item is already added when created by passing parent
}

void GraphScene::addComment(GraphVisEdge *edge, QString commentText, QPointF pos)
{
    commentText = "<div style='background-color:#FFFFFF;'>" + commentText + "</div>";
    QGraphicsTextItem* comment = new QGraphicsTextItem(edge);
    comment->setHtml(commentText);
    edge->mdata->comment = comment->document();
    comment->setPos(pos);
    comment->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void GraphScene::init()
{

}

QList<GraphVisNode *> GraphScene::nodes()
{
    QList<QGraphicsItem *> items = this->items();
    QList<GraphVisNode *> gvns;
    foreach (QGraphicsItem *it, items)
    {
        GraphVisNode *gvn = dynamic_cast<GraphVisNode *>(it);
        if (gvn)
        {
            gvns.push_back(gvn);
        }
    }
    return gvns;
}

QPointF GraphScene::cg(QList<GraphVisNode *> l)
{
    if (l == QList<GraphVisNode *>())
    {
         l = nodes();
    }
    if (l.size() == 0)
    {
        return QPointF(0,0);
    }
    QPointF t(0,0);
    foreach(GraphVisNode *gvn, l)
    {
        t += gvn->pos();
    }
    return t/l.size();
}

QList<GraphVisNode *> GraphScene::selectedNodes()
{
    QList<QGraphicsItem *> items = selectedItems();
    QList<GraphVisNode *> gvns;
    foreach (QGraphicsItem *it, items)
    {
        GraphVisNode *gvn = dynamic_cast<GraphVisNode *>(it);
        if (gvn)
        {
            gvns.push_back(gvn);
        }
    }
    return gvns;
}

QList<GraphVisEdge *> GraphScene::selectedEdges()
{
    QList<QGraphicsItem *> items =  selectedItems();
    QList<GraphVisEdge *> gves;
    foreach (QGraphicsItem *it, items)
    {
        GraphVisEdge *gve = dynamic_cast<GraphVisEdge *>(it);
        if (gve)
        {
            gves.push_back(gve);
        }
    }
    return gves;
}

GraphModel *GraphScene::getGraphModel() const
{
    return graphModel;
}

void GraphScene::setGraphModel(GraphModel *value)
{
    graphModel = value;
}
