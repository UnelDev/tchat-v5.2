/*By Unel at 30/12/21
For Ananta Project*/
#ifndef CESAR_H
#define CESAR_H
#include <QString>
#include <vector>

class cesar
{
public:
    cesar();
    cesar(int selectGap = 1);
    void changegap(const int newGap);
    void addChar(const char add);
    void addTabChar(const std::vector<char> add);
    void chageTabChar(const std::vector<char> change);
    QString chiffre(QString text);
    QString deChiffre(QString text);
private:
    bool initialize();
    int gap;
    std::vector<char> alphabet;

};

#endif // CESAR_H
