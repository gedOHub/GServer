/* 
 * File:   TCPClientGSocket.cpp
 * Author: gedas
 * 
 * Created on Antradienis, 2016, balandis 12, 02.44
 */

#include "TCPClientGSocket.h"

GServer::TCPClientGSocket::TCPClientGSocket(int descritor,
        GServer::GConfig* conf, GServer::GLogger* logger, fd_set* visiSocket,
        int &maxDescriptor, GCommandExecution* commands) 
: TCPGSocket(conf, logger, commands) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":TCPClientGSocket";
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

GServer::TCPClientGSocket::~TCPClientGSocket() {
    this->logger->logDebug(this->className, "Baigiu darba su " +
            std::to_string(this->socket_descriptor) + " socketu");
    this->close();
    this->logger->logDebug(this->className, "Pasalinu is skaitomu saraso");
    FD_CLR(this->socket_descriptor, this->skaitomiSocket);

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}
