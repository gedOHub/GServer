/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, kovas 27, 04.51
 */

#include "GSocket.h"
#include "exitCodes.h"

GServer::GSocket::GSocket( libconfig::Config* conf, GLogger* logger ) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":GSocket";
    // Nustatau numatytaja socket_descritptor reiksme
    this->socket_descriptor = -1;
    // Nustatau logeri
    this->logger = logger;
    // Laikinas kintamsis saugoti buferio dydziui
    int bufferSize = -1;
    // Nuskaitau buferio dydi
    try{
        // Gaunu buferio dydi
        bufferSize = conf->lookup("SOCKET_BUFFER_SIZE");
        this->logger->logDebug(this->className, 
                "Nuskaityta buferio dyzio reiksme: " + 
                std::to_string(bufferSize));
    }catch(int e){
        this->logger->logError(this->className, 
            "Klaida nuskaitant SOCKET_BUFFER_SIZE nustatymo reiksme. Klaidos kodas: " 
            + std::to_string(e));
    }
    // Nustatu buferio dydi
    this->buffer.resize(bufferSize);
    // Spausdinu nustatytai buferio dydi
    this->logger->logDebug(this->className, "Sukurto buferio dydis: " + 
            std::to_string(this->buffer.size()));
    // Tirkinu ar pavyko sukurti buferi
    if(this->buffer.size() < bufferSize){
        // Buferio dydis per mazas
        this->logger->logError(this->className, 
                "Nepavyko sukurti norimo dydzio buferio");
        // Nutraukiamas programos darbas
        exit(GServer::EXIT_CODES::SOCKET_BUFFER_TO_SMALL);
    }
    
    // Atspausdinu derinimo inforamcija
    this->logger->logDebug(this->className, "socket_descriptor reiksme: " + 
            std::to_string(this->socket_descriptor));
    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::GSocket::~GSocket() {
    
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}
