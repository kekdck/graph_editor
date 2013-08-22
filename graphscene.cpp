#include "graphscene.h"

GraphScene::GraphScene(QObject *parent) :
    QGraphicsScene(parent)
{
    init();
}

GraphScene::GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
    init();
}

void GraphScene::refreshItemProps()
{
    //Check if only 1 element selected
    QList <QGraphicsItem *> selection = selectedItems();
    if (selection.isEmpty()) return;
    //Check if it is Node
    GraphNode *item = qgraphicsitem_cast<GraphNode *>(selection.first());
    if (!item) return;

    for (int i = 0; i < 10; i++)
    {
        curItemPropModel->setData(QModelIndex(), item->data(i));
    }
//    QModelIndex index = model->index(item->filePath());
//    ui->treeView->scrollTo(index);
//    ui->treeView->setCurrentIndex(index);
}

QFileSystemModel *GraphScene::getFileModel() const
{
    return fileModel;
}

void GraphScene::setFileModel(QFileSystemModel *value)
{
    fileModel = value;
}

void GraphScene::addNode(QFileInfo _fileinfo)
{
    GraphNode* node = new GraphNode(_fileinfo);

    node->setBrush(QBrush( (_fileinfo.isDir()) ? Qt::green : Qt::yellow));
    addItem(node);
}

void GraphScene::addEdge(GraphNode *source, GraphNode *destin)
{
    GraphEdge *edge = new GraphEdge(source, destin);

    addItem(edge);
}

QStandardItemModel *GraphScene::getCurItemPropModel() const
{
    return curItemPropModel;
}

void GraphScene::setCurItemPropModel(QStandardItemModel *value)
{
    curItemPropModel = value;
}

void GraphScene::addComment(QGraphicsItem *node)
{
    GraphComment* comment = new GraphComment("default", node);

    addItem(comment);
}

void GraphScene::init()
{
    curItemPropModel = new QStandardItemModel(10, 1, this);
    QStringList rows;
    rows    << "Name"
            << "Connections"
            << "FileName"
            << "Path"
            << "Color"
            << "X"
            << "Y"
            << "Comment";
    curItemPropModel->setVerticalHeaderLabels(rows);
}
