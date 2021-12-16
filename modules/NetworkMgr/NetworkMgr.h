#ifndef NETWORKMGR_H
#define NETWORKMGR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class NetworkMgr : public QObject {
    Q_OBJECT

    NetworkMgr(QObject* parent = NULL){};
    static QNetworkAccessManager* qnam;

public:
    static QNetworkAccessManager* getInstance(){
        if(qnam == NULL){
            qnam = new QNetworkAccessManager();
        }
        return qnam;
    }
//    QNetworkAccessManager(QNetworkAccessManager const&) = delete;
//    void operator=(QNetworkAccessManager const&) = delete;
};

#endif
