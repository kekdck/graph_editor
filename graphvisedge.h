#ifndef GRAPHVISEDGE_H
#define GRAPHVISEDGE_H

#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include "graphvisnode.h"

class GraphEdge;

class GraphVisEdge : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 2 };
    explicit GraphVisEdge(GraphEdge *_data, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;

    friend QDebug operator<< (QDebug d, GraphVisEdge &edge);

    GraphEdge *mdata;
private:

    GraphVisNode *src, *dest;

};

#endif // GRAPHVISEDGE_H
