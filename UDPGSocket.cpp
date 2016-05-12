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
    int MAXUDPPaketoDydis = 65507;
    // Paziuriu koks paketas atejo
    //returnValue = recvfrom(this->socket_descriptor, &buffer[0], paketoDydis, MSG_PEEK, (struct sockaddr *) &serverStorage, &addr_size);
    // Nustatau headeri
    //header* head = (struct header*) & buffer[0];
    // Tikrinu ar gavau kazka
    //if (returnValue > 1) {
    // Atejo kazkas
    //paketoDydis = paketoDydis + ntohl(head->lenght);
    //this->logger->logDebug(this->className, "Reikai gauti: " + std::to_string(paketoDydis));
    // Gaunu headeri ir paketa
    returnValue = recvfrom(this->socket_descriptor, &buffer[0], MAXUDPPaketoDydis, 0, (struct sockaddr *) &serverStorage, &addr_size);
    this->logger->logDebug(this->className, "Gauta: " + std::to_string(returnValue));
    //if (returnValue != paketoDydis) {
    //    this->logger->logError(this->className, "Gautas netinkamas dydis. "
    //            "Gauta: " + std::to_string(returnValue) + " Laukta: " +
    //            std::to_string(paketoDydis));
    //}
    //}
    // Grazinu ka gavau
    return returnValue;
}

int GServer::UDPGSocket::sendData(char* data, int size) {
    int returnValue = 0;
    this->logger->logDebug(this->className, "Reikia issiusti: " + std::to_string(size));

    /*
    while (returnValue != size) {
        // Priimu duomenis
        returnValue = returnValue + sendto(this->socket_descriptor,
                &data[returnValue], size - returnValue, 0,
                (struct sockaddr *) &serverStorage, addr_size);
        this->logger->logDebug(this->className, "Jau issiunciau: " + std::to_string(returnValue));
    }
     * */
    returnValue = sendto(this->socket_descriptor, &data[returnValue], size, 
            MSG_CONFIRM , (struct sockaddr *) &serverStorage, addr_size);
    this->logger->logDebug(this->className, "Issiusta: " +
            std::to_string(returnValue));
    // Tureciau niekaka nepasiekti
    return returnValue;
}
