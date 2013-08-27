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
    scene = new GraphScene(Gmodel, -1000, -1000, 2000, 2000, this);

    ui->listView->setModel(Gmodel);
    createMenus();
    loadSettings();

    //Setup model and listView
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
    //calling edit window
    connect(ui->pushEditButton, &QPushButton::clicked, ui->actionEdit, &QAction::trigger);
    connect(ui->actionEdit, &QAction::triggered, ui->graphicsView, &GraphView::openEdit);
    //add node
    connect(ui->pushAddButton, &QPushButton::clicked, ui->actionAdd, &QAction::trigger);
    //add comment
    connect(ui->pushCommentButton, &QPushButton::clicked, ui->actionAddComment, &QAction::trigger);
    //remove
    connect(ui->pushRemoveButton, &QPushButton::clicked, ui->actionRemove, &QAction::trigger);
    //connecting
    connect(ui->pushConnectButton, &QPushButton::clicked, ui->actionConnect, &QAction::trigger);
    //diconnecting
    connect(ui->pushDisconnectButton, &QPushButton::clicked, ui->actionDisconnect, &QAction::trigger);
    //clearing
    connect(ui->actionClear, &QAction::triggered, scene, &GraphScene::clear);
    //quitting
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
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
    delete settings;
    delete Gmodel;
    delete Fmodel;
    delete scene;
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
    if (settings->value("view/grid").toBool())
    {
        ui->actionGrid->setChecked(true);
    }
    else
    {
        ui->actionGrid->setChecked(false);
    }

    //Check if it is the first run
    if (settings->value("firstrun").toBool() == false)
    {
        QMessageBox::information(this,
                                 tr("First run"),
                                 tr("Welcome to our graphEditor!"),
                                 QMessageBox::NoButton);
        settings->setValue("firstrun", QVariant(true));
    }
}

void MainWindow::saveSettings()
{
    //Save any settings you want if they were not set in setProperty()
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save graph"),
                                                    settings->value("savedir").toString(),
                                                    tr("XML files (*.xml)"),
                                                    0, QFileDialog::DontUseNativeDialog);

    if(fileName == QString(""))
    {
        return;
    }

    if(fileName.section(".", -1, -1) != "xml")
    {
        fileName.append(".xml");
    }
    GraphMlSaver saver(fileName);
    saver.save(Gmodel);
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    //anything you want
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Shift:
        {
            ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        }break;
    default:
        {
            //some default nn?
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
            ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
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

void MainWindow::on_actionAdd_triggered()
{
    //get selected item in treeView
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;

    scene->addNode(new QFileInfo(Fmodel->fileInfo(index)));
}

void MainWindow::on_actionRemove_triggered()
{
    if (scene->items().isEmpty()) return;
    QList<QGraphicsItem *> items = scene->selectedItems();
    QList<GraphNode *> gvns;
    QList<GraphEdge *> gves;
    //Get only nodes
    foreach(QGraphicsItem *item, items)
    {
        GraphVisNode *gvn = dynamic_cast<GraphVisNode *>(item);
        if (gvn)
        {
            gvns.push_back(gvn->mdata);
        }
    }
    //delete these nodes
    foreach(GraphNode *n, gvns)
    {
        Gmodel->removeNode(n);
    }
    //refresh selection and get left edges
    items = scene->selectedItems();
    foreach(QGraphicsItem *item, items)
    {
        GraphVisEdge *gve = dynamic_cast<GraphVisEdge *>(item);
        if (gve)
        {
            gves.push_back(gve->mdata);
        }
    }
    //delete these edges
    foreach(GraphEdge *e, gves)
    {
        Gmodel->removeEdge(e);
    }
    scene->clearSelection();
    scene->update();
}

void MainWindow::on_actionConnect_triggered()
{
    QList<QGraphicsItem *> items =  scene->selectedItems();
    QList<GraphVisNode *> gvns;
    foreach (QGraphicsItem *it, items)
    {
        GraphVisNode *gvn = dynamic_cast<GraphVisNode *>(it);
        if (gvn)
        {
            gvns.push_back(gvn);
        }
    }

    if (gvns.length() == 2)
    {
        if (!gvns.at(0)->connectedDirectlyTo(gvns.at(1)->mdata))
        {
            scene->addEdge(gvns.at(0), gvns.at(1));
        }
    }
    scene->clearSelection();
    scene->update();
}

void MainWindow::on_actionAddComment_triggered()
{
    QList<QGraphicsItem* > items =  scene->selectedItems();

    if(items.length() == 1)
    {
        GraphVisEdge *edge = dynamic_cast<GraphVisEdge *>(items.at(0));
        if (edge && edge->mdata->comment == 0)
        {
            scene->addComment(edge);
            return;
        }
        GraphVisNode *node = dynamic_cast<GraphVisNode *>(items.at(0));
        if (node && node->mdata->comment == 0)
        {
            scene->addComment(node);
            return;
        }
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    QList<GraphVisNode *> gvns;
    foreach (QGraphicsItem *it, items)
    {
        GraphVisNode *gvn = dynamic_cast<GraphVisNode *>(it);
        if (gvn)
        {
            gvns.push_back(gvn);
        }
    }
    switch (gvns.size())
    {
    case 0:
        return;
    case 1:
        Gmodel->eraseEdges(gvns.at(0)->mdata);
        break;
    case 2:
        GraphEdge *e = gvns.at(0)->connectedDirectlyTo(gvns.at(1)->mdata);
        if (e)
            Gmodel->removeEdge(e);
        break;
    }
    scene->clearSelection();
}

void MainWindow::on_actionGrid_toggled(bool arg1)
{
    if (arg1)
    {
        scene->setBackgroundBrush(QBrush(QColor(150,150,150), Qt::CrossPattern));
    }
    else
    {
        scene->setBackgroundBrush(QBrush(QColor(255,255,255)));
    }
    setProperty("view/grid", QVariant::fromValue(arg1));
    scene->update();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Open graph",
                                                    settings->value("opendir").toString(),
                                                    tr("XML files (*.xml)"),
                                                    0, QFileDialog::DontUseNativeDialog);

    if(filePath == QString(""))
    {
        return;
    }

    delete Gmodel;
    delete scene;
    GraphMlLoader loader(filePath);
    scene = loader.getGraph();
    ui->actionGrid->toggle();
    ui->actionGrid->toggle();
    Gmodel = scene->getGraphModel();
    ui->graphicsView->setScene(scene);
}
