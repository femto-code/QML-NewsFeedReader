#include <QGuiApplication>
#include <QtQuick>

#include <iostream>
#include <string>
#include <vector>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Feed.h"
#include <QDomDocument>

using namespace std;

int main(int argc, char* argv[])
{

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

    QGuiApplication app(argc, argv);

// ///////////////////////////////////  Begin of QNAM test

    QNetworkAccessManager* mgr = new QNetworkAccessManager;
    qDebug() << "QNetworkAccessManager" << mgr;

    Feed feed( nullptr, mgr);

    qInfo() << "I'm here";
    feed.get("https://www.deskmodder.de/blog/feed/");

// ///////////////////////////////////  End of QNAM test

    qputenv("QT_QUICK_BACKEND", "software");

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
    engine->addImportPath(":/");

    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
