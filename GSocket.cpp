/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, kovas 27, 04.51
 */

#include "GSocket.h"

GServer::GSocket::GSocket() {
    // Nustatau objekto pavadinima
    this->className = "GSocket";
    
    // Nustatau numatytaja socket_descritptor reiksme
    this->socket_descriptor = -1;
    
    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::GSocket::~GSocket() {
}

