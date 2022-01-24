/*By Unel at 30/12/21
For Ananta Project*/
#include "parametre.h"
#include "ui_parametre.h"

parametre::parametre(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::parametre)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    ui->checkBox_2->setChecked(settings->value("settings/visualNotification").toBool());
    ui->checkBox->setChecked(settings->value("settings/SoundNotification").toBool());
    ui->setcollor->setCurrentText(settings->value("settings/color").toString());
    ui->comboBox->setCurrentText(settings->value("settings/path").toString());
    ui->language->setCurrentText(settings->value("settings/langage").toString());
    ui->checkBox_3->setChecked(settings->value("settings/SaveMessage").toBool());
    ui->checkboxmodecondensee->setChecked(settings->value("settings/server/activeTransparnece").toBool());
    starttheme();
    checklanguage();
}
parametre::~parametre()
{
    delete ui;
}
void parametre::checklanguage(){
    QSettings language("language/language.ini", QSettings::IniFormat);
    if(!language.contains("nbLanguage")){
        language.setValue("nbLanguage",1);
        language.setValue("langageName/1","francais");
        language.setValue("pathOfFrancais","/franscais");
        language.setValue("CurrentLangage","francais");
        QMessageBox::warning(nullptr,tr("erreur de traduction"),tr("ops se message ne doit pas saficher si il saficher c'st qu'il y a pas de traduction disponble, contacter nous sur le discord ou reinsatalez le tchat","dans les chargemment des trad"));
    }
    ui->language->clear();
    for (int i = 0;i<language.value("nbLanguage").toInt();i++) {//tan qu'il reste des launge
        ui->language->addItem(language.value("langageName/"+QString::number(i+1)).toString());
   }
    ui->language->setCurrentText(settings->value("CurrentLangage").toString());
}
QPalette parametre::starttheme(){
   if(settings->value("settings/color").toString()==tr("noir","meme text que dans la selection de couleur")){
       ui->setcollor->setCurrentIndex(2);
        return darkmode();
   }else if(settings->value("settings/color").toString()==tr("blanc","meme text que dans la selection de couleur")){
       ui->setcollor->setCurrentIndex(0);
       return whitemode();
   }else if(settings->value("settings/color").toString()==tr("oled","meme text que dans la selection de couleur")){
       ui->setcollor->setCurrentIndex(3);
       return darkmodeUltra();
   }else if(settings->value("settings/color").toString()==tr("blanc ultra","meme text que dans la selection de couleur")){
       ui->setcollor->setCurrentIndex(1);
       return whitehultra();
   }else{
       return whitemode();
       QMessageBox::warning(this,tr("erreur de lecture"),tr("il est imposible de lire la couleur par defaut. elle est donc par defaut a blanc"));
       on_setcollor_activated(tr("blanc","atention meme chose que dans l'ui la combo box de coulleur"));
   }
}
QPalette parametre::darkmode(){
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    return darkPalette;
}
QPalette parametre::whitemode(){
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(240,240,240));
    darkPalette.setColor(QPalette::WindowText, QColor(0,0,0));
    darkPalette.setColor(QPalette::Base, QColor(255,255,255));
    darkPalette.setColor(QPalette::AlternateBase, QColor(240,240,240));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::black);
    darkPalette.setColor(QPalette::ToolTipText, Qt::black);
    darkPalette.setColor(QPalette::Text, Qt::black);
    darkPalette.setColor(QPalette::Button, QColor(240,240,240));
    darkPalette.setColor(QPalette::ButtonText, Qt::black);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(59, 62, 178));
    darkPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    return darkPalette;
}
QPalette parametre::darkmodeUltra(){
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(0,0,0));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(0,0,0));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(0,0,0));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    return darkPalette;
}
QPalette parametre::whitehultra(){
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(255,255,255));
    darkPalette.setColor(QPalette::WindowText, QColor(0,0,0));
    darkPalette.setColor(QPalette::Base, QColor(255,255,255));
    darkPalette.setColor(QPalette::AlternateBase, QColor(255,255,255));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::black);
    darkPalette.setColor(QPalette::ToolTipText, Qt::black);
    darkPalette.setColor(QPalette::Text, Qt::black);
    darkPalette.setColor(QPalette::Button, QColor(255,255,255));
    darkPalette.setColor(QPalette::ButtonText, Qt::black);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(59, 62, 178));
    darkPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    return darkPalette;
}
void parametre::on_checkBox_2_toggled(bool checked)
{
        settings->setValue("settings/visualNotification",checked);
}
void parametre::on_checkBox_toggled(bool checked)
{
    settings->setValue("settings/SoundNotification",checked);
}
void parametre::on_comboBox_2_activated(const QString &arg1)
{
    settings->setValue("CurrentLangage", arg1);
}
void parametre::on_setcollor_activated(const QString &arg1)
{
    settings->setValue("settings/color",arg1);
    starttheme();
}
void parametre::on_comboBox_activated(const QString &arg1)
{
    {
        if(arg1==tr("selectioner une musique","atention meme chose que dans l'ui la combo box de selection de musique")){
            //path = reponse of message box
            settings->setValue("settings/path",QFileDialog::getOpenFileName(this, tr("charger une musique"), nullptr , tr("fichier audio (*.MP3 *.WAV)")));
            if(settings->value("settings/path")==""){
                settings->setValue("settings/path",":/sound/notifdefault.wav");
                QMessageBox::warning(this,tr("erreur de chemin"),tr("atention le chemin de fichier et inutilisablepassage en musique par default"));

            }
        }else if(arg1==tr("blup blup","atention meme chose que dans l'ui la combo box de selection de musique")){
            settings->setValue("sound/path",":/sound/Sonnerie_Ananta.wav");
        }else if(arg1==tr("son par default","atention meme chose que dans l'ui la combo box de selection de musique")){
            settings->setValue("sound/path",":/sound/notifdefault.wav");
        }
    }
}
void parametre::on_site_clicked()
{
    if(!QDesktopServices::openUrl(QUrl("https://anantasystem.com"))){
        QMessageBox::information(this,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir le probleme vien de votre navigateur par default taper anantasystem.com dans votre navigateur et faite nous un raport de bug sur le discord"));
    }
}
void parametre::on_discord_clicked()
{
    if(!QDesktopServices::openUrl(QUrl("https://anantasystem.com/discord.html"))){
        QMessageBox::information(this,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir le probleme vien de votre navigateur par default taper anantasystem.com/discord.html dans votre navigateur et faite nous un raport de bug sur le discord"));
    }
}
void parametre::on_tweter_clicked()
{
    if(!QDesktopServices::openUrl(QUrl("https://anantasystem.com/twitter.html"))){
        QMessageBox::information(this,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir le probleme vien de votre navigateur par default taper anantasystem.com/twitter.html dans votre navigateur et faite nous un raport de bug sur le discord"));
    }
}
void parametre::on_don_clicked(){
    if(!QDesktopServices::openUrl(QUrl("https://anantasystem.com/tip.html"))){
        QMessageBox::information(this,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir le probleme vien de votre navigateur par default taper anantasystem.com/tip.html dans votre navigateur et faite nous un raport de bug sur le discord"));
    }
}
void parametre::on_checkboxmodecondensee_toggled(bool checked)
{
    settings->setValue("settings/server/activeTransparnece",checked);
}
void parametre::on_pushButton_3_clicked()
{
    succes = new sucees(this);
    succes->show();
}
void parametre::on_pushButton_4_clicked()
{
    moreinformations = new moreinformation(this);
    moreinformations->show();
}
void parametre::on_pushButton_clicked()
{
    QMessageBox::information(this,tr("changement couleur","dans les boite d'aide"),tr("permet de changer la couleur par defaut","boite d'aide"));
}
void parametre::on_pushButton_2_clicked()
{
    QMessageBox::information(this,tr("parametre de mode condensée","dans les boite d'aide"),tr("permet d'activer le mode transparent dans le mode condesée ATENTION: ne fonctionne pas dans windows 11","boite d'aide"));
}
void parametre::on_pushButton_5_clicked()
{
    QFile file("chat.dat");
    if(file.remove()){
        QMessageBox::information(this,tr("supression reussi","dans la supression"),tr("les sauvgarde de discussion on été suprimée il faut relancer le tchat pour que ce changement soit efectif","supression de message"));
    }else{
        QMessageBox::critical(this,tr("supression echouer","dans la supression"),tr("les sauvgarde de discussion n'on pas pue etre suprimée contacter nous sur notre discord","supression de message"));
    }
}


void parametre::on_checkBox_3_toggled(bool checked)
{
    settings->setValue("settings/SaveMessage", checked);
}


void parametre::on_recap_clicked() {emit parametre::recapClicked();}

