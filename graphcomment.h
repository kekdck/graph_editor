#ifndef GRAPHCOMMENT_H
#define GRAPHCOMMENT_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPainter>


class GraphComment : public QGraphicsTextItem
{
    Q_OBJECT
public:
    GraphComment(const QString& text, QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

};

#endif // GRAPHCOMMENT_H
