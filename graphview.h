#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QScrollBar>
#include <QMenu>
#include <QContextMenuEvent>
#include "graphscene.h"
#include "editnodedialog.h"

class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphView(QWidget * parent = 0);
    virtual ~GraphView();

    GraphScene *scene();


    QMenu *getContextMenu() const;
    void setContextMenu(QMenu *value);

    void goToCenter();

    void openEdgeEdit(GraphVisEdge *e);
    void openNodeEdit(GraphVisNode *n);
    void openCommEdit(QGraphicsTextItem *c);
    void openItemEdit(QGraphicsItem *item);
signals:

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private:

    QMenu *contextMenu;

public slots:
    void openEdit();

    void zoomIn();

    void zoomOut();
};

#endif // GRAPHVIEW_H
