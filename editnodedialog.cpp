#include "editnodedialog.h"
#include "ui_editnodedialog.h"

editNodeDialog::editNodeDialog(GraphNode *n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editNodeDialog)
{
    ui->setupUi(this);
    node = n;
    setupGUI();
}

editNodeDialog::~editNodeDialog()
{
    delete ui;
}

void editNodeDialog::markName()
{
    ui->nameLabel->setText("<b>Name:</b>");
}

void editNodeDialog::setColor()
{
    QColor col = QColorDialog::getColor(node->mdata->brush().color(), this,
                                    "Edit color of " + node->name, QColorDialog::DontUseNativeDialog);
    if (!col.isValid())
    {
        return;
    }

    ui->colorEdit->setText(col.name());

    ui->colorLabel->setText("<b>Color:</b>");
}

void editNodeDialog::setupGUI()
{
    ui->nameEdit->setText(node->name);
    ui->colorEdit->setText(node->mdata->brush().color().name());
    if (node->comment)
    {
        ui->commentEdit->setText(node->comment->toPlainText());
    }
    else
    {
        ui->commentEdit->setText("No comment");
    }
    ui->consLabel->setText(QString::number(node->connections()));
    ui->pathEdit->setText(node->filePath());
    connect(ui->colorToolButton, &QToolButton::clicked, this, &editNodeDialog::setColor);
    connect(ui->cancelButton, &QPushButton::clicked, this, &editNodeDialog::close);
    connect(ui->OkButton, &QPushButton::clicked, this, &editNodeDialog::acceptEdit);
    connect(ui->nameEdit, &QLineEdit::textChanged, this, &editNodeDialog::markName);
}

void editNodeDialog::acceptEdit()
{
    QColor col(ui->colorEdit->text());
    if (col.isValid())
    {
        node->mdata->setColor(col);
    }
    node->mdata->setNameText(ui->nameEdit->text());
    if (QFileInfo(ui->pathEdit->text()).exists())
    {
        node->setFileInfo(new QFileInfo(ui->pathEdit->text()));
    }
    else
    {
        QMessageBox::information(this, "Wrong filePath",
                                 "Filepath links to unexisting file, it will not be changed.",
                                 QMessageBox::Ok);
    }
    close();
}

void editNodeDialog::on_pathToolButton_clicked()
{
    QFileDialog fd;
    QString filePath = fd.getOpenFileName(this,
                                          "Select file",
                                          node->filePath(),
                                          tr("Any files (*)"),
                                          0,
                                          QFileDialog::DontUseNativeDialog);
    ui->pathEdit->setText(filePath);
}


void editNodeDialog::on_pathDirToolButton_clicked()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly, true);
    QString filePath = fd.getExistingDirectory(this,
                                               "Select directory",
                                               node->filePath(),
                                               QFileDialog::DontUseNativeDialog);
    ui->pathEdit->setText(filePath);
}
