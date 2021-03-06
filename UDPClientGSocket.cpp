/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDPGSocketClient.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, balandis 24, 21.52
 */

#include "UDPClientGSocket.h"
#include "GLogger.h"

GServer::UDPClientGSocket::UDPClientGSocket(GServer::GConfig*
        conf, GLogger* logger, GCommandExecution* command, int id, int serverSocket,
        sockaddr_storage klientoDuomenys) : UDPGSocket(conf, logger, command) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":UDPGSocketClient";
    // Nustatau socketo numeri
    this->socket_descriptor = id;
    // Nustatau adreso informacija
    this->serverStorage = klientoDuomenys;
    // Nustatua per kuri socketa siusti
    this->serverSocket = serverSocket;

    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::UDPClientGSocket::~UDPClientGSocket() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

int GServer::UDPClientGSocket::sendData(char * data, int size){
    int temp  = this->socket_descriptor, resultValue= 0;
    // Nustatau laikinai deskritpriu
    this->socket_descriptor = this->serverSocket;
    // Issiucui duomensi
    resultValue = GServer::UDPGSocket::sendData(data, size);
    // ATstatau deskritpriu
    this->socket_descriptor = temp;
    // Grazinu rezultatus
    return resultValue;
}

void GServer::UDPClientGSocket::sendKeepAliveAck(){
    if(this->sendData(this->buffer.data(), 1) < 1 ) {
        this->logger->logError(this->className, "Nepavyko issiusti KEEP_ALIVE_ACK paketo");
    }
}

