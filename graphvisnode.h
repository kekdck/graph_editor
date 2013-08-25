#ifndef GRAPHVISNODE_H
#define GRAPHVISNODE_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QFileInfo>

class GraphNode;
class GraphEdge;

class GraphVisNode : public QGraphicsRectItem
{
public:
    enum { Type = UserType + 1 };
    GraphVisNode(GraphNode *data, qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //Selection events
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;

    //Delegation block
    QString fileName();
    QString filePath();
    void addOutEdge(GraphEdge *edge);
    void addInEdge(GraphEdge *edge);

    GraphEdge *connectedDirectlyTo(GraphNode *);
    int connections();

    void removeEdge(GraphEdge *edge);
    void eraseEdges();
    //////

    friend QDebug operator<< (QDebug d, GraphVisNode &item);
    GraphNode *mdata;
private:

    QTextDocument *comment;
    QGraphicsTextItem *nameText;

    QFileInfo *fileInfo;

};

#endif // GRAPHVISNODE_H
