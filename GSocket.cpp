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

GServer::GSocket::GSocket(GServer::GConfig* conf, GLogger* logger) : MAX_BUFFER_SIZE(conf->getIntSetting("MAX_SOCKET_BUFFER_SIZE")) {
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
    if (this->buffer.size() < conf->getIntSetting("SOCKET_BUFFER_SIZE")) {
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

int GServer::GSocket::resizeBuffer(int newSize) {
    // Tikrinu ar nuajas dydis nera didesnis nei leistinas
    if (newSize > this->MAX_BUFFER_SIZE) {
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

int GServer::GSocket::setBufferSize(int newSize) {
    // Nustatau nauja buferio dydi
    this->buffer.resize(newSize);
    // Grazinu nauja dydi
    return this->buffer.size();
}

int GServer::GSocket::send(vector<char>* data) {
    this->logger->logError(this->className, "Neigyvendinta SEND funkcija");
    return -1;
}

int GServer::GSocket::recive(vector<char>* data) {
    this->logger->logError(this->className, "Neigyvendinta RECIVE funkcija");
    return -1;
}

int GServer::GSocket::createSocket(char* ip, char* port, int socketFamily,
        int socketType, int socketProtocol, int socketFlag) {
    // Grazinamo socketo numeris
    int returnValue = -1;
    // Strukturos kuriso saugos visa inforamcija apie norima adresa ir prievada
    addrinfo *result = NULL;
    addrinfo hints;
    // Isvalo filtruojancia
    memset(&hints, sizeof (hints), sizeof (struct addrinfo));
    // Nustatom norimus parametrus
    hints.ai_family = socketFamily;
    hints.ai_socktype = socketType;
    hints.ai_protocol = socketProtocol;
    hints.ai_flags = socketFlag;
    // Bandau gauti galimus rezultatus
    int searchResult = getaddrinfo(ip, port, &hints, &result);
    // TIkrinu ar neivyko klaida
    if (searchResult != 0) {
        // Ivyko klaida
        // Pranesu kas ivyko
        this->logger->logError(this->className, gai_strerror(searchResult));
        exit(GServer::EXIT_CODES::UNABLE_TO_GET_ADDRESS_INFO);
    }
    // Begu per visus galimus variantus
    for (addrinfo* i = result; i != NULL; i->ai_next) {
        returnValue = socket(i->ai_family, i->ai_socktype, i->ai_protocol);
        // Tikrinu ar pavyko sukurti socketa
        if (returnValue == -1) {
            // Nepavyko, einu per galimus varaintus toliau
            this->logger->logDebug(this->className, "Nepavyko sukurti socketo");
            continue;
        } else
            // Pavyko, baigiu eijima per variantus
            break;
    }
    // Tirkinu ar pavyko kazka gauti
    if(returnValue == -1){
        this->logger->logDebug(this->className, "Nepavyko sukurti socketo");
        exit(GServer::EXIT_CODES::UNABLE_TO_CREATE_SOCKET);
    }
    // Grazinu socketo numeri
    this->logger->logDebug(this->className, "Grazinamo socketo numeris- " +
            std::to_string(returnValue));
    return returnValue;
}
