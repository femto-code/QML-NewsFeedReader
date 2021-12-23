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
    setActive(true);
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

const QString &Feed::description() const
{
    return m_description;
}

void Feed::setDescription(const QString &newDescription)
{
    if (m_description == newDescription)
        return;
    m_description = newDescription;
}

std::unordered_map<int, Item *> Feed::getFeedItems()
{
    return feedItems;
}

int Feed::getItemCount()
{
    return m_itemCount;
}

void Feed::setLink(const QString &newLink)
{
    if (m_link == newLink)
        return;
    m_link = newLink;
}

QString Feed::link()
{
    return m_link;
}

void Feed::get()
{
    if(m_active){

        qInfo() << "Getting Feed from Server...";

        qDebug() << "Feed::get: " << m_nMgr;
        QNetworkReply* reply = m_nMgr->get(QNetworkRequest(QUrl(m_url)));

        if(reply) {
            qInfo() << "Next step...";
        }
    }
    else{
        qDebug() << "No URL set..."; }

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect( m_nMgr, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);
    loop.exec();

    qDebug() << "Timer finished..";

    if(timer.isActive())
        qDebug("Download finished...");
    else
        qDebug("timeout");
}

void Feed::parse(QNetworkReply* reply){

    qInfo() << "Start of parse()...";

    QDomDocument doc("testDoc");

    qDebug() << "Setting doc...";

    if(doc.setContent(reply))
        qInfo() << "Successfully parsed...";
    else
        qDebug() << "What the fuck??";

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    // Go into "channel"
    n = n.firstChild();

    while(!n.isNull()){

        if(n.toElement().tagName() == "link"){
            m_link = n.toElement().text();
        }
        if(n.toElement().tagName() == "description"){
            m_description = n.toElement().text();
        }

        if(n.toElement().tagName() == "item"){

            qInfo() << "Found an item node...";
            QDomNode n2 = n.firstChild();

            Item* newItem = new Item();

            while(!n2.isNull()){

                if(n2.toElement().tagName() == "title"){
                    newItem->setTitle(n2.toElement().text());
                }
                if(n2.toElement().tagName() == "link"){
                    newItem->setLink(n2.toElement().text());
                }
                if(n2.toElement().tagName() == "description"){
                    newItem->setDescription(n2.toElement().text());
                }
                if(n2.toElement().tagName() == "pubDate"){
                    newItem->setPubDate(n2.toElement().text());
                }
                n2 = n2.nextSibling();
            }

            feedItems.emplace(m_itemCount, newItem);
            m_itemCount++;
            qInfo() << m_itemCount;

        }
        n = n.nextSibling();
    }

    qInfo() << "Step out of creating elements...";
}

