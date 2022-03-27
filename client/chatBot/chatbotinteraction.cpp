#include "chatbotinteraction.h"

chatBotInteraction::chatBotInteraction(){}
bool chatBotInteraction::ImageSupported(const QString nameOfFile)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QList<QString>extentionList{"png","jpeg","JPEG","JPG","jp2","j2k","jpf","jpx","jpm","mj2","tif","tiff","gif","jpg","bmp"};
    if(settings.contains("addImgFormat/nbAdd")){
        for (int i = 0; i <= settings.value("addImgFormat/nbAdd").toInt(); i++)
        {
            extentionList.append(settings.value("addImgFormat/"+QString::number(i)).toString());
        }
        
    }
    const QString extention = nameOfFile.split(".").last();
    if(extentionList.indexOf(extention)!=-1){
        return true;
    }else{
        return false;
    }
}
bool chatBotInteraction::textSuported(const QString nameOfFile)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QList<QString> extentionList{/*texte brut*/"txt",/*html*/"html","htm",/*text riche*/"md","css","xml","json",/*extention de progamation*/"h","hpp","c","cpp","js","py","bat","cmd","rs","rlib","java","cs" };
    if(settings.contains("addtxtFormat/nbAdd")){
        for (int i = 0; i <= settings.value("addtxtFormat/nbAdd").toInt(); i++)
        {
            extentionList.append(settings.value("addtxtFormat/"+QString::number(i)).toString());
        }

    }

    const QString extention = nameOfFile.split(".").last();
    if(extentionList.indexOf(extention)!=-1){
        return true;
    }else{
        return false;
    }
}
QString chatBotInteraction::exctractText(const QString nameOfFile, const int nbOfLinePrint)
{
    QFile inputFile(nameOfFile);
    QString file;
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        for (int i = 0; i < nbOfLinePrint; ++i)
        {
            QString line = in.readLine();
            file += "<br>" + line;
            if (in.atEnd())
            {
                break;
            }
        }
        inputFile.close();
        return file;
    }
    else
    {
        return QString::number(-1);
    }
}
const QList<QList<QString>>chatBotInteraction::helpChatBot(){
    QList< QList<QString>>liste;//creation de la liste principale

    const QList<QString>one{tr("help"),tr("permet d'aficher l'aide ❓")};
    liste.push_back(one);

    const QList<QString>two{tr("ping"),tr("permet de montrer le ping avec le serveur ⏱️")};
    liste.push_back(two);

    const QList<QString>four{tr("info"),tr("permet de montrer ceertaine info sur le serveur ℹ️")};
    liste.push_back(four);

    const QList<QString>five{tr("cmprs"),tr("permet de compresser la fenetre 📏 peut aussi etre : condense")};
    liste.push_back(five);

    const QList<QString>six{"clear",tr("permet de netoier la zonne de reception 🗑️")};
    liste.push_back(six);

    const QList<QString>seven{"clearAll",tr("permet de netoier la zonne de reception pour tout les utilisateur 🗑️")};
    liste.push_back(seven);

    const QList<QString>eight{"promot",tr("permet de promouvoir un utilisateur a un grade inférieur au vautre 🆙")};
    liste.push_back(eight);

    const QList<QString>nine{"acept",tr("permet chager de salon un utilisateur il faut etre admin ou superieur pour faire cette action 💱")};
    liste.push_back(nine);

    return liste;
}
