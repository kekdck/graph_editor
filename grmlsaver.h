#ifndef GRMLSAVER_H
#define GRMLSAVER_H

#include <tinyxml2.h>
#include <QList>
#include <QString>

#include "graphnode.h"
#include "graphedge.h"
#include "graphmodel.h"

using namespace tinyxml2;


class GrmlSaver
{
public:
    GrmlSaver();

    void addKey(char *id, char *item, char *type);
    XMLElement *addNode(GraphNode* node);
    XMLElement* addEdge(GraphEdge* edge);

public slots:
    void save(GraphModel* model, QString filename);

private:
    QString fileName;

    XMLDocument* doc;
    XMLElement* root;
    XMLElement* graphBegin;

    QList<XMLElement* > keys;

};

#endif // GRMLSAVER_H
