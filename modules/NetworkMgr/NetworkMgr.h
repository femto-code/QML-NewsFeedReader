#ifndef NETWORKMGR_H
#define NETWORKMGR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class NetworkMgr : public QObject {
    Q_OBJECT

    NetworkMgr(QObject* parent = NULL){};

    QNetworkAccessManager* qnam;

public:
    QNetworkAccessManager* getInstance(){
        if(qnam == NULL){
            qnam = new QNetworkAccessManager(this);
        }
        return qnam;
    }
};

#endif
