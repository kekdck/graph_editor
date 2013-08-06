#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setting up model and treeView
    model = new QFileSystemModel(this);
    model->setRootPath("");
    ui->treeView->setModel(model);

    QModelIndex index = model->index("/");
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(1);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushAddButton_clicked()
{
    //get selected item in treeView
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;

    GraphItem* item = new GraphItem(10, 10, 20, 20);
    item->setFile(index, model);
    scene->addItem(item);

    //add edge from new item to the last
//    if(!list.isEmpty())
//    {
//        GraphEdge* edge = new GraphEdge(list.last(), item);

//        item->addOutEdge(edge);
//        list.last()->addInEdge(edge);

//        scene->addItem(edge);
//#ifdef QT_DEBUG
//        qDebug() << "Added edge from " << item->fileName() << " to " << list.last()->fileName();
//#endif //QT_DEBUG
//    }

    list.push_back(item);
    ui->graphicsView->update();
#ifdef QT_DEBUG
    qDebug() << "Pushed index" <<  item->fileName();
#endif //QT_DEBUG
}

void MainWindow::on_pushRemoveButton_clicked()
{
    if (list.isEmpty()) return;
    scene->removeItem(list.last());
    list.pop_back();
}

void MainWindow::on_pushConnectButton_clicked()
{
    QList<QGraphicsItem* > items =  scene->selectedItems();
    if (items.length() == 2)
    {
        GraphItem* firstItem = dynamic_cast<GraphItem* >(items.first());
        GraphItem* lastItem  = dynamic_cast<GraphItem* >(items.last());

        if (firstItem && lastItem)
        {
            QPointF source = lastItem->mapToScene(lastItem->boundingRect().center());
            QPointF dest = firstItem->mapToScene(firstItem->boundingRect().center());

            GraphEdge* edge = new GraphEdge(lastItem, firstItem);

            firstItem->addOutEdge(edge);
            lastItem->addInEdge(edge);

            scene->addItem(edge);
        }
    }

    scene->clearSelection();
}
