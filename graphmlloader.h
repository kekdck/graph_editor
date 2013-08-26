#ifndef GRAPHMLLOADER_H
#define GRAPHMLLOADER_H

#include <QXmlStreamReader>
#include <QMessageBox>
#include <QFileInfo>

#include "graphvisnode.h"
#include "graphvisedge.h"
#include "graphscene.h"


class GraphMlLoader
{
public:
    GraphMlLoader(const QString filePath);

    void getNode();
    void getEdge();

    GraphScene* getGraph();
private:
    GraphModel *Gmodel;
    GraphScene *graph;
    QXmlStreamReader reader;
};

#endif // GRAPHMLLOADER_H
