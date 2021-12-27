#ifndef FEEDLIST_H
#define FEEDLIST_H

#include "Feed.h"
#include <QObject>
#include <QQmlListProperty>
#include <Qlist>

typedef QList<Feed*> FeedSources;

class FeedList : public QObject {

    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Feed> feedSources READ feedSources NOTIFY feedSourcesChanged)

    FeedSources m_FeedSources;

public:
    FeedList(QObject* parent = nullptr);
    QQmlListProperty<Feed> feedSources();

public slots:
    void add(QString name);
    void saveToDB();
    void debugFeedList();

signals:
    void feedSourcesChanged();
};

#endif
