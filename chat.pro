QT       += core gui network multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    client\main.cpp \
    moreinformation.cpp \
    client\parametre.cpp \
    succees.cpp \
    client\widget.cpp \
    cesar.cpp

HEADERS += \
    client.h \
    moreinformation.h \
    cesar.h \
    succees.h \
    client\parametre.h \
    client\widget.h


FORMS += \
    moreinformation.ui \
    succees.ui \
    client\widget.ui \
    client\parametre.ui

TRANSLATIONS += \
    client\chat_fr_FR.ts
    client\chat_An_AN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    client\chat_An_AN.ts
    client\chat_fr_FR.ts

RESOURCES += \
    client\resources.qrc
