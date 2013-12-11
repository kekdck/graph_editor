#ifndef EDITNODEDIALOG_H
#define EDITNODEDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "graphvisnode.h"
#include "graphnode.h"

namespace Ui {
class editNodeDialog;
}

class editNodeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit editNodeDialog(GraphNode *node, QWidget *parent = 0);
    ~editNodeDialog();
    
private slots:
    void on_pathToolButton_clicked();
    void markName();
    void setColor();
    void setupGUI();
    void acceptEdit();

    void on_pathDirToolButton_clicked();

private:
    GraphNode *node;
    Ui::editNodeDialog *ui;
};

#endif // EDITNODEDIALOG_H
