/*By Unel at 30/12/21
For Ananta Project*/
#include "cesar.h"
cesar::cesar(int selectGap)
{

    initialize();
    const int size = static_cast<int>(alphabet.size());
    while(selectGap>size){
        selectGap-=size;
    }
    gap = selectGap;
}
bool cesar::initialize(){
    alphabet.push_back('a');//creation alphabet
    alphabet.push_back('b');
    alphabet.push_back('c');
    alphabet.push_back('d');
    alphabet.push_back('e');
    alphabet.push_back('f');
    alphabet.push_back('g');
    alphabet.push_back('h');
    alphabet.push_back('i');
    alphabet.push_back('j');
    alphabet.push_back('k');
    alphabet.push_back('l');
    alphabet.push_back('m');
    alphabet.push_back('n');
    alphabet.push_back('o');
    alphabet.push_back('p');
    alphabet.push_back('q');
    alphabet.push_back('r');
    alphabet.push_back('s');
    alphabet.push_back('t');
    alphabet.push_back('u');
    alphabet.push_back('v');
    alphabet.push_back('w');
    alphabet.push_back('x');
    alphabet.push_back('y');
    alphabet.push_back('z');
    alphabet.push_back('0');
    alphabet.push_back('1');
    alphabet.push_back('2');
    alphabet.push_back('3');
    alphabet.push_back('4');
    alphabet.push_back('5');
    alphabet.push_back('6');
    alphabet.push_back('7');
    alphabet.push_back('8');
    alphabet.push_back('9');
    return true;
}
const QString cesar::chiffre( QString text){
    int size =alphabet.size();
    for (int i(0) ; i < text.size() ; i++)
    {
        auto pos = find(alphabet.begin(), alphabet.end(), text[i]);
        if(pos!=alphabet.end()||text[i]==alphabet[size]){
            int index = pos - alphabet.begin();
            //index trouver

            if((index+gap)>size-1){//gestion de tableaux cyrculaire
                index=index-size;
            }
            int t = index+gap;
            text[i]=alphabet[t];
        }//si la letre se trouve pas dans le dico on linore est on la remplace pas
    }
    return text;
}
const QString cesar::deChiffre( QString text){
    for (int i {text.size()-1}; i >= 0; --i)
    {
        auto pos = find(alphabet.begin(), alphabet.end(), text[i]);
        if(pos!=alphabet.end()||text[i]==alphabet[alphabet.size()-1]){
            int index = pos - alphabet.begin();//index trouver
            if((index-gap)<0){//gestion de tableaux cyrculaire
                index=index+alphabet.size();
                text[i]=alphabet[index-gap];
            }else{
                text[i]=alphabet[index-gap];
            }

        }//si la letre se trouve pas dans le dico on linore est on la remplace pas
    }
    return text;
}
