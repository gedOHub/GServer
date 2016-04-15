/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCPClientGSocket.h
 * Author: gedas
 *
 * Created on Antradienis, 2016, balandis 12, 02.43
 */

#ifndef TCPCLIENTGSOCKET_H
#define TCPCLIENTGSOCKET_H

#include "GLogger.h"
#include "TCPGSocket.h"

namespace GServer {

    class TCPClientGSocket : public TCPGSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** TCPClientGSocket **
         * Metodas skirtas sukurti TCPClientGSocket tipo objektui.
         *  descriptor- gauto nauji prisjungimo descriptrius
         *  conf- objektas dirbantis su nustatymu failu
         *  logger- objektas, kuris organizuoja pranesimu rasyma
         *  visiSocket- sarasas visu skaitomu socketu
         *  maxDescritpor- maksimalaus deskritoriaus reiksme */
        TCPClientGSocket( int descritor, GServer::GConfig* conf,
                GServer::GLogger* logger, fd_set* visiSocket, 
                int &maxDescriptor );
        virtual ~TCPClientGSocket();
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
#endif /* TCPCLIENTGSOCKET_H */

