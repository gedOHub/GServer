/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPGSocket.cpp
 * Author: gedas
 * 
 * Created on Antradienis, 2016, balandis 12, 04.41
 */

#include "SCTPGSocket.h"

GServer::SCTPGSocket::SCTPGSocket(GConfig* conf, GLogger* logger) : 
GSocket(conf, logger) {
}

GServer::SCTPGSocket::~SCTPGSocket() {
}

