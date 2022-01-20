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
#include "DataBase.h"

int main(int argc, char* argv[]){

    qputenv("QT_QUICK_BACKEND", "software");
    QGuiApplication app(argc, argv);

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);

    qmlRegisterType<Feed>("SET", 1, 1, "Feed");
    //qmlRegisterType<Item>("SET2", 2, 2, "Item");

    QPointer<FeedList> feedList(new FeedList());
    engine->rootContext()->setContextProperty("feedList", feedList.data());
    feedList->add("https://www.deskmodder.de/blog/feed/");
    //feedList->debugFeedList();

    DataBase::open(":local:","TimoFlo","SET22");
    bool result = DataBase::readAll(*feedList);
    qDebug() << "Database result: " << result;

    if(result == false){
        DataBase::createTableFeedItems();
        DataBase::createTableFeedSources();
    }

    engine->addImportPath(":/");
    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
