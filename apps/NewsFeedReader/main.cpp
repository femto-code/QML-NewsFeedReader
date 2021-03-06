#include <QGuiApplication>
#include <QtQuick>

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

    //feedList->debugFeedList();

    DataBase::open("NFRdb","TimoFlo","SET22");
    bool result = DataBase::readAll(*feedList);
    qDebug() << "Database result: " << result;

    if(result == false){
        qInfo() << "Creating 1st table..." << DataBase::createTableFeedItems();
        qInfo() << "Creating 2nd table..." << DataBase::createTableFeedSources();
        feedList->add("https://www.deskmodder.de/blog/feed/");
    } else {
        feedList->triggerUpdate();
    }

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, feedList, &FeedList::triggerUpdate);

    timer.start(600000);

    engine->addImportPath(":/");
    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
