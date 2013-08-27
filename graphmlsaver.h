#ifndef GRAPHMLSAVER_H
#define GRAPHMLSAVER_H

#include <QList>
#include <QString>
#include <QXmlStreamWriter>

#include "graphnode.h"
#include "graphedge.h"
#include "graphmodel.h"



class GraphMlSaver
{
public:
    GraphMlSaver(QString filePath);

    void addKey(QString id, QString item, QString type);

    void addNode(GraphNode* node);
    void addEdge(GraphEdge* edge);

    void addGraph(QString id = "");

    void addData(QString key, QString value, bool cdata = false);


public slots:
    void save(GraphModel* _model);

private:
    QFile file;

    QXmlStreamWriter *writer;

    GraphModel* model;
};

#endif // GRAPHMLSAVER_H

