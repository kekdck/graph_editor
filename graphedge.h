#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
#include <QGraphicsLineItem>
#include <QPainter>

class GraphNode;

class GraphEdge: public QGraphicsLineItem
{
public:
    enum { Type = UserType + 2 };
    GraphEdge(GraphNode *source, GraphNode *destin, QGraphicsItem* parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;

    friend QDebug operator<< (QDebug d, GraphEdge &edge);


    GraphNode *getSrc() const;
    void setSrc(GraphNode *value);

    GraphNode *getDest() const;
    void setDest(GraphNode *value);

private:
    GraphNode *src;
    GraphNode *dest;

};

#endif // GRAPHEDGE_H
