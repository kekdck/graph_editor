#ifndef GRAPHCOMMENT_H
#define GRAPHCOMMENT_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTextDocument>

class GraphComment : public QGraphicsTextItem
{
    Q_OBJECT
public:
    GraphComment(const QString& text, QGraphicsItem* parent);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private slots:

    void updateBlob();

private:
    QGraphicsRectItem* blob;

};

#endif // GRAPHCOMMENT_H
