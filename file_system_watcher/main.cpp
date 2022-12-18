#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>

#include "listmodelwatchedpath.h"
#include "listwatchedpath.h"
#include "testwatcher.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<ListModelWatchedPath>("FolderTracker", 1, 0, "LVModel");
    qmlRegisterType<ListWatchedPath>("FolderTracker", 1, 0, "LVwatchedPaths");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "file_system_watcher_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    ListWatchedPath mPaths;
    engine.rootContext()->setContextProperty(QStringLiteral("mPaths"), &mPaths);
    TestWatcher folderWatcher;
    folderWatcher.setItemsPtr(mPaths.getPathsPtr());
    engine.rootContext()->setContextProperty(QStringLiteral("folderWatcher"), &folderWatcher);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
