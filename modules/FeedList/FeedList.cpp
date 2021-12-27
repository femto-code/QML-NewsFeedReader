#include "FeedList.h"



FeedList::FeedList(QObject *parent) : QObject(parent) {

}

QQmlListProperty<Feed> FeedList::feedSources()
{
    return QQmlListProperty<Feed>(this, &m_FeedSources);
}

void FeedList::add(QString url) {
    Feed* feed = new Feed();
    feed->setUrl(url);
    m_FeedSources.push_back(feed);
    emit feedSourcesChanged();
}
