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
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    UDPServerSocket();
    UDPServerSocket(const UDPServerSocket& orig);
    virtual ~UDPServerSocket();
    // ##### END Metodai #####
private:
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    // ##### END Metodai #####
};

#endif /* UDPSERVERSOCKET_H */
