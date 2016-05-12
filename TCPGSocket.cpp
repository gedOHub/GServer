/* 
 * File:   TCPGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#include "TCPGSocket.h"

GServer::TCPGSocket::TCPGSocket(GServer::GConfig* conf, GLogger* logger,
        GCommandExecution* command) : GSocket(conf, logger, command) {
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

int GServer::TCPGSocket::sendData(char* data, int size) {
    /*int returnValue = -1;
    this->logger->logDebug(this->className, "Reikia issiusti: " + std::to_string(size));
    // Kintamais rodantis kiek jau issiusta
    int issiusta = 0;
    while (issiusta != size) {
        // Siunciu duomenis
        // Siusti duomenis
        issiusta = issiusta + send(this->socket_descriptor, &data[issiusta], (size - issiusta), 0);
        // Pranesimas issiutus duomenis
        this->logger->logDebug(this->className,
                std::to_string(this->socket_descriptor) + " ---> " +
                std::to_string(issiusta));
    }
    return issiusta;*/

    int issiusta = 0, likosiusti = size;
    while (likosiusti != 0) {
        issiusta = issiusta + send(this->socket_descriptor, &data[issiusta], likosiusti, 0);
        // Pranesimas issiutus duomenis
        this->logger->logDebug(this->className, "Socket[" +
                std::to_string(this->socket_descriptor) + "] Turiu issiusti: " +
                std::to_string(likosiusti) + " ---> " +
                std::to_string(issiusta));
        likosiusti = (size - issiusta);
    }
    return issiusta;
}

int GServer::TCPGSocket::reciveData(char* buffer, int size) {
    return recv(this->socket_descriptor, buffer, size, 0);
}
