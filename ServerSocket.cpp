/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, kovas 27, 04.52
 */

#include "GServerSocket.h"

GServer::GServerSocket::GServerSocket(libconfig::Config* conf, GLogger* logger ): GSocket(conf, logger) {
}

GServer::GServerSocket::~GServerSocket() {
}

