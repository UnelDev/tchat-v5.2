#ifndef CHATBOTINTERACTION_H
#define CHATBOTINTERACTION_H

#include <QObject>

class chatBotInteraction
{
    Q_OBJECT
public:
    chatBotInteraction();
    static bool fileSupported(QString nameOfFile);
};

#endif // CHATBOTINTERACTION_H
