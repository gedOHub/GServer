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
        /** TCPServerGSocket **
         * Metodas skirtas sukurti TCPSERVERGSocket objekta, kuris organizuoja 
         * darba su nauju klientu prijsungimu
         *  conf- objektas, kuris dirba su nustatymu failu
         *  logger- objektas, kuris dirba su pranesimu isvedimu
         *  visiSocket- kintamaisi, kuris saugo visu socketu sarasa
         *  maxDeskriptor- nuoroda i kintamji, kuris saugo didziuasio 
         * desktoriaus reikse */
        TCPServerGSocket(GServer::GConfig* conf, GLogger* logger, 
                fd_set& visiSocket, int& maxDeskriptor);
        
        virtual ~TCPServerGSocket();
        
        /** acceptConnection **
         * Metodas skirtas priimti kliento prisjugimui. Metodas grazina naujai
         *  sukurti kliento objekta */
        virtual GServer::GSocket* acceptConnection( GServer::GConfig* conf, 
        int &maxDescriptor );
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

