#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QString>
#include <QPainter>

//вообще это модифицированный квадратик
class GraphItem: public QGraphicsRectItem
{
public:
    GraphItem(qreal x, qreal y, qreal width, qreal height, QString name, QGraphicsItem* parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setFile(QString file);

protected:

private:
    QString path;
    QGraphicsTextItem *nameText;
};

#endif // GRAPHITEM_H
