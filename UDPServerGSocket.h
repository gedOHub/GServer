/* 
 * File:   UDPServerGSocket.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 23, 00.47
 */

#ifndef UDPSERVERGSOCKET_H
#define UDPSERVERGSOCKET_H

#include "UDPGSocket.h"


namespace GServer {

    class UDPServerGSocket : public UDPGSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** UDPServerGSocket **
         * Metodas skirtas sukurti UDPServerGSocket objekta, kuris organizuoja 
         * darba su nauju klientu prijsungimu per UDP protokola
         *  conf- objektas, kuris dirba su nustatymu failu
         *  logger- objektas, kuris dirba su pranesimu isvedimu
         *  visiSocket- kintamaisi, kuris saugo visu socketu sarasa
         *  maxDeskriptor- nuoroda i kintamji, kuris saugo didziuasio 
         * desktoriaus reikse */
        UDPServerGSocket(GServer::GConfig* conf, GLogger* logger, 
                fd_set& visiSocket, int& maxDeskriptor);
        virtual ~UDPServerGSocket();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** listen **
         * Metodas sksirtas pradeti klausimuisi klientu prisjungimu nurodytu 
         * prievadu. Placiau: http://linux.die.net/man/2/listen
         * UDP nepaliko listen saukinio */
        virtual void listenSocket(){};
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* UDPSERVERGSOCKET_H */

