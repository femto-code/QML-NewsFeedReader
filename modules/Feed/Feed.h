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
#include <QList>
#include <QQmlListProperty>
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

        m_active = false;

    };

    const QString name() const;
    void setName(QString);

    const QString url() const;
    void setUrl(QString);

    int id() const;
    void setId(int);

    bool active() const;
    void setActive(bool);

    const QString link() const;
    void setLink(const QString &newLink);

    const QString &description() const;
    void setDescription(const QString &newDescription);

    const QList<Item*> FeedItems() const;
    void setFeedItems(const QList<Item*> l);

    QString getItemValue(int, QString);
    QList<Item*> getFeedItems();
    int getItemCount();

public slots:
    void get();

private:
    QString m_name;
    QUrl m_url;
    int m_id;
    bool m_active;
    QNetworkAccessManager* m_nMgr;
    QList<Item*> m_FeedItems;
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
    void itemsChanged();
    void addFinished();
};

#endif
