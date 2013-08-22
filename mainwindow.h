#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QList>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDirModel>
#include <QDebug>
#include <QGraphicsItem>

#include "graphnode.h"
#include "graphedge.h"

#include "graphvisedge.h"
#include "graphvisnode.h"

#include "graphmodel.h"
#include "graphscene.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit        MainWindow(QWidget *parent = 0);
    virtual void    keyPressEvent(QKeyEvent *);
    virtual void    keyReleaseEvent(QKeyEvent *);
    virtual void    mousePressEvent(QMouseEvent *);
    ~MainWindow();

    void createMenus();

private slots:
    void on_pushRemoveButton_clicked();
    void on_pushAddButton_clicked();
    void on_pushConnectButton_clicked();
    void on_pushCommentButton_clicked();

    void on_actionNew_triggered();

    void on_gridCheckBox_stateChanged(int arg1);

    void loadSettings();
    void saveSettings();

private:
    Ui::MainWindow  *ui;
    QSettings       *settings;

//File model & tree view of files
    QFileSystemModel *Fmodel;
    GraphModel *Gmodel;
    GraphScene *scene;
};

#endif // MAINWINDOW_H
