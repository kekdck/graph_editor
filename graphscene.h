#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
<<<<<<< HEAD
#include <QList>

#include "graphcomment.h"
#include "graphnode.h"
#include "graphedge.h"


class GraphScene : public QGraphicsScene
{
public:
    GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);

    void addNode(QFileInfo _fileinfo);
    void addEdge(GraphNode* source, GraphNode* destin);
    void addComment(QGraphicsItem* node);
=======

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(QObject *parent = 0);
    GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    
signals:
    
public slots:

    void zoomIn();

    void zoomOut();
>>>>>>> b261cf3054b31b0477d9c90fd98ea0b393a413d7
};

#endif // GRAPHSCENE_H
