/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPClientGSocket.cpp
 * Author: gedas
 * 
 * Created on Penktadienis, 2016, balandis 15, 20.54
 */

#include "SCTPClientGSocket.h"

GServer::SCTPClientGSocket::SCTPClientGSocket( int descritor, 
        GServer::GConfig* conf, GServer::GLogger* logger, fd_set* visiSocket,
        int &maxDescriptor, GCommandExecution* command ) : 
        SCTPGSocket(conf, logger, command) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":SCTPClientGSocket";
    // Priskiriu logeri
    this->logger = logger;
    // Pransu deskriptoriu
    this->socket_descriptor = descritor;
    this->logger->logDebug(this->className, "Descriptorius: " +
            std::to_string(this->socket_descriptor));
    // Nustatau skaitomu socketu sarasa
    this->skaitomiSocket = visiSocket;
    // Pridedu socketa i socketu sarasa
    FD_SET(this->socket_descriptor, this->skaitomiSocket);
    //Tikrinu maksimalu deskriptoriu
    this->checkMaxDescriptor(maxDescriptor);
    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::SCTPClientGSocket::~SCTPClientGSocket() {
    this->logger->logDebug(this->className, "Baigiu darba su " +
            std::to_string(this->socket_descriptor) + " socketu");
    this->close();
    this->logger->logDebug(this->className, "Pasalinu is skaitomu saraso");
    FD_CLR(this->socket_descriptor, this->skaitomiSocket);

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

