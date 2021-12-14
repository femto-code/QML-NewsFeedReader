#include "Feed.h"

QString Feed::name()
{
    return m_name;
}

void Feed::setName(QString newName)
{
    if(m_name != newName){
        m_name = newName;
        //emit nameChanged();
    }
}

QString Feed::url()
{
    return m_url;
}

void Feed::setUrl(QString newUrl)
{
    if(m_url != newUrl){
        m_url = newUrl;
       //emit urlChanged();
    }
}

int Feed::id()
{
    return m_id;
}

void Feed::setId(int newId)
{
    if(m_id != newId){
        m_id = newId;
        //emit idChanged();
    }
}

bool Feed::active()
{
    return m_active;
}

void Feed::setActive(bool newActive)
{
    if(m_active != newActive){
        m_active = newActive;
        //emit activeChanged();
    }
}

void Feed::get(QString location)
{
    qInfo() << "Getting Feed from Server...";



//    QNetworkReply* reply = m_nMgr->get(QNetworkRequest(QUrl(location)));
    QNetworkReply* reply = qnam->get(QNetworkRequest(QUrl(location)));
//    QNetworkReply* reply = globalManager.get(QNetworkRequest(QUrl(location)));


    if(reply) {
        qInfo() << "Next step...";
    }
}


void Feed::downloadFinished(QNetworkReply * reply)
{
    qInfo() << "Ready to read...";

    if(reply){
        qInfo() << reply->readAll();
    }
}


