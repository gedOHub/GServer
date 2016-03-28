/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileGLogger.cpp
 * Author: gedas
 * 
 * Created on Pirmadienis, 2016, kovas 28, 22.32
 */

#include "FileGLogger.h"

GServer::FileGLogger::FileGLogger( libconfig::Config* conf ) : GLogger(conf) {
    // Nustatau pavadinima ir paveldejimo grandinele
    this->className = this->className + ":FileGLogger";
    // Pradine reiksme pranesumu failui
    this->logFile = NULL;
    // Bandau atverti faila
    try{
        this->openLogFile(conf);
        // Tirkinu ar pranesimu failas atvertas
        if(!this->logFile->is_open()){
            GLogger::logError(this->className, "Nepavyko atverti pranesimu failo");
        }
    }catch(int e){
        GLogger::logError(this->className, "Klaida atveriant pranesimu faila");
    }
    
    this->logDebug(this->className, "Objektas sukurtas");
}

GServer::FileGLogger::~FileGLogger() {
    // Uzveriu pranesimu faila
    GLogger::logDebug(this->className, "Uzveriu pranesuimu faila");
    this->logFile->close();
    GLogger::logDebug(this->className, "Naikinu pranesuimu failo objekta");
    delete this->logFile;
}

void GServer::FileGLogger::openLogFile( libconfig::Config * conf ){
    // Laikinas kintamasis
    string path;
    // Bandau nuskaityti LOGGER_FILE_PATH reiksme
    try{
        path = conf->lookup("LOGGER_FILE_PATH").c_str();
        GLogger::logDebug(this->className, "Nuskaityta LOGGER_FILE_PATH reiksme: " + path);
    }catch(int e){
        GLogger::logError(this->className, "Nepavyko nuskaityti LOGGER_FILE_PATH nustatymo");
    }
    // Bandau atverti faila
    try{
        // Kuriu pranesimu failo objekta
        this->logFile = new ofstream(path.c_str(),std::ofstream::app);
    }catch(int e){
        GLogger::logError(this->className, "Nepavyko atverti failo: " + path);
        GLogger::logError(this->className, "Klaida: " + string(strerror(errno)));
    }
}

void GServer::FileGLogger::logInfo(std::string className, std::string message){
    // Laikinas stringas
    std::string tempString;
    // Formuoju pranesimu eilute
    this->formMessage(className,message,INFO,tempString);
    // Skelbiu pranesimo eilute
    this->logFile->write(tempString.c_str(), tempString.length());
    // Irasai viska i pranesimu faila
    this->logFile->flush();
}

void GServer::FileGLogger::logError(std::string className, std::string message){
    // Laikinas stringas
    std::string tempString;
    // Formuoju pranesimu eilute
    this->formMessage(className,message,ERROR,tempString);
    // Skelbiu pranesimo eilute
    this->logFile->write(tempString.c_str(), tempString.length());
    // Irasai viska i pranesimu faila
    this->logFile->flush();
}
void GServer::FileGLogger::logDebug(std::string className, std::string message){
    // Tirkinu ar derinimo informacija ijungta
    if(this->debug){
        // Laikinas stringas
        std::string tempString;
        // Formuoju pranesimu eilute
        this->formMessage(className,message,INFO,tempString);
        // Skelbiu pranesimo eilute
        this->logFile->write(tempString.c_str(), tempString.length());
        // Irasai viska i pranesimu faila
        this->logFile->flush();
    }
}


