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

