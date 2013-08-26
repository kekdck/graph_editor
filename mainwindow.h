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
#include <QFileDialog>

#include "graphnode.h"
#include "graphedge.h"

#include "graphvisedge.h"
#include "graphvisnode.h"

#include "graphmodel.h"
#include "graphscene.h"

#include "graphmlloader.h"
#include "graphmlsaver.h"

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
    virtual ~MainWindow();

    void createMenus();

private slots:

    void on_actionNew_triggered();

    void loadSettings();
    void saveSettings();

    void on_actionSave_triggered();

    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionConnect_triggered();

    void on_actionAddComment_triggered();

    void on_actionDisconnect_triggered();

    void on_actionGrid_toggled(bool arg1);

    void on_actionOpen_triggered();

    void on_pushDisconnectButton_clicked();

private:
    Ui::MainWindow  *ui;
    QSettings       *settings;

//File model & tree view of files
    QFileSystemModel *Fmodel;
    GraphModel *Gmodel;
    GraphScene *scene;
};

#endif // MAINWINDOW_H
