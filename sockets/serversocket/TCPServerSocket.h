/* 
 * File:   TCPServerSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.53
 */

#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#include "ServerSocket.h"


class TCPServerSocket : public ServerSocket {
public:
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    TCPServerSocket();
    TCPServerSocket(const TCPServerSocket& orig);
    virtual ~TCPServerSocket();
    // ##### END Metodai #####    
private:
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    // ##### END Metodai #####
};

#endif /* TCPSERVERSOCKET_H */

