#include "FeedList.h"
#include "Item.h"
#include <QList>


FeedList::FeedList(QObject *parent) : QObject(parent) {

}

QQmlListProperty<Feed> FeedList::feedSources()
{
    return QQmlListProperty<Feed>(this, &m_FeedSources);
}

void FeedList::deleteSrc(QString name)
{
    QList<Feed*>::iterator pos;

    for( pos = m_FeedSources.begin(); pos<m_FeedSources.end(); ++pos ) {
        if((*pos)->name() == name){
            m_FeedSources.erase(pos);
        }

    }
    emit feedSourcesChanged();
}

/*
 * Hier könnte der Fehler liegen, dass die feedItem Liste sich neu initialisiert, wenn man von der
 * Startseite wieder auf den feedView geht. Ich denke wir brauchen hier einfach eine Funktion die
 * die feedItems zurück gibt, wie bei feedSources. So bekommen wir die gleichen Items mehrfach angezeigt
 *
 */
QQmlListProperty<Item> FeedList::feedItems()
{
    merged.clear();
    qInfo() << "BEGIN ___ FEEDLIST.CPP::feedItems() : FeedSources.count() : " << m_FeedSources.count();
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        //qInfo() << "Found Feed";

        Feed* el = m_FeedSources[i];
        QList<Item*> items = el->getFeedItems();
        for( int j=0; j<items.count(); ++j ) {
            //qInfo() << "Found Item";
            merged.push_back(items[j]);
        }
        qInfo() << "FEEDLIST.CPP::feedItems() : FeedSource: " << el->name() << " with item count: " << items.count();
    }
    qInfo() << "END ___ Merged count: " << merged.count();
    return QQmlListProperty<Item>(this, &merged);
}

void FeedList::add(QString url) {
    if(url==""){
        return;
    }
    Feed* feed = new Feed();
    //qDebug() << "FEEDLIST.CPP::add() : address: " << feed;
    feed->setUrl(url);

    m_FeedSources.push_back(feed);
    int idx = m_FeedSources.count()-1;
    //qInfo() << "FEEDLIST.CPP::add() : count of feed src: " << m_FeedSources.count();
    m_FeedSources[idx]->get();        // Der Aufruf hat gefehlt, um auch den neuen Feed zu downloaden
//    int n=10000;
//    while(n>0){
//        n--;
//    }
    //debugFeedList();
    emit feedItemsChanged();
    emit feedSourcesChanged();
}
void FeedList::debugFeedList(){
    qInfo() << "----------  I'm here --------------";
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        Feed* el = m_FeedSources[i];
        qInfo() << "FEEDLIST.CPP::debugFeedList() : FeedSource: " << i << ":" << el->name();
        //el->get();
        qInfo() << "get ItemCount: " << el->getItemCount();
        QList<Item*> testItem = el->getFeedItems();
        qInfo() << testItem[10]->link();
        qInfo() << testItem[10]->title();
        qInfo() << testItem[10]->pubDate();
        qInfo() << testItem[10]->description();
    }
    qInfo() << "----------  END DEBUG FEEDLIST --------------";
}
void FeedList::saveToDB(){
    for( int i=0; i<m_FeedSources.count(); ++i ) {
        Feed* el = m_FeedSources[i];
        // save
    }
}
