/* 
 * File:   UDPGSocket.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 23, 00.31
 */

#ifndef UDPGSOCKET_H
#define UDPGSOCKET_H

#include "GSocket.h"

namespace GServer {

    class UDPGSocket : public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        UDPGSocket(GServer::GConfig* conf, GLogger* logger);
        virtual ~UDPGSocket();
        // ##### END Metodai #####
    public:
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
#endif /* UDPGSOCKET_H */

