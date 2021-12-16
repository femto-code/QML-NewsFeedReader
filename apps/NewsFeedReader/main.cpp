#include "main.h"

using namespace std;

// //////////////////
static QPointer<QNetworkAccessManager> globalManager;

QNetworkAccessManager* nMgr(){
    Q_ASSERT(!qApp || QThread::currentThread() == qApp->thread());
    return globalManager;
}
// /////////////////


int main(int argc, char* argv[])
{

    cout << "\nParsing my students data (sample.xml)....." << endl;

    // TODO: text will be the XML / RSS data queried by
    // QNetworkAccessManager Class ...WIP

    //return 0; // ////// END OF EXAMPLE PROGRAM for demonstrating use of rapixml ///////////////

    QGuiApplication app(argc, argv);

// ///////////////////////////////////  Begin of QNAM test
    QNetworkAccessManager mgr;
    globalManager = &mgr;

    Feed feed(&mgr);

    qInfo() << "I'm here";
    feed.get("https://www.deskmodder.de/blog/feed/");
// ///////////////////////////////////  End of QNAM test

    qputenv("QT_QUICK_BACKEND", "software");

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
    engine->addImportPath(":/");

    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
