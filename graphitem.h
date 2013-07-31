#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QString>
#include <QPainter>
#include <QGraphicsScene>
#include <QDirModel>

//вообще это модифицированный квадратик
class GraphItem: public QGraphicsRectItem
{
public:
    GraphItem(qreal x, qreal y, qreal width, qreal height, QString name, QGraphicsItem* parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setFile(QModelIndex index, QDirModel *model);
    QString fileName(QDirModel *model);


protected:

private:
    QString path;
    QGraphicsTextItem *nameText;

    QModelIndex fileIndex;
    //Really? Do we need treeModel in EVERY graphitem? Maybe change to QFile or smth similar?
    QDirModel* treeModel;
};

#endif // GRAPHITEM_H
