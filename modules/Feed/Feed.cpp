#include "Feed.h"
#include "FeedList.h"

const QString Feed::name() const
{
    return m_name;
}

void Feed::setName(QString newName)
{
    if(m_name != newName){
        m_name = newName;
    }
}

const QString Feed::url() const
{
    return m_url.toString();
}

void Feed::setUrl(QString newUrl)
{
    if(m_url.toString() != newUrl){
        QUrl test(newUrl);
        if(test.isValid()){
            m_url = test;
            qInfo() << "Valid Url";
            setActive(true);
        }else{
            qDebug() << "Non conformant Url";
        }
    }
}

int Feed::id() const
{
    return m_id;
}

void Feed::setId(int newId)
{
    if(m_id != newId){
        m_id = newId;
    }
}

bool Feed::active() const
{
    return m_active;
}

void Feed::setActive(bool newActive)
{
    if(m_active != newActive){
        m_active = newActive;
    }
}

void Feed::setLink(const QString &newLink) {
    if (m_link == newLink)
        return;
    m_link = newLink;
}

const QString Feed::link() const {
    return m_link;
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

const QList<Item *> Feed::FeedItems() const
{
    return m_FeedItems;
}

void Feed::setFeedItems(const QList<Item *> l)
{
    if (l == m_FeedItems)
        return;
    m_FeedItems = l;
}

QList<Item *> Feed::getFeedItems()
{
    return m_FeedItems;
}

int Feed::getItemCount()
{
    return m_itemCount;
}

void Feed::get()
{
    if(m_active){
        connect(m_nMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(parse(QNetworkReply*)));
        qInfo() << "FEED.CPP::get() :: Getting Feed from Server...";
        qDebug() << "FEED.CPP::get() :: " << m_nMgr;
        QNetworkReply* reply = m_nMgr->get(QNetworkRequest(m_url));
        qDebug() << "FEED.CPP::get() :: " << m_url;
        if(reply) {
            qInfo() << "FEED.CPP::get() :: Next step...";
        }
    }
    else{
        qDebug() << "No URL set..."; }
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

        if(n.toElement().tagName() == "title"){
            qInfo() << "!!!!!!: FEED.CPP::parse() :: Current m_name: " << m_name << ", tagNameTitle: "<<n.toElement().text();
            if( (m_name != n.toElement().tagName()) && (m_name != "") ){
                return;
            }
            m_name = n.toElement().text();
        }
        if(n.toElement().tagName() == "link"){
            m_link = n.toElement().text();
        }
        if(n.toElement().tagName() == "description"){
            m_description = n.toElement().text();
        }
        if(n.toElement().tagName() == "item"){
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
        }
        n = n.nextSibling();
    }

    qInfo() << "FEED.CPP::parse() :: itemCount:" << m_itemCount;

    qInfo() << "FEED.CPP::parse() :: Step out of creating elements...";
    disconnect(m_nMgr, nullptr, nullptr, nullptr);
}
