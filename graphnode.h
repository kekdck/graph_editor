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
    virtual ~GraphNode();

    QString fileName();
    QString filePath();

    void addOutEdge(GraphEdge *edge);
    void addInEdge(GraphEdge *edge);

    GraphEdge *connectedDirectlyTo(GraphNode *);
    int connections();

    void removeEdge(GraphEdge *edge);
    void eraseEdges();
    void setName(QString);

    GraphVisNode *mdata;

    QList<GraphEdge *> getOutEdges();
    QList<GraphEdge *> getInEdges();
    QFileInfo *getFileInfo() const;
    void setFileInfo(QFileInfo *value);

    friend QDebug operator<< (QDebug d, GraphNode &node);

    int getId() const;
    void setId(int value);

private:
    QFileInfo *fileInfo;

    QList<GraphEdge *> outEdges;
    QList<GraphEdge *> inEdges;

    qint64 id;
};

Q_DECLARE_METATYPE(GraphNode *)

#endif // GraphNode_H
