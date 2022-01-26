#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <qobject.h>
#include <qstring.h>
#include <QDate>

#include "Feed.h"
#include "FeedList.h"

class QSqlDatabase;
class QSqlQuery;
class Patient;

class DataBase : public QObject {

    Q_OBJECT

    static QSqlDatabase _dB;

    static bool readFeed( QSqlQuery& q, Feed& f );
    static void readItem( QSqlQuery& q, Item& m );

    DataBase();
public:
    static bool open( const QString& dbName, const QString& userName, const QString& passwd );
    static void close();

    static void saveFeedList(const FeedList& collection);

    static bool createTableFeedSources();
    static bool createTableFeedItems();
    static bool addFeed( const Feed*& f );
    static bool addItem( const Item*& m, int feedid );

//    static bool changePatient( const Patient& p );
//    static bool readPatient( int id, Patient& p );
    static bool readAll( FeedList& collection );
};

#endif // DATA_BASE_H
