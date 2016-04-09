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

GServer::FileGLogger::FileGLogger( std::string filePath, bool debug ) :
LocalGLogger(debug) {
    // Nustatau pavadinima ir paveldejimo grandinele
    this->className = this->className + ":FileGLogger";
    // Pradine reiksme pranesumu failui
    this->logFile = NULL;
    // Bandau atverti faila
    try{
        this->openLogFile(filePath);
        // Tirkinu ar pranesimu failas atvertas
        if(!this->logFile->is_open()){
            GLogger::logError(this->className, 
                    "Nepavyko atverti pranesimu failo");
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
    GLogger::logDebug(this->className, "Objektas sunaikintas");
}

void GServer::FileGLogger::openLogFile( std::string filePath ){
    using namespace std;
    
    // Bandau atverti faila
    try{
        // Kuriu pranesimu failo objekta
        this->logFile = new ofstream(filePath,std::ofstream::app);
    }catch(int e){
        // Stringas saungantis kelia
        std::string temp(filePath);
        
        GLogger::logError(this->className, "Nepavyko atverti failo: " + temp );
        GLogger::logError(this->className, "Klaida: " + 
                string(strerror(errno)));
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
    if(this->DEBUG){
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


