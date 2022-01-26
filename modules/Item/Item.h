#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QGuiApplication>
#include <QtQuick>

class Item : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString link READ link WRITE setLink NOTIFY linkChanged)
    Q_PROPERTY(QString pubDate READ pubDate WRITE setPubDate NOTIFY pubDateChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)


public:
    Item(QObject* parent = NULL) : QObject(parent){
    };

    const QString title() const{return m_title;}
    void setTitle(QString newTitle){m_title = newTitle;}

    const QString link() const{return m_link;}
    void setLink(QString newLink){m_link = newLink;}

    const QString pubDate() const{return m_pubDate;}
    void setPubDate(QString newPubDate){m_pubDate = newPubDate;}

    const QString description() const{return m_description;}
    void setDescription(QString newDescription){m_description = newDescription;}

private:
    QString m_title;
    QString m_link;
    QString m_pubDate;
    QString m_description;

signals:
    void titleChanged();
    void linkChanged();
    void pubDateChanged();
    void descriptionChanged();
};

#endif
