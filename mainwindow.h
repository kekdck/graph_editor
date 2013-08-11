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
#include "graphedge.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    virtual void mousePressEvent(QMouseEvent *);
    explicit MainWindow(QWidget *parent = 0);
    virtual void wheelEvent( QWheelEvent * e );
    ~MainWindow();

private slots:
    void on_pushRemoveButton_clicked();

    void on_pushAddButton_clicked();

    void on_actionNew_triggered();

    void on_pushConnectButton_clicked();

    void on_gridCheckBox_stateChanged(int arg1);

    void zoomIn();

    void zoomOut();

    void refreshItemProps();
private:
    Ui::MainWindow *ui;

//File model & tree view of files
    QFileSystemModel* model;

    QStandardItemModel *curItemPropModel;
//Graph's members
    QList< GraphItem * > list;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
