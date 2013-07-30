#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Заготовка на нормальный диалог добавления элемента
    //dialog = new addElementDialog(this);

    //Установка обозревания файлов в treeView
    model.setRootPath("");
    ui->treeView->setModel(&model);
    ui->treeView->setBaseSize(250, 600);

    //Настройка окна параметров GraphItem
    //ui->treeWidget->header()->setBaseSize(50, 15);

    //Установка сцены
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    //GraphItem* newItem = new GraphItem(10, 10, 10, 10);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushAddButton_clicked()
{

//    GraphItem* item = new GraphItem(10, 10, 20, 20, QString::number(list.size()));
//    scene->addItem(item);
   
//    list.push_back(item);

    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    QDirModel* model = (QDirModel*)ui->treeView->model();
    int row = -1;
    foreach (QModelIndex index, list)
    {
        if (index.row()!=row && index.column()==0)
        {
            QFileInfo fileInfo = model->fileInfo(index);
            qDebug() << fileInfo.fileName() << '\n';
            row = index.row();
        }
    }
}

void MainWindow::on_pushRemoveButton_clicked()
{
    //Удаление последнего QGraphicsItem из списка
    if (list.empty())
    {
        return;
    }
    scene->removeItem(list.last());
    list.pop_back();
}


void MainWindow::on_splitter_splitterMoved(int pos, int index)
{

}
