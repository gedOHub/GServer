/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPGSocket.h
 * Author: gedas
 *
 * Created on Antradienis, 2016, balandis 12, 04.41
 */

#ifndef SCTPGSOCKET_H
#define SCTPGSOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#include "GSocket.h"
#include "exitCodes.h"


namespace GServer {

    class SCTPGSocket :public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        SCTPGSocket(GConfig* conf, GLogger* logger);
        virtual ~SCTPGSocket();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** recive **
         * Metodas skirtas gauti duomenis is tinklo. Sia funkcija turi 
         * igyvendinti kiekvienas protokolas savaitp. Rezultatas- gautu 
         * duomenu kiekis. */
        //virtual int reciveData();
        
        /** createSocket **
         * Metodas skirtas sukurti sistemos resursaui- socket. Si metoda 
         * realizuoja kiekviena vaiko klase atskirai. 
            socketFamily- kokio tipo tinklu bus bendraujama
            socketType- kokiu principu bus bendraujama
            socketProtocol- kokiu protokolu bus bendraujama
            socketFlag- papildomi socket nustatymai
            result - kintamsis saugnatis gautus rezultatus is IP ir PORT 
         * kombinacijos
         Placiau: https://msdn.microsoft.com/en-us/library/windows/desktop/ms737530(v=vs.85).aspx*/
        virtual int createSocket(char* ip, char* port, int socketFamily,
                int socketType, int socketProtocol, int socketFlag, 
                addrinfo *& result);
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* SCTPGSOCKET_H */

