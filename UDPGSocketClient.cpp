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

#include "UDPGSocketClient.h"

GServer::UDPGSocketClient::UDPGSocketClient( GServer::GConfig* 
conf, GLogger* logger,  GCommandExecution* command ) : UDPGSocket(conf, 
        logger, command) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":UDPGSocketClient";
    
    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::UDPGSocketClient::~UDPGSocketClient() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

