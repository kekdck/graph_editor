#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    scene = new GraphScene(-1000, -1000, 2000, 2000, this);
    settings = new QSettings("OSLL", "SrcGraph", this);

    ui->propTreeView->setModel(scene->getCurItemPropModel());
    createMenus();
    loadSettings();
    ui->propTreeView->horizontalHeader()->hide();

    //Setup model and treeView
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

    scene->setFileModel(model);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //Connecting actions
    connect(ui->actionClear, SIGNAL(triggered()), scene, SLOT(clear()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(scene, SIGNAL(selectionChanged()), scene, SLOT(refreshItemProps()));
    //Zoom buttons
    connect(ui->actionZoomIn, SIGNAL(triggered()), ui->graphicsView, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), ui->graphicsView, SLOT(zoomOut()));

    connect(ui->zoomInButton, SIGNAL(clicked()), ui->actionZoomIn, SLOT(trigger()));
    connect(ui->zoomOutButton, SIGNAL(clicked()), ui->actionZoomOut, SLOT(trigger()));
    //Settings
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(saveSettings()));
    connect(this, SIGNAL(destroyed()), this, SLOT(saveSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
{
    QMenu *menu = new QMenu(ui->graphicsView);
    menu->addAction(ui->actionClear);
    ui->graphicsView->setContextMenu(menu);
}

void MainWindow::loadSettings()
{
    //Setting grid
    if (settings->value("view/grid") == QVariant())
    {
        ui->gridCheckBox->setChecked(true);
    }
    else
    {
        ui->gridCheckBox->setChecked(false);
    }

    //Check if it is the first run
    if (settings->value("firstrun") == QVariant())
    {
        QMessageBox::information(this,
                                 "First run",
                                 "Welcome to our graphEditor!",
                                 QMessageBox::NoButton);
    }
    else
    {
        settings->setValue("firstrun", QVariant(true));
    }
}

void MainWindow::saveSettings()
{
    settings->setValue("view/grid", QVariant(ui->gridCheckBox->isChecked()));
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    //anything you want
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
    if (scene->items().isEmpty()) return;
    QList <QGraphicsItem *> items = scene->selectedItems();
    foreach(QGraphicsItem *item, items)
    {
        GraphNode *grit = dynamic_cast<GraphNode *>(item);
        if (grit)
        {
            grit->eraseEdges();
            scene->removeItem(grit);
            scene->items().removeOne(grit);
        }
    }
    scene->clearSelection();
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
    scene->clear();
}

void MainWindow::on_pushConnectButton_clicked()
{
    QList<QGraphicsItem* > items =  scene->selectedItems();
    if (items.length() == 2)
    {
        GraphNode *firstItem = dynamic_cast<GraphNode *>(items.at(0));
        GraphNode *lastItem  = dynamic_cast<GraphNode *>(items.at(1));

        qDebug() << firstItem << lastItem;
        if (firstItem && lastItem)
        {
            scene->addEdge(firstItem, lastItem);
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

void MainWindow::on_pushCommentButton_clicked()
{
    QList<QGraphicsItem* > items =  scene->selectedItems();

    if(items.length() == 1 && items.first()->childItems().count() < 2)
    {
        scene->addComment(items.first());
    }
}
