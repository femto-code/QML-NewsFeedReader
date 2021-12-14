#ifndef FEED_H
#define FEED_H

#include <QObject>
#include <QGuiApplication>
#include <QtQuick>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <rapidxml.hpp>
#include <iostream>

#include "main.h"

using namespace std;
using namespace rapidxml;


class Feed : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
//    Feed(QObject* parent = NULL, QNetworkAccessManager* nMgr = NULL) : QObject(parent), m_nMgr(nMgr){
    Feed(QObject* parent = NULL) : QObject(parent){

//        connect(m_nMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
        connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));

    };

    QString name();
    void setName(QString);
    QString url();
    void setUrl(QString);
    int id();
    void setId(int);
    bool active();
    void setActive(bool);

public slots:
    void get(QString location);

private:
    QString m_name;
    QString m_url;
    int m_id;
    bool m_active;
    xml_document<> entries;
//    QNetworkAccessManager* m_nMgr;
    QNetworkAccessManager* qnam = new QNetworkAccessManager(this);

private slots:
    void downloadFinished(QNetworkReply* reply);

signals:
    void nameChanged();
    void urlChanged();
    void idChanged();
    void activeChanged();
};

#endif
