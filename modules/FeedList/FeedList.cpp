#include "FeedList.h"
#include "Item.h"
#include <QList>


FeedList::FeedList(QObject *parent) : QObject(parent) {

}

QQmlListProperty<Item> FeedList::feedItems()
{
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        qInfo() << "Found Feed";
        Feed* el = m_FeedSources[i];
        QList<Item*> items = el->getFeedItems();
        for( int j=0; j<items.count(); ++j ) {
            qInfo() << "Found Item";
            merged.push_back(items[j]);
        }
    }
    qInfo() << "Merged count: " << merged.count();
    return QQmlListProperty<Item>(this, &merged);
}

void FeedList::add(QString url) {
    Feed* feed = new Feed();
    feed->setUrl(url);
    m_FeedSources.push_back(feed);
    emit feedItemsChanged();
}
void FeedList::debugFeedList(){
    qInfo() << "I'm here";
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        Feed* el = m_FeedSources[i];
        el->get();
        qInfo() << "get ItemCount: " << el->getItemCount();
        QList<Item*> testItem = el->getFeedItems();
        qInfo() << testItem[10]->link();
        qInfo() << testItem[10]->title();
        qInfo() << testItem[10]->pubDate();
        qInfo() << testItem[10]->description();
    }
}
void FeedList::saveToDB(){
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        Feed* el = m_FeedSources[i];
        // save
    }
}
