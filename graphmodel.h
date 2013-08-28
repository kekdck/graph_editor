#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QAbstractListModel>
#include "graphedge.h"
#include "graphnode.h"

class GraphModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemDataRole {
        RefNodeRole = Qt::UserRole + 1,
        RefEdgeRole = Qt::UserRole + 2
    };

    explicit GraphModel(QObject *parent = 0);
    virtual ~GraphModel();
    
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    int edgeCount();

    bool disconnectNodes(GraphNode *, GraphNode *);
    void eraseEdges(GraphNode *);

    GraphEdge *addEdge(GraphNode *, GraphNode *);
    GraphNode *addNode(QFileInfo *_fileinfo);

    void removeEdge(GraphEdge *);
    void removeNode(GraphNode *);

    QVector<GraphEdge *> getEdges() const;
    void setEdges(const QVector<GraphEdge *> &value);

    QVector<GraphNode *> getNodes() const;
    void setNodes(const QVector<GraphNode *> &value);


private:
    QVector<GraphEdge *> edges;
    QVector<GraphNode *> nodes;

public slots:
};

#endif // GRAPHMODEL_H
