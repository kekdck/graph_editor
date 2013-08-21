#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
#include <QGraphicsLineItem>
#include <QPainter>

class GraphNode;

class GraphEdge: public QGraphicsLineItem
{
public:
    GraphEdge(GraphNode *source, GraphNode *destin, QGraphicsItem* parent = 0);

    void setSource(GraphNode *source);
    void setDest(GraphNode *dest);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;

    friend QDebug operator<< (QDebug d, GraphEdge &edge);

    enum { Type = UserType + 2 };

private:
    GraphNode *src;
    GraphNode *dest;

};

#endif // GRAPHEDGE_H
