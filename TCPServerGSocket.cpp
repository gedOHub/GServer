/* 
 * File:   TCPServerGSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, balandis 10, 03.00
 */

#include "TCPServerGSocket.h"

GServer::TCPServerGSocket::TCPServerGSocket(GServer::GConfig* conf, 
        GLogger* logger) : TCPGSocket(conf, logger) {
    // Nustatau pavadinima
    this->className = this->className + ":TCPServerGSocket";
    // Objektui reikalingi veiksmai
    
    // Sukuriu socketa klausimuisi
    this->createServerScoket( 
            const_cast<char*>(conf->getStringSetting("IP").c_str()),
            const_cast<char*>(conf->getStringSetting("PORT").c_str()), 
            AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP, AI_PASSIVE);
    
    // Objektas sukurtas pilnai
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::TCPServerGSocket::~TCPServerGSocket() {
    // Naikinimas
    
    // Objektas sunaikintas
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

