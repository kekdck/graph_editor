#include "graphmlsaver.h"

GraphMlSaver::GraphMlSaver(QString filePath)
{
    file.setFileName(filePath);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "fileOpeningError";
        return;
    }

    writer = new QXmlStreamWriter(&file);
    writer->setAutoFormatting(true);
}

void GraphMlSaver::addKey(QString id, QString item, QString type)
{
    writer->writeStartElement("key");

    writer->writeAttribute("id", id);
    writer->writeAttribute("for", item);
    writer->writeAttribute("attr.name", id);
    writer->writeAttribute("attr.type", type);

    writer->writeEndElement();
}


void GraphMlSaver::addNode(GraphNode *node)
{
    writer->writeStartElement("node");
    writer->writeAttribute("id", QString::number(node->getId()));

    addData("path", node->filePath());

    addData("x", QString::number(node->mdata->x()));
    addData("y", QString::number(node->mdata->y()));


    //write comment data
    if (node->getCommentText() != QString(""))
    {
        addData("comment", node->getCommentText());
        addData("xComment", QString::number(node->mdata->childItems().first()->x()));
        addData("yComment", QString::number(node->mdata->childItems().first()->y()));
    }

    writer->writeEndElement();//node
}

void GraphMlSaver::addEdge(GraphEdge *edge)
{
    writer->writeStartElement("edge");
    writer->writeAttribute("source", QString::number(edge->getSrc()->getId()));
    writer->writeAttribute("target",  QString::number(edge->getDest()->getId()));

    //write comment data
    if (edge->getCommentText() != QString(""))
    {        
        addData("comment", edge->getCommentText());
        addData("xComment", QString::number(edge->mdata->childItems().first()->x()));
        addData("yComment", QString::number(edge->mdata->childItems().first()->y()));
    }

    writer->writeEndElement();//node
}


void GraphMlSaver::addGraph(QString id)
{
    writer->writeStartElement("graph"); //Open graph tag
    writer->writeAttribute("id", id);

    foreach(GraphNode* node, model->getNodes())
    {
        addNode(node);
    }

    foreach(GraphEdge* edge, model->getEdges())
    {
        addEdge(edge);
    }

    writer->writeEndElement();//Close graph tag
}


void GraphMlSaver::addData(QString key, QString value)
{
    writer->writeStartElement("data");
    writer->writeAttribute("id", key);
    writer->writeCDATA(value);
    writer->writeEndElement();//data comment

}

void GraphMlSaver::save(GraphModel *_model)
{
    model = _model;

    writer->writeStartDocument();

    writer->writeStartElement("graphml");//Open graphml tag
    writer->writeAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns");

    //Set keys for node
    addKey("type", "node", "string");
    addKey("path", "node", "string");
    addKey("comment", "node", "string");
    //just in case
    addKey("x", "node", "double");
    addKey("y", "node", "double");

    //Set keys for edge
    addKey("comment", "edge", "string");
    addKey("x", "edge", "double");
    addKey("y", "edge", "double");

    addGraph();

    writer->writeEndElement();//graphml
}

