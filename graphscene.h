#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QList>

#include "graphcomment.h"
#include "graphnode.h"
#include "graphedge.h"


class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(QObject *parent = 0);
    GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);

    void addNode(QFileInfo _fileinfo);
    void addEdge(GraphNode* source, GraphNode* destin);
    void addComment(QGraphicsItem* node);

};

#endif // GRAPHSCENE_H