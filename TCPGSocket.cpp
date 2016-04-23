/* 
 * File:   TCPGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#include "TCPGSocket.h"

GServer::TCPGSocket::TCPGSocket(GServer::GConfig* conf, GLogger* logger, 
        GCommandExecution* command) : GSocket(conf, logger) {
    // Nustatau pavadinima
    this->className = this->className + ":TCPGSocket";
    // Priskiriu nuorda i pranesimu objekta
    this->logger = logger;
    // Priskiriu nuoroda i komandu vykdymo objekta
    this->commands = command;

    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::TCPGSocket::~TCPGSocket() {

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

int GServer::TCPGSocket::sendData(char * data, int size){
    int returnValue = -1;
    // Siusti duomenis
    returnValue = send(this->socket_descriptor, &data, size, 0 );
    // Pranesimas issiutus duomenis
    this->logger->logDebug(this->className, 
            std::to_string(this->socket_descriptor) + " --->" + 
            std::to_string(returnValue));
    return returnValue;
}

int GServer::TCPGSocket::reciveData(){
    int returnValue = -1;
    // Siusti duomenis
    returnValue = recv(this->socket_descriptor, this->buffer.data(), 
            this->buffer.size(), 0 );
    // Pranesimas gautus duomenis
    this->logger->logDebug(this->className, 
            std::to_string(this->socket_descriptor) + ":" + 
            std::to_string(this->buffer.size()) + " <---" + 
            std::to_string(returnValue));
    // Perduodu duomenis apdorojimui
    
    return returnValue;
}
