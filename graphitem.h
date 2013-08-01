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

class GraphItem: public QGraphicsRectItem
{
public:
    GraphItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setFile(QModelIndex index, QDirModel *model);
    QString fileName();

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

protected:

private:
    QString path;
    QGraphicsTextItem *nameText;

    QModelIndex fileIndex;
    QDirModel *dirModel;
};

#endif // GRAPHITEM_H
