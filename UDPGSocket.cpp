/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDPGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 23, 00.31
 */

#include "UDPGSocket.h"
#include "GSocket.h"
#include "GLogger.h"
#include "UDPClientGSocket.h"

GServer::UDPGSocket::UDPGSocket(GServer::GConfig* conf, GLogger* logger,
        GCommandExecution* command) : GSocket(conf, logger, command) {
    // Nustatau pavadinima
    this->className = this->className + ":UDPGSocket";
    this->commands = command;

    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::UDPGSocket::~UDPGSocket() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

void GServer::UDPGSocket::listenSocket() {
    // Si funkcija padeda uzblokuoti listen funkcijos kvietima UDP protokokui
}

int GServer::UDPGSocket::reciveData(char* buffer, int size) {
    int returnValue = -1;
    // Siusti duomenis
    returnValue = recvfrom(this->socket_descriptor, buffer, size, MSG_WAITALL,
            (struct sockaddr *) &serverStorage, &addr_size);
    // Pranesimas gautus duomenis
    this->logger->logDebug(this->className,
            std::to_string(this->socket_descriptor) + ":" +
            std::to_string(this->buffer.size()) + " <---" +
            std::to_string(returnValue));

    return returnValue;
}

sockaddr_storage GServer::UDPGSocket::returnClientAddressInfo() {
    return this->serverStorage;
}

int GServer::UDPGSocket::sendData(char* data, int size) {
    int send = 0;
    while (send != size) {
        send = send + sendto(this->socket_descriptor, data, size, 0,
                (sockaddr*) & this->remoteAddress, this->remoteAddressSize);
        this->logger->logDebug(this->className,
                std::to_string(this->socket_descriptor) + ":" +
                std::to_string(size) + " ---> " + std::to_string(send));
    }
    return send;
}
