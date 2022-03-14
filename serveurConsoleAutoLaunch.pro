QT += network
QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
greaterThan(QT_MAJOR_VERSION,5)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    serveurConsoleAutoLaunch/main.cpp \
    serveur/serveur.cpp \
    serveur/utilisateur.cpp \
    cesar.cpp
HEADERS += \
    serveur/serveur.h \
    serveur/utilisateur.h \
    cesar.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
