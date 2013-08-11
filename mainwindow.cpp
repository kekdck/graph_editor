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

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    QList<int> sizes;
    sizes.push_back(150);
    sizes.push_back(600);
    ui->splitter->setSizes(sizes);


    scene = new QGraphicsScene(this);
    ui->gridCheckBox->setChecked(true);
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
            GraphEdge* edge = new GraphEdge(lastItem, firstItem);

            firstItem->addOutEdge(edge);
            lastItem->addInEdge(edge);

            scene->addItem(edge);
#ifdef QT_DEBUG
    qDebug() << "created" << *edge;
#endif //QT_DEBUG
        }
    }

    scene->clearSelection();
    scene->update();
}

void MainWindow::on_zoomInButton_clicked()
{
    ui->graphicsView->scale(1.2, 1.2);
}

void MainWindow::on_zoomOutButton_clicked()
{
    ui->graphicsView->scale(1/1.2, 1/1.2);
}

void MainWindow::on_gridCheckBox_stateChanged(int arg1)
{
    if (arg1)
    {
        scene->setBackgroundBrush(QBrush(QColor(150,150,150), Qt::CrossPattern));
    }
    else
    {
        scene->setBackgroundBrush(QBrush(QColor(255,255,255)));
    }
    scene->update();
}
