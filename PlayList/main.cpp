#include <QApplication>
#include <QQmlApplicationEngine>

#include "applicationloader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.processEvents();
    app.setQuitOnLastWindowClosed(true);

    ApplicationLoader app_loader;

    app_loader.load();

    return app.exec();
}
