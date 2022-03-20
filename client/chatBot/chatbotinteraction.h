#ifndef CHATBOTINTERACTION_H
#define CHATBOTINTERACTION_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QSettings>

class chatBotInteraction : public QObject
{
    Q_OBJECT
public:
    chatBotInteraction();
    static bool ImageSupported(const QString nameOfFile);
    static bool textSuported(const QString nameOfFile);
    static QString exctractText(const QString nameOfFile,const int nbOfLinePrint=10);
};

#endif // CHATBOTINTERACTION_H
