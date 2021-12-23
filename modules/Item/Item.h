#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QGuiApplication>
#include <QtQuick>

class Item : public QObject {

    Q_OBJECT

public:
    Item(QObject* parent = NULL) : QObject(parent){
    };

    QString title(){return m_title;}
    void setTitle(QString newTitle){m_title = newTitle;}
    QString link(){return m_link;}
    void setLink(QString newLink){m_link = newLink;}
    QString pubDate(){return m_pubDate;}
    void setPubDate(QString newPubDate){m_pubDate = newPubDate;}
    QString description(){return m_description;}
    void setDescription(QString newDescription){m_description = newDescription;}

private:
    QString m_title;
    QString m_description;
    QString m_link;
    QString m_pubDate;
};

#endif
