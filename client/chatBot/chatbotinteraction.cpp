#include "chatbotinteraction.h"

chatBotInteraction::chatBotInteraction()
{}
bool chatBotInteraction::fileSupported(QString nameOfFile){
    bool state = false;
    if(nameOfFile.split(".").last()=="png"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="jpeg"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="JPEG"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="JPG"){
        state = true;
    }
    //JPEG 2000
    if(nameOfFile.split(".").last()=="jp2"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="j2k"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="jpf"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="jpx"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="jpm"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="mj2"){
        state = true;
    }
    //TIFF
    if(nameOfFile.split(".").last()=="tif"){
        state = true;
    }
    if(nameOfFile.split(".").last()=="tiff"){
        state = true;
    }
    //gif
    if(nameOfFile.split(".").last()=="gif"){
        state = true;
    }
    //webP
    if(nameOfFile.split(".").last()=="jpg"){
        state = true;
    }
    return state;
}
