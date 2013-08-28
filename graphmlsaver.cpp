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

    addData("name", node->name);
    addData("path", node->filePath());

    addData("x", QString::number(node->mdata->x()));
    addData("y", QString::number(node->mdata->y()));
    addData("color", node->mdata->brush().color().name());

    //write comment data
    if (node->getCommentText() != QString(""))
    {
        addData("comment", node->getCommentText());
        addData("comx", QString::number(node->mdata->childItems().first()->x()));
        addData("comy", QString::number(node->mdata->childItems().first()->y()));
    }

    writer->writeEndElement();//node
}

void GraphMlSaver::addEdge(GraphEdge *edge)
{
    writer->writeStartElement("edge");
    writer->writeAttribute("source", QString::number(edge->getSrc()->getId()));
    writer->writeAttribute("target", QString::number(edge->getDest()->getId()));

    addData("name", edge->name);
    addData("color", edge->mdata->pen().color().name());

    //write comment data
    if (edge->getCommentText() != QString(""))
    {        
        addData("comment", edge->getCommentText());
        addData("comx", QString::number(edge->mdata->childItems().first()->x()));
        addData("comy", QString::number(edge->mdata->childItems().first()->y()));
    }

    writer->writeEndElement();//edge
}


void GraphMlSaver::addGraph(QString id)
{
    writer->writeStartElement("graph"); //Open graph tag
    writer->writeAttribute("id", id);

    for (int i = 0; i < model->rowCount(); i++)
    {
        GraphNode *node = qvariant_cast<GraphNode *>(model->data(model->index(i),
                                                                 GraphModel::ItemDataRole::RefNodeRole));
        addNode(node);
    }

    for (int i = 0; i < model->edgeCount(); i++)
    {
        GraphEdge *edge = qvariant_cast<GraphEdge *>(model->data(model->index(i),
                                                                 GraphModel::ItemDataRole::RefEdgeRole));
        addEdge(edge);
    }

    writer->writeEndElement();//Close graph tag
}


void GraphMlSaver::addData(QString key, QString value, bool cdata)
{
    writer->writeStartElement("data");
    writer->writeAttribute("id", key);
    if(cdata == true)
    {
        writer->writeCDATA(value);
    }
    else
    {
        writer->writeCharacters(value);
    }
    writer->writeEndElement();//data

}

void GraphMlSaver::save(GraphModel *_model)
{
    model = _model;

    writer->writeStartDocument();

    writer->writeStartElement("graphml");//Open graphml tag
    writer->writeAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns");

    //Set keys for node
    addKey("type", "node", "string");
    addKey("name", "node", "string");
    addKey("path", "node", "string");
    addKey("x", "node", "double");
    addKey("y", "node", "double");
    addKey("color", "node", "QColor");
    addKey("comment", "node", "string");

    //Keys for comment
    addKey("comx", "comment", "double");
    addKey("comy", "comment", "double");

    //Set keys for edge
    addKey("name", "node", "string");
    addKey("x", "edge", "double");
    addKey("y", "edge", "double");
    addKey("color", "edge", "QColor");
    addKey("comment", "edge", "string");

    addGraph();

    writer->writeEndElement();//graphml
}

