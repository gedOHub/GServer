/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.52
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "GSocket.h"

class ServerSocket : public GSocket {
public:
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    // ##### END Metodai #####
    ServerSocket();
    ServerSocket(const ServerSocket& orig);
    virtual ~ServerSocket();
private:
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    // ##### END Metodai #####
};

#endif /* SERVERSOCKET_H */

