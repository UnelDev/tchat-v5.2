#include "launcher.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QString texte;
    QFile fichier("languages/language.ants");
    if(fichier.open(QIODevice::ReadOnly)){
       texte = fichier.readAll();
       fichier.close();
       translator.load("languages/launcher_"+texte+".qm");
    }else{
       translator.load("languages/launcher_fr_FR.qm");
   }
    a.installTranslator(&translator);
    launcher w;
    w.show();
    return a.exec();
}

