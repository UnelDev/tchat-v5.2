/*By Unel at 30/12/21
For Ananta Project*/
#include "widget.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QSettings language("language/language.ini", QSettings::IniFormat);
    translator.load(language.value("placementOf"+language.value("CurrentLangage").toString()).toString());
    a.installTranslator(&translator);
    Widget w;
    w.show();
    return a.exec();
}
