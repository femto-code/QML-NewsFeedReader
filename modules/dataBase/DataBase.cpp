#include "DataBase.h"


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

QSqlDatabase DataBase::_dB;

/**
 * @brief DataBase::DataBase
 */
bool DataBase::open( const QString& dbName, const QString& userName, const QString& passwd ) {

    _dB = QSqlDatabase::addDatabase("QSQLITE");
    _dB.setHostName("localhost");
    _dB.setDatabaseName( dbName );
    _dB.setUserName( userName );
    _dB.setPassword( passwd );
    return _dB.open();
}

void DataBase::close() {

    _dB.close();
}

void DataBase::saveFeedList(const FeedList& collection)
{
    QSqlQuery query(_dB);
    bool result = query.exec("DELETE FROM feedsources");
    if(!result){ qDebug() << query.lastError(); }
    bool result2 = query.exec("DELETE FROM feeditems");
    if(!result2){ qDebug() << query.lastError(); }
    collection.debugFeedList();
    const QList<Feed*>& feeds = collection.getFeedSources();
    for( int i=0; i<feeds.count(); ++i ) {
        const Feed* el = feeds[i];
        qInfo() << "Found Feed: " << el->id();
        qDebug() << addFeed(el);
        const QList<Item*>& items = el->FeedItems();
        for( int j=0; j<items.count(); ++j ) {
            qInfo() << "Found Item";
            const Item* it = items[j];
            qDebug() << addItem(it,el->id());
        }
    }
}

bool DataBase::createTableFeedSources() {
    if( !_dB.open() ) { qDebug() << _dB.lastError(); qFatal( "Failed to connect." ); }
    QSqlQuery query(_dB);
    bool result = query.exec("CREATE TABLE IF NOT EXISTS feedsources (id int primary key, url varchar(100), name varchar(30), description varchar(59), active varchar(10))");
    if(!result){ qDebug() << query.lastError(); }
    return result;
}

bool DataBase::createTableFeedItems() {
    if( !_dB.open() ) { qDebug() << _dB.lastError(); qFatal( "Failed to connect." ); }
    QSqlQuery query(_dB);
    bool result = query.exec("CREATE TABLE IF NOT EXISTS feeditems (title varchar(100), link varchar(30), pubDate varchar(59), description varchar(200), feedid int(10))");
    if(!result){ qDebug() << query.lastError(); }
    return result;
}

bool DataBase::addFeed( const Feed*& f ) {
    QSqlQuery query(_dB);
    query.prepare("INSERT INTO feedsources (id, url, name, description, active) VALUES (:id, :url, :name, :description, :active)");
    query.bindValue( ":id", f->id() );
    query.bindValue( ":url", f->link() );
    query.bindValue( ":name", f->name() );
    query.bindValue( ":description", f->description() );
    query.bindValue( ":active", f->active() );
    qDebug() << f->id() << f->link() << f->name() << f->description() << f->active();
    return query.exec();
}

bool DataBase::addItem( const Item*& m, int feedid) {
    QSqlQuery query(_dB);
    query.prepare("INSERT INTO feeditems (title, link, pubDate, description, feedid) VALUES (:title, :link, :pubDate, :description, :feedid)");
    query.bindValue( ":title", m->title() );
    query.bindValue( ":link", m->link() );
    query.bindValue( ":pubDate", m->pubDate() );
    query.bindValue( ":description", m->description() );
    query.bindValue( ":feedid", feedid );
    return query.exec();
}

//bool DataBase::changePatient( const Patient& p ) {

//    QSqlQuery query(_dB);
//    query.prepare("UPDATE patient SET forename = :forename, familyName = :familyName WHERE id = :id");
//    query.bindValue( ":id", p.id() );
//    query.bindValue( ":forename", p.forename() );
//    query.bindValue( ":familyName", p.familyName() );
//    return query.exec();
//}

//bool DataBase::readPatient( int id, Patient& p ) {

//    QSqlQuery query(_dB);
//    query.prepare("SELECT id, forename, familyName FROM patient WHERE id = :id");
//    query.bindValue( ":id", id );
//    bool ok = query.exec();
//    ok = ok && query.first();
//    readPatient( query, p );
//    return ok;
//}

void DataBase::readItem( QSqlQuery& q, Item& m ) {
    m.setTitle( q.value( 0 ).toString() );
    m.setLink( q.value( 1 ).toString() );
    m.setPubDate( q.value( 2 ).toString() );
    m.setDescription( q.value( 3 ).toString() );
}

bool DataBase::readFeed( QSqlQuery& q, Feed& f ) {
    f.setId( q.value( 0 ).toInt() );
    f.setUrl( q.value( 1 ).toString() );
    f.setName( q.value( 2 ).toString() );
    f.setDescription( q.value(3).toString() );
    f.setActive( q.value(4).toBool() );

    QList<Item*> temp;
    QSqlQuery query(_dB);
    query.prepare("SELECT * FROM feeditems WHERE feedid = :fid");
    query.bindValue( ":fid", f.id() );
    bool result = query.exec();
    result = result && query.first();


    if ( result == false )
        return false;

    do {
        qInfo() << "Reading item from db";
        Item* m = new Item();
        readItem( query, *m );
        temp.push_back( m );
    } while( query.next() );

    f.setFeedItems(temp);

    return result;
}

bool DataBase::readAll( FeedList& collection ) {

    QSqlQuery query(_dB);
    query.prepare("SELECT * FROM feedsources;");
    bool result = query.exec();
    result = result && query.first();

    QList<Feed*> list;
    if ( result == false )
        return false;

    int c = 0;
    do {
        qInfo() << "Reading feed from db";
        Feed* f = new Feed();
        readFeed( query, *f );
        list.push_back( f );
        c++;
    } while( query.next() );

    collection.setFeedSources(list);
    collection.setN(c);

    return result;
}
