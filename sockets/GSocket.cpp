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

GSocket::GSocket() {
    // Nustatau numatytaja socket_descritptor reiksme
    this->socket_descriptor = -1;
}

GSocket::~GSocket() {
}

int GSocket::getSocket(){
    return this->socket_descriptor;
}

