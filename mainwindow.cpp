#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setting up model and treeView
    model = new QDirModel(this);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    ui->treeView->setModel(model);

    QModelIndex index = model->index("/");
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(1);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
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
    if (model->isDir(index))
    {
        item->setBrush(QBrush(Qt::yellow));
    }
    else
    {
        item->setBrush(QBrush(Qt::blue));
    }
    item->setFile(index, model);
    scene->addItem(item);




    if(!list.isEmpty())
    {
        QPointF source = item->mapToScene(item->boundingRect().center());
        QPointF dest = list.last()->mapToScene(list.last()->boundingRect().center());

        GraphEdge* edge = new GraphEdge(source.rx(), source.ry(), dest.rx(), dest.ry());

        item->addOutEdge(edge);
        list.last()->addInEdge(edge);

        scene->addItem(edge);
    }


    list.push_back(item);
    qDebug() << "Pushed index" <<  item->fileName();
}

void MainWindow::on_pushRemoveButton_clicked()
{
    if (list.empty()) return;
    scene->removeItem(list.last());
    list.pop_back();
}
