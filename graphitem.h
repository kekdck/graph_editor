#ifndef GRAPHITEM_H
#define GRAPHITEM_H


#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QString>
#include <QPainter>
#include <QGraphicsScene>
#include <QFile>
#include <QTreeView>
#include <QDirModel>
#include <QMessageBox>
#include <QDebug>

//вообще это модифицированный квадратик
class GraphItem: public QGraphicsRectItem
{
public:
    GraphItem(qreal x, qreal y, qreal width, qreal height, QString name, QGraphicsItem* parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setFile(QModelIndex index, QDirModel *model);
    QString fileName(QDirModel *model);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

protected:

private:
    QString path;
    QGraphicsTextItem *nameText;

    QModelIndex fileIndex;
    QDirModel *dirModel;
};

#endif // GRAPHITEM_H
