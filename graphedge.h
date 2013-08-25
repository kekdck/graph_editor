#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
#include "graphitem.h"
#include "graphvisedge.h"

class GraphNode;

class GraphEdge: public GraphItem
{
public:
    explicit GraphEdge(GraphNode *source, GraphNode *destin);
    GraphEdge();

    GraphNode *getSrc() const;
    void setSrc(GraphNode *value);

    GraphNode *getDest() const;
    void setDest(GraphNode *value);

    GraphVisEdge *mdata;

    friend QDebug operator<<(QDebug d, GraphEdge &edge);
    qint64 getId() const;
    void setId(const qint64 &value);

private:
    GraphNode *src;
    GraphNode *dest;
    qint64 id;
};

Q_DECLARE_METATYPE(GraphEdge *)

#endif // GRAPHEDGE_H
