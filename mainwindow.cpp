#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Fmodel = new QFileSystemModel(this);
    settings = new QSettings("OSLL", "SrcGraph", this);
    Gmodel = new GraphModel(this);
    scene = new GraphScene(Gmodel,-1000, -1000, 2000, 2000, this);

    ui->propTreeView->setModel(scene->getCurItemPropModel());
    createMenus();
    loadSettings();
    ui->propTreeView->horizontalHeader()->hide();

    //Setup model and treeView
    Fmodel->setRootPath("");
    ui->treeView->setModel(Fmodel);

    QModelIndex index = Fmodel->index("/");
    ui->treeView->setCurrentIndex(index);

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    QList<int> sizes;
    sizes << 150 << 600;
    ui->splitter->setSizes(sizes);

    scene->setFileModel(Fmodel);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //Connecting actions
    connect(ui->actionClear, &QAction::triggered, scene, &GraphScene::clear);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(scene, &GraphScene::selectionChanged, scene, &GraphScene::refreshItemProps);
    //Zoom buttons
    connect(ui->actionZoomIn, &QAction::triggered, ui->graphicsView, &GraphView::zoomIn);
    connect(ui->actionZoomOut, &QAction::triggered, ui->graphicsView, &GraphView::zoomOut);

    connect(ui->zoomInButton, &QPushButton::clicked, ui->actionZoomIn, &QAction::trigger);
    connect(ui->zoomOutButton, &QPushButton::clicked, ui->actionZoomOut, &QAction::trigger);
    //Settings
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::saveSettings);
}

MainWindow::~MainWindow()
{
    saveSettings();
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

    scene->addNode(new QFileInfo(Fmodel->fileInfo(index)));
}

void MainWindow::on_pushRemoveButton_clicked()
{
    if (scene->items().isEmpty()) return;
    QList <QGraphicsItem *> items = scene->selectedItems();
    foreach(QGraphicsItem *item, items)
    {
        GraphVisNode *gvn = dynamic_cast<GraphVisNode *>(item);
        if (gvn)
        {
            gvn->eraseEdges();
            scene->removeItem(gvn);
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
        GraphVisNode *firstItem = dynamic_cast<GraphVisNode *>(items.at(0));
        GraphVisNode *lastItem  = dynamic_cast<GraphVisNode *>(items.at(1));

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
        GraphVisEdge *edge = dynamic_cast<GraphVisEdge *>(items.at(0));
        if (edge)
        {
            scene->addComment(edge);
            return;
        }
        GraphVisNode *node = dynamic_cast<GraphVisNode *>(items.at(0));
        if (node)
        {
            scene->addComment(node);
            return;
        }
    }
}
