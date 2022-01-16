#include "FeedList.h"
#include "Item.h"
#include <QList>


FeedList::FeedList(QObject *parent) : QObject(parent) {

}

QQmlListProperty<Feed> FeedList::feedSources()
{
    return QQmlListProperty<Feed>(this, &m_FeedSources);
}

/*
 * Hier könnte der Fehler liegen, dass die feedItem Liste sich neu initialisiert, wenn man von der
 * Startseite wieder auf den feedView geht. Ich denke wir brauchen hier einfach eine Funktion die
 * die feedItems zurück gibt, wie bei feedSources. So bekommen wir die gleichen Items mehrfach angezeigt
 *
 */
QQmlListProperty<Item> FeedList::feedItems()
{
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        qInfo() << "Found Feed";
        qInfo() << "FEEDLIST.CPP::feedItems() : FeedSources.count() : " << m_FeedSources.count();
        Feed* el = m_FeedSources[i];
        QList<Item*> items = el->getFeedItems();
        for( int j=0; j<items.count(); ++j ) {
            qInfo() << "Found Item";
            merged.push_back(items[j]);
        }
        qInfo() << "FEEDLIST.CPP::feedItems() : FeedSource: " << m_FeedSources[i]->name();
    }
    qInfo() << "Merged count: " << merged.count();
    return QQmlListProperty<Item>(this, &merged);
}

void FeedList::add(QString url) {
    Feed* feed = new Feed();
    feed->setUrl(url);
    feed->get();        // Der Aufruf hat gefehlt, um auch den neuen Feed zu downloaden
    m_FeedSources.push_back(feed);
    emit feedItemsChanged();
    emit feedSourcesChanged();
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
