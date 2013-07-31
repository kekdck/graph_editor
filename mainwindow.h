#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QList>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDirModel>
#include <QDebug>

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

private:
    Ui::MainWindow *ui;

//File model & tree view of files
    QDirModel* model;

//Graph's members
    QList< GraphItem * > list;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
