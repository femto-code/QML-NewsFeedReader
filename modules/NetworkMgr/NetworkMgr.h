#ifndef NETWORKMGR_H
#define NETWORKMGR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class NetworkMgr : public QObject {
    Q_OBJECT

    NetworkMgr(QObject* parent = NULL) : QObject(parent){};
    ~NetworkMgr(){};


public:
    static QNetworkAccessManager* getInstance(){

        static QNetworkAccessManager instance;
        return &instance;
    }

    NetworkMgr(NetworkMgr const& copy) = delete;
    NetworkMgr& operator=(NetworkMgr const& copy) = delete;

};

#endif
