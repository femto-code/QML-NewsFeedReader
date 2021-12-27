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
void FeedList::debugFeedList(){
    qInfo() << "I'm here";
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        Feed* el = m_FeedSources[i];
        el->get();
        qInfo() << "get ItemCount: " << el->getItemCount();
        std::unordered_map<int, Item*> testItem = el->getFeedItems();
        qInfo() << testItem[10]->link();
        qInfo() << testItem[10]->title();
        qInfo() << testItem[10]->pubDate();
        qInfo() << testItem[10]->description();
    }
}
