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

int main(int argc, char* argv[]){

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
