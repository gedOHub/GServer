/*
 * T
#include <iostream>
#include <iostream>
#include <iostream>o change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLogger.cpp
 * Author: gedas
 * 
 * Created on Pirmadienis, 2016, kovas 28, 16.44
 */

#include "GLogger.h"
#include "FileGLogger.h"

GServer::GLogger::GLogger( libconfig::Config* conf ) {
    // Pataisau klases pavadinima
    this->className = this->className + ":GLogger";
    // Bandau nuskaityti DEBUG reiksme is nustatymu failo
    try{
        this->debug = conf->lookup("DEBUG");
        this->logDebug(this->className, "Nuskaityta DEBUG reiksme: " + std::to_string(this->debug));
    } catch( int e ){
        // Pranesimas apie nepavykusi nuskaityma DEBUG reiksmes
        this->logError(this->className, "Nepavyko nuskaityti DEBUG reiksmes");
    }
    
    this->logDebug(this->className, "Objektas sukurtas");
}

GServer::GLogger::~GLogger() {
}

void GServer::GLogger::logInfo(std::string className, std::string message){
    // Laikinas stringas
    string tempString;
    // Formuoju pranesimu eilute
    this->formMessage(className,message,INFO,tempString);
    // Skelbiu pranesimo eilute
    cout << tempString;
}

void GServer::GLogger::logError(std::string className, std::string message){
    // Laikinas stringas
    string tempString;
    // Formuoju pranesimu eilute
    this->formMessage(className,message,ERROR,tempString);
    // Skelbiu pranesimo eilute
    cout << tempString;
}

void GServer::GLogger::logDebug(std::string className, std::string message){
    if(this->debug) {
       // Laikinas stringas
        string tempString;
        // Formuoju pranesimu eilute
        this->formMessage(className,message,DEBUG,tempString);
        // Skelbiu pranesimo eilute
        cout << tempString; 
    }
}

std::string GServer::GLogger::getTime(){
    /* Laiko saugojimo kintamasis milisekundemis 
     * nuo 00:00 hours, Jan 1, 1970 UTC. 
     * Placiau: http://www.cplusplus.com/reference/ctime/time_t/?kw=time_t */
    time_t rawtime;
    
    /* Struktura, sauganti laika sudalinus i atitinkamas sekcijas. 
     * Placiau: http://www.cplusplus.com/reference/ctime/tm/?kw=tm */ 
    struct tm * timeinfo;
    
    /* Buferis, kuriame bus formuojamas laiko atvaizdavimas */
    char buffer[80];

    // Gaunu laika nuo 00:00 hours, Jan 1, 1970 UTC milisekundemis
    time (&rawtime);
    // Isskaidau laika pagal dabartine laiko zona
    timeinfo = localtime(&rawtime);
    // Atvaizduoju laika pagal norima formata
    strftime(buffer,80,"%Y-%m-%d %R:%M:%S",timeinfo);
    // Grazinu suformuota laika
    return std::string(buffer);
}

void GServer::GLogger::formMessage(std::string className, 
        std::string message, int type, std::string & resultString){
    // Kintamasis nusakantis kokio tipo atejo pranesimas
    string tempString;
    // Nustatau pranesimo tipa
    switch(type){
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