#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QMenu>
#include <QContextMenuEvent>

class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphView(QWidget * parent = 0);


    QMenu *getContextMenu() const;
    void setContextMenu(QMenu *value);

signals:

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:

    QMenu *contextMenu;

public slots:
    void openEdit();

    void zoomIn();

    void zoomOut();
};

#endif // GRAPHVIEW_H
