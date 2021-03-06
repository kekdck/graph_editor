#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QList>

#include "graphnode.h"
#include "graphedge.h"

#include "graphvisnode.h"
#include "graphvisedge.h"

#include "graphmodel.h"

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(QObject *parent = 0);
    GraphScene(GraphModel *mod, qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);

    GraphVisNode *addNode(QFileInfo *_fileinfo);
    GraphVisEdge *addEdge(GraphVisNode* source, GraphVisNode* destin);

    void addComment(GraphVisNode* node, QString commentText = "type comment here", QPointF pos = QPointF(0,0));
    void addComment(GraphVisEdge *edge, QString commentText = "type comment here", QPointF pos = QPointF(0,0));

    void init();


    QList<GraphVisNode *> selectedNodes();
    QList<GraphVisEdge *> selectedEdges();

    QFileSystemModel *getFileModel() const;
    void setFileModel(QFileSystemModel *value);

    GraphModel *getGraphModel() const;
    void setGraphModel(GraphModel *value);

    QList<GraphVisNode *> nodes();
    QPointF cg(QList<GraphVisNode *> l = QList<GraphVisNode *>());
private:

    QFileSystemModel *fileModel;
    GraphModel *graphModel;

public slots:

};

#endif // GRAPHSCENE_H
