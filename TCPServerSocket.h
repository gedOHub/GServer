/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCPServerSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 00.26
 */

#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#include "ServerSocket.h"


class TCPServerSocket : ServerSocket {
public:
    TCPServerSocket();
    TCPServerSocket(const TCPServerSocket& orig);
    virtual ~TCPServerSocket();
private:

};

#endif /* TCPSERVERSOCKET_H */

