#include "widget.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    QString texte;
    QFile fichier("languages/language.ants");
    if(fichier.open(QIODevice::ReadOnly)){
       texte = fichier.readAll();
       fichier.close();
       translator.load("languages/chat_"+texte+".qm");
    }else{
       translator.load("languages/chat_fr_FR.qm");
   }
    app.installTranslator(&translator);
    Widget w;
    w.show();
    return app.exec();
}
