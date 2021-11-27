#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <qobject.h>
#include <qstring.h>
#include <QDate>

class QSqlDatabase;
class QSqlQuery;
class Patient;

class DataBase : public QObject {

    Q_OBJECT

    static QSqlDatabase _dB;

    static void readPatient( QSqlQuery& q, Patient& p );

    DataBase();
public:
    static bool open( const QString& dbName, const QString& userName, const QString& passwd );
    static void close();

    static bool createTablePatient();
    static bool addPatient( const Patient& p );
    static bool changePatient( const Patient& p );
    static bool readPatient( int id, Patient& p );
    static bool readAllPatient( QList<Patient*>& list );
};

#endif // DATA_BASE_H
