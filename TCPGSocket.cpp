/* 
 * File:   TCPGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#include "TCPGSocket.h"

GServer::TCPGSocket::TCPGSocket(GServer::GConfig* conf, GLogger* logger) :
GSocket(conf, logger) {
    // Nustatau pavadinima
    this->className = this->className + ":TCPGSocket";
    // Kuriu norima socketa
    this->socket_descriptor = this->createSocket(
            const_cast<char*>(conf->getStringSetting("IP").c_str()),
            const_cast<char*>(conf->getStringSetting("PORT").c_str()),
            AF_INET, SOCK_STREAM, IPPROTO_TCP, AI_PASSIVE);

    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::TCPGSocket::~TCPGSocket() {

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

