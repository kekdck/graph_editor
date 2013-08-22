#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QAbstractListModel>
#include "graphedge.h"
#include "graphnode.h"

class GraphModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GraphModel(QObject *parent = 0);
    
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    GraphEdge *addEdge(GraphNode *, GraphNode *);
    GraphNode *addNode(QFileInfo *_fileinfo);

signals:

private:
    QVector<GraphEdge *> edges;
    QVector<GraphNode *> nodes;
    
public slots:
    
};

#endif // GRAPHMODEL_H
