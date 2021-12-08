#ifndef FEED_LIST_H
#define FEED_LIST_H

#include "Feed.h" // by Timo
#include <QObject>
#include <QQmlListProperty>
#include <QList>

typedef QList<Feed*> FeedSources;

class FeedList : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Feed> feedSources READ feedSources NOTIFY feedSourcesChanged)

    FeedSources m_FeedSources;
public:
    FeedList(QObject* parent = nullptr);
    QQmlListProperty<Feed> feedSources();
public slots:
    void add(QString name, QString urls);
signals:
    void feedSourcesChanged();
};

#endif // FEED_LIST_H