/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCPClientGSocket.cpp
 * Author: gedas
 * 
 * Created on Antradienis, 2016, balandis 12, 02.44
 */

#include "TCPClientGSocket.h"

GServer::TCPClientGSocket::TCPClientGSocket( int descritor, 
        GServer::GConfig* conf, GServer::GLogger* logger, fd_set& visiSocket ) : 
        TCPGSocket( conf, logger ) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":TCPClientGSocket";
    // Priskiriu logeri
    this->logger = logger;
    // Pransu deskriptoriu
    this->socket_descriptor = descritor;
    this->logger->logDebug(this->className, "Descriptorius: " + 
            std::to_string(this->socket_descriptor) );
    // Pridedu objekta prie visu skaitomu sokcetu saraso
    FD_SET(this->socket_descriptor, &visiSocket);
    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::TCPClientGSocket::~TCPClientGSocket() {
    this->close();

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

