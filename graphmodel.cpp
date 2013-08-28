#include "graphmodel.h"

GraphModel::GraphModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

GraphModel::~GraphModel()
{
    //Edges are deleted while going through nodes list
    //as they each delete edges connected to themselves
    if (!nodes.isEmpty())
        qDeleteAll(nodes);
}

GraphEdge *GraphModel::addEdge(GraphNode *src, GraphNode *dest)
{
    if (src->connectedDirectlyTo(dest))
    {
        return 0; //Nodes are already connected by some edge
    }
    GraphEdge *edge = new GraphEdge(src, dest);
    edges.push_back(edge);
    return edge;
}

GraphNode *GraphModel::addNode(QFileInfo *_fileinfo)
{
    GraphNode *node = new GraphNode(_fileinfo);
    nodes.push_back(node);
    emit dataChanged( index(nodes.size() - 1), index(nodes.size() - 1) );
    node->setId(nodes.indexOf(node));
    return node;
}

void GraphModel::removeEdge(GraphEdge *e)
{
    int i = edges.indexOf(e);
    if (i < 0 || i > edges.size())
        return;
    e->getDest()->removeEdge(e);
    e->getSrc()->removeEdge(e);
    delete edges.at(i);
    edges.remove(i);
}

void GraphModel::removeNode(GraphNode *n)
{
    int i = nodes.indexOf(n);
    delete nodes.at(i);
    nodes.remove(i);
    emit dataChanged(index(i - 1), index(nodes.size()) );

    foreach(GraphNode *node, nodes)
    {
        node->setId(nodes.indexOf(node));
    }
}

int GraphModel::rowCount(const QModelIndex &parent) const
{
    return nodes.size();
}

bool GraphModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    switch (role)
    {
    case Qt::EditRole:
        GraphNode *n = value.value<GraphNode *>();
        if (n)
        {
            nodes.replace(index.row(), n);
        }
        GraphEdge *e = value.value<GraphEdge *>();
        if (e)
        {
            edges.replace(index.row(), e);
        }
        emit dataChanged(index, index);
    }
    return false;
}

QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= nodes.size())
    {
        return QVariant();
    }

    switch (role)
    {
    case Qt::DisplayRole:
        return QVariant(nodes.at(index.row())->name).toString();
    case RefNodeRole:
        return QVariant::fromValue(nodes.at(index.row()));
    case RefEdgeRole:
        return QVariant::fromValue(edges.at(index.row()));
    }
    return QVariant();
}

QVariant GraphModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("#%1").arg(section);
    else
        return QString("#%1").arg(section);
}

Qt::ItemFlags GraphModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

int GraphModel::edgeCount()
{
    return edges.size();
}

bool GraphModel::disconnectNodes(GraphNode *n1, GraphNode *n2)
{
    GraphEdge *e = n1->connectedDirectlyTo(n2);
    if (e)
    {
        removeEdge(e);
        return true;
    }
    return false;
}

void GraphModel::eraseEdges(GraphNode *n)
{
    foreach(GraphEdge *e, n->getInEdges())
    {
        e->getSrc()->removeEdge(e);
        delete e;
        n->removeEdge(e);
        edges.remove(edges.indexOf(e));
    }
    foreach(GraphEdge *e, n->getOutEdges())
    {
        e->getDest()->removeEdge(e);
        delete e;
        n->removeEdge(e);
        edges.remove(edges.indexOf(e));
    }
}

QVector<GraphNode *> GraphModel::getNodes() const
{
    return nodes;
}

void GraphModel::setNodes(const QVector<GraphNode *> &value)
{
    nodes = value;
}

QVector<GraphEdge *> GraphModel::getEdges() const
{
    return edges;
}

void GraphModel::setEdges(const QVector<GraphEdge *> &value)
{
    edges = value;
}
