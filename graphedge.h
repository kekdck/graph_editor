#ifndef GRAPHEDGE_H
#include <QGraphicsLineItem>
#include <QPainter>
#define GRAPHEDGE_H



class GraphEdge: public QGraphicsLineItem
{
public:
    GraphEdge(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent = 0);

    void adjustSource(QPointF &source);
    void adjustDest(QPointF &dest);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF sourcePoint;
    QPointF destPoint;

};

#endif // GRAPHEDGE_H
