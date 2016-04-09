/* 
 * File:   TCPGSocket.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#ifndef TCPGSOCKET_H
#define TCPGSOCKET_H

#include "GSocket.h"


namespace GServer {

    class TCPGSocket : public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        TCPGSocket(GServer::GConfig* conf, GLogger* logger);
        virtual ~TCPGSocket();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** createSocket **
         * Metodas skirtas sukurti sistemos resursaui- socket. Si metoda 
         * realizuoja kiekviena vaiko klase atskirai. 
            config- objektas dirbantis su nustatymu failu*/
        virtual int createSocket(GConfig* conf);
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* TCPGSOCKET_H */

