#include <QGuiApplication>
#include <QtQuick>

#include <iostream>
#include <string>
#include <vector>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Feed.h"
#include "FeedList.h"

using namespace std;

int main(int argc, char* argv[]){


// ///////////////////////////////////  Begin of QNAM test

    //QNetworkAccessManager* mgr = new QNetworkAccessManager;
    //qDebug() << "QNetworkAccessManager" << mgr;

    Feed feed;



    qInfo() << "I'm here";
    feed.setUrl("https://www.deskmodder.de/blog/feed/");
    feed.get();

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
