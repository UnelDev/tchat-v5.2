QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    serveur/main.cpp \
    serveur/serveur.cpp \
    succees.cpp \
    serveur/utilisateur.cpp \
    serveur/widget.cpp \
    serveur/parametre.cpp \
    moreinformation.cpp \
    cesar.cpp \
    client.cpp \
    client/chatBot/useraction.cpp \
    client/chatBot/changeuserroom.cpp
HEADERS += \
    serveur/serveur.h \
    succees.h \
    serveur/utilisateur.h \
    serveur/widget.h \
    serveur/parametre.h \
    moreinformation.h \
    cesar.h \
    client.h \
    client/chatBot/useraction.h \
    client/chatBot/changeuserroom.h
FORMS += \
    succees.ui \
    serveur/widget.ui \
    serveur/parametre.ui \
    moreinformation.ui \
    client/chatBot/useraction.ui \
    client/chatBot/changeuserroom.ui

TRANSLATIONS += \
    serveur/serveur_fr_FR.ts
    serveur/serveur_an_AN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    serveur/resource.qrc
