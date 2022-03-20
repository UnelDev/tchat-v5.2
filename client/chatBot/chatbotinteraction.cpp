#include "chatbotinteraction.h"

chatBotInteraction::chatBotInteraction()
{
}
bool chatBotInteraction::ImageSupported(const QString nameOfFile)
{
    bool state = false;
    const QString extention = nameOfFile.split(".").last();
    if (extention == "png")
    {
        state = true;
    }
    if (extention == "jpeg")
    {
        state = true;
    }
    if (extention == "JPEG")
    {
        state = true;
    }
    if (extention == "JPG")
    {
        state = true;
    }
    // JPEG 2000
    if (extention == "jp2")
    {
        state = true;
    }
    if (extention == "j2k")
    {
        state = true;
    }
    if (extention == "jpf")
    {
        state = true;
    }
    if (extention == "jpx")
    {
        state = true;
    }
    if (extention == "jpm")
    {
        state = true;
    }
    if (extention == "mj2")
    {
        state = true;
    }
    // TIFF
    if (extention == "tif")
    {
        state = true;
    }
    if (extention == "tiff")
    {
        state = true;
    }
    // gif
    if (extention == "gif")
    {
        state = true;
    }
    // webP
    if (extention == "jpg")
    {
        state = true;
    }
    return state;
}
bool chatBotInteraction::textSuported(const QString nameOfFile)
{
    bool state = false;
    const QString extention = nameOfFile.split(".").last();
    //texte brut
    if (extention == "txt")
    {
        state = true;
    }
    //texte mis en forme
    if (extention == "html")
    {
        state = true;
    }
    if (extention == "htm")
    {
        state = true;
    }
    if (extention == "md")
    {
        state = true;
    }
    if (extention == "css")
    {
        state = true;
    }
    if (extention == "xml")
    {
        state = true;
    }
    //extention de programation
    if (extention == "h")
    {
        state = true;
    }
    if (extention == "hpp")
    {
        state = true;
    }
    if (extention == "c")
    {
        state = true;
    }
    if (extention == "cpp")
    {
        state = true;
    }
    if (extention == "js")
    {
        state = true;
    }
    if (extention == "py")
    {
        state = true;
    }
    if (extention == "bat")
    {
        state = true;
    }
    if (extention == "cmd")
    {
        state = true;
    }
    if (extention == "rs")
    {
        state = true;
    }
    if (extention == "rlib")
    {
        state = true;
    }
    if (extention == "java")
    {
        state = true;
    }
    
    return state;
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
