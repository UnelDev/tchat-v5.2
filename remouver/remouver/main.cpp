#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QDateTime>
#include <QSettings>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc<2){
        std::cout << "error to mutch argument "<<std::endl;
        exit(1);
    }else if(argc>2){
        std::cout << "error to less argument "<<std::endl;
        exit(1);
    }
    const QString m_name = argv[1];
    if(m_name==""){
        return 1;
    }
    QDir dir;// backup de la salle
    dir.mkdir("Log_Backup");
    QFile::remove(m_name+"/"+m_name+".dat");
    const QString nameSave = m_name+"_"+QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss");
    QFile::rename(m_name+"/"+m_name+".log",nameSave);

    QSettings room("room.ini", QSettings::IniFormat);
    room.setValue("NbOfRoom",room.value("NbOfRoom").toInt()-1);//on reduit le nombre de salle
    QFile::copy(nameSave,"Log Backup\\"+nameSave);
    QFile::remove(nameSave);
    dir.remove(m_name);
    std::cout << "remouve sucess"<<std::endl;
    return a.exec();
}
