#include <QQmlApplicationEngine>
#include <QGuiApplication>


#include <src/MainClass.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");

    MainClass mainC;

    qRegisterMetaType<QSharedPointer<QList<QSharedPointer<LogDataType>>>>("QSharedPointer<QList<QSharedPointer<LogDataType>>>");

    return app.exec();
}
