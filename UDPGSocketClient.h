/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDPGSocketClient.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, balandis 24, 21.52
 */

#ifndef UDPGSOCKETCLIENT_H
#define UDPGSOCKETCLIENT_H

#include "UDPGSocket.h"


namespace GServer {

    class UDPGSocketClient : public UDPGSocket{
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        UDPGSocketClient( GServer::GConfig* conf, GLogger* logger, 
        GCommandExecution* command );
        virtual ~UDPGSocketClient();
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

#endif /* UDPGSOCKETCLIENT_H */

