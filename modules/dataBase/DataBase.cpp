#include "DataBase.h"


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

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
    for( int i=0; i<collection.getFeedSources().count(); ++i ) {
        Feed* el = collection.getFeedSources()[i];
        qInfo() << "Found Feed: " << el->id();
        qDebug() << addFeed(el);
        QList<Item*> items = el->getFeedItems();
        for( int j=0; j<items.count(); ++j ) {
            qInfo() << "Found Item";
            qDebug() << addItem(items[i],el->id());
        }
    }
}

bool DataBase::createTableFeedSources() {
    QSqlQuery query(_dB);
    return query.exec("create table feedsources (id int primary key, url varchar(100), name varchar(30), description varchar(59), active varchar(10))");
}

bool DataBase::createTableFeedItems() {
    QSqlQuery query(_dB);
    return query.exec("create table feeditems (title varchar(100), link varchar(30), pubDate varchar(59), description varchar(200), feedid int(10))");
}

bool DataBase::addFeed( const Feed& f ) {
    QSqlQuery query(_dB);
    query.prepare("INSERT INTO feedsources (id, url, name, description, active) VALUES (:id, :url, :name, :description, :active)");
    query.bindValue( ":id", f.id() );
    query.bindValue( ":url", f.link() );
    query.bindValue( ":name", f.name() );
    query.bindValue( ":description", f.description() );
    query.bindValue( ":active", f.active() );
    return query.exec();
}

bool DataBase::addItem(const Item &m, int feedid) {
    QSqlQuery query(_dB);
    query.prepare("INSERT INTO feeditems (title, link, pubDate, description, feedid) VALUES (:title, :link, :pubDate, :description, :feedid)");
    query.bindValue( ":title", m.title() );
    query.bindValue( ":link", m.link() );
    query.bindValue( ":pubDate", m.pubDate() );
    query.bindValue( ":description", m.description() );
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

    do {
        Feed* f = new Feed();
        readFeed( query, *f );
        list.push_back( f );
    } while( query.next() );

    collection.setFeedSources(list);

    return result;
}
