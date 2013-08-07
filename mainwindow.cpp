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
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
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

    list.push_back(item);
    ui->graphicsView->update();
#ifdef QT_DEBUG
    qDebug() << "Pushed index" <<  item->fileName();
#endif //QT_DEBUG
}

void MainWindow::on_pushRemoveButton_clicked()
{
    if (list.isEmpty()) return;
    QList <QGraphicsItem *> items = scene->selectedItems();
    foreach(QGraphicsItem *item, items)
    {
        GraphItem *grit = dynamic_cast<GraphItem *>(item);
        if (grit)
        {
            grit->eraseEdges();
            scene->removeItem(grit);
            list.removeOne(grit);
        }
    }
    scene->update();
}

void MainWindow::on_actionNew_triggered()
{
    foreach (GraphItem *item, list)
    {
        item->eraseEdges();
        scene->removeItem(item);
    }
    //Removing all thing from list
    list.erase(list.begin(), list.end());
    scene->update();
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
    scene->update();
}
