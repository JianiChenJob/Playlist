#include "applicationloader.h"

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

#include <QtQuick>
#include <QObject>

#include "xmlparser.h"
#include "asyncimageprovider.h"
#include "entrymanager.h"


static const QString s_app_content = "top_songs_xml.xml";

ApplicationLoader *ApplicationLoader::Instance = nullptr;

static const bool SKIP_LOADING_COLLECTIONS = false;

ApplicationLoader::ApplicationLoader()
{
    Instance = this;
}


void ApplicationLoader::load()
{
    AsyncImageProvider *image_provider = new AsyncImageProvider;

    m_engine.addImageProvider("async", image_provider);

    QString content_folder = QFileInfo(QDir::currentPath() + "\\..\\PlayList\\content\\").absoluteFilePath();

    XMLParser parser;

    EntryManager *entry_manager = new EntryManager;
    parser.parseEntries(entry_manager, content_folder + s_app_content);

    m_engine.rootContext()->setContextProperty("entryManager", entry_manager);

    QString main_qml = QDir::currentPath() + "\\..\\PlayList\\main.qml";
    if(!QFileInfo(main_qml).exists())
    {
        QMessageBox::warning(nullptr, "Could not find main.qml", "Could not find main.qml");
    }

    connect(&m_engine, &QQmlApplicationEngine::objectCreated,
            this, &ApplicationLoader::objectCreated);

    m_engine.load(main_qml);

    QObject::connect(&m_engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));


}

void ApplicationLoader::objectCreated(QObject *object, const QUrl &url)
{
    qDebug() << "Loading QML object " << object << " " << url;
}

