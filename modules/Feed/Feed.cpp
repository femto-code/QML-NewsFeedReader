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

void Feed::get()
{
    qInfo() << "Getting Feed from Server...";


    qDebug() << "Feed::get: " << m_nMgr;
    QNetworkReply* reply = m_nMgr->get(QNetworkRequest(QUrl(m_url)));

    if(reply) {
        qInfo() << "Next step...";
    }
}

void Feed::parse(QNetworkReply* reply)
{
    char* s = reply->readAll().data();
    size_t len = strlen(s);
    char* s2 = new char[len+1];
    s2[len]='\0';

    cout << "\nParsing my students data (sample.xml)....." << endl;

    // TODO: text will be the XML / RSS data queried by
    // QNetworkAccessManager Class ...WIP

    QDomDocument doc("mydocument");
    QFile file("../NewsFeedReader/mydocument.xml");
    if (!file.open(QIODevice::ReadOnly))
        return 1;
    if (!doc.setContent(&file)) {
        file.close();
        return 1;
    }
    file.close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            cout << qPrintable(e.tagName()) << '\n'; // the node really is an element.
        }
        n = n.nextSibling();
    }

    // ////// END OF EXAMPLE PROGRAM for demonstrating use of xml parser ///////////////
}


