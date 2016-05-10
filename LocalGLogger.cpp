/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalGLogger.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 9, 15.46
 */

#include "LocalGLogger.h"

GServer::LocalGLogger::LocalGLogger(int debug) : GLogger(debug) {
    // Nustatau pavadinima
    this->className = this->className + ":LocalGLogger";
    this->logDebug(this->className, "Objektas sukurtas");
}

GServer::LocalGLogger::~LocalGLogger() {
    this->logDebug(this->className, "Objektas sunaikinamas");
}

void GServer::LocalGLogger::formMessage(std::string className,
        std::string message, int type, std::string & resultString) {
    // Kintamasis nusakantis kokio tipo atejo pranesimas
    std::string tempString;
    // Nustatau pranesimo tipa
    switch (type) {
        case INFO:
            // Atejo informacijos pranesimas
            tempString = "INFO";
            break;
        case ERROR:
            // Atejo klaidos pranesimas
            tempString = "ERROR";
            break;
        default:
            // Skaitoma, kad atejo derinimo inforamcijos pranesimas
            tempString = "DEBUG";
            break;
    }
    // Formuoju pranesimo zinute
    messageBuilder << "[" << this->getTime() << "] " << tempString << " [" <<
            className << "] " << message << endl;
    // Nustatau koks gavosi pranesimas
    resultString = this->messageBuilder.str();
    // Isvalau messageBuilder objekta
    this->messageBuilder.str("");
    this->messageBuilder.clear();
}

