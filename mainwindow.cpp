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

    scene = new QGraphicsScene(-1000, -1000, 2000, 2000, this);
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

    GraphItem* item = new GraphItem(10, 10, 20, 20);
    item->setFile(index, model);
    scene->addItem(item);

    ui->statusBar->showMessage("Added " + item->fileName(), 4000);
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
        GraphItem *grit = qgraphicsitem_cast<GraphItem *>(item);
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

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if (e->delta()>0)
    {
        zoomIn();
    }
    else
    {
        zoomOut();
    }
    return;
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
        GraphItem* firstItem = qgraphicsitem_cast<GraphItem* >(items.first());
        GraphItem* lastItem  = qgraphicsitem_cast<GraphItem* >(items.last());

        if (firstItem && lastItem)
        {
            GraphEdge* edge = new GraphEdge(lastItem, firstItem);

            edge->setFlags(QGraphicsItem::ItemIsSelectable
                           | QGraphicsItem::ItemSendsGeometryChanges);
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

void MainWindow::zoomIn()
{
    if (ui->graphicsView->matrix().m11() > 4) return;
    ui->graphicsView->scale(1.2, 1.2);
}

void MainWindow::zoomOut()
{
    if (ui->graphicsView->matrix().m11() < 0.4) return;
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

void MainWindow::refreshItemProps()
{
    QList <QGraphicsItem *> selection = scene->selectedItems();
    if (selection.count() == 0)
    {
        ui->propTreeView->setModel(0);
        return;
    }
    if (selection.count() != 1) return;

    GraphItem *item = qgraphicsitem_cast<GraphItem* >(selection.first());
    if (!item) return;
    curItemPropModel = item->model();
    ui->propTreeView->setModel(curItemPropModel);

    ui->treeView->scrollTo(item->index());
    ui->treeView->setCurrentIndex(item->index());


}

void MainWindow::on_pushCommentButton_clicked()
{
    QList<QGraphicsItem* > items =  scene->selectedItems();

    if(items.length() == 1 && items.first()->childItems().count() < 2)
    {
        GraphComment* comment = new GraphComment("default", items.first());
    }
}
