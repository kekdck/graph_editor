#include "graphedge.h"
#include "graphnode.h"

GraphEdge::GraphEdge()
{
}

GraphEdge::GraphEdge(GraphNode *source, GraphNode *destin)
{
    if (!source || !destin)
    {
        qDebug() << "Wrong node given to edge";
        return;
    }

    src = source;
    dest = destin;

    src->addOutEdge(this);
    dest->addInEdge(this);
}

GraphNode *GraphEdge::getDest() const
{
    return dest;
}

void GraphEdge::setDest(GraphNode *value)
{
    dest = value;
}

QDebug operator<<(QDebug d, GraphEdge &edge)
{
    d << edge.getSrc()->name << " to " << edge.getDest()->name;
    return d;
}

GraphNode *GraphEdge::getSrc() const
{
    return src;
}

void GraphEdge::setSrc(GraphNode *value)
{
    src = value;
}
