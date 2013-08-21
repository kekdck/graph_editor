#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

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
};

#endif // GRAPHSCENE_H
