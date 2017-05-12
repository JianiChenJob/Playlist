#pragma once

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class ApplicationLoader : public QObject
{
//=============================================================================
// PUBLIC
//=============================================================================
public:
    ApplicationLoader();

    static ApplicationLoader *Instance;

    // Load qml files
    void load();

//=============================================================================
// SLOTS
//=============================================================================
private slots:
    // main qml is loaded
    void objectCreated(QObject * object, const QUrl & url);

//=============================================================================
// PRIVATE
//=============================================================================
private:

    QQmlApplicationEngine m_engine;
};
