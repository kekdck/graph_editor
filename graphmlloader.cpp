#include "graphmlloader.h"

GraphMlLoader::GraphMlLoader(const QString filePath)
{
    QFile *file = new QFile(filePath);

    if (!file->open((QIODevice::ReadOnly | QIODevice::Text)))
    {
        QMessageBox::critical(0, "Error", "Error occured while trying to open file.",
                              QMessageBox::Ok, QMessageBox::NoButton);
    }


    Gmodel = new GraphModel();
    graph = new GraphScene(Gmodel, -1000, -1000, 2000, 2000, 0);

    reader.setDevice(file);
}

void GraphMlLoader::getNode()
{        
    QString path = "",
            comment = "",
            name = "";
    QPointF pos(0,0),
            compos(0,0);
    QColor  col;
    
    while(!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "node"))
    {
        if(reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "data") //We found "data"
        {

            //Read data's attributes
            QXmlStreamAttributes attributes = reader.attributes();

            reader.readNext();//Read data's attributes data

            if(attributes.value("id").toString() == "path")
            {
                path = reader.text().toString();
            }
            if(attributes.value("id").toString() == "x")
            {
                pos.setX(reader.text().toString().toDouble());
            }
            if(attributes.value("id").toString() == "y")
            {
                pos.setY(reader.text().toString().toDouble());
            }
            if(attributes.value("id").toString() == "comment")
            {
                comment = reader.text().toString();

                compos.setX(attributes.value("x").toString().toDouble());
                compos.setY(attributes.value("y").toString().toDouble());
            }
            if(attributes.value("id").toString() == "color")
            {
                col.setNamedColor(reader.text().toString());
            }
            if(attributes.value("id").toString() == "name")
            {
                name = reader.text().toString();
            }
        }
        reader.readNext();
    }
    
    if(path == "")
    {
        QMessageBox::warning(0, "Wrong path",
                             "Wrong path was given in "
                             + QString::number(reader.lineNumber())
                             + " line. \nNode will not be loaded.",
                             QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    
    QFileInfo *fileInfo = new QFileInfo(path);
    
    GraphVisNode* node = graph->addNode(fileInfo);
    node->setPos(pos);
    node->setColor(col);
    node->setNameText(name);

    if(comment != "")
    {
        graph->addComment(node, comment, compos);
    }
}

void GraphMlLoader::getEdge()
{
    QString comment = "";
    QPointF pos(0,0), compos(0,0);
    QColor col;

    int target_id = 0;
    int source_id = 0;

    if(reader.name() == "edge")
    {
        QXmlStreamAttributes attributes = reader.attributes();

        source_id = attributes.value("source").toString().toInt();
        target_id = attributes.value("target").toString().toInt();
    }

    while(!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "edge"))
    {
        if(reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "data")
        {
            QXmlStreamAttributes attributes = reader.attributes();

            reader.readNext();
            if(attributes.value("id").toString() == "comment")
            {
                comment = reader.text().toString();

                pos.setX(attributes.value("x").toString().toDouble());
                pos.setY(attributes.value("y").toString().toDouble());
            }
            if(attributes.value("color").toString() == "color")
            {
                col.setNamedColor(reader.text().toString());
            }
        }

        reader.readNext();
    }

    qDebug() << source_id << target_id;
    GraphVisNode *source_node = Gmodel->getNodes().at(source_id)->mdata;
    GraphVisNode *target_node = Gmodel->getNodes().at(target_id)->mdata;

    if(source_node!= NULL && target_node!=NULL)
    {
        qDebug() << "edge added";
        GraphVisEdge *edge = graph->addEdge(source_node, target_node);
        edge->setPos(pos);

        if(comment != "")
        {
            graph->addComment(edge, comment, compos);
        }
    }

}



GraphScene *GraphMlLoader::getGraph()
{
    
    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext(); 
        
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        
        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == "key" || reader.name() == "graph")
            {
                continue;
            }
            
            if(reader.name() == "node")
            {
                getNode();
            }
            if(reader.name() == "edge")
            {
                getEdge();
            }
        }
    }

    return graph;
}

