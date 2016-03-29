/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCPServerSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, kovas 27, 04.53
 */

#include "TCPServerSocket.h"

GServer::TCPServerSocket::TCPServerSocket(libconfig::Config* conf, GLogger* logger ) :ServerSocket(conf,logger) {
}

GServer::TCPServerSocket::~TCPServerSocket() {
}

