#include <QGuiApplication>
#include <QtQuick>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>

#include "Feed.h"
#include "Item.h"
#include "FeedList.h"
#include "DataBase.h"
#include "updateThread.h"

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
        //feedList->add("https://www.deskmodder.de/blog/feed/");
    }

//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &FeedList::triggerUpdate);
//    timer->start(3000);

    UpdateThread t1(feedList);
    t1.start();
    //engine->rootContext()->setContextProperty( "myThread", &myThread );


    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &t1, &UpdateThread::doUpdate);
//    QObject::connect(&timer, &QTimer::timeout, []() {
//        qDebug() << "Lambda";
//
//    });
    timer.start(60000);

    engine->addImportPath(":/");
    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
