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
    Q_PROPERTY(QQmlListProperty<Feed> feedSources READ feedSources NOTIFY feedSourcesChanged)

    FeedSources m_FeedSources;
    QList<Item*> merged;
    int n=0;

public:
    FeedList(QObject* parent = nullptr);
    QQmlListProperty<Item> feedItems();
    QQmlListProperty<Feed> feedSources();

    const FeedSources getFeedSources() const;
    void setFeedSources(FeedSources l);

public slots:
    void add(QString url);
    void saveToDB();
    void debugFeedList();
    void deleteSrc(QString name);

signals:
    void feedItemsChanged();
    void feedSourcesChanged();
};

#endif
