#ifndef FEED_H
#define FEED_H

#include <QObject>
#include <QGuiApplication>
#include <QtQuick>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <iostream>
#include <QDomDocument>
#include "NetworkMgr.h"
#include "Item.h"

class Feed : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    Feed(QObject* parent = NULL) : QObject(parent){

        m_nMgr = NetworkMgr::getInstance();

        connect(m_nMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(parse(QNetworkReply*)));

        m_active = false;

    };

    QString name();
    void setName(QString);
    QString url();
    void setUrl(QString);
    int id();
    void setId(int);
    bool active();
    void setActive(bool);
    QString getItemValue(int, QString);
    QString link();
    void setLink(const QString &newLink);
    const QString &description() const;
    void setDescription(const QString &newDescription);
    std::unordered_map<int, Item*> getFeedItems();
    int getItemCount();

public slots:
    void get();

private:
    QString m_name;
    QString m_url;
    int m_id;
    bool m_active;
    QNetworkAccessManager* m_nMgr;
    std::unordered_map<int, Item*> feedItems;
    QString m_link;
    QString m_description;
    int m_itemCount = 0;

private slots:
    void parse(QNetworkReply* reply);

signals:
    void nameChanged();
    void urlChanged();
    void idChanged();
    void activeChanged();
};

#endif
