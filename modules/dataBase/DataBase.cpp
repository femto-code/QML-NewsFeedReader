#include "DataBase.h"
#include "patient.h"

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

bool DataBase::createTablePatient() {

    QSqlQuery query(_dB);
    return query.exec("create table patient (id int primary key, forename varchar(100), familyName varchar(10))");
}

bool DataBase::addPatient( const Patient& p ) {

    QSqlQuery query(_dB);
    query.prepare("INSERT INTO patient (id, forename, familyName) VALUES (:id, :forename, :familyName)");
    query.bindValue( ":id", p.id() );
    query.bindValue( ":forename", p.forename() );
    query.bindValue( ":familyName", p.familyName() );
    return query.exec();

}

bool DataBase::changePatient( const Patient& p ) {

    QSqlQuery query(_dB);
    query.prepare("UPDATE patient SET forename = :forename, familyName = :familyName WHERE id = :id");
    query.bindValue( ":id", p.id() );
    query.bindValue( ":forename", p.forename() );
    query.bindValue( ":familyName", p.familyName() );
    return query.exec();
}

bool DataBase::readPatient( int id, Patient& p ) {

    QSqlQuery query(_dB);
    query.prepare("SELECT id, forename, familyName FROM patient WHERE id = :id");
    query.bindValue( ":id", id );
    bool ok = query.exec();
    ok = ok && query.first();
    readPatient( query, p );
    return ok;
}

void DataBase::readPatient( QSqlQuery& q, Patient& p ) {

    p.setId( q.value( 0 ).toInt() );
    p.setForename( q.value( 1 ).toString() );
    p.setFamilyName( q.value( 2 ).toString() );
}

bool DataBase::readAllPatient( QList<Patient*>& list ) {

    QSqlQuery query(_dB);
    query.prepare("SELECT * FROM patient;");
    bool result = query.exec();
    result = result && query.first();


    if ( result == false )
        return false;

    do {
        Patient* p = new Patient();
        readPatient( query, *p );
        list.push_back( p );
    } while( query.next() );

    return result;
}
