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

    void addNode(QFileInfo *_fileinfo);
    void addEdge(GraphVisNode* source, GraphVisNode* destin);
    void addComment(GraphVisNode* node);
    void addComment(GraphVisEdge *edge);

    void init();

    QFileSystemModel *getFileModel() const;
    void setFileModel(QFileSystemModel *value);

private:

    QFileSystemModel *fileModel;
    GraphModel *graphModel;

public slots:

};

#endif // GRAPHSCENE_H
