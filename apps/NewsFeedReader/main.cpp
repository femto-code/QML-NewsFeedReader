#include <QGuiApplication>
#include <QtQuick>

#include <iostream>
#include <string>
#include <vector>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Feed.h"
#include "Item.h"
#include "FeedList.h"

int main(int argc, char* argv[]){


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
    qInfo() << testItem[10]->title();
    qInfo() << testItem[10]->pubDate();
    qInfo() << testItem[10]->description();


// ///////////////////////////////////  End of QNAM test

    qputenv("QT_QUICK_BACKEND", "software");

    QGuiApplication app(argc, argv);

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);

    qmlRegisterType<Feed>("SET", 1, 1, "Feed");

    QPointer<FeedList> feedList(new FeedList());
    engine->rootContext()->setContextProperty("feedList", feedList.data());

    engine->addImportPath(":/");
    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
