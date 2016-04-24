/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPServerGSocket.h
 * Author: gedas
 *
 * Created on Antradienis, 2016, balandis 12, 04.54
 */

#ifndef SCTPSERVERGSOCKET_H
#define SCTPSERVERGSOCKET_H

#include "SCTPGSocket.h"

namespace GServer {

    class SCTPServerGSocket : public SCTPGSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** TCPServerGSocket **
         * Metodas skirtas sukurti SCTPServerGSocket objekta, kuris organizuoja 
         * darba su nauju klientu prijsungimu per SCTP portokola
         *  conf- objektas, kuris dirba su nustatymu failu
         *  logger- objektas, kuris dirba su pranesimu isvedimu
         *  visiSocket- kintamaisi, kuris saugo visu socketu sarasa
         *  maxDeskriptor- nuoroda i kintamji, kuris saugo didziuasio 
         * desktoriaus reikse 
            command- nuoroda i komandu apdorojimo objekta*/
        SCTPServerGSocket(GServer::GConfig* conf, GLogger* logger, 
                fd_set& visiSocket, int& maxDeskriptor, 
                GCommandExecution* command);
        virtual ~SCTPServerGSocket();
        
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

#endif /* SCTPSERVERGSOCKET_H */

