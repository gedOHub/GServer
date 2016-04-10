/* 
 * File:   TCPServerGSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, balandis 10, 03.00
 */

#ifndef TCPSERVERGSOCKET_H
#define TCPSERVERGSOCKET_H

#include "TCPGSocket.h"


namespace GServer {

    class TCPServerGSocket : public TCPGSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        TCPServerGSocket(GServer::GConfig* conf, GLogger* logger);
        virtual ~TCPServerGSocket();
        // ##### END Metodai #####        
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}
#endif /* TCPSERVERGSOCKET_H */

