#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
#include <QGraphicsLineItem>
#include <QPainter>

class GraphItem;

class GraphEdge: public QGraphicsLineItem
{
public:
    GraphEdge(GraphItem *source, GraphItem *destin, QGraphicsItem* parent = 0);

    void setSource(GraphItem *source);
    void setDest(GraphItem *dest);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    GraphItem *src;
    GraphItem *dest;
};

#endif // GRAPHEDGE_H
