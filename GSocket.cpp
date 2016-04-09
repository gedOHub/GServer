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

// TODO: lookupus perdaryti per objekta
GServer::GSocket::GSocket( GServer::GConfig* conf, GLogger* logger ) : MAX_BUFFER_SIZE(conf->getIntSetting("MAX_SOCKET_BUFFER_SIZE")) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":GSocket";
    // Nustatau numatytaja socket_descritptor reiksme
    this->socket_descriptor = -1;
    // Nustatau logeri
    this->logger = logger;
    // Nustatu buferio dydi
    this->buffer.resize(conf->getIntSetting("SOCKET_BUFFER_SIZE"));
    // Spausdinu nustatytai buferio dydi
    this->logger->logDebug(this->className, "Sukurto buferio dydis: " + 
            std::to_string(this->buffer.size()));
    // Tirkinu ar pavyko sukurti buferi
    if(this->buffer.size() < conf->getIntSetting("SOCKET_BUFFER_SIZE")){
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

int GServer::GSocket::resizeBuffer(int newSize){
    // Tikrinu ar nuajas dydis nera didesnis nei leistinas
    if(newSize > this->MAX_BUFFER_SIZE){
        this->logger->logInfo(this->className, "Norimas dydis: " + 
                std::to_string(newSize) + 
                " per didelis. Nustatomas maksimalus dydis: " + 
                std::to_string(this->MAX_BUFFER_SIZE));
        // Didenis, nustatau maksimalu dydi
        return this->setBufferSize(this->MAX_BUFFER_SIZE);
    }
    // Naujas dydis mazesnis nei nurimas
    this->logger->logInfo(this->className, "Nustatau tauja dydi: " + newSize);
    // Nustatau nauja dydi
    return this->setBufferSize(newSize);
}

int GServer::GSocket::setBufferSize(int newSize){
    // Nustatau nauja buferio dydi
    this->buffer.resize(newSize);
    // Grazinu nauja dydi
    return this->buffer.size();
}

int GServer::GSocket::send(vector<char>* data){
    this->logger->logError(this->className,"Neigyvendinta SEND funkcija");
    return -1;
}

int GServer::GSocket::recive(vector<char>* data){
    this->logger->logError(this->className,"Neigyvendinta RECIVE funkcija");
    return -1;
}
