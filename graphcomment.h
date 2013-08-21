#ifndef GRAPHCOMMENT_H
#define GRAPHCOMMENT_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPainter>


class GraphComment : public QGraphicsTextItem
{
public:
    enum { Type = UserType + 3 };
    GraphComment(const QString& text, QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:

};

#endif // GRAPHCOMMENT_H
