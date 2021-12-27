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
        std::cout << "No URL set..."; }
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
    emit descriptionChanged();
}

void Feed::setLink(const QString &newLink)
{
    if (m_link == newLink)
        return;
    m_link = newLink;
    emit linkChanged();
}

QString Feed::link()
{
    return m_link;
}

void Feed::parse(QNetworkReply* reply){

    QDomDocument doc("testDoc");
    if(doc.setContent(reply))
        qInfo() << "Successfully parsed...";

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    // Go into "channel"
    n = n.firstChild();

//    // Gets list of the childs of the node
//    QDomNodeList nList = docElem.childNodes();

//    // But here we can see, that there is only one child in "channel", which is very unlikely
//    qInfo() << "child count: " << nList.size();

    while(!n.isNull()){

        if(n.toElement().tagName() == "link"){
            m_link = n.toElement().text();
        }
        if(n.toElement().tagName() == "description"){
            m_description = n.toElement().text();
        }

        if(n.toElement().tagName() == "item"){
            m_itemCount++;

            while(!n.isNull()){

                /*
                 * Aktuelles Problem:
                 *      Ich müsste für jedes Item eine Map anlegen, damit ich die Werte darin ablegen kann, müsste mir aber auch die Iteratoren über diese Maps merken,
                 *      um überhaupt darauf zugreifen zu können..
                 *
                */
                if(n.toElement().tagName() == "title"){

                    itemValues.emplace("title", n.toElement().text());
                }
                if(n.toElement().tagName() == "link"){

                    itemValues.emplace("link", n.toElement().text());
                }
                if(n.toElement().tagName() == "description"){

                    itemValues.emplace("description", n.toElement().text());
                }
                if(n.toElement().tagName() == "pubDate"){

                    itemValues.emplace("pubDate", n.toElement().text());
                }
                n = n.nextSibling();
            }
        }
        n = n.nextSibling();
        qInfo() << m_description;

    }









//    while(!n.isNull()) {

//        qInfo() << "Step into creating elements...";
//        qInfo() << n.toElement().tagName();

//        if(n.toElement().tagName() == "title"){
//            qInfo() << "comparison works";
//            qInfo() << n.toElement().text();   // This works!
//        }

//        if(n.toElement().tagName() == "lastBuildDate"){
//            qInfo() << n.toElement().text();
//        }

// //        QDomElement e = n.toElement(); // try to convert the node to an element.
// //        if(!e.isNull()) {
// //            qInfo() << "Inside creating element...";
// //            cout << qPrintable(e.tagName()) << '\n'; // the node really is an element.
// //        // cout just prints after exiting the program, that's why I use qInfo() here aswell
// //            qInfo() << e.tagName();
// //        }


//        n = n.nextSibling();

//        // I'm just checking here if next sibling is null
// //        if(n.isNull())
// //            qInfo() << "something went wrong with nexSibling()...";
//    }

    qInfo() << "Step out of creating elements...";

}


/*
void Feed::parse(QNetworkReply* reply)
{
//    char* s = reply->readAll().data();
//    size_t len = strlen(s);
//    char* s2 = new char[len+1];
//    s2[len]='\0';

    qInfo() << "\nParsing my students data (sample.xml).....";

    // TODO: text will be the XML / RSS data queried by
    // QNetworkAccessManager Class ...WIP

    QDomDocument doc("mydocument");
    QFile file("../NewsFeedReader/mydocument.xml");
    if (!file.open(QIODevice::ReadOnly))
        //return 1;
    if (!doc.setContent(&file)) {
        file.close();
        //return 1;
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
*/

