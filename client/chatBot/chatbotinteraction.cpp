#include "chatbotinteraction.h"

chatBotInteraction::chatBotInteraction(){}
bool chatBotInteraction::ImageSupported(const QString nameOfFile)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QList<QString>extentionList{"png","jpeg","JPEG","JPG","jp2","j2k","jpf","jpx","jpm","mj2","tif","tiff","gif","jpg"};
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
    QList<QString> extentionList{/*texte brut*/"txt",/*html*/"html","htm",/*text riche*/"md","css","xml",/*extention de progamation*/"h","hpp","c","cpp","js","py","bat","cmd","rs","rlib","java","cs" };
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
