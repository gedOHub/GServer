/* 
 * File:   UDPServerGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 23, 00.48
 */

#include "UDPServerGSocket.h"

GServer::UDPServerGSocket::UDPServerGSocket(GServer::GConfig* conf,
        GLogger* logger, fd_set& visiSocket, int& maxDeskriptor,
        GCommandExecution* command) : UDPGSocket(conf, logger, command) {

    // Nustatau pavadinima
    this->className = this->className + ":UDPServerGSocket";
    // Objektui reikalingi veiksmai

    // Sukuriu socketa klausimuisi
    this->createServerScoket(
            const_cast<char*> (conf->getStringSetting("IP").c_str()),
            const_cast<char*> (conf->getStringSetting("PORT").c_str()),
            conf->getIntSetting("NETWORK_TYPE"), SOCK_DGRAM, IPPROTO_UDP,
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

GServer::UDPServerGSocket::~UDPServerGSocket() {
    // Naikinimas
    this->logger->logDebug(this->className, "Baigiu darba su " +
            std::to_string(this->socket_descriptor) + " socketu");
    this->close();
    this->logger->logDebug(this->className, "Pasalinu is skaitomu saraso");
    FD_CLR(this->socket_descriptor, this->skaitomiSocket);

    // Objektas sunaikintas
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

int GServer::UDPServerGSocket::reciveData(){
    // Tirkinu ar gauti duomenys is naujo kliento ar jau esamo
    
}

GServer::GSocket* GServer::UDPServerGSocket::acceptConnection(
        GServer::GConfig* conf, int& maxDescriptor) {
    this->reciveData();
    return NULL;
}
