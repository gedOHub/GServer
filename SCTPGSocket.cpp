/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPGSocket.cpp
 * Author: gedas
 * 
 * Created on Antradienis, 2016, balandis 12, 04.41
 */

#include "SCTPGSocket.h"
#include "GLogger.h"

GServer::SCTPGSocket::SCTPGSocket(GConfig* conf, GLogger* logger, 
        GCommandExecution* command) : GSocket(conf, logger, command) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":SCTPGSocket";
    
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::SCTPGSocket::~SCTPGSocket() {
    
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

/*
int GServer::SCTPGSocket::createSocket(char* ip, char* port, int socketFamily, 
        int socketType, int socketProtocol, int socketFlag, addrinfo*& result){
    // Grazinamo socketo numeris
    int returnValue = -1;
    // Bandau kurti socketa
    returnValue = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP); 
    
    // Tirkinu ar pavyko kazka gauti
    if (returnValue == -1) {
        this->logger->logDebug(this->className, "Nepavyko sukurti socketo");
        exit(GServer::EXIT_CODES::UNABLE_TO_CREATE_SOCKET);
    }
    // Grazinu socketo numeri
    this->logger->logDebug(this->className, "Grazinamo socketo numeris- " +
            std::to_string(returnValue));
    return returnValue;
}
 * */