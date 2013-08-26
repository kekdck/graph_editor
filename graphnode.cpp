#include "graphnode.h"
#include "graphedge.h"

GraphNode::GraphNode()
{
    comment = NULL;
}

GraphNode::~GraphNode()
{
    qDebug() << "Deleting > " << *this;
    foreach(GraphEdge *e, inEdges)
    {
        e->getSrc()->removeEdge(e);
        delete e;
    }
    foreach(GraphEdge *e, outEdges)
    {
        e->getDest()->removeEdge(e);
        delete e;
    }
    delete fileInfo;
    delete mdata;
}

GraphNode::GraphNode(QFileInfo *_fileInfo) : fileInfo(_fileInfo)
{
    comment = NULL;
    name = _fileInfo->fileName();
}

void GraphNode::eraseEdges()
{
    foreach(GraphEdge *e, inEdges)
    {
        e->getSrc()->removeEdge(e);
    }
    qDeleteAll(inEdges);
    foreach(GraphEdge *e, outEdges)
    {
        e->getDest()->removeEdge(e);
    }
    qDeleteAll(outEdges);
}

QList<GraphEdge *> GraphNode::getOutEdges()
{
    return outEdges;
}

QFileInfo *GraphNode::getFileInfo() const
{
    return fileInfo;
}

void GraphNode::setFileInfo(QFileInfo *value)
{
    fileInfo = value;
}

QDebug operator<<(QDebug d, GraphNode &node)
{
    d << "Name: " << node.name
      //<< ", comment: " << node.comment->toPlainText()
      << ", connections: " << node.connections();
    return d;
}

QString GraphNode::fileName()
{
    return fileInfo->fileName();
}

QString GraphNode::filePath()
{
    return fileInfo->filePath();
}

void GraphNode::addOutEdge(GraphEdge * edge)
{
    outEdges << edge;
}

void GraphNode::addInEdge(GraphEdge *edge)
{
    inEdges << edge;
}

GraphEdge *GraphNode::connectedDirectlyTo(GraphNode *node)
{
    foreach(GraphEdge *edge, inEdges)
    {
        if (edge->getSrc() == node)
        {
            return edge;
        }
    }
    foreach(GraphEdge *edge, outEdges)
    {
        if (edge->getDest() == node)
        {
            return edge;
        }
    }
    return NULL;
}

int GraphNode::connections()
{
    return inEdges.size() + outEdges.size();
}

void GraphNode::removeEdge(GraphEdge *edge)
{
    if (!inEdges.removeOne(edge))
        outEdges.removeOne(edge);
}

QList<GraphEdge *> GraphNode::getInEdges()
{
    return inEdges;
}

int GraphNode::getId() const
{
    return id;
}

void GraphNode::setId(int value)
{
    id = value;
}
