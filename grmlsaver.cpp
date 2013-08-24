#include "grmlsaver.h"

GrmlSaver::GrmlSaver()
{
    doc = new XMLDocument();
    root = doc->NewElement( "graphml" );
    doc->InsertEndChild(root);

    root->SetAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns");

    //Set keys for node
    addKey("type", "node", "srting");
    addKey("path", "node", "string");
    addKey("comment", "node", "string");
    //jsut in case
    addKey("x", "node", "int");
    addKey("y", "node", "int");

    //Set keys for edge
    addKey("comment", "edge", "string");

    //Graph representation
    graphBegin = doc->NewElement("graph");
    root->InsertEndChild(graphBegin);

    graphBegin->SetAttribute("id", (char*)fileName.constData());
}

void GrmlSaver::addKey(char* id, char* item, char* type)
{

    XMLElement* key;
    key = doc->NewElement("key");
    key->SetAttribute("id", id);
    key->SetAttribute("for", item);
    key->SetAttribute("attr.name", id);
    key->SetAttribute("attr.type", type);

    keys.append(key);

    root->InsertFirstChild(key);
}

XMLElement* GrmlSaver::addNode(GraphNode *node)
{
    XMLElement* nodeXML = doc->NewElement("node");
    nodeXML->SetAttribute("id", node->getId());

    XMLElement* pathData = doc->NewElement("data");
    XMLElement* commentData = doc->NewElement("data");

    pathData->SetAttribute("id", "path");

    if (node->getCommentText() != QString(""))
    {
        XMLText* commentText = doc->NewText(node->getCommentText().toStdString().c_str());
        commentText->SetCData(true); //For ignoring HTML marking

        commentData->SetAttribute("id", "comment");
        commentData->InsertFirstChild(commentText);
        nodeXML->InsertEndChild(commentData);
    }


    pathData->InsertFirstChild(doc->NewText(node->filePath().toStdString().c_str()));

    nodeXML->InsertEndChild(pathData);

    graphBegin->InsertFirstChild(nodeXML);
}

XMLElement *GrmlSaver::addEdge(GraphEdge *edge)
{
    XMLElement *edgeXML = doc->NewElement("edge");
    edgeXML->SetAttribute("source",edge->getSrc()->getId());
    edgeXML->SetAttribute("target",edge->getDest()->getId());

    XMLElement* commentData = doc->NewElement("data");
    XMLText* commentText = doc->NewText(edge->getCommentText().toStdString().c_str());
    commentText->SetCData(true); //For ignoring HTML marking
    commentData->InsertFirstChild(commentText);

    edgeXML->InsertEndChild(commentData);

    graphBegin->InsertEndChild(edgeXML);
}


void GrmlSaver::save(GraphModel* model, QString filename)
{
    foreach(GraphNode* node, model->getNodes())
    {
        addNode(node);
    }

    foreach(GraphEdge* edge, model->getEdges())
    {
        addEdge(edge);
    }

    doc->SaveFile(filename.toStdString().c_str());
}



