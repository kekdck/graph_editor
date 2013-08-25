#include "graphmodel.h"

GraphModel::GraphModel(QObject *parent) :
    QAbstractListModel(parent)
{
    next_id = 0;
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
    node->setId(next_id);
    next_id++;
    nodes.push_back(node);
    return node;
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
        return QVariant::fromValue(nodes.at(index.row()));
        break;
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
