/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   STCPServerSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, kovas 27, 04.54
 */

#include "STCPServerSocket.h"

GServer::STCPServerSocket::STCPServerSocket(libconfig::Config* conf, GLogger* logger) : GServerSocket(conf,logger) {
}

GServer::STCPServerSocket::~STCPServerSocket() {
}

