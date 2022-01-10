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

QList<Item *> Feed::getFeedItems()
{
    return m_FeedItems;
}

QQmlListProperty<Item> Feed::items()
{
    return QQmlListProperty<Item>(this, &m_FeedItems);
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

        qInfo() << "FEED.CPP::get() :: Getting Feed from Server...";

        qDebug() << "FEED.CPP::get() :: " << m_nMgr;
        QNetworkReply* reply = m_nMgr->get(QNetworkRequest(QUrl(m_url)));

        qDebug() << "FEED.CPP::get() :: " << m_url;

        if(reply) {
            qInfo() << "FEED.CPP::get() :: Next step...";
        }
    }
    else{
        qDebug() << "No URL set..."; }

    qDebug() << "FEED.CPP::get() :: Initializing Timer..";
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect( m_nMgr, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    qDebug() << "FEED.CPP::get() :: Starting Timer..";
    timer.start(1000);
    loop.exec();

    qDebug() << "FEED.CPP::get() :: Timer finished..";

    if(timer.isActive())
        qDebug("FEED.CPP::get() :: Download finished...");
    else
        qDebug("FEED.CPP::get() :: timeout");
}

void Feed::parse(QNetworkReply* reply){

    qInfo() << "FEED.CPP::parse() :: Start of parse()...";

    QDomDocument doc("testDoc");

    qDebug() << "FEED.CPP::parse() :: Setting doc...";

    if(doc.setContent(reply))
        qInfo() << "FEED.CPP::parse() :: Successfully parsed...";
    else
        qDebug() << "FEED.CPP::parse() :: What?? Parse fucked up...";

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

            //qInfo() << "Found an item node...";
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
                    QString plain = QTextDocumentFragment::fromHtml(n2.toElement().text()).toPlainText();
                    newItem->setDescription(plain);
                }
                if(n2.toElement().tagName() == "pubDate"){
                    newItem->setPubDate(n2.toElement().text());
                }
                n2 = n2.nextSibling();
            }

            m_FeedItems.push_back(newItem);
            m_itemCount++;
            //qInfo() << m_itemCount;

        }
        n = n.nextSibling();
    }

    qInfo() << "FEED.CPP::parse() :: itemCount:" << m_itemCount;

    qInfo() << "FEED.CPP::parse() :: Step out of creating elements...";
}
