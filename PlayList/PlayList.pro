TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp \
    applicationloader.cpp \
    xmlparser.cpp \
    entrymanager.cpp \
    XML/qxmlhelper.cpp \
    XML/xmlhelper.cpp \
    XML/xmlloader.cpp \
    XML/xmlwriter.cpp \
    Common/colorhelper.cpp \
    Common/filebrowser.cpp \
    Common/filehelper.cpp \
    Common/filereader.cpp \
    Common/infoparser.cpp \
    Common/mathhelper.cpp \
    Common/qstringhelper.cpp \
    Common/randomhelper.cpp \
    Common/stringhelper.cpp \
    Image/colordialog.cpp \
    Image/imagehelper.cpp \
    asyncimageprovider.cpp \
    tinyxml2/tinyxml2.cpp

RESOURCES += qml.qrc

INCLUDEPATH += tinyxml2/ \
    Common/ \
    XML/ \
    Image/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    content/top_songs_xml.xml \
    MultiPointPinchArea.qml

HEADERS += \
    applicationloader.h \
    xmlparser.h \
    entrymanager.h \
    XML/qxmlhelper.h \
    XML/xmlhelper.h \
    XML/xmlloader.h \
    XML/xmlwriter.h \
    Common/colorhelper.h \
    Common/filebrowser.h \
    Common/filehelper.h \
    Common/filereader.h \
    Common/infoparser.h \
    Common/mathhelper.h \
    Common/qstringhelper.h \
    Common/randomhelper.h \
    Common/stringhelper.h \
    Common/uniquelist.h \
    Image/colordialog.h \
    Image/imagehelper.h \
    asyncimageprovider.h \
    tinyxml2/tinyxml2.h
