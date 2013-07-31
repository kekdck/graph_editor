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
    model = new QDirModel(this);
    ui->treeView->setModel(model);

    QModelIndex index = model->index("/");
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(1);


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
    //выбираем выделенный в treeview элемент
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;

    GraphItem* item = new GraphItem(10, 10, 20, 20, QString::number(list.size()));
    item->setFile(index, model);
    scene->addItem(item);
   
    list.push_back(item);


    //Вывод в консоль имя вставляемого в нод файла
    qDebug() << "Pushed index" <<  item->fileName(model);
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
