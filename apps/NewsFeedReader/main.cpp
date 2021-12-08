//#include <QGuiApplication>
//#include <QtQuick>

//int main(int argc, char* argv[])
//{
//    QGuiApplication app(argc, argv);

//    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
//    engine->addImportPath(":/");
//    engine->addPluginPath(":/");
//    engine->addImportPath("../../plugin");
//    engine->addPluginPath("../../plugin");

//    engine->load(QUrl("qrc:/Mainpage.qml"));

//    return app.exec();
//}

#include <QGuiApplication>
#include <QtQuick>
#include <curl/curl.h>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    qputenv("QT_QUICK_BACKEND", "software");

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
    engine->addImportPath(":/");

    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
