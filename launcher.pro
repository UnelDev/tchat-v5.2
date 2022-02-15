QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    launcher/externalserver.cpp \
    launcher/connecttoclient.cpp \
    launcher/main.cpp \
    launcher/launcher.cpp \
    launcher/serverinteraction.cpp \
    launcher/startserveur.cpp \
    client.cpp \
    cesar.cpp

HEADERS += \
    launcher/externalserver.h \
    launcher/connecttoclient.h \
    launcher/launcher.h \
    launcher/serverinteraction.h \
    launcher/startserveur.h \
    client.h \
    cesar.h

FORMS += \
    launcher/externalserver.ui \
    launcher/connecttoclient.ui \
    launcher/launcher.ui \
    launcher/startserveur.ui

TRANSLATIONS += \
    launcher/launcher_fr_FR.ts \
    launcher/launcher_An_AN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    launcher/resource.qrc
