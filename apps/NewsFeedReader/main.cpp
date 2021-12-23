#include <QGuiApplication>
#include <QtQuick>

#include <iostream>
#include <string>
#include <vector>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Feed.h"
#include "Item.h"

int main(int argc, char* argv[]){

    QGuiApplication app(argc, argv);

// ///////////////////////////////////  Begin of QNAM test

    //QNetworkAccessManager* mgr = new QNetworkAccessManager;
    //qDebug() << "QNetworkAccessManager" << mgr;

    Feed feed;

    qInfo() << "I'm here";
    feed.setUrl("https://www.deskmodder.de/blog/feed/");
    feed.get();
    qInfo() << "Back in main... get ItemCount: " << feed.getItemCount();
    std::unordered_map<int, Item*> testItem = feed.getFeedItems();
    qInfo() << testItem[10]->link();

// ///////////////////////////////////  End of QNAM test

    qputenv("QT_QUICK_BACKEND", "software");

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
    engine->addImportPath(":/");

    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
