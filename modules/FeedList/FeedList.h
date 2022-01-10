#ifndef FEEDLIST_H
#define FEEDLIST_H

#include "Feed.h"
#include "Item.h"
#include <QObject>
#include <QQmlListProperty>
#include <QList>

typedef QList<Feed*> FeedSources;

class FeedList : public QObject {

    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Item> feedItems READ feedItems NOTIFY feedItemsChanged)

    FeedSources m_FeedSources;
    QList<Item*> merged;

public:
    FeedList(QObject* parent = nullptr);
    QQmlListProperty<Item> feedItems();

public slots:
    void add(QString url);
    void saveToDB();
    void debugFeedList();

signals:
    void feedItemsChanged();
};

#endif
