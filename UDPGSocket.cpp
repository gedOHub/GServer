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
#include <arpa/inet.h>

GServer::UDPGSocket::UDPGSocket(GServer::GConfig* conf, GLogger* logger,
        GCommandExecution* command) : GSocket(conf, logger, command) {
    // Nustatau pavadinima
    this->className = this->className + ":UDPGSocket";
    this->commands = command;
    // NUstatu didziausai paketo dydi
    this->MAX_PACKET_SIZE = 65507;

    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::UDPGSocket::~UDPGSocket() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

void GServer::UDPGSocket::listenSocket() {
    // Si funkcija padeda uzblokuoti listen funkcijos kvietima UDP protokokui
}

sockaddr_storage GServer::UDPGSocket::returnClientAddressInfo() {
    return this->serverStorage;
}

int GServer::UDPGSocket::reciveData(char* buffer, int size) {
    int returnValue = 0;
    // Tikrinu ar uzteks buferio norimam kiekiui duomenu
    if (size <= this->buffer.size()) {
        returnValue = recvfrom(this->socket_descriptor, &buffer[0],
                MAX_PACKET_SIZE, 0, (struct sockaddr *)
                &serverStorage, &addr_size);
        this->logger->logDebug(this->className, "Gauta: " + std::to_string(returnValue));
    } else {
        this->logger->logError(this->className, "Per mazas buferis. Laukiama: "
                + std::to_string(size) + " Turima vietos: " +
                std::to_string(this->buffer.size()));
    }
    // Grazinu ka gavau
    return returnValue;
}

int GServer::UDPGSocket::sendData(char* data, int size) {
    int returnValue = 0;
    this->logger->logDebug(this->className, "Reikia issiusti: " + std::to_string(size));

    // Paketas mazesnis, nereikes skaidyti
    // Issiunciu
    returnValue = sendto(this->socket_descriptor, &data[returnValue], size,
            MSG_CONFIRM, (struct sockaddr *) &serverStorage, addr_size);
    this->logger->logDebug(this->className, "Issiusta: " +
            std::to_string(returnValue));


    // Tureciau niekaka nepasiekti
    return returnValue;
}
