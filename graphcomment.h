#ifndef GRAPHCOMMENT_H
#define GRAPHCOMMENT_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

class GraphComment : public QGraphicsTextItem
{
public:
    GraphComment(const QString& text, QGraphicsItem* parent);
private:
    QGraphicsRectItem* blob;
};

#endif // GRAPHCOMMENT_H
