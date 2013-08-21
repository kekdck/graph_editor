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
    sizes << 150 << 600;
    ui->splitter->setSizes(sizes);

    scene = new GraphScene(-1000, -1000, 2000, 2000, this);

    ui->gridCheckBox->setChecked(true);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(refreshItemProps()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    refreshItemProps();
}

void MainWindow::on_pushAddButton_clicked()
{
    //get selected item in treeView
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;

    scene->addNode(model->fileInfo(index));

}

void MainWindow::on_pushRemoveButton_clicked()
{
    if (list.isEmpty()) return;
    QList <QGraphicsItem *> items = scene->selectedItems();
    foreach(QGraphicsItem *item, items)
    {
        GraphNode *grit = qgraphicsitem_cast<GraphNode *>(item);
        if (grit)
        {
            grit->eraseEdges();
            scene->removeItem(grit);
            list.removeOne(grit);
        }
    }

    scene->clearSelection();

    refreshItemProps();

    scene->update();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Shift:
        {
            ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        }break;
    default:
        {
            //some default action?
        }break;
    }
    QMainWindow::keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Shift:
        {
            ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        }break;
    default:
        {

        }break;
    }
    QMainWindow::keyReleaseEvent(e);
}

void MainWindow::on_actionNew_triggered()
{
    foreach (GraphNode *item, list)
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
        GraphNode* firstItem = qgraphicsitem_cast<GraphNode* >(items.first());
        GraphNode* lastItem  = qgraphicsitem_cast<GraphNode* >(items.last());

        if (firstItem && lastItem)
        {            
            scene->addEdge(lastItem, firstItem);
        }
    }

    scene->clearSelection();
    scene->update();
}

void MainWindow::on_gridCheckBox_stateChanged(int arg1)
{
    if (arg1)
    {
        scene->setBackgroundBrush(QBrush(QColor(150,150,150), Qt::CrossPattern));
        setProperty("Grid", QVariant(true));
    }
    else
    {
        scene->setBackgroundBrush(QBrush(QColor(255,255,255)));
        setProperty("Grid", QVariant(false));
    }
    scene->update();
}

void MainWindow::refreshItemProps()
{
    QList <QGraphicsItem *> selection = scene->selectedItems();
    if (selection.count() == 0)
    {
        ui->propTreeView->setModel(0);
        return;
    }
    if (selection.count() != 1) return;

    GraphNode *item = qgraphicsitem_cast<GraphNode* >(selection.first());
    if (!item) return;
    curItemPropModel = item->model();
    ui->propTreeView->setModel(curItemPropModel);

    QModelIndex index = model->index(item->filePath());
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
}

void MainWindow::on_pushCommentButton_clicked()
{
    QList<QGraphicsItem* > items =  scene->selectedItems();

    if(items.length() == 1 && items.first()->childItems().count() < 2)
    {
        scene->addComment(items.first());
    }
}
