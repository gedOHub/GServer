/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDPGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 23, 00.31
 */

#include "UDPGSocket.h"
#include "GSocket.h"

GServer::UDPGSocket::UDPGSocket(GServer::GConfig* conf, GLogger* logger) 
:GSocket(conf,logger) {
    // Nustatau pavadinima
    this->className = this->className + ":UDPGSocket";

    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::UDPGSocket::~UDPGSocket() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

