/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDPServerSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.53
 */

#ifndef UDPSERVERSOCKET_H
#define UDPSERVERSOCKET_H

#include "ServerSocket.h"


class UDPServerSocket : public ServerSocket {
public:
    UDPServerSocket();
    UDPServerSocket(const UDPServerSocket& orig);
    virtual ~UDPServerSocket();
private:

};

#endif /* UDPSERVERSOCKET_H */

