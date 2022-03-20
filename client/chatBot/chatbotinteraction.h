#ifndef CHATBOTINTERACTION_H
#define CHATBOTINTERACTION_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class chatBotInteraction : public QObject
{
    Q_OBJECT
public:
    chatBotInteraction();
    static bool fileSupported(const QString nameOfFile);
    static QString exctractText(const QString nameOfFile,const int nbOfLinePrint);
};

#endif // CHATBOTINTERACTION_H
