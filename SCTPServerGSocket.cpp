/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPServerGSocket.cpp
 * Author: gedas
 * 
 * Created on Antradienis, 2016, balandis 12, 04.54
 */

#include "SCTPServerGSocket.h"

GServer::SCTPServerGSocket::SCTPServerGSocket(GServer::GConfig* conf,
        GLogger* logger, fd_set& visiSocket, int& maxDeskriptor) :
SCTPGSocket(conf, logger) {
    // Nustatau pavadinima
    this->className = this->className + ":SCTPServerGSocket";
    // Objektui reikalingi veiksmai

    // Sukuriu socketa klausimuisi
    this->createServerScoket(
            const_cast<char*> (conf->getStringSetting("IP").c_str()),
            const_cast<char*> (conf->getStringSetting("PORT").c_str()),
            conf->getIntSetting("NETWORK_TYPE"), SOCK_STREAM, IPPROTO_SCTP,
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

GServer::SCTPServerGSocket::~SCTPServerGSocket() {
    // Naikinimas
    this->logger->logDebug(this->className, "Baigiu darba su " +
            std::to_string(this->socket_descriptor) + " socketu");
    this->close();
    this->logger->logDebug(this->className, "Pasalinu is skaitomu saraso");
    FD_CLR(this->socket_descriptor, this->skaitomiSocket);

    // Objektas sunaikintas
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

GServer::GSocket* GServer::SCTPServerGSocket::acceptConnection(
        GServer::GConfig* conf, int &maxDescriptor){
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
}

