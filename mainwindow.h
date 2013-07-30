#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QList>
#include <QFileSystemModel>
#include <QTreeView>

#include "graphitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushRemoveButton_clicked();

    void on_pushAddButton_clicked();

    void on_splitter_splitterMoved(int pos, int index);

private:
    Ui::MainWindow *ui;

//File model & tree view of files
    QFileSystemModel model;
    QTreeView treeView;

//Graph's members
    QList< GraphItem * > list;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
