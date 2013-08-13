#ifndef GRAPHCOMMENT_H
#define GRAPHCOMMENT_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPainter>

class GraphComment : public QGraphicsTextItem
{
public:
    GraphComment(const QString& text, QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QGraphicsRectItem* blob;
};

#endif // GRAPHCOMMENT_H
