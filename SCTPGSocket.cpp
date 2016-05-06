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

int GServer::SCTPGSocket::reciveData( char* buffer, int size ){
    int returnValue = -1;
    // Siusti duomenis

    char IP[NI_MAXHOST]; //The clienthost will hold the IP address.
    char PORT[NI_MAXSERV];

    returnValue = recvfrom(this->socket_descriptor, buffer, size, 0,
            (struct sockaddr *) &serverStorage, &addr_size);
    int theErrorCode = getnameinfo((struct sockaddr *) &serverStorage,
            sizeof (sockaddr), IP, sizeof (IP), PORT, sizeof (PORT),
            NI_NUMERICHOST | NI_NUMERICSERV);
    this->logger->logDebug(this->className, string(IP) + ":" + string(PORT));
    // Pranesimas gautus duomenis
    this->logger->logDebug(this->className,
            std::to_string(this->socket_descriptor) + ":" +
            std::to_string(this->buffer.size()) + " <---" +
            std::to_string(returnValue));

    return returnValue;
}

int GServer::SCTPGSocket::sendData(char* data, int size) {
    char IP[NI_MAXHOST]; //The clienthost will hold the IP address.
    char PORT[NI_MAXSERV];

    int theErrorCode = getnameinfo((struct sockaddr *) &serverStorage,
            sizeof (sockaddr), IP, sizeof (IP), PORT, sizeof (PORT),
            NI_NUMERICHOST | NI_NUMERICSERV);
    int send = 0;
    while (send != size && send != -1) {
        this->logger->logDebug(this->className, string(IP) + ":" + string(PORT));
        send = send + sendto(this->socket_descriptor, data, size, 0,
                (struct sockaddr *) &serverStorage, sizeof(sockaddr));
        this->logger->logDebug(this->className,
                std::to_string(this->socket_descriptor) + ":" +
                std::to_string(size) + " ---> " + std::to_string(send));
    }
    this->logger->logDebug(this->className,string(data,size));
    return send;
}