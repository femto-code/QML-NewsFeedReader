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

    qputenv("QT_QUICK_BACKEND", "software");
    QGuiApplication app(argc, argv);

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);

    qmlRegisterType<Feed>("SET", 1, 1, "Feed");

    QPointer<FeedList> feedList(new FeedList());
    engine->rootContext()->setContextProperty("feedList", feedList.data());
    feedList->add("https://www.deskmodder.de/blog/feed/");
    feedList->debugFeedList();

    engine->addImportPath(":/");
    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
