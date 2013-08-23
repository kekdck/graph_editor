#ifndef GraphNode_H
#define GraphNode_H
#include <QFileSystemModel>
#include <QGraphicsScene>
#include <QDebug>
#include <QFileInfo>
#include "graphitem.h"
#include "graphvisnode.h"

class GraphEdge;

class GraphNode: public GraphItem
{
public:
    explicit GraphNode(QFileInfo *_fileInfo);
    GraphNode();

    QString fileName();
    QString filePath();

    void addOutEdge(GraphEdge *edge);
    void addInEdge(GraphEdge *edge);

    bool connectedDirectlyTo(GraphNode *);
    int connections();

    void removeEdge(GraphEdge *edge);
    void eraseEdges();

    GraphVisNode *mdata;

    QList<GraphEdge *> getOutEdges();
    QList<GraphEdge *> getInEdges();
    QFileInfo *getFileInfo() const;
    void setFileInfo(QFileInfo *value);

    friend QDebug operator<< (QDebug d, GraphNode &node);

private:
    QModelIndex fileIndex;
    QFileSystemModel *fileModel;

    QFileInfo *fileInfo;

    QList<GraphEdge *> outEdges;
    QList<GraphEdge *> inEdges;
};

Q_DECLARE_METATYPE(GraphNode *)

#endif // GraphNode_H
