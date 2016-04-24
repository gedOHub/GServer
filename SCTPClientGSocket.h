/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPClientGSocket.h
 * Author: gedas
 *
 * Created on Penktadienis, 2016, balandis 15, 20.54
 */

#ifndef SCTPCLIENTGSOCKET_H
#define SCTPCLIENTGSOCKET_H

#include "SCTPGSocket.h"


namespace GServer {

    class SCTPClientGSocket : public SCTPGSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** SCTPClientGSocket **
         * Metodas skirtas sukurti SCTPClientGSocket tipo objektui.
         *  descriptor- gauto nauji prisjungimo descriptrius
         *  conf- objektas dirbantis su nustatymu failu
         *  logger- objektas, kuris organizuoja pranesimu rasyma
         *  visiSocket- sarasas visu skaitomu socketu
         *  maxDescritpor- maksimalaus deskritoriaus reiksme 
            command- nuoroda i komandu aprodjimo objekta*/
        SCTPClientGSocket(int descritor, GServer::GConfig* conf,
                GServer::GLogger* logger, fd_set* visiSocket, 
                int &maxDescriptor, GCommandExecution* command);
        virtual ~SCTPClientGSocket();
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

#endif /* SCTPCLIENTGSOCKET_H */

