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

    class GCommandExecution;
    
    class UDPClientGSocket : public UDPGSocket{
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        UDPClientGSocket( GServer::GConfig* conf, GLogger* logger, 
        GCommandExecution* command, int id,int serverSocket, 
                sockaddr_storage klientoDuomenys );
        virtual ~UDPClientGSocket();
        // ##### END Metodai #####      
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /*** serverSocket ***
         * Kintamasis skirtas saugoti serverio socketa, per kuri bus siunciami
         *  duomenys klientams */
        int serverSocket;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* UDPGSOCKETCLIENT_H */

