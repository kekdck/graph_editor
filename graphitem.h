#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QString>
#include <QTextDocument>
#include <QGraphicsItem>

struct GraphItem
{
    QString name;
    QTextDocument *comment;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

    QString getCommentText()
    {
        if(comment)
        {
            return comment->toPlainText();
        }

        return QString("");
    }
};
Q_DECLARE_METATYPE(GraphItem)

#endif // GRAPHITEM_H
