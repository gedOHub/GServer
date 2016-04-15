/* 
 * File:   TCPServerGSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, balandis 10, 03.00
 */

#include "TCPServerGSocket.h"
#include "TCPClientGSocket.h"

GServer::TCPServerGSocket::TCPServerGSocket(GServer::GConfig* conf, 
        GLogger* logger, fd_set& visiSocket, int& maxDeskriptor) 
: TCPGSocket(conf, logger) {
    // Nustatau pavadinima
    this->className = this->className + ":TCPServerGSocket";
    // Objektui reikalingi veiksmai
    
    // Sukuriu socketa klausimuisi
    this->createServerScoket( 
            const_cast<char*>(conf->getStringSetting("IP").c_str()),
            const_cast<char*>(conf->getStringSetting("PORT").c_str()), 
            conf->getIntSetting("NETWORK_TYPE"), SOCK_STREAM, IPPROTO_TCP, 
            AI_PASSIVE);
    // Nustatau skaitomu socketu sarasa
    this->skaitomiSocket = &visiSocket;
    // Pridedu socketa i socketu sarasa
    FD_SET(this->socket_descriptor, this->skaitomiSocket);
    // Tikrinu ar nera didenis deskritprious nei dabartinis
    this->checkMaxDescriptor(maxDeskriptor);
    
    // Objektas sukurtas pilnai
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::TCPServerGSocket::~TCPServerGSocket() {
    // Naikinimas
    this->logger->logDebug(this->className, "Baigiu darba su " + 
            std::to_string(this->socket_descriptor) + " socketu");
    this->close();
    this->logger->logDebug(this->className, "Pasalinu is skaitomu saraso");
    FD_CLR(this->socket_descriptor, this->skaitomiSocket);
    
    // Objektas sunaikintas
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

GServer::GSocket* GServer::TCPServerGSocket::acceptConnection( 
GServer::GConfig* conf, int &maxDescriptor ) {
    GServer::GSocket* returnValue = NULL;
    // Gaunu deskriptoriu
    int descriptor = acceptConnectionDescriptor();
    // Jei pavyko gauti deskriptoriu
    if( descriptor > 0 ){
        // Pavyko gauti, kuriam nauja objekta
        returnValue = new GServer::TCPClientGSocket(descriptor, conf, 
            this->logger, this->skaitomiSocket, maxDescriptor);
    }
    return returnValue;
};