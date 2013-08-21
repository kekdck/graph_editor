#ifndef GraphNode_H
#define GraphNode_H
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QString>
#include <QPainter>
#include <QGraphicsScene>
#include <QFile>
#include <QTreeView>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDebug>
#include <QList>
#include <QVariant>
#include <QFileInfo>

class GraphEdge;

const int WIDTH = 20;
const int HEIGHT = 20;

class GraphNode: public QGraphicsRectItem
{
public:
    GraphNode(QFileInfo _fileInfo, qreal x=0, qreal y=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    QString fileName();
    QString filePath();

    void addOutEdge(GraphEdge* edge);
    void addInEdge(GraphEdge* edge);

    void eraseEdges();

    QStandardItemModel* model();

    //Selection events
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;


    friend QDebug operator<< (QDebug d, GraphNode &item);
protected:

private:
    QStandardItemModel *propModel;
    QGraphicsTextItem *nameText;

    QModelIndex fileIndex;
    QFileSystemModel *fileModel;

    QFileInfo fileInfo;

    QList<GraphEdge *> outEdges;
    QList<GraphEdge *> inEdges;
};

#endif // GraphNode_H
